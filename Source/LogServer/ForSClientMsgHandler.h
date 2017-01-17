#ifndef _SERVER_HANDLER_H_
#define _SERVER_HANDLER_H_

#include "Config.h"
#include "BaseSingle.h"
#include "BaseMsgHandler.h"

/*
 *
 *	Detail: ������ws��ss,lsͨ����Ϣ 
 *   
 * Copyright (c) Created by hzd 2015-4-27.All rights reserved
 *
 */

class NetSocket;
struct NetMsgSS;

class ForSClientMsgHandler : public BaseMsgHandler, public BaseSingle<ForSClientMsgHandler>
{

public:
	ForSClientMsgHandler();
	~ForSClientMsgHandler();

	// �пͻ������ӻص� 
	virtual void OnNetMsgEnter(NetSocket& rSocket);

	// �пͻ�����Ϣ�յ� 
	virtual void OnNetMsg(NetSocket& rSocket, NetMsgSS* pHead,int32 nSize);

	// �пͻ��˶Ͽ��ص�(��ʱsocket�Ѿ�����)  
	virtual void OnNetMsgExit(NetSocket& rSocket);

	// ��¼��� 
	void RepLogined(BaseSession* pSession, const NetMsgSS* pMsg,int32 nSize);

	// ͬ��client���ӵ�server��Ϣ 
	void NofityClientSessionInfo(BaseSession* pSession, const NetMsgSS* pMsg,int32 nSize);

	// �ͻ����˳�֪ͨ 
	void NofityClientExit(BaseSession* pSession, const NetMsgSS* pMsg, int32 nSize);

	// �յ�ping ���� 
	void RepPingToS(BaseSession* pSession, const NetMsgSS* pMsg,int32 nSize);

private:

	bool m_bFirstMsg;

};

#endif


