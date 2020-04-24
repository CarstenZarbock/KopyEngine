#pragma once

#include "stdafx.h"
#include "..\Core\Object.h"

class KGameObject : public KObject
{
public:
	KGameObject::KGameObject(class KEngine* engine)
	{
		Engine = engine;
	}

	virtual void Initialize() override;
	virtual void Tick(const float deltaTime) override;

protected:
	class KRenderResource* RenderResource = nullptr;
};