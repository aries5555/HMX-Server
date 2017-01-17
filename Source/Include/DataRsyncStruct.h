#ifndef __DATA_RYSNCT_STRUCT_H_
#define __DATA_RYSNCT_STRUCT_H_

#include "BaseDefine.h"

// ȫ��ͨ�����ݱ��� 

enum EMixItemNumberType
{
	E_MIXITEM_NUMBER_TYPE_NULL = 0,
	E_MIXITEM_NUMBER_TYPE_POWER, // ս����һ
	E_MIXITEM_NUMBER_TYPE_MAX,

};

enum EMixItemBinaryType
{
	E_MIXITEM_BINARY_TYPE_NULL = 0,
};

#pragma pack(push,1)

// ��ֵ�� 
struct StMixItemNumberTable
{
	int32 nType;
	int64 nValue;
};

// �����Ʊ� 
struct StMixItemBinaryTable
{
	int32 nType;
	char data[4096];
};


#pragma pack(pop)


#endif


