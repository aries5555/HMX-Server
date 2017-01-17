#ifndef __COUNTER_CTRL_H_
#define __COUNTER_CTRL_H_

#include "character.pb.h" 

class SceneUser;


/*------------------------------------------------------------------
 *
 * @Brief : ��¼������
 *
 * @Author: hzd 
 * @File  : CounterCtrl.h
 * @Date  : 2016/01/08 00:46
 * @Copyright (c) 2016,hzd, All rights reserved.
 *-----------------------------------------------------------------*/


enum MyCounterItem
{
	Counter_ITEM_SHOP = 1,
};

class MyCounters
{
public:
	MyCounters();
	~MyCounters();

	void Serialize(::protobuf::MyCounters& proto);
	void UnSerialize(const ::protobuf::MyCounters& proto);

	/* �붨ʱ�� */
	void Timer(int32 curTime);

	/* ���涼�ǰ���Ȼ�죬�ܣ��¼��� */

	void AddDay(int32 key,int32 val);
	void SubDay(int32 key, int32 val);

	void AddWeek(int32 key,int32 val);
	void SubWeek(int32 key, int32 val);

	void AddMonth(int32 key, int32 val);
	void SubMonth(int32 key, int32 val);

	void AddBetween(int32 key, int32 val,int32 starttime,int32 endtime);
	void SubBetween(int32 key, int32 val,int32 starttime, int32 endtime);

	/* ��ǰʱ��ļ��� */ 
	int32 GetCounter(int32 key);

private:

	// typeid = > value,start,end 
	std::multimap<int32, my_streble<int32, int32, int32> > counters;

};

#endif


