#ifndef _PACKAGE_H_
#define _PACKAGE_H_

#include "srvEngine.h"
#include "ScenesServer.h"

//SKY �����Ŀ�͸�
#define PACK_WIDTH	7
#define PACK_HEIGHT	35

//SKY  �ֿ�Ŀ�͸�
#define SAVEBOX_WIDTH 7
#define SAVEBOX_HEIGHT 50

#define DECLARE(prop,type) type get_##prop() const {return prop;}
#define RESET(prop) prop = 0;
class Equips
{
public:
	Equips()
	{
		reset();
	}

	void reset()
	{
		RESET(maxhp)          // �������ֵ
			RESET(maxmp)          // �����ֵ
			RESET(maxsp)          // �������ֵ

			RESET(pdamage)          // ��С������
			RESET(maxpdamage)        // ��󹥻���
			RESET(mdamage)          // ��С����������
			RESET(maxmdamage)        // �����������
			RESET(appendminpet)           // ������ǿ��Сֵ
			RESET(appendmaxpet)        // ������ǿ���ֵ

			RESET(pdefence)        // ���
			RESET(mdefence)        // ħ��
			RESET(damagebonus)      // �˺��ӳ�
			RESET(damage)        // �����˺�ֵx��

			RESET(akspeed)        // �����ٶ�
			RESET(mvspeed)        // �ƶ��ٶ�
			RESET(atrating)        // ������
			RESET(akdodge)        // �����

			RESET(str)            // ����
			RESET(inte)            // ����
			RESET(dex)            // ����
			RESET(spi)            // ����
			RESET(con)            // ����

			RESET(hpr)          // ����ֵ�ָ�
			RESET(mpr)            // ����ֵ�ָ�
			RESET(spr)            // ����ֵ�ָ�

			RESET(holy)            //��ʥһ��
			RESET(bang)            //�ػ���
			RESET(pdam)           // ������������
			RESET(pdef)            // �������������
			RESET(mdam)            // ����ħ��������
			RESET(mdef)            // ����ħ��������

			RESET(poisondef)         //��������
			RESET(lulldef)         //���������
			RESET(reeldef)         //��ѣ������
			RESET(evildef)         //����ħ����
			RESET(bitedef)         //����������
			RESET(chaosdef)         //����������
			RESET(colddef)         //����������
			RESET(petrifydef)       //��ʯ������
			RESET(blinddef)         //��ʧ������
			RESET(stabledef)         //����������
			RESET(slowdef)         //����������
			RESET(luredef)         //���ջ�����

			RESET(poison)         //�ж�����
			RESET(lull)           //�������
			RESET(reel)           //ѣ������
			RESET(evil)           //��ħ����
			RESET(bite)          //��������
			RESET(chaos)           //��������
			RESET(cold)           //��������
			RESET(petrify)         //ʯ������
			RESET(blind)           //ʧ������
			RESET(stable)         //��������
			RESET(slow)           //��������
			RESET(lure)           //�ջ�����
			RESET(hpleech.odds)
			RESET(hpleech.effect)
			RESET(mpleech.odds)       //x%��������ֵy
			RESET(mpleech.effect)     //x%���շ���ֵy

			RESET(hptomp)          //ת������ֵΪ����ֵx��
			RESET(dhpp)           //�����˺�����x%  
			RESET(dmpp)          //�����˺�ֵ����x%    

			RESET(incgold)        //���ӽ�Ǯ����x%
			RESET(doublexp)        //x%˫������    
			RESET(mf)             //���ӵ�����x%

								  //������װ�������
			RESET(dpdam)      //�����˺�����%x
			RESET(dmdam)      //�����˺�����%x
			RESET(bdam)        //�����˺�x%
			RESET(rdam)        //�˺�����%x
			RESET(ignoredef)    //%x����Ŀ�����

								//    RESET(aftype)
			aftype = FIVE_NONE;
		RESET(afpoint)
			//    RESET(dftype)
			dftype = FIVE_NONE;
		RESET(dfpoint)
			RESET(maxhprate)
			RESET(maxmprate)

			RESET(Freedom.str_Attribute)
			RESET(Freedom.inte_Attribute)
			RESET(Freedom.dex_Attribute)
			RESET(Freedom.spi_Attribute)
			RESET(Freedom.con_Attribute)

			skill.clear();
		skills.clear();

		gempop.clear();
	}

