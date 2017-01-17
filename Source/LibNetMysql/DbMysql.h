#ifndef __DB_DATABASE_H_
#define __DB_DATABASE_H_

#include "DbConfig.h"
#include "DbRequest.h"
#include "DbResult.h"

#include <time.h>
#include <queue>

const uint32 DB_MAX_DBACCESSTIME	= 10;
const uint32 DB_MAX_STRINGSIZE		= 256;

/*-------------------------------------------------------------------
 * @Brief : MYSQL���ݿ������
 * 
 * @Author:hzd 2012/04/03
 *------------------------------------------------------------------*/
class DbMysql : public IDbBase
{
public:
	DbMysql();
	~DbMysql();

	// ���������� 
	bool Open( const char* ip,uint16 port, const char* username,const char* passwd, const char* dbname,bool bSQLChk = true );
		
	// �ر����� 
	void Close();

	// �������ID 
	virtual uint32 ID();
	
	// �ͷ��Լ� 
	virtual	void Release();

	// ͬ��ִ��sql���ؽ�� 
	virtual MYSQL_RES* ResultSQL( const char* pszSQL );

	virtual int32 ExecSQL(const char* pszSQL, int length = 0);

	// ����ִ��sql�Ƽ� 
	virtual bool ExecSQLAsync(const char* pszSQL, DBQueryFunc* queryFun = NULL);

	// ����ִ��sql select�Ƽ� 
	virtual bool ExecSelectAsync(const char* tableName, const dbCol *column, const char *swhere = NULL, const char *order = NULL,DBQueryFunc* queryFun = NULL);
	virtual bool ExecInsertAsync(const char* tableName, const dbCol *column, const char *data, DBQueryFunc* queryFun = NULL);
	virtual bool ExecDeleteAsync(const char* tableName, const char *swhere = NULL, DBQueryFunc* queryFun = NULL);
	virtual bool ExecUpdateAsync(const char* tableName, const dbCol *column, const char *data, DBQueryFunc* queryFun = NULL);

	// ��ý���� 
	virtual IDbResult* GetAsyncResult();
	
	// ��������� 
	virtual uint32 GetRequestSize();

	// ��ý���� 
	virtual uint32 GetResultSize();

	void WsSQLReplaceStr(char *to,const char *from,unsigned long length);

	// ����������Ӷ��� 
	MYSQL* GetDBHandle();

	// �Ƿ������ 
	bool IsOpen();

	// �ַ�ת��
	void Escape(char* pOutSql,const char* pInSql);

	virtual void BinaryToString(const char* pBinaryData,char* o_strBinarayData,int nLen);

	virtual int32 ExecSelect(const char* tableName,const dbCol *column,const char *where,const char *order,unsigned char** data, unsigned int limit = 0, int32 limit_from = 0);
	virtual int32 ExecSelectLimit(const char* tableName,const dbCol *column,const char *where,const char *order, unsigned char* data, unsigned int limit = 1, int32 limit_from = 0);
	virtual int32 ExecInsert(const char *tableName,const dbCol *column,const char *data);
	virtual int32 ExecDelete(const char *tableName,const char *where);
	virtual int32 ExecUpdate(const char *tableName,const dbCol *column,const char *data,const char *where);

	unsigned int fullSelectDataByRow(MYSQL_ROW row,unsigned long* lengths,const dbCol* column,unsigned char* tmepData);

	/**
	* \brief �����ύ
	* \param handleID ���������Ӿ��
	* \return �ɹ�����true��ʧ�ܷ���false
	*/
	bool Commit();
	
	/**
	* \brief ����ع�
	* \param handleID ���������Ӿ��
	* \return �ɹ�����true��ʧ�ܷ���false
	*/
	bool Rollback();

	/*
		����SQL��� 
	*/
	virtual int FetchSelectSql(const char* tableName,const dbCol *column,const char *wheres,const char *order,int32 limit = 0,int32 limit_from = 0, bool UseBak = false);

private:

	// ���sql����Ƿ�Ϸ� 
	bool CheckSQL(const char* szSQL);

	// �������ݿ� 
	MYSQL* Connect(char* ip , char* user , char* passwd , char* dbname , uint16 port = MYSQL_PORT, char* dbsocket = NULL, int32 timeout = 1000 );

	// ���ݿ��߳�ִ�е�ѭ������ 
	virtual int32 OnThreadCreate();

	// ���ݿ��߳����ٺ��� 
	virtual int32 OnThreadDestroy();

	// ����sqlִ�к��� 
	virtual int32 OnThreadProcess();

private:

	uint32	m_nID;							// ���ݿ�����ID  
	MYSQL*	m_pMysql;						// ���ݿ����Ӷ��� 
	boost::mutex m_dbMutex;					// ��������� 
	boost::mutex m_queueMutex;				// ִ�ж����� 

	bool	m_bOpen;							// �Ƿ���� (һ�㲻���жϣ�����) 
	char	m_arrHost[DB_MAX_STRINGSIZE];		// ���ݿ�host 
	char	m_arrUser[DB_MAX_STRINGSIZE];		// ���ݿ�username 
	char	m_arrPasswd[DB_MAX_STRINGSIZE];		// ���ݿ�password 
	char	m_arrDBName[DB_MAX_STRINGSIZE];		// ���ݿ��� 
		
	std::queue<DbRequest*>	m_queAsyncSQLRequest;	// sql������� 
	std::queue<IDbResult*>	m_queAsyncSQLResult;	// sqlִ�н������ 

	friend class DbConnectsMgr;

};


#endif

