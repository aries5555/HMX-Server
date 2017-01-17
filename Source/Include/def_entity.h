#ifndef __DEF_ENTITY_H_
#define __DEF_ENTITY_H_

#include "ServerDefine.h"
#include "srvEngine.h"

#pragma pack(push, 1)

// ʵ������ 
enum EntityType
{
	ENTITY_TYPE_NPC			= 1,
	ENTITY_TYPE_PLAYER		= 2,
	ENTITY_TYPE_MASTER		= 3,
	ENTITY_TYPE_TRANSFER	= 4,
};

#define MAX_SPELL_CONTROL_NUM 4

/*-------------------------------------------------------------------
* @Brief : PK�������Զ���
*
* @Author:hzd 2015:11:12
*------------------------------------------------------------------*/
////////////////////////////////////ս������������ start//////////////////////////////////////
struct EntryPkValBase
{
	int32 nStatus;							// ״̬(������λ����ֵ) 
	int32 nLevel;							// �ȼ� 
	int32 nRed;								// ��(Ѫ) 
	int32 nRedMax;							// ������ 
	int32 nBlue;							// ��(����) 
	int32 nBlueMax;							// ������ 
	int32 nRedRecover;						// ��ָ� 
	int32 nBlueRecover;						// ���ָ� 
	int32 nPhysicAttack;					// ������ 
	int32 nPhysicDefend;					// ������� 
	int32 nSpellAttack;						// �������� 
	int32 nSpellDefend;						// �������� 
	int32 nBaojilv;							// ������ 
	int32 nBaoji;							// ���� 
	int32 nGedanglv;						// ������ 
	int32 nGedang;							// ���� 
	int32 nShanbilv;						// ������ 
	int32 nMingzhonglv;						// ������ 
	int32 nAttackSpeed;						// �ٶ� 
	int32 nMoveSpeed;						// ���� 

	EntryPkValBase()
	{
		memset(this , 0, sizeof(*this));
	}

	EntryPkValBase(const EntryPkValBase& pkVal)
	{
		operator=(pkVal);
	}

	EntryPkValBase& operator=(const EntryPkValBase& pkVal)
	{
		memcpy(this, &pkVal, sizeof(*this));
		return *this;
	}

};




// ���������� 
/*-------------------------------------------------------------------
* @Brief : �������ԣ���ָ�ڵ�ͼ��ʹ�õģ����õģ�Ҳ���ǵ�ͼ�ϵ�PK���
*			�����ݣ����������Բ�ע��������
* @Author:hzd 2015:11:28
*------------------------------------------------------------------*/
enum EntiryBaseAttrType
{
	////////////////////////////////////Entry��������//////////////////////////////////////
	ENTITY_ATTRIBUTE_MAPID,
	ENTITY_ATTRIBUTE_POS_X,
	ENTITY_ATTRIBUTE_POS_Y,
	ENTITY_ATTRIBUTE_INVIEWRANGE,
	ENTITY_ATTRIBUTE_OUTVIEWRANGE,
	ENTITY_ATTRIBUTE_MAX,
};

struct BaseAttribute
{
	int32 nMapID;					// ��ͼID 
	zPos sPos;						// ���� 
	int32 nInViewRange;				// ������Ұ���� 
	int32 nOutViewRangle;			// �뿪��Ұ���� 
	BaseAttribute()
	{
		sPos.x = sPos.y = 0;
		nInViewRange = nOutViewRangle = 0;
	}
};

//////////////////////////////////////////////////////////////////////////

struct SpellData
{
	uint32 nSpellID;	// ����ID 
	int32 nPosition;    // Я��λ�� (-1δЯ��,0 - 4 Я���ڶ�Ӧ��λ����) 
};

enum CharacterType
{
	CHARACTER_TYPE_NULL		= 0,    // �Ƿ� 
	CHARACTER_TYPE_SHAOLIN	= 1,	// ���� 
	CHARACTER_TYPE_MOJIAO	= 2,	// ħ�� 
	CHARACTER_TYPE_GUMU		= 3,	// ��Ĺ 
	CHARACTER_TYPE_XIAOYAO	= 4,	// ��ң 
};

//////////////////////////////////��ɫ////////////////////////////////////////

// ��ɫר�еĻ������ݣ��󲿷������Ѿ��̳���PK��  
struct SceneUserAttr
{
	int64 nUid;						// UID
	char  arrName[MAX_NAME_LENGTH]; // ��ɫ�� 
	int32 nExp;						// ���� 
	int32 nExpMax;					// �������� 
	int32 nLandID;					// ��ͼID(����������ͼ) ����ʱ���ȼ�鸱����ͼ���ټ������ͼ 
	int32 nLandX;
	int32 nLandY;
	int32 nInstanceID;				// ����ID 
	int32 nInstanceX;
	int32 nInstanceY;
	int32 nRoleType;				// ��ɫ���� 
	int32 nClothesID;				// ����װ��ID 
	int32 nWeaponID;				// ����װ��ID 
	int32 nGold;
	int32 nSilver;
	int32 nCopper;
	int32 nLastLogin;
	int32 nCountry;
	int32 nSceneID;
	int32 nZoneID;
	int32 nTeamID;
	int32 nVip;
	SceneUserAttr()
	{

	}
	SceneUserAttr(const SceneUserAttr& pkVal)
	{
		operator=(pkVal);
	}

	SceneUserAttr& operator=(const SceneUserAttr& pkVal)
	{
		memcpy(this, &pkVal, sizeof(*this));
		return *this;
	}

	/*void Serialize(::protobuf::UserBinary& proto);
	void Unserialize(const ::protobuf::UserBinary& proto);*/

};

enum SceneUserAttrType
{
	USER_ATTR_UID = 0,
	USER_ATTR_EXP,
	USER_ATTR_EXPMAX,		
	USER_ATTR_LAND_ID,		
	USER_ATTR_LAND_X,
	USER_ATTR_LAND_Y,
	USER_ATTR_INSTANCE_ID,	
	USER_ATTR_INSTANCE_X,
	USER_ATTR_INSTANCE_Y,
	USER_ATTR_ROLETYPE,
	USER_ATTR_CLOTHESID,
	USER_ATTR_WEAPONID,

	USER_ATTR_GOLD,
	USER_ATTR_SILVER,
	USER_ATTR_COPPER,
	USER_ATTR_LASTLOGIN,
	USER_ATTR_COUNTRY,
	USER_ATTR_SCENEID,
	USER_ATTR_ZONEID,
	USER_ATTR_TEAMID,
	USER_ATTR_VIP,
	USER_ATTR_MAX
};


// �������� 
struct SceneUserItemSlot
{
	int32 nCapacity;
	int32 nUseCapacity;

};


//////////////////////////////////////////////////////////////////////////


// ��ɫ���ϴ�������װ�� 
struct CharacterWearData
{
	uint64 nCharacterID;	// ��ɫID  
	uint32 nClothesID;		// �·�ID 
	uint32 nWeaponID;		// ����ID 
};

#pragma pack(pop)

#endif

