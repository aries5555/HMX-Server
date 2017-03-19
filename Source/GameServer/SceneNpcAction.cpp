#include "SceneNpc.h"
#include "SceneNpcAIController.h"


bool SceneNpc::moveable(const zPos &tempPos, const zPos &destPos, const int radius)
{

	return true;
}

bool SceneNpc::move(const int direct, const int step)
{

	return true;
}

/**
* \brief ����NPC��AI
*
* \param ai Ҫ���õ�AI�ṹ������
*/
void SceneNpc::setAI(const t_NpcAIDefine &ai)
{
	aiDefine = ai;
}

void SceneNpc::action(int32 now)
{
	//AIC->processPhase();
}

bool SceneNpc::normalAction()
{
	switch (aiDefine.type)
	{
	case NPC_AI_NORMAL:
	{
		int ret = doNormalAI();
		return ret;
	}
	break;
	case NPC_AI_SAY:
	{
		return doSayAI();
	}
	break;
	case NPC_AI_MOVETO:
	{
		return doMovetoAI();
	}
	break;
	case NPC_AI_ATTACK:
	{
		return doAttackAI();
	}
	break;
	case NPC_AI_GO_ON_PATH:
	{
		return doGoOnPathAI();
	}
	break;
	case NPC_AI_PATROL:
	{
		return doPatrolAI();
	}
	break;
	case NPC_AI_FLEE:
	{
		return doFleeAI();
	}
	break;
	case NPC_AI_RETURN_TO_REGION:
	{
		return doReturnToRegionAI();
	}
	break;
	case NPC_AI_CHANGE_MAP:
	{
		return doChangeMapAI();
	}
	break;
	case NPC_AI_WARP:
	{
		return doWarpAI();
	}
	break;
	case NPC_AI_CLEAR:
	{
		return doClearAI();
	}
	break;
	case NPC_AI_DROP_ITEM:
	{
		return doDropItemAI();
	}
	break;
	case NPC_AI_RANDOM_CHAT:
	{
		return doRandomChatAI();
	}
	break;
	case NPC_AI_WAIT:
	{
		return true;
	}
	break;
	default:
	{
		return false;
	}
	break;
	}
	return true;
}


bool SceneNpc::doNormalAI()
{

	
	return true;
}

bool SceneNpc::doSayAI()
{
	return true;
}

bool SceneNpc::doRandomChatAI()
{
	return true;
}

bool SceneNpc::doMovetoAI()
{
	if (!AIC->phaseTimeOver())
	{
		if (checkMoveTime(H::timeTick->getMilliTime()) && canMove())
		{
			if (!gotoFindPath(getPos(), aiDefine.pos))//��Ŀ���ƶ�
				goTo(aiDefine.pos);//��һ�ַ�ʽ��Ŀ���ƶ�
			if (AIC)
				if (NPC_AI_PATROL == aiDefine.type)
					AIC->setActRegion(getPos(), 5, 5);
				else
					AIC->setActRegion(getPos());
		}
	}
	return true;
}

bool SceneNpc::doAttackAI()
{
	return true;
}

bool SceneNpc::doGoOnPathAI()
{
	return true;
}

bool SceneNpc::doPatrolAI()
{
	return true;
}

bool SceneNpc::doFleeAI()
{
	return true;
}

bool SceneNpc::doChangeMapAI()
{
	return true;
}

bool SceneNpc::doWarpAI()
{
	return true;
}

bool SceneNpc::doReturnToRegionAI()
{
	return true;
}

bool SceneNpc::doClearAI()
{
	return true;
}

bool SceneNpc::doDropItemAI()
{
	return true;
}

/**
* \brief �Ƿ�����ƶ�
*
* \return �Ƿ�����ƶ�
*/
bool SceneNpc::canMove()
{
	if (npc->kind == NPC_TYPE_TURRET ||
		npc->kind == NPC_TYPE_BARRACKS ||
		npc->kind == NPC_TYPE_CAMP)
		return false;

	return (!(aif&AIF_NO_MOVE)/* && moveAction*/);
}

bool SceneNpc::checkMoveTime(const int32 ct)
{

	return true;
}

void SceneNpc::setMoveTime(const int32 ct)
{

}

void SceneNpc::setMoveTime(const int32 ct, const int delay)
{

}

void SceneNpc::delayMoveTime(const int delay)
{

}

bool SceneNpc::checkAttackTime(const int32 ct) const
{
	return true;
}

void SceneNpc::setAttackTime(const int32 ct)
{

}

void SceneNpc::setAttackTime(const int32 ct, const int delay)
{

}

/**
* \brief npc���˵��
*
* \param type ˵��������
*/
void SceneNpc::randomChat(NpcChatType type)
{

}

/**
* \brief ˲���ƶ�
*
*
* \param newPos Ŀ��λ��
* \return �Ƿ�ɹ�
*/
bool SceneNpc::warp(const zPos &newPos, bool ignore)
{
	return true;
}

/**
* \brief ʹ�����ĳһ�����ƶ�
* ��Ѱ·�㷨���ƶ�,��������ֻ�Ƿ�װ��һ��,���ڲ�ͬ��npc������ͬ,��������ò�ͬ������A*�㷨
* \param srcPos �������
* \param destPos Ŀ�ĵ�����
* \return �ƶ��Ƿ�ɹ�
*/
bool SceneNpc::gotoFindPath(const zPos &srcPos, const zPos &destPos)
{
	return zAStar<>::gotoFindPath(srcPos, destPos);
}

/**
* \brief Npc��ĳһ�����ƶ�
* ����Ѱ·�㷨���ƶ�,��������ֻ�Ƿ�װ��һ��,���ڲ�ͬ��npc������ͬ,��������ò�ͬ������A*�㷨
* \param pos Ŀ�ĵ�����
* \return �ƶ��Ƿ�ɹ�
*/
bool SceneNpc::goTo(const zPos &pos)
{
	return zAStar<>::goTo(getPos(), pos);
}

/**
* \brief Npc�����ĳһ�������ƶ�
* ��������ֻ�Ƿ�װ��һ��,���ڲ�ͬ��npc������ͬ,��������ò�ͬ������A*�㷨
* \param direct �������
* \return �ƶ��Ƿ�ɹ�
*/
bool SceneNpc::shiftMove(const int direct)
{
	return zAStar<>::shiftMove(direct);
}



