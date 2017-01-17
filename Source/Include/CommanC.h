#ifndef __COMMON_C2F_H_
#define __COMMON_C2F_H_

#include "ServerDefine.h"
#include "NetConfig.h"
#include "SrvEngine.h"

#pragma pack(push,1)

//////////////////////////////////////////////////////////////////////////

enum EProC2F
{

	PRO_C2F_ENCRYPT		= PRO_C2F_BASE + 0, // �����Կ 
	PRO_C2F_CLOSE		= PRO_C2F_BASE + 1, // �����˳� 
	
};



// ���ͼ������� 
struct C2FepEncryptInfo : public NetMsgSS
{
	C2FepEncryptInfo():NetMsgSS(PRO_C2F_ENCRYPT)
	{
	}
	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};

struct C2FepClose : public NetMsgSS
{
	C2FepClose():NetMsgSS(PRO_C2F_CLOSE)
	{
	}
	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};


//////////////////////////////////////////////////////////////////////////


enum EProC2L
{

	PRO_C2L_ACCOUNT_LOGIN	= PRO_C2L_BASE + 0, // �ʺŵ�¼ 
	PRO_C2L_RAND_NAMES		= PRO_C2L_BASE + 2, // �������� 


};

struct C2LAccountLogin : public NetMsgSS
{
	char username[32];
	char password[32];
	C2LAccountLogin():NetMsgSS(PRO_C2L_ACCOUNT_LOGIN)
	{
	}
	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};

struct C2LRandNames : public NetMsgSS
{
	C2LRandNames():NetMsgSS(PRO_C2L_RAND_NAMES)
	{

	}
	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};


//////////////////////////////////////////////////////////////////////////

enum EProC2SFunc
{
	PRO_C2S_SCENE_BASE = PRO_C2S_BASE + 0,		// ����ģ��  
	PRO_C2S_CHAR_BASE = PRO_C2S_BASE + 100,		// ����ģ��
	PRO_C2S_EQUIP_BASE = PRO_C2S_BASE + 200,	// װ��ģ��
	PRO_C2S_ITEM_BASE = PRO_C2S_BASE + 300,		// ����ģ�� 
	PRO_C2S_QUEST_BASE = PRO_C2F_BASE + 400,	// ����ģ�� 
	PRO_C2S_CHAT_BASE	= PRO_C2S_BASE + 500,	/* ����ģ�� */
	PRO_C2S_RELATION_BASE = PRO_C2S_BASE + 600, 
};

enum EProC2S
{

	//////////////////////////////����ģ��////////////////////////////////////////////
	PRO_C2S_SCENE_INIT_DATA = PRO_C2S_SCENE_BASE + 1,	// ���볡��������� 
	PRO_C2S_CHANGE_SCENE = PRO_C2S_SCENE_BASE + 2,	// �л�����

	//////////////////////////////����ģ��////////////////////////////////////////////
	PRO_C2S_POSITION_MOVE = PRO_C2S_CHAR_BASE + 100,   // 


	//////////////////////////////װ��ģ��////////////////////////////////////////////	

	//////////////////////////////����ģ��////////////////////////////////////////////
	PRO_C2S_ITEM_MOVE_POSITION = PRO_C2S_ITEM_BASE + 0, // �ƶ�λ�� 
	PRO_C2S_ITEM_UPDATE = PRO_C2S_ITEM_BASE + 1, // ������Ʒ���� 
	PRO_C2S_ITEM_USE_OBJECT = PRO_C2S_ITEM_BASE + 2, // ʹ����Ʒ 


	//////////////////////////////�̳�ģ��////////////////////////////////////////////
	PRO_C2S_SHOPPING_BUY_ITME = PRO_C2S_BASE + 500,	// �̳ǹ�����Ʒ 
	PRO_C2S_SHOPPING_SELL_ITME = PRO_C2S_BASE + 501,	// �̳�������Ʒ 

