#include "GameServer_PCH.h"
#include "SceneNpcAIController.h"
#include "srvEngine.h"
#include "ScenesServer.h"

const int SceneNpcAIController::npc_call_fellow_rate = 30;///NPC�ٻ�ͬ��ļ���
const int SceneNpcAIController::npc_one_checkpoint_time = 60;///NPC����·���ƶ�ʱ,��һ��·����ʱ��
const int SceneNpcAIController::npc_checkpoint_region = 2;///NPC�ƶ�,����һ��·����ж���Χ
const int SceneNpcAIController::npc_onhit_stop_time = 2;///����NPC�ƶ��б�����ʱ,ֹͣ��ʱ��
const int SceneNpcAIController::npc_flee_distance = 4;///NPC���빥���ߵľ���
const int SceneNpcAIController::npc_min_act_region = 5;///NPC���빥���ߵľ���

SceneNpcAIController::SceneNpcAIController(SceneNpc* sceneNpc) :npc(sceneNpc), curPhase(0), repeat(-1), active(false), reached(false)
{
	bzero(dstMap, sizeof(dstMap));
	//if (sn)
	//	strncpy(dstMap, sn->scene->name, MAX_NAMESIZE - 1);
	dstPos = zPos(0, 0);
	curAI.type = NPC_AI_NORMAL;
	phaseEndTime = 0;
}

/**
* \brief �������¼�,���л���Ӧ״̬
* �÷�����SceneNpc::action��ִ�У��������ֱ���ִ��SceneNpc::action 
*
*/
void SceneNpcAIController::processPhase()
{
	switch (curAI.type)
	{
	case NPC_AI_MOVETO:
	{
		if (arrived(curAI.pos))
		{
			setActRegion(curAI.pos, curAI.regionX, curAI.regionY);
			nextPhase();
		}
	}
	break;
	case NPC_AI_PATROL:
	{
		if (arrived(curAI.pos))
			nextPhase();
	}
	break;
	case NPC_AI_RETURN_TO_REGION:
	{
		if (arrived())
		{
			setAI(oldAI);
			//npc->resetSpeedRate();
		}
	}
	break;
	default:
		break;
	}
}

/**
* \brief ����npc��AI,���ý׶�ʱ��
*
* \param ai Ҫ���õ�AI���������û�������
* \param setTime �Ƿ�ͬʱ����ʱ��,Ĭ��Ϊ��
*/
void SceneNpcAIController::setAI(const t_NpcAIDefine ai, const bool setTime)
{
	oldAI = curAI;
	npc->setAI(ai);
	curAI = ai;
	if (setTime)
		setPhaseTime(ai.lasttime * 1000);

	switch (curAI.type)
	{
	case NPC_AI_ATTACK:
	{
		setActRegion(curAI.pos, curAI.regionX, curAI.regionY);
	}
	break;
	case NPC_AI_FLEE:
	{
		npc->randomChat(NPC_CHAT_ON_FLEE);
	}
	break;
	default:
		break;
	}
	//Zebra::logger->debug("setAI(): %s AI=%d",npc->name,ai.type);
}

/**
* \brief �ж�Npc�Ƿ��߳���������з�Χ֮��
* ���û���ڸ����û�״̬,��Ҫ��Χ��������
* ׷��ʱ��Χ����10
* \return �Ƿ񳬳����Χ
*/
bool SceneNpcAIController::outOfRegion() const
{
	//if (!(npc->canMove())) return false;
	//const zPos &pos = npc->getPos();
	////if (npc->getChaseMode() == SceneNpc::CHASE_NONE)
	//if (0 == npc->curTargetID)
	//	return !((pos.x >= actPos.x - actRegionX)
	//		&& (pos.x <= actPos.x + actRegionX)
	//		&& (pos.y >= actPos.y - actRegionY)
	//		&& (pos.y <= actPos.y + actRegionY));
	//else
	//	return !((pos.x >= actPos.x - (actRegionX + 10))
	//		&& (pos.x <= actPos.x + (actRegionX + 10))
	//		&& (pos.y >= actPos.y - (actRegionY + 10))
	//		&& (pos.y <= actPos.y + (actRegionY + 10)));
	return false;
}

