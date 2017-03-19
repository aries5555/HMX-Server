/**
 * \brief ���弼��״̬������ͷ�ļ�
 *
 */

#include "ScenesServer.h"
#include "SceneEntryPk.h"
#include "SceneUser.h"
#include "SceneUserMgr.h"

/**
 * \brief  ״̬0 ��״̬,�����κβ���
 * \param pEntry ״̬������
 * \param sse ����״̬
 * \return ����״̬����ֵ,�μ�ͷ�ļ��еļ���״̬������ֵö��
 */
BYTE SkillStatus_0(SceneEntryPk *pEntry,SkillStatusElement &sse)
{
  sse.byGoodnessType = SKILL_GOOD;
  sse.byMutexType = 0;
  return SKILL_RETURN;
}

/**
 * \brief  ״̬1 ��״̬�������˺����ӹ̶���ֵ
 * \param pEntry ״̬������
 * \param sse ����״̬
 * \return ����״̬����ֵ,�μ�ͷ�ļ��еļ���״̬������ֵö��
 */
BYTE SkillStatus_1(SceneEntryPk *pEntry,SkillStatusElement &sse)
{
  sse.byGoodnessType = SKILL_BAD;
  sse.byMutexType = 1;

  switch(sse.byStep)
  {
    case ACTION_STEP_DOPASS:
    case ACTION_STEP_START:
    case ACTION_STEP_RELOAD:
      {
        if (selectByPercent((int)(sse.percent)))
        {
//          pEntry->skillValue.dvalue += sse.value;
          //pEntry->pkValue.dvalue += sse.value;
          return SKILL_ACTIVE;
        }
        else
          return SKILL_RETURN;
      }
      break;
    case ACTION_STEP_TIMER:
      {
//        pEntry->skillValue.dvalue += sse.value;
       // pEntry->pkValue.dvalue += sse.value;
        return SKILL_RETURN;
      }
      break;
    case ACTION_STEP_STOP:
    case ACTION_STEP_CLEAR:
      {
      }
      break;
    default:
      break;
  }

  return SKILL_RETURN;
}

/**
 * \brief  ״̬2 ��״̬�������˺����Ӱٷֱ�,��׼��ֵΪ��ɫ��������װ�����������ܺ�
 * \param pEntry ״̬������
 * \param sse ����״̬
 * \return ����״̬����ֵ,�μ�ͷ�ļ��еļ���״̬������ֵö��
 */
BYTE SkillStatus_2(SceneEntryPk *pEntry,SkillStatusElement &sse)
{
  sse.byGoodnessType = SKILL_BAD;
  sse.byMutexType = 1;

  switch(sse.byStep)
  {
    case ACTION_STEP_DOPASS:
    case ACTION_STEP_START:
    case ACTION_STEP_RELOAD:
      {
        if (selectByPercent((int)(sse.percent)))
        {
         /* pEntry->skillValue.dvaluep = sse.value;
          pEntry->pkValue.dvaluep = sse.value;*/
          return SKILL_ACTIVE;
        }
        else
          return SKILL_RETURN;
      }
      break;
    case ACTION_STEP_TIMER:
      {
        /*pEntry->skillValue.dvaluep = sse.value;
        pEntry->pkValue.dvaluep = sse.value;*/
        return SKILL_RETURN;
      }
      break;
    case ACTION_STEP_STOP:
    case ACTION_STEP_CLEAR:
      {
      }
      break;
    default:
      break;
  }

  return SKILL_RETURN;
}

/**
 * \brief  ״̬3 ���ܵ���������[��״̬�����Ѿ�������]
 * \param pEntry ״̬������
 * \param sse ����״̬
 * \return ����״̬����ֵ,�μ�ͷ�ļ��еļ���״̬������ֵö��
 */
BYTE SkillStatus_3(SceneEntryPk *pEntry,SkillStatusElement &sse)
{
  sse.byGoodnessType = SKILL_GOOD;
  sse.byMutexType = 2;
 // pEntry->reSendData = true;

  switch(sse.byStep)
  {
    case ACTION_STEP_DOPASS:
    case ACTION_STEP_START:
    case ACTION_STEP_RELOAD:
      {
        if (selectByPercent((int)(sse.percent)))
        {
//          pEntry->skillValue.pdam = sse.value;
         // pEntry->pkValue.pdamage = sse.value;
          return SKILL_RECOVERY;
        }
        else
          return SKILL_RETURN;
      }
      break;
    case ACTION_STEP_TIMER:
      {
//        pEntry->skillValue.pdam += sse.value;
       // pEntry->pkValue.pdamage = sse.value;
        return SKILL_RETURN;
      }
      break;
    case ACTION_STEP_STOP:
    case ACTION_STEP_CLEAR:
      {
      }
      break;
    default:
      break;
  }

  return SKILL_RETURN;
}

/**
 * \brief  ״̬4 ָ��״̬�����ߵ������������ֵ[�����ϲ��������ּ������Դ�״̬����Ҳ�Ѿ�������]
 * \param pEntry ״̬������
 * \param sse ����״̬
 * \return ����״̬����ֵ,�μ�ͷ�ļ��еļ���״̬������ֵö��
 */
BYTE SkillStatus_4(SceneEntryPk *pEntry,SkillStatusElement &sse)
{
  sse.byGoodnessType = SKILL_GOOD;
  sse.byMutexType = 3;
 // pEntry->reSendData = true;

  switch(sse.byStep)
  {
    case ACTION_STEP_DOPASS:
    case ACTION_STEP_START:
    case ACTION_STEP_RELOAD:
      {
        if (selectByPercent((int)(sse.percent)))
        {
//          pEntry->skillValue.pdef = sse.value;
       //   pEntry->pkValue.pdefence = sse.value;
          return SKILL_RECOVERY;
        }
        else
          return SKILL_RETURN;
      }
      break;
    case ACTION_STEP_TIMER:
      {
       // pEntry->pkValue.pdefence = sse.value;
        return SKILL_RETURN;
      }
      break;
    case ACTION_STEP_STOP:
    case ACTION_STEP_CLEAR:
      {
      }
      break;
    default:
      break;
  }

  return SKILL_RETURN;
}

/**
 * \brief  ״̬5 ��ʾ״̬������������������,װ���������������ܺ�
 * \param pEntry ״̬������
 * \param sse ����״̬
 * \return ����״̬����ֵ,�μ�ͷ�ļ��еļ���״̬������ֵö��
 */
BYTE SkillStatus_5(SceneEntryPk *pEntry,SkillStatusElement &sse)
{
  sse.byGoodnessType = SKILL_GOOD;
  sse.byMutexType = 10;
//  pEntry->reSendData = true;

  switch(sse.byStep)
  {
    case ACTION_STEP_DOPASS:
    case ACTION_STEP_START:
    case ACTION_STEP_RELOAD:
      {
        if (selectByPercent((int)(sse.percent)))
        {
//          pEntry->skillValue.mdam = sse.value;
       //   pEntry->pkValue.mdamage = sse.value;
          return SKILL_RECOVERY;
        }
        else
          return SKILL_RETURN;
      }
      break;
    case ACTION_STEP_TIMER:
      {
       // pEntry->pkValue.mdamage = sse.value;
        return SKILL_RETURN;
      }
      break;
    case ACTION_STEP_STOP:
    case ACTION_STEP_CLEAR:
      {
      }
      break;
    default:
      break;
  }

  return SKILL_RETURN;
}

/**
 * \brief  ״̬6 ��ʾ״̬������������������,װ���������������ܺ�
 * \param pEntry ״̬������
 * \param sse ����״̬
 * \return ����״̬����ֵ,�μ�ͷ�ļ��еļ���״̬������ֵö��
 */