	DECLARE(maxhp, WORD)        // �������ֵ
		DECLARE(maxmp, WORD)        // �����ֵ
		DECLARE(maxsp, WORD)        // �������ֵ

		DECLARE(pdamage, WORD)      // ��С������
		DECLARE(maxpdamage, WORD)    // ��󹥻���
		DECLARE(mdamage, WORD)      // ��С����������
		DECLARE(maxmdamage, WORD)    // �����������
		DECLARE(appendminpet, WORD)  // ��С������ǿ
		DECLARE(appendmaxpet, WORD)  // ��������ǿ

		DECLARE(pdefence, WORD)      // ���
		DECLARE(mdefence, WORD)      // ħ��
		DECLARE(damagebonus, BYTE)    // �˺��ӳ�
		DECLARE(damage, BYTE)        // �����˺�ֵx��

		DECLARE(akspeed, WORD)      // �����ٶ�
		DECLARE(mvspeed, WORD)      // �ƶ��ٶ�
		DECLARE(atrating, WORD)      // ������
		DECLARE(akdodge, WORD)      // �����

		DECLARE(str, WORD)          // ����
		DECLARE(inte, WORD)         // ����
		DECLARE(dex, WORD)         // ����
		DECLARE(spi, WORD)          // ����
		DECLARE(con, WORD)          // ����

		DECLARE(hpr, WORD)          // ����ֵ�ָ�
		DECLARE(mpr, WORD)          // ����ֵ�ָ�
		DECLARE(spr, WORD)          // ����ֵ�ָ�

		DECLARE(holy, WORD)        //��ʥһ��
		DECLARE(bang, WORD)        //�ػ���
		DECLARE(pdam, WORD)          // ������������
		DECLARE(pdef, WORD)          // �������������
		DECLARE(mdam, WORD)          // ����ħ��������
		DECLARE(mdef, WORD)          // ����ħ��������

		DECLARE(poisondef, WORD)       //��������
		DECLARE(lulldef, WORD)       //���������
		DECLARE(reeldef, WORD)       //��ѣ������
		DECLARE(evildef, WORD)       //����ħ����
		DECLARE(bitedef, WORD)       //����������
		DECLARE(chaosdef, WORD)       //����������
		DECLARE(colddef, WORD)       //����������
		DECLARE(petrifydef, WORD)     //��ʯ������
		DECLARE(blinddef, WORD)       //��ʧ������
		DECLARE(stabledef, WORD)       //����������
		DECLARE(slowdef, WORD)       //����������
		DECLARE(luredef, WORD)       //���ջ�����

		DECLARE(poison, WORD)       //�ж�����
		DECLARE(lull, WORD)         //�������
		DECLARE(reel, WORD)         //ѣ������
		DECLARE(evil, WORD)         //��ħ����
		DECLARE(bite, WORD)         //��������
		DECLARE(chaos, WORD)         //��������
		DECLARE(cold, WORD)         //��������
		DECLARE(petrify, WORD)       //ʯ������
		DECLARE(blind, WORD)         //ʧ������
		DECLARE(stable, WORD)       //��������
		DECLARE(slow, WORD)         //��������
		DECLARE(lure, WORD)         //�ջ�����

		DECLARE(hptomp, BYTE)       //ת������ֵΪ����ֵx��
		DECLARE(dhpp, BYTE)         //�����˺�����x%  
		DECLARE(dmpp, BYTE)         //�����˺�ֵ����x%    

