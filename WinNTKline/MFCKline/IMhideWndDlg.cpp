// IMhideWndDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "afxdialogex.h"
#include "MFCKline.h"
#include "RegistDlg.h"
#include "IMhideWndDlg.h"
#include "SetMarkDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//收缩模式
#define HM_NONE     0   //不收缩
#define HM_TOP      1   //置顶收缩
#define HM_BOTTOM   2   //置底收缩
#define HM_LEFT     3   //靠左收缩
#define HM_RIGHT    4   //靠右收缩

#define CM_ELAPSE   200 //检测鼠标是否离开窗口的时间间隔
#define HS_ELAPSE   5   //隐藏或显示过程每步的时间间隔
#define HS_STEPS    10  //隐藏或显示过程分成多少步

#define INTERVAL    20  //触发粘附时鼠标与屏幕边界的最小间隔,单位为象素
#define INFALTE     10  //触发收缩时鼠标与窗口边界的最小间隔,单位为象素
#define MINCX       200 //窗口最小宽度
#define MINCY       400 //窗口最小高度

IMPLEMENT_DYNAMIC(CIMhideWndDlg, CDialogEx)

CIMhideWndDlg::CIMhideWndDlg(IMUSR* imusr, CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_IMHIDEWND, pParent)
{
	//{{AFX_DATA_INIT(CIMhideWndDlg)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32

	if (imusr != NULL)
		memcpy(&oimusr, imusr, sizeof(IMUSR));

	m_isSizeChanged = FALSE;
	m_isSetTimer = FALSE;
	m_hsFinished = TRUE;
	m_hiding = FALSE;

	m_oldWndHeight = MINCY;
	m_taskBarHeight = 30;
	m_edgeHeight = 0;
	m_edgeWidth = 0;
	m_hideMode = HM_NONE;
}

CIMhideWndDlg::~CIMhideWndDlg()
{
}

void CIMhideWndDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TIMER, m_timeStatus);
	DDX_Control(pDX, IDC_COMM, m_commbo);
	DDX_Control(pDX, IDC_LISTFRND, m_frndList);
	DDX_Control(pDX, IDC_SEEKNEW, m_AddBtn);
}


BEGIN_MESSAGE_MAP(CIMhideWndDlg, CDialogEx)
	//{{AFX_MSG_MAP(CIMhideWndDlg)
	ON_WM_SYSCOMMAND()
	//ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_NCHITTEST()
	ON_WM_TIMER()
	ON_WM_SIZING()
	ON_WM_CREATE()
	ON_WM_MOVING()
	//}}AFX_MSG_MAP
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_EXIT, &CIMhideWndDlg::OnBnClickedExit)
	ON_CBN_SELCHANGE(IDC_COMM, &CIMhideWndDlg::OnCbnSelchangeComm)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTFRND, &CIMhideWndDlg::OnNMDblclkListfrnd)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_SEEKNEW, &CIMhideWndDlg::OnBnClickedSeeknew)
END_MESSAGE_MAP()

void ShowMsg(void* lp) {
	int len;
	char rcv[128];
	char info[256];
	CIMhideWndDlg curWin;
	struct LPR* lpr = (struct LPR*)lp;
	do {
		len = recv(lpr->sock, rcv, 256, 0);
		if (len != 256) {
			Sleep(100);
			//curWin.m_timeStatus.SetWindowText("connection lost\n");
			//exit(0);
			return;
		};
		EnterCriticalSection(&lpr->wrcon);
		switch (rcv[1])
		{
		case 10:
			sprintf_s(info, 32, "join to gruop %s successfully\n", (lpr->msg->lastgroup + 8));
			break;
		case 11:
			sprintf_s(info, 32, "join to gruop %s rejected :%s\n", (lpr->msg->lastgroup + 8), (rcv + 32));
			break;
		case 20:
			sprintf_s(info, 128, "%s\n", (rcv + 8));
			break;
		case 21:
			sprintf_s(info, 128, "%s\n", (rcv + 32));
			break;
		case 22:
			sprintf_s(info, 256, "info of %s:\t %s \n", (rcv + 8), (rcv + 32));
			break;
		case 30:
			sprintf_s(info, 1024, "you said to %s : %s\n", (lpr->msg->lastuser + 8), (lpr->msg->lastuser + 32));
			break;
		case 32:
			sprintf_s(info, 256, "talk to %s failed\n", (lpr->msg->lastuser + 8));
			break;
		case 42:
			sprintf_s(info, 128, "other info %d\n", rcv[1]);
			break;
		case SETPSW:
			sprintf_s(info, 32, "password changed successfully\n");
			break;
		default:
			sprintf_s(info, 128, "other info %d\n", rcv[1]);
			break;
		}
		curWin.m_timeStatus.SetWindowText(info);
		LeaveCriticalSection(&lpr->wrcon);
	} while (1);
};

int CIMhideWndDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO: Add your specialized creation code here

	CRect tRect;
	//获得任务栏高度
	CWnd* p = this->FindWindow("Shell_TrayWnd", NULL);
	if (p != NULL)
	{
		p->GetWindowRect(tRect);
		m_taskBarHeight = tRect.Height();
	}

	//修改风格使得他不在任务栏显示
	ModifyStyleEx(WS_EX_APPWINDOW, WS_EX_TOOLWINDOW);
	//去掉关闭按键(如果想画3个按键的话)
	//ModifyStyle(WS_SYSMENU,NULL);
	//获得边缘高度和宽度
	m_edgeHeight = GetSystemMetrics(SM_CYEDGE);
	m_edgeWidth = GetSystemMetrics(SM_CXFRAME);

	//开启聊天
	//int err = InitChat(oimusr.addr);
	int err = InitChat();
	StartChat(err, ShowMsg);
	return 0;
}

BOOL CIMhideWndDlg::SetWindowPos(const CWnd* pWndInsertAfter, LPCRECT pCRect, UINT nFlags)
{
	return CDialog::SetWindowPos(pWndInsertAfter, pCRect->left, pCRect->top,
		pCRect->right - pCRect->left, pCRect->bottom - pCRect->top, nFlags);
}

LRESULT CIMhideWndDlg::OnNcHitTest(CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (m_hideMode != HM_NONE && !m_isSetTimer &&
		//防止鼠标超出屏幕右边时向右边收缩造成闪烁
		point.x < GetSystemMetrics(SM_CXSCREEN) + INFALTE)
	{   //鼠标进入时,如果是从收缩状态到显示状态则开启Timer
		SetTimer(1, CM_ELAPSE, NULL);
		m_isSetTimer = TRUE;

		m_hsFinished = FALSE;
		m_hiding = FALSE;
		SetTimer(2, HS_ELAPSE, NULL); //开启显示过程
	}
	CString str;
	str.Format("LOCAL(%d,%d)", point.x, point.y);
	GetDlgItem(IDC_TIMER)->SetWindowText(str);
	return CDialog::OnNcHitTest(point);
}

void CIMhideWndDlg::OnTimer(UINT nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent == 1)
	{
		POINT curPos;
		GetCursorPos(&curPos);

		CString str;
		str.Format("Timing\r");
		GetDlgItem(IDC_TIMER)->SetWindowText(str);

		CRect tRect;
		//获取此时窗口大小
		GetWindowRect(tRect);
		//膨胀tRect,以达到鼠标离开窗口边沿一定距离才触发事件
		tRect.InflateRect(INFALTE, INFALTE);

		if (!tRect.PtInRect(curPos)) //如果鼠标离开了这个区域
		{
			KillTimer(1); //关闭检测鼠标Timer
			m_isSetTimer = FALSE;
			GetDlgItem(IDC_TIMER)->SetWindowText("Timer Off");

			m_hsFinished = FALSE;
			m_hiding = TRUE;
			SetTimer(2, HS_ELAPSE, NULL); //开启收缩过程
		}
	}

	if (nIDEvent == 2)
	{
		if (m_hsFinished) //如果收缩或显示过程完毕则关闭Timer	  
			KillTimer(2);
		else
			m_hiding ? DoHide() : DoShow();
	}

	CDialog::OnTimer(nIDEvent);
}