	///////////////////////////////����ģ��///////////////////////////////////////////
	PRO_C2S_CHAT_TO_CHANNEL = PRO_C2S_CHAT_BASE + 0,
	PRO_C2S_CHAT_TO_TEAM = PRO_C2S_CHAT_BASE + 1,
	PRO_C2S_CHAT_TO_DISCUSS = PRO_C2S_CHAT_BASE + 2,
	PRO_C2S_CHAT_TO_WORLD = PRO_C2S_CHAT_BASE + 3,

	/* ����ϵ */
	PRO_C2S_RELATION_LIST = PRO_C2S_RELATION_BASE + 0,
	PRO_C2S_RELATION_ADD = PRO_C2S_RELATION_BASE + 1,
	PRO_C2S_RELATION_REMOVE = PRO_C2S_RELATION_BASE + 2,


};

/*
 *	�������� 
 */
//struct C2SCharWorld : public NetMsgSS
//{
//	C2SCharWorld():NetMsgSS(0)
//	{
//		nLength = 0;
//	}
//	int32 nLength;
//	char arrMsg[MAX_CHAR_WORLD_MSG_LENGTH];
//	inline int32 GetPackLength()const
//	{
//		return sizeof(*this) - sizeof(arrMsg) + nLength;
//	}
//};

/*
 *	������س��������� 
 */
struct C2SClientIsReady : public NetMsgSS
{
	enum
	{
		E_DATA_TYPE_NULL		= 0x00000000,
		E_DATA_TYPE_CHARMAIN	= 0x00000001,
		E_DATA_TYPE_PACKAGE		= 0x00000002,
		E_DATA_TYPE_RELATION	= 0x00000004,
		E_DATA_TYPE_PET			= 0x00000008,
		E_DATA_TYPE_ALL			= 0x0fffffff,
	};
	
	int32 nLoadDataFlags; // ��Ҫ���ص����� 
		
	C2SClientIsReady():NetMsgSS(PRO_C2S_SCENE_INIT_DATA)
	{

	}
	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};

/*
 *	�л����� 
 */
struct C2SChanageScene : public NetMsgSS
{
	int32 nSceneID;
	C2SChanageScene() :NetMsgSS(PRO_C2S_CHANGE_SCENE)
	{
		nSceneID = 0;
	}

	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};

struct C2SPositionMove : public NetMsgSS
{
	int32 nNewX; // �Ѿ��Ŵ�һ�ٱ���������ֱ��ʹ�ü��� 
	int32 nNewY; // �Ѿ��Ŵ�һ�ٱ���������ֱ��ʹ�ü��� 
	C2SPositionMove() :NetMsgSS(PRO_C2S_POSITION_MOVE)
	{
		nNewX = nNewY = 0;
	}

	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};

/* ��Ʒģ�鿪ʼ */

struct C2SItemMovePosition : public NetMsgSS
{
	int32 nSrcPos;
	int32 nDstPos;
	C2SItemMovePosition() : NetMsgSS(PRO_C2S_ITEM_MOVE_POSITION)
	{
		nSrcPos = nDstPos = 0;
	}
	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};

struct C2SItemUseObject : public NetMsgSS
{
	int32 nUniqueID;
	int32 nItemNum;
	C2SItemUseObject() :NetMsgSS(PRO_C2S_ITEM_USE_OBJECT)
	{

	}
	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};

/* �̳�ģ�鿪ʼ */

struct C2SShoppingBuyItem : public NetMsgSS
{
	int32 nShopID;
	int32 nShopNum;
	C2SShoppingBuyItem() : NetMsgSS(PRO_C2S_SHOPPING_BUY_ITME)
	{
		nShopID = nShopNum = 0;
	}
	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};

struct C2SShoppingSellItem : public NetMsgSS
{
	int32 nUniqueID;
	int32 nItemNum;
	C2SShoppingSellItem() : NetMsgSS(PRO_C2S_SHOPPING_SELL_ITME)
	{
		nUniqueID = nItemNum = 0;
	}
	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
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
struct C2SChatToChannel : public NetMsgSS
{
	C2SChatToChannel() :NetMsgSS(PRO_C2S_CHAT_TO_CHANNEL)
	{
		
	}

