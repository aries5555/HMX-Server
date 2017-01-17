#ifndef __DB_REQUEST_H_
#define __DB_REQUEST_H_

#include "DbConfig.h"

/*-------------------------------------------------------------------
 * @Brief : ���ݿ�������
 * 
 * @Author:hzd 2016/04/03
 *------------------------------------------------------------------*/
class DbRequest
{
public:

	DbRequest();
	~DbRequest();

public:
	char			m_arrSql[DB_MAX_SQL];
	void*			m_pData;
	DBQueryFunc*	m_queryFunc;
};

#endif


