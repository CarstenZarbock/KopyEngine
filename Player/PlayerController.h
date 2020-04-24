#pragma once

#include "stdafx.h"
#include "..\Core\Object.h"

class KPlayerController : public KObject
{
public:
	KPlayerController::KPlayerController() = default;

	KPlayerController::KPlayerController(class KEngine* engine, class KScene* scene)
	{
		Engine = engine;
		Scene = scene;
	}

protected:
	class KScene* Scene = nullptr;
};