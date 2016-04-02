#pragma once

#include "World.h"

class Client
{
public:
	char pad_0x0000[0x28]; //0x0000
	World* pWorld; //0x0028 
	char pad_0x0030[0x3D8]; //0x0030

};//Size=0x0408

class RClient
{
public:
	char pad_0x0000[0x88]; //0x0000
	void* N000001AE; //0x0088 
	char pad_0x0090[0x90]; //0x0090
	Client* pClient; //0x0120 
	void* N000001C2; //0x0128 
	char pad_0x0130[0x2D8]; //0x0130

	static RClient* Get()
	{
		size_t location = (size_t)(Utils::FindPattern((size_t)GetModuleHandle(NULL), 0x6B57000, sigRClient, sizeof(sigRClient)) + 3);
		#ifdef MESSAGES_ENABLED
		printf("location: 0x%IX\n", location);
		#endif
		
		DWORD offset = *(DWORD*)(location);
		#ifdef MESSAGES_ENABLED
		printf("offset: 0x%X\n", offset);
		#endif
		
		size_t address = *(size_t*)(location + offset + 4);
		#ifdef MESSAGES_ENABLED
		printf("address: 0x%IX\n", address);
		#endif

		return (RClient*)address;
	}

};//Size=0x0408