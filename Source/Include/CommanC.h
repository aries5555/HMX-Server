#ifndef __COMMON_Rq_H_
#define __COMMON_Rq_H_

#include "BaseDefine.h"
#include "DbConfig.h"
#include "NetConfig.h"
#include "csCommon.h"

namespace C
{
	/*
		��������ͻ��˻�ͻ����������ֱ��ͨ�ŵ�Э��
	 */

#pragma pack(push,1)


	enum ProRqFunc
	{
		PRO_LOGIN = PRO_C2S + 100,		// ��¼��� 
		PRO_SCENE = PRO_C2S + 200,		// ������� 
		PRO_USER = PRO_C2S + 300,		// �������  
		PRO_EQUIP = PRO_C2S + 400,		// װ�����
		PRO_ITEM = PRO_C2S + 500,		// �������
		PRO_QUEST = PRO_C2S + 600,		// ������� 
		PRO_CHANNEL = PRO_C2S + 700,	// Ƶ����� 
		PRO_RELATION = PRO_C2S + 800,	// ����ϵ
		PRO_CHAT = PRO_C2S + 900,		// ����ģ��
		PRO_SHOP = PRO_C2S + 1000,		// �̳�ģ��
		PRO_PACK = PRO_C2S + 1100,		// ����ģ��
		PRO_MESSAGE = PRO_C2S + 1200,	// ����ģ��
	};

	// �����Ͽ����� 
	const int32 RQ_CLOSE = PRO_LOGIN + 1;
	struct RqClose : public NetMsgSS
	{
		RqClose() :NetMsgSS(RQ_CLOSE)
		{
		}
	};

	// ���ͼ������� 
	const int32 RQ_ENCRYPT = PRO_LOGIN + 2;
	struct RqEncryptInfo : public NetMsgSS
	{
		RqEncryptInfo() :NetMsgSS(RQ_ENCRYPT)
		{
		}
	};

	// ������Կ 
	const int32 RT_ENCRYPT_INFO = PRO_LOGIN + 3;
	struct RtEncryptInfo : public NetMsgSS
	{
		RtEncryptInfo() :NetMsgSS(RT_ENCRYPT_INFO)
		{

		}
		char encryptKey[MAX_ENCRYPTSIZE + 1];
	};


	// �������Լ�����¼����׼����� 
	const int32 RT_LOGIN_READY_FINISH = PRO_LOGIN + 4;
	struct RtLoginReadyFinish : public NetMsgSS
	{
		RtLoginReadyFinish() :NetMsgSS(RT_LOGIN_READY_FINISH)
		{

		}
	};

	// �ʺŵ�¼ 
	const int32 RQ_ACCOUNT_LOGIN = PRO_LOGIN + 5;
	struct RqAccountLogin : public NetMsgSS
	{
		RqAccountLogin() :NetMsgSS(RQ_ACCOUNT_LOGIN)
		{
			loginType = LOGINTYPE_NAMEPASS;
			bzero(username, sizeof(username));
			bzero(password, sizeof(password));
		}
		enum
		{
			LOGINTYPE_NAMEPASS = 0,	//��ͨ�ʺ������¼
			LOGINTYPE_RSA,			//RSA�����¼
			LOGINTYPE_CREATENAME,	//������ͨ�ʺ�
			LOGINTYPE_CREATERSA,	//����RSA�ʺ�
		};
		int8 loginType;
		char username[MAX_NAMESIZE + 1];
		char password[MAX_NAMESIZE + 1];
	};

	// ע���ʺ�
	const int32 RQ_ACCOUNT_REGIEST = PRO_LOGIN + 6;
	struct RqAccountRegiest : public NetMsgSS
	{
		RqAccountRegiest() :NetMsgSS(RQ_ACCOUNT_REGIEST)
		{
			bzero(username, sizeof(username));
			bzero(password, sizeof(password));
		}
		char username[MAX_NAMESIZE + 1];
		char password[MAX_NAMESIZE + 1];
	};

	// �������� 
	const int32 RQ_ACCOUNT_RAND = PRO_LOGIN + 7;
	struct RqRandAccount : public NetMsgSS
	{
		RqRandAccount() :NetMsgSS(RQ_ACCOUNT_RAND)
		{
			bzero(username, sizeof(username));
			bzero(password, sizeof(password));
		}
		char username[MAX_NAMESIZE + 1];
		char password[MAX_NAMESIZE + 1];
	};

