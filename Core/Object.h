#pragma once

#include "stdafx.h"

class KObject
{
public:
	KObject::KObject() = default;
	virtual void PreTick() { };
	virtual void Tick(const float deltaTime) { };
	virtual void PostTick() { };

	virtual void OnDestroy() { };

	const bool IsMarkedForDestroy() const { return bMarkedForDestroy; }
	void SetMarkedForDestroy() { bMarkedForDestroy = true; }

private:
	bool bMarkedForDestroy = false;
};