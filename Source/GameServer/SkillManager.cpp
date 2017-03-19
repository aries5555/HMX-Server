#include "ScenesServer.h"



bool UserSkillM::getUniqeID(QWORD &tempid)
{
	return true;
}

void UserSkillM::putUniqeID(const QWORD &tempid)
{
}

UserSkillM::UserSkillM(SceneUser* u):pOwner(u)
{

}


UserSkillM::~UserSkillM()
{
  for(zEntryTempID::hashmap::iterator it=zEntryTempID::ets.begin();it!=zEntryTempID::ets.end();it++)
  {
    zSkill *skill = (zSkill *)it->second;
    SAFE_DELETE(skill);
  }
}


zSkill *UserSkillM::getSkillByTempID(DWORD id)
{
  return (zSkill *)getEntryByTempID(id);
}


void UserSkillM::removeSkillByTempID(DWORD id)
{
  zEntry *e=getEntryByTempID(id);
  if (e)
    removeEntry(e);
}


void UserSkillM::removeSkill(zSkill *s)
{
  removeEntry(s);
}


bool UserSkillM::addSkill(zSkill *s)
{
  bool bret = false;
  if (s)
  {
    zSkill *ret = (zSkill *)getEntryByTempID(s->id);
    if (ret)
    {
      H::logger->debug("����ID�ظ�(%ld)",s->id);
    }

    bret = addEntry((zSkill *)s);
    if (!bret)
    {
      H::logger->fatal("��Ӽ��ܱ�ʧ��");
    }
  }

  return bret;
}


zSkill *UserSkillM::findSkill(DWORD skillid)
{
  //zSkill *s;
  //for(zEntryTempID::hashmap::iterator it=zEntryTempID::ets.begin();it!=zEntryTempID::ets.end();it++)
  //{
  //  s = (zSkill *)it->second;
  //  if (s->data.skillid == skillid)
  //  {
  //    return (zSkill *)it->second;
  //  }
  //}
  //return NULL;
  return (zSkill *)getEntryByTempID(skillid);
}


DWORD UserSkillM::getPointInTree(DWORD mySubkind)
{
  zSkill *s;
  DWORD num=0;
  for(zEntryTempID::hashmap::iterator it=zEntryTempID::ets.begin();it!=zEntryTempID::ets.end();it++)
  {
    s = (zSkill *)it->second;

	////sky �жϼ��ܵ���ϵ�Ƿ��Ҫѧ�ļ��ܵ���ϵһ��
 //   if ((s->base->subkind == mySubkind)) 
	//	num+=s->base->level;  //sky �ǵľͰѸ�ϵ�ĵ�����1
  }

  return num;
}


void UserSkillM::execEvery(UserSkillExec &exec)
{
  for(zEntryTempID::hashmap::iterator it=zEntryTempID::ets.begin();it!=zEntryTempID::ets.end();it++)
  {
    if (!exec.exec((zSkill *)it->second))
      return;
  }
}

/**
 * \brief  ������û����еļ�����ȴʱ��
 */
void UserSkillM::resetAllUseTime()
{
  zSkill *s;
  for(zEntryTempID::hashmap::iterator it=zEntryTempID::ets.begin();it!=zEntryTempID::ets.end();it++)
  {
    s = (zSkill *)it->second;
    s->resetUseTime();
	s->refresh(true);
  }
}

/**
 * \brief  ������û����еļ�����ȴʱ��
 * \skillID �������֮�еļ���ID
 */
void UserSkillM::clearAllUseTime(DWORD skillID)
{
  zSkill *s;
  for(zEntryTempID::hashmap::iterator it=zEntryTempID::ets.begin();it!=zEntryTempID::ets.end();it++)
  {

	  s = (zSkill *)it->second;
	  if(s && s->base->id != skillID)
	  {
		  s->clearUseTime();
		  s->refresh(true);
	  }
  }
}

/**
 * \brief  ˢ�¼���(�����������ܵȼ�����������)
 */
void UserSkillM::refresh()
{
  zSkill *s;
  for(zEntryTempID::hashmap::iterator it=zEntryTempID::ets.begin();it!=zEntryTempID::ets.end();it++)
  {
    s = (zSkill *)it->second;
    s->refresh();
  }
}

void UserSkillM::clear()
{
	zEntryMgr::clear();
}

int UserSkillM::size() const
{
  return zEntryMgr::size();
}

/**
 * \brief  ���ݼ���id���Ҷ�Ӧ�ļ��ܶ���ɾ��
  * \return ���ܶ���
 */
void UserSkillM::clearskill(DWORD skillid)
{
	zEntryMgr::removeEntry(getEntryByTempID(skillid));
}
