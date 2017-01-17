#ifndef __SCENE_INFO_MANAGER_H_
#define __SCENE_INFO_MANAGER_H_

#include "Includes.h"
#include "Config.h"


/*-------------------------------------------------------------------
 * @Brief : �����¼����������Ϣ����¼��������WS��ע������Щ����ID
 *			ͬʱ
 * @Author:hzd 2015:11:18
 *------------------------------------------------------------------*/

/*
	������̬��Ϣ id=����ID 
*/
class SceneReg : public zEntry
{
public:
	SceneReg()
	{
		sessid = mapid = 0;
	}

public:
	int64 sessid;
	int32 mapid;

};


/*--
	���������� 
*/
class SceneRegMgr : protected zEntryMgr<zEntryID>,public Single<SceneRegMgr>
{
protected:
	friend class Single<SceneRegMgr>;
	SceneRegMgr();
	~SceneRegMgr();

public:

	SceneReg* CreateObj();
	void DestroyObj(SceneReg* obj);

	bool add(SceneReg* scene);
	void remove(SceneReg* scene);
	SceneReg* get(int64 id);
	SceneReg* getBymapid(int32 mapid);// ��õ�һ��scene(ͨ��Ҳֻ��һ��scene)
	SceneReg* getFreeBymapid(int32 mapid); // ��ñȽϿ��еĳ��� 

private:

	ObjPool<SceneReg> objpool;

};


#endif