BYTE SkillStatus_6(SceneEntryPk *pEntry,SkillStatusElement &sse)
{
  sse.byGoodnessType = SKILL_GOOD;
  sse.byMutexType = 11;
  //pEntry->reSendData = true;

  switch(sse.byStep)
  {
    case ACTION_STEP_DOPASS:
    case ACTION_STEP_START:
    case ACTION_STEP_RELOAD:
      {
        if (selectByPercent((int)(sse.percent)))
        {
          //pEntry->skillValue.mdef = sse.value;
       //   pEntry->pkValue.mdefence = sse.value;
          return SKILL_RECOVERY;
        }
        else
          return SKILL_RETURN;
      }
      break;
    case ACTION_STEP_TIMER:
      {
      //  pEntry->pkValue.mdefence = sse.value;
        return SKILL_RETURN;
      }
      break;
    case ACTION_STEP_STOP:
    case ACTION_STEP_CLEAR:
      {
      }
      break;
    default:
      break;
  }

  return SKILL_RETURN;
}

/**
 * \brief  ״̬7 ����״̬�����ߵĹ̶�ֵ����ֵ
 * \param pEntry ״̬������
 * \param sse ����״̬
 * \return ����״̬����ֵ,�μ�ͷ�ļ��еļ���״̬������ֵö��
 */
BYTE SkillStatus_7(SceneEntryPk *pEntry,SkillStatusElement &sse)
{
  sse.byGoodnessType = SKILL_BAD;
  sse.byMutexType = 4;

  WORD value=0;
  if (sse.attacktype == zSceneEntry::SceneEntry_Player)
  {
    SceneUser *pUser = NULL;
    pUser = GameService::getMe().getSceneUserMgr().getUserBySessID(sse.dwTempID);
    if (pUser)
    {
     // value= (WORD)(0.5f*pUser->charstate.wdMen);
    }
  }

  switch(sse.byStep)
  {
    case ACTION_STEP_DOPASS:
    case ACTION_STEP_START:
    case ACTION_STEP_RELOAD:
      {
        if (selectByPercent((int)(sse.percent)))
        {
         // pEntry->changeMP(0-sse.value-value);
          return SKILL_ACTIVE;
        }
        else
          return SKILL_RETURN;
      }
      break;
    case ACTION_STEP_TIMER:
      {
      //  pEntry->changeMP(0-sse.value-value);
        return SKILL_RETURN;
      }
      break;
    case ACTION_STEP_STOP:
    case ACTION_STEP_CLEAR:
      {
      }
      break;
    default:
      break;
  }

  return SKILL_RETURN;
}

/**
 * \brief  ״̬8 ����״̬�����ߵİٷֱȷ���ֵ
 * \param pEntry ״̬������
 * \param sse ����״̬
 * \return ����״̬����ֵ,�μ�ͷ�ļ��еļ���״̬������ֵö��
 */
BYTE SkillStatus_8(SceneEntryPk *pEntry,SkillStatusElement &sse)
{
  sse.byGoodnessType = SKILL_BAD;
  sse.byMutexType = 4;

  switch(sse.byStep)
  {
    case ACTION_STEP_DOPASS:
    case ACTION_STEP_START:
    case ACTION_STEP_RELOAD:
      {
        if (selectByPercent((int)(sse.percent)))
        {
         /* SDWORD value = (SDWORD)(pEntry->getMaxMP()*(sse.value/100.0f));
          pEntry->changeMP(value);*/
          return SKILL_RECOVERY;
        }
        else
          return SKILL_RETURN;
      }
      break;
    case ACTION_STEP_TIMER:
      {
        /*SDWORD value = (SDWORD)(pEntry->getMaxMP()*(sse.value/100.0f));
        pEntry->changeMP(value);*/
        return SKILL_RETURN;
      }
      break;
    case ACTION_STEP_STOP:
    case ACTION_STEP_CLEAR:
      {
      }
      break;
    default:
      break;
  }

  return SKILL_RETURN;
}

/**
 * \brief  ״̬9 ����״̬�����ߵĹ̶�ֵ����ֵ
 * \param pEntry ״̬������
 * \param sse ����״̬
 * \return ����״̬����ֵ,�μ�ͷ�ļ��еļ���״̬������ֵö��
 */
BYTE SkillStatus_9(SceneEntryPk *pEntry,SkillStatusElement &sse)
{
  sse.byGoodnessType = SKILL_BAD;
  sse.byMutexType = 5;

  WORD value=0;
  if (sse.attacktype == zSceneEntry::SceneEntry_Player)
  {
    SceneUser *pUser = NULL;
    pUser = GameService::getMe().getSceneUserMgr().getUserBySessID(sse.dwTempID);
    if (pUser)
    {
      //value= (WORD)(1*pUser->charstate.wdMen);
    }
  }

  switch(sse.byStep)
  {
    case ACTION_STEP_DOPASS:
    case ACTION_STEP_START:
    case ACTION_STEP_RELOAD:
      {
        if (selectByPercent((int)(sse.percent)))
        {
          //pEntry->changeHP(0-sse.value);
          return SKILL_ACTIVE;
        }
        else
          return SKILL_RETURN;
      }
      break;
    case ACTION_STEP_TIMER:
      {
        SceneEntryPk *pAtt = NULL;
        switch(sse.attacktype)
        {
          case zSceneEntry::SceneEntry_Player:  // ��ҽ�ɫ
            {
             // pAtt = NetService::getMe().getSceneUserMgr().getUserBySessID(sse.dwTempID);
            }
            break;
          case zSceneEntry::SceneEntry_NPC:    // NPC
            {
              //pAtt = SceneNpcManager::getMe().getNpcByTempID(sse.dwTempID);
            }
            break;
          default:
            break;
        }

        if (pAtt)
        {
          //pEntry->directDamage(pAtt,sse.value+value,true);
          //pEntry->processDeath(pAtt);
        }
        return SKILL_RETURN;
      }
      break;
    case ACTION_STEP_STOP:
    case ACTION_STEP_CLEAR:
      {
      }
      break;
    default:
      break;
  }

  return SKILL_RETURN;
}

/**
 * \brief  ״̬10 ����״̬�����ߵİٷֱ�����ֵ,��׼Ϊ�������ֵ
 * \param pEntry ״̬������
 * \param sse ����״̬
 * \return ����״̬����ֵ,�μ�ͷ�ļ��еļ���״̬������ֵö��
 */
BYTE SkillStatus_10(SceneEntryPk *pEntry,SkillStatusElement &sse)
{
  sse.byGoodnessType = SKILL_BAD;
  sse.byMutexType = 5;

  switch(sse.byStep)
  {
    case ACTION_STEP_DOPASS:
    case ACTION_STEP_START:
    case ACTION_STEP_RELOAD:
      {
        if (selectByPercent((int)(sse.percent)))
        {
          //SDWORD value = (SDWORD)(pEntry->getMaxHP()*(sse.value/100.0f));
          //pEntry->changeHP(0-value);
          return SKILL_ACTIVE;
        }
        else
          return SKILL_RETURN;
      }
      break;
    case ACTION_STEP_TIMER:
      {
        SceneEntryPk *pAtt = NULL;
        switch(sse.attacktype)
        {
          case zSceneEntry::SceneEntry_Player:  // ��ҽ�ɫ
            {
           //   pAtt = NetService::getMe().getSceneUserMgr().getUserBySessID(sse.dwTempID);
            }
            break;
          case zSceneEntry::SceneEntry_NPC:    // NPC
            {
           //   pAtt = SceneNpcManager::getMe().getNpcByTempID(sse.dwTempID);
            }
            break;
          default:
            break;
        }

        if (pAtt)
        {
   /*       SDWORD value = (SDWORD)(pEntry->getMaxHP()*(sse.value/100.0f));
          pEntry->directDamage(pAtt,value,true);
          pEntry->processDeath(pAtt);*/
        }
        return SKILL_RETURN;
      }
      break;
    case ACTION_STEP_STOP:
    case ACTION_STEP_CLEAR:
      {
      }
      break;
    default:
      break;
  }

  return SKILL_RETURN;
}

//--------------------------------------------------

/**
 * \brief ����״̬���������캯��
 */
SkillStatusManager::SkillStatusManager()
{
  entry = NULL;
  bclearActiveSkillStatus = false;
}


/**
 * \brief ����״̬��������������
 */
SkillStatusManager::~SkillStatusManager()
{
  //if (entry->getType() == zSceneEntry::SceneEntry_Player)  saveSkillStatus();
}

/**
 * \brief ����״̬��������������
 * \param pEntry ���뼼�ܹ�������ʹ�ö���
 */
