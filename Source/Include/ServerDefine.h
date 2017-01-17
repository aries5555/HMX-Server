
#ifndef __PROTOCOL_DEFIEN_H_
#define __PROTOCOL_DEFIEN_H_

#include "BaseDefine.h"

#define SERVERKEY "key123"


/*
 * ͨ��ֵ���� 
 */
union ValueType
{
	ValueType()
	{
		memset(this, 0, sizeof(*this));
	}

	template<typename T>
	ValueType(T v)
	{
		if (!(sizeof(*this) < sizeof(T)))
		{
			memcpy(this, &v, sizeof(T));
		}
	}
	template<typename T>
	void operator+=(const T& v)
	{
		ValueType tmpType(v);
		nInt8 += tmpType.nInt8;
		nInt16 += tmpType.nInt16;
		nInt32 += tmpType.nInt32;
		nInt64 += tmpType.nInt64;
		nUint8 += tmpType.nUint8;
		nUint16 += tmpType.nUint16;
		nUint32 += tmpType.nUint32;
		nUint64 += tmpType.nUint64;
		fFloat += tmpType.fFloat;
	}

	int8	nInt8;
	int16	nInt16;
	int32	nInt32;
	int64	nInt64;
	uint8	nUint8;
	uint16	nUint16;
	uint32	nUint32;
	uint64	nUint64;
	float32	fFloat;
};


typedef boost::function<void(const ValueType& vOldValue, const ValueType& vNewValue)> AttributeHandler;

// ����ƫ�ƽṹ 
struct AttributeOffset
{
	void*				nOffset;				// ����λ�� 
	int32				nSize;					// ���Դ�С 
	bool				bCanSet;				// �Ƿ������ 
	AttributeHandler	hHandler;				// �����޸Ļص� 

	AttributeOffset()
	{
		nOffset = NULL;
		nSize = 0;
		bCanSet = false;
		hHandler = NULL;
	}

	bool CheckCanSet()
	{
		return nOffset != NULL && nSize != 0;
	}
};



typedef std::vector< std::string > StringVector;
typedef std::vector< std::string >::iterator StringIter;

typedef std::vector< int32 > IntVector;
typedef std::vector< int32 >::iterator IntIter;




// ���ݿ�� 
enum ETableType
{
	E_TABLE_NULL = 0 ,
	E_TABLE_USER,
	E_TABLE_QUEST,
};

#pragma pack(push,1)

// �����¼��ws��ͨ�����ݽṹ 
struct LoginData2Ws
{
	LoginData2Ws()
	{
	}
	char arrServerAddr[32]; // ��������ַ 
	int32 nServerPort;		// �˿� 
	int32 nServerID;		// ��������ʶID 
};

// ��������Ϣ 
struct t_ServerReg
{
	t_ServerReg()
	{
		id = 0;
	}

	int32 id;
};

typedef std::vector<t_ServerReg> ServerInfoDataVecType;


// Э��ŷ�Χ���� 

enum 
{
	// �ڲ�Э��server��server֮ǰ��ͨ��ͨ��Э�� 
	PRO_INTERNAL_BASE = 100,

	// �̶�ֵ(1)+����form+����to+��λ�Զ��� 
	PRO_C2F_BASE = 1010000,
	PRO_C2L_BASE = 1020000,
	PRO_C2W_BASE = 1030000,
	PRO_C2S_BASE = 1040000,
	
	PRO_F2C_BASE = 1100000,
	PRO_F2L_BASE = 1120000,
	PRO_F2W_BASE = 1130000,
	PRO_F2S_BASE = 1140000,

	PRO_L2C_BASE = 1200000,
	PRO_L2F_BASE = 1210000,
	PRO_L2W_BASE = 1230000,
	PRO_L2D_BASE = 1250000,

	PRO_W2C_BASE = 1300000,
	PRO_W2F_BASE = 1310000,
	PRO_W2L_BASE = 1320000,
	PRO_W2S_BASE = 1340000,
	PRO_W2D_BASE = 1350000,

	PRO_S2C_BASE = 1400000,
	PRO_S2F_BASE = 1410000,
	PRO_S2L_BASE = 1420000,
	PRO_S2W_BASE = 1430000,
	PRO_S2D_BASE = 1450000,

	PRO_D2L_BASE = 1520000,
	PRO_D2W_BASE = 1530000,
	PRO_D2S_BASE = 1540000,

};

// ��ɫ���� 
enum ERoleType
{
	E_ROLE_TYPE_NULL,
	E_ROLE_TYPE_1,
	E_ROLE_TYPE_2,
	E_ROLE_TYPE_3,
	E_ROLE_TYPE_4,
	E_ROLE_TYPE_MAX,
};


// ���볡����������
struct stEnterSceneParam
{
	int32 nSubIdx; // ��̬��ͼΨһID 
	int32 nPram1;
	int32 nPram2;
	stEnterSceneParam()
	{
		memset(this, 0, sizeof(*this));
	}
};



#pragma pack(pop)



/* ��ʱ���ö��� */ 
#define __INTERAVAL_ONE_SECOND__	(nSrvTime % 5 == 0)
#define __INTERAVAL_TWO_SECOND__	(nSrvTime % 10 == 0)
#define __INTERAVAL_THREE_SECOND__  (nSrvTime % 15 == 0)
#define __INTERAVAL_FOUR_SECOND__	(nSrvTime % 20 == 0)
#define __INTERAVAL_FIVE_SECOND__	(nSrvTime % 25 == 0)
#define __INTERAVAL_ONE_MINUTE__	(nSrvTime % 300 == 0)

/* �첽�¼�Ψһ��� */ 
enum SocketEventCode
{
	SOCKET_EVENT_CODE_SAVE_CHANGE_MAP = 1,
};

#define MAX_LOAD_ALL_UID 1000 

/* �䳤�ṹ���� */
#define BUFFER_MSG(msg,size) char buffmsg[65535]; \
memcpy(buffmsg, (const char*)(msg), (size));

enum EnterType
{
	ENTER_TYPE_ONLINE_FIRST = 0,	/* �״ν��� */
	ENTER_TYPE_SCENE_CHANGE,		/* ���ĳ��� */
	ENTER_TYPE_OFFLINE_SYNC,		/* ����ת�����߳��� */
	ENTER_TYPE_OFFLINE_LOAD,		/* �������ݼ��� */
};


#endif


