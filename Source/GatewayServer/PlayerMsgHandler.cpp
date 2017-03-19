#include "GatewayServer_PCH.h"
#include "PlayerMsgHandler.h"


// �� fep �� ��client��sessionIDΪsocketID

PlayerMsgHandler::PlayerMsgHandler()
{

	// to fep
#define REGISTER_FEP_MESSAGE(msg_idx, cls,handler)\
	{\
		RegisterMessage(msg_idx, sizeof(cls),boost::bind(&PlayerMsgHandler::handler, this, _1, _2,_3)); \
	}

	REGISTER_FEP_MESSAGE(C::RQ_ENCRYPT, C::RqEncryptInfo,	ReqFepEncyptHandler);

#undef REGISTER_FEP_MESSAGE

	// to ls
#define REGISTER_LS_MESSAGE(msg_idx,cls)\
	{\
	RegisterMessage(msg_idx,sizeof(cls),boost::bind(&PlayerMsgHandler::ReqSendToLoginServer,this, _1, _2,_3));\
	}
	
	REGISTER_LS_MESSAGE(C::RQ_ACCOUNT_LOGIN, C::RqAccountLogin);
	
#undef REGISTER_LS_MESSAGE

	// to ws
#define REGISTER_WS_MESSAGE(msg_idx,cls)\
	{\
		RegisterMessage(msg_idx, sizeof(cls), boost::bind(&PlayerMsgHandler::ReqSendToWorldServer, this, _1, _2,_3)); \
	}

	REGISTER_WS_MESSAGE(C::RQ_SWITCH_SCENE, C::RqSwitchScene);	// �л��³��� 
	REGISTER_WS_MESSAGE(C::RQ_Rq_SELECT_ROLE, C::RqSelectRole);		// ѡ���ɫ
	REGISTER_WS_MESSAGE(C::RQ_CREATE_ROLE, C::RqCreateRole);
	REGISTER_WS_MESSAGE(C::RQ_DELETE_ROLE, C::RqDeleteRole);

	REGISTER_WS_MESSAGE(C::RQ_LOOK_MESSAGE,	C::rqLookMessage);
	REGISTER_WS_MESSAGE(C::RQ_OPT_MESSAGE, C::rqOptMessage);

#undef REGISTER_WS_MESSAGE

	// to ss
#define REGISTER_SS_MESSAGE(msg_idx,cls)\
	{\
		RegisterMessage(msg_idx, sizeof(cls), boost::bind(&PlayerMsgHandler::ReqSendToSceneServer, this, _1, _2,_3)); \
	}

	//REGISTER_SS_MESSAGE(RQ_CHAT_WORLD,		RqCharWorld);
	REGISTER_SS_MESSAGE(C::RQ_SCENE_INIT_DATA, C::RqClientIsReady);
	REGISTER_SS_MESSAGE(C::RQ_CHANGE_SCENE, C::RqChanageScene);

	REGISTER_SS_MESSAGE(C::RQ_ITEM_MOVE_POSITION, C::RqItemMovePosition);
	REGISTER_SS_MESSAGE(C::RQ_POSITION_MOVE, C::RqPositionMove);
	REGISTER_SS_MESSAGE(C::RQ_ITEM_USE_OBJECT, C::RqItemUseObject);

	REGISTER_SS_MESSAGE(C::RQ_SHOPPING_BUY_ITME, C::RqShoppingBuyItem);
	REGISTER_SS_MESSAGE(C::RQ_SHOPPING_SELL_ITME, C::RqShoppingSellItem);

	REGISTER_SS_MESSAGE(C::RQ_CHAT_TO_WORLD, C::RqChatToWorld);

	REGISTER_SS_MESSAGE(C::RQ_RELATION_LIST, C::RqRelationList);
	REGISTER_SS_MESSAGE(C::RQ_RELATION_ADD, C::RqRelationAdd);
	REGISTER_SS_MESSAGE(C::RQ_RELATION_REMOVE, C::RqRelationRemove);

#undef REGISTER_SS_MESSAGE

}


PlayerMsgHandler::~PlayerMsgHandler()
{
}