void CIMhideWndDlg::OnSysCommand(UINT nID, LPARAM lparam)
{
	if (nID == SC_CLOSE)
	{
		DestroyWindow();
		delete this;
		return;
		//AfxDump << "OnSysCommand\n";
	}
	CDialog::OnSysCommand(nID, lparam);
}

void CIMhideWndDlg::OnMoving(UINT fwSide, LPRECT pRect)
{
	FixMoving(fwSide, pRect); //修正pRect
	CDialog::OnMoving(fwSide, pRect);
}

void CIMhideWndDlg::DoHide()
{
	if (m_hideMode == HM_NONE)
		return;

	CRect tRect;
	GetWindowRect(tRect);

	if ((m_logDlg != NULL) && (m_logDlg->m_hWnd != NULL))
		m_logDlg->ShowWindow(SW_HIDE);

	INT height = tRect.Height();
	INT width = tRect.Width();

	INT steps = 0;

	switch (m_hideMode)
	{
	case HM_TOP:
		steps = height / HS_STEPS;
		tRect.bottom -= steps;
		if (tRect.bottom <= m_edgeWidth)
		{   //你可以把下面一句替换上面的 ...+=|-=steps 达到取消抽屉效果
			//更好的办法是添加个BOOL值来控制,其他case同样.
			tRect.bottom = m_edgeWidth;
			m_hsFinished = TRUE;  //完成隐藏过程
		}
		tRect.top = tRect.bottom - height;
		break;
	case HM_BOTTOM:
		steps = height / HS_STEPS;
		tRect.top += steps;
		if (tRect.top >= (GetSystemMetrics(SM_CYSCREEN) - m_edgeWidth))
		{
			tRect.top = GetSystemMetrics(SM_CYSCREEN) - m_edgeWidth;
			m_hsFinished = TRUE;
		}
		tRect.bottom = tRect.top + height;
		break;
	case HM_LEFT:
		steps = width / HS_STEPS;
		tRect.right -= steps;
		if (tRect.right <= m_edgeWidth)
		{
			tRect.right = m_edgeWidth;
			m_hsFinished = TRUE;
		}
		tRect.left = tRect.right - width;
		tRect.top = -m_edgeHeight;
		tRect.bottom = GetSystemMetrics(SM_CYSCREEN) - m_taskBarHeight;
		break;
	case HM_RIGHT:
		steps = width / HS_STEPS;
		tRect.left += steps;
		if (tRect.left >= (GetSystemMetrics(SM_CXSCREEN) - m_edgeWidth))
		{
			tRect.left = GetSystemMetrics(SM_CXSCREEN) - m_edgeWidth;
			m_hsFinished = TRUE;
		}
		tRect.right = tRect.left + width;
		tRect.top = -m_edgeHeight;
		tRect.bottom = GetSystemMetrics(SM_CYSCREEN) - m_taskBarHeight;
		break;
	default:
		break;
	}

	SetWindowPos(&wndTopMost, tRect);
}