	struct t_NameInfo
	{
		char name[MAX_NAMESIZE + 1];
	};

	// �����б� 
	const int32 RT_NAMES_LIST = PRO_LOGIN + 8;
	struct RtNamesList : public NetMsgSS
	{
		RtNamesList() :NetMsgSS(RT_NAMES_LIST)
		{
			count = 0;
		}
		int8 count;
		t_NameInfo list[0];
	};

	// ѡ���ɫ 
	const int32 RQ_Rq_SELECT_ROLE = PRO_LOGIN + 9;
	struct RqSelectRole : public NetMsgSS
	{
		int64 uid;
		RqSelectRole() :NetMsgSS(RQ_Rq_SELECT_ROLE)
		{
			uid = 0;
		}
	};

	// ���ص�¼��Ϣ 
	const int32 RT_ACC_LOGIN = PRO_LOGIN + 10;
	struct RtAccLogin : public NetMsgSS
	{
		RtAccLogin() :NetMsgSS(RT_ACC_LOGIN)
		{
			accid = result = keytime = 0;
			memset(keymd5, 0, MAX_NAMESIZE);
		}
		int64 accid;
		int32 result; //0�ɹ�,1ʧ��,2...
		char keymd5[MAX_NAMESIZE + 1];
		int32 keytime;
	};

	// ������ɫ 
	const int32 RQ_CREATE_ROLE = PRO_LOGIN + 11;
	struct RqCreateRole : public NetMsgSS
	{
		int64 accid;
		int8 roleType;
		char name[MAX_NAMESIZE + 1];
		char keymd5[MAX_NAMESIZE + 1];
		int32 keytime;

		RqCreateRole() :NetMsgSS(RQ_CREATE_ROLE)
		{
			accid = roleType = keytime = 0;
			memset(name, 0, sizeof(name));
			memset(keymd5, 0, sizeof(keymd5));
		}
	};

	// �������
	const int32	RT_CREATE_RET = PRO_LOGIN + 12;
	struct RtCreateRet : public NetMsgSS
	{
		RtCreateRet() :NetMsgSS(RT_CREATE_RET)
		{
			reasoin = newid = 0;
		}
		int8 reasoin;
		int64 newid;
	};

	// ɾ����ɫ
	const int32 RQ_DELETE_ROLE = PRO_LOGIN + 13;
	struct RqDeleteRole : public NetMsgSS
	{
		RqDeleteRole() :NetMsgSS(RQ_DELETE_ROLE)
		{
			uid = accid = keytime = 0;
			memset(keymd5, 0, sizeof(keymd5));
		}
		int64 uid;
		int64 accid;
		char keymd5[MAX_NAMESIZE + 1];
		int32 keytime;
	};

	// ��ɫ�б�
	const int32 RT_USERLIST_LOGIN = PRO_LOGIN + 14;
	struct RtUserListLogon : public NetMsgSS
	{
		RtUserListLogon() :NetMsgSS(RT_USERLIST_LOGIN)
		{

		}
		struct UserInfo
		{
			int64 id;
			char name[MAX_NAMESIZE + 1];
			int16 level;
			UserInfo()
			{
				id = level = 0;
				memset(name, 0, sizeof(name));
			}
		};
		UserInfo datas[4];
	};

	// ���������ʺ�
	const int32 RQ_GENENER_ACCOUNT = PRO_LOGIN + 15;
	struct rqGenenerAccount : public NetMsgSS
	{
		rqGenenerAccount() :NetMsgSS(RQ_GENENER_ACCOUNT)
		{
			bzero(inpassword, sizeof(inpassword));
		}
		char inpassword[MAX_NAMESIZE + 1];
	};

	//�������ɵ��ʺ�
	const int32 RT_GENERATE_ACCOUNT = PRO_LOGIN + 16;
	struct rtGenerateAccount : public NetMsgSS
	{
		rtGenerateAccount() :NetMsgSS(RT_GENERATE_ACCOUNT)
		{
			AccounID = 0;
			bzero(publickey, sizeof(publickey));
			bzero(privatekey, sizeof(privatekey));
		}
		int64 AccounID;
		char publickey[MAX_ACCNAMESIZE + 1];
		char privatekey[MAX_ACCNAMESIZE + 1];
	};

	//////////////////////////////����ģ��////////////////////////////////////////////

