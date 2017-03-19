#ifndef __SCENE_SERVER_H_
#define __SCENE_SERVER_H_


#include "srvEngine.h"
#include "ConfigBase.h"
#include "CommandS.h"

class SceneEntryPk;
class SceneNpc;
class Scene;
class SceneEntryPk;
class SceneUser;
class SceneTask;
class SceneTaskManager;
class QuestList;
class Vars;
class Condition;
class Action;

class GuardNpc;
class CartoonPet;
class Dice;

class Scene;
class ScenePet;
struct zSkill;
struct zSkillB;


//sky ���⴦���ܵ�ID
#define SKILLID_IMMOLATE	24	//�׼�
#define SKILLID_SOUL		88	//���״̬
//sky �������м����Ƴ��ļ���
#define SKILLID_FEAR		53	//�־�
#define SKILLID_FROZEN		34	//����
#define SKILLID_LIME		64	//ʯ�ҷ�
#define SKILLID_REPENTANCE	57	//��� 

/**
* \brief AI����,npc�����Ļ�������
* �ߡ�������Ѳ�ߡ���ת��
*
*/
enum SceneNpcAIType
{
	NPC_AI_NORMAL,///��ͨAI
	NPC_AI_SAY,///˵��
	NPC_AI_MOVETO,///�ƶ���ĳλ��
	NPC_AI_ATTACK,///��ĳ��Χ�ڹ���
	NPC_AI_FLEE,///�������
	NPC_AI_RETURN_TO_REGION,///�ص����Χ
	NPC_AI_GO_ON_PATH,///����һ��·���ƶ�
	NPC_AI_CHANGE_MAP,///�л���ͼ��ͬһ�������ڣ�
	NPC_AI_WARP,///ͬһ��ͼ��˲���ƶ�
	NPC_AI_PATROL,///Ѳ��
	NPC_AI_CLEAR,///�����npc
	NPC_AI_WAIT,///�ȴ�,ʲôҲ����
	NPC_AI_GUARD_DOOR,///����
	NPC_AI_GUARD_ARCHER,///����
	NPC_AI_GUARD_GUARD,///����
	NPC_AI_GUARD_PATROL,///Ѳ����ʿ
	NPC_AI_DROP_ITEM,///������
	NPC_AI_CALL_PET,///�г���
	NPC_AI_RANDOM_CHAT///���˵��
};

///sky npc��Ϊģʽ
enum NpcAIFlag
{
	AIF_ATK_PDEF = 0x00000001, ///���ȹ��������͵ĵ���
	AIF_ATK_MDEF = 0x00000002, ///���ȹ���ħ����͵ĵ���
	AIF_ATK_HP = 0x00000004, ///���ȹ�������ֵ��͵ĵ���
	AIF_GIVEUP_10_SEC = 0x00000008, ///׷��10�����Ŀ��
	AIF_GIVEUP_6_SEC = 0x00000010, ///6��δ�ܵ��˺�����Ŀ��
	AIF_GIVEUP_3_SEC = 0x00000020, ///3��δ�ܵ��˺�����Ŀ��
	AIF_FLEE_30_HP = 0x00000040, ///HP30%��������4��
	AIF_FLEE_3_ENEMY_4 = 0x00000080, ///��3�����ϵ���Χ������4��
	AIF_NO_BATTLE = 0x00000100,///��ս��npc
	AIF_NO_MOVE = 0x00000200, ///���ƶ���������������·��ȣ�
	AIF_WARP_MOVE = 0x00000400, ///˲�Ʒ�ʽ�ƶ�
	AIF_CALL_FELLOW_7 = 0x00000800, ///�ٻ�7*7��Χ��δ����npc(����50%)
	AIF_CALL_FELLOW_9 = 0x00001000, ///�ٻ�9*9��Χ��δ����npc������50%��
	AIF_CALL_BY_ATYPE = 0x00002000, ///�ٻ�ͬ�ֹ������͵�ͬ�飨����������־������
	AIF_HELP_FELLOW_5 = 0x00004000,///����5*5��Χ�ڵ�ͬ�鹥�������ڱ���npc��
	AIF_ATK_MASTER = 0x00008000,///ֱ�ӹ������������
	AIF_ATK_REDNAME = 0x00010000,///�������������
	AIF_DOUBLE_REGION = 0x00020000,///������Χ�ӱ�
	AIF_SPD_UP_HP20 = 0x00040000,///hp20%�����ƶ��ٶȼӱ�
	AIF_ASPD_UP_HP50 = 0x00080000,///hp50%���¹����ٶȼӱ�
	AIF_ACTIVE_MODE = 0x00100000,///��������
	AIF_RUN_AWAY = 0x00200000,///�������
	AIF_LOCK_TARGET = 0x00400000,///���л�����Ŀ��ֱ����
	AIF_RCV_UNDER_30 = 0x00800000,///hp30%���³�����Ѫ1%
	AIF_RCV_REST = 0x01000000,///����ս��30����Ѫһ��5%
	AIF_LIMIT_REGION = 0x02000000  ///���ƻ��Χ
};

///npc˵��������
enum NpcChatType
{
	NPC_CHAT_ON_FIND_ENEMY = 1,///���ֵ���
	NPC_CHAT_ON_ATTACK,///����ʱ˵�Ļ�
	NPC_CHAT_ON_RETURN,///׷�𷵻�ʱ˵�Ļ�
	NPC_CHAT_ON_DIE,///����ʱ��˵�Ļ�
	NPC_CHAT_ON_FLEE,///����ʱ˵�Ļ�
	NPC_CHAT_ON_HIT,///����ʱ˵�Ļ�
	NPC_CHAT_ON_HELP,///����ͬ��ʱ˵�Ļ�
	NPC_CHAT_ON_BE_HELP,///ͬ��������ʱ˵�Ļ�
	NPC_CHAT_RANDOM    ///���˵��
};

// ����ʹ�ü��ܵ����� [sky add ������Щ ����������]
enum NpcSkillCond
{
	NPC_COND_ALWAYS,			//������
	NPC_COND_HPGMAXRATE,		//����HP����n%ʱ
	NPC_COND_HPLMAXRATE,		//����HP����n%ʱ
	NPC_COND_FHPLMAXRATE,		//�ѷ�ħ��HP����n%ʱ����Χ����Χ8��뾶
	NPC_COND_ATPCGE,			//������PC����>=n�Ļ�
	NPC_COND_TARGEHPGMAX,		//���������HP����n%ʱ
	NPC_COND_TARGEHPLMAX,		//���������HP����n%ʱ
	NPC_COND_TARGETSTATUON,		//����������õ�ĳ���쳣״̬ʱ(��cond2Ϊ��׼)
	NPC_COND_TARGETSTATUOFF,	//����������û��ĳ���쳣״̬ʱ(��cond2Ϊ��׼)
	NPC_COND_MAXSTHPGMAX,		//���˵�HP����nʱ(Ԥ��������BB��)
	NPC_COND_MAXSTHPLMAX,		//���˵�HP����nʱ(Ԥ��������BB��)
	NPC_COND_MASTERSTATUON,		//������û��ĳ���쳣״̬ʱ(��cond2Ϊ��׼)(Ԥ��������BB��)
	NPC_COND_MASTERSTATUOFF,	//�����˵õ�ĳ���쳣״̬ʱ(��cond2Ϊ��׼)(Ԥ��������BB��)
	NPC_COND_CLOSEDATACKED,		//��������ʱ
	NPC_COND_LONGRANGEATTACKED,	//��Զ�̹���ʱ
	NPC_COND_RUDEATTACKED,		//�����������ܷ���ʱ(��ʱ�ò���)

								//�쳣״̬��״������ NPC_COND_TARGETSTATUON  NPC_COND_TARGETSTATUOFF �ȣ���ʱֻ����2���ӿڣ�
	NPC_COND_STAN,		//��ѣ
	NPC_COND_SLEEP		//˯��
};

enum PkAttrType
{
	PK_ATTRIBUTE_STATUS = 0,		// ״̬ 
	PK_ATTRIBUTE_LEVEL,				// �ȼ� 
	PK_ATTRIBUTE_RED,				// �� 
	PK_ATTRIBUTE_REDMAX,			// ��MAX
	PK_ATTRIBUTE_BLUE,				// �� 
	PK_ATTRIBUTE_BLUEMAX,			// ��MAX
	PK_ATTRIBUTE_REDRECOVER,		// ��ָ� 
	PK_ATTRIBUTE_BLUERECOVER,		// ���ָ� 
	PK_ATTRIBUTE_PHYSICATTACK,		// ������ 
	PK_ATTRIBUTE_PHYSICDEFEND,		// ������� 
	PK_ATTRIBUTE_SPELLATTACK,		// �������� 
	PK_ATTRIBUTE_SPELLDEFEND,		// �������� 
	PK_ATTRIBUTE_BAOJILV,			// ������ 
	PK_ATTRIBUTE_BAOJI,				// ���� 
	PK_ATTRIBUTE_GEDANGLV,			// ������ 
	PK_ATTRIBUTE_GEDANG,			// ���� 
	PK_ATTRIBUTE_SHANBILV,			// ������ 
	PK_ATTRIBUTE_MINGZHONGLV,		// ������ 
	PK_ATTRIBUTE_ATTACKSPEED,		// �����ٶ� 
	PK_ATTRIBUTE_MOVESPEED,			// �ƶ��ٶ� 
	PK_ATTRIBUTE_MAX,
};

enum PKStatus
{
	PK_STATUS_NULL = 0,

	PK_STATUS_ALIVE = 0x00000001,	// ���� 
	PK_STATUS_DEAD = 0x00000002,	// ���� 

	PK_STATUS_DEHUANMAN = 0x00000008,	// ������ 
	PK_STATUS_XUANYUN = 0x00000010,	// ѣ�� 
	PK_STATUS_DEXUANYUN = 0x00000020,	// ��ѣ�� 
	PK_STATUS_HUNLUAN = 0x00000040,	// ���� 
	PK_STATUS_DEHUNLUAN = 0x00000080,	// ������ 
	PK_STATUS_DINGSHEN = 0x00000100,	// ���� 
	PK_STATUS_DEDINGSHEN = 0x00000200,	// ������ 
	PK_STATUS_CHENMO = 0x00000400,	// ��Ĭ 
	PK_STATUS_DECHENMO = 0x00000800,	// ����Ĭ 
	PK_STATUS_MIWU = 0x00001000,	// ���� 
	PK_STATUS_DEMIWU = 0x00002000,	// ������ 
	PK_STATUS_FUKONG = 0x00004000,	// ���� 
	PK_STATUS_DEFUKONG = 0x00008000,	// ������ 
	PK_STATUS_JIDAO = 0x00010000,	// ���� 
	PK_STATUS_DEJIDAO = 0x00020000,	// ������ 
	PK_STATUS_SHOUJI = 0x00040000,	// �ܻ� 
	PK_STATUS_DESHOUJI = 0x00080000,	// ���ܻ� 
	PK_STATUS_DEJITUI = 0x00200000,	// ������ 
};

enum PKAttackType
{
	PK_ATTACK_TYPE_NULL,

	PK_ATTACK_TYPE_Melee = 0x00000001,	// ��ս 
	PK_ATTACK_TYPE_Remote = 0x00000002,	// Զ�� 
	PK_ATTACK_TYPE_PHYSIC = 0x00000004,	// ���� 
	PK_ATTACK_TYPE_SPELL = 0x00000008,	// ���� 
};

struct PkValue
{
	PkValue()
	{
		bzero(dwValue, sizeof(dwValue));
	}
	void init()
	{
		bzero(dwValue, sizeof(dwValue));
	}
	union
	{
		struct
		{
			int32 nStatus;			// ״̬(������λ����ֵ) 
			int32 nLevel;			// �ȼ� 
			int32 nRed;				// ��(Ѫ) 
			int32 nRedMax;			// ������ 
			int32 nBlue;			// ��(����) 
			int32 nBlueMax;			// ������ 
			int32 nRedRecover;		// ��ָ� 
			int32 nBlueRecover;		// ���ָ� 
			int32 nPhysicAttack;	// ������ 
			int32 nPhysicDefend;	// ������� 
			int32 nSpellAttack;		// �������� 
			int32 nSpellDefend;		// �������� 
			int32 nBaojilv;			// ������ 
			int32 nBaoji;			// ���� 
			int32 nGedanglv;		// ������ 
			int32 nGedang;			// ���� 
			int32 nShanbilv;		// ������ 
			int32 nMingzhonglv;		// ������ 
			int32 nAttackSpeed;		// �ٶ� 
			int32 nMoveSpeed;		// ���� 
		};
		DWORD dwValue[PK_ATTRIBUTE_MAX];
	};
};

/**
* \brief ��ṹ
*/
struct Point
{
	/// ����
	char name[MAX_NAMESIZE + 1];

	/// λ��
	zPos pos;

	/**
	* \brief ���캯����ʼ��
	*/
	Point() : pos()
	{
		bzero(name, sizeof(name));
	}

	/**
	* \brief ��������
	* \param point ��
	*/
	Point(const Point &point)
	{
		bcopy(point.name, name, sizeof(name), sizeof(name));
		pos = point.pos;
	}

	/**
	* \brief ���ز�����,������
	* \param point �������ĵ�
	*/
	Point & operator= (const Point &point)
	{
		bcopy(point.name, name, sizeof(name), sizeof(name));
		pos = point.pos;
		return *this;
	}
};

// [ranqd] �������Ͷ���
struct zZone {
	zPos pos;// ���Ͻǵĵ�
	int  width; // ������
	int  height; // ����߶�

	zZone()
	{
		pos = zPos(0, 0);
		width = 0;
		height = 0;
	}
	bool IsInZone(zPos p) // �жϵ�p�Ƿ��ڴ�������
	{
		return  p.x >= pos.x && p.x < pos.x + width && p.y >= pos.y && p.y < pos.y + height;
	}
	zPos GetRandPos() // ���ظ����������һ��
	{
		zPos p;
		p.x = randBetween(pos.x, pos.x + width - 1);
		p.y = randBetween(pos.y, pos.y + height - 1);
		return p;
	}
	bool IsEmpty()
	{
		return width == 0 && height == 0;
	}
};
// [ranqd] ����ͼ���Ƶ�����
struct zPoint
{
	/// ��ͼ����
	char name[MAX_NAMESIZE + 1];

	/// ��ͼ����
	zZone pos;

	/**
	* \brief ���캯����ʼ��
	*/
	zPoint() : pos()
	{
		bzero(name, sizeof(name));
	}

	/**
	* \brief ��������
	* \param point ��
	*/
	zPoint(const zPoint &point)
	{
		bcopy(point.name, name, sizeof(name), sizeof(name));
		pos = point.pos;
	}

	/**
	* \brief ���ز�����,������
	* \param point �������ĵ�
	*/
	zPoint & operator= (const zPoint &point)
	{
		bcopy(point.name, name, sizeof(name), sizeof(name));
		pos = point.pos;
		return *this;
	}
};

