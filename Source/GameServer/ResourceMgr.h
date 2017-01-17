#ifndef __WS_RESOURCE_MGR_HEADER__
#define __WS_RESOURCE_MGR_HEADER__

#include "Includes.h"

typedef std::map<int32,StMapInfoResCfg>			MapInfoResMapType;
typedef std::map<int32,StMapZoneResCfg>			MapZoneResMapType;
typedef std::map<int32,StMapSceneResCfg>		MapSceneResMapType;
typedef std::map<int32,StCharacterLevelCfg>		CharacterLevelMapType;
typedef std::map<int32,StRoleTypeInitCfg>		RoleTypeInitMapType;
typedef std::map<int32,StQuestInfoResCfg>		QuestResMapType;

class ResourceMgr  : public Single<ResourceMgr> 
{
public:

	ResourceMgr();
	~ResourceMgr();

	// ����������Դ�ļ� 
	bool LoadAllResources();


	const StCharacterLevelCfg* GetCharacterLevelBase(int32 nRoleType,int32 nLevel);

	const StRoleTypeInitCfg* GetRoleTypeInitInfoRes(int32 nRoleType);

	const StMapInfoResCfg* GetMapInfoCfg(int32 nMapID);

	const StMapZoneResCfg* GetMapZoneRes(int32 nMapID);

private:

	//------------------------��Դ���غ���-----------------------------------------

	/*------------------------------------------------
	 * ���ؽ�ɫ�ȼ�
	 *-----------------------------------------------*/
	bool LoadCharLevelResource(const std::string& strFileName);

	/*------------------------------------------------
	 * ���ص�ͼ�ļ� 
	 *-----------------------------------------------*/
	bool LoadMapInfoResource(const std::string& strFileName);

	/*------------------------------------------------------------------
	 * ���ش�����ɫ����Դ
	 *-----------------------------------------------------------------*/
	bool LoadCharTypeResource(const std::string& strFileName);

	/*------------------------------------------------
	 * ���ص�ͼ������Դ 
	 *-----------------------------------------------*/
	bool LoadZoneRes(int32 nMapId,const std::string& strFileName);

	/*------------------------------------------------
	 * ���ص�ͼ�赲��Դ
	 *-----------------------------------------------*/
	bool LoadMapRes(int32 nMapId,const std::string& strFileName);

	/*-------------------------------------------------------------------
	 * @Brief : �������� 
	 * 
	 * @Author:hzd 2015:11:26
	 *------------------------------------------------------------------*/
	bool LoadQuestResource(const std::string& strFileName);

	/* ������� */ 
	bool LoadNpcBaseResource(const std::string& strFileName);

	/* ��Ʒ�� */
	bool LoadItemResource(const std::string& strFileName);

	/* �̳Ǳ� */ 
	bool LoadShopResource(const std::string& strFileName);

	/* ���ؼ��� */ 
	bool LoadSkillResource(const std::string& strFileName);
	
private:


	//------------------------��Դ���ݶ���-------------------------------



	RoleTypeInitMapType		m_mapRoleTypeInitInfo;	// ��ɫ���ͳ�ʼ����Ϣ 
	

	// ��ͼ��Դ����Serverֻ�����ȡ�������ļ�����WS֪ͨ�Һ�Ž��д�����ͼ���ȴ���ɺ� 
	// һ����Server��¼�ɹ���WS�ͻ�֪ͨ��������ͼ 
	MapInfoResMapType		m_mapMapInfo;					// ��ͼ��Ϣ��Դ(��ws֪ͨ�����) 
	MapZoneResMapType		m_mapZoneInfo;					// ��ͼ������Դ 
	MapSceneResMapType		m_mapSceneInfo;					// ��ͼ�赲��Դ 


	CharacterLevelMapType	m_mapCharacterLevelBase;		// ��ɫ�ȼ�������Դ 

	QuestResMapType			m_mapQuestResInfo;				// ������Դ(����ǰ���Լ�����)  

};

#define g_cResourceMgr ResourceMgr::get_instance()

#endif
