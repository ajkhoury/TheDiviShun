#include "sdk.h"

unsigned int __stdcall KeyboardListenerThread(LPVOID lpArguments)
{
	for (;;)
	{
		Sleep(1); // Make sure cpu can keep up

		bool shift = IsKeyDown(VK_LSHIFT);
		bool ctrl = IsKeyDown(VK_LCONTROL);

		if (shift && WasKeyDown(VK_UP))
		{
			gVars.varReloadTime += 1.0f;
			printf("varReloadTime: %f\n", gVars.varReloadTime.Get());
		}
		if (shift && WasKeyDown(VK_DOWN))
		{
			if (gVars.varReloadTime <= 1.0f)
				gVars.varReloadTime = 1.0f;
			else
				gVars.varReloadTime -= 1.0f;
			printf("varReloadTime: %f\n", gVars.varReloadTime.Get());
		}

		if (shift && WasKeyDown(VK_RIGHT))
		{
			if (gVars.varFireRate > 8000.0f)
				gVars.varFireRate = 8000.0f;
			else
				gVars.varFireRate += 1.0f;
			printf("varFireRate: %f\n", gVars.varFireRate.Get());
		}
		if (shift && WasKeyDown(VK_LEFT))
		{
			if (gVars.varFireRate < 1.0f)
				gVars.varFireRate = 1.0f;
			else
				gVars.varFireRate -= 1.0f;
			printf("varFireRate: %f\n", gVars.varFireRate.Get());
		}

		if (ctrl && WasKeyDown(VK_RIGHT))
		{
			gVars.varMovementSpeed += 1.0f;
			printf("varMovementSpeed: %f\n", gVars.varMovementSpeed.Get());
		}
		if (ctrl && WasKeyDown(VK_LEFT))
		{
			if (gVars.varMovementSpeed < 1.0f)
				gVars.varMovementSpeed = 1.0f;
			else
				gVars.varMovementSpeed -= 1.0f;
			printf("varMovementSpeed: %f\n", gVars.varMovementSpeed.Get());
		}
		 
		if (WasKeyDown(VK_F1))
		{
			gVars.varEnableMovementSpeed.Toggle();
			printf("varEnableMovementSpeed: %s\n", gVars.varEnableMovementSpeed.Get() ? "true" : "false");
		}

		#ifdef Friend
		if (WasKeyDown(VK_NUMPAD1))
		{
			gVars.varFireRate = 700.0f;
			printf("gVars.varFireRate: %f\n", gVars.varFireRate.Get());
		}
		else if (WasKeyDown(VK_NUMPAD2))
		{
			gVars.varFireRate = 1000.0f;
			printf("gVars.varFireRate: %f\n", gVars.varFireRate.Get());
		}
		else if (WasKeyDown(VK_NUMPAD3))
		{
			gVars.varFireRate = 2100.0f;
			printf("gVars.varFireRate: %f\n", gVars.varFireRate.Get());
		}
		#endif
	}

}

unsigned int __stdcall HackThread(LPVOID lpArguments)
{

	for (;;)
	{
		RClient* pRClient = RClient::Get();
		if (!pRClient)
			continue;
		#ifdef MESSAGES_ENABLED
		printf("pRClient: %p\n", pRClient);
		#endif

		Client* pClient = pRClient->pClient;
		if (!pClient)
			continue;
		#ifdef MESSAGES_ENABLED
		printf("pClient: %p\n", pClient);
		#endif

		World* pWorld = pClient->pWorld;
		if (!pWorld)
			continue;		
		#ifdef MESSAGES_ENABLED
		printf("pWorld: %p\n", pWorld);
		#endif

		// Make sure entity array has been initialized
		if (!pWorld->m_pEntities)
			continue;

		Entity* pLocalEntity = pWorld->m_pEntities[LOCAL_ENTITY_INDEX];
		if (!pLocalEntity)
			continue;
		#ifdef MESSAGES_ENABLED
		printf("pLocalEntity: %p\n", pLocalEntity);
		#endif

		AttributeInfo* pAttributeInfo = pLocalEntity->m_pAttributeInfo;
		if (!pAttributeInfo)
			continue;
		#ifdef MESSAGES_ENABLED
		printf("pAttributeInfo: %p\n", pAttributeInfo);
		#endif

		/* Hacks start here! */

		#ifndef Friend
		// Change movement speed
		if (gVars.varEnableMovementSpeed)
			pAttributeInfo->SetMovementSpeed(gVars.varMovementSpeed.Get());
		else
			pAttributeInfo->SetMovementSpeed(1.0f);
		#endif	

		// Change fire rate
		#ifndef Friend
		pAttributeInfo->SetFireRate(gVars.varFireRate.Get());
		#endif

		// Change reload time
		pAttributeInfo->SetReloadTime(gVars.varReloadTime.Get());

		// And shell reload time
		pAttributeInfo->SetShellReloadTime(gVars.varReloadTime.Get());

		// Null Recoil
		pAttributeInfo->NullRecoil();

		// Null Spread
		pAttributeInfo->NullSpread();

		// Null Sway
		pAttributeInfo->NullSway();

		//AttributeManager* module = AttributeManager::Get();
		//if (!module)
		//	continue;
		//for (int idx = 0; idx < AttributeManager::AtributeIndexMax; idx++)
		//{
		//	auto pAttrib = pAttributeInfo->GetInfoByIndex(module->GetIndexer(idx)->index);
		//	if (!pAttrib)
		//		continue;
		//	printf("%s: %f\n", GetAttributeStringfromIndex(idx), pAttrib->data);
		//}

	}

	return 0;
}


int __stdcall DllMain(HMODULE hModule, DWORD fdwReason, LPVOID lpvReserved)
{
	static HANDLE hMainThread = INVALID_HANDLE_VALUE;
	static HANDLE hKeyThread = INVALID_HANDLE_VALUE;
	if (fdwReason == DLL_PROCESS_ATTACH)
	{
		printf("*** TheDiviShun ***\n    by dude719\n\nLoaded at 0x%IX\n", (size_t)hModule);
		hMainThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)HackThread, NULL, 0, NULL);
		hKeyThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)KeyboardListenerThread, NULL, 0, NULL);
		return (hMainThread != INVALID_HANDLE_VALUE) && (hKeyThread != INVALID_HANDLE_VALUE);
	}
	else if (fdwReason == DLL_PROCESS_DETACH)
	{
		//gConsole.Release();
		
		TerminateThread(hMainThread, 0);
		TerminateThread(hKeyThread, 0);
	}

	return 0;
}