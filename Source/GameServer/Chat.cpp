#include "ScenesServer.h"
#include "SceneUser.h"

extern DWORD cancel_country_need_money;
extern DWORD is_cancel_country;


/**
* \brief GMָ������
*
*/
Gm GmCmds[] =
{
	//��ͨGM��
	//{"reloadScript",Gm::reloadScript,Gm::gm_mode |Gm::captain_mode | Gm::super_mode | Gm::debug_mode,"���µ���ű�"},
	//{"help",Gm::help,Gm::gm_mode |Gm::captain_mode | Gm::super_mode | Gm::debug_mode,"��ʾָ�����"},
	//{"levelup",Gm::levelup,Gm::gm_mode |Gm::captain_mode | Gm::super_mode | Gm::debug_mode,"����"},
	//{"goto",Gm::goTo_Gm,Gm::gm_mode |Gm::captain_mode | Gm::super_mode | Gm::debug_mode,"��תλ��"},
	//{"gomap",Gm::gomap_Gm,Gm::gm_mode |Gm::captain_mode | Gm::super_mode | Gm::debug_mode,"��ת��ͼ"},
	{NULL,NULL,0,NULL}
};


template<typename TMsg>
struct MsgSendToAllPlayer : public execEntry<zSession>
{
	MsgSendToAllPlayer(TMsg* __msg,int32 __size) :_msg(__msg), _size(__size)
	{
	}
	virtual bool exec(zSession *entry)
	{
		if (entry->sessionType == zSession::FOR_FEP)
		{
			entry->sendMsg(_msg, _size);
		}
		return true;
	}
	TMsg* _msg;
	int32 _size;
};


/*
* \brief ���û�������Ϣ
* ����û����ڸ÷�����,����sessionת��
*
* \param id �û���ID
* \param cmd ��Ϣ
* \param len ��Ϣ����
*
* \return �Ƿ�ɹ�
*/
bool sendCmdByID(DWORD id, const void *cmd, int len)
{

	return true;
}


/*
* \brief ���û�������Ϣ
* ����û����ڸ÷�����,����sessionת��
*
* \param id �û�����ʱID
* \param cmd ��Ϣ
* \param len ��Ϣ����
*
* \return �Ƿ�ɹ�
*/
bool sendCmdByTempID(DWORD id, const void *cmd, int len)
{

	return true;
}


/*
* \brief ���û�������Ϣ
* ����û����ڸ÷�����,����sessionת��
*
* \param name �û�������
* \param cmd ��Ϣ
* \param len ��Ϣ����
*
* \return �Ƿ�ɹ�
*/
bool sendCmdByName(char * name, const void *cmd, int len)
{

	return true;
}

/**
* \brief ���캯��
*
*
* \param pUser: ������Ƶ�����û�
*/
Channel::Channel(SceneUser *pUser) :zEntry()
{
	creater.id = pUser->id;
	creater.tempid = pUser->tempid;
	strncpy(creater.name, pUser->name, MAX_NAMESIZE);
}

Channel::Channel(DWORD chID, const std::string& _name)
{
	creater.id = chID;
	creater.tempid = chID;
	strncpy(creater.name, _name.c_str(), MAX_NAMESIZE);
}

Channel::~Channel()
{

}

/**
* \brief ���͸���Ƶ���������û�
*
*
* \param cmd: ��������
* \param len:���ݳ���
* \return �����Ƿ�ɹ�
*/
bool Channel::sendCmdToAll(const NetMsgSS *cmd, int len)
{
	BUFFER_CMD(S::SSNtBoradCastMsg, send, MAX_BUFFERSIZE);
	send->msgtype = S::SSNtBoradCastMsg::TYPE_ALL;
	send->regid = 0;
	send->size = len;
	memcpy(send->data, cmd, len);

	MsgSendToAllPlayer<S::SSNtBoradCastMsg> exec(send,sizeof(S::SSNtBoradCastMsg) + send->size * sizeof(send->data[0]));
	GameService::getMe().getSessionMgr().execEveryConn(exec);

	return true;
}

