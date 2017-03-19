#include "GameServer_PCH.h"


NetMsgHandler::NetMsgHandler()
{
	/* common ��Ҫ�õ��ڲ�Э�� */
	/* �ڲ�Э�飬�����ֲ�ͬservertype����ȥ��ͳһ�����飬���¼�������б�ping�ȵȲ��� */ 
#define REGISTER_INTERNAL_MESSAGE(msg_idx,cls,handler) \
	{\
	RegisterMessage(msg_idx, sizeof(cls), boost::bind(&NetMsgHandler::handler, this, _1, _2, _3)); \
}

	REGISTER_INTERNAL_MESSAGE(S::SS_RQ_LOGIN,S::SSRqLogin,doLoginRequest);
	REGISTER_INTERNAL_MESSAGE(S::SS_RT_LOGINED,S::SSRtLogined,doLoginReponse);
	REGISTER_INTERNAL_MESSAGE(S::SS_RQ_PING_S,S::SSRqPingToS, doPingRequest);
	REGISTER_INTERNAL_MESSAGE(S::SS_RT_SERVERINFO_LIST, S::SSServerRegList, doSrvListNotifty);

#undef REGISTER_INTERNAL_MESSAGE

	/*  ��WS������ҵ��Э�� */
#define REGISTER_W2S_MESSAGE(msg_idx,cls,handler) \
	{\
		RegisterMessage(msg_idx, sizeof(cls), boost::bind(&ProcWorldHandler::handler, ProcWorldHandler::Instance(), _1, _2, _3)); \
	}

	REGISTER_W2S_MESSAGE(S::SS_RQ_ReqTransfer, S::SSRqEnterScene, RqEnterScene);		/* ������볡�� */
	REGISTER_W2S_MESSAGE(S::SS_RQ_ENTER_RESULT, S::SSRqEnterResult, NtEnterResult);/* ������볡�� */


#undef REGISTER_W2S_MESSAGE

	// dp 
#define REGISTER_DP_MESSAGE(msg_idx,cls,handler)\
	{\
	RegisterMessage(msg_idx, sizeof(cls), boost::bind(&ProcDpHandler::handler, ProcDpHandler::Instance(), _1, _2, _3)); \
	}

	REGISTER_DP_MESSAGE(S::SS_RT_LOAD_USER, S::SSRtLoadUser, RtLoadUserData);

#undef REGISTER_DP_MESSAGE

		// ls
#define REGISTER_LS_MESSAGE(msg_idx,cls,handler)\
	{\
	RegisterMessage(msg_idx, sizeof(cls), boost::bind(&ProcLsHandler::handler, ProcLsHandler::Instance(), _1, _2, _3)); \
	}

//	REGISTER_LS_MESSAGE(PRO_L2W_LOADLIST, L2WLoadList, RqLoadList);

#undef REGISTER_LS_MESSAGE

	/* ��FEP��Э�� */
#define REGISTER_RQ_MESSAGE(msg_idx,cls,handler)\
	{\
	RegisterMessage(msg_idx, sizeof(cls), boost::bind(&ProcFepHandler::handler, ProcFepHandler::Instance(), _1, _2, _3)); \
	}\

	REGISTER_RQ_MESSAGE(S::SS_RQ_PLAYER_EXIT, S::SSRqPlayerExit, doPlayerExit);
	REGISTER_RQ_MESSAGE(C::RQ_SCENE_INIT_DATA, C::RqClientIsReady, doClientIsReady);	/* ���󳡾����� */
	REGISTER_RQ_MESSAGE(C::RQ_CHANGE_SCENE, C::RqClientIsReady, doChangeScene);		/* �л����� */
	REGISTER_RQ_MESSAGE(C::RQ_POSITION_MOVE, C::RqPositionMove, doPositionMove);	/* �����ƶ� */
	REGISTER_RQ_MESSAGE(C::RQ_SHOPPING_BUY_ITME, C::RqShoppingBuyItem, doShoppingBuyItem); /* �̳� */
	REGISTER_RQ_MESSAGE(C::RQ_SHOPPING_SELL_ITME, C::RqShoppingSellItem, doShoppingSellItem); /* �̳� */

	REGISTER_RQ_MESSAGE(C::RQ_ITEM_USE_OBJECT, C::RqItemUseObject, doUseItem);
	REGISTER_RQ_MESSAGE(C::RQ_CHAT_TO_WORLD, C::RqChatToWorld, doChatToWorld);

	REGISTER_RQ_MESSAGE(C::RQ_RELATION_LIST, C::RqRelationList, doRelationList);
	REGISTER_RQ_MESSAGE(C::RQ_RELATION_ADD, C::RqRelationAdd, doRelationAdd);
	REGISTER_RQ_MESSAGE(C::RQ_RELATION_REMOVE, C::RqRelationRemove, doRelationRemove);

#undef REGISTER_RQ_MESSAGE

}