	int64 fromUID;
	int64 toChannelID;
	t_ChatBase fromBase;
	uint16 msgleg;
	char msgdata[0];

};

struct C2SChatToTeam : public NetMsgSS
{
	C2SChatToTeam() :NetMsgSS(PRO_C2S_CHAT_TO_TEAM)
	{

	}
	t_ChatBase msg;
};

struct C2SChatToDiscuss : public NetMsgSS
{
	C2SChatToDiscuss() :NetMsgSS(PRO_C2S_CHAT_TO_DISCUSS)
	{

	}
	t_ChatBase msg;
};

struct C2SChatToWorld : public NetMsgSS
{
	C2SChatToWorld() :NetMsgSS(PRO_C2S_CHAT_TO_WORLD)
	{

	}
	t_ChatBase msg;
};

struct C2SRelationList : public NetMsgSS
{
	C2SRelationList() :NetMsgSS(PRO_C2S_RELATION_LIST)
	{

	}
};

struct C2SRelationAdd : public NetMsgSS
{
	C2SRelationAdd() :NetMsgSS(PRO_C2S_RELATION_ADD)
	{
		memset(name, 0, sizeof(name));
		rel = 0;
	}
	char name[MAX_NAME_LENGTH + 1];
	int32 rel;
};

struct C2SRelationRemove : public NetMsgSS 
{
	C2SRelationRemove() :NetMsgSS(PRO_C2S_RELATION_REMOVE)
	{
		uid = 0;
	}
	int64 uid;
};

//����һ���Ự(���Լ���ӽ���)
const BYTE PRO_C2S_REL_CREATE_SESS = PRO_C2S_RELATION_BASE + 3;
struct C2SRelCreateSess : public NetMsgSS
{
	C2SRelCreateSess() : NetMsgSS(PRO_C2S_REL_CREATE_SESS)
	{

	}
};

//���ͻỰ��Ƶ����
const BYTE PRO_C2S_ReL_SEND_MSG = PRO_C2S_RELATION_BASE + 4;
struct C2SRelSendMsg : public NetMsgSS
{
	C2SRelSendMsg() :NetMsgSS(PRO_C2S_ReL_SEND_MSG)
	{

	}
};

//////////////////////////////////////////////////////////////////////////

enum EProC2W
{

	PRO_C2W_SWITCH_SCENE = PRO_C2W_BASE + 0, // ��������  ѡ���ɫ���ֱ�Ӹ��ݳ���ID������Ϸ 
	PRO_C2W_SELECT_ROLE	 = PRO_C2W_BASE + 1, // ѡ���ɫ 
	PRO_C2W_CREATE_ROLE	 = PRO_C2W_BASE + 2, // ������ɫ 
	PRO_C2W_DELETE_ROLE  = PRO_C2W_BASE + 3, // ɾ����ɫ

};




// fep->ws->ss,��ssȷ�� 
struct C2WSwitchScene : public NetMsgSS
{
	C2WSwitchScene():NetMsgSS(PRO_C2W_SWITCH_SCENE)
	{
		nSceneID = 0;
	}
	int32 nSceneID;
	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};

struct C2WSelectRole : public NetMsgSS
{
	int64 uid;
	C2WSelectRole():NetMsgSS(PRO_C2W_SELECT_ROLE)
	{
		uid = 0; 
	}
	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};


struct C2WCreateRole : public NetMsgSS
{
	int64 accid;
	int8 roleType;
	char name[MAX_NAMESIZE + 1];
	char keymd5[MAX_NAMESIZE + 1];
	int32 keytime;

