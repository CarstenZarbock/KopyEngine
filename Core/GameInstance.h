#pragma once

#include "stdafx.h"

class KGameInstance
{
public:
	KGameInstance::KGameInstance() = default;
	virtual void PreTick() = 0;
	virtual void Tick(float deltaTime) = 0;
	virtual void PostTick() = 0;

	virtual const std::wstring& GetTitle() const { return Title; }

protected:
	std::wstring Title = L"";
};