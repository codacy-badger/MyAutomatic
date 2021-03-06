﻿#ifndef _IMCHAT_H
#define _IMCHAT_H
#pragma comment(lib, "WS2_32.lib")
#pragma warning (disable:4477)
#pragma warning (disable:4819)

#ifdef _UTILAPIS_
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

typedef struct IMSetting {
    int erno = -1;
    char addr[MAX_PATH] = { NULL };
    char IP[16];
    char auth[80];
    unsigned int PORT;
} st_settings;

struct LAST
{
    char lastuser[24];
    char lastgrop[24];
};

typedef struct CLIENT
{
    SOCKET sock = NULL;
    sockaddr_in srvaddr;
    CRITICAL_SECTION wrcon;
    LAST last;
    char url[64];
    int flag = 0;
    void* Dlg;
    void(*fp2p)(void*);
    int count = 0;
} st_client;

struct PPSOCK
{
    SOCKET sock = NULL;
    sockaddr_in addr;
};

struct MENU {
    int key; std::string value;
};

struct MSG_trans {
    unsigned char rsv;
    unsigned char uiCmdMsg;
    unsigned char rtn[2];
    unsigned char chk[4];
    union {
        unsigned char usr[24];
        unsigned char grpnm[24];
    };
    union {
        unsigned char psw[24];
        unsigned char peer[24];
        unsigned char TOKEN[24];
        unsigned char grpmrk[24];
    };
    union {
        unsigned char sign[24];
        unsigned char hgrp[24];
        unsigned char jgrp[24];
        unsigned char npsw[24];
        unsigned char grpbrf[24];
    };
};

const MENU menus[] =
{
    { 0x00,"命令菜单" },
    { 0x01,"注册" },
    { 0x02,"登陆" },
    { 0x03,"帮助" },
    { 0x04,"登出" },
    { 0x05,"设置密码" },
    { 0x06,"重新载入" },
    { 0x07,"聊天对象" },
    { 0x08,"好友列表" },
    { 0x09,"群" },
    { 0x0A,"群成员" },
    { 0x0B,"创建群" },
    { 0x0C,"加入群" },
    { 0x0D,"退群" },
};

enum  em_menu {
    REGIST = 0,
    LOGIN,
    HELP,
    LOGOUT,
    SETPSW,
    RELOAD,
    CHATWITH,
    FRIENDLIST,
    VIEWGROUP,
    MEMBEROF,
    HOSTGROUP,
    JOINGROUP,
    EXITGROUP,
    CHAT = 0xe,
    TALK,
};

int InitChat(st_settings* setting = NULL);
int StartChat(int erno, void(*func)(void*));
int CloseChat();
int SetChatMsg(MSG_trans* msg = NULL);
int GetStatus();
int callbackLog(char* usr, char* psw);
int checkPswValid(char* str); 
int p2pMessage(char *userName, int UserIP, unsigned int UserPort, const char *Message);

#endif
