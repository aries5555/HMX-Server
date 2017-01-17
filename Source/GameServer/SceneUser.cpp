#include "SceneUser.h"
#include "ResourceMgr.h"
#include "def_entity.h"
#include "ServerDefine.h"
#include "def_resource.h"
#include "RelationCtrl.h"


SceneUser::SceneUser(): SceneEntryPk(zSceneEntry::SceneEntry_Player)
	, uuid(this), objM(this), usm(this), mesM(this), relM(this)
{
	clientReady = false;
	userModity = false;
	initDataFinish = false;
};

SceneUser::~SceneUser()
{

}

void SceneUser::CheckSaveToDb(int32 nSrvTime)
{
	// ����Ƿ����޸� 
	if (__INTERAVAL_FIVE_SECOND__)
	{
		if (!userModity) return;
		userModity = false;
		SaveToDb(0);
	}
}

bool SceneUser::loadFromDb(const D2SLoadUser* packet, int32 nSize)
{
	// ��������������
	memcpy(&userbase,&packet->base,sizeof(userbase));

	// ��ʼ��Entryʵ������ 
	this->id = userbase.id;
	this->tempid = packet->sessid;
	strncpy(this->name, userbase.name, MAX_NAMESIZE);

	// ��������������
	::protobuf::UserBinary proto;
	proto.ParsePartialFromArray(packet->data, packet->size);
	UnSerialize(proto);

	return true;
}

bool SceneUser::SaveToDb(int32 nScoketEventCode)
{
	BUFFER_CMD(S2DSaveUser,send,MAX_BUFFERSIZE);

	send->uid = this->id;
	memcpy(&send->base,&userbase,sizeof(send->base));
	::protobuf::UserBinary proto;

	Serialize(proto);
	proto.SerializeToArray(send->data, MAX_BUFFERSIZE - sizeof(S2DSaveUser));

	send->size = proto.ByteSize();
	NetService::getMe().getSessionMgr().sendToDp(send, sizeof(S2DSaveUser) + send->size * sizeof(send->data[0]));

	return true;
}

// �������� 
bool SceneUser::Serialize(::protobuf::UserBinary& proto)
{
	//* ������������� */ 
	::protobuf::Relation* relation = proto.mutable_relation();
	if (relation)
	{
		relM.serialize(*relation);
	}
	return true;
}

// ��ʼ����ɫ�������� 
void SceneUser::UnSerialize(const ::protobuf::UserBinary& proto)
{
	/* ���������ݽ��� */ 
	const ::protobuf::Relation& relation = proto.relation();
	relM.unserialize(relation);
}

/* ����-����С�߼�����Ĺ��� */
void SceneUser::Online()
{

	/* ��������Ƶ�� */
	Channel* wdCh = NetService::getMe().getChannelM().get(CHANNEL_TYPE_WORLD);
	if (wdCh)
	{
		wdCh->add(this);
	}
	else
	{
		Zebra::logger->error("Not Found The World Channel");
	}

	relM.sendAllRelList();
}

void SceneUser::Update(const zTaskTimer* timer)
{	
	//CheckSaveToDb(nSrvTime);

	//if (__INTERAVAL_ONE_SECOND__)
	//{
	//	int32 nowTime = Zebra::timeTick->getNowTime();
	//	Timer(nowTime);

	//}
}

void SceneUser::Timer(int32 curTime)
{
	ucm.Timer(curTime);

	//Channel* wdCh = NetService::getMe().getChannelM().get(CHANNEL_TYPE_WORLD);
	//if (wdCh)
	//{
	//	S2CRepCharWorld msg;
	//	wdCh->sendCmdToAll(&msg, (int)msg.GetPackLength());
	//}
}

void SceneUser::UpdateAttribute()
{

}

void SceneUser::OnExpChange(const ValueType& vOldValue, const ValueType& vNewValue)
{

}

void SceneUser::OnMapIDChange(const ValueType& vOldValue, const ValueType& vNewValue)
{

}

void SceneUser::OnClothesChange(const ValueType& vOldValue, const ValueType& vNewValue)
{

}

void SceneUser::OnWeaponChange(const ValueType& vOldValue, const ValueType& vNewValue)
{

}

void SceneUser::OnMoneyChange(const ValueType& vOldValue, const ValueType& vNewValue)
{
	S2CCharMoneyData msg;
	msg.nGold = 0;
	msg.nSilver = 0;
	msg.nCopper = 0;
	sendCmdToMe(&msg, msg.GetPackLength());
}

void SceneUser::sendCmdToMe(NetMsgSS* pMsg, int32 nSize)
{
	if (!initDataFinish)
	{
		Zebra::logger->warn("Server Not initDataFinish");
		ASSERT(0);
		return;
	}

	if (!clientReady)
	{
		Zebra::logger->warn("ClientReady Not Ready");
		return;
	}
	SendToFep(pMsg, nSize);
}

void SceneUser::SendToFep(NetMsgSS* pMsg, int32 nSize)
{
	zSession* session = NetService::getMe().getSessionMgr().getFep(fepsid);
	if (session)
	{
		pMsg->sessid = this->sessid;
		pMsg->fepsid = this->fepsid;
		session->sendMsg(pMsg, nSize);
	}
}

void SceneUser::SendToDp(NetMsgSS* pMsg, int32 nSize)
{
	pMsg->sessid = this->sessid;
	pMsg->fepsid = this->fepsid;
	NetService::getMe().getSessionMgr().sendToDp(pMsg, nSize);
}