/**
* \brief �뿪Ƶ��
*
*
* \param uname: �뿪��Ƶ�����û�
* \return ��Ƶ���Ƿ��ܼ�������
*/
bool Channel::remove(const char *uname)
{
	WORD found = has(uname);
	if (found != (WORD)-1)
	{
		H::logger->info("%s�뿪%s������Ƶ��", uname, creater.name);
		C::RtChannelLeave send;
		send.channelID = tempid;
		strncpy(send.name, uname, MAX_NAMESIZE);
		sendCmdToAll(&send, sizeof(send));

		if ((found + 1) < (WORD)userlist.size())
		{
			userlist[found] = userlist.back();
		}
		userlist.pop_back();
	}
	if (userlist.empty())
		return false;
	else
		return true;
}

/**
* \brief ��������Ƶ��
*
*
* \param pUser: Ҫ������û�
* \return �����Ƿ�ɹ�
*/
bool Channel::add(SceneUser *pUser)
{
	if (pUser != NULL)
	{
		WORD found = has(pUser->name);
		if (found == (WORD)-1)
		{
			H::logger->info("%s����%s������Ƶ��", zUtility::Utf8ToGBK(pUser->name), creater.name);

			zEntryC temp;
			temp.id = pUser->id;
			temp.tempid = pUser->tempid;
			strncpy(temp.name, pUser->name, MAX_NAMESIZE);
			userlist.push_back(temp);

			/* ���Լ����͸������� */
			C::RtChannelJion send;
			send.channelID = tempid;
			strncpy(send.name, pUser->name, MAX_NAMESIZE);
			sendCmdToAll(&send, sizeof(send));

			/* �������г�Ա���Լ� */
			for (DWORD i = 0; i < userlist.size(); i++)
			{
				strncpy(send.name, userlist[i].name, MAX_NAMESIZE);
				pUser->sendCmdToMe(&send, sizeof(send));
			}
			return true;
		}
	}
	return false;
}

/**
* \brief ����Ƶ�����Ƿ����ĳ��
*
*
* \param name: �û���
* \return ���ڷ��ظ��û���Ƶ���е�λ��,�����ڷ���-1
*/
WORD Channel::has(const char *name)
{
	if (name)
	{
		for (DWORD i = 0; i < userlist.size(); i++)
		{
			if (strncmp(userlist[i].name, name, MAX_NAMESIZE) == 0)
				return i;
		}
	}
	return (WORD)-1;
}

/**
* \brief ת��������Ϣ��9��
*
*
* \param pUser: ��������
* \param rev: ת��������
* \param cmdLen: ���ݳ���
* \return �����Ƿ�ɹ�
*/
bool Channel::sendNine(SceneUser *pUser, const NetMsgSS *cmd, DWORD len)
{
	BUFFER_CMD(S::SSNtBoradCastMsg, send, MAX_BUFFERSIZE);
	send->msgtype = S::SSNtBoradCastMsg::TYPE_ALL;
	send->regid = 0;
	send->size = len;
	memcpy(send->data, cmd, len);
	MsgSendToAllPlayer<S::SSNtBoradCastMsg> exec(send,sizeof(S::SSNtBoradCastMsg) + send->size * sizeof(send->data[0]));
	GameService::getMe().getSessionMgr().execEveryConn(exec);
	return true;
}

#define getMessage(msg,msglen,pat)  \
	do  \
{  \
	va_list ap;  \
	bzero(msg,msglen);  \
	va_start(ap,pat);    \
	vsnprintf(msg,msglen - 1,pat,ap);  \
	va_end(ap);  \
}while(false)


/**
* \brief ���͹��ҹ���
*
*
* \param countryID: countryID
* \param infoType: infoType
* \param pattern: ����
* \return �����Ƿ�ɹ�
*/
bool Channel::sendCountryInfo(DWORD countryID, DWORD infoType, const char *pattern, ...)
{

	return true;
}

/**
* \brief ����ȫ������
*
* \param infoType: infoType
* \param pattern: ����
* \return �����Ƿ�ɹ�
*/
bool Channel::sendAllInfo(DWORD infoType, const char *pattern, ...)
{

	return true;
}

/**
* \brief ������Ϣ������Ƶ��
*
*
* \param pUser: ��������
* \param pattern: ����
* \return �����Ƿ�ɹ�
*/
bool Channel::sendCountry(SceneUser *pUser, const char *pattern, ...)
{

	return true;
}

