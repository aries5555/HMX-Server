#ifndef __CREATURE_MANAGER_H
#define __CREATURE_MANAGER_H

#include "SceneEntryPk.h"
#include "UnorderedSet.h"
#include "Single.h"
#include "srvEngine.h"

#include "SceneNpc.h"


class SceneNpcManager : public Single<SceneNpcManager>
{
	typedef UNORDERED_SET<SceneNpc*> CreatureUSetType;
public:
	SceneNpcManager();
	~SceneNpcManager();
	
	// ��������� 
	void AddCreature(SceneNpc& rCreature);

	// ��������ʧ 
	void DelCreature(SceneNpc& rCreature);

	// ����(nTimeElapse��λ:����) 
	void Update(int32 nTimeElapse);

private:
	
	CreatureUSetType	m_usetCreaturies;			// �������������� 

};

#endif
