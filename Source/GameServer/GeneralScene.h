#ifndef __GENERAL_SCENE_H_
#define __GENERAL_SCENE_H_

#include "Base.h"
#include "ScenesServer.h"

class Scene;

/*-------------------------------------------------------------------
 * @Brief : ��ͨ�ĵ�ͼ�������糣�õ���Ϸ�е���ͼ��ͼ������ʵ����ͼ
 *          ��ͼ�����г��ù���
 * @Author:hzd 2015:11:9
 *------------------------------------------------------------------*/

class GeneralScene : public BaseScene, public zEntry
{
public:
	
	/*-------------------------------------------------------------------
	 * @Brief : ��ͨ�����������������ҹ��еģ�һ������ֻ��һ�������ĳ���
	 *			Scene����Ϸ����ʱ���Ѿ�������
	 * @Author:hzd 2015:11:9
	 *------------------------------------------------------------------*/
	GeneralScene(Scene* _scene);
	~GeneralScene(void);

	virtual bool CheckEnter(const stEnterSceneParam& param) { return true; };
	virtual void OnUserEnter(SceneUser* pUser) {};
	virtual void OnUserLeave(SceneUser* pUser) {};


public:

	Scene* scene;
	
};


/*
 *	��Ҫ��ͨ��������̬������ÿ��mapid������Ϸ�н���һ����ͼ��
 */
class GeneralSceneMgr : public zEntryMgr< zEntryID, zMultiEntryName >
{
protected:

	bool getUniqeID(QWORD& tempid);
	void putUniqeID(const QWORD& tempid);
	GeneralSceneMgr();
	virtual ~GeneralSceneMgr();
	static GeneralSceneMgr *ins;

public:

	void CreateAllScene();
	GeneralScene* CreateScene(int32 mapID);
	GeneralScene* CreateObj(Scene* scene);
	void DestroyObj(GeneralScene* obj);
	static GeneralSceneMgr &getMe();
	static void destroyMe();

	bool AddGeneralScene(GeneralScene* generalScene);

	GeneralScene* getInsSceneByID(int32 id);
	GeneralScene* getInsSceneByTempID(int32 tempid);

	void Update(DWORD nSrvTimes);

private:

	zMutex mlock;
	ObjPool<GeneralScene> objpool;
};

#endif