	C2WCreateRole():NetMsgSS(PRO_C2W_CREATE_ROLE)
	{
		accid = roleType = keytime = 0;
		memset(name, 0, sizeof(name));
		memset(keymd5, 0, sizeof(keymd5));
	}

	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};

struct C2WDeleteRole : public NetMsgSS
{
	int64 uid;
	int64 accid;
	char keymd5[MAX_NAMESIZE + 1];
	int32 keytime;
	C2WDeleteRole() :NetMsgSS(PRO_C2W_DELETE_ROLE)
	{
		uid =  accid = keytime = 0;
		memset(keymd5, 0, sizeof(keymd5));
	}

	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};

#pragma pack(pop)





#endif

#ifndef __COMMONS2C_H_
#define __COMMONS2C_H_

#include "ServerDefine.h"
#include "NetConfig.h"
#include "def_entity.h"

enum EProcS2CFunc
{
	PRO_S2C_SCENE_BASE = PRO_S2C_BASE + 0,		// ������� 
	PRO_S2C_CHAR_BASE = PRO_S2C_BASE + 100,	// �������  
	PRO_S2C_EQUIP_BASE = PRO_S2C_BASE + 200,	// װ�����
	PRO_S2C_ITEM_BASE = PRO_S2C_BASE + 300,	// �������
	PRO_S2C_QUEST_BASE = PRO_S2C_BASE + 400,	// ������� 
	PRO_S2C_CHANNEL_BASE = PRO_S2C_BASE + 500,	// Ƶ����� 
	PRO_S2C_RELATION_BASE = PRO_S2C_BASE + 600,	// ����ϵ

	PRO_S2C_MAX_BASE = PRO_S2C_BASE + 9999,	// ���ģ������99
};


// s2cЭ�� 
enum EProS2C
{

	//////////////////////////////����ģ��////////////////////////////////////////////
	PRO_S2C_SCENE_INIT_RESULT = PRO_S2C_SCENE_BASE + 0, // ������ʼ�� 
	PRO_S2C_CHAR_WORLD = PRO_S2C_SCENE_BASE + 1, // ss�ϵ��������� 
	PRO_S2C_SCENE_LOADING = PRO_S2C_SCENE_BASE + 2, // ���������� 
	PRO_S2C_SEND_DATA_FINISH = PRO_S2C_SCENE_BASE + 3, // ����������� 
	PRO_S2C_SCENE_LOAD_INFO = PRO_S2C_SCENE_BASE + 4, // ����ĳ�����Ϣ 

													  //////////////////////////////��ɫģ��////////////////////////////////////////////
													  PRO_S2C_CHAR_MAIN_DATA = PRO_S2C_CHAR_BASE + 0,	// ��ɫ������ 
													  PRO_S2C_CHAR_MONEY_DATA = PRO_S2C_CHAR_BASE + 1,	// Ǯ������ 

																										//////////////////////////////װ��ģ��////////////////////////////////////////////
																										PRO_S2C_EQUIP_MAIN_DATA = PRO_S2C_EQUIP_BASE + 0, // װ��������(���ϴ�)


																																						  //////////////////////////////����ģ��///////////////////////////////////////////////
																																						  PRO_S2C_QUEST_MAIN_DATA = PRO_S2C_QUEST_BASE + 0, // ���������� 


																																																			//////////////////////////////����ģ��///////////////////////////////////////////////
																																																			PRO_S2C_ITEM_MAIN_DATA = PRO_S2C_ITEM_BASE + 0, // ���������� 
																																																			PRO_S2C_ITEM_UPDATE_DATA = PRO_S2C_ITEM_BASE + 1, // ���ӻ���� 
																																																			PRO_S2C_ITEM_DELTE_DATA = PRO_S2C_ITEM_BASE + 2, // ɾ������װ��

																																																															 //////////////////////////////Ƶ��ģ��///////////////////////////////////////////////
																																																															 PRO_S2C_CHANNEL_JION = PRO_S2C_CHANNEL_BASE + 0,	/* ����Ƶ�� */
																																																															 PRO_S2C_CHANNEL_LEAVE = PRO_S2C_CHANNEL_BASE + 1,	/* �뿪Ƶ�� */

