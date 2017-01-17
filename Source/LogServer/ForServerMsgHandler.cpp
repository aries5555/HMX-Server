#include "ForServerMsgHandler.h"
#include "../DyNetSocket/NetSocket.h"
#include "../DyNetSocket/NetClient.h"

#include "LogManager.h"
#include "BaseDefine.h"
#include "CommonServerOpt.h"
#include "ServerSession.h"
#include "CommonInternal.h"
#include "ServerClientCommon.h"

#include "CommonS2S.h"
#include "ProcServerHandler.h"

#include "LogManager.h"


ForServerMsgHandler::ForServerMsgHandler()
{
	// �ڲ�Э�� 
#define REGISTER_INTERNAL_MESSAGE(msg_idx,cls,handler)\
	{\
	RegisterMessage(msg_idx, sizeof(cls), boost::bind(&ForServerMsgHandler::handler, this, _1, _2, _3)); \
}

	REGISTER_INTERNAL_MESSAGE(PRO_SS_REQ_LOGIN_S, SSReqLoginS, ReqLogined);	// �����¼ 
	REGISTER_INTERNAL_MESSAGE(PRO_SS_REQ_PING_S,SSReqPingToS,ReqPingToS);

#undef REGISTER_INTERNAL_MESSAGE


#define REGISTER_S2LOG_MESSAGE(msg_idx,cls,handler)\
	{\
	RegisterMessage(msg_idx, sizeof(cls), boost::bind(&ProcServerHandler::handler, ProcServerHandler::Instance(), _1, _2, _3)); \
	}

	REGISTER_S2LOG_MESSAGE(PRO_S2LOG_MSG,S2LogMsg,ReqSaveToDb);	

#undef REGISTER_S2LOG_MESSAGE

}


ForServerMsgHandler::~ForServerMsgHandler()
{
}

// �пͻ������ӻص� 
void ForServerMsgHandler::OnNetMsgEnter(NetSocket& rSocket)
{
	//---------------------------------���������begin-------------------------------
	ServerCommonHandler::ForServerOnMsgEnter(rSocket,ESERVER_TYPE_LOG);
	//---------------------------------���������end-------------------------------
}

// �пͻ�����Ϣ�յ�
void ForServerMsgHandler::OnNetMsg(NetSocket& rSocket, NetMsgSS* pMsg,int32 nSize)
{
	//---------------------------------���������begin-------------------------------
	ServerCommonHandler::ForServerOnMsg(*this,rSocket, pMsg,nSize);
	//---------------------------------���������end-------------------------------
}

// �пͻ��˶Ͽ��ص�(��ʱsocket�Ѿ�����) 
void ForServerMsgHandler::OnNetMsgExit(NetSocket& rSocket)
{
	//---------------------------------���������begin-------------------------------
	ServerCommonHandler::ForServerOnMsgExit(rSocket);
	//---------------------------------���������end-------------------------------
}

void ForServerMsgHandler::ReqLogined(BaseSession* pSession, const NetMsgSS* pMsg,int32 nSize)
{
	//---------------------------------���������begin-------------------------------
	ServerCommonHandler::ForServerOnLogin(pSession, pMsg);
	//---------------------------------���������end-------------------------------
}

// �յ�ping������Ϣ 
void ForServerMsgHandler::ReqPingToS(BaseSession* pSession, const NetMsgSS* pMsg,int32 nSize)
{
	ServerSession* pServerSession = static_cast<ServerSession*>(pSession);
	SSRepPingS sMsg;
	pServerSession->SendMsg(&sMsg,sMsg.GetPackLength());
}
