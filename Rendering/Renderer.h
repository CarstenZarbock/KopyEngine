#pragma once

#include "stdafx.h"

#define MAX_X 80
#define MAX_Y 30

struct FDrawBuffer;

class KRenderer
{
public:
	KRenderer::KRenderer() = default;
	void CleanUp();
	void Update();
	void Draw();

	void RegisterComponent(class CRenderResource* resource);
	void UnRegisterComponent(class CRenderResource* resource);

protected:
	void DrawToBackbuffer(FDrawBuffer& buffer, int x, int y);

	std::vector<class CRenderResource*> Resources;

};