void SceneUser::SendToWs(NetMsgSS* pMsg, int32 nSize)
{
	pMsg->sessid = this->sessid;
	pMsg->fepsid = this->fepsid;
	NetService::getMe().getSessionMgr().sendToWs(pMsg, nSize);
}


void SceneUser::sendMainToMe()
{
	/* ��ɫ��������  */ 
	S2CCharMainData sMsg;
	//sMsg.userVal = userAttribute;
	//sMsg.pkVal = GetEntryPkValBase();
	sendCmdToMe(&sMsg, sMsg.GetPackLength());

	/* �������� */
	S2CUserPackages sendItemMsg;
	std::vector<qObject*> allItems;
	getAllItemSlots(allItems);
	sendItemMsg.nCount = 0;
	for (int i = 0; i < allItems.size(); ++i)
	{
		sendItemMsg.items[sendItemMsg.nCount].nUniqueID = allItems[i]->tempid;
		sendItemMsg.items[sendItemMsg.nCount].nItemID = allItems[i]->itemID;
		sendItemMsg.items[sendItemMsg.nCount].nItemNum = allItems[i]->itemNum;
		sendItemMsg.items[sendItemMsg.nCount].nIndex = allItems[i]->id;
		sendItemMsg.items[sendItemMsg.nCount].nLock = 0;
		sendItemMsg.nCount++;
	}
	Zebra::logger->debug("Items Count:%u", sendItemMsg.nCount);
	sendCmdToMe(&sendItemMsg, sendItemMsg.GetPackLength());
}

void SceneUser::setupCharBase()
{

}

bool SceneUser::CheckMoneyEnough(int32 nType, int32 nNum)
{
	//switch (nType)
	//{
	//case 1:
	//{
	//	return (GetUserAttrInt32(USER_ATTR_GOLD) < nNum);
	//}
	//break;
	//case 2:
	//{
	//	return (GetUserAttrInt32(USER_ATTR_SILVER) < nNum);
	//}
	//break;
	//case 3:
	//{
	//	return (GetUserAttrInt32(USER_ATTR_COPPER) < nNum);
	//}
	//break;
	//default:
	//	break;
	//}
	return false;
}

bool SceneUser::TrySubMoney(int32 type, int32 num)
{
	return SubMoney(type, num, false, true);

}

bool SceneUser::SubMoney(int32 nType, int32 nNum, bool notify, bool isTry)
{
	//switch (nType)
	//{
	//case 1:
	//{
	//	int32 nGold = GetUserAttrInt32(USER_ATTR_GOLD);
	//	if (nGold < nNum) return false;
	//	if (isTry) return true;
	//	SetUserAttr(USER_ATTR_GOLD, nGold - nNum);
	//}
	//break;
	//case 2:
	//{
	//	int32 nSilver = GetUserAttrInt32(USER_ATTR_SILVER);
	//	if (nSilver < nNum) return false;
	//	if (isTry) return true;
	//	SetUserAttr(USER_ATTR_SILVER, nSilver - nNum);
	//}
	//break;
	//case 3:
	//{
	//	int32 nCopper = GetUserAttrInt32(USER_ATTR_COPPER);
	//	if (nCopper < nNum) return false;
	//	if (isTry) return true;
	//	SetUserAttr(USER_ATTR_COPPER, nCopper - nNum);
	//}
	//break;
	//default:
	//	return false;
	//	break;
	//}

	//if (notify)
	//{
	//	S2CCharMoneyData sendMsg;
	//	sendMsg.nGold = GetUserAttrInt32(USER_ATTR_GOLD);
	//	sendMsg.nSilver = GetUserAttrInt32(USER_ATTR_SILVER);
	//	sendMsg.nCopper = GetUserAttrInt32(USER_ATTR_COPPER);
	//	SendToMe(&sendMsg,sizeof(sendMsg));
	//}

	return true;
}

void SceneUser::changeHP(const SDWORD &hp)
{

}

void SceneUser::changeSP(const SDWORD &sp)
{

}

void SceneUser::changeMP(const SDWORD &mp)
{

}


int SceneUser::isEnemy(SceneEntryPk *entry, bool notify, bool good)
{
	return true;
}


SceneEntryPk* SceneUser::getMaster()
{
	return this;
}


SceneEntryPk* SceneUser::getTopMaster()
{
	return this;
}


bool SceneUser::isDie()
{
	return false;
}


DWORD SceneUser::getLevel() const
{
	return SceneEntryPk::GetLevel();
}



bool SceneUser::needType(const DWORD &needtype)
{
	return false;
}


bool SceneUser::addSkillToMe(zSkill *skill)
{
	return false;
}


bool SceneUser::needWeapon(DWORD skillid)
{
	return false;
}


bool SceneUser::isPkZone(SceneEntryPk *other)
{
	return false;
}


bool SceneUser::reduce(const DWORD &object, const BYTE num)
{
	return false;
}


bool SceneUser::checkReduce(const DWORD &object, const BYTE num)
{
	return false;
}


bool SceneUser::doSkillCost(const zSkillB *base)
{
	return false;
}

void SceneUser::showCurrentEffect(const WORD &state, bool isShow, bool notify)
{

}


bool SceneUser::preAttackMe(SceneEntryPk *pUser, const Cmd::stAttackMagicUserCmd *rev, bool physics, const bool good)
{
	return false;
}

void SceneUser::toDie(const DWORD &dwTempID)
{

}

SWORD SceneUser::directDamage(SceneEntryPk *pAtt, const SDWORD &dam, bool notify)
{
	
	return 0;
}