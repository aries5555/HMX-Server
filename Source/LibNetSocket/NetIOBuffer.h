
/*
 *
 *	Detail: IOBuffer
 *   
 *  Copyright (c) Created by hzd 2012. All rights reserved.
 *
 */

#ifndef _NET_IOBUFFER_H_
#define _NET_IOBUFFER_H_

#include "NetConfig.h"

class NetIOBuffer
{
public:

	NetIOBuffer();
	~NetIOBuffer();

	/*
	 *
	 *	Detail: no
	 *   
	 *  Created by hzd 2015/05/31  
	 *
	 */
	void InitBuffer(int32 nMax);

	/*
	 *
	 *	Detail: no
	 *   
	 *  Created by hzd 2015/05/31  
	 *
	 */
	void ReleaseBuffer();

	/*
	 *
	 *	Detail: no
	 *   
	 *  Created by hzd 2015/05/31  
	 *
	 */
	bool Write(char* c, int32 nLen);

	/*
	 *
	 *	Detail: no
	 *   
	 *  Created by hzd 2015/05/31  
	 *
	 */
	void Read(void** b, int32 nLen);

	/*
	 *
	 *	Detail: no
	 *   
	 *  Created by hzd 2015/05/31  
	 *
	 */
	int32 ReadRemove(void* pMsg, int32 nLen);

	/*
	 *
	 *	Detail: no
	 *   
	 *  Created by hzd 2015/05/31  
	 *
	 */
	void RemoveBuffer(int32 nLen);

	/*
	 *
	 *	Detail: no
	 *   
	 *  Created by hzd 2015/05/31  
	 *
	 */
	int32 GetLen();

	/*
	 *
	 *	Detail: no
	 *   
	 *  Created by hzd 2015/05/31  
	 *
	 */
	int32 GetSpace();

	/*
	 *
	 *	Detail: no
	 *   
	 *  Created by hzd 2015/05/31  
	 *
	 */
	void* GetBuffer();

	/*
	 *
	 *	Detail: no
	 *   
	 *  Created by hzd 2015/05/31  
	 *
	 */
	void* GetStart();

	/*
	 *
	 *	Detail: no
	 *   
	 *  Created by hzd 2015/05/31  
	 *
	 */
	void* GetBufferEnd();

	/*
	 *
	 *	Detail: no
	 *   
	 *  Created by hzd 2015/05/31  
	 *
	 */
	void ClearBuffer();

	/*
	 *
	 *	Detail: no
	 *   
	 *  Created by hzd 2015/05/31  
	 *
	 */
	void MoveBuffer();

protected:

	boost::mutex m_cMutex;		// ��/д�� 
	int32 m_nBegin;       // ��һ�ζ�/д��λ�� 
	int32 m_nLen;			// �Ѿ��������ݳ���(�����ж����)  
	char* m_pBuffer;		// �ֶ�����  
	char* m_pBuffer2;		// �ֶ�����2 
	int32 m_nMax;         // ����ֶγ���  

};

#endif