/**
* \brief ���㶨��
*/
struct WayPoint
{
	friend class WayPointM;
private:

	/// Ŀ������㼯��
	//   std::vector<Point> dest;
	// [ranqd] ���͵����Ϊ������
	std::vector<zPoint> dest;

	/// Ŀ���������Ŀ
	WORD destC;
public:
	/// ��������㼯��
	// std::vector<zPos> point;
	// [ranqd] ���͵����Ϊ������
	std::vector<zZone> point;
	/// �����������Ŀ
	WORD pointC;

	bool init(zXMLParser *parser, const xmlNodePtr node, DWORD countryid);
	WayPoint();
	const Point getRandDest();
	const zPos getRandPoint();
};

class WayPointM
{
private:
	/// ���㼯��
	std::vector<WayPoint> wps;
public:
	bool addWayPoint(const WayPoint &wp);
	WayPoint *getWayPoint(const zPos &pos);
	WayPoint *getWayPoint(const char *filename);
	WayPoint *getRandWayPoint();
};

/**
* \brief ����Npc����״̬
*
*/
enum SceneNpcChase
{
	CHASE_NONE,     /// û�и���״̬
	CHASE_ATTACK,   /// ���ٹ���״̬
	CHASE_NOATTACK    /// ��ͨ����״̬
};


/**
* \brief Npc����
* ��̬�Ļ��Ƕ�̬�����
*/
enum SceneNpcType
{
	STATIC,       /// ��̬��
	GANG        /// ��̬��
};

/**
* \brief һ��AI�Ķ���
*
*/
struct t_NpcAIDefine
{
	///����,NPC�ڸý׶ε���Ҫ����
	SceneNpcAIType type;
	///λ�� ���ݲ�ͬ����λ�õ�����Ҳ�Բ���ͬ
	///�ƶ�ʱ��ʾĿ�ĵ�,������ʾ���Χ����
	zPos pos;
	///��Χ 
	///�ƶ�ʱ��ʾ����Ŀ�ĵص��ж���Χ,������ʾ���Χ
	int regionX, regionY;
	//zRTime endTime;
	///��AI�ĳ���ʱ��(��)
	int lasttime;

	///�Ƿ���������
	bool flee;
	///���ܵķ���
	int fleeDir;
	///���ܼ���
	int fleeCount;

	///�л���ͼʱ,Ҫȥ�ĵ�ͼ
	///˵��ʱ,Ҫ˵�Ļ�
	char str[MAX_CHATINFO];


	/**
	* \brief Ĭ�Ϲ��캯��
	*
	*/
	t_NpcAIDefine()
		:type(NPC_AI_NORMAL), pos(zPos(0, 0)), regionX(2), regionY(2), lasttime(0), flee(false), fleeDir(-1), fleeCount(0)
	{
		bzero(str, sizeof(str));
	}

	/**
	* \brief ���캯��
	*
	*
	* \param type AI����
	* \param pos λ��
	* \param regionX ��Χ��
	* \param regionY ��Χ��
	* \param lasttime ����ʱ��
	* \return
	*/
	t_NpcAIDefine(SceneNpcAIType type, const zPos &pos, int regionX, int regionY, int lasttime)
		:type(type), pos(pos), regionX(regionX), regionY(regionY), lasttime(lasttime)
	{
		bzero(str, sizeof(str));
	}


	/**
	* \brief �������캯��
	*
	* \param ad Ҫ���ƵĶ���
	*/
	t_NpcAIDefine(const t_NpcAIDefine &ad)
	{
		type = ad.type;
		pos = ad.pos;
		regionX = ad.regionX;
		regionY = ad.regionY;
		lasttime = ad.lasttime;
		flee = ad.flee;
		fleeDir = ad.fleeDir;
		fleeCount = ad.fleeCount;
		strncpy_s(str, ad.str, sizeof(str) - 1);
	}

	/**
	* \brief ��ֵ
	*
	* \param ad Ҫ�����Ķ���
	* \return ���������ַ
	*/
	t_NpcAIDefine & operator = (const t_NpcAIDefine &ad)
	{
		type = ad.type;
		pos = ad.pos;
		regionX = ad.regionX;
		regionY = ad.regionY;
		lasttime = ad.lasttime;
		flee = ad.flee;
		fleeDir = ad.fleeDir;
		fleeCount = ad.fleeCount;
		strncpy_s(str, ad.str, sizeof(str) - 1);

		return *this;
	}
};


typedef std::vector<zPos> zPosIndex;

/**
* \brief ����Ķ���
* ������ͷ�����ġ������������������ڷ��赲������
*
*/
struct zRegion
{
	zPos s;        /// ���ϵ�
	zPos c;        /// ���ĵ�
	zPos e;        /// ���µ�
	zPosIndex index;  /// ���赲������
					  /**
					  * \brief ���캯��
					  *
					  */
	zRegion()
	{
	}
	/**
	* \brief �������캯��
	*
	*/
	zRegion(const zRegion &reg)
	{
		s = reg.s;
		c = reg.c;
		e = reg.e;
		index = reg.index;
	}
	/**
	* \brief ��ֵ��������
	*
	*/
	zRegion & operator= (const zRegion &reg)
	{
		s = reg.s;
		c = reg.c;
		e = reg.e;
		index = reg.index;
		return *this;
	}

	/**
	* \brief �ж������Ƿ�������Χ֮��
	*
	*/
	const bool isIn(const zPos &pos) const
	{
		return pos >= s && pos <= e;
	}

};



//�����ļ��й���NPC�Ķ���
/**
* \brief npc����ṹ
* �������,����λ�á���Χ���������Ϣ
*
*/
struct t_NpcDefine
{
	DWORD id;                //���
	char  name[MAX_NAMESIZE + 1];        //����
	zPos  pos;                //����
	WORD  width;              //���ο�
	WORD  height;              //���γ�
	DWORD num;                //����
	DWORD interval;              //ˢ��ʱ��
	zSceneEntry::SceneEntryState initstate;  //��ʼ״̬,���ػ��߷�����
	zRegion region;              //��Χ����,������Χ�ڵĿ����ߵ���������

								 //std::vector<zPos> path;//�̶��ƶ���·��

	DWORD rushID;//��������ID
	BYTE rushRate;//�������ǵļ���
	DWORD rushDelay;//�������ǵ���ʱ

	int scriptID;//���ܽű���id
	DWORD intervalAmendment;		//sky ����ʱ������ֵ
	DWORD AmendmentFactor;		//sky ����ϵ��
	WORD Camp;					//sky ������Ӫ����ֵ

	std::map<DWORD, std::pair<DWORD, DWORD> > petList;
	std::map<DWORD, std::pair<DWORD, DWORD> > summonList;
	std::map<DWORD, std::pair<DWORD, DWORD> > deathSummonList;
	std::list< std::pair<DWORD, zPos> > dieList;
	/**
	* \brief ���캯��
	*
	*/
	t_NpcDefine() : pos(), region()
	{
		id = 0;
		bzero(name, sizeof(name));
		width = 0;
		height = 0;
		num = 0;
		interval = 0;
		rushID = 0;
		rushRate = 0;
		rushDelay = 0;
		initstate = zSceneEntry::SceneEntry_Normal;
		scriptID = 0;
		intervalAmendment = 0;
		AmendmentFactor = 0;
		Camp = 0;
	}
	/**
	* \brief �������캯��
	*
	*/
	t_NpcDefine(const t_NpcDefine &reg)
	{
		id = reg.id;
		bcopy(reg.name, name, sizeof(name), sizeof(name));
		pos = reg.pos;
		width = reg.width;
		height = reg.height;
		num = reg.num;
		interval = reg.interval;
		initstate = reg.initstate;
		region = reg.region;
		//path = reg.path;
		rushID = reg.rushID;
		rushRate = reg.rushRate;
		rushDelay = reg.rushDelay;
		scriptID = reg.scriptID;
		petList = reg.petList;
		summonList = reg.summonList;
		deathSummonList = reg.deathSummonList;
		dieList = reg.dieList;
		intervalAmendment = reg.intervalAmendment;
		AmendmentFactor = reg.AmendmentFactor;
		Camp = reg.Camp;
	}
	/**
	* \brief ��ֵ��������
	*
	*/
	t_NpcDefine & operator= (const t_NpcDefine &reg)
	{
		id = reg.id;
		bcopy(reg.name, name, sizeof(name), sizeof(name));
		pos = reg.pos;
		width = reg.width;
		height = reg.height;
		num = reg.num;
		interval = reg.interval;
		initstate = reg.initstate;
		region = reg.region;
		//path = reg.path;
		rushID = reg.rushID;
		rushRate = reg.rushRate;
		rushDelay = reg.rushDelay;
		scriptID = reg.scriptID;
		petList = reg.petList;
		summonList = reg.summonList;
		deathSummonList = reg.deathSummonList;
		dieList = reg.dieList;
		intervalAmendment = reg.intervalAmendment;
		AmendmentFactor = reg.AmendmentFactor;
		Camp = reg.Camp;
		return *this;
	}

	void fillNpcMap(const char * tempChar, std::map<DWORD, std::pair<DWORD, DWORD> > &map)
	{
		std::vector<std::string> vs;
		std::vector<std::string> sub_vs;
		vs.clear();
		stringtok(vs, tempChar, ";");
		for (DWORD i = 0; i<vs.size(); i++)
		{
			sub_vs.clear();
			stringtok(sub_vs, vs[i].c_str(), "-");
			if (sub_vs.size() == 2)
				map[atoi(sub_vs[0].c_str())] = std::make_pair(atoi(sub_vs[1].c_str()), 100);
			else if (sub_vs.size() == 3) //npcID,num,rate
				map[atoi(sub_vs[0].c_str())] = std::make_pair(atoi(sub_vs[1].c_str()), atoi(sub_vs[2].c_str()));
		}
	}

	//sky ���㸴��ʱ���޸�ϵ��
	void InitIntervalAmendment()
	{
		//sky ����ʱ��Ϊ0��������С��1��ʱ��
		if (interval == 0 || num <= 1)
			return;

		//sky ϵ��ȡ����ʱ����ˢ��������ƽ��ֵ(ʱ����ת���ɺ��뼶)
		intervalAmendment = (interval * 1000) / num;
		AmendmentFactor = num;

		return;
	}

	//sky ��ȡ����ʱ������ֵ
	//Dead ����״̬ (true:���� false:����)
	DWORD GetIntervalAmendmaent(bool Dead)
	{
		if (Dead)
		{
			//sky ���������,��������ϵ�����
			AmendmentFactor++;
			if (AmendmentFactor > num)
				AmendmentFactor = num;
		}
		else
		{
			//sky ���������,�Ͱ�������ϵ������
			AmendmentFactor--;
			if (AmendmentFactor < 0)
				AmendmentFactor = 0;
		}

		//sky ��������ֵ
		return intervalAmendment * AmendmentFactor;
	}
};

typedef std::vector<t_NpcDefine> NpcDefineVector;

#define MAX_NPC_GROUP 5

/**
* \brief ��������Ļص���
*
* ֻҪ�����ڱ���һ�����,����ĳЩ�������
*
* ʹ���߱���Ҫʵ��exec����
*/
struct zSceneEntryCallBack
{
	virtual bool exec(zSceneEntry *entry) = 0;
	virtual ~zSceneEntryCallBack() {};
};

//�����ļ��й����������Ͷ���
/**
* \brief �������͵Ķ���
* �������͡���С��
*
*/
struct ZoneTypeDef
{
	enum
	{
		ZONE_NONE = 0, //һ����
		ZONE_PK_SAFE = 1,   // pk��ȫ��
		ZONE_ABSOLUTE_SAFE = 2,   // ���԰�ȫ��
		ZONE_RELIVE = 4,   // ����������
		ZONE_NEWBIE = 8,   // ���ֳ�����
		ZONE_SPORTS = 16,   // ������
		ZONE_FOREIGN_RELIVE = 32,   // ��������������
		ZONE_PRIVATE_STORE = 128,      // ��̯��
		ZONE_PRIVATE_DARE = 256,      // ��ս��ת��
		ZONE_PRIVATE_RELIVE = 512,    // ��ս������
		ZONE_PRIVATE_UNION = 1024,     // �����������ת��
		ZONE_COUNTRY_WAR = 2048,    // �߾��Ĺ�ս��ת��
		ZONE_PRIVATE_DARE_UNION = 4096,    // ���ս��ս����ת��
		ZONE_DARE_SAFE = 8192,    // ��սʱΪ���԰�ȫ��,ƽʱΪ�ǰ�ȫ��
		ZONE_PRIVATE_THIRD_UNION = 16384,    // ��������ص�������ת��
		ZONE_EMPEROR_DEF_RELIVE = 32768,    // �ʳ�ս�ط�������
		ZONE_EMPEROR_ATT_RELIVE = 65536,    // �ʳ�ս����������  
	};

	zPos  pos;                //����
	WORD  width;              //���ο�
	WORD  height;              //���γ�
	DWORD type;                //�������������
	zSceneEntry::SceneEntryState initstate;  //��ʼ״̬,���ػ��߷�����
	zSceneEntry::SceneEntryState state;    //��ǰ״̬,���ػ��߷�����
	zRegion region;              //��Χ����,������Χ�ڵĿ����ߵ���������

								 /**
								 * \brief ���캯��
								 *
								 */
	ZoneTypeDef() : pos(), region()
	{
		width = 0;
		height = 0;
		type = 0;
		initstate = zSceneEntry::SceneEntry_Normal;
		state = zSceneEntry::SceneEntry_Normal;
	}
	/**
	* \brief �������캯��
	*
	*/
	ZoneTypeDef(const ZoneTypeDef &zone)
	{
		pos = zone.pos;
		width = zone.width;
		height = zone.height;
		type = zone.type;
		initstate = zone.initstate;
		state = zone.state;
		region = zone.region;
	}
	/**
	* \brief ��ֵ��������
	*
	*/
	ZoneTypeDef & operator= (const ZoneTypeDef &zone)
	{
		pos = zone.pos;
		width = zone.width;
		height = zone.height;
		type = zone.type;
		initstate = zone.initstate;
		state = zone.state;
		region = zone.region;
		return *this;
	}
};

typedef std::vector<ZoneTypeDef> ZoneTypeDefVector;

//------------------------------------
// ObjectBase
//------------------------------------
struct ObjectBase {
	const DWORD getUniqueID() const
	{
		return dwField0;
	}

	DWORD  dwField0;    // ���
	char  strField1[64];    // ����
	DWORD  dwField2;    // �������
	DWORD  dwField3;    // ����
	DWORD  dwField4;    // ְҵ�޶�
	DWORD  dwField5;    // ��Ҫ�ȼ�
	DWORD  dwField6;    // ���ߵȼ�
	char  strField7[256];    // ��
	DWORD  dwField8;    // �����Ʒ
	char  strField9[256];    // ҩƷ����
	DWORD  dwField10;    // �������ֵ
	DWORD  dwField11;    // �����ֵ
	DWORD  dwField12;    // �������ֵ
	DWORD  dwField13;    // ��С�﹥
	DWORD  dwField14;    // ����﹥
	DWORD  dwField15;    // ��Сħ��
	DWORD  dwField16;    // ���ħ��
	DWORD  dwField17;    // ���
	DWORD  dwField18;    // ħ��
	DWORD  dwField19;    // �˺��ӳ�

