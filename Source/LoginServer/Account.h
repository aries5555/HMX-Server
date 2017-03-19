#ifndef __ACCOUNT_H_
#define __ACCOUNT_H_
#include "SrvEngine.h"

namespace acc
{

	enum 
	{
		TYPE_5_MIN = 1,	// 5����	
		TYPE_10_MIN,	// 10����
		TYPE_20_MIN,	// 10����
		TYPE_30_MIN,	// 60����
		TYPE_1_HOUR,	// 1Сʱ
		TYPE_1_DAY,		// 1��
	};

#pragma pack(push,1)

	const dbCol Id[] =
	{
		{ "ID",DB_QWORD,sizeof(QWORD) },
		{ NULL,0,0 },
	};

	const dbCol fields[] =
	{
		{ "ID",DB_QWORD,sizeof(int64) },
		{ "USERNAME",DB_STR,MAX_NAMESIZE + 1 },
		{ "PASSWORD",DB_STR,MAX_NAMESIZE + 1 },
		{ "CREATETIME",DB_DWORD,sizeof(int32) },
		{ "LASTLOGIN",DB_DWORD,sizeof(int32) },
		{ "STATE",DB_BYTE,sizeof(int8) },
		{ "TYPE",DB_BYTE,sizeof(int8) },
		{ "INFO",DB_BIN2, 0 },
		{ NULL,0,0 }
	};


	struct dbID
	{
		QWORD id;
	};

	struct Base
	{
		int64 id;
		char username[MAX_NAMESIZE + 1];
		char password[MAX_NAMESIZE + 1];
		int8 state;//0����ʹ��,1...����ԭ������
		int8 type; //0��ͨ�ʺ�,1��ʱ5,2��ʱ10,3��ʱ30,4��ʱ60,5��ʱ24,6�賿3��
		int32 createtime;
		int32 lastlogin;
	};

	struct Record
	{
		Base base;
		int32 size;
		BinaryHeader header;
	};

#pragma pack(pop)

}


class Account : public zEntry
{
public:
	Account();
	~Account();
	bool loadDB();
	void saveDB();
	void readBinary(const char* data, int32 len);
	int32 writeBinary(char* data);
	void timer();

public:
	char password[MAX_NAMESIZE + 1];
	int32 createtime;
	int32 lastlogin;
};



#endif




