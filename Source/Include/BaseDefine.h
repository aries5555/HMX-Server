#ifndef _BASE_DEFINE_H_
#define _BASE_DEFINE_H_
#define _CRT_SECURE_NO_DEPRECATE

#include <stdio.h>
#include <assert.h>
#include <map>
#include <set>
#include <list>
#include <queue>
#include <vector>
#include <string>
#include <sstream>
#include <memory>
#include <utility>
#include <functional>

#ifdef WIN32
#include <WinSock2.h>
#include <ws2tcpip.h>
#include <mstcpip.h>
#include <mswsock.h>
#include <Windows.h>
#else
#include <stdint.h>
#endif

#ifdef WIN32
typedef __int64                     int64;
#else
typedef int64_t                     int64;
#endif
typedef unsigned long long          uint64;
typedef wchar_t						wchar;
typedef unsigned char				uchar;
typedef char						int8;
typedef unsigned char				uint8;
typedef short						int16;
typedef unsigned short				uint16;
typedef int							int32;
typedef unsigned int				uint32;
typedef float						float32;
typedef double						float64;


typedef int64 UID;

#include <boost/timer.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/foreach.hpp>
#include <boost/function.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/container/set.hpp>
#include <boost/thread/thread.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/typeof/std/utility.hpp>


#define S_SAFE_DELETE(a) if( a ){ delete a;a=NULL; }
#define S_SAFE_RELEASE(a) if( a ){ a->Release(); }

#define S_USE_PRINT
#define STRCMP strcmp
#define STRCPY strcpy
#define SPRINTF sprintf
#define RAND rand
#define ATOF atof
#define ATOI atoi
#define ATOL atol

#ifdef ASSERT
#undef ASSERT
#endif 
#define ASSERT assert

#ifdef WIN32
#define SSleep(ms) Sleep(ms)
#else
#define SSleep(ms) usleep(ms)
#endif

#define INSERT_FLAG(value, query_flags)	{(value) |= (query_flags);}
#define REMOVE_FLAG(value, query_flags)	{(value) &= ~(query_flags);}
#define HAS_FLAG(value, query_flags)	( ((value) & (query_flags)) != 0 ? true : false )
//
//	��־λ���� 
//
#define INSERT_FLAG(value, query_flags)	{(value) |= (query_flags);}
#define REMOVE_FLAG(value, query_flags)	{(value) &= ~(query_flags);}
#define HAS_FLAG(value, query_flags)		( ((value) & (query_flags)) != 0 ? true : false )

// 64λ���� 
#define MAKE_PAIR64(l, h)  uint64( uint32(l) | ( uint64(h) << 32 ) )
#define PAIR64_HIPART(x)   (uint32)((uint64(x) >> 32) & 0x00000000FFFFFFFFLL)
#define PAIR64_LOPART(x)   (uint32)(uint64(x)         & 0x00000000FFFFFFFFLL)
#define MAKE_MAPSCENEID(mapid,sceneid)  MAKE_PAIR64(mapid, sceneid)
#define MAKE_FLATZONEID(flatid,zoneid)	MAKE_PAIR64(flatid, zoneid)
#define MAKE_FZMSID(msid,fzid)			MAKE_PAIR64(msid,fzid)

// 32λ���� 
#define MAKE_PAIR32(l, h)  uint32( uint16(l) | ( uint32(h) << 16 ) )
#define PAIR32_HIPART(x)   (uint16)((uint32(x) >> 16) & 0x0000FFFF)
#define PAIR32_LOPART(x)   (uint16)(uint32(x)         & 0x0000FFFF)
			//��־ǰ׺ 
#define  __PRINT_MSG__ __FUNCTION__ << " " << __FILE__ << ":" << __LINE__ 

#ifdef _MSC_VER
#	define SERVER_DECL __declspec(dllexport)
#	define SCRIPT_DECL __declspec(dllimport)
#	define TWP_DLL_EXPORT extern "C" __declspec(dllexport)
#	define TWP_DLL_DECL __declspec(dllexport)
#else
#	define SERVER_DECL
#	define SCRIPT_DECL
#	define TWP_DLL_EXPORT extern "C"
#endif

#define SERVERKEY "key123"


#pragma pack(push,1)


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


//typedef boost::function<void(const ValueType& vOldValue, const ValueType& vNewValue)> AttributeHandler;

// ����ƫ�ƽṹ 
//struct AttributeOffset
//{
//	void*				nOffset;				// ����λ�� 
//	int32				nSize;					// ���Դ�С 
//	bool				bCanSet;				// �Ƿ������ 
//	AttributeHandler	hHandler;				// �����޸Ļص� 
//
//	AttributeOffset()
//	{
//		nOffset = NULL;
//		nSize = 0;
//		bCanSet = false;
//		hHandler = NULL;
//	}
//
//	bool CheckCanSet()
//	{
//		return nOffset != NULL && nSize != 0;
//	}
//};

typedef std::vector< std::string > StringVector;
typedef std::vector< std::string >::iterator StringIter;

typedef std::vector< int32 > IntVector;
typedef std::vector< int32 >::iterator IntIter;

// ���ݿ�� 
enum ETableType
{
	E_TABLE_NULL = 0,
	E_TABLE_USER,
	E_TABLE_QUEST,
};

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
	PRO_C2S = 100000,
	PRO_S2S = 200000,
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


/* ��ʱ���ö��� */
#define __INTERAVAL_ONE_SECOND__	(nSrvTime % 5 == 0)
#define __INTERAVAL_TWO_SECOND__	(nSrvTime % 10 == 0)
#define __INTERAVAL_THREE_SECOND__  (nSrvTime % 15 == 0)
#define __INTERAVAL_FOUR_SECOND__	(nSrvTime % 20 == 0)
#define __INTERAVAL_FIVE_SECOND__	(nSrvTime % 25 == 0)
#define __INTERAVAL_ONE_MINUTE__	(nSrvTime % 300 == 0)

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

#pragma pack(pop)


#endif







