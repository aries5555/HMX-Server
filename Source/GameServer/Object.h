#ifndef __OBJECT_H_
#define __OBJECT_H_

#include "ScenesServer.h"


/* �������� */
struct qObject : public zItemEntry
{
	qObject(zItemB* _base) :base(_base)
	{
		nLock = 0;
	}

	zItemB* base;
	int8 nLock;
};



#endif