void PlayerMsgHandler::OnNetMsgEnter(NetSocket& rSocket)
{
	H::logger->info("[���]���ӳɹ���������:id=%d ip=%s,port=%d", rSocket.SID(), rSocket.GetIp().c_str(), (int32)rSocket.GetPort());

	zSession* session = GameService::getMe().getSessionMgr().get(rSocket.SLongID());
	if (session)
	{
		session->initEncrypt();
		zSession* ws = GameService::getMe().getSessionMgr().getWs();
		if (ws == NULL)
		{
			H::logger->warn("[���]WS��δ���ӣ��ܾ��������");
			session->socket->OnEventColse();
			return;
		}

		zSession* ls = GameService::getMe().getSessionMgr().getLs();
		if (ls == NULL)
		{
			H::logger->warn("[���]LS��δ���ӣ��ܾ��������");
			session->socket->OnEventColse();
			return;
		}
		session->setSessionType(zSession::FOR_PLAYER);
		session->status = E_CLIENT_STATUS_CONNECTED;
	}
	else
	{
		ASSERT(0);
	}
}


void PlayerMsgHandler::OnNetMsg(NetSocket& rSocket, NetMsgSS* pMsg,int32 nSize)
{
	zSession* session = GameService::getMe().getSessionMgr().get(rSocket.SLongID());
	if(session)
	{
		// ���ܴ��� 
		static char msgEnBuffer[65536];
		static char msgUnBuffer[65536];

		int nCHeadSize = sizeof(NetMsgC);
		int nSHeadSize = sizeof(NetMsgSS);
		memcpy(&msgEnBuffer[0], pMsg, nSize);		
		
		zEncrypt::xorCode(nSize, session->encrypt, msgEnBuffer, nSize);

		// ��װΪNetMsgSSͷЭ�飬�м䲹����ͷЭ����ֽڲ� 
		memcpy(&msgUnBuffer[0], msgEnBuffer, nCHeadSize);
		memset(&msgUnBuffer[nCHeadSize], 0, nSHeadSize - nCHeadSize);
		memcpy(&msgUnBuffer[nSHeadSize], &msgEnBuffer[nCHeadSize], nSize - nCHeadSize);

		pMsg = (NetMsgSS*)&msgUnBuffer[0];

		const MsgFunc* handler = GetMsgHandler(pMsg->protocol);
		if(handler == NULL)
		{
			H::logger->error("[���]�Ҳ���Э��:%d,��С:%d", pMsg->protocol,nSize);
			rSocket.OnEventColse();
			return;
		}
		else
		{
			H::logger->info("[���]�յ�Э��:%d", pMsg->protocol);
			(handler->handlerFun)(session, pMsg,nSize + nSHeadSize - nCHeadSize);
		}
	}
	else
	{
		H::logger->error("[���]�Ҳ���������:%lld", rSocket.SLongID());
		rSocket.OnEventColse();
	}
}

void PlayerMsgHandler::OnNetMsgExit(NetSocket& rSocket)
{
	// ��ӡ�˳�ԭ��  
	std::string strExitMsg;
	int32 nErrorCode = rSocket.ErrorCode(strExitMsg);
	H::logger->error("[���]���ӶϿ�:%lld,�Ͽ�ԭ��:%s", rSocket.SLongID(), strExitMsg.c_str());

	zSession* session = GameService::getMe().getSessionMgr().get(rSocket.SLongID());
	ASSERT(session);

	// �������δ������֤�����Բ�����WS�� 
	if (session->status < E_CLIENT_STATUS_ENCRYPTED)
	{
		return;
	}

	// �����ͻ����˳���Ϣ 
	S::SSNtRqPlayerExit sendExitWs;
	sendExitWs.nReason = nErrorCode;
	ReqSendToWorldServer(session, &sendExitWs, sizeof(sendExitWs));

	S::SSRqPlayerExit sendExitScene;
	sendExitScene.nReason = nErrorCode;
	ReqSendToSceneServer(session, &sendExitScene, sizeof(sendExitScene));

	GateUser* gateUser = GateUserManager::getMe().getBySessID(rSocket.SLongID());
	if (gateUser)
	{
		GateUserManager::getMe().remove(gateUser);
		GateUserManager::getMe().DestoryObj(gateUser);
	}

}

// ���͵� ls 
void PlayerMsgHandler::ReqSendToLoginServer(zSession* pSession, const NetMsgSS* pMsg,int32 nSize)
{
	if(pSession->status != E_CLIENT_STATUS_NOTIFY_INITED)
	{
		H::logger->warn("[���]�޷�ת����LS,����%lld״̬δ��ɳ�ʼ��", pSession->id);
		return;
	}
	zSession* ls = GameService::getMe().getSessionMgr().getLs();
	if (ls == NULL)
	{
		H::logger->warn("[���]�޷�ת����LS,�Ҳ���LS Session");
		return;
	}
	
	MSG_MAKE_PLAYER_SESSID(pSession->id,GameService::getMe().getServerID(),pMsg,nSize);
	ls->sendMsg((NetMsgSS*)(&vecMsgBuffer[0]), vecMsgBuffer.size());
}