void CIMhideWndDlg::DoShow()
{
	if (m_hideMode == HM_NONE)
		return;

	CRect tRect;
	GetWindowRect(tRect);
	INT height = tRect.Height();
	INT width = tRect.Width();

	INT steps = 0;

	switch (m_hideMode)
	{
	case HM_TOP:
		steps = height / HS_STEPS;
		tRect.top += steps;
		if (tRect.top >= -m_edgeHeight)
		{   //可以把下面一句替换上面的 ...+=|-=steps 达到取消抽屉效果
			//更好的办法是添加个BOOL值来控制,其他case同样.
			tRect.top = -m_edgeHeight;
			m_hsFinished = TRUE;  //完成显示过程
		}
		tRect.bottom = tRect.top + height;
		break;
	case HM_BOTTOM:
		steps = height / HS_STEPS;
		tRect.top -= steps;
		if (tRect.top <= (GetSystemMetrics(SM_CYSCREEN) - height))
		{
			tRect.top = GetSystemMetrics(SM_CYSCREEN) - height;
			m_hsFinished = TRUE;
		}
		tRect.bottom = tRect.top + height;
		break;
	case HM_LEFT:
		steps = width / HS_STEPS;
		tRect.right += steps;
		if (tRect.right >= width)
		{
			tRect.right = width;
			m_hsFinished = TRUE;
		}
		tRect.left = tRect.right - width;
		tRect.top = -m_edgeHeight;
		tRect.bottom = GetSystemMetrics(SM_CYSCREEN) - m_taskBarHeight;
		break;
	case HM_RIGHT:
		steps = width / HS_STEPS;
		tRect.left -= steps;
		if (tRect.left <= (GetSystemMetrics(SM_CXSCREEN) - width))
		{
			tRect.left = GetSystemMetrics(SM_CXSCREEN) - width;
			m_hsFinished = TRUE;
		}
		tRect.right = tRect.left + width;
		tRect.top = -m_edgeHeight;
		tRect.bottom = GetSystemMetrics(SM_CYSCREEN) - m_taskBarHeight;
		break;
	default:
		break;
	}
	SetWindowPos(&wndTopMost, tRect);
}

void CIMhideWndDlg::FixMoving(UINT fwSide, LPRECT pRect)
{
	CRect tRect;
	POINT curPos;
	GetCursorPos(&curPos);
	INT screenHeight = GetSystemMetrics(SM_CYSCREEN);
	INT screenWidth = GetSystemMetrics(SM_CXSCREEN);
	INT height = pRect->bottom - pRect->top;
	INT width = pRect->right - pRect->left;

	if (curPos.y <= INTERVAL)
	{   //粘附在下边
		pRect->bottom = height - m_edgeHeight;
		pRect->top = -m_edgeHeight;
		m_hideMode = HM_BOTTOM;
	}
	else if (curPos.y >= (screenHeight - INTERVAL - m_taskBarHeight))
	{   //粘附在上边
		pRect->top = screenHeight - m_taskBarHeight - height;
		pRect->bottom = screenHeight - m_taskBarHeight;
		m_hideMode = HM_TOP;
	}
	else if (curPos.x < INTERVAL)
	{	//粘附在左边	
		if (!m_isSizeChanged)
		{
			GetWindowRect(tRect);
			m_oldWndHeight = tRect.Height();
		}
		pRect->right = width;
		pRect->left = 0;
		pRect->top = -m_edgeHeight;
		pRect->bottom = screenHeight - m_taskBarHeight;
		m_isSizeChanged = TRUE;
		m_hideMode = HM_LEFT;
	}
	else if (curPos.x >= (screenWidth - INTERVAL))
	{   //粘附在右边
		if (!m_isSizeChanged)
		{
			GetWindowRect(tRect);
			m_oldWndHeight = tRect.Height();
		}
		pRect->left = screenWidth - width;
		pRect->right = screenWidth;
		pRect->top = -m_edgeHeight;
		pRect->bottom = screenHeight - m_taskBarHeight;
		m_isSizeChanged = TRUE;
		m_hideMode = HM_RIGHT;
	}
	else
	{   //不粘附
		if (m_isSizeChanged)
		{   //如果收缩到两边,则拖出来后会变回原来大小
			//在"拖动不显示窗口内容下"只有光栅变回原来大小
			pRect->bottom = pRect->top + m_oldWndHeight;
			m_isSizeChanged = FALSE;
		}
		if (m_isSetTimer)
		{   //如果Timer开启了,则关闭之
			if (KillTimer(1) == 1)
				m_isSetTimer = FALSE;
		}
		m_hideMode = HM_NONE;
		GetDlgItem(IDC_TIMER)->SetWindowText("Timer off");
	}
}

