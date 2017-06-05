#ifndef IM_IMCHAT_H
#define IM_IMCHAT_H
#pragma comment(lib, "WS2_32.lib")
#pragma warning (disable:4477)
#pragma warning (disable:4819)

#ifdef _TESTAPIS_
// /clr模式包含该头文件将会导致
// error LNK2022 : 元数据操作失败(8013118D) : 重复类型(group_filter)中的布局信息不一致 : (0x0200020b)。
// 2>LINK : fatal error LNK1255 : 由于元数据错误，链接失败
#include <WS2tcpip.h>
#else
#include <winsock2.h>
#endif
#include <process.h>
#include <conio.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdio>
#include <map>

typedef struct IMUSR {
	char addr[MAX_PATH];
	char comm[64];
	char psw[32];
	char usr[32];
	int err;
} st_imusr;

struct CHATMSG
{
	char lastuser[256];
	char lastgroup[256];
};

struct LPR
{
	SOCKET sock;
	CRITICAL_SECTION wrcon;
	void* dlg;
	CHATMSG *msg;
};

struct CMD {
	int idx; std::string val;
};

const CMD idx_CMD[] =
{
	{ 0x00,"命令菜单" },
	{ 0x01,"注册" },
	{ 0x02,"登陆" },
	{ 0x03,"登出" },
	{ 0x04,"帮助" },
	{ 0x08,"刷新列表" },
	{ 0x09,"设置密码" },
	{ 0x05,"好友列表" },
	{ 0x06,"群" },
	{ 0x07,"群成员" },
	{ 0x0A,"创建群" },
	{ 0x0B,"加入群" },
	{ 0x0C,"退群" },
};

enum  em_CMD{
	REGIST,
	LOGIN,
	LOGOUT,
	HELP,
	REFRASH,
	SETPSW,
	FRIENDLIST,
	VIEWGROUP,
	VIEWMEMBER,
	HOSTGROUP,
	JOINGROP,
	EXITGROP,
};

int InitChat(char argv[] = "127.0.0.1", int argc = 2);
int StartChat(int err, void(*func)(void*));
int SetChatCmd(unsigned int opt);
int CloseChat();

#endif