		DECLARE(incgold, BYTE)       //���ӽ�Ǯ����x%
		DECLARE(doublexp, BYTE)       //x%˫������    
		DECLARE(mf, BYTE)         //���ӵ�����x%

								  //������װ�������
		DECLARE(dpdam, BYTE)      //�����˺�����%x
		DECLARE(dmdam, BYTE)      //�����˺�����%x
		DECLARE(bdam, BYTE)        //�����˺�x%
		DECLARE(rdam, BYTE)        //�˺�����%x
		DECLARE(ignoredef, BYTE)    //%x����Ŀ�����
		DECLARE(maxhprate, BYTE)    //���ٷֱ��������hp
		DECLARE(maxmprate, BYTE)    //���ٷֱ��������mp

									//sky �������ɼӵ������ 
		WORD get_Freedom_str()		const { return Freedom.str_Attribute; }
	WORD get_Freedom_inte()		const { return Freedom.inte_Attribute; }
	WORD get_Freedom_dex()		const { return Freedom.dex_Attribute; }
	WORD get_Freedom_spi()		const { return Freedom.spi_Attribute; }
	WORD get_Freedom_con()		const { return Freedom.con_Attribute; }

	BYTE get_hpleech_odds()    const { return hpleech.odds; }
	WORD get_hpleech_effect()  const { return hpleech.effect; }	 //x%��������ֵy
	BYTE get_mpleech_odds()    const { return mpleech.odds; }
	WORD get_mpleech_effect()  const { return mpleech.effect; }     //x%���շ���ֵy

																	/**
																	* \brief sky ��ȡ��ʯ����
																	* \return ������������
																	*/
	WORD get_gem_str() const   //��ȡ��ʯ������
	{
		WORD str;
		const_iterator1 it;

		for (it = gempop.begin(); it != gempop.end(); it++)
		{
			if (it->GemID != INVALID_HOLE)
				str += it->gem_str;
		}

		return str;
	}

	WORD get_gem_inte() const   //��ȡ��ʯ������
	{
		WORD inte;
		const_iterator1 it;

		for (it = gempop.begin(); it != gempop.end(); it++)
		{
			if (it->GemID != INVALID_HOLE)
				inte += it->gem_inte;
		}

		return inte;
	}

	WORD get_gem_dex() const   //��ȡ��ʯ������
	{
		WORD dex;
		const_iterator1 it;

		for (it = gempop.begin(); it != gempop.end(); it++)
		{
			if (it->GemID != INVALID_HOLE)
				dex += it->gem_dex;
		}

		return dex;
	}

	WORD get_gem_spi() const   //��ȡ��ʯ�ľ���
	{
		WORD spi;
		const_iterator1 it;

		for (it = gempop.begin(); it != gempop.end(); it++)
		{
			if (it->GemID != INVALID_HOLE)
				spi += it->gem_spi;
		}

		return spi;
	}

	WORD get_gem_con() const   //��ȡ��ʯ������
	{
		WORD con;
		const_iterator1 it;

		for (it = gempop.begin(); it != gempop.end(); it++)
		{
			if (it->GemID != INVALID_HOLE)
				con += it->gem_con;
		}

		return con;
	}

	WORD	gem_atk;	//��������
	WORD	gem_mkt;

	WORD get_gem_def() const   //��ȡ��ʯ���������
	{
		WORD def;
		const_iterator1 it;

		for (it = gempop.begin(); it != gempop.end(); it++)
		{
			if (it->GemID != INVALID_HOLE)
				def += it->gem_def;
		}

		return def;
	}

	WORD get_gem_mdef() const   //��ȡ��ʯ��ħ������
	{
		WORD mdef;
		const_iterator1 it;

		for (it = gempop.begin(); it != gempop.end(); it++)
		{
			if (it->GemID != INVALID_HOLE)
				mdef += it->gem_mdef;
		}

		return mdef;
	}