/**
* \brief ��������Ϣ������Ƶ��
*
*
* \param pUser: ����ָ����û�
* \param rev: �յ���ָ��
* \param cmdLen: ָ���
* \return �����Ƿ�ɹ�
*/
bool Channel::sendCountry(SceneUser *pUser, const NetMsgSS *cmd, DWORD len)
{
	BUFFER_CMD(S::SSNtBoradCastMsg, send, MAX_BUFFERSIZE);
	send->msgtype = S::SSNtBoradCastMsg::TYPE_ALL;
	send->regid = 0;
	send->size = len;
	memcpy(send->data, cmd, len);
	MsgSendToAllPlayer<S::SSNtBoradCastMsg> exec(send, sizeof(S::SSNtBoradCastMsg) + send->size * sizeof(send->data[0]));
	GameService::getMe().getSessionMgr().execEveryConn(exec);
	return true;
}

/**
* \brief ���͸��õ�ͼ�������û�
*
* \param scene ��ͼ
* \param cmd ��Ϣ
* \param len: ����
* \return �����Ƿ�ɹ�
*/
bool Channel::sendCmdToMap(Scene* scene, const NetMsgSS *cmd, int len)
{
	if (cmd == NULL) return false;
	if (!scene) return false;
	//scene->SendToAllEntiries(cmd,len);
	return true;
}

/**
* \brief ���͸��õ�ͼ�������û�
*
* \param mapID ��ͼID
* \param cmd ��Ϣ
* \param len: ����
* \return �����Ƿ�ɹ�
*/
bool Channel::sendCmdToMap(DWORD mapID, const NetMsgSS *cmd, int len)
{
	BUFFER_CMD(S::SSNtBoradCastMsg, send, MAX_BUFFERSIZE);
	send->msgtype = S::SSNtBoradCastMsg::TYPE_ALL;
	send->regid = mapID;
	send->size = len;
	memcpy(send->data, cmd, len);
	MsgSendToAllPlayer<S::SSNtBoradCastMsg> exec(send, sizeof(S::SSNtBoradCastMsg) + send->size * sizeof(send->data[0]));
	GameService::getMe().getSessionMgr().execEveryConn(exec);
	return true;
}

/**
* \brief ����9����Ϣ
*
*
* \param pNpc: �����͵�npc
* \param pattern: ����
* \return �����Ƿ�ɹ�
*/
bool Channel::sendNine(const SceneNpc *pNpc, const char *pattern, ...)
{
	if (0 == pNpc)  return false;

	char buf[MAX_CHATINFO];
	getMessage(buf, MAX_CHATINFO, pattern);
	zRTime ctv;
	Cmd::stChannelChatUserCmd send;
	send.dwType = Cmd::CHAT_TYPE_NPC;
	send.dwFromID = pNpc->tempid;
	send.dwChatTime = ctv.sec();
	bzero(send.pstrName, sizeof(send.pstrName));
	bzero(send.pstrChat, sizeof(send.pstrChat));
	strncpy((char *)send.pstrChat, buf, MAX_CHATINFO - 1);
	strncpy((char *)send.pstrName, pNpc->name, MAX_NAMESIZE);
	pNpc->scene->sendCmdToNine(pNpc->getPosI(), &send, sizeof(send), pNpc->dupIndex);
	return true;
}

/**
* \brief ת��������Ϣ
*
*
* \param teamid: ����id
* \param rev: ��Ҫת����ָ��
* \param cmdLen: ָ���
* \return ת���Ƿ�ɹ�
*/
bool Channel::sendTeam(DWORD teamid, const NetMsgSS *cmd, DWORD len)
{
	BUFFER_CMD(S::SSNtBoradCastMsg, send, MAX_BUFFERSIZE);
	send->msgtype = S::SSNtBoradCastMsg::TYPE_ALL;
	send->regid = teamid;
	send->size = len;
	memcpy(send->data, cmd, len);
	MsgSendToAllPlayer<S::SSNtBoradCastMsg> exec(send, sizeof(S::SSNtBoradCastMsg) + send->size * sizeof(send->data[0]));
	GameService::getMe().getSessionMgr().execEveryConn(exec);
	return true;
}

/**
* \brief ����ϵͳ��Ϣ
*
*
* \param pUser: Ҫ������Ϣ���û�
* \param type: ϵͳ��Ϣ����
* \param pattern: ����
* \return �����Ƿ�ɹ�
*/
bool Channel::sendSys(SceneUser *pUser, int type, const char *pattern, ...)
{

	return false;
}