	DWORD  dwField20;    // �����ٶ�
	DWORD  dwField21;    // �ƶ��ٶ�
	DWORD  dwField22;    // ������
	DWORD  dwField23;    // �����
	DWORD  dwField24;    // ����
	DWORD  dwField25;    // �ϳɵȼ�
	DWORD  dwField26;    // ����
	char  strField27[32];    // ��Ҫ����
	char  strField28[1024];    // ��Ҫԭ��
	DWORD  dwField29;    // װ��λ��
	DWORD  dwField30;    // �;ö�
	DWORD  dwField31;    // �۸�
	DWORD  dwField32;    // ��ɫ
	DWORD  dwField33;    // ���ӿ�
	DWORD  dwField34;    // ���Ӹ�
	DWORD  dwField35;    // ����
	DWORD  dwField36;    // �ϳɵ���
	DWORD  dwField37;    // �ػ�
	DWORD  dwField38;    // ��ʥ����
	char  strField39[256];    // ��ʥ��ʶ 

							  //sky ��������
	DWORD  dwField40;    // ����
	DWORD  dwField41;    // ����
	DWORD  dwField42;    // ����
	DWORD  dwField43;    // ����
	DWORD  dwField44;    // ����
	DWORD  dwField45;    // ��������
	DWORD  dwField46;    // ħ������
};//���� ObjectBase �ɹ����� 940 ����¼ 


/**
* \brief ��Ʒ������
*/
struct zObjectB :public zEntry
{
	DWORD maxnum;        // �������
	BYTE kind;          // ����
	BYTE job;          // sky ְҵ����
	WORD level;          // ���ߵȼ�
	std::vector<DWORD> hole;  //��

	WORD needobject;      // �����Ʒ
	struct leechdom_t {
		WORD id; //���ܱ�ʶ
		WORD effect; //Ч��
		WORD time; //ʱ��
		leechdom_t(const std::string& _id = "", const std::string& _effect = "", const std::string& _time = "")
			: id(atoi(_id.c_str())), effect(atoi(_effect.c_str())), time(atoi(_time.c_str()))
		{ }
	} leechdom;         // ҩƷ����

	WORD needlevel;        // ��Ҫ�ȼ�

	DWORD maxhp;          // �������ֵ
	DWORD maxmp;          // �����ֵ
	DWORD maxsp;          // �������ֵ

	DWORD pdamage;        // ��С������
	DWORD maxpdamage;      // ��󹥻���
	DWORD mdamage;        // ��С����������
	DWORD maxmdamage;      // �����������

	DWORD pdefence;        // ���
	DWORD mdefence;        // ħ��

	WORD damagebonus;      //�˺��ӳ�

	WORD akspeed;        // �����ٶ�
	WORD mvspeed;        // �ƶ��ٶ�
	WORD atrating;        // ������
	WORD akdodge;        // �����

	DWORD color;        // ��ɫ  

						//struct socket
						//{
						//  WORD odds;
						//  BYTE min;
						//  BYTE max;
						//  socket(const std::string& odds_,const std::string& number_)
						//  {
						// odds=atoi(odds_.c_str());
						// min=0;
						// max=0;
						//    std::string::size_type pos = 0;
						//    if  ( (pos = number_.find("-")) != std::string::npos )
						//    {
						//      
						//      min = atoi(number_.substr(0,pos).c_str());
						//      max = atoi(number_.substr(pos+strlen("-")).c_str());
						//      //if (odds) Zebra::logger->debug("odds:%d\tmin:%d\tmax:%d",odds,min,max);
						//    }
						//  }
						//} hole;            //��

	BYTE recast;        // ����

	BYTE recastlevel;       // �ϳɵȼ�
	WORD recastcost;      // �ϳɵ���


	WORD make;          // ����
	struct skills
	{
		WORD id;
		BYTE level;
		skills(const std::string& id_ = "0", const std::string& level_ = "0") : id(atoi(id_.c_str())), level(atoi(level_.c_str()))
		{ }
	};
	skills need_skill;      // ��Ҫ����

	struct material
	{
		WORD gold;
		struct  stuff
		{
			WORD id;
			WORD number;
			BYTE level;
			stuff(const std::string& id_, const std::string& level_, const std::string& number_) : id(atoi(id_.c_str())), number(atoi(number_.c_str())), level(atoi(level_.c_str()))
			{ }
		};
		std::vector<stuff> stuffs;
		typedef std::vector<stuff>::iterator stuffs_iterator;
	};
	material need_material;    // ��Ҫԭ��

	BYTE setpos;        // װ��λ��
	WORD durability;      // �;ö�
	DWORD price;        // �۸�

	BYTE width;          // ���ӿ�
	BYTE height;        // ���Ӹ�
	union
	{
		DWORD cardpoint;      // ���� (�Ѿ�����)
		DWORD cointype;        // ��������
	};
	WORD bang;          //�ػ�
	DWORD holyrating;      //��ʥ����
	std::vector<DWORD> holys;     //��ʥ��ʶ

								  // sky ������������
	WORD str;				 //����
	WORD inte;			 //����
	WORD dex;				 //����
	WORD spi;				 //����
	WORD con;				 //����

	WORD atkhpp;  //ħ������
	WORD mtkhpp;  //ħ������

	int  nSuitData;

	void fill(ObjectBase &data)
	{
		nSuitData = -1;

		id = data.dwField0;
		strncpy(name, data.strField1, MAX_NAMESIZE);

		maxnum = data.dwField2;
		kind = data.dwField3;
		job = data.dwField4;
		needlevel = data.dwField5;
		level = data.dwField6;

		init_identifier(hole, data.strField7);

		needobject = data.dwField8;
		init_leechdom(data.strField9);

		maxhp = data.dwField10;
		maxmp = data.dwField11;
		maxsp = data.dwField12;

		pdamage = data.dwField13;
		maxpdamage = data.dwField14;
		mdamage = data.dwField15;
		maxmdamage = data.dwField16;
		pdefence = data.dwField17;
		mdefence = data.dwField18;
		damagebonus = data.dwField19;

		akspeed = data.dwField20;
		mvspeed = data.dwField21;
		atrating = data.dwField22;
		akdodge = data.dwField23;

		recast = data.dwField24;
		recastlevel = data.dwField25;

		make = data.dwField26;

		init_need_skills(data.strField27);
		init_need_material(data.strField28);

		setpos = data.dwField29;
		durability = data.dwField30;
		price = data.dwField31;

		//sky  ����Ϸ���Ѿ�����Ҫ���������
		/*bluerating = data.dwField34;
		goldrating = data.dwField35;*/

		color = data.dwField32;
		width = data.dwField33;
		height = data.dwField34;
		cardpoint = data.dwField35;
		recastcost = data.dwField36;
		bang = data.dwField37;

		holyrating = data.dwField38;
		init_identifier(holys, data.strField39);

		//sky ����������
		str = data.dwField40;	//����
		inte = data.dwField41;	//����
		dex = data.dwField42;	//����
		spi = data.dwField43;	//����
		con = data.dwField44;	//����
		atkhpp = data.dwField45;  //ħ������
		mtkhpp = data.dwField46;  //ħ������


	}

	zObjectB() :zEntry()/*,hole("0","0-0")*/
	{
		bzero(this, sizeof(zObjectB));
	};

	void init_identifier(std::vector<DWORD>& list, const std::string& info)
	{
		list.clear();
		//getAllNum(info.c_str(), list);
	}

	void init_leechdom(const std::string& info)
	{
		/*leechdom_t* p = Parse3<leechdom_t>()(info, ":");
		if (p) {
			leechdom = *p;
			SAFE_DELETE(p);
		}*/
	}

	/*void init_socket(const std::string& socket_info)
	{
	std::string::size_type pos = socket_info.find(':');
	if (pos != std::string::npos) {
	hole = socket(socket_info.substr(0,pos),socket_info.substr(pos+1));
	}

	}*/

	void init_need_skills(const std::string& skills_list)
	{
		std::string::size_type pos = skills_list.find(':');
		if (pos != std::string::npos) {
			need_skill = skills(skills_list.substr(0, pos), skills_list.substr(pos + 1));
		}
	}

	void init_need_material(const std::string& materials)
	{
		/*need_material.stuffs.clear();
		Split<Parse3> p;
		std::string::size_type pos = materials.find(':');
		if (pos != std::string::npos) {
			need_material.gold = atoi(materials.substr(0, pos).c_str());
			p(materials.substr(pos + 1), need_material.stuffs, ";", "-");
		}*/
	}

};

//------------------------------------
// ColorObjectBase
//------------------------------------
struct ColorObjectBase {
	const DWORD getUniqueID() const
	{
		return dwField0;
	}

	DWORD  dwField0;    // ���
	char  strField1[64];    // ����
	char  strField2[32];    // ���ӷ�
	char  strField3[128];    // ��ɫƷ��
	char  strField4[32];    // ����
	char  strField5[32];    // ����
	char  strField6[32];    // ����
	char  strField7[32];    // ����
	char  strField8[32];    // ����
	char  strField9[32];    // ��������
	char  strField10[32];    // ��С�﹥
	char  strField11[32];    // ����﹥
	char  strField12[32];    // ��Сħ��
	char  strField13[32];    // ���ħ��
	char  strField14[32];    // ���
	char  strField15[32];    // ħ��
	char  strField16[32];    // �������ֵ
	char  strField17[32];    // �����ֵ
	char  strField18[32];    // �������ֵ
	char  strField19[32];    // �ƶ��ٶ�
	char  strField20[32];    // ����ֵ�ָ�
	char  strField21[32];    // ����ֵ�ָ�
	char  strField22[32];    // ����ֵ�ָ�
	char  strField23[32];    // �����ٶ�
	char  strField24[32];    // ������������
	char  strField25[32];    // �������������
	char  strField26[32];    // ����ħ��������
	char  strField27[32];    // ����ħ��������
	char  strField28[32];    // ������
	char  strField29[32];    // ������
	char  strField30[32];    // ��������
	char  strField31[32];    // ���������
	char  strField32[32];    // ��ѣ������
	char  strField33[32];    // ����ħ����
	char  strField34[32];    // ����������
	char  strField35[32];    // ����������
	char  strField36[32];    // ����������
	char  strField37[32];    // ��ʯ������
	char  strField38[32];    // ��ʧ������
	char  strField39[32];    // ����������
	char  strField40[32];    // ����������
	char  strField41[32];    // ���ջ�����
	char  strField42[32];    // �ָ��;ö�
	char  strField43[32];    // �ػ�
	DWORD  dwField44;    // ��ʥװ������
	char  strField45[1024];    // ���ܼӳ�
	char  strField46[32];    // ȫϵ���ܼӳ�
};

struct zObject :zEntry
{
	friend class GlobalObjectIndex;
public:
	t_Object data;
	zObjectB *base;

	//only for RebuildObject::make,it's ugly,but .....sigh
	WORD* _p1[5];
	WORD* _p2[18];

	static zObject *create(zObjectB *objbase, DWORD num = 1, BYTE level = 0);
	static void destroy(zObject* ob);
	static void logger(QWORD createid, DWORD objid, char *objname, DWORD num, DWORD change, DWORD type, DWORD srcid, char *srcname, DWORD dstid, char *dstname, const char *action, zObjectB *base, BYTE kind, BYTE upgrade);
	static DWORD RepairMoney2RepairGold(DWORD dwObjectRepair);
	static zObject *create(zObject *objsrc);
	static zObject *load(const SaveObject *o);
	bool getSaveData(SaveObject *save);
	int foundSocket();
	bool canMail();
	void checkBind();

	//zCountryMaterialB* canContribute(); // �Ƿ��ܱ�����
	DWORD getMaterialKind(); // ���ԭ�����: 0,��ͨ���ʣ�1,˿��,2,��ʯ,3,���,4,ľ�ģ�5,Ƥë,6,��ҩ

	const stObjectLocation &reserve() const;
	void restore(const stObjectLocation &loc);

	union
	{
		struct
		{
			DWORD createtime;
			DWORD dwCreateThisID;
		};
		QWORD createid;
	};
	// */
private:
	//friend class Package;
	//friend class Packages;
	//friend class MainPack;
	//friend class zSceneObject;
	//friend class luabind::detail::delete_s<zObject>;

	zObject();
	~zObject();

	bool free() const;
	void free(bool flag);

	void fill(t_Object& d);
	void generateThisID();
	bool inserted;

	//[Shx Add ������Ʒ�Ƿ���װ���]
	void MakeSuit(zObjectB *objbase);
	void FillSuit();
	void FillSuitPPT(int nIndex);
};
struct zSceneObject :public zSceneEntry
{
	static zSceneObject *create(zObject *obj, const zRTime &ct)
	{
		if (obj == NULL) return NULL;
		zSceneObject *ret = new zSceneObject(obj, ct);
		return ret;
	}
	/**
	* \brief ��������Ʒ�Ƿ����
	* ���ڵĵ�����Ʒ����ʧ��
	* \param ct ��ǰʱ��
	* \return �Ƿ����
	*/
	bool checkOverdue(const zRTime &ct) const
	{
		return ct >= this->ct;
	}

	bool checkProtectOverdue(const zRTime &ct)
	{
		if (ownerID == 0)
		{
			return false;
		}
		if (ct > protectTime)
		{
			protectTime = 0;
			ownerID = 0;
			return true;
		}
		return false;
	}

	void setOwner(DWORD dwID, int protime = 10)
	{
		if (dwID)
		{
			ownerID = dwID;
			zRTime ctv;
			protectTime = ctv;
			this->protectTime.addDelay(protime * 1000);
		}
	}

	void setOverDueTime(zRTime &ct_1)
	{
		ct = ct_1;
	}
	DWORD getOwner()
	{
		return ownerID;
	}

	~zSceneObject()
	{
		//if (o) o->free();
		zObject::destroy(o);
	}

	void clear()
	{
		o = NULL;
	}

	zObject *getObject()
	{
		return o;
	}

	// sky �������ñ���ʱ��
	void setprotectTime(int i)
	{
		protectTime.addDelay(i * 1000);
	}

	// sky ǿ��ɾ����Ʒ����
	bool DelProtectOverdue()
	{
		if (ownerID == 0)
			return false;

		protectTime = 0;
		ownerID = 0;
		return true;
	}

private:
	DWORD ownerID;
	zRTime protectTime;
	zObject *o;
	zRTime ct;
	zSceneObject(zObject *obj, const zRTime &ct) :zSceneEntry(SceneEntry_Object), ct(ct)
	{
		this->ct.addDelay(600 * 1000);
		o = obj;
		ownerID = 0;
		id = obj->data.qwThisID;
		tempid = obj->base->id;
		strncpy_s(name, obj->data.strName, MAX_NAMESIZE);
	}
};

