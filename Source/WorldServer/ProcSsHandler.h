#ifndef _SCENE_SERVER_MSG_HANDLER_H_
#define _SCENE_SERVER_MSG_HANDLER_H_

#include "Single.h"

class ProcSsHandler : public Single<ProcSsHandler>
{
public:
	ProcSsHandler();
	~ProcSsHandler();

	/*--------------------------------------------
	 *  @brief    :	���󳡾�ע�ᣬ��ss��¼ws��ɺ�����ע���������ڵĵ�ͼID
	 *  @input	  :
	 *  @return   :	
	 *-------------------------------------------*/
	void RqSceneRegister(zSession* pSession, const NetMsgSS* pMsg,int32 nSize);

	/*--------------------------------------------
	 *  @brief    :	���󳡾�ע��������ȡ��������ͼע��
	 *  @input	  :
	 *  @return   :	
	 *-------------------------------------------*/
	void RqSceneCancel(zSession* pSession, const NetMsgSS* pMsg,int32 nSize);

	/*--------------------------------------------
	 *  @brief  : ���볡���󷵻صĽ�� 
	 *  @input	: 
	 *  @return :	
	 *-------------------------------------------*/
	void RpEnterSceneResult(zSession* pSession, const NetMsgSS* pMsg,int32 nSize);

	void RpChangeScene(zSession* pSession, const NetMsgSS* pMsg, int32 nSize);

	/* ������Ϣת�� */
	void TurnChatToOne(zSession* pSession, const NetMsgSS* pMsg, int32 nSize);

	void NtBroadcastMsg(zSession* pSession, const NetMsgSS* pMsg, int32 nSize);

	void rqRelAdd(zSession* pSession, const NetMsgSS* pMsg, int32 nSize);
};

#endif