	WORD get_gem_dhpp() const   //��ȡ��ʯ����������
	{
		WORD dhpp;
		const_iterator1 it;

		for (it = gempop.begin(); it != gempop.end(); it++)
		{
			if (it->GemID != INVALID_HOLE)
				dhpp += it->gem_dhpp;
		}

		return dhpp;
	}

	WORD get_gem_dmpp() const   //��ȡ��ʯ��ħ������
	{
		WORD dmpp;
		const_iterator1 it;

		for (it = gempop.begin(); it != gempop.end(); it++)
		{
			if (it->GemID != INVALID_HOLE)
				dmpp += it->gem_dmpp;
		}

		return dmpp;
	}

	WORD get_gem_atk() const   //��ȡ��ʯ����������
	{
		WORD atk;
		const_iterator1 it;

		for (it = gempop.begin(); it != gempop.end(); it++)
		{
			if (it->GemID != INVALID_HOLE)
				atk += it->gem_atk;
		}

		return atk;
	}

	WORD get_gem_mtk() const   //��ȡ��ʯ��ħ��������
	{
		WORD mtk;
		const_iterator1 it;

		for (it = gempop.begin(); it != gempop.end(); it++)
		{
			if (it->GemID != INVALID_HOLE)
				mtk += it->gem_mkt;
		}

		return mtk;
	}

	/**
	* \brief ��ȡ��������
	* \return ������������
	*/
	DWORD getAttFive() const { return aftype; }

	/**
	* \brief ��ȡ�������е���
	* \return ���е���
	*/
	DWORD getAttFivePoint() const { return afpoint; }

	/**
	* \brief ��ȡ��������
	* \return ������������
	*/
	DWORD getDefFive() const { return dftype; }

	/**
	* \brief ��ȡ�������е���
	* \return ���е���
	*/
	DWORD getDefFivePoint() const { return dfpoint; }

	/**
	* \brief ��ȡװ���Ե������ܵļӳ�
	*
	* \param id: ����id
	* \return �ӳɵȼ�
	*/
	DWORD getMaxSkill(WORD id) const
	{
		const_iterator it = skill.find(id);
		if (it != skill.end()) {
			return it->second;
		}

		return 0;
	}

	/**
	* \brief ��ȡװ����ĳϵ���ܵļӳ�
	*
	* \param id: ����ϵ��
	* \return �ӳɵȼ�
	*/
	DWORD getMaxSkills(WORD id) const
	{
		const_iterator it = skills.find(id);
		if (it != skills.end()) {
			return it->second;
		}

		return 0;
	}

private:
	friend class EquipPack;
	DWORD maxhp;          // �������ֵ
	DWORD maxmp;          // �����ֵ
	DWORD maxsp;          // �������ֵ

	DWORD pdamage;        // ��С������
	DWORD maxpdamage;      // ��󹥻���
	DWORD mdamage;        // ��С����������
	DWORD maxmdamage;      // �����������
	WORD appendminpet;         // �����ٻ���������ǿ��Сֵ
	WORD appendmaxpet;         // �����ٻ���������ǿ���ֵ

	WORD pdefence;        // ���
	WORD mdefence;        // ħ��
	BYTE damagebonus;      // �˺��ӳ�
	BYTE damage;        // �����˺�ֵx��

	WORD akspeed;        // �����ٶ�
	WORD mvspeed;        // �ƶ��ٶ�
	WORD atrating;        // ������
	WORD akdodge;        // �����

	WORD str;  // ����
	WORD inte;  // ����
	WORD dex;  // ����
	WORD spi;  // ����
	WORD con;  // ����


			   //      WORD fivetype;  // ��������
			   //      WORD fivepoint; // ��������

	WORD hpr;  // ����ֵ�ָ�
	WORD mpr;  // ����ֵ�ָ�
	WORD spr;  // ����ֵ�ָ�

	WORD holy;  //��ʥһ��  
	WORD bang;  //�ػ���
	WORD pdam;  // ������������
	WORD pdef;  // �������������
	WORD mdam;  // ����ħ��������
	WORD mdef;  // ����ħ��������

