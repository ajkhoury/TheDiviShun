#pragma once

#include "Vector.h"
#include "Entity.h"

class World
{
public:
	char pad_0x0000[0x20]; //0x0000
	Vector m_vLocalPosition; //0x0020 
	char pad_0x002C[0xEC]; //0x002C
	char m_szName[8]; //0x0118 
	char pad_0x0120[0x250]; //0x0120
	Entity** m_pEntities; //0x0370 Update 12/04
	__int32 m_NumOfEntities; //0x0378
	__int32 m_MaxNumOfEntities; //0x037C 
	char pad_0x0380[0x268]; //0x0380

};//Size=0x05D8