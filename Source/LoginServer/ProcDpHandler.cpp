#include "ProcDpHandler.h"
#include "CommandS.h"
#include "LoginAccountMgr.h"
#include "NamesManager.h"

ProcDpHandler::ProcDpHandler(void)
{
}


ProcDpHandler::~ProcDpHandler(void)
{
}

void ProcDpHandler::RepNamesList(zSession* pSession, const NetMsgSS* pMsg,int32 nSize)
{
	const D2LNamesList* packet = static_cast<const D2LNamesList*>(pMsg);
	for (int32 i = 0 ; i < packet->nCount; ++i)
	{
		NamesManager::getMe().LoadItems(packet->arrNameList[i].arrName);
	}
}

void ProcDpHandler::AccountLogin(zSession* pSession, const NetMsgSS* pMsg,int32 nSize)
{

	//const D2LAccountLogin* packer = static_cast<const D2LAccountLogin*>(pMsg);

	//if(ClientSession* pClientSession = ClientSessionMgr::getMe().getSession(packer->clientSessionID))
	//{

	//	L2CAccountLogin sMsg;
	//	switch (packer->result)
	//	{
	//	case D2LAccountLogin::E_RESULT_SUCCESS:
	//		{
	//			pClientSession->SetStatus(E_CLIENT_STATUS_LOGINED);

	//			// ���ص�¼�ɹ���Ϣ 
	//			sMsg.nAccountId = packer->accountID;
	//			sMsg.nResult = L2CAccountLogin::E_RESULT_SUCCESS;
	//		}
	//		break;

	//	case D2LAccountLogin::E_RESULT_FAIL:
	//		{
	//			// ���ص�¼ʧ����Ϣ 
	//			sMsg.nResult = L2CAccountLogin::E_RESULT_FAIL;
	//		}	
	//		break;
	//	default:
	//		{
	//			return;
	//		}
	//		break;
	//	}

	//	pClientSession->SendMsgToFep(&sMsg,sMsg.GetPackLength());

	//	// �Ƿ���¼��Ƶ����¼��� 
	//	StAccountInfo* pAccountInfo = LoginAccountMgr::getMe().GetAccountInfo(packer->clientSessionID);
	//	if(!pAccountInfo)
	//	{
	//		pAccountInfo = LoginAccountMgr::getMe().AddAccountInfo(packer->clientSessionID);
	//		if(!pAccountInfo)
	//		{
	//			return;
	//		}
	//	}
	//	pAccountInfo->AddLoginTimes();
	//	if(pAccountInfo->CheckLoginIllegal())
	//	{
	//		// �������� TODO 

	//		// ɾ���ü�¼
	//		LoginAccountMgr::getMe().RemoveAccountInfo(packer->clientSessionID);
	//		return ;
	//	}
	//}	
}

void ProcDpHandler::CharacterList(zSession* pSession, const NetMsgSS* pMsg,int32 nSize)
{

	//const D2LCharacterList* packet = static_cast<const D2LCharacterList*>(pMsg);
	//if(ClientSession* pClientSession = ClientSessionMgr::getMe().getSession(packet->clientSessionID))
	//{

	//	if(pClientSession->Status() != E_CLIENT_STATUS_LOGINED)
	//	{

	//		return ; // �ǵ�¼���״̬�����ܻ�ý�ɫ�б� TODO 
	//	}

	//	L2CCharacterList sMsg;
	//	sMsg.nCount = packet->nCount;
	//	for (int32 i = 0; i < packet->nCount; ++i)
	//	{
	//		sMsg.arrInfo[i].nCharID = packet->arrInfo[i].nCharID;
	//		sMsg.arrInfo[i].nLevel = packet->arrInfo[i].nLevel;
	//		sMsg.arrInfo[i].nLastLogin = packet->arrInfo[i].nLastLogin;
	//		strcpy(sMsg.arrInfo[i].arrName,packet->arrInfo[i].arrName);
	//	}
	//	pClientSession->SendMsgToFep(&sMsg,sMsg.GetPackLength());	
	//}

}

void ProcDpHandler::RoleCreateResult(zSession* pSession, const NetMsgSS* pMsg,int32 nSize)
{
	//const D2LRoleCreateResult* pPacket = static_cast<const D2LRoleCreateResult*>(pMsg);
	//if(ClientSession* pClientSession = ClientSessionMgr::getMe().getSession(pPacket->clientSessionID))
	//{
	//	L2CRoleCreateResult sMsg;
	//	sMsg.nResult = pPacket->nResult;
	//	sMsg.nNewCharID = pPacket->nNewCharID;
	//	pClientSession->SendMsgToFep(&sMsg,sMsg.GetPackLength());
	//}
}