																																																																												//////////////////////////////����ϵģ��///////////////////////////////////////////////
																																																																												PRO_S2C_RELATION_LIST = PRO_S2C_RELATION_BASE + 0,  /* �����б� */
																																																																												PRO_S2C_RELATION_UPDATE = PRO_S2C_RELATION_BASE + 1,
																																																																												PRO_S2C_RELATION_DELETE = PRO_S2C_RELATION_BASE + 2,
};


#pragma pack(push, 1)


//////////////////////////////����ģ��////////////////////////////////////////////
struct S2CRepCharWorld : public NetMsgSS
{
	int64 fromUID;
	char fromName[MAX_NAME_LENGTH];

	int32 sayLen;
	char sayMsg[MAX_CHAR_WORLD_MSG_LENGTH];

	S2CRepCharWorld() :NetMsgSS(PRO_S2C_CHAR_WORLD)
	{
		fromUID = sayLen = 0;
		memset(fromName, 0, sizeof(fromName));
		memset(sayMsg, 0, sizeof(sayMsg));
	}
	inline int32 GetPackLength()const
	{
		return sizeof(*this) - sizeof(sayMsg) + sayLen;
	}
};

// ���볡���ĳ�ʼ����� 
struct S2CSceneInitResult : public NetMsgSS
{

	enum
	{
		SUCCESS = 0,
		FAIL
	};
	int32 nResult;

	S2CSceneInitResult() :NetMsgSS(PRO_S2C_SCENE_INIT_RESULT)
	{

	}
	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};

struct S2CSceneLoadInfo : public NetMsgSS
{
	int32 mapid;
	S2CSceneLoadInfo() :NetMsgSS(PRO_S2C_SCENE_LOAD_INFO)
	{
		mapid = 0;
	}
	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};

/*-------------------------------------------------------------------
* @Brief : �����ݷ������
*
* @Author:hzd 2015:11:24
*------------------------------------------------------------------*/
struct S2CSendDataFinish : public NetMsgSS
{

	// ��������һЩ���ֵ ������ʱ���  
	int32 nServerTime; // ������ʱ��
	int32 nMsgOrderID; // ��Ϣ˳��ֵ��������Ҽ�� 	
	S2CSendDataFinish() :NetMsgSS(PRO_S2C_SEND_DATA_FINISH)
	{
		nServerTime = nMsgOrderID = 0;
	}
	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};

//////////////////////////////��ɫģ��////////////////////////////////////////////

// ���������� 
struct S2CCharMainData : public NetMsgSS
{
	SceneUserAttr userVal;
	EntryPkValBase pkVal;
	S2CCharMainData() :NetMsgSS(PRO_S2C_CHAR_MAIN_DATA)
	{

	}
	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};

// Ǯ������ 
struct S2CCharMoneyData : public NetMsgSS
{
	int32 nGold;
	int32 nSilver;
	int32 nCopper;
	S2CCharMoneyData() :NetMsgSS(PRO_S2C_CHAR_MONEY_DATA)
	{
		nGold = nSilver = nCopper = 0;
	}
	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};

//////////////////////////////Ƶ��ģ��////////////////////////////////////////////
struct S2CChannelJion : public NetMsgSS
{
	int32 channelID;
	char name[MAX_NAME_LENGTH];
	S2CChannelJion() :NetMsgSS(PRO_S2C_CHANNEL_JION)
	{
		channelID = 0;
		memset(name, 0, sizeof(name));
	}
	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};

struct S2CChannelLeave : public NetMsgSS
{
	int32 channelID;
	char name[MAX_NAME_LENGTH];
	S2CChannelLeave() :NetMsgSS(PRO_S2C_CHANNEL_LEAVE)
	{
		channelID = 0;
		memset(name, 0, sizeof(name));
	}
	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};

//////////////////////////////װ��ģ��////////////////////////////////////////////

// ���ŵ�װ������ 
struct S2CEquipMainData : public NetMsgSS
{
	S2CEquipMainData() :NetMsgSS(PRO_S2C_EQUIP_MAIN_DATA)
	{

	}
	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};

//////////////////////////////����ģ��///////////////////////////////////////////////

// ������Ʒ����
struct stItemSlot
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
struct S2CUserPackages : public NetMsgSS
{
	int32 nCount;
	stItemSlot items[100]; // 12 + �����ϵ����� ������ֻ�ܷ���100�� 
	S2CUserPackages() :NetMsgSS(PRO_S2C_ITEM_MAIN_DATA)
	{
		nCount = 0;
	}
	inline int32 GetPackLength()const
	{
		return sizeof(*this) - sizeof(items) + nCount * sizeof(items[0]);
	}
};

struct S2CItemSlotUpdate : public NetMsgSS
{
	int32 nCount;
	stItemSlot items[100]; // ������ֻ�ܷ���100�� 
	S2CItemSlotUpdate() :NetMsgSS(PRO_S2C_ITEM_UPDATE_DATA)
	{
		nCount = 0;
	}
	inline int32 GetPackLength()const
	{
		return sizeof(*this) - sizeof(items) + nCount * sizeof(items[0]);
	}
};

struct S2CItemSlotDelete : public NetMsgSS
{
	int32 nCount;
	int32 nUniqueIDs[100];
	S2CItemSlotDelete() :NetMsgSS(PRO_S2C_ITEM_DELTE_DATA)
	{
		nCount = 0;
		memset(nUniqueIDs, 0, sizeof(nUniqueIDs));
	}
	inline int32 GetPackLength() const
	{
		return sizeof(*this) - sizeof(nUniqueIDs) + nCount * sizeof(nUniqueIDs[0]);
	}
};

//////////////////////////////����ģ��///////////////////////////////////////////////

// ����������  
struct S2CQuestMainData : public NetMsgSS
{

