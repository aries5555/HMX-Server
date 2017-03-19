#include "Client_PCH.h"
#include "PlayerProcHandler.h"
#include "NetMsgHandler.h"
#include "Player.h"


PlayerProcHandler::PlayerProcHandler(void)
{
}


PlayerProcHandler::~PlayerProcHandler(void)
{
}

void PlayerProcHandler::SendRequestClose(Player* player)
{
	player->session->socket->OnEventColse();
}

void PlayerProcHandler::SendEncrypt(Player* player)
{
	C::RqEncryptInfo send;
	player->SendMsg(&send,sizeof(send));
}

void PlayerProcHandler::SendLogin(Player* player)
{
	// ʹ��Ĭ���˺������� 
	C::RqAccountLogin send;
	zUtility::GBKToUTF8("hzd", send.username, sizeof(send.username));
	zUtility::GBKToUTF8("123", send.password, sizeof(send.password));
	player->SendMsg(&send, sizeof(send));
}


void PlayerProcHandler::SendLogin2(Player* player)
{
	// ʹ��Ĭ���˺������� 
	C::RqAccountLogin send;
	send.loginType = C::RqAccountLogin::LOGINTYPE_CREATERSA;
	//zUtility::GBKToUTF8("kfc", send.username, sizeof(send.username));
	//zUtility::GBKToUTF8("123", send.password, sizeof(send.password));
	player->SendMsg(&send, sizeof(send));
}

void PlayerProcHandler::SendRandName(Player* player)
{
	C::RqRandAccount send;
	player->SendMsg(&send, sizeof(send));
}

void PlayerProcHandler::SendCharacterList(Player* player)
{

}

void PlayerProcHandler::SendChar2World(Player* player)
{

}

void PlayerProcHandler::SendRoleCreate(Player* player)
{
	std::string arrXing[10];
	arrXing[0] = "��";
	arrXing[1] = "��";
	arrXing[2] = "��";
	arrXing[3] = "��";
	arrXing[4] = "��";
	arrXing[5] = "��";
	arrXing[6] = "��";
	arrXing[7] = "ŷ��";
	arrXing[8] = "�Ϲ�";
	arrXing[9] = "����";

	std::string arrMing[20];
	arrMing[0] = "����";
	arrMing[1] = "����";
	arrMing[2] = "��";
	arrMing[3] = "���";
	arrMing[4] = "��Զ";
	arrMing[5] = "�Ĳ�";
	arrMing[6] = "Ӣ��";
	arrMing[7] = "��Զ";
	arrMing[8] = "����";
	arrMing[9] = "���";
	arrMing[10] = "�ž�";
	arrMing[11] = "����";
	arrMing[12] = "���";
	arrMing[13] = "����";
	arrMing[14] = "����";
	arrMing[15] = "ٻѩ";
	arrMing[16] = "��ܿ";
	arrMing[17] = "��ѩ";
	arrMing[18] = "����";
	arrMing[19] = "����";

	int32 nXingIndex = zUtility::RangedRand(0,9);
	int32 nMingIndex = zUtility::RangedRand(0,19);

	std::stringstream strName;
	strName << arrXing[nXingIndex] << arrMing[nMingIndex];

	// ������ɫ 
	C::RqCreateRole send;
	send.accid = player->accid;
	send.roleType = 1;
	char nameUtf8[MAX_NAMESIZE + 1];
	memset(nameUtf8,0,sizeof(nameUtf8));
	zUtility::GBKToUTF8(strName.str().c_str(),nameUtf8,MAX_NAMESIZE);
	nameUtf8[MAX_NAMESIZE] = '\0';
	strcpy(send.name,nameUtf8);
	strncpy(send.keymd5, player->keymd5, MAX_NAMESIZE);
	send.keytime = player->keytime;

	player->SendMsg(&send, sizeof(send));
	printf(" ���󴴽���ɫ \n");
}

void PlayerProcHandler::SendRoleDelete(Player* player)
{
	// ������ɫ 
	C::RqDeleteRole send;
	send.uid = player->getFirstCharID();
	send.accid = player->accid;
	strncpy(send.keymd5, player->keymd5, MAX_NAMESIZE);
	send.keytime = player->keytime;

	player->SendMsg(&send, sizeof(send));
	printf(" ���󴴽���ɫ \n");
}

void PlayerProcHandler::SendSelectRole(Player* player)
{
	// ѡ���ɫ
	C::RqSelectRole send;
	send.uid = player->getFirstCharID();
	player->SendMsg(&send,sizeof(send));
	printf(" ѡ���ɫ \n");


}

void PlayerProcHandler::SendEnterChangeScene(Player* player)
{	
	C::RqChanageScene send;
	send.nSceneID = 10001;
	player->SendMsg(&send,sizeof(send));
}

void PlayerProcHandler::SendEnterChangeScene2(Player* player)
{
	C::RqChanageScene send;
	send.nSceneID = 10004;
	player->SendMsg(&send, sizeof(send));
}

void PlayerProcHandler::SendLoadResed(Player* player)
{

}

void PlayerProcHandler::SendReqSceneData(Player* player)
{
	printf(" ��ǰ�˳�ʼ���ó�����Դ��ɣ����󳡾�����Ҫ������\n");
	C::RqClientIsReady send;
	send.nLoadDataFlags = C::RqClientIsReady::E_DATA_TYPE_ALL;
	player->SendMsg(&send,sizeof(send));
}

void PlayerProcHandler::SendMoveTo(Player* player)
{
	C::RqPositionMove send;
	send.nNewX = 20;
	send.nNewY = 30;
	player->SendMsg(&send, sizeof(send));
}

