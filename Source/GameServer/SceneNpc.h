#ifndef __CREATURE_H_
#define __CREATURE_H_

#include "SceneEntryPk.h"
#include "UnorderedSet.h"
#include "Single.h"
#include "srvEngine.h"
#include "ScenesServer.h"

class SceneNpcAIController;
struct Buff;

class SceneNpc : public SceneEntryPk, public zAStar<1>
{
public:
	SceneNpc(zNpcB* npc, const t_NpcDefine* define, const SceneEntryType entrytype);

private:

	//////////////////////////////AI//////////////////////////////////////
public:

	/**
	* \brief Ѱ·�������ж��м���Ƿ�ɴ�Ŀ�ĵ�
	* \param tempPos Ѱ·���̵��м��
	* \param destPos Ŀ�ĵ�����
	* \param radius Ѱ·��Χ��������Χ����ΪĿ�ĵز��ɴ�
	* \return �����Ƿ�ɵ���Ŀ�ĵ�
	*/
	virtual bool moveable(const zPos &tempPos, const zPos &destPos, const int radius = 12);

	/**
	* \brief �����ĳһ�������ƶ�
	* \param direct ����
	* \param step ��ʾ����
	* \return �ƶ��Ƿ�ɹ�
	*/
	virtual bool move(const int direct, const int step = 1);

	void setAI(const t_NpcAIDefine &ad);
	// ���� 
	void action(int32 now);
	virtual bool normalAction();
	//---
	virtual bool doNormalAI();
	virtual bool doSayAI();
	virtual bool doRandomChatAI();
	virtual bool doMovetoAI();
	virtual bool doAttackAI();
	virtual bool doGoOnPathAI();
	virtual bool doPatrolAI();
	virtual bool doFleeAI();
	virtual bool doChangeMapAI();
	virtual bool doWarpAI();
	virtual bool doReturnToRegionAI();
	virtual bool doClearAI();
	virtual bool doDropItemAI();

	virtual bool canMove();

	bool checkMoveTime(const int32 ct);
	void setMoveTime(const int32 ct);
	void setMoveTime(const int32 ct, const int delay);
	void delayMoveTime(const int delay);
	bool checkAttackTime(const int32 ct) const;
	void setAttackTime(const int32 ct);
	void setAttackTime(const int32 ct, const int delay);

	void randomChat(NpcChatType type);

	bool warp(const zPos &pos, bool ignore = false);//��ת
	void jumpTo(zPos &newPos) {};
	bool gotoFindPath(const zPos &srcPos, const zPos &destPos);
	bool goTo(const zPos &pos);
	bool shiftMove(const int direct);
	
	virtual void on_reached() { }//�ص��� 

public:

	// npcai������ 
	SceneNpcAIController* AIC;

	// Npc��������
	const t_NpcDefine* define;

	// npc��ǰ��AI
	t_NpcAIDefine aiDefine;

	// npcAI��־
	int32 aif;

	// Npc��������
	zNpcB *npc;

	// ��һ���ƶ�ʱ��
	int32 nextMoveTime;

	// ��һ�ι���ʱ��
	int32 nextAttackTime;

	bool	m_bFighting;		//NPC�Ƿ���ս���еı�־
	int32	m_dwNowTime;		
	int32	m_dwGtime;			//��¼ս��������ʱ��(�뼶)
	bool	m_mobType;			//�ٻ������־

};



#endif