	// �������
	const int32 RT_ENTER_SCENE_LOADED = PRO_SCENE + 1;
	struct RtEnterSceneLoaded : public NetMsgSS
	{

		RtEnterSceneLoaded() :NetMsgSS(RT_ENTER_SCENE_LOADED)
		{

		}
		enum EEnterSceneResult
		{
			SUCCESS = 0,
			FAIL
		};
		int32 nResult;
	};

	//������س���������
	const int32 RQ_SCENE_INIT_DATA = PRO_SCENE + 2;
	struct RqClientIsReady : public NetMsgSS
	{
		RqClientIsReady() :NetMsgSS(RQ_SCENE_INIT_DATA)
		{

		}

		enum
		{
			E_DATA_TYPE_NULL = 0x00000000,
			E_DATA_TYPE_CHARMAIN = 0x00000001,
			E_DATA_TYPE_PACKAGE = 0x00000002,
			E_DATA_TYPE_RELATION = 0x00000004,
			E_DATA_TYPE_PET = 0x00000008,
			E_DATA_TYPE_ALL = 0x0fffffff,
		};

		int32 nLoadDataFlags; // ��Ҫ���ص����� 
	};

	const int32 RT_CHAR_WORLD = PRO_SCENE + 3; // ss�ϵ��������� 
	struct RtCharWorld : public NetMsgSS
	{
		RtCharWorld() :NetMsgSS(RT_CHAR_WORLD)
		{
			fromUID = sayLen = 0;
			memset(fromName, 0, sizeof(fromName));
			memset(sayMsg, 0, sizeof(sayMsg));
		}
		int64 fromUID;
		char fromName[MAX_NAME_LENGTH];
		int32 sayLen;
		char sayMsg[MAX_CHAR_WORLD_MSG_LENGTH];
	};

	// ���볡���ĳ�ʼ����� 
	const int32 RT_SCENE_INIT_RESULT = PRO_SCENE + 4; // ������ʼ�� 
	struct RtSceneInitResult : public NetMsgSS
	{
		RtSceneInitResult() :NetMsgSS(RT_SCENE_INIT_RESULT)
		{

		}
		enum
		{
			SUCCESS = 0,
			FAIL
		};
		int32 nResult;
	};

	const int32 RT_SCENE_LOAD_INFO = PRO_SCENE + 5; // ����ĳ�����Ϣ 
	struct RtSceneLoadInfo : public NetMsgSS
	{
		RtSceneLoadInfo() :NetMsgSS(RT_SCENE_LOAD_INFO)
		{
			mapid = 0;
		}
		int32 mapid;
	};

	// ����������� 
	const int32 RT_SEND_DATA_FINISH = PRO_SCENE + 6;
	struct RtSendDataFinish : public NetMsgSS
	{
		RtSendDataFinish() :NetMsgSS(RT_SEND_DATA_FINISH)
		{
			nServerTime = nMsgOrderID = 0;
		}
		// ��������һЩ���ֵ ������ʱ���  
		int32 nServerTime; // ������ʱ��
		int32 nMsgOrderID; // ��Ϣ˳��ֵ��������Ҽ�� 	
	};

	/*
	 *	�л�����
	 */
	const int32 RQ_CHANGE_SCENE = PRO_SCENE + 7;	// �л�����
	struct RqChanageScene : public NetMsgSS
	{
		RqChanageScene() :NetMsgSS(RQ_CHANGE_SCENE)
		{
			nSceneID = 0;
		}

		int32 nSceneID;
	};


	// fep->ws->ss,��ssȷ�� 
	const int32 RQ_SWITCH_SCENE = PRO_SCENE + 8; // ��������  ѡ���ɫ���ֱ�Ӹ��ݳ���ID������Ϸ 
	struct RqSwitchScene : public NetMsgSS
	{
		RqSwitchScene() :NetMsgSS(RQ_SWITCH_SCENE)
		{
			nSceneID = 0;
		}
		int32 nSceneID;

	};

	const int32 RQ_POSITION_MOVE = PRO_USER + 1;   // 
	struct RqPositionMove : public NetMsgSS
	{
		RqPositionMove() :NetMsgSS(RQ_POSITION_MOVE)
		{
			nNewX = nNewY = 0;
		}

		int32 nNewX; // �Ѿ��Ŵ�һ�ٱ���������ֱ��ʹ�ü��� 
		int32 nNewY; // �Ѿ��Ŵ�һ�ٱ���������ֱ��ʹ�ü��� 
	};

