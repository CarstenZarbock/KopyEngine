#pragma once

#include "stdafx.h"
#include "Object.h"

class KGameInstance : public KObject
{
public:
	KGameInstance::KGameInstance() = default;

	virtual const std::wstring& GetTitle() const { return Title; }

protected:
	std::wstring Title = L"";
};