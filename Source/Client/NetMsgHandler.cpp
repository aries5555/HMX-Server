#include "Client_PCH.h"

NetMsgHandler::NetMsgHandler()
{
	/* common ��Ҫ�õ��ڲ�Э�� */
	/* �ڲ�Э�飬�����ֲ�ͬservertype����ȥ��ͳһ�����飬���¼�������б�ping�ȵȲ��� */
#define REGISTER_INTERNAL_MESSAGE(msg_idx,cls,handler) \
	{\
	RegisterMessage(msg_idx, sizeof(cls), boost::bind(&NetMsgHandler::handler, this, _1, _2, _3)); \
	}

	REGISTER_INTERNAL_MESSAGE(PRO_SS_RQ_LOGIN, SSRqLogin, recvLoginRequest);
	REGISTER_INTERNAL_MESSAGE(PRO_SS_RT_LOGINED, SSRtLogined, recvLoginReponse);

#undef REGISTER_INTERNAL_MESSAGE

	// from server
#define REGISTER_FEP_MESSAGE(msg_idx,cls,handler)\
	{\
	RegisterMessage(msg_idx, sizeof(cls), boost::bind(&PlayerProcHandler::handler, PlayerProcHandler::Instance(), _1, _2, _3)); \
	}

	REGISTER_FEP_MESSAGE(PRO_F2C_ENCRYPT_INFO, F2CEncryptInfo, RecvEncryptInfo);
	REGISTER_FEP_MESSAGE(PRO_F2C_LOGIN_READY_FINISH, F2CLoginReadyFinish, RecvLoginReadyFinish);
	REGISTER_FEP_MESSAGE(PRO_F2C_ENTER_SCENE_LOADED, F2CEnterSceneLoaded, RecvEnterScene);
	REGISTER_FEP_MESSAGE(PRO_L2C_ACC_LOGIN, L2CAccLogin, RecvLoginAccountResult);
	REGISTER_FEP_MESSAGE(PRO_S2C_CHAR_WORLD, S2CRepCharWorld, RecvChatWorld);
	REGISTER_FEP_MESSAGE(PRO_S2C_SCENE_INIT_RESULT, SSRtLogined, RecvSceneInitResult);
	REGISTER_FEP_MESSAGE(PRO_W2C_USERLIST, W2CUserList, RecvCharacterList);
	REGISTER_FEP_MESSAGE(PRO_W2C_CREATE_RET, W2CCreateRet, RecvRoleCreateResult);
	REGISTER_FEP_MESSAGE(PRO_S2C_CHAR_MAIN_DATA, S2CCharMainData, RecvCharacterMainData);
	REGISTER_FEP_MESSAGE(PRO_S2C_QUEST_MAIN_DATA, S2CQuestMainData, RecvQuestMainData);
	REGISTER_FEP_MESSAGE(PRO_S2C_SEND_DATA_FINISH, S2CSendDataFinish, RecvSendDataFinish);
	REGISTER_FEP_MESSAGE(PRO_S2C_SCENE_LOAD_INFO, S2CSceneLoadInfo, RecvEnterSceneInfo);
	REGISTER_FEP_MESSAGE(PRO_L2C_NAMES_LIST, L2CNamesList, RecvRandNames);
	REGISTER_FEP_MESSAGE(PRO_S2C_CHANNEL_JION, S2CChannelJion, RecvChannelJion);
	REGISTER_FEP_MESSAGE(PRO_S2C_CHANNEL_LEAVE, S2CChannelLeave, RecvChannelLeave);
	REGISTER_FEP_MESSAGE(PRO_S2C_RELATION_LIST, S2CRelationList, RecvRelationList);
	REGISTER_FEP_MESSAGE(PRO_S2C_RELATION_UPDATE, S2CRelationUpdate, RecvRelationUpdate);
	REGISTER_FEP_MESSAGE(PRO_S2C_RELATION_DELETE, S2CRelationDelete, RecvRelationDelete);
	REGISTER_FEP_MESSAGE(PRO_S2C_ITEM_MAIN_DATA, S2CUserPackages, RecvUserPackages);

#undef REGISTER_FEP_MESSAGE

}


NetMsgHandler::~NetMsgHandler()
{
}


void NetMsgHandler::OnNetMsgEnter(NetSocket& rSocket)
{
	Zebra::logger->info("���ӳɹ���������:id=%d ip=%s,port=%d", rSocket.SID(), rSocket.GetIp().c_str(), (int32)rSocket.GetPort());
	zSession* pSession = NetService::getMe().getSessionMgr().get(rSocket.SLongID());
	if (pSession)
	{
		if (pSession->serverType == zSession::SERVER_TYPE_CLIENT && pSession->sessionType == zSession::FOR_NULL)
		{
			Player* player = PlayerMgr::getMe().get(pSession->id);
			if (player)
			{
				PlayerProcHandler::SendEncrypt(player);
				Zebra::logger->info("����������Կ��Ϣ��:ip=%s port=%d", rSocket.GetIp().c_str(), (int32)rSocket.GetPort());
			}
		}
	}
	else
	{
		ASSERT(0);
	}
}