bool Channel::sendSys(DWORD dwUserTempID, int type, const char *pattern, ...)
{
	//SceneUser *pToUser = SceneUserManager::getMe().getUserByTempID(dwUserTempID);
	//if (pToUser)
	//{
	//	char buf[MAX_CHATINFO];
	//	getMessage(buf, MAX_CHATINFO, pattern);
	//	zRTime ctv;
	//	Cmd::stChannelChatUserCmd send;
	//	send.dwType = Cmd::CHAT_TYPE_SYSTEM;
	//	send.dwSysInfoType = type;//ϵͳ��Ϣ������
	//	send.dwChatTime = ctv.sec();
	//	bzero(send.pstrName, sizeof(send.pstrName));
	//	bzero(send.pstrChat, sizeof(send.pstrChat));
	//	strncpy((char *)send.pstrChat, buf, MAX_CHATINFO - 1);
	//	pToUser->sendCmdToMe(&send, sizeof(send));
	//	return true;
	//}
	return false;
}

/**
* \brief ˽��
*
*
* \param pUser: ��������
* \param rev:����ָ��
* \param cmdLen: ָ���
* \return �����Ƿ�ɹ�
*/
bool Channel::sendPrivate(SceneUser *pUser, const NetMsgSS *rev, DWORD cmdLen)
{

	return true;
}

/**
* \brief Ψһʵ��
*
*/
ChannelM::ChannelM()
{
	channelUniqeID = new zUniqueDWORDID(1);
}

ChannelM::~ChannelM()
{
	SAFE_DELETE(channelUniqeID);
}

/**
* \brief �õ�һ��Ψһ���
*
*
* \param tempid: Ψһ���(���)
* \return �õ��ı���Ƿ�Ψһ
*/
bool ChannelM::getUniqeID(QWORD &tempid)
{
	tempid = channelUniqeID->get();
	return (tempid != channelUniqeID->invalid());
}

/**
* \brief �ջ�һ��Ψһ���
*
*
* \param tempid: �ջصı��
*/
void ChannelM::putUniqeID(const QWORD &tempid)
{
	channelUniqeID->put(tempid);
}

/**
* \brief ��������Ƶ��
*
*
* \param channel: Ƶ��
* \return �����Ƿ�ɹ�
*/
bool ChannelM::add(Channel *channel)
{
	bool ret;
	mlock.lock();
	ret = addEntry(channel);
	mlock.unlock();
	return ret;
}

/**
* \brief ������Ƶ����ɾ��һ���û�
*
*
* \param name: �û���
*/
void ChannelM::removeUser(const char *name)
{
	// ��������Ƶ�����name�û�
	for (zEntryName::hashmap::iterator it = zEntryName::ets.begin(); it != zEntryName::ets.end(); it++)
	{
		Channel *temp = (Channel *)it->second;
		temp->remove(name);
	}
}

/**
* \brief ������Ƶ����ɾ��һ������Ƶ��
*
*
* \param dwChannelID: Ƶ��id
*/
void ChannelM::remove(DWORD dwChannelID)
{
	Channel *ret = NULL;
	mlock.lock();
	ret = (Channel *)getEntryByTempID(dwChannelID);
	removeEntry(ret);
	mlock.unlock();
}

/**
* \brief �õ�һ������Ƶ��
*
*
* \param dwChannelID: Ƶ��id
* \return ����Ƶ��
*/
Channel *ChannelM::get(DWORD dwChannelID)
{
	Channel *ret = NULL;
	mlock.lock();
	ret = (Channel *)getEntryByTempID(dwChannelID);
	mlock.unlock();
	return ret;
}

Channel* ChannelM::CreateObj(SceneUser *pUser)
{
	return objpool.CreateObj(pUser);
}

Channel* ChannelM::CreateObj(DWORD chID, const std::string& _name)
{
	return objpool.CreateObj(chID, _name);
}

void ChannelM::DestroyObj(Channel* obj)
{
	objpool.DestroyObj(obj);
}

/**
* \brief ��16������תΪ10����
*
*
* \param ch: 16�����ַ�
* \return ת�����10������
*/
BYTE hexchtoi(char &ch)
{
	if (ch >= '0' && ch <= '9')
	{
		return BYTE(ch - '0');
	}
	else if ((ch >= 'A' && ch <= 'F') || (ch >= 'a' && ch <= 'f'))
	{
		return BYTE(toupper(ch) - 'A') + 10;
	}
	return 0;
}