/**
* \brief �ж�npc�Ƿ񵽴�ĳλ�õ�ĳ��Χ��
*
* \param pos ����λ��,Ĭ���ǵ�ǰAI��Ŀ��λ��
* \param regionX ��Χ��,Ĭ���ǵ�ǰAI�ķ�Χ��
* \param regionY ��Χ��,Ĭ���ǵ�ǰAI�ķ�Χ��
* \return �Ƿ��ڷ�Χ��
*/
bool SceneNpcAIController::arrived(zPos pos, int regionX, int regionY)
{
	if (pos == zPos(0, 0)) pos = curAI.pos;
	if (-1 == regionX) regionX = curAI.regionX;
	if (-1 == regionY) regionY = curAI.regionY;

	//zPos npcPos = npc->getPos();
	return (npc->getPos().x >= pos.x - regionX)
		&& (npc->getPos().x <= pos.x + regionX)
		&& (npc->getPos().y >= pos.y - regionY)
		&& (npc->getPos().y <= pos.y + regionY);
}

//�ص����Χ,׷�ٵ��˳�����Χʱ��5���ٷ���
/**
* \brief ���ûص���Χ��AIʹNPC�ص����Χ
* ���NPC�Ǹ��ٵ��˶������˻��Χ,����5���ٷ��ػ��Χ��,ͬʱ��������Ŀ��
*
*/
void SceneNpcAIController::returnToRegion()
{
	//t_NpcAIDefine def = curAI;
	//def.type = NPC_AI_RETURN_TO_REGION;
	//def.pos = actPos;
	//def.regionX = randBetween(2, actRegionX);
	//def.regionY = randBetween(2, actRegionY);
	//def.lasttime = 10;
	//setAI(def);
	////if (npc->getChaseMode() != SceneNpc::CHASE_NONE)
	//if (0 != npc->curTargetID)
	//{
	//	npc->randomChat(NPC_CHAT_ON_RETURN);
	//	npc->unChaseUser();
	//	npc->setSpeedRate(npc->getSpeedRate()*4.0);
	//}
	//Channel::sendNine(npc,"�ҵûص�(%d,%d)��Χ%d,%d����",curAI.pos.x,curAI.pos.y,def.regionX,def.regionY);
}

/**
* \brief �Ƿ񵽴�Ŀ�ĵ�
* Ŀ�ĵصĶ����ǽű������һ���ƶ���λ��
* ��ͼ��ͬ���㵽��
*
*/
bool SceneNpcAIController::dstReached()
{
	//if (strcmp(dstMap, npc->scene->name)) return false;

	//if (arrived(dstPos, npc_checkpoint_region, npc_checkpoint_region))
	//	return true;

	return false;
}

/**
* \brief ������һ�׶�
*
* \param index ����ָ��Ҫ����Ľ׶α��,-1��ʾ��һ�׶�
*/
void SceneNpcAIController::nextPhase(int index)
{
	/* //��������npcҲҪִ�нű�
	if (!active)
	{
	setNormalAI();
	return;
	}
	*/

	if (index>-1)
		curPhase = index;
	else
	{
		if (curPhase == phaseVector.size() - 1)
		{
			if (-2 == repeat)
			{
				curPhase = randBetween(0, phaseVector.size() - 1);
			}
			else if (-1 == repeat)
			{
				curPhase = 0;
			}
			else if (1 == repeat)
			{
				active = false;
				phaseVector.clear();
				repeat--;
				npc->on_reached();
				setNormalAI();
				return;
			}
			else if (repeat>1)
			{
				curPhase = 0;
				repeat--;
				//Channel::sendNine(npc,"repeat=%d",repeat);
			}
		}
		else
			curPhase++;
	}

	setPhaseTime(phaseVector[curPhase].lasttime*1000);

	if (phaseVector.size())
		setAI(phaseVector[curPhase]);
	//Channel::sendNine(npc,"����׶�%d",curPhase);
}


