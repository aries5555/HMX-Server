#ifndef __DB_CONFIG_H_
#define __DB_CONFIG_H_

#include <map>
#include <set>
#include <vector>
#include <string>
#include <memory.h>


#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/container/set.hpp>
#include <boost/thread/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>


#include <mysql.h>


#ifdef WIN32
#define SSleep(ms) Sleep(ms)
#else
#define SSleep(ms) usleep(ms)
#endif

#ifndef S_SAFE_DELETE
#define S_SAFE_DELETE(x) { if (NULL != x) { delete (x); (x) = NULL; } }
#endif

#ifndef S_SAFE_DELETE_VEC
#define S_SAFE_DELETE_VEC(x) { if (NULL != x) { delete [] (x); (x) = NULL; } }
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

enum EDbMode
{
	E_DB_MODE_NONE = 0,
	E_DB_MODE_READ,
	E_DB_MODE_EDIT
};

const int32	DB_MAX_SQL = 50000;

#define MAX_SQL_BUFFER 1024

#define MAX_SELECT_BUFFER 1000000


/*-------------------------------------------------------------------
 * @Brief : �����ֶ���Ϣ 
 * 
 * @Author:hzd 2015:12:28
 *------------------------------------------------------------------*/
class IDbData
{
public:
		
	virtual	void Release() = 0;
	virtual char* GetValue() = 0;
	virtual uint32 GetLen() const = 0;
	virtual uint32 GetType() const = 0;

	virtual operator char() const = 0;
	virtual operator uchar() const = 0;
	virtual operator int16() const = 0;
	virtual operator uint16() const = 0;
	virtual operator int32() const = 0;
	virtual operator uint32() const = 0;
	virtual operator int64() const = 0;
	virtual operator uint64() const = 0;
	virtual operator float32() const = 0;
	virtual operator float64() const = 0;
	virtual operator char*() const = 0;
	virtual operator const char*() const = 0;
		
	virtual IDbData& operator = ( char chOp ) = 0;
	virtual IDbData& operator = ( uchar chOp ) = 0;
	virtual IDbData& operator = ( int16 nOp ) = 0;
	virtual IDbData& operator = ( uint16 unOp ) = 0;
	virtual IDbData& operator = ( int32 iOp ) = 0;
	virtual IDbData& operator = ( uint32 uOp ) = 0;
	virtual IDbData& operator = ( int64 uOp ) = 0;
	virtual IDbData& operator = ( uint64 uOp ) = 0;
	virtual IDbData& operator = ( float32 fltOp ) = 0;
	virtual IDbData& operator = ( float64 dblOp ) = 0;
	virtual IDbData& operator = ( const char* szVal ) = 0;
};

/*-------------------------------------------------------------------
 * @Brief : �м�¼������ 
 * 
 * @Author:hzd 2015:12:28
 *------------------------------------------------------------------*/
class IDbRecord
{
public:
		
	virtual	void Release() = 0;
	virtual IDbData& Field( uint32 idx ) = 0;
	virtual IDbData& Field( uint32 idx ) const = 0;
	virtual IDbData& Field( const char* pszName ) = 0;
	virtual IDbData& Field( const char* pszName ) const = 0;
	virtual uint32 GetFieldCount() = 0;
	virtual IDbData& Key() = 0;
	virtual	void* GetRowBuff() = 0;
	virtual uint32 GetRecordSize() = 0;
};

/*-------------------------------------------------------------------
 * @Brief : ���л������� 
 * 
 * @Author:hzd 2015:12:28
 *------------------------------------------------------------------*/
class IDbRecordSet
{
public:	
	virtual bool Create(MYSQL_RES* pRES) = 0;
	virtual	void Release() = 0;
	virtual IDbRecord* GetRecord() const = 0;
	virtual void* GetRecordData(uint32 nIndex) const = 0;
	virtual int32 Rows() const = 0;
	virtual void Move(uint32 index) = 0;
};

// �ص����� 
enum EResultHandlerType 
{
	ECALLBACK_NULL			= 0,	// �Ƿ����� 
	ECALLBACK_DB_NULL		= 1,	// ִ�����ݺ�����ص� 
	ECALLBACK_DB_HANDLER	= 2,	// ���ݽ���ص�����ѯ�����أ� 
};

// ���ݿ�ص� 
struct DBQueryFunc
{
	virtual void QueryResult(IDbRecordSet* pSet,int32 nCount)
	{
	}
};

/*-------------------------------------------------------------------
 * @Brief : ��������ص���(�첽�������õ�)
 * 
 * @Author:hzd 2015:12:28
 *------------------------------------------------------------------*/
