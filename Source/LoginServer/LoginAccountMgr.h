#ifndef __LOGIN_ACCOUNT_MGR_H_
#define __LOGIN_ACCOUNT_MGR_H_

#include "BaseDefine.h"
#include "Single.h"
#include "ServerDefine.h"

#include "Utility.h"


/*------------------------------------------------------------------
 *
 * @Brief : �ʺŵ�¼������ʱʧЧ���������²�������
 *
 * @Author: hzd 
 * @File  : LoginAccountMgr.h
 * @Date  : 2015/10/19 23:21
 * @Copyright (c) 2015,hzd, All rights reserved.
 *-----------------------------------------------------------------*/

/*------------------------------------------------
 *  �ʺ���Ϣ
 *-----------------------------------------------*/
struct StAccountInfo
{

	int32 nSessionID;
	int32 nAccountId;
	char  arrName[MAX_ACCOUNT_LENG];
	int32 nLastLogin;
	int32 nIllegalTime;

	StAccountInfo(int32 _nSessionID)
	{
		nSessionID = _nSessionID;
		nAccountId = nLastLogin = nIllegalTime = 0;
	}

	/*--------------------------------------------
	 *  @brief    :	��¼��¼
	 *  @input	  :
	 *  @return   :	
	 *-------------------------------------------*/
	void AddLoginTimes()
	{
		int32 now = Zebra::timeTick->getNowTime();
		if(now - nLastLogin < 1) // С��1���صǶ������ڷǷ� 
		{
			nIllegalTime++;
		}
	}

	/*--------------------------------------------
	 *  @brief    :	�Ƿ�Ƿ�
	 *  @input	  :
	 *  @return   :	
	 *-------------------------------------------*/
	bool CheckLoginIllegal()
	{
		if( nIllegalTime > 3 )
		{
			nIllegalTime = 0;
			return true;
		}
		return false;
	}
};


class LoginAccountMgr : public Single<LoginAccountMgr>
{
public:

	LoginAccountMgr(void);
	~LoginAccountMgr(void);

	/*--------------------------------------------
	 *  @brief    :	�������
	 *  @input	  :
	 *  @return   :	
	 *-------------------------------------------*/
	void Update(int32 nServerTimes);

	/*--------------------------------------------
	 *  @brief    :	����ʺ���Ϣ
	 *  @input	  :
	 *  @return   :	
	 *-------------------------------------------*/
	StAccountInfo* GetAccountInfo(int32 nFepSessionId);

	/*--------------------------------------------
	 *  @brief    :	�����ʺż�¼
	 *  @input	  :
	 *  @return   :	
	 *-------------------------------------------*/
	StAccountInfo* AddAccountInfo(int32 nFepSessionId);

	/*--------------------------------------------
	 *  @brief    :	ɾ��һ���ʺż�¼
	 *  @input	  :
	 *  @return   :	
	 *-------------------------------------------*/
	void RemoveAccountInfo(int32 nFepSessionId);

private:

	typedef std::map<int32,StAccountInfo*> AccountInfoMapType;


	AccountInfoMapType m_mapAccountInfo;

	static ObjPool<StAccountInfo> s_cAccountInfoFactory;

};

#endif



