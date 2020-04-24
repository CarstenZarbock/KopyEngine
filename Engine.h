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
	void PreInitialize();
	class KRenderer& GetRenderer() { return *Renderer; }

protected:
	void UpdateTitle(const float deltaTime, const float fps);
	
	bool Initialize();
	
	void BeginScene(const float deltaTime, const float fps);
	void UpdateScene(const float deltaTime, const float fps);
	void EndScene();
	int Loop();
	void CleanUp();
	void HideCursor();

	class KRenderer* Renderer = nullptr;
};