/**
* \brief ����npc��ͨAI
* ��ͨAIʱAIDefine��������������Ч
*/
void SceneNpcAIController::setNormalAI()
{
	curAI.type = NPC_AI_NORMAL;
	setAI(curAI);
}

/**
* \brief NPC���������¼�����
*
* \param pAtk ������
*/
void SceneNpcAIController::on_hit(SceneEntryPk *pAtk)
{

	npc->randomChat(NPC_CHAT_ON_HIT);

	//[sky] NPC��һ���ܵ���������AI��ʱ��
	if (!npc->m_bFighting)
	{
		npc->m_dwNowTime = GetTickCount();
		npc->m_mobType = false;
		npc->m_bFighting = true;
		npc->m_dwGtime = 0;
	}

	//npc->delayMoveTime(npc->npc->distance/2);//�����������ӳ�
	switch (npc->npc->kind)
	{
	case NPC_TYPE_HUMAN:      ///����
	case NPC_TYPE_NORMAL:      /// ��ͨ����
	case NPC_TYPE_BBOSS:      /// ��Boss����
	case NPC_TYPE_PBOSS:      /// ��Boss����
	case NPC_TYPE_LBOSS:      /// СBoss����
	case NPC_TYPE_BACKBONE:      /// ��Ӣ����
	case NPC_TYPE_GOLD:        /// �ƽ�����
	case NPC_TYPE_SUMMONS:      /// �ٻ�����
	case NPC_TYPE_AGGRANDIZEMENT:  /// ǿ������
	case NPC_TYPE_ABERRANCE:    /// ��������
	case NPC_TYPE_BACKBONEBUG:    /// ��������
	case NPC_TYPE_TURRET:			/// ����
	case NPC_TYPE_BARRACKS:
	case NPC_TYPE_CAMP:
	case NPC_TYPE_GHOST:			/// Ԫ��
	case NPC_TYPE_ANIMON:        /// ������
	{

	}
	break;
	case NPC_TYPE_GUARD:  /// ʿ������
	case NPC_TYPE_PET:  /// ��������
	case NPC_TYPE_TASK:    /// ��������
	case NPC_TYPE_TOTEM:      /// ͼ������
	case NPC_TYPE_TRADE:  /// ��������
		break;
	default:
		break;
	}
}

/**
* \brief ����NPC�Ļ��Χ
*
* \param pos ����λ��
* \param x,y ��Χ�Ŀ�͸�
* \return
*/
void SceneNpcAIController::setActRegion(zPos pos, int x, int y)
{
	if (pos == zPos(0, 0)) 
		pos = npc->getPos();
	npc->SetPosition(pos);
	actPos = pos;
	if (0 <= x) actRegionX = x >= npc_min_act_region ? x : npc_min_act_region;
	if (0 <= y) actRegionY = y >= npc_min_act_region ? y : npc_min_act_region;
	//Channel::sendNine(npc,"���Χ:(%d,%d) x=%d y=%d",actPos.x,actPos.y,actRegionX,actRegionY);
}

/**
* \brief ���øý׶εĽ���ʱ��
*
* \param delay �����ڿ�ʼ���ӳ�,����Ϊ��λ
*/
void SceneNpcAIController::setPhaseTime(const int delay)
{
	phaseEndTime = Zebra::timeTick->getMilliTime();
	phaseEndTime += delay;
}

/**
* \brief ���׶�ʱ���Ƿ����
*
* \return �Ƿ��˽׶ν���ʱ��
*/
bool SceneNpcAIController::phaseTimeOver()
{
	if (NPC_AI_NORMAL != curAI.type)
	{
		return Zebra::timeTick->getMilliTime() >= phaseEndTime;
	}
	else
		return false;
}

