#ifndef __BASE_H_
#define __BASE_H_

#include "BaseDefine.h"
#include "ServerDefine.h"


class SceneUser;


/* ������������� */ 

enum EPkSceneType
{
	E_PK_SCENE_TYPE_NULL = 0,	// ��  
	E_PK_SCENE_TYPE_GENERAL,	// ��ͨ 
	E_PK_SCENE_TYPE_INSTANCE,	// ���� 
};


/* �������� */
class BaseScene
{
public:
	BaseScene(){};

	/* Ԥǰ���/���(����ڴ滹δ����) */ 
	virtual bool CheckEnter(const stEnterSceneParam& param) = 0;

	/* ����ó��������(��ȼ�飬�Ѿ���������ڴ�) */ 
	virtual void OnUserEnter(SceneUser* pUser) = 0;

	/* �˳����� */ 
	virtual void OnUserLeave(SceneUser* pUser) = 0;

protected:


};


#endif 



