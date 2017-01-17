#include "LoginServer_PCH.h"
#include "ProcFepHandler.h"
#include "NamesManager.h"



ProcFepHandler::ProcFepHandler(void)
{
}


ProcFepHandler::~ProcFepHandler(void)
{
}

void ProcFepHandler::RqAccountLogin(zSession* pSession, const NetMsgSS* pMsg,int32 nSize)
{

	const C2LAccountLogin* packet = static_cast<const C2LAccountLogin*>(pMsg);

	// ����ַ����Ƿ�Ϸ� TODO
	char wheres[100];
	bzero(wheres,sizeof(wheres));
	sprintf(wheres, "`username`='%s' AND `password`='%s'", packet->username, packet->password);

	const dbCol fields[] = 
	{
		{"id",DB_QWORD,sizeof(int64)},
		{NULL,0,0}
	};

#pragma pack(push,1)
	struct MyStruct
	{
		int64 id;
		MyStruct()
		{
			id = 0;
		}
	};
#pragma pack(pop)
	
	MyStruct data;
	int32 retsize = NetService::getMe().getDbMysql()->ExecSelectLimit("Account", fields, wheres, NULL, (unsigned char*)&data);
	if (retsize < 1)
	{
		Zebra::logger->warn("��¼ʧ��"); // ��¼��¼ʧ�ܵĴ������ﵽһ����������Ĭ��Ϊ�����ƽ� 
	}

	L2CAccLogin sendRet;
	sendRet.sessid = packet->sessid;
	sendRet.fepsid = packet->fepsid;
	sendRet.accid = data.id;
	sendRet.result = retsize == 1 ? 1 : 0;

	if (retsize == 1)
	{
		int32 nowTime = Zebra::timeTick->getNowTime();
		// md5(�ʺ�+��Կ+ʱ��)
		std::ostringstream outstr;
		outstr << data.id;
		outstr << SERVERKEY;
		outstr << nowTime;
		unsigned char md5str[MAX_NAMESIZE + 1];
		memset(md5str, 0, sizeof(md5str));
		EncryptMD5(md5str, (unsigned char*)outstr.str().c_str());
		md5str[MAX_NAMESIZE] = '\0';

		strncpy(sendRet.keymd5, (const char*)md5str, MAX_NAMESIZE);
		
		sendRet.keytime = nowTime;

		Zebra::logger->info("������Կ:%s", md5str);
	}

	pSession->sendMsg(&sendRet, sendRet.GetPackLength());

	Zebra::logger->info("%s��¼%s",packet->username,(retsize == 1 ? "�ɹ�":"ʧ��"));

	if (retsize)
	{
		// ���ͼ��ؽ�ɫ�б��ظ��û� 
		L2WLoadList sendWs;
		sendWs.sessid = packet->sessid;
		sendWs.fepsid = packet->fepsid;
		sendWs.accid = data.id;
		NetService::getMe().getSessionMgr().sendToWs(&sendWs, sendWs.GetPackLength());
	}
}

void ProcFepHandler::RqRoleCreate(zSession* pSession, const NetMsgSS* pMsg,int32 nSize)
{
	// ���͵�db���󴴽� 
	//ClientSession* pClientSession = ClientSessionMgr::getMe().getSession(pMsg->clientSessionID);
	//ASSERT(pClientSession);

	//const C2LRoleCreate* packet = static_cast<const C2LRoleCreate*>(pMsg);

	//// ������� 
	//if(packet->nType <= E_ROLE_TYPE_NULL || packet->nType >= E_ROLE_TYPE_MAX)
	//{
	//	return ;
	//}

	//// ������� 
	//if(packet->arrName[MAX_NAME_LENGTH - 1] != '\0')
	//{
	//	return ;
	//}

	//// ���ֳ������� 
	//if (strlen(packet->arrName) < 6 || strlen(packet->arrName) > 30)
	//{
	//	return;
	//}

	//L2DRoleCreate sMsg;
	//sMsg.nType = packet->nType;
	//sMsg.nAccountID = packet->nAccountID;
	//memcpy(sMsg.arrName,packet->arrName,MAX_NAME_LENGTH);

	//pClientSession->SendMsgToDp(&sMsg,sMsg.GetPackLength());

}

void ProcFepHandler::RqRandNames(zSession* pSession, const NetMsgSS* pMsg,int32 nSize)
{
	// Login�б������Ѿ����������е��ǳƣ��������ѡ������Դ�û��ʹ�ù����ǳ� 

	//const C2LRandNames* packet = static_cast<const C2LRandNames*>(pMsg);
	//ClientSession* pClientSession = ClientSessionMgr::getMe().getSession(packet->clientSessionID);
	//ASSERT(pClientSession);

	//L2CNamesList sMsg;
	//sMsg.nCount = 0;
	//for (int32 i = 0 ; i < 10; ++i)
	//{
	//	static char arrName[32];
	//	memset(arrName,0,sizeof(arrName));
	//	if(NamesManager::getMe().GetRandTtems(arrName))
	//	{
	//		memcpy(sMsg.arrNames[i],arrName,sizeof(arrName));
	//		sMsg.nCount++;
	//	}else
	//	{
	//		break;
	//	}
	//}
	//
	//pClientSession->sendMsg(&sMsg,sMsg.GetPackLength());

}
