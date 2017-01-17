#ifndef __PROC_SERVER_HANDLER_H_
#define __PROC_SERVER_HANDLER_H_

#include "BaseDefine.h"
#include "BaseSingle.h"
#include "../DyNetMysql/DbRecordSet.h"

class BaseSession;
struct NetMsgSS;

/*
 *	ҵ���߼� 
 */
class ProcServerHandler : public BaseSingle<ProcServerHandler> 
{
public:
	ProcServerHandler(void);
	~ProcServerHandler(void);

	//  ����Server������־��¼ 
	void ReqSaveToDb(BaseSession* pBaseSession, const NetMsgSS* pMsg,int32 nSize);

	
};


#endif