/**
* \brief �������������
*/
class zSceneEntryIndex : private zNoncopyable
{

protected:

	///������͸�
	zPos sceneWH;
	///������������
	DWORD screenMax;
	///���������Ļ
	DWORD screenx;
	///���������Ļ
	DWORD screeny;

private:

	typedef std::set<zSceneEntry *, std::less<zSceneEntry *> > SceneEntry_SET;
	typedef std::set<SceneNpc *, std::less<SceneNpc *> > Npc_Index;

	typedef UNORDERED_MAP<zPosI, SceneEntry_SET> PosIMapIndex;
	typedef UNORDERED_MAP<DWORD, Npc_Index> SpecialNpc_Index;

	/**
	* \brief map��������
	*/
	PosIMapIndex index[zSceneEntry::SceneEntry_MAX];
	/// �������������
	SceneEntry_SET all[zSceneEntry::SceneEntry_MAX];
	/// ��������npc������
	SpecialNpc_Index special_index;
	/// ���ڹ���npc������
	Npc_Index functionNpc;

	typedef std::map<DWORD, int, std::less<DWORD> > PosiEffectMap;

	typedef PosiEffectMap::iterator PosiEffectMap_iter;
	PosiEffectMap posiEffect[MAX_NPC_GROUP];

	//�ڼ��ص�ʱ����������ϵ������
	typedef UNORDERED_MAP<DWORD, zPosIVector> NineScreen_map;
	typedef NineScreen_map::iterator NineScreen_map_iter;
	typedef NineScreen_map::const_iterator NineScreen_map_const_iter;
	typedef NineScreen_map::value_type NineScreen_map_value_type;
	NineScreen_map ninescreen;
	NineScreen_map direct_screen[8];
	NineScreen_map reversedirect_screen[8];

	void freshEffectPosi(const zPosI oldposi, const zPosI newposi);

public:

	/**
	* \brief ���캯��
	*/
	zSceneEntryIndex() {}
	/**
	* \brief ��������
	*/
	virtual ~zSceneEntryIndex() {}

	virtual void freshGateScreenIndex(SceneUser *pUser, const DWORD screen) = 0;

	bool refresh(zSceneEntry *e, const zPos & newPos);
	bool removeSceneEntry(zSceneEntry *e);
	void execAllOfScreen(const zPosI screen, zSceneEntryCallBack &callback);
	void execAllOfScreen(const zSceneEntry::SceneEntryType type, const zPosI screen, zSceneEntryCallBack &callback);
	void execAllOfScene(zSceneEntryCallBack &callback);
	void execAllOfScene(const zSceneEntry::SceneEntryType type, zSceneEntryCallBack &callback);
	void execAllOfScene_npc(const DWORD id, zSceneEntryCallBack &callback);
	void execAllOfScene_functionNpc(zSceneEntryCallBack &callback);

	void setSceneWH(const zPos sceneWH, const DWORD screenx, const DWORD screeny, const DWORD screenMax);
	zSceneEntry *getSceneEntryByPos(zSceneEntry::SceneEntryType type, const zPos &pos, const bool bState = true, const zSceneEntry::SceneEntryState byState = zSceneEntry::SceneEntry_Normal);

	void execAllOfEffectNpcScreen(const DWORD group, zSceneEntryCallBack &callback);

	/**
	* \brief ��ȡ��ͼ��
	* ��λ�Ǹ��
	* \return ��ͼ��
	*/
	const DWORD width() const { return sceneWH.x; }
	/**
	* \brief ��ȡ��ͼ��
	* ��λ�Ǹ��
	* \return ��ͼ��
	*/
	const DWORD height() const { return sceneWH.y; }
	/**
	* \brief ��ȡ��ͼ��
	* ��λ����
	* \return ��ͼ��
	*/
	const DWORD getScreenX() const { return screenx; }
	/**
	* \brief ��ȡ��ͼ��
	* ��λ����
	* \return ��ͼ��
	*/
	const DWORD getScreenY() const { return screeny; }
	/**
	* \brief ����ת��
	* ��������ת��Ϊ������������
	* \param p ��������ϵͳ
	* \param pi �������ϵͳ
	* \return ����ת������������ϵͳ
	*/
	zPosI &zPos2zPosI(const zPos &p, zPosI &pi) const
	{
		zSceneEntry::zPos2zPosI(sceneWH, p, pi);
		return pi;
	}
	/**
	* \brief ���¼������꣬��֤��Խ��
	* \param pos ����֤������
	*/
	const void zPosRevaluate(zPos &pos) const
	{
		if (pos.x & 0x80000000)
			pos.x = 0;
		if (pos.y & 0x80000000)
			pos.y = 0;
		if (pos.x >= sceneWH.x)
			pos.x = sceneWH.x - 1;
		if (pos.y >= sceneWH.y)
			pos.y = sceneWH.y - 1;
	}
	/**
	* \brief ��֤�����Ƿ�Ϸ����Ƿ�Խ��
	* \param pos ����
	* \return �Ƿ�Ϸ�
	*/
	const bool zPosValidate(const zPos &pos) const { return pos.x < sceneWH.x && pos.y < sceneWH.y; }
	/**
	* \brief ��֤�����Ƿ�Ϸ����Ƿ�Խ��
	* \param posi ����
	* \return �Ƿ�Ϸ�
	*/
	const bool zPosIValidate(const zPosI &posi) const { return posi < screenMax; }
	/**
	* \brief ��������������Ƿ���9����ϵ
	* \param one ��һ�����
	* \param two �ڶ������
	* \return �Ƿ���9����ϵ
	*/
	bool checkTwoPosIInNine(const zPosI one, const zPosI two) const
	{
		int oneX, oneY, twoX, twoY;
		oneX = one % screenx;
		oneY = one / screenx;
		twoX = two % screenx;
		twoY = two / screenx;
		if (abs(oneX - twoX) <= 1 && abs(oneY - twoY) <= 1)
		{
			return true;
		}
		return false;
	}
	/**
	* \brief �ж�����֮������Ƿ񳬳��˰뾶
	* \param pos1 ���
	* \param pos2 �յ�
	* \param radius �뾶
	* \return �Ƿ񳬳���Χ
	*/
	const bool zPosShortRange(const zPos &pos1, const zPos &pos2, const int radius) const
	{
		if (abs((long)(pos1.x - pos2.x)) <= radius
			&& abs((long)(pos1.y - pos2.y)) <= radius)
			return true;
		else
			return false;
	}
	/**
	* \brief �ж�����֮������Ƿ񳬳��˾��η�Χ
	* \param pos1 ���
	* \param pos2 �յ�
	* \param wide ���ο�
	* \param height ���θ�
	* \return �Ƿ񳬳���Χ
	*/
	const bool zPosShortRange(const zPos &pos1, const zPos &pos2, const int wide, const int height) const
	{
		if (abs((long)(pos1.x - pos2.x)) <= wide
			&& abs((long)(pos1.y - pos2.y)) <= height)
			return true;
		else
			return false;
	}
	/*
	* \brief �õ�����ľ���
	* �������ֻ����Ϊ�Ƚ��жϣ�������Ϊʵ�ʵľ���
	* \param pos1 λ��1
	* \param pos2 λ��2
	* \return ����
	*/
	DWORD getDistance(zPos pos1, zPos pos2) const { return abs((long)(pos1.x - pos2.x)) + abs((long)(pos1.y - pos2.y)); }
	/**
	* \brief ����ȡ��
	* \param direct ����
	* \return �෴�ķ���
	*/
	int getReverseDirect(const int direct) const { return (direct + 4) % 8; }
	/**
	* \brief ���������жϾŸ�����
	* \param posiorg ԭ�������
	* \param posinew �����������
	* \return �����ţ����Ϊ-1��ʾ���ǾŸ�����֮һ
	*/
	int getScreenDirect(const zPosI posiorg, const zPosI posinew) const
	{
		using namespace Cmd;
		DWORD orgX = posiorg % screenx;
		DWORD orgY = posiorg / screenx;
		DWORD newX = posinew % screenx;
		DWORD newY = posinew / screenx;
		if (orgX == newX && orgY == newY + 1)
		{
			return _DIR_UP;
		}
		else if (orgX + 1 == newX && orgY == newY + 1)
		{
			return _DIR_UPRIGHT;
		}
		else if (orgX + 1 == newX && orgY == newY)
		{
			return _DIR_RIGHT;
		}
		else if (orgX + 1 == newX && orgY + 1 == newY)
		{
			return _DIR_RIGHTDOWN;
		}
		else if (orgX == newX && orgY + 1 == newY)
		{
			return _DIR_DOWN;
		}
		else if (orgX == 1 + newX && orgY + 1 == newY)
		{
			return _DIR_DOWNLEFT;
		}
		else if (orgX == 1 + newX && orgY == newY)
		{
			return _DIR_LEFT;
		}
		else if (orgX == 1 + newX && orgY == 1 + newY)
		{
			return _DIR_LEFTUP;
		}
		else
			return _DIR_WRONG;
	}

	/**
	* \brief ����������һ�������Ĵ��·���
	* \param myPos �ҵ�λ��
	* \param otherPos �Է���λ��
	* \return ����otherPos����Է���
	*/
	static int getCompDir(const zPos &myPos, const zPos &otherPos)
	{
		int x = otherPos.x - myPos.x;
		int y = otherPos.y - myPos.y;
		int absx = abs(x);
		int absy = abs(y);
		if (absx > absy && absy < absx / 2)
			y = 0;
		else if (absx < absy && absx < absy / 2)
			x = 0;

		int bkDir = 0;

		if (x < 0 && y < 0)
			bkDir = 7;
		else if (x < 0 && 0 == y)
			bkDir = 6;
		else if (x < 0 && y > 0)
			bkDir = 5;
		else if (0 == x && y > 0)
			bkDir = 4;
		else if (x > 0 && y > 0)
			bkDir = 3;
		else if (x > 0 && 0 == y)
			bkDir = 2;
		else if (x > 0 && y < 0)
			bkDir = 1;
		else if (0 == x && y < 0)
			bkDir = 0;
		return bkDir;
	}
	const zPosIVector &getScreenByRange(const zPos &pos, const int range);
	/**
	* \brief ����������ȡ��Χ9������Ļ���
	* \param posi ������
	* \param pv ��������������
	*/
	const zPosIVector &getNineScreen(const zPosI &posi)
	{
		NineScreen_map_const_iter iter = ninescreen.find((DWORD)posi);
		if (iter != ninescreen.end())
		{
			return iter->second;
		}
		//��������쳣����0��ŵ�������
		return ninescreen[(DWORD)-1];
	}

	/**
	* \brief ����������ȡ��ǰ��3������5������Ļ���
	* \param posi ������
	* \param direct ����
	* \return ��������������
	*/
	const zPosIVector &getDirectScreen(const zPosI &posi, const int dir)
	{
		NineScreen_map_const_iter iter = direct_screen[dir].find((DWORD)posi);
		if (iter != direct_screen[dir].end())
		{
			return iter->second;
		}
		//��������쳣����0��ŵ�������
		return direct_screen[dir][(DWORD)-1];
	}

	/**
	* \brief ����������ȡ����3������5������Ļ���
	* \param posi ������
	* \param direct ����
	* \return ��������������
	*/
	const zPosIVector &getReverseDirectScreen(const zPosI &posi, const int dir)
	{
		NineScreen_map_const_iter iter = reversedirect_screen[dir].find((DWORD)posi);
		if (iter != reversedirect_screen[dir].end())
		{
			return iter->second;
		}
		//��������쳣����0��ŵ�������
		return reversedirect_screen[dir][(DWORD)-1];
	}

};

//��Ҫ����AI������npc
typedef std::set<SceneNpc *, std::less<SceneNpc *> > MonkeyNpcs;

enum
{
	MAP_FUNCTION_NORIDE = 0x1,	//sky ������������
	MAP_FUNCTION_CAPITAL = 0x2,	//sky �׶�
	MAP_FUNCTION_MAZE = 0x4,	//sky ���³�
	MAP_FUNCTION_NOSCROLL = 0x8,	//sky ������ʹ�þ���
	MAP_FUNCTION_NORED = 0x10,	//sky ������
	MAP_FUNCTION_NOVICE = 0x20,	//sky ���ֱ���
	MAP_FUNCTION_NOTEAM = 0x40, //sky ���������
	MAP_FUNCTION_NOCALLOBJ = 0x80, //sky ������ʹ������
	MAP_FUNCTION_BATTLEFIEL = 0x100,//sky ս�����ͼ

};

/**
* \brief ���Ӷ���
*/
#define TILE_BLOCK      0x01  // �赲��
#define TILE_MAGIC_BLOCK  0x02  // ħ���赲��
#define TILE_NOCREATE    0x04  // ���ܽ����
#define TILE_DOOR      0x08  // ��
#define TILE_ENTRY_BLOCK  0x10  // �������Npc�赲
#define TILE_OBJECT_BLOCK  0x20  // ��Ʒ�赲
#pragma  pack(1)
/**
* \brief �������ݽṹ
*
*/
struct stSrvMapTile
{
	BYTE  flags;  // ��������
	BYTE  type;  // ��������
};
#pragma pack()

typedef stSrvMapTile Tile;
typedef std::vector<Tile> zTiles;


/**
* \brief ��ͼ����
*/
class Scene :public zScene, public zSceneEntryIndex
{

protected:

	Scene();

public:

	//��Session����ˢ�µ�npc
	std::map<DWORD, SceneNpc *> bossMap;

	/**
	* \brief �������Ͷ���
	*/
	enum SceneType
	{
		STATIC,   /// ��̬��ͼ
		GANG    /// ��̬��ͼ
	};

	virtual ~Scene();
	virtual bool save() = 0;

	bool init(DWORD countryid, DWORD mapid);
	void final();
	void freshGateScreenIndex(SceneUser *pUser, const DWORD screen);

	bool sendCmdToWatchTrap(const zPosI screen, const void *pstrCmd, const int nCmdLen);
	bool sendCmdToNine(const zPosI screen, const void *pstrCmd, const int nCmdLen, unsigned short dupIndex = 0);
	bool sendCmdToNineUnWatch(const zPosI screen, const void *pstrCmd, const int nCmdLen);
	bool sendCmdToScene(const void *pstrCmd, const int nCmdLen, unsigned short dupIndex = 0);
	bool sendCmdToNineExceptMe(zSceneEntry *pEntry, const zPosI screen, const void *pstrCmd, const int nCmdLen);
	bool sendCmdToDirect(const zPosI screen, const int direct, const void *pstrCmd, const int nCmdLen, unsigned short dupIndex = 0);
	bool sendCmdToReverseDirect(const zPosI screen, const int direct, const void *pstrCmd, const int nCmdLen, unsigned short dupIndex = 0);
	bool findEntryPosInNine(const zPos &vpos, zPosI vposi, zPosVector &range);
	bool findEntryPosInOne(const zPos &vpos, zPosI vposi, zPosVector &range);