	/* ��Ʒģ�鿪ʼ */
	const int32 RQ_ITEM_MOVE_POSITION = PRO_ITEM + 1;// �ƶ�λ�� 
	struct RqItemMovePosition : public NetMsgSS
	{
		RqItemMovePosition() : NetMsgSS(RQ_ITEM_MOVE_POSITION)
		{
			nSrcPos = nDstPos = 0;
		}
		int32 nSrcPos;
		int32 nDstPos;
	};

	const int32 RQ_ITEM_USE_OBJECT = PRO_ITEM + 2; // ʹ����Ʒ 
	struct RqItemUseObject : public NetMsgSS
	{

		RqItemUseObject() :NetMsgSS(RQ_ITEM_USE_OBJECT)
		{

		}

		int32 nUniqueID;
		int32 nItemNum;
	};

	/* �̳�ģ�鿪ʼ */
	const int32 RQ_SHOPPING_BUY_ITME = PRO_SHOP + 1;	// �̳ǹ�����Ʒ 
	struct RqShoppingBuyItem : public NetMsgSS
	{
		RqShoppingBuyItem() : NetMsgSS(RQ_SHOPPING_BUY_ITME)
		{
			nShopID = nShopNum = 0;
		}
		int32 nShopID;
		int32 nShopNum;
	};

	const int32 RQ_SHOPPING_SELL_ITME = PRO_SHOP + 2;	// �̳�������Ʒ 
	struct RqShoppingSellItem : public NetMsgSS
	{

		RqShoppingSellItem() : NetMsgSS(RQ_SHOPPING_SELL_ITME)
		{
			nUniqueID = nItemNum = 0;
		}
		int32 nUniqueID;
		int32 nItemNum;
	};

	// ������������Ϣ 
	struct t_ChatBase
	{
		int64 uid;
		char name[MAX_NAMESIZE + 1];
		int16 level;
		int8 vip;
	};

	// ����
	const int32 RQ_CHAT_TO_CHANNEL = PRO_CHAT + 0;
	struct RqChatToChannel : public NetMsgSS
	{
		RqChatToChannel() :NetMsgSS(RQ_CHAT_TO_CHANNEL)
		{

		}

		int64 fromUID;
		int64 toChannelID;
		C::t_ChatBase fromBase;
		uint16 msgleg;
		char msgdata[0];

	};
	const int32 RQ_CHAT_TO_TEAM = PRO_CHAT + 1;
	struct RqChatToTeam : public NetMsgSS
	{
		RqChatToTeam() :NetMsgSS(RQ_CHAT_TO_TEAM)
		{

		}
		C::t_ChatBase msg;
	};

	const int32 RQ_CHAT_TO_DISCUSS = PRO_CHAT + 2;
	struct RqChatToDiscuss : public NetMsgSS
	{
		RqChatToDiscuss() :NetMsgSS(RQ_CHAT_TO_DISCUSS)
		{

		}
		C::t_ChatBase msg;
	};

	const int32 RQ_CHAT_TO_WORLD = PRO_CHAT + 3;
	struct RqChatToWorld : public NetMsgSS
	{
		RqChatToWorld() :NetMsgSS(RQ_CHAT_TO_WORLD)
		{

		}
		C::t_ChatBase msg;
	};

	struct ChatMsgInfo2
	{
		ChatMsgInfo2()
		{
			len = 0;
			memset(data, 0, sizeof(data));
		}
		uint16 len;
		char data[MAX_SOCKET_BUFFER];
	};

	// �������� 
	const int32	RT_CHATTOWORLD = PRO_CHAT + 4;
	struct RtChatToWorld : public NetMsgSS
	{

		RtChatToWorld() :NetMsgSS(RT_CHATTOWORLD)
		{

		}
		ChatMsgInfo2 msg;
	};



	const int32 RQ_RELATION_LIST = PRO_RELATION + 0;
	struct RqRelationList : public NetMsgSS
	{
		RqRelationList() :NetMsgSS(RQ_RELATION_LIST)
		{

		}
	};

	const int32 RQ_RELATION_ADD = PRO_RELATION + 1;
	struct RqRelationAdd : public NetMsgSS
	{
		RqRelationAdd() :NetMsgSS(RQ_RELATION_ADD)
		{
			memset(name, 0, sizeof(name));
			rel = 0;
		}
		char name[MAX_NAMESIZE + 1];
		int32 rel;
	};

