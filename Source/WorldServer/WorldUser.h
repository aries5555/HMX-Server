#ifndef __WORLD_USER_H_
#define __WORLD_USER_H_

#include "Config.h"

/*

  ��̬���������û���
	
 */

// id=uid,tempid=sessid,name=nick
class WorldUser : public zEntrysessid
{
public:
	WorldUser();
	~WorldUser();
	void sendToFep(NetMsgSS* pMsg, int32 nSize);
	void sendToSs(NetMsgSS* pMsg, int32 nSize);

public:

	zSession* fepSession;
	zSession* sceneSession;

public:

	int64 sceneid;
	int32 mapid;
	int16 level;
	int32 enterscenetime; // ������л�����ʱ�� 

};


#endif

