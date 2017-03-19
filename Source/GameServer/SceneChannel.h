#ifndef __SCENECHANNEL_H_
#define __SCENECHANNEL_H_

#include <set>
#include "Single.h"
#include "UnorderedSet.h"


/*------------------------------------------------------------------
 *
 * @Brief : ����Ƶ�������ļ����������ע��ͨ��ͨ��
 *
 * @Author: hzd 
 * @Fileanme  : SceneChannel.h
 * @Date  : 2014/09/18 01:31
 * @Copyright (c) 2014,hzd, All rights reserved.
 *-----------------------------------------------------------------*/


/*-------------------------------------------------------------
 * ����ע��ӿڣ���Ҫ���볡�������壬����Ҫ�̳иýӿ�
 *------------------------------------------------------------*/
struct IChannelRegist
{
	// �Ƿ�ע��ָ��Ƶ�� 
	virtual bool IsRegist(EChannelRegistType eType) const = 0;
};


/*--------------------------------------------------------------------------------
 * �����ɣ�IChannelOperateNotifyType һ��Ƶ������ṹ��
 * ��  ����NotifyType Ϊһ��struct��Ϣ���ݽṹ��
 * ��  �ڣ������е�������Ҫ��NotifyType��Ϣ�Ĺ㲥�����ʱ����Ҫ�̳��ڸó���ӿ�
 *-------------------------------------------------------------------------------*/
#define DEF_IChannelOperate(NotifyType)\
template<typename NotifyType>\
struct IChannelOperate##NotifyType\
{\
	FUNCTION_CHANNEL_BROADCAST(NotifyType)\
	FUNCTION_CHANNEL_COLLECT(NotifyType)\
protected:\
	NotifyType m_s##NotifyType;\
};

/*------------------------------------------------
 * �����ɣ�����������ҪNotifyType���͵���Ϣ����
 * ��  �ڣ������е�������Ҫ��NotifyType��Ϣ�Ĺ㲥�����ʱ����Ҫ�̳��ڸó���ӿ�
 *-----------------------------------------------*/
#define IChannelOperate(NotifyType) IChannelOperate##NotifyType<NotifyType>


/*------------------------------------------------------------------
 *
 * @Brief : Ƶ������
 *
 * @Author: hzd 
 * @File  : SceneChannel.h
 * @Date  : 2014/09/19 01:36
 * @Copyright (c) 2014,hzd, All rights reserved.
 *-----------------------------------------------------------------*/
class ChannelEx
{
public:

	/*--------------------------------------------
	 *  @brief    :	Ƶ�����죺ÿ��Ƶ��ֻ�ܹ㲥һ����Ϣ������һ����Ϣ
	 *  @input	  : ChannelRegistType:�㲥����,ChannelRegistType:�ռ�����
	 *  @return   :	
	 *-------------------------------------------*/
	ChannelEx(EChannelRegistType eBroadcastType, EChannelRegistType eCollectType)
		: m_eBroadcastType(eBroadcastType), m_eReceiveType(eCollectType) {}

	/*------------------------------------------------
	 * Ϊ��Ƶ������һ��������
	 *-----------------------------------------------*/
	virtual void RegistReceiver(IChannelRegist& rRegister) = 0;

	/*------------------------------------------------
	 * Ϊ��Ƶ���Ƴ�һ��������
	 *-----------------------------------------------*/
	virtual void CancelReceiver(IChannelRegist& rRegister) = 0;
	
	/*------------------------------------------------
	 * Ϊ��Ƶ������һ���㲥��
	 *-----------------------------------------------*/
	virtual void RegistBroadcaster(IChannelRegist& rRegister) = 0;

	/*------------------------------------------------
	 * Ϊ��Ƶ���Ƴ�һ���㲥��
	 *-----------------------------------------------*/
	virtual void CancelBroadcaster(IChannelRegist& rRegister) = 0;

	/*------------------------------------------------
	 * ˢ����Ϣ���ռ��㲥�ߵ���Ϣ����������  
	 *-----------------------------------------------*/
	virtual void Update() = 0;

protected:
	const EChannelRegistType		m_eBroadcastType;				// �㲥������ 
	const EChannelRegistType		m_eReceiveType;					// ���������� 
};

/*------------------------------------------------------------------
 *
 * @Brief : ����Ƶ���궨��
 *
 * @Author: hzd 
 * @File  : SceneChannel.h
 * @Date  : 2014/09/18 23:56
 * @Copyright (c) 2014,hzd, All rights reserved.
 *-----------------------------------------------------------------*/
