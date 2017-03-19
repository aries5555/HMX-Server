#ifndef __Net_SERVER_H_
#define __Net_SERVER_H_

#include "NetSocket.h"

/*-------------------------------------------------------------------
* @Brief : Socket��������װ��
*
* @Author:hzd 2012/04/03
*------------------------------------------------------------------*/
class NetServer : public io_service
{
public:

	/*
	 *
	 *	Detail: �����·�����
	 *  @param ���������
	 *  @param ����յ�������С
	 *  @param ���һ�η��ʹ�С(1+��)
	 *  @param �����ջ����С
	 *  @param ����ͻ����С
	 *  Created by hzd 2012/04/03
	 *
	 */
	NetServer(int32 nMaxConnected, int32 nMaxRecivedSize = 10 * 1024, int32 nMaxSendoutSize = 10 * 1024, int32 nMaxRecivedCacheSize = 64 * 1024, int32 nMaxSendoutCacheSize = 64 * 1024);
	virtual ~NetServer();

	/*
	 *
	 *	Detail: ��ñ�ʶID
	 *
	 *  Created by hzd 2013/01/23
	 *
	 */
	int32 SID();

	/*
	 *
	 *	Detail: �����������ַ������˿�
	 *
	 *  Created by hzd 2013/01/23
	 *
	 */
	void SetAddress(const char* pIp, uint16 pPort);

	/*
	 *
	 *	Detail: ��ʱ�Ͽ�ʱ��(��)
	 *
	 *  Created by hzd 2013-6-2
	 *
	 */
	void SetTimeout(int32 nTimeout);

	/*
	 *
	 *	Detail: ����Socket�¼��ص�(���û��ָ����������Ĭ�ϻص�������ʹ�ü̳л�ûص�)
	 *
	 *  Created by hzd 2013/01/23
	 *
	 */
	void SetHandler(PNetServerEnterHandler pEnter, PNetServerOnMsgHandler pMsg, PNetServerExistHandler pExit);


	/*
	 *
	 *	Detail: ��������
	 *
	 *  Created by hzd 2013/01/23
	 *
	 */
	void Start();

	/*
	 *
	 *	Detail: ֹͣ����
	 *
	 *  Created by hzd 2013/01/23
	 *
	 */
	void Stop();

	/*
	 *
	 *	Detail: ��Socket�������¹���
	 *
	 *  Created by hzd 2013/01/23
	 *
	 */
	void SetAccept(NetSocket& pSocket);

	/*
	 *
	 *	Detail: ��Ϣ����
	 *
	 *  Created by hzd 2013/01/23
	 *
	 */
	void OnUpdate();

	/*
	 *
	 *	Detail: ���Socket
	 *
	 *  Created by hzd 2013/01/23
	 *
	 */
	NetSocket& GetSocket(int32 nIndex);

	/*
	 *
	 *	Detail: �Ѿ�������Socket����
	 *
	 *  Created by hzd 2013-4-16
	 *
	 */
	size_t ConnectedSockets();

	/*
	 *
	 *	Detail: �ڽ��н��ܵ�Socket����
	 *
	 *  Created by hzd 2013-4-16
	 *
	 */
	size_t AcceptingSockets();

	/*
	*
	*	Detail: ����������ӵ�socket
	*
	*  Created by hzd 2013-4-16
	*
	*/
	NetSocket* getAcceptSocket(int64 socketid);

	/*
	*
	*	Detail: �������ʹ�õ�socket
	*
	*  Created by hzd 2013-4-16
	*
	*/
	NetSocket* getUsedSocket(int64 socketid);

	/*
	 * ������ڵȴ����ӵ�socket 
	 */
	SocketMap&	getSetAccepts() { return m_setAcceptSocket; }

private:

	/*
	 *
	 *	Detail: IOѭ������
	 *
	 *  Created by hzd 2013/01/23
	 *
	 */
	void Run();

	/*
	 *
	 *	Detail: �����пͻ��������¼�������
	 *
	 *  Created by hzd 2013/01/23
	 *
	 */
	void HandleStart();

	/*
	 *
	 *	Detail: ���ӻص�
	 *
	 *  Created by hzd 2013/01/23
	 *
	 */
	void HandleAccept(const boost::system::error_code& error, NetSocket* socket);

	/*
	 *
	 *	Detail: �����������
	 *
	 * Copyright (c) Created by hzd 2013-4-25.All rights reserved
	 *
	 */
	void OnUpdateAccept();

	/*
	 *
	 *	Detail: ��������ϢSocket
	 *
	 * Copyright (c) Created by hzd 2013-4-25.All rights reserved
	 *
	 */
	void OnUpdateRecived();

private:

	int32			m_nMaxConnected;			// ���Socket������ < 65536 
	int32			m_nServerID;				// ��������ʶΨһID  

	SocketMap		m_setAcceptSocket;			// �������ӵ�socket
	SocketMap		m_mapUsedSocket;			// ʹ���е�Socket  
	SocketMap		m_mapAcceptSocket;			// �����е�Socket  

	NetSocket*		m_arrSocket[1000];			// ���е�Scoket 

	tcp::endpoint   m_cServerAddr;				// �����ַ�� 
	tcp::acceptor   m_cAcceptor;				// ���ӹ����� 

	PNetServerEnterHandler		m_pOnEnter;		// ���ӻص� 
	PNetServerOnMsgHandler		m_pOnMsg;		// ��Ϣ�ص� 
	PNetServerExistHandler		m_pOnExit;		// �Ͽ��ص� 

	boost::thread  m_cServiceThread;
	boost::mutex   m_cClientListMutex;

};


#endif





