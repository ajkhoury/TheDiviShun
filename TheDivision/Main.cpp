#include "sdk.h"

void CheckKeys()
{
	// Make sure CPU can keep up
	SHORT shiftKey = GetAsyncKeyState(VK_LSHIFT);

	if (shiftKey & GetAsyncKeyState(VK_UP))
	{
		gVars.varReloadTime += 1.0f;
		printf("varReloadTime: %f\n", gVars.varReloadTime.Get());
	}
	else if (shiftKey & GetAsyncKeyState(VK_DOWN))
	{
		if (gVars.varReloadTime <= 1.0f)
			gVars.varReloadTime = 1.0f;
		else
			gVars.varReloadTime -= 1.0f;
		printf("varReloadTime: %f\n", gVars.varReloadTime.Get());
	}

	if (shiftKey & GetAsyncKeyState(VK_RIGHT))
	{
		if (gVars.varFireRate > 8000.0f)
			gVars.varFireRate = 8000.0f;
		else
			gVars.varFireRate += 1.0f;
		printf("varFireRate: %f\n", gVars.varFireRate.Get());
	}
	else if (shiftKey & GetAsyncKeyState(VK_LEFT))
	{
		if (gVars.varFireRate < 1.0f)
			gVars.varFireRate = 1.0f;
		else
			gVars.varFireRate -= 1.0f;
		printf("varFireRate: %f\n", gVars.varFireRate.Get());
	}

	SHORT ctrlKey = GetAsyncKeyState(VK_LCONTROL);
	if (ctrlKey & GetAsyncKeyState(VK_RIGHT))
	{
		gVars.varMovementSpeed += 1.0f;
		printf("varMovementSpeed: %f\n", gVars.varMovementSpeed.Get());
	}
	else if (ctrlKey & GetAsyncKeyState(VK_LEFT))
	{
		if (gVars.varMovementSpeed < 1.0f)
			gVars.varMovementSpeed = 1.0f;
		else
			gVars.varMovementSpeed -= 1.0f;
		printf("varMovementSpeed: %f\n", gVars.varMovementSpeed.Get());
	}


}

unsigned int __stdcall Init(LPVOID lpArguments)
{
	for (;;)
	{
		CheckKeys();

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

		// Change movement speed
		pAttributeInfo->SetMovementSpeed(gVars.varMovementSpeed.Get());

		// Change fire rate
		pAttributeInfo->SetFireRate(gVars.varFireRate.Get());

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



	}

	return 0;
}


int __stdcall DllMain(HMODULE hModule, DWORD fdwReason, LPVOID lpvReserved)
{
	static HANDLE hMainThread = INVALID_HANDLE_VALUE;
	if (fdwReason == DLL_PROCESS_ATTACH)
	{
		//Utils::CreateConsole("Yolo");
		printf("*** TheDiviShun ***\n    by dude719\n\nLoaded at 0x%IX\n", (size_t)hModule);
		hMainThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Init, NULL, 0, NULL);
		return (hMainThread != INVALID_HANDLE_VALUE);
	}
	else if (fdwReason == DLL_PROCESS_DETACH)
	{
		gConsole.Release();
		TerminateThread(hMainThread, 0);
	}

	return 0;
}