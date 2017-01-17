#ifndef __INSTANCE_SCENE_H_
#define __INSTANCE_SCENE_H_

#include "Base.h"

class Scene;
class SceneUser;

/*-------------------------------------------------------------------
 * @Brief : �������������࣬���и�������Ҫ�̳и��� 
 * 
 * @Author:hzd 2015:11:9
 *------------------------------------------------------------------*/
class InstanceScene : public BaseScene
{
public:
	/*-------------------------------------------------------------------
	 * @Brief : ���������Ǹ������������ģ�һ��server�����N���������в�ͬ
	 *			����Ҽ������(��̬����)
	 * @Author:hzd 2015:11:9
	 *------------------------------------------------------------------*/
	InstanceScene(Scene* _scene);
	~InstanceScene(void);

	virtual bool CheckEnter(const stEnterSceneParam& param) { return true; };

	virtual void OnUserEnter(SceneUser* pUser) {};

	virtual void OnUserLeave(SceneUser* pUser) {};

public:

	/* �����ĳ�����ͼ */ 
	Scene* scene;

	std::map<int64,SceneUser*> allUsers;

};


/*
	
	���������� 

*/
class InstanceSceneMgr : public zEntryMgr< zEntryID >
{
protected:

	bool getUniqeID(QWORD& tempid);
	void putUniqeID(const QWORD& tempid);
	InstanceSceneMgr();
	virtual ~InstanceSceneMgr();
	static InstanceSceneMgr *ins;

public:

	InstanceScene* CreateObj(Scene* scene);
	void DestroyObj(InstanceScene* obj);
	static InstanceSceneMgr &getMe();
	static void destroyMe();

	InstanceScene* getInsSceneByID(int32 id);
	InstanceScene* getInsSceneByTempID(int32 tempid);

	void Update(DWORD nSrvTimes);

private:

	ObjPool<InstanceScene> objpool;

};



#endif