class IDbResult
{
public:
	virtual void Release() = 0;
	virtual IDbResult& operator=(IDbResult* pResult) = 0;
	virtual void DBCallRead() = 0;
	virtual IDbRecordSet* GetRecordSet() = 0;
};

typedef struct
{
	const char *name;	/**< �ֶ����� */
	int32 type;			/**< ZEBRA�������� */
	int32 size;			/**< ���ݴ�С */
} dbCol;

enum
{
	DB_BYTE,    /**< BYTE���� 1�ֽڳ��� */
	DB_CHAR,    /**< CHAR���� 1�ֽڳ��� */
	DB_WORD,    /**< WORD���� 2�ֽڳ��� */
	DB_DWORD,    /**< DWORD���� 4�ֽڳ��� */
	DB_FLOAT,	 /**< DB_FLOAT���� 4�ֽڳ��� */
	DB_QWORD,    /**< QWORD���� 8�ֽڳ��� */
	DB_STR,      /**< �ַ������� */
	DB_BIN,      /**< �������������� */
	DB_ZIP,      /**< zipѹ���������� */
	DB_BIN2,    /**< ��չ�������������� ���struct �ṹ�Ķ������ֶ�ǰ���һ��DWORD size�ֶ�,mysql �ֶ�����Ϊblob , ������֧�֣��䳤�޷����÷Ż��� */
	DB_ZIP2      /**< ��չzipѹ���������� */
};

typedef struct StBinData{
	uint32 len;
	char pData[5000];
} BDATA;

typedef std::vector<BDATA> BINDDATA;
typedef std::vector<BDATA>::iterator BINDDATAIT;

/*-------------------------------------------------------------------
 * @Brief : ���ݿ�������� 
 * 
 * @Author:hzd 2015:12:28
 *------------------------------------------------------------------*/
class IDbBase
{
public:

	// ���ýӿ� 
	virtual uint32 ID() = 0;
	virtual	void Release() = 0;
	virtual void BinaryToString(const char* pBinaryData,char* o_strBinarayData,int nLen) = 0;
	virtual void Escape(char* pOutSql,const char* pInSql) = 0;
	virtual MYSQL_RES* ResultSQL(const char* pszSQL ) = 0;
	virtual int32 ExecSQL(const char* pszSQL,int length = 0 ) = 0;

	// ���ڻ��δȷ���������������У��ö�άָ��char����ȡ {{[0...]},{[1...]},...},**data Ϊexecselect�ڲ������ڴ�
	virtual int32 ExecSelect(const char *tableName,const dbCol *column,const char *where,const char *order,unsigned char** data, unsigned int limit = 0, int32 limit_from =0) = 0;

	// ���ڻ�ö�����structȷ��Limit�����ݣ���һάָ��char����ȡ {[0][1][2]...},*data ΪexecselectΪ�ⲿ�������ڴ沢��֤�㹻�� 
	// Ҳ�������ڻ��һ���䳤��struct���ⲿ�����㹻�䳤���ڴ�(������ջ�ڴ�) 
	virtual int32 ExecSelectLimit(const char* tableName, const dbCol *column, const char *where, const char *order, unsigned char* data, unsigned int limit = 1, int32 limit_from =0) = 0;
	virtual int32 ExecInsert(const char *tableName,const dbCol *column,const char *data) = 0;
	virtual int32 ExecDelete(const char *tableName,const char *where) =0;
	virtual int32 ExecUpdate(const char *tableName,const dbCol *column,const char *data,const char *where) =0;

	// �첽�ӿ� 
	virtual uint32 GetRequestSize() = 0;
	virtual uint32 GetResultSize() = 0;
	virtual IDbResult* GetAsyncResult() = 0;
	virtual bool ExecSQLAsync(const char* pszSQL, DBQueryFunc* pCallBack ) =0 ;
	virtual bool ExecSelectAsync(const char* tableName, const dbCol *column, const char *where = NULL, const char *order = NULL, DBQueryFunc* queryFun = NULL) = 0;
	virtual bool ExecInsertAsync(const char* tableName, const dbCol *column, const char *data, DBQueryFunc* queryFun = NULL) = 0;
	virtual bool ExecDeleteAsync(const char* tableName, const char *where = NULL, DBQueryFunc* queryFun = NULL) = 0;
	virtual bool ExecUpdateAsync(const char* tableName, const dbCol *column, const char *data, DBQueryFunc* queryFun = NULL) = 0;

	// ����SQL��� 
	virtual int FetchSelectSql(const char* tableName, const dbCol *column, const char *where, const char *order, int32 limit = 0, int32 limit_from = 0, bool UseBak = false) = 0;

};
extern "C" IDbBase*	DatabaseCreate( const char* szDBServer , const char* szLoginName , const char* szPassword , const char* szDBName , bool bEnableSQLChk = true ); 


#endif
	
	
