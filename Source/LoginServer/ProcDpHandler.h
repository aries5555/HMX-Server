#ifndef __PROC_DP_HANDLER_H_
#define __PROC_DP_HANDLER_H_

#include "BaseDefine.h"
#include "Single.h"

class zSession;
struct NetMsgSS;


class ProcDpHandler : public Single<ProcDpHandler>
{
public:
	ProcDpHandler(void);
	~ProcDpHandler(void);

	/*--------------------------------------------
	 *  @brief  : �ʺŵ�¼�ķ���
	 *  @input	: 
	 *  @return :	
	 *-------------------------------------------*/
	void AccountLogin(zSession* pSession, const NetMsgSS* pMsg,int32 nSize);

	/*--------------------------------------------
	 *  @brief  : ��ɫ���ݷ��أ�ֻ�е��ʺ�������ȷ
	 *  @input	: �Ż��з��أ�����ж���dp��
	 *  @return :	
	 *-------------------------------------------*/
	void CharacterList(zSession* pSession, const NetMsgSS* pMsg,int32 nSize);

	/*--------------------------------------------
	 *  @brief  : ������ɫ�������
	 *  @input	: 
	 *  @return :	
	 *-------------------------------------------*/
	void RoleCreateResult(zSession* pSession, const NetMsgSS* pMsg,int32 nSize);
};

#endif