	int summonNpc(const t_NpcDefine &define, const zPos &pos, zNpcB *base, unsigned short dupIndex = 0);
	template <typename Npc>
	Npc* summonOneNpc(const t_NpcDefine &define, const zPos &pos, zNpcB *base, unsigned short dupIndex, DWORD standTime = 0, zNpcB* abase = NULL, BYTE vdir = 4, SceneEntryPk * m = NULL);

	bool refreshNpc(SceneNpc *sceneNpc, const zPos & newPos);

	/**
	* \brief ��ȡ������ͼ
	* \return ������ͼID
	*/
	DWORD backtoMap() const { return backtoMapID; }
	/**
	* \brief ��ȡ�سǵ�ͼ
	* \return �سǵ�ͼID
	*/
	DWORD backtoCityMap() const { return backtoCityMapID; }
	/**
	* \brief �����໥pk�ĵȼ�
	* \return ��true
	*/
	DWORD getPkLevel() const { return pklevel; }
	/**
	* \brief ���õ�ͼ�Ƿ��������
	* \return ������ʱtrue
	*/
	bool canRide() const { return !(function & MAP_FUNCTION_NORIDE); }
	/**
	* \brief ����ʹ�þ���
	* \return �����Ƿ���true
	*/
	bool canUserScroll() const { return !(function & MAP_FUNCTION_NOSCROLL); }
	/**
	* \brief ���õ�ͼ�Ƿ�������
	* \return �����ʱtrue
	*/
	bool noTeam() const { return (function & MAP_FUNCTION_NOTEAM); }
	/**
	* \brief ���õ�ͼ�Ƿ����ʹ������
	* \return �Ƿ����
	*/
	bool checkCallObj() const { return (function & MAP_FUNCTION_NOCALLOBJ); }
	/**
	* \brief �Ƿ�������
	* \return �����Ƿ���true
	*/
	bool isMainCity() const { return (function & MAP_FUNCTION_CAPITAL); }
	/**
	* \brief �Ƿ��ǵض���
	* \return �����Ƿ���true
	*/
	bool isField() const { return (function & MAP_FUNCTION_MAZE); }
	/**
	* \brief sky �޸�Ϊ���ֱ�����ͼ
	* \return �����ֱ�����ͼ����true
	*/
	bool isNovice() const { return (function & MAP_FUNCTION_NOVICE); }
	/**
	* \brief �Ƿ��ǲ�������ͼ
	* \return ��true
	*/
	bool isNoRedScene() const { return (function & MAP_FUNCTION_NORED); }
	/**
	* \brief �Ƿ���PK��ͼ
	* \return ��true
	*/
	bool isPkMap() const { return getRealMapID() >= 213 && getRealMapID() <= 215; }
	/**
	* \brief ��ȡ��ͼ���
	* \return ��ͼ���
	*/
	const DWORD getRealMapID() const { return id & 0x0000FFFF; }
	/**
	* \brief ��ȡ��ͼ��������
	* \return ��ͼ��������
	*/
	const DWORD getCountryID() const { return countryID; }

	const char *getCountryName() const;

	/**
	* \brief ��ȡ��ͼ����
	* \return ��ͼ����(���ڷ����)
	*/
	const char *getName() const { return name; }
	/**
	* \brief ��ȡ��ͼ����
	* \return ��ͼ����(δ������ϵ�����)
	*/
	const char *getRealName() const
	{
		char *real = const_cast<char*>(strstr(name, "��"));
		if (real != NULL)
			return real + 2;
		else
			return name;
	}
	/**
	* \brief ��ȡ��ͼ�ļ�����
	* ���Ʋ�����ǰ׺
	* \return ��ͼ�ļ�����(���ڷ����)
	*/
	const char *getFileName() const { return fileName.c_str(); }
	/**
	* \brief ��ȡ��ͼ�ļ�����
	* ���Ʋ�����ǰ׺
	* \return ��ͼ�ļ�����(Ϊ������ϵ�����)
	*/
	const char *getRealFileName() const { return fileName.c_str() + fileName.find(".") + 1; }
	/**
	* \brief ��ȡָ����ͼ�ļ�����
	* ���Ʋ�����ǰ׺
	* \param file �ļ���
	* \return ��ͼ�ļ�����(Ϊ������ϵ�����)
	*/
	const char *getRealFileName(std::string file) const { return file.c_str() + file.find(".") + 1; }
	/**
	* \brief ��������赲��Ϣ
	* \param pos ����
	* \param block �赲���
	* \return �Ƿ��赲��
	*/
	const bool checkBlock(const zPos &pos, const BYTE block) const
	{
		if (zPosValidate(pos))
			return (0 != (allTiles[pos.y * width() + pos.x].flags & block));
		else
			return true;
	}
	/**
	* \brief ��������赲��Ϣ
	* \param pos ����
	* \return �Ƿ��赲��
	*/
	const bool checkBlock(const zPos &pos) const { return checkBlock(pos, TILE_BLOCK | TILE_ENTRY_BLOCK); }
	/**
	* \brief ����Ŀ���赲����
	* \param pos ����
	* \param block �赲���
	*/
	void setBlock(const zPos &pos, const BYTE block)
	{
		if (zPosValidate(pos))
			allTiles[pos.y * width() + pos.x].flags |= block;
	}
	/**
	* \brief ����Ŀ���赲����
	* \param pos ����
	*/
	void setBlock(const zPos &pos) { setBlock(pos, TILE_ENTRY_BLOCK); }

	// [ranqd] ���������赲����
	void setBlock(const zZone &zone, const BYTE block)
	{
		for (int x = zone.pos.x; x < zone.pos.x + zone.width; x++)
		{
			for (int y = zone.pos.y; y < zone.pos.y + zone.height; y++)
			{
				zPos pos;
				pos.x = x;
				pos.y = y;
				if (zPosValidate(pos))
					allTiles[pos.y * width() + pos.x].flags |= block;
			}
		}
	}

	void setBlock(const zZone &pos) { setBlock(pos, TILE_ENTRY_BLOCK); }
	/**
	* \brief ���Ŀ���赲����
	* \param pos ����
	* \param block �赲���
	*/
	void clearBlock(const zPos &pos, const BYTE block)
	{
		if (zPosValidate(pos))
			allTiles[pos.y * width() + pos.x].flags &= ~block;
	}
	/**
	* \brief ���Ŀ���赲����
	* \param pos ����
	*/
	void clearBlock(const zPos &pos) { clearBlock(pos, TILE_ENTRY_BLOCK); }
	/**
	* \brief ��������赲��Ϣ
	* ��Ҫ�ڶ���Ʒ��ʱ��ʹ��
	* \param pos ����
	* \return �Ƿ��赲��
	*/
	const bool checkObjectBlock(const zPos &pos) const { return checkBlock(pos, TILE_BLOCK | TILE_OBJECT_BLOCK); }
	/**
	* \brief ����Ŀ���赲����
	* ��Ҫ�ڶ���Ʒ��ʱ��ʹ��
	* \param pos ����
	*/
	void setObjectBlock(const zPos &pos) { setBlock(pos, TILE_OBJECT_BLOCK); }
	/**
	* \brief ���Ŀ���赲����
	* ��Ҫ�ڶ���Ʒ��ʱ��ʹ��
	* \param pos ����
	*/
	void clearObjectBlock(const zPos &pos) { clearBlock(pos, TILE_OBJECT_BLOCK); }
	/**
	* \brief ��ȡ�ر�����
	* \param pos ����
	* \return ���صر�����
	*/
	const Tile* getTile(const zPos &pos) const
	{
		if (zPosValidate(pos))
			return &allTiles[pos.y * width() + pos.x];
		else
			return NULL;
	}
	/**
	* \brief ����λ�õõ�·��
	* \param pos Ҫ���ҵ�λ��
	* \return �ҵ���·��,ʧ�ܷ���0
	*/
	//WayPoint *getWayPoint(const zPos &pos) { return wpm.getWayPoint(pos); }
	/**
	* \brief ����Ŀ���ҵ�·��
	* \param filename Ŀ���ͼ�ļ���
	* \return �ҵ���·��,ʧ�ܷ���0
	*/
	//WayPoint *getWayPoint(const char *filename) { return wpm.getWayPoint(filename); }
	/**
	* \brief ���ѡһ��·��
	* \return �ҵ���·��
	*/
	//WayPoint *getRandWayPoint() { return wpm.getRandWayPoint(); }
	/**
	* \brief ���ص�ͼ�ϵ�����
	* \return һ�ŵ�ͼ�ϵ�����
	*/
	const DWORD countUser() const { return userCount; }
	/**
	* \brief ��������
	* \return ���Ӻ������
	*/
	const DWORD addUserCount() { return ++userCount; }
	/**
	* \brief ��������
	* \return ���ٺ������
	*/
	const DWORD subUserCount() { return --userCount; }

	bool findPosForObject(const zPos &pos, zPos &findedPos);
	bool findPosForUser(const zPos &pos, zPos &findedPos);
	SceneUser *getSceneUserByPos(const zPos &pos, const bool bState = true, const zSceneEntry::SceneEntryState byState = zSceneEntry::SceneEntry_Normal);
	SceneUser *getUserByID(DWORD userid);
	SceneUser *getUserByTempID(DWORD usertempid);
	SceneUser *getUserByName(const char *username);
	SceneNpc *getSceneNpcByPos(const zPos &pos, const bool bState = true, const zSceneEntry::SceneEntryState byState = zSceneEntry::SceneEntry_Normal);
	SceneNpc *getNpcByTempID(DWORD npctempid);
	zSceneObject *getSceneObjectByPos(const zPos &pos);

	bool addObject(unsigned short dupIndex, zObject *ob, const zPos &pos, const unsigned long overdue_msecs = 0, const unsigned long dwID = 0, int protime = 10);
	bool addObject(unsigned short dupIndex, zObjectB *ob, const int num, const zPos &pos, const unsigned long dwID = 0, DWORD npc_mul = 0, DWORD teamID = 0);
	void removeUser(SceneUser *so);
	void removeObject(zSceneObject *so);
	void removeNpc(SceneNpc *sn);
	bool checkZoneType(const zPos &pos, const int type) const;
	int getZoneType(const zPos &pos) const;
	bool randzPosByZoneType(const int type, zPos &pos) const;
	int changeMap(SceneUser *pUser, bool deathBackto = true, bool ignoreWar = false);
	bool randzPosByZoneType(const int type, zPos &pos, const zPos orign);
	bool randzPosOnRect(const zPos &center, zPos &pos, WORD rectx = SCREEN_WIDTH, WORD recty = SCREEN_HEIGHT) const;

	bool getNextPos(int &side, const int direct, const zPos &orgPos, const int clockwise, zPos &crtPos) const;
	void getNextPos(const zPos &orgPos, const int dir, zPos &newPos) const;
	bool SceneEntryAction(const zRTime& ctv, const DWORD group);
	void removeSceneObjectInOneScene();

	
	void reliveSecGen();
	const DWORD getTax() const { return countryTax; }
	void addFieldMapName(const char *name)
	{
		stMapName mapname;
		strncpy_s(mapname.strMapName, name, MAX_NAMESIZE);
		fieldMapName.push_back(mapname);
	}
	void clearFieldMapName() { fieldMapName.clear(); }
	DWORD getField(const char *ou) const
	{
		stMapName *out = (stMapName *)ou;
		int i = 0;
		for (std::vector<stMapName>::const_iterator iter = fieldMapName.begin(); iter != fieldMapName.end(); iter++)
		{
			strncpy_s((&out[i])->strMapName, (*iter).strMapName, MAX_NAMESIZE);
			i++;
		}
		return i;
	}
	bool checkField(const char *out) const
	{
		for (std::vector<stMapName>::const_iterator iter = fieldMapName.begin(); iter != fieldMapName.end(); iter++)
		{
			if (strncmp((char *)out, (*iter).strMapName, MAX_NAMESIZE) == 0)
			{
				return true;
			}
		}
		return false;
	}
	void addMainMapName(const char *name)
	{
		stMapName mapname;
		strncpy_s(mapname.strMapName, name, MAX_NAMESIZE);
		mainMapName.push_back(mapname);
	}

	void clearMainMapName() { mainMapName.clear(); }
	DWORD getMainCity(const char *ou) const
	{
		stMapName *out = (stMapName *)ou;
		int i = 0;
		for (std::vector<stMapName>::const_iterator iter = mainMapName.begin(); iter != mainMapName.end(); iter++)
		{
			strncpy_s((&out[i])->strMapName, (*iter).strMapName, MAX_NAMESIZE);
			i++;
		}
		return i;
	}
	bool checkMainCity(const char *out) const
	{
		for (std::vector<stMapName>::const_iterator iter = mainMapName.begin(); iter != mainMapName.end(); iter++)
		{
			if (strncmp((char *)out, (*iter).strMapName, MAX_NAMESIZE) == 0)
			{
				return true;
			}
		}
		return false;
	}

	void addIncMapName(const char *name)
	{
		stMapName mapname;
		strncpy_s(mapname.strMapName, name, MAX_NAMESIZE);
		incMapName.push_back(mapname);
	}

	void clearIncMapName() { incMapName.clear(); }
	DWORD getIncCity(const char *ou) const
	{
		stMapName *out = (stMapName *)ou;
		int i = 0;
		for (std::vector<stMapName>::const_iterator iter = incMapName.begin(); iter != incMapName.end(); iter++)
		{
			strncpy_s((&out[i])->strMapName, (*iter).strMapName, MAX_NAMESIZE);
			i++;
		}
		return i;
	}
	bool checkIncCity(const char *out) const
	{
		for (std::vector<stMapName>::const_iterator iter = incMapName.begin(); iter != incMapName.end(); iter++)
		{
			if (strncmp((char *)out, (*iter).strMapName, MAX_NAMESIZE) == 0)
			{
				return true;
			}
		}
		return false;
	}


	DWORD sceneExp(DWORD exp) const { return (DWORD)(exp * exprate); }
	DWORD winnerExp(DWORD exp) const
	{/*
		if (winner_exp)
		{
			return (DWORD)(exp * 0.5f);
		}
		else*/
		{
			return 0;
		}
	}
	BYTE getLevel() const { return level; }
	bool checkUserLevel(SceneUser *pUser);


	/**
	* \brief �Ƿ����շѵ�ͼ
	* \return �Ƿ����շѵ�ͼ
	*/
	bool isTrainingMap()
	{
		DWORD i = id & 0x0000FFFF;
		return (i >= 193 && i <= 202);
	}
	void initRegion(zRegion &reg, const zPos &pos, const WORD width, const WORD height);

