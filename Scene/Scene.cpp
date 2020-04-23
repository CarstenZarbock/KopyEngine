#pragma once

#include "Scene.h"

void KScene::PreTick()
{
	bIsOutOfTick = false;

	for (int objectIndex = Objects.size() - 1; objectIndex >= 0; --objectIndex)
	{
		KObject& object = *Objects[objectIndex];

		if (object.IsMarkedForDestroy() == true)
		{
			object.OnDestroy();
			delete &object;
			Objects.erase(Objects.begin() + objectIndex);
		}
		else
		{
			object.PreTick();
		}
	}
}

void KScene::Tick(const float deltaTime)
{
	for (KObject* object : Objects)
	{
		object->Tick(deltaTime);
	}
}

void KScene::PostTick()
{
	for (KObject* object : Objects)
	{
		object->PostTick();
	}

	bIsOutOfTick = true;
}

void KScene::NewObject(class KObject* object)
{
	if (object != nullptr)
	{
		Objects.push_back(object);
	}
}

void KScene::DestroyObject(class KObject* object)
{
	if (object != nullptr)
	{
		object->SetMarkedForDestroy();
	}
}

void KScene::OnDestroy()
{
	if (bIsOutOfTick == false)
	{
		return;
	}

	for (int objectIndex = Objects.size() - 1; objectIndex >= 0; --objectIndex)
	{
		KObject& object = *Objects[objectIndex];

		DestroyObject(&object);
		object.OnDestroy();
		delete& object;
		Objects.erase(Objects.begin() + objectIndex);
	}
}