void SkillStatusManager::initMe(SceneEntryPk *pEntry)
{
  entry = pEntry;
  funlist[0].func = SkillStatus_0;
  funlist[1].func = SkillStatus_1;
  funlist[2].func = SkillStatus_2;
  funlist[3].func = SkillStatus_3;
  funlist[4].func = SkillStatus_4;
  funlist[5].func = SkillStatus_5;
  funlist[6].func = SkillStatus_6;
  funlist[7].func = SkillStatus_7;
  funlist[8].func = SkillStatus_8;
  funlist[9].func = SkillStatus_9;
  funlist[10].func = SkillStatus_10;

  //if (entry->getType() == zSceneEntry::SceneEntry_Player) loadSkillStatus();
}

/**
 * \brief ֪ͨĳ��״̬��ֵ
 */
void SkillStatusManager::sendSelectStates(SceneEntryPk *pThis,DWORD state,WORD value,WORD time)
{
  //pThis->sendtoSelectedState(state,value,time);
  //pThis->sendSevenStateToMe(state,value,time);
}

/**
 * \brief �õ���ǰ7��״̬����ֵ
 */
void SkillStatusManager::getSelectStates(Cmd::stSelectReturnStatesPropertyUserCmd *buf,unsigned long maxSize)
{

  using namespace Cmd;
  std::map<DWORD,SkillStatusElement>::iterator tIterator;
  zRTime ctv;
  for(tIterator = _activeElement.begin() ; tIterator !=_activeElement.end(); tIterator++)
  {
    if (tIterator->second.state >0 && 
        (sizeof(stSelectReturnStatesPropertyUserCmd) + sizeof(buf->states[0]) * buf->size)<= maxSize)
    {
      buf->states[buf->size].state = tIterator->second.state;
      buf->states[buf->size].result = tIterator->second.value;
      buf->states[buf->size].time = tIterator->second.dwTime;
      buf->size ++;
    }
/*        break;
      default:
        break;
    }*/
  }

  for(tIterator = _recoveryElement.begin() ; tIterator !=_recoveryElement.end(); tIterator++)
  {

    if (tIterator->second.state >0 &&
        (sizeof(stSelectReturnStatesPropertyUserCmd) + sizeof(buf->states[0]) * buf->size)<= maxSize)
    {
      buf->states[buf->size].state = tIterator->second.state;
      buf->states[buf->size].result = tIterator->second.value;
      buf->states[buf->size].time = (tIterator->second.qwTime- ctv.msecs())/1000;
      buf->size ++;
    }
  }

}

/**
 * \brief ������ʷ�ļ���״̬,�ϴ����ߵ�ʱ���ܻ����������ϵļ���״̬������Ч
 */
void SkillStatusManager::loadSkillStatus(char *buf,DWORD length)
{
  SkillStatusElement *value;
//  char buf[zSocket::MAX_DATASIZE];
  DWORD count;
  DWORD statelen;
  bool notify;
  /*DWORD length;

  count = 0; 
  length=0;
  bzero(buf,zSocket::MAX_DATASIZE);*/

  SkillState *pState = (SkillState *)buf;
  statelen = sizeof(SkillState);
 // memcpy(&(entry->skillValue),pState,statelen,sizeof(entry->skillValue));
  length-=statelen;

#ifdef _DEBUG
  H::logger->debug("[Ϊ��ɫ(%s)(%d)���ر���ļ���״̬]",entry->name,entry->id);
#endif
  //COfflineSkillStatus::getOfflineSkillStatus(entry->id,buf,length);
  count = length/sizeof(SkillStatusElement);
  notify = false;
#ifdef _DEBUG
  H::logger->debug("[��%d������״̬��Ҫ����]",count);
#endif
  value = (SkillStatusElement *)(buf+statelen);

  SceneEntryPk *pAtt = NULL;
  if (value->attacktype == zSceneEntry::SceneEntry_Player)
  {
   // pAtt = NetService::getMe().getSceneUserMgr().getUserByID(value->dwAttackerID);
    if (pAtt) value->dwTempID = pAtt->tempid;
  }

  for(DWORD i=0; i<count; i++)
  {
    value->byStep = ACTION_STEP_RELOAD;
    switch(runStatusElement(*value))
    {
      case SKILL_RECOVERY:
        {
#ifdef _DEBUG
          H::logger->debug("[%d�ż���״̬�����ص���ʱ��������]",value->id);
#endif
          //value->refresh = 1;
          //value->qwTime = H::timeTick->getMilliTime()+value->dwTime *1000;
          _recoveryElement[value->id/*value->byMutexType*/]=*value;
         // _recoveryElement[value->id].qwTime = H::timeTick->getMilliTime()+_recoveryElement[value->id].dwTime *1000;
          if (value->state >0)
          {
            sendSelectStates(entry,value->state,value->value,value->dwTime);
            //entry->setEffectStatus(value->state);
           // entry->showCurrentEffect(value->state,true);
          }
          notify = true;
        }
        break;
      case SKILL_ACTIVE:
        {
#ifdef _DEBUG
          H::logger->debug("[%d�ż���״̬�����ص���������]",value->id);
#endif
          _activeElement[value->id/*value->byMutexType*/]=*value;
         // _recoveryElement[value->id].qwTime = H::timeTick->getMilliTime()+_recoveryElement[value->id].dwTime *1000;
          if (value->state >0)
          {
            sendSelectStates(entry,value->state,value->value,value->dwTime);
            //entry->setEffectStatus(value->state);
          //  entry->showCurrentEffect(value->state,true);
          }
          notify = true;
        }
        break;
      default:
#ifdef _DEBUG
          H::logger->debug("[%d�ż���״̬�޷����ӵ���Ӧ�ı���]",value->id);
#endif
        break;
    }
    value++;
  }

  if (notify&&entry)
  {
    //entry->changeAndRefreshHMS(true,true);
  }
}

/**
 * \brief �洢��ʷ�ļ���״̬,�ϴ����ߵ�ʱ���ܻ����������ϵļ���״̬������Ч
 */
void SkillStatusManager::saveSkillStatus(char *buf,DWORD &size)
{
  std::map<DWORD,SkillStatusElement>::iterator tIterator;
  SkillStatusElement *value;
  DWORD count;
  DWORD statelen;
  DWORD length;

  length = 0;
  count = 0;
  statelen = 0;

  SkillState *pState = (SkillState *)buf;
  statelen = sizeof(SkillState);
  //memcpy(pState,&(entry->skillValue),statelen,statelen);

  value = (SkillStatusElement *)(buf+statelen);
  length = sizeof(SkillStatusElement);
  for(tIterator = _activeElement.begin() ; tIterator !=_activeElement.end();tIterator ++)
  {
    //memcpy(value,&tIterator->second,length,length);
#ifdef _DEBUG
    H::logger->debug("[����״̬%d���洢]",tIterator->second.id);
#endif
    count++;
    value++;
    if (count>3000) break;
  }

  if (count<3000)
  {
    for(tIterator = _recoveryElement.begin() ; tIterator !=_recoveryElement.end();tIterator ++)
    {
      //memcpy(value,&tIterator->second,length,length);
#ifdef _DEBUG
    H::logger->debug("[����״̬%d���洢]",tIterator->second.id);
#endif
      count++;
      value++;
      if (count>3000) break;
    }
  }
  //if (count >0) COfflineSkillStatus::writeOfflineSkillStatus(entry->id,buf,count*length);
  size = statelen + count*length;
#ifdef _DEBUG
  H::logger->debug("[��%d������״̬��Ҫ�洢]",count);
#endif
}

/**
 * \brief ��һ�����ܲ���ʩ�����ҵ�����[SKY��������3��]
 * \param carrier ���ܲ���Ͷ����,��������˼���״̬
 * \param good ��־��������ǲ���һ������ļ���
 * \return true Ϊ������һ������,falseΪֹͣ�����ء�
 */
