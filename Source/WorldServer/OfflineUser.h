#ifndef __OFFLINE_USER_H_
#define __OFFLINE_USER_H_

#include "Includes.h"
#include "character.pb.h"


/*
  ��̬���������û���
 */
class OfflineUser : public zEntry
{
public:
	OfflineUser();
	~OfflineUser();

	bool loadDB();

public:

	int16 level;
	int8 vip;
	int8 country;
	int32 teamid;

};

#endif

