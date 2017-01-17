#ifndef __NET_SOCKET_H_
#define __NET_SOCKET_H_


#include "NetIOBuffer.h"

/*
 *
 *	Detail: Socket �� 
 *
 *  Created by hzd 2013-1-1
 *
 */
enum ERecvType
{
	REVC_FSRS_NULL = 0,
	REVC_FSRS_HEAD,
	REVC_FSRS_BODY,
};
enum  EMsgRead
{
	MSG_READ_INVALID,
	MSG_READ_WAITTING,
	MSG_READ_OK,
	MSG_READ_REVCING,
};

// SCOKET �Ͽ�ԭ�� 
enum ESocketExist
{
	ESOCKET_EXIST_NULL = 0,				/* 0:�� */
	ESOCKET_EXIST_LOCAL,				/* 1:���������Ͽ�-------����˵�����SetWellColse */
	ESOCKET_EXIST_REMOTE,				/* 2:Զ�������Ͽ�-------�û�ֱ�� */
	ESOCKET_EXIST_TIMEOUT,				/* 3:��ʱ�Ͽ�-----------��ֵ���������������趨 */
	ESOCKET_EXIST_PACK_LENGTH_ERROR,	/* 4:��ͷ����ֵ�Ƿ�-----С��sizeof(NetMsgHead)��������ý���������С */
	ESOCKET_EXIST_WRITE_TOO_DATA,		/* 5:д�����ݵ�buffer��ʧ��--�յ������ݹ��࣬��������������ٶȹ����������趨��buffer����̫С */
	ESCOKET_EXIST_SEND_CONNECT_INVAILD, /* 6:��������ʱʧ��------����ʧЧ */
};

class NetSocket : public tcp::socket
{
	friend class NetServer;
	friend class NetClient;
public:
	NetSocket(io_service& rIo_service,int32 nMaxRecivedSize,int32 nMaxSendoutSize,int32 nMaxRecivedCacheSize,int32 nMaxSendoutCacheSize);
	virtual ~NetSocket();

	/*
	 *
	 *	Detail:  ���SocketID����0��ʼ���� 
	 *
	 */
	int32 SID() { return m_nID; }
	int64 SLongID() { return m_nLongID; }

	/*
	 *
	 *	Detail:  ѹ��Ҫ׼�����͵����� 
	 *
	 *
	 */
	void ParkMsg(const NetMsgSS* pMsg,int32 nLength);

	/*
	 *
	 *	Detail:  ѹ��Ҫ׼�����͵�����
	 *
	 *
	 */
	void ParkMsg(const NetMsgC* pMsg, int32 nLength);

	/*
	 *	Detail:  �������� 
	 *
	 */
	void SendMsg();

	/*
	 *
	 *	Detail:  ��ȡ�����е����� 
	 *
	 */
	EMsgRead ReadMsg(NetMsgSS** pMsg,int32& nSize);

	/*
	 *	Detail: �Ƴ������е����� 
	 *
	 */
	void RemoveMsg(uint32 nLen);

	/*
	 *	Detail: ����Socket�����Խ����շ����� 
	 */
	void Run();

	/*
	 *	Detail: ���Socket�ͻ���IP��ַ 
	 */
	const string GetIp();

	/*
	 * ��������Ķ˿� 
	 */
	uint16 GetPort();

	/*
	 *	Detail: ���ر�Socket(�����Ͽ��ͻ���) 
	 *
	 */
	void OnEventColse();

	/*
	 *
	 *	Detail: �����Ͽ� 
	 *
	 */
	void SetTimeout(int32 nTimeout);

	/*
	 *
	 *	Detail: ��ʱ���� 
	 *
	 */
	void TimeoutStart();

	/*
	 *	Detail: ��ʱ�ر� 
	 */
	void TimeoutCancel();

	/*
	 * 0:��
	 * 1:���������Ͽ�-------����˵�����SetWellColse
	 * 2:Զ�������Ͽ�-------�û�ֱ��
	 * 3:��ʱ�Ͽ�-----------��ֵ���������������趨
	 * 4:��ͷ����ֵ�Ƿ�-----С��sizeof(NetMsgHead)��������ý���������С 
	 * 5:д�����ݵ�buffer��ʧ��--�յ������ݹ��࣬��������������ٶȹ����������趨��buffer����̫С
	 * 6:��������ʱʧ��------����ʧЧ 
	 * @Author:hzd 2013:11:19
	 */
	int32 ErrorCode(std::string& error);

	/*
	 *	�ж϶���Ϣ������Ϊwarriting 
	 */
	void BreakUpdateIO();

	/*
	 *	ȥ���жϣ���read��Ϣ����waitting�� 
	 */
	void UnBreakUpdateIO(); 

	/*
	 * �����¼�������ر�socket
	 */ 
	void AddEventLocalClose();