	bool randPosByRegion(const zPosIndex &index, zPos &pos) const;
public:
	struct stMapName
	{
		stMapName()
		{
			bzero(strMapName, sizeof(strMapName));
		}
		char strMapName[MAX_NAMESIZE + 1];
	};
	//�������ͼ
	std::vector<stMapName> fieldMapName;
	//���ǵ�ͼ
	std::vector<stMapName> mainMapName;
	//��ֵ��ͼ
	std::vector<stMapName> incMapName;
	std::map<std::string, std::string> params;

	///��npc���鴦��
	DWORD execGroup;

	/// �����ս���б�־
	bool isUnionDare;

	/// �ó����������
	DWORD dwHoldUnionID;

	/// �ó���ռ���߹���ID
	DWORD dwHoldCountryID;


	/// ��ʽ��ս���ڸó������еı�־
	bool isCountryFormalDare;

	/// �ʳ�ս���ڸó������еı�־
	bool isEmperorDare;

	/// �ʳ�ս���ط�
	DWORD dwEmperorDareDef;

	///�������Ĺ����б�
	//std::list<Rush *> rushList;

	///һ�붨ʱ��
	Timer _one_sec;

	///�Ѿ���ʼ��
	bool inited;

	///���еĵ�ͼ����
	zTiles allTiles;
	///���е�npc����
	NpcDefineVector npcDefine;
	///�����и�������Ķ���
	ZoneTypeDefVector zoneTypeDef;

	///�������û���
	DWORD userCount;
	///�������ͼû��������ʱ��Ҫ��ת���ĵ�ͼ
	DWORD backtoMapID;
	///�ص����ǵĵ�ͼid
	DWORD backtoCityMapID;
	///�ص���սĿ�ĵ�
	DWORD backtoDareMapID;
	/// �����������Ӧ�ûص��ĵ�ͼid(û�й�����Ϣ)
	DWORD foreignerBacktoMapID;
	/// �ڹ�����������Ӧ�ûص��ĵ�ͼid(û�й�����Ϣ)
	DWORD commonCountryBacktoMapID;
	/// �޹��������������������
	DWORD commonUserBacktoMapID;
	/// ��սս��������,�ط����������
	DWORD countryDefBackToMapID;
	///��ͼ����˵��
	DWORD function;
	/// ���໥pk�ĵȼ�
	DWORD pklevel;
	///����id
	DWORD countryID;
	///������Ӧ���ļ���
	std::string fileName;
	///·�������
	WayPointM wpm;
	///����ͼ��ȡ˰��
	DWORD countryTax;
	///����ͼ����������С��ҵȼ�
	BYTE level;
	///������ͼ�ӳ�
	float exprate;

	struct FixedRush
	{
		DWORD id;//ID
		DWORD nextTime;//�´ε�ʱ��
		DWORD allStart;//�ܿ�ʼʱ��
		DWORD allEnd;//�ܽ���ʱ��
		int weekDay;//���ڼ�
		tm startTime;//һ���п�ʼ��ʱ��
		tm endTime;//һ���н�����ʱ��
		DWORD delay;//��ʼ�ӳ�

		FixedRush()
		{
			id = 0;//ID
			nextTime = 0;//�´ε�ʱ��
			allStart = 0;//�ܿ�ʼʱ��
			allEnd = 0;//�ܽ���ʱ��
			weekDay = 0;//���ڼ�
			delay = 0;//��ʼ�ӳ�
		}
	} fixedRush;

	//sky ս�������ļ��������·��
	char DulesFileName[MAX_PATH];

	bool initWayPoint(zXMLParser *parser, const xmlNodePtr node, DWORD countryid);
	bool loadMapFile();
	void initNpc(SceneNpc *sceneNpc, zRegion *init_region, zPos myPos = zPos(0, 0));
	bool initByNpcDefine(const t_NpcDefine *pDefine);

	void runCircle_anti_clockwise(const int side, const DWORD X, const DWORD Y, DWORD &CX, DWORD &CY) const;
	void runCircle_clockwise(const int side, const DWORD X, const DWORD Y, DWORD &CX, DWORD &CY) const;

	void updateSceneObject();

	zPosIndex _index;  /// ���赲������
public:
	//sky ����ս���ೡ���麯��
	virtual bool IsGangScene() { return false; }
	virtual void GangSceneTime(const zRTime& ctv) { return; }
	virtual DWORD ReCampThisID(BYTE index) { return 0; }
	//sky ����ս���ೡ���麯�� end
};

/**
* \brief ��̬����
*
*/
class StaticScene :public Scene
{
public:
	StaticScene();
	~StaticScene();
	bool save();
	virtual bool IsGangScene() { return false; }
};

/**
* \brief ��ÿ��sceneִ�еĻص�����
*
*/
struct SceneCallBack
{
	virtual bool exec(Scene *scene) = 0;
	virtual ~SceneCallBack() {};
};

/**
* \brief ����������
*
*/
class SceneManager
	:public zSceneManager
{
public:
	typedef std::vector<std::pair<DWORD, DWORD> > NewZoneVec;
	typedef NewZoneVec::iterator newZoneVec_iter;
public:

	DWORD getMapId(DWORD countryid, DWORD mapid);

private:
	///Ψһʵ��
	static SceneManager * sm;
	///ΨһID������
	zUniqueDWORDID *sceneUniqeID;

	///�Ƿ��ѳ�ʼ��
	bool inited;

	SceneManager();
	~SceneManager();

	bool getUniqeID(QWORD &tempid);
	void putUniqeID(const QWORD &tempid);

	///sky ����ΨһID������
	zUniqueDWORDID *sceneTeamID;

	//sky DWORD1 ����ΨһID  
	//TeamManager �������
	//std::map<DWORD, TeamManager*> ScenTeamMap;

	bool newzone;
	NewZoneVec newzon_vec;

public:
	static SceneManager &getInstance();
	static void delInstance();
	bool init();
	void final();

	NewZoneVec &queryNewZonePos();
	bool isNewZoneConfig();
	bool randzPosNewZone(Scene *intoScene, zPos &findedPos);
	void addNewZonePos(DWORD x, DWORD y);
	void setNewZoneConfig(bool type);
	Scene * getSceneByFileName(const char * name);
	Scene * getSceneByName(const char * name);
	Scene * getSceneByTempID(DWORD tempid);
	Scene * getSceneByID(DWORD id);
	Scene * loadScene(/*Scene::SceneType type*/int type, DWORD countryid, DWORD mapid);
	//sky ����ս����̬��ͼ����
	Scene * loadBattleScene(DWORD baseid);
	//sky end
	void unloadScene(std::string &name);
	void unloadScene(Scene * &scene);
	void unloadAllScene();

	void freshEverySceneField();
	void execEveryScene(SceneCallBack &callback);
	//void execEveryMap(MapCallBack &callback);
	template <class YourEntry>
	void execEveryMap(execEntry<YourEntry> &callback)
	{
		SceneManager::MapMap_iter map_iter = SceneManager::getInstance().map_info.begin();
		for (; map_iter != SceneManager::getInstance().map_info.end(); map_iter++)
		{
			callback.exec(&map_iter->second);
		}
	}

	void checkUnloadOneScene();

	//sky �������
	///sky ��������ΨһID�������ķ���
	bool getTeamID(DWORD &tempid);
	void putTeamID(const DWORD &tempid);

	//sky ���ݶ����ΨһID���ض������ָ��
	//TeamManager* GetMapTeam(DWORD TeamID);
	//bool SceneNewTeam(SceneUser *pUser);		//sky �½�����
	//bool SceneNewTeam(Cmd::Session::t_Team_Data* send);	//sky �½�����(�糡��ר��)
														//sky ɾ����ǰ�����Ķ����������Ķ��� ͬʱ֪ͨSessionҲɾ������������Ķ���
	bool SceneDelTeam(DWORD TeamID);
	//sky ֻɾ����ǰ�����Ķ����������Ķ���
	bool DelMapTeam(DWORD TeamID);
	//sky �����������������roll����
	void TeamRollItme();
	//sky ���� end

	/**
	* \brief ������Ϣ
	*
	*/
	struct CountryInfo
	{
		///���
		DWORD id;
		///����
		char name[MAX_NAMESIZE + 1];
		///���ڵĵ�ͼ����
		DWORD mapid;
		///���ҹ��ܱ�ʶ�ֶ�
		DWORD function;
	};
	/**
	* \brief ��ͼ��Ϣ
	*
	*/
	struct MapInfo
	{
		///���
		DWORD id;
		///����
		char name[MAX_NAMESIZE + 1];
		///��Ӧ�ĵ�ͼ�ļ���
		char filename[MAX_NAMESIZE + 1];
		///����ڸõ�ͼ����ص��ĵ�ͼ
		DWORD backto;
		///����ڸõ�ͼ����ص��ĳ���
		DWORD backtoCity;
		///����������ͼ����ص��ĳ���
		DWORD foreignbackto;
		///����ڹ�������ͼ����ص��ĳ���
		DWORD commoncountrybackto;
		///�޹������������ͼ����ص��ĳ���
		DWORD commonuserbackto;
		///��սĿ�ĵ�
		DWORD backtodare;
		///��ս�ڼ�,�ڹ�սս����Ŀǰ�����ǣ�������,�����������
		DWORD countrydarebackto;
		///��ս�ڼ�,�ڹ�սս����Ŀǰ�����ǣ�������,�ط��������
		DWORD countrydefbackto;
		///���໥pk�ĵȼ�
		DWORD pklevel;
		///��ʾ�õ�ͼĳЩ�����Ƿ����,�����
		DWORD function;
		///��ʾ�õ�ͼ�����level�������ҽ���
		BYTE level;
		///��ʾ�õ�ͼ�ľ���ӳ�(ʹ��ʱ/100�������)
		BYTE exprate;
	};
	typedef std::map<DWORD, CountryInfo> CountryMap;
	typedef CountryMap::iterator CountryMap_iter;
	typedef CountryMap::value_type CountryMap_value_type;
	///������Ϣ��ID��ӳ��
	CountryMap country_info;
	DWORD getCountryIDByCountryName(const char *name);
	const char * getCountryNameByCountryID(DWORD);
	DWORD getMapIDByMapName(const char *name);
	const char *getMapMapNameByMapID(DWORD mapid);
	DWORD buildMapID(DWORD countryid, DWORD mapid);
	bool buildMapName(DWORD countryid, const char *in, char *out);
	bool buildMapName(DWORD countryid, DWORD mapid, char *out);
	typedef std::map<DWORD, MapInfo> MapMap;
	typedef MapMap::value_type MapMap_value_type;
	typedef MapMap::iterator MapMap_iter;
	///��ͼ��Ϣ��ID��ӳ��
	MapMap map_info;
};


/**
* \brief ��ÿ������npcִ�еĻص�
*
*/
struct specialNpcCallBack
{
public:
	virtual bool exec(SceneNpc *npc) = 0;
	virtual ~specialNpcCallBack() {};
};

/**
* \brief npc������
*
*/
class SceneNpcManager : public zEntryMgr< zEntryTempID >
{
public:

	bool init();
	bool addSceneNpc(SceneNpc *sceneNpc);
	bool addSpecialNpc(SceneNpc *, bool = false);
	void removeSceneNpc(SceneNpc *sceneNpc);

	SceneNpc *getNpcByTempID(DWORD tempid);
	static SceneNpcManager &getMe();
	static void destroyMe();
	/**
	* \brief ��ÿ��npcִ�лص�����
	*
	*
	* \param exec �ص�����
	* \return �Ƿ����ִ��
	*/
	template <class YourNpcEntry>
	bool execEveryNpc(execEntry<YourNpcEntry> &exec)
	{
		rwlock.rdlock();
		bool ret = execEveryEntry<>(exec);
		rwlock.unlock();
		return ret;
	}

	/**
	* \brief ɾ������������npc
	*
	* \param pred �ж�����
	*/
	template <class YourNpcEntry>
	void removeNpc_if(removeEntry_Pred<YourNpcEntry> &pred)
	{
		rwlock.wrlock();
		removeEntry_if<>(pred);
		rwlock.unlock();
	}

	/**
	* \brief ɾ��һ�����ڵ�npc
	*
	*
	* \param scene ����
	*/
	void removeNpcInOneScene(Scene *scene);
	void SpecialAI();
	/**
	* \brief ��ÿ������npcִ�лص�������
	*
	*
	* \param callback �ص�����
	* \return
	*/
	void execAllSpecialNpc(specialNpcCallBack &callback)
	{
		rwlock.wrlock();
		for (MonkeyNpcs::iterator it = specialNpc.begin(); it != specialNpc.end(); it++)
		{
			if (!callback.exec(*it))
			{
				rwlock.unlock();
				return;
			}
		}
		rwlock.unlock();
	}

	MonkeyNpcs &getSepcialNpc()
	{
		return specialNpc;
	}
	bool getNpcCommonChat(DWORD type, char * content);
	void removeSpecialNpc(SceneNpc *);
	void closeFunctionNpc();
private:
	///specialNpc��ָ��ʹû������ڸ���ҲҪ�������NPC
	///�������boss������NPC
	MonkeyNpcs specialNpc;

	SceneNpcManager();
	~SceneNpcManager();

	///SceneNpcManager��Ψһʵ��
	static SceneNpcManager *snm;
	///��д��
	zRWLock rwlock;

	bool getUniqeID(QWORD &tempid) { return true; }
	void putUniqeID(const QWORD &tempid) {}

	///npc���˵��������
	std::map<DWORD, std::vector<std::string> > NpcCommonChatTable;
	///npc���˵���ĸ���
	std::map<DWORD, int> NpcCommonChatRate;

	bool loadNpcCommonChatTable();
};

//sky ��̬��ͼ������
class stRangMap
{
private:
	WORD Countryid;	//sky ս������ID
	WORD BaseID;		//sky ԭID(���������Ѱ�ҵ�ͼ�Ļ�������)
	WORD MinID;			//sky �ó�����̬�ɷ������СID
	WORD MaxID;			//sky �ó�����̬�ɷ�������ID
	zUniqueDWORDID * MapIDManager;	//sky ΨһID������

public:
	stRangMap()
	{
		Countryid = 0;
		BaseID = 0;
		MinID = 0;
		MaxID = 0;
		MapIDManager = NULL;
	}

	~stRangMap()
	{
		if (MapIDManager)
			delete MapIDManager;
	}

	void init(WORD countryid, WORD baseid, WORD minid, WORD maxid)
	{
		Countryid = countryid;
		BaseID = baseid;
		MinID = minid;
		MaxID = maxid;
		MapIDManager = new zUniqueDWORDID(minid, maxid);
	}

	WORD GetCountryid()
	{
		return Countryid;
	}

	/**
	* \brief ����һ��ΨһID
	*/
	bool getUniqeID(QWORD &tempid)
	{
		tempid = MapIDManager->get();
		return (tempid != MapIDManager->invalid());
	}

	/**
	* \brief �ͷ�ΨһID
	*/
	void putUniqeID(const QWORD &tempid)
	{
		MapIDManager->put(tempid);
	}
};

//sky ��̬��ͼ��������
extern std::map<WORD, stRangMap*> RangMapData;


