#ifndef __COMMON_INTERNAL_H_
#define __COMMON_INTERNAL_H_

/*
 *
 *	Detail: �ڲ�ͨ��Э�� 
 *   
 *  Created by hzd 2015-5-21
 *
 */

#include "ServerDefine.h"
#include "NetConfig.h"
#include "DbConfig.h"

enum EProReqInternal
{
	PRO_SS_RQ_LOGIN			= PRO_INTERNAL_BASE + 0,	// ��¼��������,���з�������¼��ws 
	PRO_SS_REQ_LOGIN_S			= PRO_INTERNAL_BASE + 1,	// ��¼��dp,fep 
	PRO_SS_RQ_CHECK_SERIVCES	= PRO_INTERNAL_BASE + 2,	// �����������Ϣ  
	PRO_SS_RQ_PING_S			= PRO_INTERNAL_BASE + 3,	// PINGЭ��ͻ���ping����ˣ�ping�󣬾�socket->setTimeout,�յ����ݣ���ȡ�� 
};

enum EProRepInternal
{
	PRO_SS_RT_LOGINED			= PRO_INTERNAL_BASE + 50, // ��¼���  
	PRO_SS_RT_SERVERINFO_LIST	= PRO_INTERNAL_BASE + 51, // ��������Ϣ 
	PRO_SS_NOTIFY_SERVERID		= PRO_INTERNAL_BASE + 52, // ���·�������Ϣ 
	PRO_SS_REP_PING_S			= PRO_INTERNAL_BASE + 53, // ����������PING�Ľ������socketȡ����ʱ��  
};


#pragma pack(push,1)


//------------------------req------------------------------

struct SSRqLogin : public NetMsgSS
{
	SSRqLogin():NetMsgSS(PRO_SS_RQ_LOGIN)
	{
		serverID = serverID = 0;
	}
	int32 serverID; 
	int32 serivceID;
	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};

struct SSCheckSerivces : public NetMsgSS
{
	SSCheckSerivces():NetMsgSS(PRO_SS_RQ_CHECK_SERIVCES)
	{

	}
	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};


struct SSRqPingToS : public NetMsgSS
{
	SSRqPingToS():NetMsgSS(PRO_SS_RQ_PING_S)
	{

	}
	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};



//--------------------------rep------------------------------------

struct SSRtLogined : public NetMsgSS
{
	enum 
	{
		SUCCESS,
		FAIL,
	};

	int32 result;

	SSRtLogined():NetMsgSS(PRO_SS_RT_LOGINED)
	{
	}

	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};

// �������б���Ϣ 
struct SSServerRegList : public NetMsgSS
{

	int32 count;
	t_ServerReg reglist[MAX_SERVERINFO_LIST];

	SSServerRegList() :NetMsgSS(PRO_SS_RT_SERVERINFO_LIST)
	{
		count = 0;
	}

	inline int32 GetPackLength()const
	{
		return sizeof(*this) - sizeof(reglist) + count * sizeof(t_ServerReg);
	}
};

/*-------------------------------------------------------------------
 * @Brief : ͬ����ҵķ�����������Ϣ
 * 
 * @Author:hzd 2015:10:24
 *------------------------------------------------------------------*/
struct SSInitUserClient : public NetMsgSS
{
	int32 nSceneID;

	SSInitUserClient() :NetMsgSS(PRO_SS_NOTIFY_SERVERID)
	{
		nSceneID = 0;
	}
	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};

struct SSRepPingS : public NetMsgSS
{
	SSRepPingS():NetMsgSS(PRO_SS_REP_PING_S)
	{

	}
	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};

static dbCol user_columns[] =
{
	{ "ID", DB_QWORD, sizeof(int64) },
	{ "ACCID", DB_QWORD, sizeof(int64) },
	{ "NAME",DB_STR,MAX_NAMESIZE + 1},
	{ "STATUS",DB_BYTE, sizeof(int8) },
	{ "LEVEL",DB_WORD, sizeof(int16) },
	{ "VIP",DB_BYTE, sizeof(int8) },
	{ "SCENEID",DB_DWORD, sizeof(int64) },
	{ "MAPID",DB_DWORD, sizeof(int32) },
	{ "ROLETYPE",DB_DWORD, sizeof(int8) },
	{ "EXP",DB_DWORD, sizeof(int32) },
	{ "POSX",DB_DWORD, sizeof(int32) },
	{ "POSY",DB_DWORD, sizeof(int32) },
	{ "GOLD",DB_DWORD, sizeof(int32) },
	{ "SILVER",DB_DWORD, sizeof(int32) },
	{ "COPPER",DB_DWORD, sizeof(int32) },
	{ "LASTLOGIN",DB_DWORD, sizeof(int32) },
	{ "COUNTRY",DB_DWORD, sizeof(int8) },
	{ "TEAMID",DB_DWORD, sizeof(int32) },
	{ "BINDATA",DB_BIN2, 0 },
	{ NULL,0,0 }
};

struct UserSceneBase
{
	UserSceneBase()
	{
		id = accid = status = level = sceneid = mapid = vip = roletype = exp = 0;
		posx = posy = gold = silver = copper = lastLogin = country = teamid = 0;
	}

	int64 id;
	int64 accid;
	char name[MAX_NAMESIZE + 1];
	int8 status;
	int16 level;
	int8 vip;
	int64 sceneid;
	int32 mapid;
	int8 roletype;				// ��ɫ���� 
	int32 exp;					// ���� 
	int32 posx;					// X
	int32 posy;					// Y
	int32 gold;
	int32 silver;
	int32 copper;
	int32 lastLogin;
	int8 country;
	int32 teamid;
};

struct UserGateBase
{
	UserGateBase()
	{
		x = y = level = vip = sceneid = mapid = zoneid = countryID = teamid = 0;
	}

	int32 x;
	int32 y;
	int16 level;
	int8 vip;
	int64 sceneid;
	int32 mapid;
	int32 zoneid;
	int8 countryID;
	int32 teamid;
};

#pragma pack(pop)





#endif


