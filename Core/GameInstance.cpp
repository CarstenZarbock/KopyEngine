#pragma once

#include "..\Scene\Scene.h"
#include "GameInstance.h"
#include "Engine.h"

void KGameInstance::InitializeDefaultScene(KEngine* engine)
{
	Scene = new KScene();
	Scene->Load();
}

void KGameInstance::Tick(const float deltaTime)
{
	if (Scene != nullptr)
	{
		Scene->Tick(deltaTime);
	}
}

bool KGameInstance::SwitchScene(KScene& scene, bool keepAlive /*= false*/)
{
	if (keepAlive == false)
	{
		UnloadScene();
	}

	LoadScene(scene);
	return true;
}

bool KGameInstance::LoadScene(KScene& scene)
{
	scene.Load();
	Scene = &scene;
	return true;
}

bool KGameInstance::RestoreScene(KScene& scene)
{
	return true;
}

bool KGameInstance::UnloadScene()
{
	if (Scene != nullptr)
	{
		Scene->Unload();
		Scene->SetMarkedForDestroy();
		Scene->OnDestroy();
		delete Scene;
		Scene = nullptr;
	}

	return true;
}