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

	void doPlayerExit(zSession* pSession, const NetMsgSS* pMsg, int32 nSize);
	void doChatWorld(zSession* pSession, const NetMsgSS* pMsg,int32 nSize);
	void doClientIsReady(zSession* pSession, const NetMsgSS* pMsg,int32 nSize);
	void doChangeScene(zSession* pSession, const NetMsgSS* pMsg, int32 nSize);
	void doItemMovePosition(zSession* pSession, const NetMsgSS* pMsg, int32 nSize);

	// 
	void doQuestAccept(zSession* pSession, const NetMsgSS* pMsg,int32 nSize);
	
	// �ƶ� 
	void doPositionMove(zSession* pSession, const NetMsgSS* pMsg, int32 nSize);

	void doShoppingBuyItem(zSession* pSession, const NetMsgSS* pMsg, int32 nSize);

	void doShoppingSellItem(zSession* pSession, const NetMsgSS* pMsg, int32 nSize);

	void doUseItem(zSession* pSession, const NetMsgSS* pMsg, int32 nSize);

	// Ƶ��
	void doChanneCmd(zSession* pSession, const NetMsgSS* pMsg, int32 nSize);


	/* ���� */
	void doChatToOne(zSession* pSession, const NetMsgSS* pMsg, int32 nSize);

	/* Ⱥ�� */
	void doChatToTeam(zSession* pSession, const NetMsgSS* pMsg, int32 nSize);

	/* ������ */
	void doChatToDiscuss(zSession* pSession, const NetMsgSS* pMsg, int32 nSize);

	/* ������ */
	void doChatToWorld(zSession* pSession, const NetMsgSS* pMsg, int32 nSize);

	// ����ϵ
	void doRelationList(zSession* pSession, const NetMsgSS* pMsg, int32 nSize);
	void doRelationAdd(zSession* pSession, const NetMsgSS* pMsg, int32 nSize);
	void doRelationRemove(zSession* pSession, const NetMsgSS* pMsg, int32 nSize);
};


#endif