bool SkillStatusManager::putOperationToMe(const SkillStatusCarrier &carrier,const bool good,SWORD rangDamageBonus)
{
  std::vector<SkillElement>::const_iterator tIterator;
  bool sendData = false;

  entry->isPhysics = false;
  if (!entry->preAttackMe(carrier.attacker,&carrier.revCmd,false,good)) return true;

  for (tIterator = carrier.status->_StatusElementList.begin();
    tIterator != carrier.status->_StatusElementList.end();
    tIterator++)
  {
    SkillStatusElement element;
    element.byStep  =  ACTION_STEP_START;
    element.id    =  tIterator->id;
    element.percent =  tIterator->percent;
    element.value  =  tIterator->value;
    element.state  =  tIterator->state;

    element.dwSkillID = carrier.skillbase->id;//carrier.skillID; 
    element.dwTime = tIterator->time;
    element.qwTime = H::timeTick->getMilliTime()+element.dwTime *1000;

    SceneEntryPk *pAtt = carrier.attacker->getTopMaster();
    element.dwTempID = pAtt->tempid;
    element.dwAttackerID = pAtt->id;
    element.attacktype = pAtt->getType();
    if (element.dwTime <=2)
    {
      element.refresh = 0;
    }
    else
    {
      element.refresh = 1;
      sendData = true;
    }

    entry->curMagicManType = element.attacktype;
    entry->curMagicManID = element.dwTempID;
    entry->keepPos.x = (DWORD)carrier.revCmd.xDes;
    entry->keepPos.y = (DWORD)carrier.revCmd.yDes;
    entry->keepDir = carrier.revCmd.byDirect;

    switch(runStatusElement(element))
    {
      case SKILL_RECOVERY:
        {
#ifdef _DEBUG
          H::logger->debug("[��ʱ����]��[%u]��״̬��ʩ�������ϳ���ʱ��Ϊ[%u]",element.id,element.dwTime);
          Channel::sendSys(entry->tempid,Cmd::INFO_TYPE_SYS,"[��ʱ����]��[%u]��״̬��ʩ�������ϳ���ʱ��Ϊ[%u]",element.id,element.dwTime);
#endif
          element.qwTime = H::timeTick->getMilliTime()+element.dwTime *1000;
          if (element.state >0)
          {
            clearMapElement(element.id/*element.byMutexType*/,_recoveryElement,element.id,false);
            _recoveryElement[element.id/*element.byMutexType*/]=element;
            sendSelectStates(entry,element.state,element.value,element.dwTime);
            //entry->setEffectStatus(element.state);
            entry->showCurrentEffect(element.state,true);
          }
          else
          {
            clearMapElement(element.id/*element.byMutexType*/,_recoveryElement,element.id);
            _recoveryElement[element.id/*element.byMutexType*/]=element;
          }
        }
        break;
      case SKILL_BREAK:
        {
          return false;
        }
        break;
      case SKILL_ACTIVE:
        {
#ifdef _DEBUG
          H::logger->debug("[�˺�״̬]��[%u]��״̬��ʩ�������ϳ���ʱ��Ϊ[%u]",element.id,element.dwTime);
          Channel::sendSys(entry->tempid,Cmd::INFO_TYPE_SYS,"[����״̬]��[%u]��״̬��ʩ�������ϳ���ʱ��Ϊ[%u]",element.id,element.dwTime);
#endif
          if (element.dwTime==0) break;
          clearMapElement(element.id/*element.byMutexType*/,_activeElement,element.id);
          _activeElement[element.id/*element.byMutexType*/]=element;
          if (element.state >0)
          {
            sendSelectStates(entry,element.state,element.value,element.dwTime);
            //entry->setEffectStatus(element.state);
            entry->showCurrentEffect(element.state,true);
          }
        }
        break;
      case SKILL_RETURN:
      default:
        break;
    }
  }

  if (carrier.status->isInjure == 1)
  {
    entry->AttackMe(carrier.attacker,&carrier.revCmd,entry->isPhysics,rangDamageBonus);
   // carrier.attacker->setPetsChaseTarget(entry);
#ifdef _DEBUG
    H::logger->debug("[�߹������㹫ʽ]");
    Channel::sendSys(entry->tempid,Cmd::INFO_TYPE_SYS,"[�˺�����]");
#endif
  }
  else
  {
    if (entry->notifyHMS)
    {
      entry->attackRTHpAndMp();
    }
    SceneEntryPk *pAtt = carrier.attacker->getTopMaster();
    if (pAtt&&pAtt->isEnemy(entry)&&carrier.status->range!=22)
    {
      SceneEntryPk * aMaster = pAtt->getTopMaster();
      SceneEntryPk * pMaster = entry->getTopMaster();
      if (aMaster->getType()==zSceneEntry::SceneEntry_Player)
      {
        SceneUser * a = (SceneUser *)aMaster;
        if (pMaster->getType()==zSceneEntry::SceneEntry_Player)
        {
          SceneUser * p = (SceneUser *)pMaster;
         // ScenePk::checkProtect(a,p);
        }
      }
    }
    //entry->processDeath(carrier.attacker);
#ifdef _DEBUG
    H::logger->debug("[���߹������㹫ʽ]");
    Channel::sendSys(entry->tempid,Cmd::INFO_TYPE_SYS,"[����Ѫ�Է���]");
#endif
  }
  entry->isPhysics = false;
  if (entry->reSendData) entry->changeAndRefreshHMS(true,sendData);
  return true;
}

/**
 * \brief ��ʱ��ˢ��
 */
void SkillStatusManager::timer()
{
  std::map<DWORD,SkillStatusElement>::iterator tIterator,delIterator;
  bool dirty=false;
  bool sendData =false;

  for(tIterator = _activeElement.begin() ; tIterator !=_activeElement.end() ; )
  {
#ifdef _DEBUG
    H::logger->debug("[��ʱ.��]ʩ�������ϵĵ�[%u]��״̬ʣ��ʱ��[%u]",tIterator->second.id,tIterator->second.dwTime);
    Channel::sendSys(entry->tempid,Cmd::INFO_TYPE_SYS,"[��ʱ.��]ʩ�������ϵĵ�[%u]��״̬ʣ��ʱ��[%u]",tIterator->second.id,tIterator->second.dwTime);
#endif
	if (tIterator->second.dwTime>0)
	{
		//sky �׼������״̬û��ʱ�����
		if(tIterator->second.dwSkillID != SKILLID_IMMOLATE && tIterator->second.dwSkillID != SKILLID_SOUL)
			tIterator->second.dwTime --;
	}
	else 
	{
		tIterator->second.dwTime = 0;
	}

    tIterator->second.byStep = ACTION_STEP_TIMER;
    runStatusElement(tIterator->second);

    if (0 == tIterator->second.dwTime)
    {
      tIterator->second.byStep = ACTION_STEP_STOP;
      runStatusElement(tIterator->second);
      if (tIterator->second.refresh) sendData = true;
      if (tIterator->second.state >0)
      {
        //entry->clearEffectStatus(tIterator->second.state);
        //entry->showCurrentEffect(tIterator->second.state,false);
      }
#ifdef _DEBUG
    H::logger->debug("[�˺�״̬]ʩ�������ϵĵ�[%u]��״̬��ɾ��",tIterator->second.id);
    Channel::sendSys(entry->tempid,Cmd::INFO_TYPE_SYS,"[�˺�״̬]ʩ�������ϵĵ�[%u]��״̬��ɾ��",tIterator->second.id);
#endif
      delIterator = tIterator;
      tIterator ++;
      _activeElement.erase(delIterator->first);
      dirty = true;
    }
    else
    {
      tIterator ++;
    }
  }

  for(tIterator = _recoveryElement.begin() ; tIterator !=_recoveryElement.end();)
  {
    QWORD curQtime = H::timeTick->getMilliTime();
    if (curQtime >= tIterator->second.qwTime)
    {
      tIterator->second.byStep = ACTION_STEP_STOP;
      runStatusElement(tIterator->second);
      if (tIterator->second.refresh) sendData = true;
      if (tIterator->second.state >0)
      {
        //entry->clearEffectStatus(tIterator->second.state);
        entry->showCurrentEffect(tIterator->second.state,false);
      }
#ifdef _DEBUG
      H::logger->debug("[��ʱ����]ʩ�������ϵĵ�[%u]��״̬��ɾ��",tIterator->second.id);
      Channel::sendSys(entry->tempid,Cmd::INFO_TYPE_SYS,"[��ʱ����]ʩ�������ϵĵ�[%u]��״̬��ɾ��",tIterator->second.id);
#endif
      delIterator = tIterator;
      tIterator ++;
      _recoveryElement.erase(delIterator->first);
      dirty = true;
    }
    else
    {
      tIterator->second.dwTime = (tIterator->second.qwTime - curQtime)/1000;
      tIterator ++;
    }
  }
  if (entry->notifyHMS)
  {
    entry->attackRTHpAndMp();
  }
  if (dirty||entry->reSendData)
  {
    entry->changeAndRefreshHMS(false,sendData);
  }
  //std::map<DWORD,SkillStatusElement>::iterator tIterator,delIterator;
  if (bclearActiveSkillStatus)
  {
    for(tIterator = _activeElement.begin() ; tIterator !=_activeElement.end() ; )
    {
      tIterator->second.byStep = ACTION_STEP_CLEAR;
      runStatusElement(tIterator->second);
      if (tIterator->second.state >0)
      {
        //entry->clearEffectStatus(tIterator->second.state);
        entry->showCurrentEffect(tIterator->second.state,false);
      }
      delIterator = tIterator;
      tIterator ++;
      _activeElement.erase(delIterator->first);
  
    }

    for(tIterator = _recoveryElement.begin() ; tIterator !=_recoveryElement.end();)
    {
      tIterator->second.byStep = ACTION_STEP_CLEAR;
      runStatusElement(tIterator->second);
      if (tIterator->second.state >0)
      {
        //entry->clearEffectStatus(tIterator->second.state);
        entry->showCurrentEffect(tIterator->second.state,false);
      }
      delIterator = tIterator;
      tIterator ++;
      _recoveryElement.erase(delIterator->first);
    }
    bclearActiveSkillStatus = false;
  }
}

