#ifndef __CREATURE_CONTROLLER_H_
#define __CREATURE_CONTROLLER_H_

#include "SceneNpc.h"
#include "srvEngine.h"
#include "ScenesServer.h"

/**
* \brief AI������
* ���������Զ�ȡNPC�ű�,ʹNPC���սű�������
*
* ��������������¼�,ʱ�䡢��������������
* ���ݲ�ͬ������ΪNPC���ò�ͬ��AI
*
*/
class SceneNpcAIController
{
public:
	static const int npc_call_fellow_rate;///NPC�ٻ�ͬ��ļ���
	static const int npc_one_checkpoint_time;///NPC����·���ƶ�ʱ,��һ��·����ʱ��
	static const int npc_checkpoint_region;///NPC�ƶ�,����һ��·����ж���Χ
	static const int npc_onhit_stop_time;///����NPC�ƶ��б�����ʱ,ֹͣ��ʱ��
	static const int npc_flee_distance;///NPC���빥���ߵľ���
	static const int npc_min_act_region;///NPC��С���Χ

	///�����������Ƶ�npc
	SceneNpc * npc;
										///AI����,AI�����������е�˳������ִ��
	std::vector<t_NpcAIDefine> phaseVector;
	///��ǰ��AI����
	DWORD curPhase;
	///��ǰAI�Ľ���ʱ��
	int64 phaseEndTime;

	///�ű��ظ�����
	///-1������ѭ��  0��ֹͣ  >0��ѭ������
	int repeat;

	///�Ƿ������˽ű�
	bool active;
	void nextPhase(int index = -1);
	void on_phaseEnd();
	SceneNpcAIType parseAction(char *);


	///��ǰ��AI�ͱ����ǰһ��AI
	t_NpcAIDefine curAI;
	t_NpcAIDefine oldAI;
	///���Χ������
	zPos actPos;
	///���Χ�Ŀ�͸�
	int actRegionX, actRegionY;
	bool outOfRegion() const;
	void returnToRegion();

	bool arrived(zPos pos = zPos(0, 0), int x = -1, int y = -1);
	bool dstReached();
	///�Ƿ񵽴�Ŀ�ĵ�
	bool reached;

	///Ŀ�ĵ�ͼ
	char dstMap[32];
	///Ŀ��λ��
	zPos dstPos;

public:
	SceneNpcAIController(SceneNpc *);
	void setAI(const t_NpcAIDefine ai, const bool setTime = true);
	void switchAI(const bool setTime = true);
	void setNormalAI();
	void setActRegion(zPos pos = zPos(0, 0), int x = -1, int y = -1);
	void getActRegion(zPos &, int &, int  &);
	bool loadScript(DWORD id);
	void unloadScript();
	void processPhase();
	void setRepeat(int repeat);
	int getRepeat();
	bool isActive();
	void setPhaseTime(const int delay);
	void delayPhaseTime(const int delay);
	bool phaseTimeOver();

	void on_relive();
	void on_find_enemy(const SceneEntryPk *);
	void on_hit(SceneEntryPk *pAtk);
	void on_die();

};

#endif

