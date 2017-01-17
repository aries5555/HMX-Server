#ifndef __OBJECT_MANAGER_H_
#define __OBJECT_MANAGER_H_

#include "ScenesServer.h"
#include "character.pb.h" 

struct qObject;
class SceneUser;



/* ���������� */
class ObjectManager : protected zItemManager
{

public:
	ObjectManager(SceneUser* _u);
	~ObjectManager();

	bool Serialize(::protobuf::Itemslots& proto);
	void UnSerialize(const ::protobuf::Itemslots& proto);

	qObject* CreateObj(zItemB* base);
	void DestroyObj(qObject* obj);

	qObject* getObjectByUUID(DWORD uniqueID);

	/* ��λ���±꣬���ң����Զ�λ��ĳЩ������λ�� */
	qObject* getByIndex(DWORD id);

	bool addObject(qObject* obj);
	void removeObject(qObject* obj);
	void removeAllObject();
	template <class YourNpcEntry>
	bool execEveryObject(execEntry<YourNpcEntry> &exec)
	{
		rwlock.rdlock();
		bool ret = execEveryItemEntry<>(exec);
		rwlock.unlock();
		return ret;
	}

	bool getUniqeID(QWORD& tempid);
	void putUniqeID(const QWORD& tempid);

	int32 getCapacity()
	{
		return nCapacity;
	}

	int32 getUseCapacity()
	{
		return nUseCapacity;
	}

private:

	SceneUser* u;
	ObjPool<qObject> objpool;

	int32 nCapacity;
	int32 nUseCapacity;
};




#endif


