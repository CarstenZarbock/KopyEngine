#pragma once

#include "stdafx.h"

class KEngine
{

public:
	KEngine::KEngine() = default;
	KEngine::KEngine(class KGameInstance* gameInstance)
	{
		GameInstance = gameInstance;
	}

	int Main();

protected:
	clock_t begin_time;
	clock_t f_time;

	class KGameInstance* GameInstance = nullptr;
public:
	class KRenderer* Renderer = nullptr;

protected:
	void UpdateTitle(float deltaTime, float fps);
	bool Initialize();
	void BeginScene(float deltaTime, float fps);
	void UpdateScene(float deltaTime, float fps);
	void EndScene();
	int Loop();
	void CleanUp();
	void HideCursor();
};