#ifndef __BASE_PROC_HANDLER_H_
#define __BASE_PROC_HANDLER_H_


/*
 *
 *	Detail: �߼�������
 *   
 * Copyright (c) Created by hzd 2015-5-8.All rights reserved
 *
 */

#include "BaseDefine.h"
#include "Single.h"

#include "NetConfig.h"

class BaseProcHandler
{
public:

	bool CheckLogin(zSession& pBaseSession, const LoginData2Ws& pLoginData,int32 int32) 
	{
		// �����¼ 
		//if(pBaseSession.Status() != E_CLIENT_STATUS_CONNECTED)
		//{
//			FLOG_INFO("pBaseSession->Status() != EPLAYER_STATUS_CONNECTED");
		//	return false;
	//	}

		// ������Ҫ�����鹤������ֹ��ҵ����� 

		return true;
	}
};











#endif

