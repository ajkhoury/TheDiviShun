#include "sdk.h"

unsigned int __stdcall Init(LPVOID lpArguments)
{
	for (;;)
	{
		Sleep(200);

		SHORT shiftKey = GetAsyncKeyState(VK_LSHIFT);
		if (shiftKey & GetAsyncKeyState(VK_UP)) 
		{
			gVars.varReloadTime += 1.0f;
			printf("varReloadTime: %f\n", gVars.varReloadTime.Get());
		}
		if (shiftKey & GetAsyncKeyState(VK_DOWN))
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
		if (shiftKey & GetAsyncKeyState(VK_LEFT))
		{
			if (gVars.varFireRate < 1.0f)
				gVars.varFireRate = 1.0f;
			else
				gVars.varFireRate -= 1.0f;
			printf("varFireRate: %f\n", gVars.varFireRate.Get());
		}

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

		// Change fire rate
		auto fireRate = pAttributeInfo->GetFireRate();
		if (fireRate)
			fireRate->data = gVars.varFireRate;
		// Change reload time
		auto pReloadTimeMSFinal = pAttributeInfo->GetReloadTime();
		if (pReloadTimeMSFinal) 
			pReloadTimeMSFinal->data = gVars.varReloadTime;

		pAttributeInfo->NullRecoil();

	}

	return 0;
}


int __stdcall DllMain(HMODULE hModule, DWORD fdwReason, LPVOID lpvReserved)
{
	static HANDLE hMainThread = INVALID_HANDLE_VALUE;
	if (fdwReason == DLL_PROCESS_ATTACH)
	{
		Utils::CreateConsole("Yolo");
		hMainThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Init, NULL, 0, NULL);
		return (hMainThread != INVALID_HANDLE_VALUE);
	}
	else if (fdwReason == DLL_PROCESS_DETACH)
	{
		TerminateThread(hMainThread, 0);
		FreeConsole();
		return 1;
	}

	return 0;
}