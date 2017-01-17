#ifndef _PROC_CLIENT_HANDLER_H_
#define _PROC_CLIENT_HANDLER_H_

#include "BaseDefine.h"
#include "Single.h"

class zSession;
struct NetMsgSS;


class ProcFepHandler : public Single<ProcFepHandler>
{
public:
	ProcFepHandler(void);
	~ProcFepHandler(void);

	void RqPlayerExit(zSession* pSession, const NetMsgSS* pMsg, int32 nSize);
	void ReqChatWorld(zSession* pSession, const NetMsgSS* pMsg,int32 nSize);
	void RqClientIsReady(zSession* pSession, const NetMsgSS* pMsg,int32 nSize);
	void ReqChangeScene(zSession* pSession, const NetMsgSS* pMsg, int32 nSize);
	void ReqItemMovePosition(zSession* pSession, const NetMsgSS* pMsg, int32 nSize);

	// 
	void ReqQuestAccept(zSession* pSession, const NetMsgSS* pMsg,int32 nSize);
	
	// �ƶ� 
	void ReqPositionMove(zSession* pSession, const NetMsgSS* pMsg, int32 nSize);

	void ReqShoppingBuyItem(zSession* pSession, const NetMsgSS* pMsg, int32 nSize);

	void ReqShoppingSellItem(zSession* pSession, const NetMsgSS* pMsg, int32 nSize);

	void ReqUseItem(zSession* pSession, const NetMsgSS* pMsg, int32 nSize);

	// Ƶ��
	void rqChanneCmd(zSession* pSession, const NetMsgSS* pMsg, int32 nSize);


	/* ���� */
	void RqChatToOne(zSession* pSession, const NetMsgSS* pMsg, int32 nSize);

	/* Ⱥ�� */
	void RqChatToTeam(zSession* pSession, const NetMsgSS* pMsg, int32 nSize);

	/* ������ */
	void RqChatToDiscuss(zSession* pSession, const NetMsgSS* pMsg, int32 nSize);

	/* ������ */
	void RqChatToWorld(zSession* pSession, const NetMsgSS* pMsg, int32 nSize);

	// ����ϵ
	void rqRelationList(zSession* pSession, const NetMsgSS* pMsg, int32 nSize);
	void rqRelationAdd(zSession* pSession, const NetMsgSS* pMsg, int32 nSize);
	void rqRelationRemove(zSession* pSession, const NetMsgSS* pMsg, int32 nSize);
};


#endif




