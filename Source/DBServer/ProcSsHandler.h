#ifndef __PROC_SERVER_HANDLER_H_
#define __PROC_SERVER_HANDLER_H_

#include "Includes.h"
#include "DbRecordSet.h"

class zSession;
class ClientSession;
struct NetMsgSS;

/*
 *	ҵ���߼� 
 */
class ProcSsHandler : public Single<ProcSsHandler> 
{
public:
	ProcSsHandler(void);
	~ProcSsHandler(void);

	// client��¼��ѯ 
	void ReqAccountLogin(zSession* pBaseSession, const NetMsgSS* pMsg,int32 nSize);

	// ������ɫ 
	void ReqRoleCreate(zSession* pBaseSession, const NetMsgSS* pMsg,int32 nSize);

	// ss �м��ؽ�ɫ���� 
	void ReqLoadUser(zSession* pBaseSession, const NetMsgSS* pMsg,int32 nSize);

	// ss �б������� 
	void ReqSaveUser(zSession* pBaseSession, const NetMsgSS* pMsg,int32 nSize);

	void ReqSaveMixItemNumber(zSession* pBaseSession, const NetMsgSS* pMsg,int32 nSize);


	//------------------db�ص�����--------------------
public:

	// ������ɫ
	static void DbRoleCreate(void* pSession,const void* pData);

	static void QueryCharacterList(ClientSession* pClientSession,int64 nAccountID = 0 , int64 nCharacterID = 0);
	
};


#endif

