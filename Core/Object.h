#pragma once

#include "stdafx.h"

class KObject
{
public:
	KObject::KObject()
	{
		KObject(nullptr);
	}

	KObject::KObject(class KEngine* engine)
	{
		Engine = engine;
	}

	virtual void Initialize() { };
	virtual void PreTick() { };
	virtual void Tick(const float deltaTime) { };
	virtual void PostTick() { };

	virtual void OnDestroy() { };

	const bool IsMarkedForDestroy() const { return bMarkedForDestroy; }
	void SetMarkedForDestroy() { bMarkedForDestroy = true; }

protected:
	bool bMarkedForDestroy = false;

	class KEngine* Engine = nullptr;
};