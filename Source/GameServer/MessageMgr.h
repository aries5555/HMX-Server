#ifndef __MESSAGE_MGR_H_
#define __MESSAGE_MGR_H_


#include "Includes.h"
#include "SrvEngine.h"
#include "SceneUser.h"

#include "chatmsg.pb.h"

#define MAX_MSG_LENGTH 300

typedef std::map<int32, t_ChatBase, std::greater<int32> > UidChatMsgMapType;
typedef std::map<int32, t_ChatBase, std::greater<int32> > TeamChatMsgMapType;

class zMessage : public zEntry
{
public:

	zMessage()
	{
		createTime = readyTime = len = 0;
		memset(msg, 0, sizeof(msg));
	}

	int32 createTime;
	int32 readyTime;
	int16 len;
	char msg[MAX_MSG_LENGTH];
};


class MessageMgr : protected zEntryMgr<zEntryID>
{
public:
	MessageMgr(SceneUser* u);
	~MessageMgr();

	//bool Serialize(::protobuf::MyChatMsg& proto);
	//void UnSerialize(const ::protobuf::MyChatMsg& proto);

	zMessage* CreateObj();
	void DestroyObj(zMessage* obj);

	bool addMessage(zMessage* mess);
	void removeMessage(zMessage* mess);
	void removeMessageAll();
	void removeMessageBefore(int32 time);

	zMessage* getMessage(QWORD id);
	void getMessageNearest(int num);
	void getMessageNearestFrom(int num,QWORD fromID);
	void getMessageFromTo(QWORD formID,QWORD toID);

private:

	SceneUser* user;
	ObjPool<zMessage> objpool;


private:

	/* ������Ϣ �Է�ID=>��ϢID=>��Ϣ���� */
	std::map<int64, UidChatMsgMapType > chatOneMsg;

	/* Ⱥ����Ϣ��ȺID=>��ϢID=>��Ϣ���� */
	/* ������Ϣ��ͨ��ָ����ϢIDȥ������ݣ�����δ�����ģ����ᵥ������һ�ݣ�����ǹۿ�������ᱣ�� */
	/* ��������ֻ����WS�� */
	std::map<int32, TeamChatMsgMapType > chatTeamMsg;

};

#endif