	WORD poisondef; //��������
	WORD lulldef; //���������
	WORD reeldef; //��ѣ������
	WORD evildef; //����ħ����
	WORD bitedef; //����������
	WORD chaosdef; //����������
	WORD colddef; //����������
	WORD petrifydef; //��ʯ������
	WORD blinddef; //��ʧ������
	WORD stabledef; //����������
	WORD slowdef; //����������
	WORD luredef; //���ջ�����

	WORD poison; //�ж�����
	WORD lull; //�������
	WORD reel; //ѣ������
	WORD evil; //��ħ����
	WORD bite; //��������
	WORD chaos; //��������
	WORD cold; //��������
	WORD petrify; //ʯ������
	WORD blind; //ʧ������
	WORD stable; //��������
	WORD slow; //��������
	WORD lure; //�ջ�����

	struct leech
	{
		BYTE odds;    //x
		WORD effect;  //y
	};
	leech hpleech; //x%��������ֵy
	leech mpleech; //x%���շ���ֵy

	BYTE hptomp; //ת������ֵΪ����ֵx��
	BYTE dhpp; //�����˺�����x%  
	BYTE dmpp; //�����˺�ֵ����x%    

	BYTE incgold; //���ӽ�Ǯ����x%
	BYTE doublexp; //x%˫������    
	BYTE mf; //���ӵ�����x%

	union {
		BYTE _five_props[5];
		struct {
			//������װ�������
			BYTE dpdam; //�����˺�����%x
			BYTE dmdam; //�����˺�����%x
			BYTE bdam; //�����˺�x%
			BYTE rdam; //�˺�����%x
			BYTE ignoredef; //%x����Ŀ�����
		};
	};

	WORD aftype;
	WORD afpoint;
	WORD dftype;
	WORD dfpoint;

	typedef std::map<WORD, WORD> SKILL;
	typedef SKILL::const_iterator const_iterator;
	SKILL skill;  //�������ܼӳ�
	SKILL skills; //ȫϵ���ܼӳ� 
	BYTE maxhprate;  //���ٷֱ��������hp
	BYTE maxmprate;  //���ٷֱ��������mp

	struct Freedom_Attribute {
		WORD str_Attribute;		// �����Ѿ��ӹ������ɵ�
		WORD inte_Attribute;	// �����Ѿ��ӹ������ɵ�
		WORD dex_Attribute;		// �����Ѿ��ӹ������ɵ�
		WORD spi_Attribute;		// �����Ѿ��ӹ������ɵ�
		WORD con_Attribute;		// �����Ѿ��ӹ������ɵ�

	} Freedom;

	//sky ������ʯ���Խṹ
	typedef std::vector<GemPop> GEMPOP;
	typedef GEMPOP::const_iterator const_iterator1;
	GEMPOP gempop;
};


struct PackageCallback
{
	virtual bool exec(zObject * o) = 0;
	virtual ~PackageCallback() {};
};

class Package :private zNoncopyable
{
protected:
	zObject** container;

	virtual bool add(zObject *object, bool find);
	virtual bool remove(zObject *object);
	virtual bool checkAdd(SceneUser *pUser, zObject *object, WORD x, WORD y);
public:
	Package(WORD type, DWORD id, WORD w, WORD h);
	virtual ~Package();

	virtual bool getObjectByZone(zObject **ret, WORD x, WORD y);
	virtual bool getObjectByID(zObject **ret, DWORD id);
	virtual void execEvery(PackageCallback &callback);

	virtual WORD space() const;
	virtual WORD size() const;
	WORD type() const;
	DWORD id() const;

	void setSpace(WORD);
private:
	friend class Packages;

	virtual void removeAll();
	bool find_space(WORD &x, WORD &y) const;
	virtual int position(WORD x, WORD y) const;

	WORD _type;
	DWORD _id;
	WORD _width;
	WORD _height;