NetMsgHandler::~NetMsgHandler()
{ 
}


void NetMsgHandler::OnNetMsgEnter(NetSocket& rSocket)
{
	H::logger->info("���ӳɹ���������:id=%d ip=%s,port=%d", rSocket.SID(),rSocket.GetIp().c_str(),(int32)rSocket.GetPort());
	zSession* pSession = GameService::getMe().getSessionMgr().get(rSocket.SLongID());
	if (pSession)
	{
		if (pSession->serverType == zSession::SERVER_TYPE_CLIENT)
		{
			S::SSRqLogin send;
			send.serverID = GameService::getMe().getServerID();
			send.serivceID = pSession->serivceid;
			pSession->sendMsg(&send, sizeof(send));
			H::logger->info("���͵�¼��Ϣ��:ip=%s port=%d", rSocket.GetIp().c_str(), (int32)rSocket.GetPort());
		}
	}
	else
	{
		ASSERT(0);
	}
}

void NetMsgHandler::OnNetMsg(NetSocket& rSocket, NetMsgSS* pMsg,int32 nSize)
{
	zSession* pSession = GameService::getMe().getSessionMgr().get(rSocket.SLongID());
	if(pSession == NULL)
	{
		H::logger->error("Can not find session");
		rSocket.OnEventColse();
		return ;
	}

	const MsgFunc* pMsgHandlerInfo = GetMsgHandler(pMsg->protocol);
	if(pMsgHandlerInfo == NULL)
	{
		H::logger->error("�Ҳ�����Э��:%d,��С:%d", pMsg->protocol,nSize);
		rSocket.OnEventColse();
		return;
	}

	H::logger->info("�յ�Э��=%d", pMsg->protocol);

	(pMsgHandlerInfo->handlerFun)((zSession*)(pSession),pMsg,nSize);

}

/* ��Server�Ͽ��ص�(��ʱsocket�Ѿ�����) */ 
void NetMsgHandler::OnNetMsgExit(NetSocket& rSocket)
{     
	H::logger->info("���ӶϿ���������:id=%d ip=%s,port=%d", rSocket.SID(), rSocket.GetIp().c_str(), (int32)rSocket.GetPort());
}