	const int32 RQ_RELATION_REMOVE = PRO_RELATION + 2;
	struct RqRelationRemove : public NetMsgSS
	{
		RqRelationRemove() :NetMsgSS(RQ_RELATION_REMOVE)
		{
			uid = 0;
		}
		int64 uid;
	};

	//����һ���Ự(���Լ���ӽ���)
	const int32  RQ_REL_CREATE_SESS = PRO_RELATION + 3;
	struct RqRelCreateSess : public NetMsgSS
	{
		RqRelCreateSess() : NetMsgSS(RQ_REL_CREATE_SESS)
		{

		}
	};

	//���ͻỰ��Ƶ����
	const int32 RQ_ReL_SEND_MSG = PRO_RELATION + 4;
	struct RqRelSendMsg : public NetMsgSS
	{
		RqRelSendMsg() :NetMsgSS(RQ_ReL_SEND_MSG)
		{

		}
	};

	// ������ϵ��Ϣ 
	struct t_RelationData
	{
		int64 uid;
		char name[MAX_NAMESIZE + 1];
		int32 rel; // 0����δͬ��,1����,2İ����,3������
		int32 createtime;
		int32 dealreltime; // �ϴβ���ʱ��
	};

	// �����б�
	const int32 RT_RELATION_LIST = PRO_RELATION + 5;
	struct RtRelationList : public NetMsgSS
	{
		RtRelationList() :NetMsgSS(RT_RELATION_LIST)
		{
			count = 0;
		}
		int32 count;
		C::t_RelationData list[0];
	};

	// ������Ϣ���� 
	const int32 RT_RELATION_UPDATE = PRO_RELATION + 6;
	struct RtRelationUpdate : public NetMsgSS
	{
		RtRelationUpdate() :NetMsgSS(RT_RELATION_UPDATE)
		{

		}
		C::t_RelationData rel;
	};

	// ����ɾ��
	const int32 RT_RELATION_DELETE = PRO_RELATION + 7;
	struct RtRelationDelete : public NetMsgSS
	{
		RtRelationDelete() :NetMsgSS(RT_RELATION_DELETE)
		{
			uid = 0;
		}
		int64 uid;
	};

	//////////////////////////////��ɫģ��////////////////////////////////////////////

	// ���������� 
	const int32  RT_CHAR_MAIN_DATA = PRO_USER + 0;	// ��ɫ������ 
	struct RtCharMainData : public NetMsgSS
	{
		RtCharMainData() :NetMsgSS(RT_CHAR_MAIN_DATA)
		{

		}
		SceneUserAttr userVal;
		EntryPkValBase pkVal;
	};

	// Ǯ������ 
	const int32 RT_CHAR_MONEY_DATA = PRO_USER + 1;	// Ǯ������ 
	struct RtCharMoneyData : public NetMsgSS
	{
		RtCharMoneyData() :NetMsgSS(RT_CHAR_MONEY_DATA)
		{
			nGold = nSilver = nCopper = 0;
		}
		int32 nGold;
		int32 nSilver;
		int32 nCopper;
	};

	//////////////////////////////Ƶ��ģ��////////////////////////////////////////////
	const int32 RT_CHANNEL_JION = PRO_CHANNEL + 0;	/* ����Ƶ�� */
	struct RtChannelJion : public NetMsgSS
	{
		RtChannelJion() :NetMsgSS(RT_CHANNEL_JION)
		{
			channelID = 0;
			memset(name, 0, sizeof(name));
		}
		int32 channelID;
		char name[MAX_NAME_LENGTH];
	};

	const int32 RT_CHANNEL_LEAVE = PRO_CHANNEL + 1;	/* �뿪Ƶ�� */
	struct RtChannelLeave : public NetMsgSS
	{
		RtChannelLeave() :NetMsgSS(RT_CHANNEL_LEAVE)
		{
			channelID = 0;
			memset(name, 0, sizeof(name));
		}
		int32 channelID;
		char name[MAX_NAME_LENGTH];
	};

	//////////////////////////////װ��ģ��////////////////////////////////////////////

	// ���ŵ�װ������ 
	const int32 RT_EQUIP_MAIN_DATA = PRO_EQUIP + 0; // װ��������(���ϴ�)
	struct RtEquipMainData : public NetMsgSS
	{
		RtEquipMainData() :NetMsgSS(RT_EQUIP_MAIN_DATA)
		{

		}
	};