	struct QuestInfo
	{
		int32 nQuestID;
		int32 nResult0;
		int32 nResult1;
	};

	QuestInfo arrHadAccept[MAX_QUEST_LIST_COUNT];
	QuestInfo arrCanAccept[MAX_QUEST_LIST_COUNT];

	S2CQuestMainData() :NetMsgSS(PRO_S2C_QUEST_MAIN_DATA)
	{

	}
	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};



//////////////////////////////////////////////////////////////////////////


enum EProF2C
{

	PRO_F2C_ENCRYPT_INFO = PRO_F2C_BASE + 0,	// ������Կ��Ϣ 
	PRO_F2C_LOGIN_READY_FINISH = PRO_F2C_BASE + 1, // �������Լ�����¼����׼����� 
	PRO_F2C_ENTER_SCENE_LOADED = PRO_F2C_BASE + 2, // �����������  

};


// ������Կ 
struct F2CEncryptInfo : public NetMsgSS
{

	char encryptKey[MAX_ENCRYPTSIZE];

	F2CEncryptInfo() :NetMsgSS(PRO_F2C_ENCRYPT_INFO)
	{

	}
	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};

struct F2CLoginReadyFinish : public NetMsgSS
{
	F2CLoginReadyFinish() :NetMsgSS(PRO_F2C_LOGIN_READY_FINISH)
	{

	}
	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};

// ������� 
struct F2CEnterSceneLoaded : public NetMsgSS
{
	enum EEnterSceneResult
	{
		SUCCESS = 0,
		FAIL
	};

	int32 nResult;