	WORD _space;
	WORD _size;

};

#if 0
class MultiPack :public Package
{
protected:
	WORD width;
	WORD height;
	std::vector<std::vector<zObject *> >grid;
	std::set<zObject *> allset;
public:
	MultiPack(WORD type, DWORD id, WORD width, WORD height);
	virtual ~MultiPack();
	virtual bool add(zObject *object, bool find);
	virtual void remove(zObject *object);
	virtual void removeAll();
	virtual bool checkAdd(SceneUser *pUser, zObject *object, WORD x, WORD y);
	virtual bool getObjectByZone(zObject **ret, WORD x, WORD y, WORD width, WORD height);
	virtual void execEvery(PackageCallback &callback);
	virtual bool findSpace(WORD owidth, WORD oheight, WORD &x, WORD &y);
	std::set<zObject *> &getAllset()
	{
		return allset;
	}

	WORD get_width() const
	{
		return width;
	}

	WORD get_height() const
	{
		return height;
	}

};
#endif

class ObjectPack : public Package
{
public:
	ObjectPack(zObject* ob, int type = Cmd::OBJECTCELLTYPE_PACKAGE, bool consume = true);
	~ObjectPack();

	bool empty() const
	{
		return space() == size();
	}

	zObject* object()
	{
		return _ob;
	}

	void consume_dur_by(SceneUser* user, const zRTime& current);
	bool can_input()
	{
		if (!_ob || _ob->data.dur == 0) {
			return false;
		}
		return true;
	}

private:
	bool checkAdd(SceneUser *pUser, zObject *object, WORD x, WORD y);
	//bool add(zObject *object,bool find);

	zObject* _ob;
	bool _cosume_by_time;
	Timer _one_min;
};


class EquipPack : public Package
{
public:

	enum EQUIPNO {
		BODY,
		HEAD,
		HANDL,
		HANDR,
		BELT,
		NECKLACE,//5

		RINGL,
		RINGR,
		BANGL,
		BANGR,
		BOOTS,//10

		OTHERS,
		OTHERS1,
		OTHERS2,
		OTHERS3,
		OTHERS4, //15  
	};

	enum PACKNO {
		R_PACK,
		L_PACK,
		R_MAKE,
		L_MAKE,
	};
	EquipPack(SceneUser* user);
	~EquipPack();

	DWORD doubleexp_obj;
	DWORD doubleexp_obj_time;
	DWORD family_obj_times;
	DWORD family_obj_time;
	DWORD tong_obj_times;
	DWORD tong_obj_time;
	DWORD king_obj_times;
	DWORD king_obj_time;
	const Equips &getEquips() const;
	ObjectPack* pack(PACKNO no) const;
	zObject* equip(EQUIPNO no) const;

	bool getObjectByZone(zObject **ret, WORD x, WORD y);
	zObject *getObjectByEquipNo(EQUIPNO no);
	zObject *getObjectByEquipPos(DWORD no);

	bool costAttackDur(SceneUser *pThis);
	bool costDefenceDur(SceneUser *pThis);
	bool costAttackDurByPet(SceneUser *pThis);
	bool costDefenceDurByPet(SceneUser *pThis);
	void restituteDurability(SceneUser *pThis, const zRTime &ct);
	void updateDurability(SceneUser *pThis, DWORD value);
	DWORD fullAllEquiped(char *buf);

	bool needRecalc;
	int effectCount;

	bool skillReduceObject(SceneUser* pThis, DWORD kind, WORD num);
	bool skillCheckReduceObject(SceneUser* pThis, DWORD id, WORD num);
	bool canChangeColor();
	void calcAll();
	int reduceDur(SceneUser *pThis, DWORD which, DWORD type, DWORD num, bool needFresh = true, bool needCal = true);
	bool isTonic();

	void obtain_exp(SceneUser* user, DWORD exp, bool force = false);