BOOL CIMhideWndDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	if (m_commbo.m_hWnd != NULL)
	{
		m_commbo.InsertString(0, idx_CMD[0].val.c_str());
		m_commbo.SetCurSel(0);
		for (int i = 1; i <= 0x0C; i++)
			m_commbo.InsertString(i, idx_CMD[i].val.c_str());
	}
	SetListCtl();
	hBitmap = (HBITMAP)::LoadImage(NULL, ".\\res\\bit+.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	if (hBitmap != NULL)
		m_AddBtn.SetBitmap(hBitmap);
	return TRUE;
}

void CIMhideWndDlg::OnBnClickedExit()
{
	CloseChat();
	if (!AfxGetMainWnd()->IsWindowVisible())
	{
		delete this;
		AfxGetMainWnd()->PostMessage(WM_QUIT, 0, 0);
	}
	else
		DestroyWindow();
}

int ifsh = 0;
void CIMhideWndDlg::OnCbnSelchangeComm()
{
	if (IDX == 0)
	{
		m_commbo.DeleteString(0);
		IDX++;
	}
	CRect listrect;
	LVCOLUMN lvcol;
	CRegistDlg m_crgist("192.168.1.3");
	m_logDlg = new IMlogDlg();
	int comsel = m_commbo.GetCurSel();
	char item[8];
	SetChatCmd(comsel);
	switch (comsel)
	{
	case REGIST:
		m_crgist.DoModal();
		break;
	case LOGIN:
		if (::IsWindowVisible(m_logDlg->m_hWnd))
			return;
		if (m_frndList.m_hWnd != NULL)
		{
			m_frndList.GetWindowRect(&listrect);
			//ScreenToClient(&listrect);
			//listrect.top += 80;*/
			m_logDlg->Create(IDD_IMMODAL,this/*FromHandle(m_frndList.m_hWnd)*/); 
			m_logDlg->MoveWindow(listrect);
			m_logDlg->ShowWindow(SW_SHOW);
			UpdateData(TRUE);
		}
		break;
	case REFRASH:
		sprintf(item, "%03d", ifsh);
		m_frndList.InsertItem(0, item);
		sprintf(item, "%03X", (ifsh + 11) * 13 - 19);
		m_frndList.InsertItem(1, item);
		ifsh++;
		break;
	case FRIENDLIST:
		lvcol.pszText = _T("好友");
		m_frndList.SetColumn(0, &lvcol);
		m_frndList.ShowWindow(SW_SHOW);
		break;
	case VIEWGROUP:
		m_frndList.DeleteAllItems();
		lvcol.pszText = _T("群成员");
		m_frndList.SetColumn(0, &lvcol);
		lvcol.pszText = _T("所在群");
		m_frndList.SetColumn(1, &lvcol);
		m_frndList.ShowWindow(SW_SHOW);
		break;
	default:
		break;
	}
}

void CIMhideWndDlg::SetListCtl()
{
	if (m_frndList.m_hWnd != NULL)
	{
		m_frndList.SetExtendedStyle(m_frndList.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
		m_frndList.InsertColumn(0, _T("好友"), 0, 80);
		m_frndList.InsertItem(0, "001");
		m_frndList.InsertItem(1, "Abc");
	}
}

void CIMhideWndDlg::OnNMDblclkListfrnd(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	int N = *pResult = 0;
	POSITION curPos = m_frndList.GetFirstSelectedItemPosition();
	if (m_frndList.GetHeaderCtrl()->GetItemCount() == 1)
		m_frndList.InsertColumn(1, _T("备注"), 0, m_frndList.GetColumnWidth(0));
	SetMarkDlg setmark;
	setmark.DoModal();
	while (curPos)
	{
		N = m_frndList.GetNextSelectedItem(curPos);
		m_frndList.SetItemText(N, 1, setmark.GetMark(m_frndList.GetItemText(N, 1), m_frndList.GetItemText(N, 0)));
	}
}


void CIMhideWndDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // 不为绘图消息调用 CDialogEx::OnPaint()
}


void CIMhideWndDlg::OnBnClickedSeeknew()
{
	MessageBox("");
}