	F2CEnterSceneLoaded() :NetMsgSS(PRO_F2C_ENTER_SCENE_LOADED)
	{

	}
	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};

//////////////////////////////////////////////////////////////////////////

enum EProL2C
{
	PRO_L2C_ACC_LOGIN = PRO_L2C_BASE + 0,	// ���ص�¼��Ϣ 
	PRO_L2C_CREATE_RES = PRO_L2C_BASE + 2, // ��ɫ������� 
	PRO_L2C_NAMES_LIST = PRO_L2C_BASE + 3, // �����б� 
};


struct L2CAccLogin : public NetMsgSS
{
	int64 accid;
	int32 result; //1�ɹ�,0ʧ��
	char keymd5[MAX_NAMESIZE + 1];
	int32 keytime;
	L2CAccLogin() :NetMsgSS(PRO_L2C_ACC_LOGIN)
	{
		accid = result = keytime = 0;
		memset(keymd5, 0, MAX_NAMESIZE);
	}
	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};

struct L2CRoleCreateRes : public NetMsgSS
{

	enum
	{
		E_SUCCESS = 0,
		E_FAIL_SYNC,
		E_FAIL_ROLE_MAX,
		E_FAIL_NAME_EXIST,
		E_FAIL_INSERT_FAIL,
	};

	int32 nResult;
	int64 nNewCharID;

	L2CRoleCreateRes() :NetMsgSS(PRO_L2C_CREATE_RES)
	{
		nResult = 0;
		nNewCharID = 0;
	}
	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};

struct L2CNamesList : public NetMsgSS
{
	int32 nCount;
	char arrNames[10][32];
	L2CNamesList() :NetMsgSS(PRO_L2C_NAMES_LIST)
	{
		nCount = 0;
		memset(arrNames, 0, 10 * 32);
	}
	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};

// ������ϵ��Ϣ 
struct t_RelData
{
	int64 uid;
	char name[MAX_NAMESIZE + 1];
	int32 rel; // 0����δͬ��,1����,2İ����,3������
	int32 createtime;
	int32 dealreltime; // �ϴβ���ʱ��
};

// �����б�
struct S2CRelationList : public NetMsgSS
{
	S2CRelationList() :NetMsgSS(PRO_S2C_RELATION_LIST)
	{
		count = 0;
	}
	int32 count;
	t_RelData list[0];
};

// ������Ϣ���� 
struct S2CRelationUpdate : public NetMsgSS
{
	S2CRelationUpdate() :NetMsgSS(PRO_S2C_RELATION_UPDATE)
	{

	}
	t_RelData rel;
};

// ����ɾ��
struct S2CRelationDelete : public NetMsgSS
{
	S2CRelationDelete() :NetMsgSS(PRO_S2C_RELATION_DELETE)
	{
		uid = 0;
	}
	int64 uid;
};

#pragma pack(pop)

#endif

#ifndef __COMMON_W2C_H_
#define __COMMON_W2C_H_


#include "ServerDefine.h"
#include "NetConfig.h"
#include "SrvEngine.h"
#include "csCommon.h"


//---------------------------------------

enum EProWS2C
{
	PRO_W2C_CHATTOWORLD = PRO_W2C_BASE + 0, // �������� 
	PRO_W2C_USERLIST = PRO_W2C_BASE + 1,	// ��ɫ�б�
	PRO_W2C_CREATE_RET = PRO_W2C_BASE + 2,	// �������
};

#pragma pack(push,1)




struct W2CUserList : public NetMsgSS
{
	W2CUserList() :NetMsgSS(PRO_W2C_USERLIST)
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

	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};


struct ChatMsgInfo2
{
	uint16 len;
	char data[MAX_SOCKET_BUFFER];
	ChatMsgInfo2()
	{
		len = 0;
		memset(data, 0, sizeof(data));
	}
	inline int32 GetLength() const
	{
		return sizeof(*this) - sizeof(data) + len;
	}
};

struct WS2CChatToWorld : public NetMsgSS
{

	WS2CChatToWorld() :NetMsgSS(PRO_W2C_CHATTOWORLD)
	{

	}

	ChatMsgInfo2 msg;

	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};

struct W2CCreateRet : public NetMsgSS
{
	W2CCreateRet() :NetMsgSS(PRO_W2C_CREATE_RET)
	{
		reasoin = newid = 0;
	}
	int8 reasoin;
	int64 newid;
	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};

#pragma pack(pop)


#endif