void PlayerProcHandler::SendChatToWorld(Player* player)
{
	//RqChatToWorld send;
	//int leng = GBKToUTF8("Hello", send.msg.data, sizeof(send.msg.data));
	//send.msg.len = leng;
	//player->SendMsg(&send, sizeof(send));
}

void PlayerProcHandler::SendRelationList(Player* player)
{
	C::RqRelationList send;
	player->SendMsg(&send, sizeof(send));
}

void PlayerProcHandler::SendRelationAdd(Player* player)
{
	C::RqRelationAdd send;
	std::string strName = "���ž�";
	char nameUtf8[MAX_NAMESIZE + 1];
	memset(nameUtf8, 0, sizeof(nameUtf8));
	zUtility::GBKToUTF8(strName.c_str(), nameUtf8, MAX_NAMESIZE);
	strncpy(send.name, nameUtf8, MAX_NAMESIZE);
	player->SendMsg(&send, sizeof(send));
}

void PlayerProcHandler::SendRelationRmove(Player* player)
{
	C::RqRelationRemove send;
	send.uid = 100000001;
	player->SendMsg(&send, sizeof(send));
}

////////////////////////////����//////////////////////////////////////////

void PlayerProcHandler::RecvEncryptInfo(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{
	const C::RtEncryptInfo* packet = static_cast<const C::RtEncryptInfo*>(pMsg);
	Player* player = PlayerMgr::getMe().get(pSession->id);
	if (player)
	{
		memcpy(player->session->encrypt, packet->encryptKey, MAX_ENCRYPTSIZE);
	}

}

void PlayerProcHandler::RecvLoginReadyFinish(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{
	//SendLogin(player);
}

void PlayerProcHandler::RecvEnterScene(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{
	Player* player = PlayerMgr::getMe().get(pSession->id);
	if (player)
	{
		SendReqSceneData(player);
	}

}

void PlayerProcHandler::RecvChatWorld(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{
	int32 a = 1;
	const C::RtCharWorld* packet = static_cast<const C::RtCharWorld*>(pMsg);
	printf("Recveid Client ID: %s ,Msg:%s\n", packet->fromName, packet->sayMsg);
}

void PlayerProcHandler::RecvSceneInitResult(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{
	int32 a = 1;
}

void PlayerProcHandler::RecvRandNames(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{
	const C::RtNamesList* packet = static_cast<const C::RtNamesList*>(pMsg);
	for (int32 i = 0; i < packet->count; ++i)
	{
		printf("==== %s === \n", zUtility::Utf8ToGBK(packet->list[i].name));
	}
}

void PlayerProcHandler::RecvRelationList(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{

}

void PlayerProcHandler::RecvRelationUpdate(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{

}

void PlayerProcHandler::RecvRelationDelete(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{

}

void PlayerProcHandler::RecvUserPackages(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{

}

void PlayerProcHandler::RecvLoginAccountResult(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{
	Player* player = PlayerMgr::getMe().get(pSession->id);
	if (player)
	{
		const C::RtAccLogin* packet = static_cast<const C::RtAccLogin*>(pMsg);
		switch (packet->result)
		{
		case 0:
		{
			player->accid = packet->accid;
			strncpy(player->keymd5, packet->keymd5, MAX_NAMESIZE);
			player->keytime = packet->keytime;
			printf("Login success!\n");
		}
		break;
		default:
			printf("Login fail!\n");
		break;
		}
	}
}

void PlayerProcHandler::RecvCharacterList(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{
	Player* player = PlayerMgr::getMe().get(pSession->id);
	if (player)
	{
		const C::RtUserListLogon* packet = static_cast<const C::RtUserListLogon*>(pMsg);
		int32 nCount = 0;
		std::vector<int64> recvieUids;
		for (int32 i = 0; i < sizeof(packet->datas) / sizeof(packet->datas[0]); ++i)
		{
			const C::RtUserListLogon::UserInfo& data = packet->datas[i];
			if (data.id)
			{
				printf("ID:%-10lld Name:%-12s Lv:%-8d \n", data.id, zUtility::Utf8ToGBK(data.name), data.level);
				recvieUids.push_back(data.id);
				nCount++;
			}
		}

		if (nCount)
		{
			player->setCharList(recvieUids);
		}
	}

}

void PlayerProcHandler::RecvRoleCreateResult(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{
	const C::RtCreateRet* packet = static_cast<const C::RtCreateRet*>(pMsg);
	switch(packet->reasoin)
	{
	case 0:
		printf("�����½�ɫ�ɹ�\n");
		break;
	case 1:
		printf("����ʧ�ܣ���������\n");
		break;
	case 2:
		printf("����ʧ�ܣ��ǳ�ͬ��\n");
		break;
	case 3:
		printf("�������ݿ�ʧ��\n");
		return;
	}
}

void PlayerProcHandler::RecvCharacterMainData(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{

}

void PlayerProcHandler::RecvQuestMainData(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{

}

void PlayerProcHandler::RecvSendDataFinish(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{

}

void PlayerProcHandler::RecvEnterSceneInfo(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{
	H::logger->info("�յ�������Ϣ�����ͽ��볡��");
	Player* player = PlayerMgr::getMe().get(pSession->id);
	if (player)
	{
		SendReqSceneData(player);
	}
}

void PlayerProcHandler::RecvChannelJion(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{
	const C::RtChannelJion* packet = static_cast<const C::RtChannelJion*>(pMsg);
	H::logger->info("%s����Ƶ��%d", zUtility::Utf8ToGBK(packet->name),packet->channelID);
}

void PlayerProcHandler::RecvChannelLeave(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{
	const C::RtChannelLeave* packet = static_cast<const C::RtChannelLeave*>(pMsg);
	H::logger->info("%s����Ƶ��%d", zUtility::Utf8ToGBK(packet->name), packet->channelID);
}