	//////////////////////////////����ģ��///////////////////////////////////////////////

	// ������Ʒ����
	struct t_ItemSlot
	{
		int32 nUniqueID; // ΨһID 
		int32 nItemID;

		// ������̬����
		uint8 nItemNum;		// ���� 
		uint8 nIndex;		// ����λ�� 0-99 
		uint8 nLock;		// �Ƿ����� 
	};

	// inventory
	// ���ڷ�������˵��ֻ��һ�������������������ϣ�
	// ���������� inventory
	const int32 RT_ITEM_MAIN_DATA = PRO_PACK + 0; // ���������� 
	struct RtUserPackages : public NetMsgSS
	{
		RtUserPackages() :NetMsgSS(RT_ITEM_MAIN_DATA)
		{
			nCount = 0;
		}
		int32 nCount;
		t_ItemSlot items[100]; // 12 + �����ϵ����� ������ֻ�ܷ���100�� 
	};

	const int32 RT_ITEM_UPDATE_DATA = PRO_PACK + 1; // ���ӻ���� 
	struct RtItemSlotUpdate : public NetMsgSS
	{
		RtItemSlotUpdate() :NetMsgSS(RT_ITEM_UPDATE_DATA)
		{
			nCount = 0;
		}
		int32 nCount;
		t_ItemSlot items[100]; // ������ֻ�ܷ���100�� 
	};

	const int32 RT_ITEM_DELTE_DATA = PRO_PACK + 2; // ɾ������װ��
	struct RtItemSlotDelete : public NetMsgSS
	{
		RtItemSlotDelete() :NetMsgSS(RT_ITEM_DELTE_DATA)
		{
			nCount = 0;
			memset(nUniqueIDs, 0, sizeof(nUniqueIDs));
		}
		int32 nCount;
		int32 nUniqueIDs[100];
	};

	//////////////////////////////����ģ��///////////////////////////////////////////////

	// ����������  
	const int32 RT_QUEST_MAIN_DATA = PRO_QUEST + 0; // ���������� 
	struct RtQuestMainData : public NetMsgSS
	{
		RtQuestMainData() :NetMsgSS(RT_QUEST_MAIN_DATA)
		{

		}

		struct QuestInfo
		{
			int32 nQuestID;
			int32 nResult0;
			int32 nResult1;
		};

		QuestInfo arrHadAccept[MAX_QUEST_LIST_COUNT];
		QuestInfo arrCanAccept[MAX_QUEST_LIST_COUNT];

	};

	///////////////////////////����ģ��///////////////////////////////////////////////

	// �鿴ĳ���ż�
	const int32 RQ_LOOK_MESSAGE = PRO_MESSAGE + 0;
	struct rqLookMessage : public NetMsgSS
	{
		rqLookMessage():NetMsgSS(RQ_LOOK_MESSAGE)
		{
			msgID = askPass = 0;
		}
		int64 msgID;	// �ż�ID
		int32 askPass;	// �ż�����0ʱ�����ǲ鿴�Ƿ��и��ż���>0�ǻ������
	};

	// �����ż���������
	const int32 RT_NEED_PASS_MESSAGE = PRO_MESSAGE + 1;
	struct rtNeedPassMessage : public NetMsgSS
	{
		rtNeedPassMessage(): NetMsgSS(RT_NEED_PASS_MESSAGE)
		{
			msgID = needPass = 0;
		}
		int64 msgID;
		int32 needPass;	 // ��Ҫָ��������ܲ鿴
	};

	// ����������Ϣ
	const int32 RT_CONNET_MESSAGE = PRO_MESSAGE + 2;
	struct rtConentMessage : public NetMsgSS
	{
		rtConentMessage():NetMsgSS(RT_CONNET_MESSAGE)
		{
			msgID = msgLen = 0;
		}
		int64 msgID;
		int16 msgLen;
		char msgData[0];
	};

	// �ż�����
	const int32 RQ_OPT_MESSAGE = PRO_MESSAGE + 3;
	struct rqOptMessage : public NetMsgSS
	{
		rqOptMessage() :NetMsgSS(RQ_OPT_MESSAGE)
		{
			msgID = pass = optType = 0;
		}
		int64 msgID;
		int32 pass;
		int8 optType; //0��,1ɾ��
	};

#pragma pack(pop)

};	//namespace

#endif
