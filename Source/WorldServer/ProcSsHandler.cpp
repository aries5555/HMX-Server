#include "WorldServer_PCH.h"
#include "ProcSsHandler.h"
#include "SceneRegMgr.h"
#include "WorldUserMgr.h"

ProcSsHandler::ProcSsHandler()
{
}

ProcSsHandler::~ProcSsHandler()
{
}

void ProcSsHandler::RqSceneRegister(zSession* pSession, const NetMsgSS* pMsg,int32 nSize)
{
	zSession* session = static_cast<zSession*>(pSession);
	const S2WRegisterScene* packet = static_cast<const S2WRegisterScene*>(pMsg);
	SceneReg* reg = SceneRegMgr::getMe().get(packet->sceneid);
	if (reg)
	{
		Zebra::logger->error("�Ѿ�ע�����������ID");
		return;
	}
	else
	{
		reg = SceneRegMgr::getMe().CreateObj();
		reg->id = packet->sceneid;
		reg->tempid = packet->sceneTempID;
		reg->sessid = pSession->id;
		reg->mapid = packet->mapid;
		bool ret = SceneRegMgr::getMe().add(reg);
		Zebra::logger->info("ע��ó���%s,id=%lld,name=%s",ret?"�ɹ�":"ʧ��", packet->sceneid, packet->name);
	}
}

void ProcSsHandler::RqSceneCancel(zSession* pSession, const NetMsgSS* pMsg,int32 nSize)
{
	//zSession* pSSession = static_cast<zSession*>(pSession);
	//const S2WReqCancelScene* packet = static_cast<const S2WReqCancelScene*>(pMsg);
	//ASSERT( packet->nSceneNum <= MAX_MAP_NUM);

	//std::vector<int32> vecSceneID;
	//for (int32 i = 0; i < packet->nSceneNum; ++i)
	//{
	//	int32 nSceneID = packet->arrSceneID[i];
	//	ASSERT(nSceneID > 0);
	//	vecSceneID.push_back(nSceneID);
	//}
	//SceneRegisterManager::getMe().RemoveScene(vecSceneID,pSSession->getServerID());

}

void ProcSsHandler::RpEnterSceneResult(zSession* pSession, const NetMsgSS* pMsg,int32 nSize)
{
	//zSession* pSSession = static_cast<zSession*>(pSession);
	//const S2WEnterSceneResult* packet = static_cast<const S2WEnterSceneResult*>(pMsg);
	//int32 nCSID = packet->nSessionID;
	//int32 nSceneID = packet->nSceneID;
	//switch(packet->nResult)
	//{
	//case S2WEnterSceneResult::E_ENTER_SUCCESS:
	//	{
	//		ClientSession* pCSession = ClientSessionMgr::getMe().getSession(nCSID);
	//		ASSERT(pCSession);
	//		zSession* oldSsSession = pCSession->GetSsSession();
	//		if (oldSsSession != pSSession)
	//		{
	//			Zebra::logger->info("Send Leave Old Scene"); // todo 
	//		}
	//		pCSession->SetSceneSession(pSSession,nSceneID);
	//		pCSession->SetStatus(E_CLIENT_STATUS_IN_SCENE);
	//	}
	//	break;
	//case S2WEnterSceneResult::E_ENTER_FAIL:
	//	{
	//		Zebra::logger->info("Enter Scene Fail!");
	//		// ֪ͨԭ����  
	//		if (packet->nCross) // ���
	//		{
	//			ClientSession* pCSession = ClientSessionMgr::getMe().getSession(nCSID);
	//			ASSERT(pCSession);
	//			W2SNtEnterResult sMsgResult;
	//			sMsgResult.nResult = W2SNtEnterResult::E_ENTER_FAIL;
	//			pCSession->SendMsgToSs(&sMsgResult,sizeof(sMsgResult));
	//		}
	//		else // ͨ����¼����Ĭ�Ͻ�����һ��ʧ�� 
	//		{


	//			// ��Ҫ����������  10001 

	//		}
	//	}
	//	break;
	//}
}