	//װ�������Ƿ�Ϊ��
	bool isEmpty();
private:
	bool add(zObject *object, bool find);
	bool remove(zObject *object);
	bool checkAdd(SceneUser *pUser, zObject *object, WORD x, WORD y);

	//sky �����Ʒ��װ��ְҵ�Ƿ���ϵ�ǰ��ҵ�ְҵ                                                                     */
	bool IsJobEquip(DWORD useJob, DWORD EquipType);

	virtual int position(WORD x, WORD y) const;

	bool reduceDur(SceneUser *pThis, DWORD which);
	inline void freshDurability(SceneUser *pThis, zObject *o);
	inline void freshUserData(SceneUser *pThis);

	bool process_extra_add(zObject* ob);
	bool process_extra_remove(zObject* ob);
	bool process_extra_get(zObject** ob, WORD x, WORD y);

	SceneUser* owner;
	ObjectPack** packs;
	Equips equips;
	const static int _poses[60];

};

#define MAX_TAB_NUM 5
#define MIN_TAB_NUM 2

class MainPack :public Package
{
public:
	enum {
		//sky ���ð����ĸ�����Ч����
		WIDTH = PACK_WIDTH,
		HEIGHT = PACK_HEIGHT,
	};

	MainPack();
	~MainPack();

	BYTE TabNum; //sky ��ҿ���ʹ�õİ���ҳ��

	bool getObjectByZone(zObject **ret, WORD x, WORD y);
	zObject * getGold();
	DWORD getGoldNum();

	bool skillReduceObject(SceneUser* pThis, DWORD kind, DWORD num);

private:
	bool add(zObject *object, bool find);
	bool remove(zObject *object);
	bool checkAdd(SceneUser *pUser, zObject *object, WORD x, WORD y);

	zObject *gold;
};

class StorePack : public Package
{
public:
	enum {
		W = SAVEBOX_WIDTH,
		H = SAVEBOX_HEIGHT,
	};

	BYTE days;

	StorePack();
	~StorePack();

	void goldstore(SceneUser *pThis, bool notify = true);
	int load(BYTE* dest);
	int save(BYTE* dest);

	void notify(SceneUser* user);

private:
	bool checkAdd(SceneUser* pUser, zObject* object, WORD x, WORD y);

};

class PetPack : public Package
{
public:
	static const BYTE W = 8;
	static const BYTE H = 10;

	PetPack();
	~PetPack();

	WORD size() const;//������������
	void setAvailable(WORD);//������������

	bool isEmpty() const;

private:
	WORD available;//���õ�����

	bool checkAdd(SceneUser* pUser, zObject* object, WORD x, WORD y);
};

template<typename T>
class Type2Type
{
public:
	typedef T BASE;
};

class GlobalObjectIndex :private zEntryMgr< zEntryID >
{
private:
	static GlobalObjectIndex *onlyme;
	zMutex mlock;

	GlobalObjectIndex();
	~GlobalObjectIndex();
public:
	static GlobalObjectIndex *getInstance();
	static void delInstance();
	void removeObject(DWORD thisid);
	bool addObject(zObject * o);
	zObject *getObjectByThisid(DWORD thisid);
};

extern GlobalObjectIndex *const goi;

class UserObjectCompare
{
public:
	virtual bool isIt(zObject * object) = 0;
};

class UserObjectExec
{
public:
	virtual bool exec(zObject * object) = 0;
};

class UserObjectM :private zEntryMgr< zEntryID >
{
public:
	typedef std::vector<DWORD > ObjID_vec;
	typedef std::vector<zObject *> Obj_vec;

	UserObjectM();
	~UserObjectM();
	zObject * getObjectByThisID(DWORD thisid);
	zObject *getObjectByPos(const stObjectLocation &dst);
	void removeObjectByThisID(DWORD thisid);
	void removeObject(zObject * o);
	bool addObject(zObject * o);
	zObject *getObject(UserObjectCompare &comp);
	void execEvery(UserObjectExec &exec);

