#pragma once

#include "stdafx.h"
#include "..\Core\Object.h"

class KInterface : public KObject
{
public:
	KInterface::KInterface() = default;
	KInterface::KInterface(class KEngine* engine)
	{
		Engine = engine;
	}

protected:
};