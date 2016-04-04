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

	bool SetDrawSpeed(float flDrawSpeed)
	{
		AttributeManager* module = AttributeManager::Get();
		if (!module)
			return false;
		auto pWeaponDrawSpeedModFinal = GetInfoByIndex(module->GetIndexer(AttributeManager::WeaponDrawSpeedModFinal)->index);
		if (!pWeaponDrawSpeedModFinal)
			return false;
		pWeaponDrawSpeedModFinal->data = flDrawSpeed;
		return true;
	}

	bool SetHolsterSpeed(float flHolsterSpeed)
	{
		AttributeManager* module = AttributeManager::Get();
		if (!module)
			return false;
		auto pWeaponHolsterSpeedModFinal = GetInfoByIndex(module->GetIndexer(AttributeManager::WeaponHolsterSpeedModFinal)->index);
		if (!pWeaponHolsterSpeedModFinal)
			return false;
		pWeaponHolsterSpeedModFinal->data = flHolsterSpeed;
		return true;
	}

	bool SetFireRate(float flFireRate)
	{
		AttributeManager* module = AttributeManager::Get();
		if (!module)
			return false;
		auto pRPMFinal = GetInfoByIndex(module->GetIndexer(AttributeManager::RPMFinal)->index);
		if (!pRPMFinal)
			return false;
		pRPMFinal->data = flFireRate;
		return true;
	}

	bool SetReloadTime(float flTime)
	{
		AttributeManager* module = AttributeManager::Get();
		if (!module)
			return false;
		auto pReloadTimeMSFinal = GetInfoByIndex(module->GetIndexer(AttributeManager::ReloadTimeMSFinal)->index);
		if (!pReloadTimeMSFinal)
			return false;
		pReloadTimeMSFinal->data = flTime;
		return true;
	}

	bool SetShellReloadTime(float flTime)
	{
		AttributeManager* module = AttributeManager::Get();
		if (!module)
			return false;
		auto pInitialShellReloadTimeMSFinal = GetInfoByIndex(module->GetIndexer(AttributeManager::InitialShellReloadTimeMSFinal)->index);
		if (!pInitialShellReloadTimeMSFinal)
			return false;
		pInitialShellReloadTimeMSFinal->data = flTime;
		return true;
	}

	bool SetMovementSpeed(float flMovementSpeed)
	{
		AttributeManager* module = AttributeManager::Get();
		if (!module)
			return false;
		auto pMovementSpeedModFinal = GetInfoByIndex(module->GetIndexer(AttributeManager::MovementSpeedModFinal)->index);
		if (!pMovementSpeedModFinal)
			return false;
		pMovementSpeedModFinal->data = flMovementSpeed;
		return true;
	}

	bool NullRecoil()
	{
		AttributeManager* module = AttributeManager::Get();
		if (!module)
			return false;
		auto pRecoilBaseFinal = GetInfoByIndex(module->GetIndexer(AttributeManager::RecoilBaseFinal)->index);
		if (!pRecoilBaseFinal)
			return false;
		pRecoilBaseFinal->data = 0.0f;
		auto pRecoilClimbTimeMSFinal = GetInfoByIndex(module->GetIndexer(AttributeManager::RecoilClimbTimeMSFinal)->index);
		if (!pRecoilClimbTimeMSFinal)
			return false;
		pRecoilClimbTimeMSFinal->data = 0.0f;
		auto pRecoilIncreasePerBulletFinal = GetInfoByIndex(module->GetIndexer(AttributeManager::RecoilIncreasePerBulletFinal)->index);
		if (!pRecoilIncreasePerBulletFinal)
			return false;
		pRecoilIncreasePerBulletFinal->data = 0.0f;
		auto pRecoilMaxFinal = GetInfoByIndex(module->GetIndexer(AttributeManager::RecoilMaxFinal)->index);
		if (!pRecoilMaxFinal)
			return false;
		pRecoilMaxFinal->data = 0.0f;
		auto pRecoilMinFinal = GetInfoByIndex(module->GetIndexer(AttributeManager::RecoilMinFinal)->index);
		if (!pRecoilMinFinal)
			return false;
		pRecoilMinFinal->data = 0.0f;
		auto pHorizontalRecoilBorderLeftFinal = GetInfoByIndex(module->GetIndexer(AttributeManager::HorizontalRecoilBorderLeftFinal)->index);
		if (!pHorizontalRecoilBorderLeftFinal)
			return false;
		pHorizontalRecoilBorderLeftFinal->data = 0.0f;
		auto pHorizontalRecoilBorderRightFinal = GetInfoByIndex(module->GetIndexer(AttributeManager::HorizontalRecoilBorderRightFinal)->index);
		if (!pHorizontalRecoilBorderRightFinal)
			return false;
		pHorizontalRecoilBorderRightFinal->data = 0.0f;
		auto pHorizontalRecoilLeftFinal = GetInfoByIndex(module->GetIndexer(AttributeManager::HorizontalRecoilLeftFinal)->index);
		if (!pHorizontalRecoilLeftFinal)
			return false;
		pHorizontalRecoilLeftFinal->data = 0.0f;
		auto pHorizontalRecoilRecoveryTimeMSFinal = GetInfoByIndex(module->GetIndexer(AttributeManager::HorizontalRecoilRecoveryTimeMSFinal)->index);
		if (!pHorizontalRecoilRecoveryTimeMSFinal)
			return false;
		pHorizontalRecoilRecoveryTimeMSFinal->data = 0.0f;
		auto pHorizontalRecoilRightFinal = GetInfoByIndex(module->GetIndexer(AttributeManager::HorizontalRecoilRightFinal)->index);
		if (!pHorizontalRecoilRightFinal)
			return false;
		pHorizontalRecoilRightFinal->data = 0.0f;
		auto pHorizontalRecoilTimeMSFinal = GetInfoByIndex(module->GetIndexer(AttributeManager::HorizontalRecoilTimeMSFinal)->index);
		if (!pHorizontalRecoilTimeMSFinal)
			return false;
		pHorizontalRecoilTimeMSFinal->data = 0.0f;
		return true;
	}

	bool NullSpread()
	{
		AttributeManager* module = AttributeManager::Get();
		if (!module)
			return false;
		auto pAimSpreadMaxFinal = GetInfoByIndex(module->GetIndexer(AttributeManager::AimSpreadMaxFinal)->index);
		if (!pAimSpreadMaxFinal)
			return false;
		pAimSpreadMaxFinal->data = 0.0f;
		auto pAimSpreadMinFinal = GetInfoByIndex(module->GetIndexer(AttributeManager::AimSpreadMinFinal)->index);
		if (!pAimSpreadMinFinal)
			return false;
		pAimSpreadMinFinal->data = 0.0f;
		auto pCoverAimSpreadMaxFinal = GetInfoByIndex(module->GetIndexer(AttributeManager::CoverAimSpreadMaxFinal)->index);
		if (!pCoverAimSpreadMaxFinal)
			return false;
		pCoverAimSpreadMaxFinal->data = 0.0f;
		auto pCoverAimSpreadMinFinal = GetInfoByIndex(module->GetIndexer(AttributeManager::CoverAimSpreadMinFinal)->index);
		if (!pCoverAimSpreadMinFinal)
			return false;
		pCoverAimSpreadMinFinal->data = 0.0f;
		auto pCoverSpreadMaxFinal = GetInfoByIndex(module->GetIndexer(AttributeManager::CoverSpreadMaxFinal)->index);
		if (!pCoverSpreadMaxFinal)
			return false;
		pCoverSpreadMaxFinal->data = 0.0f;
		auto pCoverSpreadMinFinal = GetInfoByIndex(module->GetIndexer(AttributeManager::CoverSpreadMinFinal)->index);
		if (!pCoverSpreadMinFinal)
			return false;
		pCoverSpreadMinFinal->data = 0.0f;
		auto pSpreadIncreaseSpeedFinal = GetInfoByIndex(module->GetIndexer(AttributeManager::SpreadIncreaseSpeedFinal)->index);
		if (!pSpreadIncreaseSpeedFinal)
			return false;
		pSpreadIncreaseSpeedFinal->data = 0.0f;
		auto pSpreadIncreaseTimeMSFinal = GetInfoByIndex(module->GetIndexer(AttributeManager::SpreadIncreaseTimeMSFinal)->index);
		if (!pSpreadIncreaseTimeMSFinal)
			return false;
		pSpreadIncreaseTimeMSFinal->data = 0.0f;
		auto pSpreadMaxFinal = GetInfoByIndex(module->GetIndexer(AttributeManager::SpreadMaxFinal)->index);
		if (!pSpreadMaxFinal)
			return false;
		pSpreadMaxFinal->data = 0.0f;
		auto pSpreadMinFinal = GetInfoByIndex(module->GetIndexer(AttributeManager::SpreadMinFinal)->index);
		if (!pSpreadMinFinal)
			return false;
		pSpreadMinFinal->data = 0.0f;
		auto pSpreadMovementModFinal = GetInfoByIndex(module->GetIndexer(AttributeManager::SpreadMovementModFinal)->index);
		if (!pSpreadMovementModFinal)
			return false;
		pSpreadMovementModFinal->data = 0.0f;
		auto pSpreadReductionSpeedFinal = GetInfoByIndex(module->GetIndexer(AttributeManager::SpreadReductionSpeedFinal)->index);
		if (!pSpreadReductionSpeedFinal)
			return false;
		pSpreadReductionSpeedFinal->data = 0.0f;

		return true;
	}

	bool NullSway()
	{
		AttributeManager* module = AttributeManager::Get();
		if (!module)
			return false;
		auto pAimSwayMinHorizontalFinal = GetInfoByIndex(module->GetIndexer(AttributeManager::AimSwayMinHorizontalFinal)->index);
		if (!pAimSwayMinHorizontalFinal)
			return false;
		pAimSwayMinHorizontalFinal->data = 0.0f;
		auto pAimSwayMaxHorizontalFinal = GetInfoByIndex(module->GetIndexer(AttributeManager::AimSwayMaxHorizontalFinal)->index);
		if (!pAimSwayMaxHorizontalFinal)
			return false;
		pAimSwayMaxHorizontalFinal->data = 0.0f;
		auto pAimSwayMinVerticalFinal = GetInfoByIndex(module->GetIndexer(AttributeManager::AimSwayMinVerticalFinal)->index);
		if (!pAimSwayMinVerticalFinal)
			return false;
		pAimSwayMinVerticalFinal->data = 0.0f;
		auto pAimSwayMaxVerticalFinal = GetInfoByIndex(module->GetIndexer(AttributeManager::AimSwayMaxVerticalFinal)->index);
		if (!pAimSwayMaxVerticalFinal)
			return false;
		pAimSwayMaxVerticalFinal->data = 0.0f;
		auto pAimSwaySpeedModifierFinal = GetInfoByIndex(module->GetIndexer(AttributeManager::AimSwaySpeedModifierFinal)->index);
		if (!pAimSwaySpeedModifierFinal)
			return false;
		pAimSwaySpeedModifierFinal->data = 0.0f;
		return true;
	}
	
private:
	char unknown[0x28];
	Attribute* m_AttributeArray;
};