	bool HadEventClose();

private:

	NetSocket();

	/*
	 *
	 *	Detail: �Ͽ� socket
	 *
	 *  Created by hzd 2013-1-21
	 *
	 */
	void Disconnect();

	/*
	 *
	 *	Detail: �ر� socket
	 *
	 *  Created by hzd 2013-1-21
	 *
	 */
	void HandleClose(const boost::system::error_code& error);
	
	/*
	 *
	 *	Detail: �ָ������캯������״̬ 
	 *
	 *  Created by hzd 2013-1-20
	 *
	 */
	void Clear();

	/*
	 *
	 *	Detail: �յ�ָ���������ݻص����� 
	 *
	 *  Created by hzd 2013-1-21
	 *
	 */
	void RecvMsg(const boost::system::error_code& ec, size_t bytes_transferred);

	/*
	 *
	 *	Detail: �������ݻص����������ͺ����������ݣ����ѡ��������ͣ�һ�㲻�ᷢ�����������
	 *
	 *  Created by hzd 2013-1-21
	 *
	 */
	void SendMsg(const boost::system::error_code& ec, size_t bytes_transferred);

	/*
	 *
	 *	Detail: ����Ϣͷ 
	 *
	 *  Created by hzd 2013-1-21
	 *
	 */
	void ReadHead();

	/*
	 *
	 *	Detail: ����Ϣ���� 
	 *
	 *  Created by hzd 2013-1-21
	 *
	 */
	void ReadBody();

	/*
	 *
	 *	Detail: ��ʱ�ص�����������ر� socket 
	 *
	 *  Created by hzd 2013-1-21
	 *
	 */
	void HandleWait(const boost::system::error_code& error);

private:

	int32				m_nID;				// socketID�� һ���������� Socket ΨһID��0��ʼ 
	int32				m_nIndexID;			// �Զ���ID, �����������±꣬������� 
	int64				m_nLongID;		
	int64				m_nLongIndexID;
	mutable_buffers_1	m_cHeadBuffer;		// �յ�ͷ���ݻ������ 
	mutable_buffers_1	m_cBodyBuffer;      // �յ����������ݰ��ڰ��� 
	mutable_buffers_1	m_cSendBuffer;      // ���͵����ݻ������ 

	deadline_timer		m_cTimer;			// �շ���ʱ�������ڼ���û����û���������ͨ�ţ�������ɫ HandleWait ���� 
	deadline_timer		m_cCloseTimer;		// �ر����Ӷ�ʱ�� 

	NetIOBuffer			m_cIBuffer;			// �����յ����ֽڹ�����  
	NetIOBuffer			m_cOBuffer;			// ���������ֽڹ����� 

	ERecvType			m_eRecvStage;
	int32				m_nBodyLen;			// �������ݳ��ȣ���������ͷ�� 
	char				m_arrRecvBuffer[65536];

	int32				m_bSending;
	char				m_arrSendBuffer[65536];

	int32				m_nMaxRecivedSize;
	int32				m_nMaxSendoutSize;

	int32				m_nTimeout;			// ��ʱ�Ͽ�,0��,>0ָ������ 

	/*-------------------------------------------------------------------
	 * @Brief :
	 *			-1:��
	 *			0:���������Ͽ�-------����˵�����SetWellColse
	 *			1:Զ�������Ͽ�-------�û�ֱ��
	 *			2:��ʱ�Ͽ�-----------��ֵ���������������趨
	 *			3:��ͷ����ֵ�Ƿ�-----С��sizeof(NetMsgHead)��������ý���������С
	 *			4:д�����ݵ�buffer��ʧ��--�յ������ݹ��࣬��������������ٶȹ����������趨��buffer����̫С 
	 *			5:��������ʱʧ��------����ʧЧ 
	 *
	 * @Author:hzd 2013:11:19
	 *------------------------------------------------------------------*/
	int32				m_errorCode;		// �������  

	bool m_bBreakUpdateIo; /* �ж��յ�IO������Ϣ���ڵȴ��� */ 

	bool m_bEnventClose; // �Ƿ����˳��¼� 

};

typedef boost::function<void(NetSocket& pSocket)>	PNetServerEnterHandler;
typedef boost::function<void(NetSocket& pSocket)>	PNetServerExistHandler;
typedef boost::function<void(NetSocket& pSocket, NetMsgSS* pMsg,int32 nSize)>	PNetServerOnMsgHandler;


typedef list<NetSocket*> SocketList;
typedef list<NetSocket*>::iterator SocketListIter;
typedef vector<NetSocket*> SocketVector;
typedef vector<NetSocket*>::iterator SocketVectorIter;

typedef map<int64,NetSocket*> SocketMap;
typedef map<int64, NetSocket*>::iterator SocketMapIter;

#endif