/**
 * \brief �������б���״̬,�������ñ�������ʱ����
 */
void SkillStatusManager::processPassiveness()
{
  std::map<DWORD,SkillStatusElement>::iterator tIterator;

  for(tIterator = _recoveryElement.begin() ; tIterator !=_recoveryElement.end() ; tIterator ++)
  {
    tIterator->second.byStep = ACTION_STEP_DOPASS;
    if (tIterator->second.percent<100) tIterator->second.percent=100;
    runStatusElement(tIterator->second);
  }

  for(tIterator = _passivenessElement.begin() ; tIterator !=_passivenessElement.end() ; tIterator ++)
  {
    tIterator->second.byStep = ACTION_STEP_DOPASS;
    if (tIterator->second.percent<100&&tIterator->second.id!=180) tIterator->second.percent=100;
    runStatusElement(tIterator->second);
  }
}

/**
 * \brief ִ��һ�������״̬  [���뼼��״̬��ʵ�ʴ���]
 * \return ״̬����ֵ
      SKILL_ACTIVE    //  �ӵ��MAP��
      SKILL_RECOVERY    //  �ӵ���ʱ����MAP��
      SKILL_PASSIVENESS  //  �ӵ����ñ���MAP��
      SKILL_RETURN    //  ���ز����κβ���
      SKILL_DONOW      //  ����ִ������ֵ�۳�����
 */
BYTE SkillStatusManager::runStatusElement(SkillStatusElement &element)
{
  return  funlist[element.id>SKILLSTATENUMBER?0:element.id].func(entry,element);
}

/**
 * \brief  ����������ϵĲ����ķ�����״̬
 */
void SkillStatusManager::clearBadActiveSkillStatus()
{
  std::map<DWORD,SkillStatusElement>::iterator tIterator,delIterator;

  for(tIterator = _activeElement.begin() ; tIterator !=_activeElement.end() ; )
  {
    if (tIterator->second.byGoodnessType == SKILL_BAD)
    {
      tIterator->second.byStep = ACTION_STEP_CLEAR;
      runStatusElement(tIterator->second);
      if (tIterator->second.state >0)
      {
        //entry->clearEffectStatus(tIterator->second.state);
        entry->showCurrentEffect(tIterator->second.state,false);
      }
      delIterator = tIterator;
      tIterator ++;
      _activeElement.erase(delIterator->first);
    }
    else
    {
      tIterator ++;
    }
  }

  for(tIterator = _recoveryElement.begin() ; tIterator !=_recoveryElement.end();)
  {
    if (tIterator->second.byGoodnessType == SKILL_BAD)
    {
      tIterator->second.byStep = ACTION_STEP_CLEAR;
      runStatusElement(tIterator->second);
      if (tIterator->second.state >0)
      {
        //entry->clearEffectStatus(tIterator->second.state);
        entry->showCurrentEffect(tIterator->second.state,false);
      }
      delIterator = tIterator;
      tIterator ++;
      _recoveryElement.erase(delIterator->first);
    }
    else
    {
      tIterator ++;
    }
  }
}

/**
 * \brief  ����������ϵķ�������״̬
 */
void SkillStatusManager::clearActiveSkillStatus()
{
  bclearActiveSkillStatus = true;
}

/**
 * \brief  ����������ϵķ�������״̬
 */
void SkillStatusManager::clearActiveSkillStatusOnlyUseToStatus48()
{
  std::map<DWORD,SkillStatusElement>::iterator tIterator,delIterator;

  for(tIterator = _activeElement.begin() ; tIterator !=_activeElement.end() ; )
  {
    tIterator->second.byStep = ACTION_STEP_CLEAR;
    runStatusElement(tIterator->second);
    if (tIterator->second.state >0)
    {
      //entry->clearEffectStatus(tIterator->second.state);
      entry->showCurrentEffect(tIterator->second.state,false);
    }
    delIterator = tIterator;
    tIterator ++;
    _activeElement.erase(delIterator->first);

  }

  for(tIterator = _recoveryElement.begin() ; tIterator !=_recoveryElement.end();)
  {
    if (tIterator->second.id == 173)
    { 
      tIterator++;
      continue; //������˼���⴦��һ��
    }
    tIterator->second.byStep = ACTION_STEP_CLEAR;
    runStatusElement(tIterator->second);
    if (tIterator->second.state >0)
    {
      //entry->clearEffectStatus(tIterator->second.state);
      entry->showCurrentEffect(tIterator->second.state,false);
    }
    delIterator = tIterator;
    tIterator ++;
    _recoveryElement.erase(delIterator->first);
  }
  this->entry->changeAndRefreshHMS();
}


/**
 * \brief  ���ָ������ID�ļ���״̬
 */
void SkillStatusManager::clearSkill(DWORD dwSkillID)
{
  std::map<DWORD,SkillStatusElement>::iterator tIterator,delIterator;

  for(tIterator = _activeElement.begin() ; tIterator !=_activeElement.end() ; )
  {
    if (tIterator->second.dwSkillID == dwSkillID)
    {
      tIterator->second.byStep = ACTION_STEP_CLEAR;
      runStatusElement(tIterator->second);
      if (tIterator->second.state >0)
      {
        //entry->clearEffectStatus(tIterator->second.state);
        entry->showCurrentEffect(tIterator->second.state,false);
      }
	  tIterator->second.dwTime = 0;
	  tIterator ++;
      /*delIterator = tIterator;
      _activeElement.erase(delIterator->first);*/
    }
    else
    {
      tIterator++;
    }

  }

  for(tIterator = _recoveryElement.begin() ; tIterator !=_recoveryElement.end();)
  {
    if (tIterator->second.dwSkillID == dwSkillID)
    {
      tIterator->second.byStep = ACTION_STEP_CLEAR;
      runStatusElement(tIterator->second);
      if (tIterator->second.state >0)
      {
        //entry->clearEffectStatus(tIterator->second.state);
        entry->showCurrentEffect(tIterator->second.state,false);
      }
      delIterator = tIterator;
      tIterator ++;
      _recoveryElement.erase(delIterator->first);
    }
    else
    {
      tIterator++;
    }
  }
  this->entry->changeAndRefreshHMS();
}


/**
 * \brief �����������������������
 * \param skillid ����id
 * \param pSkillStatus �����еĲ���
 */