void NetMsgHandler::OnNetMsg(NetSocket& rSocket, NetMsgSS* pMsg, int32 nSize)
{
	zSession* pSession = NetService::getMe().getSessionMgr().get(rSocket.SLongID());
	if (pSession == NULL)
	{
		Zebra::logger->error("Can not find session");
		rSocket.OnEventColse();
		return;
	}

	// ���ܴ��� 
	static char msgEnBuffer[65536];
	static char msgUnBuffer[65536];

	int nCHeadSize = sizeof(NetMsgC);
	int nSHeadSize = sizeof(NetMsgSS);
	memcpy(&msgEnBuffer[0], pMsg, nSize);

	zEncrypt::xorCode(nSize, pSession->encrypt, msgEnBuffer, nSize);

	// ��װΪNetMsgSSͷЭ�飬�м䲹����ͷЭ����ֽڲ� 
	memcpy(&msgUnBuffer[0], msgEnBuffer, nCHeadSize);
	memset(&msgUnBuffer[nCHeadSize], 0, nSHeadSize - nCHeadSize);
	memcpy(&msgUnBuffer[nSHeadSize], &msgEnBuffer[nCHeadSize], nSize - nCHeadSize);

	pMsg = (NetMsgSS*)&msgUnBuffer[0];

	const MsgFunc* pMsgHandlerInfo = GetMsgHandler(pMsg->protocol);
	if (pMsgHandlerInfo == NULL)
	{
		Zebra::logger->error("�Ҳ�����Э��:%d,��С:%d", pMsg->protocol, nSize);
		rSocket.OnEventColse();
		return;
	}

	Zebra::logger->info("�յ�Э��=%d", pMsg->protocol);

	(pMsgHandlerInfo->handlerFun)((zSession*)(pSession), pMsg, nSize);

	

}

/* ��Server�Ͽ��ص�(��ʱsocket�Ѿ�����) */
void NetMsgHandler::OnNetMsgExit(NetSocket& rSocket)
{
	Zebra::logger->info("���ӶϿ���������:id=%d ip=%s,port=%d", rSocket.SID(), rSocket.GetIp().c_str(), (int32)rSocket.GetPort());
}

void NetMsgHandler::recvLoginRequest(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{
	const SSRqLogin* packet = static_cast<const SSRqLogin*>(pMsg);
	const zSerivceCfgMgr::Server* serverCfg = NetService::getMe().getServerCfgMgr().getServer(packet->serverID);
	if (!serverCfg)
	{
		ASSERT(0);
		return;
	}

	zServerRegMgr& regMgr = NetService::getMe().getServerRegMgr();
	zServerReg* addReg = regMgr.CreateObj();
	if (addReg)
	{
		SSRtLogined sendLg;
		addReg->id = packet->serverID;
		addReg->sessid = pSession->id;
		if (!regMgr.add(addReg))
		{
			Zebra::logger->error("ע�������ID�ظ�");
			ASSERT(0);
			regMgr.DestroyObj(addReg);
			sendLg.result = SSRtLogined::SUCCESS;
			pSession->sendMsg(&sendLg, sendLg.GetPackLength());
			return;
		}
		else
		{
			sendLg.result = SSRtLogined::SUCCESS;
			pSession->sendMsg(&sendLg, sendLg.GetPackLength());
		}

		if (serverCfg->recvsrvlist)
		{
			struct MyStruct : public execEntry<zServerReg>
			{
				virtual bool exec(zServerReg* entry)
				{
					const zSerivceCfgMgr::Server* serverCfg = NetService::getMe().getServerCfgMgr().getServer(entry->id);
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

			SSServerRegList sendList;
			std::vector<int32>::const_iterator it = exec.outServerID.begin();
			for (; it != exec.outServerID.end(); ++it)
			{
				sendList.reglist[sendList.count].id = *it;
				sendList.count++;
			}
			pSession->sendMsg(&sendList, sendList.GetPackLength());

		}

		if (serverCfg->broadcastlist)
		{
			struct MyStruct : public execEntry<zServerReg>
			{
				MyStruct(int32 serverID) :addServerID(serverID)
				{

				}

				virtual bool exec(zServerReg* entry)
				{
					const zSerivceCfgMgr::Server* serverCfg = NetService::getMe().getServerCfgMgr().getServer(entry->id);
					if (!serverCfg)
					{
						ASSERT(0);
						return true;
					}

					if (serverCfg->recvsrvlist)
					{
						zSession* session = NetService::getMe().getSessionMgr().get(entry->sessid);
						if (session)
						{
							SSServerRegList sendList;
							sendList.reglist[sendList.count].id = addServerID;
							sendList.count++;
							session->sendMsg(&sendList, sendList.GetPackLength());
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

void NetMsgHandler::recvLoginReponse(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{
	const SSRtLogined* packet = static_cast<const SSRtLogined*>(pMsg);
	if (packet->result == SSRtLogined::SUCCESS)
	{
		Zebra::logger->error("��¼�ɹ�");
	}
	else
	{
		Zebra::logger->error("��¼ʧ��");
		ASSERT(0);
	}
}










