#include "GameServer_PCH.h"
#include "ProcWorldHandler.h"
#include "ScenesServer.h"
#include "SceneUserMgr.h"

ProcWorldHandler::ProcWorldHandler()
{
}


ProcWorldHandler::~ProcWorldHandler()
{
}

void ProcWorldHandler::RqEnterScene(zSession* pSession, const NetMsgSS* pMsg,int32 nSize)
{
	const S::SSRqEnterScene* packet = static_cast<const S::SSRqEnterScene*>(pMsg);

	zSession* dp = GameService::getMe().getSessionMgr().getDp();
	if (dp == NULL)
	{
		ASSERT(dp);
		return;
	}

	// 
	Scene* scene = SceneManager::getInstance().getSceneByID(packet->sceneid);
	if (scene == NULL)
	{

		return;
	}

	S::SSRqLoadUser sMsgLoad;
	sMsgLoad.uid = packet->uid;
	sMsgLoad.sessid = packet->sessid;
	sMsgLoad.fepsid = packet->fepsid;
	dp->sendMsg(&sMsgLoad, sizeof(sMsgLoad));
}

void ProcWorldHandler::NtEnterResult(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{
	const S::SSRqEnterResult* packet = static_cast<const S::SSRqEnterResult*>(pMsg);

	if (packet->nResult == S::SSRqEnterResult::E_ENTER_SUCCESS)
	{
		// �ɹ���ɾ�������ڴ漴�ɣ�����Ҫ��������
		SceneUser* pUser = GameService::getMe().getSceneUserMgr().getUserByID(packet->nCharID);
		if (pUser)
		{
			GameService::getMe().getSceneUserMgr().removeUser(pUser);
			GameService::getMe().getSceneUserMgr().DestroyObj(pUser);
		}

	}
	else if (packet->nResult == S::SSRqEnterResult::E_ENTER_FAIL)
	{
		// ʧ�ܣ���ʾǰ�˼��� 
	}

}

void ProcWorldHandler::NtLoadUids(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{

}