void SkillStatusManager::putPassivenessOperationToMe(const DWORD skillid,const SkillStatus *pSkillStatus)
{
  std::vector<SkillElement>::const_iterator tIterator;

  for (tIterator = pSkillStatus->_StatusElementList.begin();
    tIterator != pSkillStatus->_StatusElementList.end();
    tIterator++)
  {
    SkillStatusElement element;
    element.id    =  tIterator->id;
    element.percent =  tIterator->percent;
    element.value  =  tIterator->value;
    element.state  =  tIterator->state;
    element.dwSkillID = skillid;
    element.dwTime = tIterator->time;
    _passivenessElement[element.id]=element;

#ifdef _DEBUG
      H::logger->debug("[���ñ���]֮[%u]��״̬��ʩ��������",element.id);
      Channel::sendSys(entry->tempid,Cmd::INFO_TYPE_SYS,"[���ñ���]֮[%u]��״̬��ʩ��������",element.id);
#endif
  }
}

/**
 * \brief  ���Ӳ���״̬�ĳ���ʱ����ֵ
 */
void SkillStatusManager::addBadSkillStatusPersistTime(const DWORD &value)
{
  std::map<DWORD,SkillStatusElement>::iterator tIterator;

  for(tIterator = _activeElement.begin() ; tIterator !=_activeElement.end() ; tIterator ++)
  {
    if (tIterator->second.byGoodnessType == SKILL_BAD)
    {
      tIterator->second.dwTime += value;
    }
  }

  for(tIterator = _recoveryElement.begin() ; tIterator !=_recoveryElement.end(); tIterator++)
  {
    if (tIterator->second.byGoodnessType == SKILL_BAD)
    {
      tIterator->second.dwTime += value;
      tIterator->second.qwTime += value;
    }
  }
}

/**
 * \brief  ���Ӳ���״̬�ĳ���ʱ��ٷֱ�
 */
void SkillStatusManager::addBadSkillStatusPersistTimePercent(const DWORD &value)
{
  std::map<DWORD,SkillStatusElement>::iterator tIterator;

  for(tIterator = _activeElement.begin() ; tIterator !=_activeElement.end() ; tIterator ++)
  {
    if (tIterator->second.byGoodnessType == SKILL_BAD)
    {
      tIterator->second.dwTime = (DWORD)(tIterator->second.dwTime*(value/100.0f));
    }
  }

  for(tIterator = _recoveryElement.begin() ; tIterator !=_recoveryElement.end(); tIterator++)
  {
    if (tIterator->second.byGoodnessType == SKILL_BAD)
    {
      tIterator->second.dwTime = (DWORD)(tIterator->second.dwTime*(value/100.0f));
      tIterator->second.qwTime = (DWORD)(tIterator->second.qwTime*(value/100.0f));
    }
  }
}

/**
 * \brief  �������״̬�е�ָ�����
 * \param byMutexType ���ܴ���
 * \param myMap ������״̬map
 * \param dwID ����״̬id
 */
void SkillStatusManager::clearMapElement(const BYTE &byMutexType,std::map<DWORD,SkillStatusElement> &myMap,DWORD dwID,bool notify)
{
/*  std::map<DWORD,SkillStatusElement>::iterator tIterator,delIterator;

  for(tIterator = myMap.begin() ; tIterator !=myMap.end();)
  {
    if (tIterator->second.byMutexType == byMutexType)
    {
      if (tIterator->second.id != dwID)
      {
        tIterator->second.byStep = ACTION_STEP_CLEAR;
        runStatusElement(tIterator->second);
      }
      if (tIterator->second.state >0)
      {
        //entry->clearEffectStatus(tIterator->second.state);
        entry->showCurrentEffect(tIterator->second.state,false);
      }
      delIterator = tIterator;
      tIterator ++;
      myMap.erase(delIterator->first);
    }
    else
    {
      tIterator ++;
    }
  }*/
  std::map<DWORD,SkillStatusElement>::iterator tIterator,delIterator;

  for(tIterator = myMap.begin() ; tIterator !=myMap.end();)
  {
    if (tIterator->second.id == byMutexType)
    {
      if (tIterator->second.id != dwID)
      {
        tIterator->second.byStep = ACTION_STEP_CLEAR;
        runStatusElement(tIterator->second);
      }
      if (tIterator->second.state >0)
      {
        //entry->clearEffectStatus(tIterator->second.state);
        entry->showCurrentEffect(tIterator->second.state,false,notify);
      }
      delIterator = tIterator;
      tIterator ++;
      myMap.erase(delIterator->first);
    }
    else
    {
      tIterator ++;
    }
  }

}

void SkillStatusManager::clearRecoveryElement(DWORD value)
{
  clearMapElement(value,_recoveryElement,0);
}

void SkillStatusManager::clearActiveElement(DWORD value)
{
  clearMapElement(value,_activeElement,0);
}

void SkillStatusManager::processDeath()
{
  if (entry->bombskillId >0)
  {
    Cmd::stAttackMagicUserCmd cmd;

    cmd.byAttackType = Cmd::ATTACKTYPE_U2P;
    cmd.dwDefenceTempID = 0;
    cmd.dwUserTempID = entry->tempid;
    cmd.wdMagicType = entry->bombskillId;
    cmd.byAction = Cmd::Ani_Num;
    cmd.byDirect = entry->getDir();
    cmd.xDes = (WORD)entry->getPos().x;
    cmd.yDes = (WORD)entry->getPos().y;

    zSkill *s = NULL;

    s = zSkill::createTempSkill(entry,entry->bombskillId,1);
    if (s)
    {
      s->action(&cmd,sizeof(cmd));
      SAFE_DELETE(s);
    }
  }

  clearActiveSkillStatus();
}


/**
 * \brief  ���Ժ���������ʾ����״̬��ǰֵ
 */