// �����ϵ��߶��� 
struct zItemEntry :public zEntry
{
public:
	// id=ΨһIDҲ��λ���±�(0��ʼ)
	DWORD itemID;
	DWORD itemNum;
};

/*
 * ��Ʒ������ 	
 */
class zItemManager : public zEntryMgr< zEntryID, zEntryTempID >
{
protected:

	zRWLock rwlock;

	zItemEntry* getItemEntryByID(DWORD id)
	{
		rwlock.rdlock();
		zItemEntry *ret = (zItemEntry *)getEntryByID(id);
		rwlock.unlock();
		return ret;
	}

	zItemEntry* getItemEntryByTempID(DWORD tempid)
	{
		rwlock.rdlock();
		zItemEntry *ret = (zItemEntry *)getEntryByTempID(tempid);
		rwlock.unlock();
		return ret;
	}

	bool addItem(zItemEntry *user)
	{
		rwlock.wrlock();
		bool ret = addEntry((zEntry *)user);
		rwlock.unlock();
		return ret;
	}

	void removeItem(zItemEntry *user)
	{
		rwlock.wrlock();
		removeEntry((zEntry *)user);
		rwlock.unlock();
	}

	template <class YourItemEntry>
	void removeItem_if(removeEntry_Pred<YourItemEntry> &pred)
	{
		rwlock.wrlock();
		removeEntry_if<>(pred);
		rwlock.unlock();
	}

	template <class YourItemEntry>
	bool execEveryItemEntry(execEntry<YourItemEntry> &exec)
	{
		rwlock.rdlock();
		bool ret = execEveryEntry<>(exec);
		rwlock.unlock();
		return ret;
	}

public:

	zItemManager()
	{

	}

	~zItemManager()
	{
		clear();
	}
};


struct zSkill;
using namespace SkillDef;
class ScenePk
{
public:
	static bool physicalMagicU2U(const Cmd::stAttackMagicUserCmd *rev, SceneUser *pAtt, SceneUser *pDef);
	static bool attackDeathUser(SceneUser *pAtt, SceneUser *pDef);
	static bool sendChangedUserData(SceneUser *pUser);
	static bool attackDeathNpc(SceneEntryPk *pAtt, SceneNpc *pDef);
	static bool attackFailToMe(const Cmd::stAttackMagicUserCmd *rev, SceneEntryPk * pAtt, bool failed = true, bool me = false);
	static void  checkProtect(SceneEntryPk *pAtt, SceneEntryPk *pDef);
	static bool attackUserCmdToNine(const Cmd::stAttackMagicUserCmd *rev, SceneEntryPk *pAtt);
	static void attackRTHpAndMp(SceneUser *pUser);
	static void attackRTExp(SceneUser *pUser, DWORD exp, DWORD dwTempID = 0, BYTE byType = 0);
	static bool attackRTCmdToNine(const Cmd::stAttackMagicUserCmd *rev, SceneEntryPk *pAtt, SceneEntryPk *pDef, const SDWORD sdwHP, BYTE byLuck);
	static bool checkAttackSpeed(SceneUser *pAtt, const Cmd::stAttackMagicUserCmd *rev);
	static void  calpdamU2U(const Cmd::stAttackMagicUserCmd *rev, SceneUser *pAtt, SceneUser *pDef);
	static void  calpdamU2N(const Cmd::stAttackMagicUserCmd *rev, SceneUser *pAtt, SceneNpc *pDef);
	static void  calmdamU2U(const Cmd::stAttackMagicUserCmd *rev, SceneUser *pAtt, SceneUser *pDef);
	static void calmdamU2N(const Cmd::stAttackMagicUserCmd *rev, SceneUser *pAtt, SceneNpc *pDef);
	static void calpdamN2U(const Cmd::stAttackMagicUserCmd *rev, SceneNpc *pAtt, SceneUser *pDef);
	static void calmdamN2U(const Cmd::stAttackMagicUserCmd *rev, SceneNpc *pAtt, SceneUser *pDef);
	static void calpdamN2N(const Cmd::stAttackMagicUserCmd *rev, SceneNpc *pAtt, SceneNpc *pDef);
	static void calmdamN2N(const Cmd::stAttackMagicUserCmd *rev, SceneNpc *pAtt, SceneNpc *pDef);
};

/// �����ƶ�����ö��
enum {
	SKILL_GOOD = 0,
	SKILL_BAD = 1
};

/// ����״̬����ö��
enum {
	SKILL_TYPE_INITIAVITE = 1,// ��������
	SKILL_TYPE_RECOVERY = 2,  // ��ʱ��������
	SKILL_TYPE_PASSIVENESS = 3  // ���ñ�������
};

/// ����״̬������ֵö��
enum {
	SKILL_ACTIVE = 1,//  �ӵ��MAP��
	SKILL_RECOVERY,    //  �ӵ���ʱ����MAP��
	SKILL_PASSIVENESS,  //  �ӵ����ñ���MAP��
	SKILL_RETURN,    //  ���ӵ��κ�MAP��
	SKILL_BREAK,    //  ������Ͷ�Ų���
};

/// ����״ִ̬�в���ö��
enum {
	ACTION_STEP_DOPASS = 0,// һ������״̬�Ŀ�ʼ����
	ACTION_STEP_START = 1,// һ������״̬�Ŀ�ʼ����
	ACTION_STEP_TIMER,  // һ������״̬�Ķ�ʱ����
	ACTION_STEP_STOP,  // һ������״̬��ֹͣ����
	ACTION_STEP_CLEAR,  // һ������״̬���ⲿ���
	ACTION_STEP_RELOAD,    // һ������״̬����������
};

/// ����״̬�����Ŀ����
#define SKILLSTATENUMBER 354   /// ����״̬����� [sky]���䵽400

/**
* \brief  ����״̬Ԫ������
*/
struct SkillStatusCarrier
{
	/// ���ܲ���
	const SkillStatus *status;
	/// �����ֵ�
	const zSkillB *skillbase;
	/// �յ��Ĺ�����Ϣ
	Cmd::stAttackMagicUserCmd revCmd;
	/// �����ߵ�ָ��
	SceneEntryPk *attacker;
	/**
	* \brief  ���캯������ʼ����������
	*/
	SkillStatusCarrier()
	{
		status = NULL;
		skillbase = NULL;
		attacker = NULL;
	}
};

/**
* \brief  ����״̬Ԫ��
*/
struct SkillStatusElement
{
	/// ״̬�� id
	DWORD  id;

	/// ״̬��������
	DWORD percent;

	/// ״̬��Ӱ����ֵ(sky �ٻ�:����ID�����Ѿ�����65535)
	DWORD value;

	/// ״̬�ĳ���ʱ��
	QWORD qwTime;

	/// ״ִ̬�еĲ����־
	DWORD state;


	///�����ߵ���ʱID;
	DWORD dwTempID;

	///�����ߵ�ID
	DWORD dwAttackerID;

	///����ID
	DWORD dwSkillID;

	///ִ��ʱ��
	DWORD dwTime;

	///ִ�в���
	BYTE  byStep;

	///�ƶ�����
	BYTE  byGoodnessType;

	///���ܵĻ������
	BYTE  byMutexType;

	///�Ƿ�ˢ����������1Ϊˢ��0Ϊ��
	BYTE  refresh;

	///�����ߵ�����
	zSceneEntry::SceneEntryType attacktype;

	/**
	* \brief  ����״̬Ԫ�ع��캯����ʼ����������
	*/
	SkillStatusElement()
	{
		id = 0;          //״̬��id;
		percent = 0;
		value = 0;
		qwTime = 0;
		state = 0;
		dwTempID = 0;
		dwSkillID = 0;
		dwTime = 0;
		byStep = 0;
		refresh = 0;
	}
};

/**
* \brief  ����״̬������
*/
class SkillStatusManager
{
private:
	/// ��������״̬�б�
	std::map<DWORD, SkillStatusElement> _activeElement;

	/// ��ʱ��������״̬�б�
	std::map<DWORD, SkillStatusElement> _recoveryElement;

	/// ���ñ�������״̬�б�
	std::map<DWORD, SkillStatusElement> _passivenessElement;

	/// ���Ͷ���
	typedef std::map<DWORD, SkillStatusElement>::value_type VALUE_TYPE;

	/**
	* \brief  ����״̬�����б�
	*/
	struct {
		BYTE(*func)(SceneEntryPk *, SkillStatusElement &);
	}funlist[SKILLSTATENUMBER + 1];

	/// ����״̬����������
	SceneEntryPk *entry;
	bool bclearActiveSkillStatus;

public:
	SkillStatusManager();
	~SkillStatusManager();
	void initMe(SceneEntryPk *pEntry);
	void loadSkillStatus(char *buf, DWORD length);
	void getSelectStates(Cmd::stSelectReturnStatesPropertyUserCmd *buf, unsigned long maxSize);
	void sendSelectStates(SceneEntryPk *pThis, DWORD state, WORD value, WORD time);
	void saveSkillStatus(char *buf, DWORD &size);
	bool putOperationToMe(const SkillStatusCarrier &carrier, const bool good = false, SWORD rangDamageBonus = 0);
	void putPassivenessOperationToMe(const DWORD skillid, const SkillStatus *pSkillStatus);
	void processPassiveness();
	inline BYTE runStatusElement(SkillStatusElement &element);
	void timer();
	void clearActiveSkillStatus();
	void clearActiveSkillStatusOnlyUseToStatus48();
	void clearBadActiveSkillStatus();
	void addBadSkillStatusPersistTime(const DWORD &value);
	void addBadSkillStatusPersistTimePercent(const DWORD &value);
	void clearMapElement(const BYTE &byMutexType, std::map<DWORD, SkillStatusElement> &myMap, DWORD dwID, bool notify = true);
	WORD getSaveStatusSize();
	void clearRecoveryElement(DWORD value);
	void clearActiveElement(DWORD value);
	void processDeath();
	void clearSkill(DWORD dwSkillID);

	//[test]-----------------------------------------------------------------
	void showValue();
	void showValueToLog();
	void showActive();
	void showRecovery();
	void showPassiveness();
	//-----------------------------------------------------------------------

	//sky ���� begin
	void SetStatuToRecovery(DWORD id, DWORD time, DWORD percent, DWORD value = 0, DWORD state = 0);
	//sky end
};

//sky ����������������ö��
enum
{
	SPEC_NULL = 0,	//sky ��	
	SPEC_MAGIC = 1,	//sky ħ����
	SPEC_PHYSICS = 2,	//sky ������
	SPEC_IMMUNE = 4,	//sky ������
	SPEC_REBOUND = 8,	//sky �ɱ�����
	SPEC_TREATMENT = 16,	//sky ����
	SPEC_BUFF = 32,	//sky ����BUFF
	SPEC_DEBUFF = 64,	//sky ����BUFF
	SPEC_DRUG = 128,	//sky ��
	SPEC_OTHER = 256,	//sky ����
};

/**
* \brief ������,���弼�ܵĻ������Լ�����ִ�з���
*/
struct zSkill : zEntry
{
	static const DWORD maxUniqueID = 100000;
public:
	t_Skill data;
	const zSkillB *base;
	const zSkillB *actionbase;

	static zSkill *create(SceneEntryPk *pEntry, DWORD id, DWORD level);
	static zSkill *createTempSkill(SceneEntryPk *pEntry, DWORD id, DWORD level);
	static zSkill *load(SceneEntryPk *pEntry, const SaveSkill *s);
	bool canUpgrade(SceneEntryPk *pEntry);
	bool setupSkillBase(SceneEntryPk *pEntry);
	bool getSaveData(SaveSkill *save);
	bool canUse();
	bool checkSkillBook(bool nextbase = false);
	bool checkSkillStudy(bool nextbase = false);
	void resetUseTime();
	void clearUseTime();
	void refresh(bool ignoredirty = false);

	//sky ���������������Լ�⺯��
	bool IsMagicSkill();	//sky ��⼼���Ƿ���ħ��ϵ����
	bool IsPhysicsSkill();	//sky ��⼼���Ƿ�������ϵ����
	bool IsImmuneSkill();	//sky ��⼼���Ƿ��ܱ�����
	bool IsReboundSkill();	//sky ��⼼���Ƿ��ܱ�����
	bool IsTreatmentSkill();//sky ��⼼���Ƿ�������ϵ
	bool IsBuffSkill();		//sky ��⼼���Ƿ�������BUFFϵ
	bool IsDeBuffSkill();	//sky ��⼼���Ƿ��Ǽ���BUFFϵ
	bool IsDrugSkill();		//sky ��⼼���Ƿ��Ƕ�ϵ
	bool IsOtherSkill();	//sky ��⼼���Ƿ�������ϵ

	~zSkill();
	QWORD lastUseTime;
private:
	bool dirty;
	bool istemp;
	bool needSave;
	bool inserted;
	SceneEntryPk *_entry;
	const Cmd::stAttackMagicUserCmd *curRevCmd;
	DWORD curRevCmdLen;
	zSkill();

	//static DWORD uniqueID;

	// �����ӵļ��ܷ���
public:
	bool action(const Cmd::stAttackMagicUserCmd *rev, const DWORD cmdLen);
	inline void doOperation(const SkillStatus *pSkillStatus);
	inline void doPassivenessSkill();
	inline bool showMagicToAll();
	inline bool findAttackTarget(const SkillStatus *pSkillStatus, zPos &pd, DWORD &count, SWORD rangDamageBonus = 0);
	inline const zSkillB *getNewBase();
};

/**
* \brief  �ص�����
*/
class UserSkillExec
{
public:
	virtual bool exec(zSkill *s) = 0;
};


/**
* \brief  ���ܹ���������
*/
class UserSkillM : private zEntryMgr < zEntryID, zEntryTempID >
{
public:
	UserSkillM(SceneUser* u);
	~UserSkillM();
	bool getUniqeID(QWORD &tempid);
	void putUniqeID(const QWORD &tempid);
	zSkill *getSkillByTempID(DWORD id);
	void removeSkillByTempID(DWORD id);
	void removeSkill(zSkill *s);
	bool addSkill(zSkill *s);
	zSkill *findSkill(DWORD skillid);
	void execEvery(UserSkillExec &exec);
	void resetAllUseTime();
	void clearAllUseTime(DWORD skillID = 0);
	void clear();
	DWORD getPointInTree(DWORD mySubkind);
	void refresh();
	int size() const;
	void clearskill(DWORD skillid);
public:
	SceneUser* pOwner;

};