	DWORD exist(DWORD id, DWORD number, BYTE upgrade = 0, BYTE type = 0) const;
	int space(const SceneUser* user) const;

	zObject* getObjectByID(DWORD id, BYTE upgrade = 0, bool not_need_space = false) const;
	int reduceObjectNum(SceneUser* user, DWORD id, DWORD number, zObject*& update_ob, ObjID_vec& del_obs, BYTE upgrade = 0);
	int addObjectNum(SceneUser* user, DWORD id, DWORD number, zObject* & orig_ob, Obj_vec& new_obs, BYTE upgrade);
	int addGreenObjectNum(SceneUser* user, DWORD id, DWORD number, zObject* & orig_ob, Obj_vec& new_obs, BYTE upgrade);
};

class Packages
{
private:
	SceneUser *owner;

	Package** getPackage(int packs);

public:
	enum {
		MAIN_PACK = 1,
		LEFT_PACK = 2,
		RIGHT_PACK = 4,
		EQUIP_PACK = 8,
		STORE_PACK = 16,
		LM_PACK = 32,
		RM_PACK = 64,
		PET_PACK = 128,
	};

	UserObjectM uom;
	MainPack main;
	EquipPack equip;
	StorePack store;
	PetPack petPack;

	Packages(SceneUser* user);
	~Packages();
	void addMoney(DWORD num, const char *disc, const char *note = NULL, bool notify = true);
	void addGold(DWORD num, const char *disc, const char *note = NULL, bool notify = true, bool pack = false);
	void addTicket(DWORD num, const char *disc, const char *note = NULL, bool notify = true);
	bool checkMoney(DWORD need);
	bool checkTicket(DWORD need);
	bool checkGold(DWORD need);
	bool removeMoney(DWORD num, const char *disc);
	bool removeGold(DWORD num, const char *disc, bool need = true);
	bool removeTicket(DWORD num, const char *disc);

	bool moveObject(SceneUser *pUser, zObject *srcObj, stObjectLocation &dst);
	bool moveObjectToScene(zObject *o, const zPos &pos, DWORD overdue_msecs = 0, const unsigned long dwID = 0);
	bool removeObject(zObject *srcObj, bool notify = true, bool del = true);
	bool addObject(zObject *srcObj, bool needFind, int packs = 0);
	Package* getPackage(DWORD type, DWORD id);
	SceneUser *getOwner()
	{
		return owner;
	}

	template<typename T>
	void execEvery(Package* pack, T t)
	{
		typename T::BASE cb(this);
		pack->execEvery(cb);
	}

	template<typename T, typename P1>
	void execEvery(Package* pack, T t, P1 p1)
	{
		typename T::BASE cb(this, p1);
		pack->execEvery(cb);
	}

	zObject *getGold();
	DWORD getGoldNum();
};

#define AUTO_PACK Packages::MAIN_PACK |Packages::LEFT_PACK| Packages::RIGHT_PACK

struct Combination : public PackageCallback
{
public:
	Combination(SceneUser* user, zObject* get) : _user(user), _get(get), _num(0)
	{ }

	virtual bool exec(zObject* o);

	int num() const
	{
		return _num;
	}

private:
	SceneUser* _user;
	zObject* _get;
	int _num;
};

struct ClearPack : public PackageCallback
{
public:
	ClearPack(const Packages* ps) : _ps(ps)
	{ }

	virtual bool exec(zObject* p);
private:
	const Packages* _ps;
};

struct DropFromPack : public PackageCallback
{
public:
	struct Param
	{
		Package* pack;
		int drop_num;
		zPos pos;

		Param(Package* p, int d, const zPos& s) : pack(p), drop_num(d), pos(s)
		{ }
	};

	DropFromPack(const Packages* ps, const Param&  p);
	virtual bool exec(zObject* ob);
private:
	const Packages* _ps;
	Param _p;

	int _begin;
	int _pos;
};


#endif // !1def 



