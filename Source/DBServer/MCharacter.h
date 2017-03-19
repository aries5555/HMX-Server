#ifndef __MUSER_H_
#define __MUSER_H_

#include "Includes.h"
#include "Memory.h"
#include "Collection.h"

#pragma pack(push,1)

struct DUser
{
	int64 id;
	int8 state;
	int64 accid;
	char name[MAX_NAMESIZE + 1];
	int8 status;
	int16 level;
	int64 sceneid;
	int32 mapid;
	int32 size;
};

struct DRelation
{
	int64 id;
	int8 state;
	int64 myuid;
	int64 friuid;
	int32 rel;
	int32 createtime;
	int32 dealreltime;
};

struct DUserRecord
{
	int64 uid;
	int32 size;
	BinaryHeader header;
};

#pragma pack(pop)


/*
	�ڴ���������Զ������ݿ��ȡ���Զ����µ����ݣ�֧�����֧������key�ṹ����(key1=>key2=>value)
	�ر�ע���ǣ��ڴ�ṹ��ȡ��Ҫ�ϸ񰴵�һ�η��������У�����ݵ�һ���������ֲ�ṹ��
	��һ��:get(),put()
	�ڶ���:getMap(); putMap();
	����ͬһ������������ͬʱ�ã�ֻ��ʹ������һ��
 */
class MCharacter : public Single<MCharacter>
{
public:

	DUser* getUser(int64 uid);
	DWORD getBinary(int64 uid, char* out);

	void getRelation(int64 uid, std::vector<DRelation*>& relList);
	DRelation* getReltion(int64 uid,int64 id);
	void putRelation(int64 uid, int64 id, DRelation* rel);

	int32 writeBinary(char* out);
	int32 readBinary(const char* data,const int size);
	
private:

	DCollection<DUser>& getUserCollection();
	DCollection<DRelation>& getRelationCollection();

private:

	bool isInited;

};

#endif


