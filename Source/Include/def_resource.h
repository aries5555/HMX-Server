#ifndef __DEF_RESOURCE_H_
#define __DEF_RESOURCE_H_




#pragma pack(push, 1)

struct StRoleTypeInitCfg
{
	int32 nRoleType;
	int32 arrSkillId[MAX_SKILL_COUNT];
	int32 nLandMapId;
	int32 nLandX;
	int32 nLandY;
	int32 nInViewRange;
	int32 nOutViewRange;
	int32 nInitRed;
	int32 nInitBlue;
	int32 nAttackType;
	int32 nSpeed;
};


struct StCharacterLevelCfg
{
	int32 nIdx;			// ID  
	int32 nCharType;	// ��ɫ����   
	int32 nLevel;		// �ȼ� 
	int32 nUpLevelExp;  // ��һ����Ҫ����  
	int32 nRedMax;		// ����  
	int32 nRedRecover;  // ��ظ�/s  
	int32 nBlueMax;     // ����� 
	int32 nBlueRecover; // ���ظ�/s 
	int32 nPhysicAttack;// ��ͨ����  
	int32 nPhysicDefend;// ��ͨ���� 
	int32 nSpellAttack; // ���ܹ��� 
	int32 nSpellDefend; // ���ܷ��� 
	int32 nBaojilv;		// ������ 
	int32 nBaoji;		// ����(����) 
	int32 nGedanglv;    // ���ʣ��񵲶Է������˺��� 
	int32 nGedang;		// ��ֵ 
	int32 nShanbilv;	// ������(���ܶԷ��ļ���) 
	int32 nMingZhonglv; // ������(���жԷ����ü���) 
};

// ��ͼ��Ϣ 
struct StMapInfoResCfg
{
	int32	nMapId;
	int32	nSceneType;
	string	strZoneFileName;
	string	strSceneFileName;
};

// ��ͼ���� 
struct StMapZoneResCfg
{
	int32 nMapId;									// ��ͼID 
	int32 nXAmount;									// ��������� 
	int32 nYAmount;									// ���¸����� 
	int32 nXCellLength;								// ����С�����赲��С���ӵ�λ��ͬ 
	int32 nYCellLength;								// ���С�����赲��С���ӵ�λ��ͬ 
	int32 nBlock;									// ������������ã� 
	int32 nNpc;										// NPC���ã������ã� 
	std::string strData;							// 0246ֵ 
	std::vector<std::vector<int8> > regionValue;	// ������ӵ�ֵ 
};

// ��ͼ�赲 
struct StMapSceneResCfg
{
	int32 nMapId;	// ��ͼID 
	int32 nXAmount; // ��������� 
	int32 nYAmount;	// ���¸����� 
	int32 nXCellLength;// �����أ���С�ĸ��ӳ��� 
	int32 nYCellLength;// �����أ���С�ĸ��ӳ��� 
	string strData; // 0246 ֵ 
	std::vector<std::vector<int8> > regionValue;	// ������ӵ�ֵ 
	/*--------------------------------------------
	 *  @brief    :	���صĴ�СҪ����ʵ��ͼ�ĳߴ���һ������
	 *  @input	  : ��ͼ����Ϊ(�׻�cm��)
	 *  @return   :	
	 *-------------------------------------------*/
};


// �������ñ� 
struct StQuestInfoResCfg  
{
	int32 nId;
	int32 nType;
	int32 nSubType;

	string strTitle;
	string strContent;

	struct AcceptInfo
	{
		int32 nType;
		int32 nArg0;
		int32 nArg1;

	};
	AcceptInfo accept[4];

	struct FinishInfo
	{
		int32 nType;
		int32 nArg0;
		int32 nArg1;
	};

	FinishInfo finish[4];

	struct AwardInfo
	{
		int32 nType;
		int32 nArg0;
		int32 nArg1;
	};

	AwardInfo award[4];

};

#endif