void SkillStatusManager::showValue()
{
  //Channel::sendSys((SceneUser *)entry,Cmd::INFO_TYPE_SYS,"��ɫ���ϵ�[SkillValue]�����б�:---------------------------");
  //Channel::sendSys((SceneUser *)entry,Cmd::INFO_TYPE_SYS,"�˺�ֵ���ӹ̶���ֵ1=%ld",entry->skillValue.dvalue);
  //Channel::sendSys((SceneUser *)entry,Cmd::INFO_TYPE_SYS,"�˺�ֵ����x%2=%ld",entry->skillValue.dvaluep);
  //Channel::sendSys((SceneUser *)entry,Cmd::INFO_TYPE_SYS,"���������ֵ��� 57,86=%ld",entry->skillValue.pdefence);
  //Channel::sendSys((SceneUser *)entry,Cmd::INFO_TYPE_SYS,"�����������ٷֱ�=%ld",entry->skillValue.pdefencep);
  //Channel::sendSys((SceneUser *)entry,Cmd::INFO_TYPE_SYS,"��Ϊ���С����79=%ld",entry->skillValue.topet);
  //Channel::sendSys((SceneUser *)entry,Cmd::INFO_TYPE_SYS,"���������˺�83=%ld",entry->skillValue.appenddam);
  //Channel::sendSys((SceneUser *)entry,Cmd::INFO_TYPE_SYS,"�ƶ��ٶȱ���ٷֱ� 16,56=%ld",entry->skillValue.movespeed);
  //Channel::sendSys((SceneUser *)entry,Cmd::INFO_TYPE_SYS,"���ټ���ʩ�ż��17=%ld",entry->skillValue.mgspeed);
  //Channel::sendSys((SceneUser *)entry,Cmd::INFO_TYPE_SYS,"�����������״̬����18=%ld",entry->skillValue.coldp);
  //Channel::sendSys((SceneUser *)entry,Cmd::INFO_TYPE_SYS,"���������ж�״̬����19=%ld",entry->skillValue.poisonp);
  //Channel::sendSys((SceneUser *)entry,Cmd::INFO_TYPE_SYS,"��������ʯ��״̬����20=%ld",entry->skillValue.petrifyp);
  //Channel::sendSys((SceneUser *)entry,Cmd::INFO_TYPE_SYS,"��������ʧ��״̬����21=%ld",entry->skillValue.blindp);
  //Channel::sendSys((SceneUser *)entry,Cmd::INFO_TYPE_SYS,"�����������״̬����22=%ld",entry->skillValue.chaosp);
  //Channel::sendSys((SceneUser *)entry,Cmd::INFO_TYPE_SYS,"����������33,64=%ld",entry->skillValue.atrating);
  //Channel::sendSys((SceneUser *)entry,Cmd::INFO_TYPE_SYS,"����������33,64=%ld",entry->skillValue.reduce_atrating);

  //Channel::sendSys((SceneUser *)entry,Cmd::INFO_TYPE_SYS,"����ֵ�ָ��ٶ�����34=%ld",entry->skillValue.hpspeedup);
  //Channel::sendSys((SceneUser *)entry,Cmd::INFO_TYPE_SYS,"����ֵ�ָ��ٶ�����35=%ld",entry->skillValue.mpspeedup);
  //Channel::sendSys((SceneUser *)entry,Cmd::INFO_TYPE_SYS,"����ֵ�ָ��ٶ�����36=%ld",entry->skillValue.spspeedup);
  //Channel::sendSys((SceneUser *)entry,Cmd::INFO_TYPE_SYS,"����������37=%ld",entry->skillValue.akdodge);
  //Channel::sendSys((SceneUser *)entry,Cmd::INFO_TYPE_SYS,"����45=%ld",entry->skillValue.reflect);
  //Channel::sendSys((SceneUser *)entry,Cmd::INFO_TYPE_SYS,"����x%46=%ld",entry->skillValue.reflectp);
  //Channel::sendSys((SceneUser *)entry,Cmd::INFO_TYPE_SYS,"Ϊ�����ٷ�֮���ĵ����˺�50=%ld",entry->skillValue.reflect2);
  //Channel::sendSys((SceneUser *)entry,Cmd::INFO_TYPE_SYS,"�����������59,=%ld",entry->skillValue.mdefence);
  //Channel::sendSys((SceneUser *)entry,Cmd::INFO_TYPE_SYS,"������������ٷֱ�x%=%ld",entry->skillValue.mdefencep);
  //Channel::sendSys((SceneUser *)entry,Cmd::INFO_TYPE_SYS,"�����ٶȱ��80,81=%ld",entry->skillValue.uattackspeed);
  //Channel::sendSys((SceneUser *)entry,Cmd::INFO_TYPE_SYS,"���������ߴ�״̬����82=%ld",entry->skillValue.sevendownp);
  //Channel::sendSys((SceneUser *)entry,Cmd::INFO_TYPE_SYS,"�˺�ת�ưٷֱ�=%ld",entry->skillValue.tsfdamp);
  //Channel::sendSys((SceneUser *)entry,Cmd::INFO_TYPE_SYS,"����:�����˺�=%ld",entry->skillValue.passdam);
  //Channel::sendSys((SceneUser *)entry,Cmd::INFO_TYPE_SYS,"��ɫ���ϵ�[PkValue]�����б�:---------------------------");
  //Channel::sendSys((SceneUser *)entry,Cmd::INFO_TYPE_SYS,"��������=%ld",entry->pkValue.pdamage);
  //Channel::sendSys((SceneUser *)entry,Cmd::INFO_TYPE_SYS,"���������=%ld",entry->pkValue.pdefence);
  //Channel::sendSys((SceneUser *)entry,Cmd::INFO_TYPE_SYS,"����������=%ld",entry->pkValue.mdamage);
  //Channel::sendSys((SceneUser *)entry,Cmd::INFO_TYPE_SYS,"����������=%ld",entry->pkValue.mdefence);
  //Channel::sendSys((SceneUser *)entry,Cmd::INFO_TYPE_SYS,"���ķ���ֵ=%ld",entry->pkValue.mcost);
  //Channel::sendSys((SceneUser *)entry,Cmd::INFO_TYPE_SYS,"��������ֵ=%ld",entry->pkValue.hpcost);
  //Channel::sendSys((SceneUser *)entry,Cmd::INFO_TYPE_SYS,"��������ֵ=%ld",entry->pkValue.spcost);
  //Channel::sendSys((SceneUser *)entry,Cmd::INFO_TYPE_SYS,"��������=%ld",entry->pkValue.exp);
  //Channel::sendSys((SceneUser *)entry,Cmd::INFO_TYPE_SYS,"�˺�ֵ=%ld",entry->pkValue.dvalue);
  //Channel::sendSys((SceneUser *)entry,Cmd::INFO_TYPE_SYS,"�˺�ֵ���Ӱٷֱ�=%ld",entry->pkValue.dvaluep);
  //Channel::sendSys((SceneUser *)entry,Cmd::INFO_TYPE_SYS,"�б����:----------------------------------------------");
}

/**
 * \brief  ��ӡ����״̬��ǰֵ��log�ļ���
 */
void SkillStatusManager::showValueToLog()
{
  //Zebra::logger->debug("��ɫ���ϵ�[SkillValue]�����б�:---------------------------");
  //Zebra::logger->debug("�˺�ֵ���ӹ̶���ֵ1=%ld",entry->skillValue.dvalue);
  //Zebra::logger->debug("�˺�ֵ����x%2=%ld",entry->skillValue.dvaluep);
  //Zebra::logger->debug("���������ֵ��� 57,86=%ld",entry->skillValue.pdefence);
  //Zebra::logger->debug("�����������ٷֱ�=%ld",entry->skillValue.pdefencep);
  //Zebra::logger->debug("��Ϊ���С����79=%ld",entry->skillValue.topet);
  //Zebra::logger->debug("���������˺�83=%ld",entry->skillValue.appenddam);
  //Zebra::logger->debug("�ƶ��ٶȱ���ٷֱ� 16,56=%ld",entry->skillValue.movespeed);
  //Zebra::logger->debug("���ټ���ʩ�ż��17=%ld",entry->skillValue.mgspeed);
  //Zebra::logger->debug("�����������״̬����18=%ld",entry->skillValue.coldp);
  //Zebra::logger->debug("���������ж�״̬����19=%ld",entry->skillValue.poisonp);
  //Zebra::logger->debug("��������ʯ��״̬����20=%ld",entry->skillValue.petrifyp);
  //Zebra::logger->debug("��������ʧ��״̬����21=%ld",entry->skillValue.blindp);
  //Zebra::logger->debug("�����������״̬����22=%ld",entry->skillValue.chaosp);
  //Zebra::logger->debug("����������33,64=%ld",entry->skillValue.atrating);
  //Zebra::logger->debug("����ֵ�ָ��ٶ�����34=%ld",entry->skillValue.hpspeedup);
  //Zebra::logger->debug("����ֵ�ָ��ٶ�����35=%ld",entry->skillValue.mpspeedup);
  //Zebra::logger->debug("����ֵ�ָ��ٶ�����36=%ld",entry->skillValue.spspeedup);
  //Zebra::logger->debug("����������37=%ld",entry->skillValue.akdodge);
  //Zebra::logger->debug("����45=%ld",entry->skillValue.reflect);
  //Zebra::logger->debug("����x%46=%ld",entry->skillValue.reflectp);
  //Zebra::logger->debug("Ϊ�����ٷ�֮���ĵ����˺�50=%ld",entry->skillValue.reflect2);
  //Zebra::logger->debug("�����������59,=%ld",entry->skillValue.mdefence);
  //Zebra::logger->debug("������������ٷֱ�x%=%ld",entry->skillValue.mdefencep);
  //Zebra::logger->debug("�����ٶȱ��80,81=%ld",entry->skillValue.uattackspeed);
  //Zebra::logger->debug("���������ߴ�״̬����82=%ld",entry->skillValue.sevendownp);
  //Zebra::logger->debug("�˺�ת�ưٷֱ�=%ld",entry->skillValue.tsfdamp);
  //Zebra::logger->debug("����:�����˺�=%ld",entry->skillValue.passdam);
  //Zebra::logger->debug("��ɫ���ϵ�[PkValue]�����б�:---------------------------");
  //Zebra::logger->debug("��������=%ld",entry->pkValue.pdamage);
  //Zebra::logger->debug("���������=%ld",entry->pkValue.pdefence);
  //Zebra::logger->debug("����������=%ld",entry->pkValue.mdamage);
  //Zebra::logger->debug("����������=%ld",entry->pkValue.mdefence);
  //Zebra::logger->debug("���ķ���ֵ=%ld",entry->pkValue.mcost);
  //Zebra::logger->debug("��������ֵ=%ld",entry->pkValue.hpcost);
  //Zebra::logger->debug("��������ֵ=%ld",entry->pkValue.spcost);
  //Zebra::logger->debug("��������=%ld",entry->pkValue.exp);
  //Zebra::logger->debug("�˺�ֵ=%ld",entry->pkValue.dvalue);
  //Zebra::logger->debug("�˺�ֵ���Ӱٷֱ�=%ld",entry->pkValue.dvaluep);
  //Zebra::logger->debug("�б����:----------------------------------------------");
}