// ���͵� ss
void PlayerMsgHandler::ReqSendToSceneServer(zSession* pSession, const NetMsgSS* pMsg,int32 nSize)
{
	if(pSession->status != E_CLIENT_STATUS_IN_SCENE)
	{
		H::logger->warn("[���]�޷�ת����SS,����%lld״̬δ���볡��", pSession->id);
		return;
	}

	GateUser* gateUser = GateUserManager::getMe().getBySessID(pSession->id);
	if (gateUser)
	{
		zSession* ss = GameService::getMe().getSessionMgr().getSs(gateUser->sceneServerid);
		if (ss == NULL)
		{
			H::logger->warn("[���]�޷�ת����SS,�Ҳ���SS,serverid:%d", gateUser->sceneServerid);
			return;
		}
		MSG_MAKE_PLAYER_SESSID(pSession->id, GameService::getMe().getServerID(), pMsg, nSize);
		ss->sendMsg((NetMsgSS*)(&vecMsgBuffer[0]), vecMsgBuffer.size());
	}
}

// ���͵� ws
void PlayerMsgHandler::ReqSendToWorldServer(zSession* pSession, const NetMsgSS* pMsg,int32 nSize)
{
	if(pSession->status <= E_CLIENT_STATUS_ENCRYPTED)
	{
		H::logger->warn("[���]�޷�ת����WS,����%lld״̬δ��ɳ�ʼ��", pSession->id);
		return;
	}
	
	MSG_MAKE_PLAYER_SESSID(pSession->id,GameService::getMe().getServerID(),pMsg,nSize);
	zSession* ws = GameService::getMe().getSessionMgr().getWs();
	if (!ws)
	{
		H::logger->warn("[���]�޷�ת����WS,�Ҳ���WS Session");

	}
	ws->sendMsg((NetMsgSS*)(&vecMsgBuffer[0]), vecMsgBuffer.size());
}

void PlayerMsgHandler::SendToPlayer(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{
	static char arrUnBuffer[65536];
	static char arrEnBuffer[65536];
	int nCHeadSize = sizeof(NetMsgC);
	int nSHeadSize = sizeof(NetMsgSS);
	int nCSize = nSize - (nSHeadSize - nCHeadSize);
	memcpy(&arrUnBuffer[0], pMsg, nSize);
	memcpy(&arrEnBuffer[0], &arrUnBuffer[0], nCHeadSize);
	memcpy(&arrEnBuffer[nCHeadSize], &arrUnBuffer[nSHeadSize], nSize - nSHeadSize);
	zEncrypt::xorCode(nCSize, pSession->encrypt, arrEnBuffer, nCSize);
	pSession->socket->ParkMsg((NetMsgSS*)&arrEnBuffer[0], nCSize);
	pSession->socket->SendMsg();
}

void PlayerMsgHandler::ReqFepEncyptHandler(zSession* pSession,const NetMsgSS* pMsg,int32 nSize)
{
	if(pSession->status == E_CLIENT_STATUS_CONNECTED )
	{
		char arrRandKey[MAX_ENCRYPTSIZE + 1];
		bzero(arrRandKey,sizeof(arrRandKey));
		zEncrypt::getRandKey(arrRandKey,MAX_NAMESIZE);
		
		C::RtEncryptInfo sendEncrypt;
		strncpy(sendEncrypt.encryptKey, arrRandKey, MAX_ENCRYPTSIZE);
		SendToPlayer(pSession, &sendEncrypt, sizeof(sendEncrypt));

		// Ҫ�ȷ����ݺ���ܸ� 
		strncpy(pSession->encrypt,arrRandKey,MAX_ENCRYPTSIZE);
		pSession->status = E_CLIENT_STATUS_ENCRYPTED;

		// ��÷�����״̬�Ƿ���� 
		S::SSRqCheckSerivces sendCheckSerivces;
		sendCheckSerivces.sessid = pSession->id;
		zSession* wsSession = GameService::getMe().getSessionMgr().getWs();
		if (!wsSession)
		{
			H::logger->warn("[���]��¼ǰ����������״̬�Ƿ����ת��ʧ�ܣ��Ҳ���WS Session");
			return;
		}
		wsSession->sendMsg(&sendCheckSerivces, sizeof(sendCheckSerivces));

		pSession->status = E_CLIENT_STATUS_NOTIFY_INITED;
	}
	else
	{
		H::logger->error("[���]����%lld״̬δ���ӳɹ����޷������Կ", pSession->id);
	}
}


