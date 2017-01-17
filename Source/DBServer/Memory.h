#ifndef __DATABSE_MANAGER_H_
#define __DATABSE_MANAGER_H_

#include "Includes.h"
#include "Collection.h" 

namespace dbmem
{
	// �ڴ������,������=>�����µ������ڴ�
	class Memory : protected zEntryMgr<zEntryName>
	{
	public:
		Memory(const char* _name);
		~Memory();

		template<typename TData>
		inline DCollection<TData>& getCollection(const string& collectionName, const dbCol* dbCol, const char* collectionKey)
		{
			return getCollection<TData>(collectionName.c_str(),dbCol,collectionKey);
		}

		template<typename TData>
		inline DCollection<TData>& getCollection(const char* collectionName,const dbCol* dbCol, const char* collectionKey)
		{
			DCollection<TData>* collectionObj = (DCollection<TData>*)zEntryMgr::getEntryByName(collectionName);
			if (collectionObj == NULL)
			{
				collectionObj = CreateObj<TData>(collectionName,dbCol,collectionKey);
				ASSERT(collectionObj); // ���ﲻ�����ڴ治����� 
			}
			return *collectionObj;
		}

		inline void setDB(IDbBase* _db)
		{
			dbConn = _db;
		}

		inline IDbBase* getDB()
		{
			return dbConn;
		}

	private:

		template<typename TData>
		inline DCollection<TData>* CreateObj(const char* collectionName, const dbCol* dbCol, const char* collectionKey)
		{
			DCollection<TData>* obj = new DCollection<TData>(dbConn, collectionName, dbCol, collectionKey);
			strncpy(obj->name, collectionName, MAX_NAMESIZE);
			if (!zEntryMgr::addEntry(obj))
			{
				S_SAFE_DELETE(obj);
				return NULL;
			}
			return obj;
		}

	private:

		char name[MAX_NAMESIZE + 1];

		IDbBase* dbConn;

	public:

		static Memory data;
		static Memory log;

	};
}


#endif // !__DATABSE_MANAGER_H_




