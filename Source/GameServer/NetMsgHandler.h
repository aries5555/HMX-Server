#ifndef _SERVER_MSG_HANDLER_H_
#define _SERVER_MSG_HANDLER_H_

#include "Single.h"
#include "NetConfig.h"
#include "SrvEngine.h"

class NetMsgHandler : public zMsgHandler, public Single<NetMsgHandler>
{
public:
	NetMsgHandler();
	~NetMsgHandler();
	void OnNetMsgEnter(NetSocket& rSocket);
	void OnNetMsg(NetSocket& rSocket, NetMsgSS* pMsg,int32 nSize);
	void OnNetMsgExit(NetSocket& rSocket);

	// �ɶ�������������¼��ע��serverid��
	void doLoginRequest(zSession* pSession, const NetMsgSS* pMsg, int32 nSize);
	void doLoginReponse(zSession* pSession, const NetMsgSS* pMsg, int32 nSize);

	// �ɶ��������Ping
	void doPingRequest(zSession* pSession, const NetMsgSS* pMsg, int32 nSize);

	// �������б� 
	void doSrvListNotifty(zSession* pSession, const NetMsgSS* pMsg, int32 nSize);
	
};

#endif