//����Ӱ���״̬����
struct SkillState
{
	SkillState();
	void init();
	union
	{
		struct
		{
			SWORD dvalue;    //�˺�ֵ���ӹ̶���ֵ1
			SWORD dvaluep;    //�˺�ֵ����x%2
			SWORD pdefence;    //���������ֵ��� 57��86
			SWORD pdefencep;  //�����������ٷֱ�
			SWORD updam;    //���������ӹ̶���ֵ
			SWORD updamp;    //���������Ӱٷֱ�
			SWORD umdam;    //�����������ӹ̶���ֵ
			SWORD umdamp;    //�����������Ӱٷֱ�
			SWORD dpdam;    //���������ٹ̶���ֵ
			SWORD dpdamp;    //���������ٰٷֱ�
			SWORD dmdam;    //�����������ٹ̶���ֵ
			SWORD dmdamp;    //�����������ٰٷֱ�
			SWORD updef;    //����������ӹ̶���ֵ
			SWORD updefp;    //����������Ӱٷֱ�
			SWORD umdef;    //�����������ӹ̶���ֵ
			SWORD umdefp;    //�����������Ӱٷֱ�
			SWORD dpdef;    //����������ٹ̶���ֵ
			SWORD dpdefp;    //����������ٰٷֱ�
			SWORD dmdef;    //�����������ٹ̶���ֵ
			SWORD dmdefp;    //�����������ٰٷֱ�
			SWORD topet;    //��Ϊ���С����79
			SWORD appenddam;  //���������˺�83
			SWORD movespeed;  //�ƶ��ٶȱ���ٷֱ� 16��56
			SWORD mgspeed;    //���ټ���ʩ�ż��17
			SWORD coldp;    //�����������״̬����18
			SWORD poisonp;    //���������ж�״̬����19
			SWORD petrifyp;    //��������ʯ��״̬����20
			SWORD blindp;    //��������ʧ��״̬����21
			SWORD chaosp;    //�����������״̬����22
			SWORD atrating;    //����������33,64
			SWORD reduce_atrating;  // �����ʼ��� ZJW����
			SWORD hpspeedup;  //����ֵ�ָ��ٶ�����34
			SWORD mpspeedup;  //����ֵ�ָ��ٶ�����35
			SWORD spspeedup;  //����ֵ�ָ��ٶ�����36
			SWORD akdodge;    //����������37
			SWORD reduce_akdodge;  // �������½�
			SWORD mdefence;    //�����������59��             // 40
			SWORD mdefencep;  //������������ٷֱ�x%
			SWORD uattackspeed;  //�����ٶ���߰׷ֱ�
			SWORD dattackspeed;  //�����ٶȽ��Ͱ׷ֱ�
			SWORD sevendownp;  //���������ߴ�״̬����82
			SWORD tsfdamp;    //�˺�ת�ưٷֱ�
			SWORD tsfdam;    //�˺�ת����ֵ
			SWORD passdam;    //�����������˺�117
			SWORD maxhp;       //����ֵ���ֵ���
			SWORD maxmp;       //����ֵ���ֵ���
			SWORD maxsp;       //����ֵ���ֵ���
			SWORD pupdam;    //���������ӹ̶���ֵ��������
			SWORD pumdam;    //�����������ӹ̶���ֵ��������
			SWORD pupdef;    //����������ӹ̶���ֵ��������
			SWORD pumdef;    //�����������ӹ̶���ֵ��������
			SWORD supdam;    //�������������������̶�ֵ(��Ч)
			SWORD spupdam;    //�������������������̶�ֵ(����)
			SWORD spupdamp;    //�������������������ٷֱ�(����)
			SWORD rpupdam;    //�������������������̶�ֵ(����)
			SWORD lupdam;    //��Ч����������ǿ�̶�ֵ
			SWORD satrating;  //����������������
			SWORD patrating;   // ���������ʣ�������
			SWORD pattackspeed;  //���ӹ����ٶȣ�������
			SWORD upattribute;  //���Ե�����
			SWORD tuling;      //������ǿ
			SWORD kulou;    //���ù�����ǿ
			SWORD tianbing;    //�����ǿ
			SWORD weaponupdamp; //�����������������ٷֱ�
			SWORD weaponumdamp; //�������������������ٷֱ�
			SWORD uppetdamage; //�����ٻ��޵Ĺ�����
			SWORD uppetdefence; //�����ٻ��޵ķ�����
			SWORD pmaxhp;    //���������������ֵ
			SWORD bang;      //��������ʩ�ų��ػ��ļ���
			SWORD theurgy_updam; //����������������
			SWORD theurgy_updamp; //�����������������ٷֱ�
			SWORD theurgy_updef; //�����������������
			SWORD theurgy_umdefp; //�������ӷ����������ٷֱ�
			SWORD theurgy_umdef; //�������ӷ���������
			SWORD theurgy_umdam; //�������ӷ���������
			SWORD theurgy_umdamp; //�������ӷ����������ٷֱ�
			SWORD theurgy_updefp;//������������������ٷֱ�
			SWORD theurgy_dpdef; //�����������������
			SWORD theurgy_dmdef; //�����������������
			SWORD theurgy_dpdam;    //���������ٹ̶���ֵ
			SWORD theurgy_dmdam;    //�����������ٹ̶���ֵ
			SWORD hpupbylevel; //��������ȼ��������Ѫ��                    //80
			SWORD reflect_ardor; // ��������״̬�������Լ��ĵ���
			SWORD reflect_poison; //�����ж�״̬�������Լ��ĵ���
			SWORD reflect_lull;  // �������״̬�������Լ��ĵ���
			SWORD reflect_frost; // ��������״̬�������Լ��ĵ���
			WORD introject_maxmdam; // �ٻ���������ħ������
			WORD introject_maxpdam; // �ٻ���������������
			WORD introject_mdam; // �ٻ���������ħ������
			WORD introject_pdam; // �ٻ���������������
			WORD introject_mdef; // �ٻ���������ħ������
			WORD introject_pdef; // �ٻ����������������
			WORD introject_maxhp; // �ٻ�����������������
			SWORD summonrelive; // �ٻ�������
			SWORD pdamtodef;  // �﹥ת���
			SWORD mdamtodef;  // ħ��תħ��
			SWORD pdeftodam;  // ���ת�﹥
			SWORD mdeftodam;  // ħ��תħ��
			SWORD sept_updamp;  // �����������ٷֱ�
			SWORD sept_umdamp;  // ����ħ�������ٷֱ�
			SWORD sept_updefp;  // ������������ٷֱ�
			SWORD sept_umdefp;  // �������������ٷֱ�
			SWORD sept_maxhp;  // �����������ֵ�ٷֱ�
			SWORD sept_maxmp;  // �����������ֵ�ٷֱ�
			SWORD blazeappend; // ����ϵ�����˺���������ǧ��֮��
			SWORD pblazeappend; // ����ϵ�����˺���������ǧ��֮��
			SWORD levinappend; // �׵�ϵ�����˺���������ǧ��֮��
			SWORD plevinappend; // �׵�ϵ�����˺���������ǧ��֮��(����)
			SWORD trapappend;  // ����ϵ�����˺���������ǧ��֮��
			SWORD iceappend;  // ����ϵ�����˺���������ǧ��֮��
			SWORD udef;      // ���������̶�ֵ������ͷ���������
			SWORD magicattack;  // �����ķ���������ʱ�򸽴������˺�
			SWORD array_udamp; // �󷨵�˫����������
			SWORD array_ddefp; // �󷨵�˫�����ʽ���
			SWORD array_dmvspeed; // �󷨵��ƶ��ٶȽ���
			SWORD upcon; //��������
			SWORD upint; //��������
			SWORD updex; //��������
			SWORD sword_udam; //���������������˺�����   // 110
			SWORD attackaddhpnum; // ���������Լ�����ֵ��Ŀ
			SWORD dodge;         // ��һ���������ܵ��˹���
			SWORD reflect_icelull; // ����һ�����״̬ ���׶���
			SWORD pumdamp;    //�������������������ٷֱ�
			SWORD addmenp;   // ���Ӿ���ٷֱ�
			SWORD ice_umdefp; //����������ħ�������ٷֱ�
			SWORD protectdam; //����״̬֮�˺�
			SWORD protectUpAtt; //����״̬֮��������
			SWORD unitarybattle; //һԪ��Ͷ��С���ܵ��ӳ����ڹ����ĵ������ϣ���ΪͶ�͵ļ���ID
			SWORD teamappend; //��ӹ����ӳɣ��������ŵ�����Ӷӳ���ID
			SWORD nsc_updamp; //���̵ִ�ר�ü�������״̬��
			SWORD tgyt_updefp; //��������ר�ü�������״̬
			SWORD tgzh_updef; //����֮��ר�ü�������״̬
			SWORD lm_updamp;   // ³ç�������������ٷֱ�
			SWORD upallattrib; // ��������������ֵ
			SWORD dnallattrib; // �������Խ�����ֵ
			SWORD upstr;      // �����������԰ٷֱ�
			SWORD dpallattrib; // ���������½��ٷֱ�
			SWORD upattribstr; // �����������԰ٷֱ�
			SWORD upattribcon; // �����������԰ٷֱ�
			SWORD upattribmen; // �����������԰ٷֱ�
			SWORD upattribdex; // �����������԰ٷֱ�
			SWORD upattribint; // �����������԰ٷֱ�
			SWORD relive;    // ����
			SWORD nowrelive; // ��������ʱ�ظ��ٷֱ�
			SWORD brappenddam; //����ӡ�����ṩ�Ķ����˺���
			SWORD dpintmen;   // �������񽵵Ͱٷֱ�
			SWORD dpstrdex;   // �������ݽ��Ͱٷֱ�
			SWORD enervation; // ˥��
			SWORD erupt;      // �Ƹ�����״̬ ħ�﹥����300%����ʱ�������ø�������״̬

							  //sky ��������Ч��
			SWORD AttAddDam;		//sky �����˺��ٷֱ�
			SWORD reflect;		//sky �����˺��̶�ֵ
			SWORD reflectp;		//sky �����������˺��ٷֱ�
			SWORD reflect2;		//sky ����ħ�������˺��ٷֱ�
			SWORD MagicReflex;	//sky ħ��ϵ���ܷ���(ֱ�ӰѼ��ܷ����ȥ)
			SWORD PhyReflex;		//sky ������ٷֱ�
			SWORD DaggerAddDam;	//sky ����ذ���˺��ٷֱ�
			SWORD ThroAddDam;		//sky ����Ͷ�������˺��ٷֱ�
			SWORD HandsAddDam;	//sky ����˫�������˺��ٷֱ�
			SWORD HandAddDam;		//sky ���ӵ��������˺��ٷֱ�
			SWORD FlameAddDam;	//sky ���ӻ���ħ���˺��ٷֱ�
			SWORD IceAddDam;		//sky ���ӱ�˪ħ���˺��ٷֱ�
			SWORD SacredAddDam;	//sky ������ʥħ���˺��ٷֱ�
			SWORD DarkAddDam;		//sky ���Ӻڰ�ħ���˺��ٷֱ�

			SWORD DaggerAddDamA;	//sky ����ذ���˺��̶�ֵ
			SWORD ThroAddDamA;	//sky ����Ͷ�������˺��̶�ֵ
			SWORD HandsAddDamA;	//sky ����˫�������˺��̶�ֵ
			SWORD HandAddDamA;	//sky ���ӵ��������˺��̶�ֵ
			SWORD FlameAddDamA;	//sky ���ӻ���ħ���˺��̶�ֵ
			SWORD IceAddDamA;		//sky ���ӱ�˪ħ���˺��̶�ֵ
			SWORD SacredAddDamA;	//sky ������ʥħ���˺��̶�ֵ
			SWORD DarkAddDamA;	//sky ���Ӻڰ�ħ���˺��̶�ֵ
		};
		SWORD swdValue[171];
	};
};

/**
* \brief Ƶ������ 
*
*/
enum ChannelType
{
	CHANNEL_TYPE_WORLD = 1,
};


/**
* \brief ����Ƶ��
*
*/
class Channel :public zEntry
{
private:
	std::vector< zEntryC > userlist;
	zEntry creater;
public:
	Channel(SceneUser *pUser);
	Channel(DWORD chID,const std::string& _name);
	~Channel();

	static bool sendNine(SceneUser *pUser, const NetMsgSS *cmd, DWORD len);
	static bool sendNine(const SceneNpc *pNpc, const char *pattern, ...);
	static bool sendPrivate(SceneUser *pUser, const NetMsgSS *cmd, DWORD len);
	static bool sendTeam(DWORD teamid, const NetMsgSS *cmd, DWORD len);
	static bool sendCountry(SceneUser *pUser, const NetMsgSS *cmd, DWORD len);
	
	static bool sendCmdToMap(DWORD mapID, const NetMsgSS *cmd, int len);
	static bool sendCmdToMap(Scene* scene, const NetMsgSS *cmd, int len);
	static bool sendSys(SceneUser *pUser, int type, const char *pattern, ...);
	static bool sendSys(DWORD dwUserTempID, int type, const char *pattern, ...);
	static bool sendCountry(SceneUser *pUser, const char *pattern, ...);
	static bool sendCountryInfo(DWORD countryID, DWORD infoType, const char *pattern, ...);
	static bool sendAllInfo(DWORD infoType, const char *pattern, ...);
	
	bool sendCmdToAll(const NetMsgSS *cmd,int len);

	bool remove(const char *name);
	bool add(SceneUser *pUser);
	WORD has(const char *name);
	
};

/**
* \brief Ƶ��������
*
*/
class ChannelM : public zEntryMgr< zEntryID, zEntryTempID ,zEntryName >
{
private:
	zUniqueDWORDID *channelUniqeID;
	zMutex mlock;
	zObjPool<Channel> objpool;

	bool getUniqeID(QWORD &tempid);
	void putUniqeID(const QWORD &tempid);
	
public:
	ChannelM();
	~ChannelM();
	bool add(Channel *channel);
	void remove(DWORD dwChannelID);
	Channel* get(DWORD dwChannelID);
	void removeUser(const char *name);
	Channel* CreateObj(SceneUser *pUser);
	Channel* CreateObj(DWORD chID, const std::string& _name);
	void DestroyObj(Channel* obj);

};

/// ����GM��id,ֻ��1������GM
#define SUPER_GM_ID 1

struct Gm
{
	enum
	{
		none_mode = 0x00,
		normal_mode = 0x01,
		gm_mode = 0x02,
		captain_mode = 0x04,
		super_mode = 0x08,
		debug_mode = 0x10,
		all_mode = 0x1f,/// all_mode
						//admin_mode =   0x10,
						//magic_mode =   0x20
	};

	const char *cmd;
	bool(*parse)(SceneUser *pUser, const char *para);
	BYTE priv;
	const char *desc;

	static void sendLog(SceneUser *pUser, const char *cmd, const char * content);

	static void exec(SceneUser *pUser, char *cmd);
	static bool fetch(SceneUser *pUser, const char *para);
	static bool getgive(SceneUser *pUser, const char *para);
	static bool summon(SceneUser *pUser, const char *para);
	static bool help(SceneUser *pUser, const char *para);
	static bool levelup(SceneUser *pUser, const char *para);
	static bool goTo(SceneUser *pUser, const char *para);
	static bool goTo_Gm(SceneUser *pUser, const char *para);
	static bool gomap(SceneUser *pUser, const char *para);
	static bool gomap_Gm(SceneUser *pUser, const char *para);

};


#endif