void NetMsgHandler::doLoginRequest(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{
	const S::SSRqLogin* packet = static_cast<const S::SSRqLogin*>(pMsg);
	const zSerivceCfgMgr::Server* serverCfg = GameService::getMe().getServerCfgMgr().getServer(packet->serverID);
	if (!serverCfg)
	{
		ASSERT(0);
		return;
	}

	pSession->setSessionType(serverCfg->getSessType());
	pSession->serivceid = packet->serivceID;
	pSession->serverid = packet->serverID;
	zServerRegMgr& regMgr = GameService::getMe().getServerRegMgr();
	zServerReg* addReg = regMgr.CreateObj();
	if (addReg)
	{
		S::SSRtLogined sendLg;
		addReg->id = packet->serverID;
		addReg->sessid = pSession->id;
		if (!regMgr.add(addReg))
		{
			H::logger->error("ע�������ID�ظ�");
			ASSERT(0);
			regMgr.DestroyObj(addReg);
			sendLg.result = S::SSRtLogined::SUCCESS;
			pSession->sendMsg(&sendLg, sizeof(sendLg));
			return;
		}
		else
		{
			sendLg.result = S::SSRtLogined::SUCCESS;
			pSession->sendMsg(&sendLg, sizeof(sendLg));
		}

		if (serverCfg->recvsrvlist)
		{
			struct MyStruct : public execEntry<zServerReg>
			{
				virtual bool exec(zServerReg* entry)
				{
					const zSerivceCfgMgr::Server* serverCfg = GameService::getMe().getServerCfgMgr().getServer(entry->id);
					if (!serverCfg)
					{
						ASSERT(0);
						return true;
					}

					if (serverCfg->broadcastlist)
					{
						outServerID.push_back(entry->id);
					}
					return true;
				}
				std::vector<int32> outServerID;
			};

			MyStruct exec;
			regMgr.execEveryServer(exec);
			BUFFER_CMD(S::SSServerRegList, send, MAX_USERDATASIZE);
			send->count = 0;
			std::vector<int32>::const_iterator it = exec.outServerID.begin();
			for (; it != exec.outServerID.end(); ++it)
			{
				send->reglist[send->count].id = *it;
				send->count++;
			}
			pSession->sendMsg(send, send->getSize());

		}

		if (serverCfg->broadcastlist)
		{
			struct MyStruct : public execEntry<zServerReg>
			{
				MyStruct(int32 serverID):addServerID(serverID)
				{

				}

				virtual bool exec(zServerReg* entry)
				{
					const zSerivceCfgMgr::Server* serverCfg = GameService::getMe().getServerCfgMgr().getServer(entry->id);
					if (!serverCfg)
					{
						ASSERT(0);
						return true;
					}

					if (serverCfg->recvsrvlist)
					{
						zSession* session = GameService::getMe().getSessionMgr().get(entry->sessid);
						if (session)
						{
							BUFFER_CMD(S::SSServerRegList,send,MAX_USERDATASIZE);
							send->count = 0;
							send->reglist[send->count].id = addServerID;
							send->count++;
							session->sendMsg(send,send->getSize());
						}
					}
					return true;
				}

				int32 addServerID;
			};
			MyStruct exec(addReg->id);
			regMgr.execEveryServer(exec);
		}
	}
	else
	{
		ASSERT(0);
	}

}

void NetMsgHandler::doLoginReponse(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{
	const S::SSRtLogined* packet = static_cast<const S::SSRtLogined*>(pMsg);
	if (packet->result == S::SSRtLogined::SUCCESS)
	{
		H::logger->error("��¼�ɹ�");
		if (pSession->sessionType == zSession::FOR_WORLD)
		{
			SceneManager::getInstance().init();
		}

	}
	else
	{
		H::logger->error("��¼ʧ��");
		ASSERT(0);
	}
}

void NetMsgHandler::doPingRequest(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{

}

void NetMsgHandler::doSrvListNotifty(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{
	const S::SSServerRegList* packet = static_cast<const S::SSServerRegList*>(pMsg);

	// to connect
	for (int32 i = 0; i < packet->count; ++i)
	{
		int32 serverID = packet->reglist[i].id;
		const zSerivceCfgMgr::Server* serverCfg = GameService::getMe().getServerCfgMgr().getServer(serverID);
		if (serverCfg == NULL)
		{
			H::logger->error("�����Ҳ����÷���������ID:%d",serverID);
			continue;
		}

		std::map<int32, zSerivceCfgMgr::Serivce>::const_iterator it = serverCfg->serivces.begin();
		for (; it != serverCfg->serivces.end();++it)
		{
			const zSerivceCfgMgr::Serivce& info = it->second;
			if (stricmp(info.name.c_str(), "server") == 0 && stricmp(info.fun.c_str(), "forss") == 0)
			{
				zSession* session = GameService::getMe().getSessionMgr().connect(info.id, info.ip.c_str(), info.port,
					boost::bind(&NetMsgHandler::OnNetMsgEnter, NetMsgHandler::Instance(), _1),
					boost::bind(&NetMsgHandler::OnNetMsg, NetMsgHandler::Instance(), _1, _2, _3),
					boost::bind(&NetMsgHandler::OnNetMsgExit, NetMsgHandler::Instance(), _1)
				);
				if (!session)
				{
					H::logger->error("Connect Server Fail!");
					ASSERT(0);
					continue;
				}
				session->setSessionType(serverCfg->getSessType());
				session->setServerID(serverID);
			}
		}
	}
}


