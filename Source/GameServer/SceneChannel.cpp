#include "SceneChannel.h"


zObjPool<SceneChannel(ChannelPosition)>	g_cPositionChannelFactory;
zObjPool<SceneChannel(ChannelCreature)>	g_cCreatureChannelFactory;
zObjPool<SceneChannel(ChannelWear)>		g_cEquipmentChannelFactory;	
zObjPool<SceneChannel(ChannelSpell)>		g_cSpellChannelFactory;
zObjPool<SceneChannel(ChannelBuff)>		g_cBuffChannelFactory;

// ����Ƶ�� 
void SceneChannelManager::AddSceneChannel(ChannelEx& rChannel)
{
	m_usetChannels.insert(&rChannel);
}

// ��������Ƶ�� 
void SceneChannelManager::Update()
{
	UNORDERED_SET<ChannelEx*>::iterator it = m_usetChannels.begin();
	UNORDERED_SET<ChannelEx*>::iterator itEnd = m_usetChannels.end();
	for (;it != itEnd; ++it)
	{
		ChannelEx* pTemp = *it;
		pTemp->Update();
	}
}



