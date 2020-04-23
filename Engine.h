#pragma once

#include "stdfx.h"

class CGameInstance
{
public:
	CGameInstance::CGameInstance() = default;
	virtual void PreTick() = 0;
	virtual void Tick(float deltaTime) = 0;
	virtual void PostTick() = 0;

	virtual const std::wstring& GetTitle() const = 0;
};

class CEngine
{

public:
	CEngine::CEngine() = default;
	CEngine::CEngine(CGameInstance* gameInstance)
	{
		GameInstance = gameInstance;
	}

	int Main();

protected:
	clock_t begin_time;
	clock_t f_time;

	CGameInstance* GameInstance = nullptr;
public:
	class CRenderer* Renderer = nullptr;

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