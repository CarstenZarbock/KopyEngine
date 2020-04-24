#pragma once

#include "stdafx.h"
#include "Object.h"

class KGameInstance : public KObject
{
public:
	KGameInstance::KGameInstance() = default;

	virtual const std::wstring& GetTitle() const { return Title; }
	virtual void InitializeDefaultScene(class KEngine* engine);
	virtual void Tick(const float deltaTime);

	bool SwitchScene(class KScene& scene, bool keepAlive = false);
	bool RestoreScene(class KScene& scene);

protected:
	bool LoadScene(class KScene& scene);
	bool UnloadScene();

	std::wstring Title = L"";

	class KScene* Scene = nullptr;
};