#define DEF_SceneChannel(NotifyType)\
template<typename NotifyType>\
class SceneChannel##NotifyType : public ChannelEx\
{\
public:\
	SceneChannel##NotifyType(EChannelRegistType eBroadcastType, EChannelRegistType eCollectType)\
		: ChannelEx(eBroadcastType, eCollectType)\
	{}\
	virtual void RegistReceiver(IChannelRegist& rRegister)\
	{\
		if (rRegister.IsRegist(m_eBroadcastType))\
		{\
			if (IChannelOperate(NotifyType)* pOperate = dynamic_cast< IChannelOperate(NotifyType) * >(&rRegister))\
			{\
				m_setChannnelReceivers.insert(pOperate);\
			}\
		}\
	}\
	virtual void CancelReceiver(IChannelRegist& rRegister)\
	{\
		if (rRegister.IsRegist(m_eBroadcastType))\
		{\
			if (IChannelOperate(NotifyType)* pOperate = dynamic_cast< IChannelOperate(NotifyType) * >(&rRegister))\
			{\
				m_setChannnelReceivers.erase(pOperate);\
			}\
		}\
	}\
	virtual void RegistBroadcaster(IChannelRegist& rRegister)\
	{\
		if (rRegister.IsRegist(m_eReceiveType))\
		{\
			if (IChannelOperate(NotifyType)* pOperate = dynamic_cast< IChannelOperate(NotifyType) * >(&rRegister))\
			{\
				m_setChannnelBroadcasters.insert(pOperate);\
			}\
		}\
	}\
	virtual void CancelBroadcaster(IChannelRegist& rRegister)\
	{\
		if (rRegister.IsRegist(m_eReceiveType))\
		{\
			if (IChannelOperate(NotifyType)* pOperate = dynamic_cast< IChannelOperate(NotifyType) * >(&rRegister))\
			{\
				m_setChannnelBroadcasters.erase(pOperate);\
			}\
		}\
	}\
	virtual void Update()\
	{\
		std::set<const NotifyType*> setChannnelMsg;\
		{\
			typename std::set< IChannelOperate(NotifyType) * >::const_iterator iter_broadcaster;\
			for (iter_broadcaster = m_setChannnelBroadcasters.begin(); iter_broadcaster != m_setChannnelBroadcasters.end(); ++iter_broadcaster)\
			{\
				const NotifyType* pMsg;\
				(**iter_broadcaster).ChannelCollect(pMsg);\
				setChannnelMsg.insert(pMsg);\
			}\
		}\
		{\
			typename std::set< IChannelOperate(NotifyType) * >::const_iterator iter_receiver;\
			for (iter_receiver = m_setChannnelReceivers.begin(); iter_receiver != m_setChannnelReceivers.end(); ++iter_receiver)\
			{\
				(**iter_receiver).ChannelBroadcast(setChannnelMsg);\
			}\
		}\
	}\
private:\
	std::set< IChannelOperate(NotifyType) * >		m_setChannnelBroadcasters;\
	std::set< IChannelOperate(NotifyType) * >		m_setChannnelReceivers;\
};

/*------------------------------------------------
 * ����Ƶ���궨��
 *-----------------------------------------------*/
#define SceneChannel(NotifyType) SceneChannel##NotifyType<NotifyType>

/*------------------------------------------------------------------
 *
 * @Brief : ����Ƶ��������
 *
 * @Author: hzd 
 * @File  : SceneChannel.h
 * @Date  : 2014/09/18 23:57
 * @Copyright (c) 2014,hzd, All rights reserved.
 *-----------------------------------------------------------------*/
class SceneChannelManager : public Single<SceneChannelManager>
{
public:

	/*--------------------------------------------
	 *  @brief    :	����һ��Ƶ��
	 *  @input	  : SceneChannel##NotifyType
	 *  @return   :	�� 
	 *-------------------------------------------*/
	void AddSceneChannel(ChannelEx& rChannel);
	
	/*--------------------------------------------
	 *  @brief    :	����Ƶ��update��Ϣ
	 *  @input	  : ��
	 *  @return   :	��
	 *-------------------------------------------*/
	void Update();

private:

	/*------------------------------------------------
	 * Ƶ������
	 *-----------------------------------------------*/
	UNORDERED_SET<ChannelEx*>		m_usetChannels;
};


/*------------------------------------------------
 * ������λ��Ƶ���ӿ�
 *-----------------------------------------------*/
DEF_IChannelOperate(ChannelPosition)
DEF_SceneChannel(ChannelPosition)
extern zObjPool< SceneChannel(ChannelPosition) > g_cPositionChannelFactory;		 

/*------------------------------------------------
 * ������������Ƶ���ӿ�
 *-----------------------------------------------*/
DEF_IChannelOperate(ChannelCreature)
DEF_SceneChannel(ChannelCreature)
extern zObjPool< SceneChannel(ChannelCreature) > g_cCreatureChannelFactory;			

/*------------------------------------------------
 * �����ɴ���Ƶ���ӿ�
 *-----------------------------------------------*/
DEF_IChannelOperate(ChannelWear)
DEF_SceneChannel(ChannelWear)
extern zObjPool< SceneChannel(ChannelWear) > g_cWearChannelFactory;		

/*------------------------------------------------
 * �����ɼ���Ƶ���ӿ�
 *-----------------------------------------------*/
DEF_IChannelOperate(ChannelSpell)
DEF_SceneChannel(ChannelSpell)
extern zObjPool< SceneChannel(ChannelSpell) > g_cSpellChannelFactory;		

/*------------------------------------------------
 * ������BuffƵ���ӿ�
 *-----------------------------------------------*/
DEF_IChannelOperate(ChannelBuff)
DEF_SceneChannel(ChannelBuff)
extern zObjPool< SceneChannel(ChannelBuff) > g_cBuffChannelFactory;		

#endif