/**
 * \brief  ��ʾ��ɫ���ϵ���������״̬
 */
void SkillStatusManager::showActive()
{
  std::map<DWORD,SkillStatusElement>::iterator tIterator;
  SkillStatusElement *element;

  Channel::sendSys((SceneUser *)entry,Cmd::INFO_TYPE_SYS,"��ɫ���ϵ�����״̬�б�:");
  for(tIterator = _activeElement.begin() ; tIterator !=_activeElement.end(); tIterator++)
  {
    std::string myname;
    char buf [45];
    element = &tIterator->second;
    SceneUser *pUser = GameService::getMe().getSceneUserMgr().getUserBySessID(element->dwTempID);
    if (pUser)
      myname = pUser->name;
    else
    {
      sprintf(buf,"��ʱID:%u",element->dwTempID);
      myname = buf;
    }
    Channel::sendSys((SceneUser *)entry,Cmd::INFO_TYPE_SYS,"����:%u ����:%u ״̬���:%u %s ʣ��ʱ��:%u ������:%s ����:%u ��ʱ��:%u ״ֵ̬%u ��Чֵ:%u",element->dwSkillID,element->byMutexType,element->id,element->byGoodnessType==1?"�˺�":"��ƽ",element->dwTime,myname.c_str(),element->percent,element->dwTime,element->value,element->state);
  }
  Channel::sendSys((SceneUser *)entry,Cmd::INFO_TYPE_SYS,"----------------------------------------------");
}

/**
 * \brief  ��ʾ��ɫ���ϵ���ʱ��������״̬
 */
void SkillStatusManager::showRecovery()
{
  std::map<DWORD,SkillStatusElement>::iterator tIterator;
  SkillStatusElement *element;

  Channel::sendSys((SceneUser *)entry,Cmd::INFO_TYPE_SYS,"��ɫ���ϵ���ʱ����״̬�б�:");
  for(tIterator = _recoveryElement.begin() ; tIterator !=_recoveryElement.end(); tIterator++)
  {
    std::string myname;
    char buf [45];
    element = &tIterator->second;
    SceneUser *pUser = GameService::getMe().getSceneUserMgr().getUserBySessID(element->dwTempID);
    if (pUser)
      myname = pUser->name;
    else
    {
      sprintf(buf,"��ʱID:%u",element->dwTempID);
      myname = buf;
    }
    Channel::sendSys((SceneUser *)entry,Cmd::INFO_TYPE_SYS,"����:%u ����:%u ״̬���:%u %s ʣ��ʱ��:%u ������:%s ����:%u ��ʱ��:%u ״ֵ̬%u ��Чֵ:%u",element->dwSkillID,element->byMutexType,element->id,element->byGoodnessType==1?"�˺�":"��ƽ",element->dwTime,myname.c_str(),element->percent,element->dwTime,element->value,element->state);
  }
  Channel::sendSys((SceneUser *)entry,Cmd::INFO_TYPE_SYS,"----------------------------------------------");
}

/**
 * \brief  ��ʾ��ɫ���ϵ����ñ�������״̬
 */
void SkillStatusManager::showPassiveness()
{
  std::map<DWORD,SkillStatusElement>::iterator tIterator;
  SkillStatusElement *element;

  Channel::sendSys((SceneUser *)entry,Cmd::INFO_TYPE_SYS,"��ɫ���ϵ����ñ���״̬�б�:");
  for(tIterator = _passivenessElement.begin() ; tIterator !=_passivenessElement.end(); tIterator++)
  {
    std::string myname;
    char buf [45];
    element = &tIterator->second;
    SceneUser *pUser = GameService::getMe().getSceneUserMgr().getUserBySessID(element->dwTempID);
    if (pUser)
      myname = pUser->name;
    else
    {
      sprintf(buf,"��ʱID:%u",element->dwTempID);
      myname = buf;
    }
    Channel::sendSys((SceneUser *)entry,Cmd::INFO_TYPE_SYS,"����:%u ����:%u ״̬���:%u %s ʣ��ʱ��:%u ������:%s ����:%u ��ʱ��:%u ״ֵ̬%u ��Чֵ:%u",element->dwSkillID,element->byMutexType,element->id,element->byGoodnessType==1?"�˺�":"��ƽ",element->dwTime,myname.c_str(),element->percent,element->dwTime,element->value,element->state);
  }
  Channel::sendSys((SceneUser *)entry,Cmd::INFO_TYPE_SYS,"----------------------------------------------");
}

/**
 * \brief  ��õ�ǰ��ɫ��Я���ļ���״̬��Ŀ
 */
WORD SkillStatusManager::getSaveStatusSize()
{
  WORD ret =0;

  ret = _recoveryElement.size()+_activeElement.size();
  return ret; 
}

/**
* \brief sky ϵͳΪ�û�����һ��״̬����ʱ����״̬��������
*/
void SkillStatusManager::SetStatuToRecovery(DWORD id, DWORD time, DWORD percent, DWORD value, DWORD state)
{
	SkillStatusElement element;
	element.byStep  =  ACTION_STEP_START;
	element.id    =  id;
	element.percent =  percent;
	element.value  =  value;
	element.state  =  state;

	element.dwSkillID = 0;
	element.dwTime = time;
	element.qwTime = H::timeTick->getMilliTime()+element.dwTime *1000;
	

	switch(runStatusElement(element))
	{
	case SKILL_RECOVERY:
		{
#ifdef _DEBUG
			H::logger->debug("[��ʱ����]��[%u]��״̬��ʩ�������ϳ���ʱ��Ϊ[%u]",element.id,element.dwTime);
			Channel::sendSys(entry->tempid,Cmd::INFO_TYPE_SYS,"[��ʱ����]��[%u]��״̬��ʩ�������ϳ���ʱ��Ϊ[%u]",element.id,element.dwTime);
#endif
			element.qwTime = H::timeTick->getMilliTime()+element.dwTime *1000;
			if (element.state >0)
			{
				clearMapElement(element.id/*element.byMutexType*/,_recoveryElement,element.id,false);
				_recoveryElement[element.id/*element.byMutexType*/]=element;
				sendSelectStates(entry,element.state,element.value,element.dwTime);
				//entry->setEffectStatus(element.state);
				entry->showCurrentEffect(element.state,true);
			}
			else
			{
				clearMapElement(element.id/*element.byMutexType*/,_recoveryElement,element.id);
				_recoveryElement[element.id/*element.byMutexType*/]=element;
			}
		}
		break;
	case SKILL_BREAK:
		{
			return;
		}
		break;
	case SKILL_ACTIVE:
		{
#ifdef _DEBUG
			H::logger->debug("[�˺�״̬]��[%u]��״̬��ʩ�������ϳ���ʱ��Ϊ[%u]",element.id,element.dwTime);
			Channel::sendSys(entry->tempid,Cmd::INFO_TYPE_SYS,"[����״̬]��[%u]��״̬��ʩ�������ϳ���ʱ��Ϊ[%u]",element.id,element.dwTime);
#endif
			if (element.dwTime==0) break;
			clearMapElement(element.id/*element.byMutexType*/,_activeElement,element.id);
			_activeElement[element.id/*element.byMutexType*/]=element;
			if (element.state >0)
			{
				sendSelectStates(entry,element.state,element.value,element.dwTime);
				//entry->setEffectStatus(element.state);
				//entry->showCurrentEffect(element.state,true);
			}
		}
		break;
	case SKILL_RETURN:
	default:
		break;
	}

	Channel::sendSys(entry->tempid,Cmd::INFO_TYPE_SYS,"[������״̬]֮[%u]��״̬��ʩ��������",element.id);
}
