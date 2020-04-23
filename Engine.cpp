#pragma once

#include "Rendering\Renderer.h"
#include "Core\GameInstance.h"

#include "Engine.h"

bool KEngine::Initialize()
{
	begin_time = clock();

	RECT ConsoleRect;
	HWND console = GetConsoleWindow();
	GetWindowRect(console, &ConsoleRect);
	MoveWindow(console, ConsoleRect.left, ConsoleRect.top, 680, 535, TRUE);

	HideCursor();

	Renderer = new KRenderer();

	return true;
}

void KEngine::HideCursor()
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(out, &cursorInfo);
}

void setCursorPosition(int x, int y)
{
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(hOut, coord);
}

void KEngine::UpdateTitle(const float deltaTime, const float fps)
{
	//Move to OS module
	std::wstring windowTitle;
	if (GameInstance == nullptr)
	{
		windowTitle = L"TextEngine - NoGame ++ Delta: ";
	}
	else
	{
		windowTitle = GameInstance->GetTitle();
	}

	windowTitle.append(L" Delta: ");
	windowTitle.append(std::to_wstring(deltaTime));
	windowTitle.append(L" FPS: ");
	windowTitle.append(std::to_wstring(fps));

	SetConsoleTitle(windowTitle.c_str());
}

int KEngine::Loop()
{
	float drawRefresh = 0.f;

	f_time = clock();

	while (true)
	{
		float seconds = float(clock() - begin_time);
		float deltaTime = (seconds / CLOCKS_PER_SEC);

		float f_seconds = float(clock() - f_time);
		float f_deltaTime = (f_seconds / CLOCKS_PER_SEC);
		float fps = 1.f / std::max<float>(f_deltaTime, 0.00001f);

		begin_time = clock();
		drawRefresh += 1.f * deltaTime;

		BeginScene(deltaTime, fps);

		UpdateScene(deltaTime, fps);

		if (drawRefresh > 0.033f)
		{
			drawRefresh -= 0.033f;
			EndScene();
		}

		setCursorPosition(0, 0);
		Sleep(1);
	}

	return 0;
}

void KEngine::BeginScene(const float deltaTime, const float fps)
{
	UpdateTitle(deltaTime, fps);
	HideCursor();
	setCursorPosition(0, 0);

	if (GameInstance == nullptr)
	{
		return;
	}

	GameInstance->PreTick();
}

void KEngine::UpdateScene(const float deltaTime, const float fps)
{
	if (GameInstance == nullptr)
	{
		return;
	}

	GameInstance->Tick(deltaTime);
}

void KEngine::EndScene()
{

	if (GameInstance != nullptr)
	{
		GameInstance->PostTick();
	}

	setCursorPosition(0, 0);

	Renderer->Update();
	Renderer->Draw();

	f_time = clock();
}

int KEngine::Main()
{
	Initialize();

	const int result = Loop();

	CleanUp();
	return result;
}

void KEngine::CleanUp()
{
	Renderer->CleanUp();
	delete Renderer;
}