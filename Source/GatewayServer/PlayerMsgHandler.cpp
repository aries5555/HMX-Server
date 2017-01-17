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

	REGISTER_FEP_MESSAGE(PRO_C2F_ENCRYPT,	C2FepEncryptInfo,	ReqFepEncyptHandler);

#undef REGISTER_FEP_MESSAGE

	// to ls
#define REGISTER_LS_MESSAGE(msg_idx,cls)\
	{\
	RegisterMessage(msg_idx,sizeof(cls),boost::bind(&PlayerMsgHandler::ReqSendToLoginServer,this, _1, _2,_3));\
	}
	
	REGISTER_LS_MESSAGE(PRO_C2L_ACCOUNT_LOGIN,	C2LAccountLogin); 
	
#undef REGISTER_LS_MESSAGE

	// to ws
#define REGISTER_WS_MESSAGE(msg_idx,cls)\
	{\
		RegisterMessage(msg_idx, sizeof(cls), boost::bind(&PlayerMsgHandler::ReqSendToWorldServer, this, _1, _2,_3)); \
	}

	REGISTER_WS_MESSAGE(PRO_C2W_SWITCH_SCENE,C2WSwitchScene);	// �л��³��� 
	REGISTER_WS_MESSAGE(PRO_C2W_SELECT_ROLE,C2WSelectRole);		// ѡ���ɫ
	REGISTER_WS_MESSAGE(PRO_C2W_CREATE_ROLE,C2WCreateRole);
	REGISTER_WS_MESSAGE(PRO_C2W_DELETE_ROLE,C2WDeleteRole);

#undef REGISTER_WS_MESSAGE

	// to ss
#define REGISTER_SS_MESSAGE(msg_idx,cls)\
	{\
		RegisterMessage(msg_idx, sizeof(cls), boost::bind(&PlayerMsgHandler::ReqSendToSceneServer, this, _1, _2,_3)); \
	}

	//REGISTER_SS_MESSAGE(PRO_C2S_CHAT_WORLD,		C2SCharWorld);
	REGISTER_SS_MESSAGE(PRO_C2S_SCENE_INIT_DATA,C2SClientIsReady);
	REGISTER_SS_MESSAGE(PRO_C2S_CHANGE_SCENE,C2SChanageScene);

	REGISTER_SS_MESSAGE(PRO_C2S_ITEM_MOVE_POSITION,C2SItemMovePosition);
	REGISTER_SS_MESSAGE(PRO_C2S_POSITION_MOVE,C2SPositionMove);
	REGISTER_SS_MESSAGE(PRO_C2S_ITEM_USE_OBJECT, C2SItemUseObject);

	REGISTER_SS_MESSAGE(PRO_C2S_SHOPPING_BUY_ITME,C2SShoppingBuyItem);
	REGISTER_SS_MESSAGE(PRO_C2S_SHOPPING_SELL_ITME,C2SShoppingSellItem);

	REGISTER_SS_MESSAGE(PRO_C2S_CHAT_TO_WORLD,C2SChatToWorld);

	REGISTER_SS_MESSAGE(PRO_C2S_RELATION_LIST, C2SRelationList);
	REGISTER_SS_MESSAGE(PRO_C2S_RELATION_ADD, C2SRelationAdd);
	REGISTER_SS_MESSAGE(PRO_C2S_RELATION_REMOVE, C2SRelationRemove);

#undef REGISTER_SS_MESSAGE

}


PlayerMsgHandler::~PlayerMsgHandler()
{
}

void PlayerMsgHandler::OnNetMsgEnter(NetSocket& rSocket)
{
	Zebra::logger->info("[���]���ӳɹ���������:id=%d ip=%s,port=%d", rSocket.SID(), rSocket.GetIp().c_str(), (int32)rSocket.GetPort());

	zSession* session = NetService::getMe().getSessionMgr().get(rSocket.SLongID());
	if (session)
	{
		session->initEncrypt();
		zSession* ws = NetService::getMe().getSessionMgr().getWs();
		if (ws == NULL)
		{
			Zebra::logger->warn("[���]WS��δ���ӣ��ܾ��������");
			session->socket->OnEventColse();
			return;
		}

		zSession* ls = NetService::getMe().getSessionMgr().getLs();
		if (ls == NULL)
		{
			Zebra::logger->warn("[���]LS��δ���ӣ��ܾ��������");
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
	zSession* session = NetService::getMe().getSessionMgr().get(rSocket.SLongID());
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
			Zebra::logger->error("[���]�Ҳ���Э��:%d,��С:%d", pMsg->protocol,nSize);
			rSocket.OnEventColse();
			return;
		}
		else
		{
			Zebra::logger->info("[���]�յ�Э��:%d", pMsg->protocol);
			(handler->handlerFun)(session, pMsg,nSize + nSHeadSize - nCHeadSize);
		}
	}
	else
	{
		Zebra::logger->error("[���]�Ҳ���������:%lld", rSocket.SLongID());
		rSocket.OnEventColse();
	}
}