void ProcSsHandler::RpChangeScene(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{
	//const S2WChangeScene* packet = static_cast<const S2WChangeScene*>(pMsg);

	//Zebra::logger->info("Request change new scene id:%d",packet->sceneID);

	//WorldUser* user = NetService::getMe().getWorldUserMgr().get(packet->uid);
	//if (user == NULL)
	//{
	//	Zebra::logger->error( "Not Found User!");
	//	return;
	//}

	//const SceneBaseInfo* sceneInfo = SceneRegisterManager::getMe().GetSceneBaseInfo(0,packet->sceneID);
	//if (sceneInfo == NULL)
	//{
	//	Zebra::logger->error("Not Found register sceneid :%d", packet->sceneID);
	//	return;
	//}

	//if (sceneInfo->nSceneType == 1) // ��ͨ��ͼ
	//{
	//	// ����ҵ�����ʵ�Ȩ�� �����Ϊ������� ��ǰ����ֵ = ��serverѡ������ + ��scene��ʹ������ 
	//	SceneInfo* pSceneInfo = SceneManager::getMe().GetLoadLestServerID(packet->sceneID);
	//	if (pSceneInfo == NULL)
	//	{
	//		ASSERT(pSceneInfo);
	//		return; // ֪ͨǰ��ѡ�����ĳ��� 
	//	}

	//	// ѡ�����ó��� 
	//	zSession* pSSession = ServerSessMgr::getMe().getBySs(pSceneInfo->nServerID);
	//	if (pSSession == NULL)
	//	{
	//		ASSERT(pSSession);
	//		return;
	//	}

	//	user->sceneid = packet->sceneID;
	//	user->SceneSesion = pSSession;

	//	//W2SRqEnterScene sMsg;
	//	//sMsg.sessid = user->getSessID();
	//	//sMsg.uid = user->id;
	//	//sMsg.nSceneID = user->sceneid;
	//	//sMsg.nFepServerID = user->fepSession->id;
	//	//sMsg.nEnterType = 1;

	//	//user->sendToSs(&sMsg, sMsg.GetPackLength());

	//	Zebra::logger->info("Send to dist scene of requst enter this %lld scene", user->sessid);
	//	return;
	//}
	//else if (sceneInfo->nSceneType == 2) // ������ͼ 
	//{

	//}
	//else
	//{
	//	ASSERT(0);
	//}
}

void ProcSsHandler::TurnChatToOne(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{
	const S2WChatToOne* cmd = static_cast<const S2WChatToOne*>(pMsg);
	
	WorldUser* toUser = NetService::getMe().getWorldUserMgr().get(cmd->toUID);
	if (toUser == NULL) /* �������� */ 
	{
		/* ����Ϣ���͵����߳��������� */
	}
	else
	{
		/* ����Ϣ���͵���ǰ���ڳ��������� */
		//toUser->send
	}

}

void ProcSsHandler::NtBroadcastMsg(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{
	const C2SChatToWorld* packet = static_cast<const C2SChatToWorld*>(pMsg);
//	Zebra::logger->info("��������:%s", Utf8ToGBK(packet->msg.data));

	// ת�������� 
}


void ProcSsHandler::rqRelAdd(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{
	const C2SRelationAdd* packet = static_cast<const C2SRelationAdd*>(pMsg);
	
	OfflineUser* offuser = NetService::getMe().getOfflineUserMgr().getUserByName(packet->name);
	if (offuser == NULL)
	{
		Zebra::logger->warn("�Ҳ����ú���[%s]",Utf8ToGBK(packet->name));
		return;
	}

	pSession->sendMsg(pMsg, nSize);

	WorldUser* worldUser = NetService::getMe().getWorldUserMgr().getByName(packet->name);
	if (worldUser)
	{
		// ֪ͨ�±��ӵ��� 
	}

}


