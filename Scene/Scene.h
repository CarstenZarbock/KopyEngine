#pragma once

#include "stdafx.h"
#include "..\Core\Object.h"

class KScene : public KObject
{
public:
	KScene::KScene() = default;

	virtual void PreTick() override;
	virtual void Tick(const float deltaTime) override;
	virtual void PostTick() override;
	virtual void OnDestroy() override;
	
	
	virtual void Load();
	virtual void Unload();

	void NewObject(class KObject* object);
	void DestroyObject(class KObject* object);

protected:
	std::vector<class KObject*> Objects;

private:
	bool bIsOutOfTick = true;
};