void PlayerMsgHandler::OnNetMsgExit(NetSocket& rSocket)
{
	// ��ӡ�˳�ԭ��  
	std::string strExitMsg;
	int32 nErrorCode = rSocket.ErrorCode(strExitMsg);
	Zebra::logger->error("[���]���ӶϿ�:%lld,�Ͽ�ԭ��:%s", rSocket.SLongID(), strExitMsg.c_str());

	zSession* session = NetService::getMe().getSessionMgr().get(rSocket.SLongID());
	ASSERT(session);

	// �������δ������֤�����Բ�����WS�� 
	if (session->status < E_CLIENT_STATUS_ENCRYPTED)
	{
		return;
	}

	// �����ͻ����˳���Ϣ 
	F2WRqPlayerExit sendExitWs;
	sendExitWs.nReason = nErrorCode;
	ReqSendToWorldServer(session, &sendExitWs, sendExitWs.GetPackLength());

	F2SRqPlayerExit sendExitScene;
	sendExitScene.nReason = nErrorCode;
	ReqSendToSceneServer(session, &sendExitScene, sendExitScene.GetPackLength());

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
		Zebra::logger->warn("[���]�޷�ת����LS,����%lld״̬δ��ɳ�ʼ��", pSession->id);
		return;
	}
	zSession* ls = NetService::getMe().getSessionMgr().getLs();
	if (ls == NULL)
	{
		Zebra::logger->warn("[���]�޷�ת����LS,�Ҳ���LS Session");
		return;
	}
	
	MSG_MAKE_PLAYER_SESSID(pSession->id,NetService::getMe().getServerID(),pMsg,nSize);
	ls->sendMsg((NetMsgSS*)(&vecMsgBuffer[0]), vecMsgBuffer.size());
}

// ���͵� ss
void PlayerMsgHandler::ReqSendToSceneServer(zSession* pSession, const NetMsgSS* pMsg,int32 nSize)
{
	if(pSession->status != E_CLIENT_STATUS_IN_SCENE)
	{
		Zebra::logger->warn("[���]�޷�ת����SS,����%lld״̬δ���볡��", pSession->id);
		return;
	}

	GateUser* gateUser = GateUserManager::getMe().getBySessID(pSession->id);
	if (gateUser)
	{
		zSession* ss = NetService::getMe().getSessionMgr().getSs(gateUser->sceneServerid);
		if (ss == NULL)
		{
			Zebra::logger->warn("[���]�޷�ת����SS,�Ҳ���SS,serverid:%d", gateUser->sceneServerid);
			return;
		}
		MSG_MAKE_PLAYER_SESSID(pSession->id, NetService::getMe().getServerID(), pMsg, nSize);
		ss->sendMsg((NetMsgSS*)(&vecMsgBuffer[0]), vecMsgBuffer.size());
	}
}

// ���͵� ws
void PlayerMsgHandler::ReqSendToWorldServer(zSession* pSession, const NetMsgSS* pMsg,int32 nSize)
{
	if(pSession->status <= E_CLIENT_STATUS_ENCRYPTED)
	{
		Zebra::logger->warn("[���]�޷�ת����WS,����%lld״̬δ��ɳ�ʼ��", pSession->id);
		return;
	}
	
	MSG_MAKE_PLAYER_SESSID(pSession->id,NetService::getMe().getServerID(),pMsg,nSize);
	zSession* ws = NetService::getMe().getSessionMgr().getWs();
	if (!ws)
	{
		Zebra::logger->warn("[���]�޷�ת����WS,�Ҳ���WS Session");

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
		char arrRandKey[MAX_ENCRYPTSIZE];
		zEncrypt::getRandKey(arrRandKey);
		arrRandKey[MAX_ENCRYPTSIZE - 1] = '\0';
		
		F2CEncryptInfo sendEncrypt;
		memcpy(sendEncrypt.encryptKey, arrRandKey, MAX_ENCRYPTSIZE);
		SendToPlayer(pSession, &sendEncrypt, sendEncrypt.GetPackLength());

		// Ҫ�ȷ����ݺ���ܸ� 
		strncpy(pSession->encrypt,arrRandKey,MAX_ENCRYPTSIZE);
		pSession->status = E_CLIENT_STATUS_ENCRYPTED;

		// ��÷�����״̬�Ƿ���� 
		SSCheckSerivces sendCheckSerivces;
		sendCheckSerivces.sessid = pSession->id;
		zSession* wsSession = NetService::getMe().getSessionMgr().getWs();
		if (!wsSession)
		{
			Zebra::logger->warn("[���]��¼ǰ����������״̬�Ƿ����ת��ʧ�ܣ��Ҳ���WS Session");
			return;
		}
		wsSession->sendMsg(&sendCheckSerivces, sendCheckSerivces.GetPackLength());

		pSession->status = E_CLIENT_STATUS_NOTIFY_INITED;
	}
	else
	{
		Zebra::logger->error("[���]����%lld״̬δ���ӳɹ����޷������Կ", pSession->id);
	}
}


