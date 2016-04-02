#pragma once

#include "AttributeManager.h"

class AttributeInfo
{
public:
	// not completely sure what's in here.
	struct Info {
		unsigned int unknown; // 0 - 4
		float data; // 4 - 8
		char poop[0x38];
	};

	struct Attribute {
		char unknown[0x78];
		Info* info;
	};

public:
	Info* GetInfoByIndex(unsigned int index)
	{
		if (!m_AttributeArray || !m_AttributeArray->info)
			return NULL;
		return &m_AttributeArray->info[index];
	}

	Info* GetFireRate()
	{
		AttributeManager* module = AttributeManager::Get();
		if (!module)
			return NULL;
		return GetInfoByIndex(module->GetIndexer(AttributeManager::RPMFinal)->index);
	}

	Info* GetReloadTime()
	{
		AttributeManager* module = AttributeManager::Get();
		if (!module)
			return NULL;
		return GetInfoByIndex(module->GetIndexer(AttributeManager::ReloadTimeMSFinal)->index);
	}

	bool NullRecoil()
	{
		AttributeManager* module = AttributeManager::Get();
		if (!module)
			return false;
		AttributeInfo::Info* pRecoilBaseFinal = GetInfoByIndex(module->GetIndexer(AttributeManager::RecoilBaseFinal)->index);
		if (!pRecoilBaseFinal)
			return false;
		pRecoilBaseFinal->data = 0.0f;
		AttributeInfo::Info* pRecoilClimbTimeMSFinal = GetInfoByIndex(module->GetIndexer(AttributeManager::RecoilClimbTimeMSFinal)->index);
		if (!pRecoilClimbTimeMSFinal)
			return false;
		pRecoilClimbTimeMSFinal->data = 0.0f;
		AttributeInfo::Info* pRecoilIncreasePerBulletFinal = GetInfoByIndex(module->GetIndexer(AttributeManager::RecoilIncreasePerBulletFinal)->index);
		if (!pRecoilIncreasePerBulletFinal)
			return false;
		pRecoilIncreasePerBulletFinal->data = 0.0f;
		AttributeInfo::Info* pRecoilMaxFinal = GetInfoByIndex(module->GetIndexer(AttributeManager::RecoilMaxFinal)->index);
		if (!pRecoilMaxFinal)
			return false;
		pRecoilMaxFinal->data = 0.0f;
		AttributeInfo::Info* pRecoilMinFinal = GetInfoByIndex(module->GetIndexer(AttributeManager::RecoilMinFinal)->index);
		if (!pRecoilMinFinal)
			return false;
		pRecoilMinFinal->data = 0.0f;
		AttributeInfo::Info* pRecoilRecoveryPerSecondFinal = GetInfoByIndex(module->GetIndexer(AttributeManager::RecoilRecoveryPerSecondFinal)->index);
		if (!pRecoilRecoveryPerSecondFinal)
			return false;
		pRecoilRecoveryPerSecondFinal->data = 0.0f;
		AttributeInfo::Info* pRecoilRecoveryTimeMSFinal = GetInfoByIndex(module->GetIndexer(AttributeManager::RecoilRecoveryTimeMSFinal)->index);
		if (!pRecoilRecoveryTimeMSFinal)
			return false;
		pRecoilRecoveryTimeMSFinal->data = 0.0f;
		return true;
	}
	
private:
	char unknown[0x28];
	Attribute* m_AttributeArray;
};