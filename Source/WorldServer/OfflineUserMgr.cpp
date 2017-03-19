#include "WorldServer_PCH.h"
#include "OfflineUserMgr.h"

#include "SceneRegMgr.h"


OfflineUserMgr::OfflineUserMgr()
{

}

OfflineUserMgr::~OfflineUserMgr()
{

}

bool OfflineUserMgr::getUniqeID(QWORD& tempid)
{
	return true;
}

void OfflineUserMgr::putUniqeID(const QWORD& tempid)
{
}

OfflineUser* OfflineUserMgr::CreateObj()
{
	return objpool.CreateObj();
}

void OfflineUserMgr::DestroyObj(OfflineUser* user)
{
	objpool.DestroyObj(user);
}

void OfflineUserMgr::loadDB()
{

	const dbCol user_id[] =
	{
		{"ID",DB_QWORD,sizeof(QWORD)},
		{NULL,0,0},
	};

#pragma pack(push,1)
	struct dbUserID
	{
		QWORD id;
	};
#pragma pack(pop)

	dbUserID* dataList, *dataTmp;
	int ret = GameService::getMe().getDbMysql()->ExecSelect("USER", user_id, NULL, NULL, (unsigned char**)&dataList);
	if (ret > 0)
	{
		int usercount = 0;
		int failcount = 0;
		for (int c = 0; c < ret; ++c)
		{
			dataTmp = &dataList[c];
			OfflineUser* user = CreateObj();
			user->id = dataTmp->id;
			if (user->loadDB() && addUser(user))
			{
				usercount++;
			}
			else
			{
				failcount++;
				H::logger->error("���ؽ�ɫʧ��[ID:%lld]",user->id);
				removeUser(user);
			}
		}

		SAFE_DELETE_VEC(dataList);
		H::logger->info("��%d�����ݣ��ɹ�����%d��,ʧ��%d��",ret,usercount,failcount);

	}
}