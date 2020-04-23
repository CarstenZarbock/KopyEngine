#pragma once
#include "..\stdfx.h"

#define MAX_X 80
#define MAX_Y 30

struct FDrawBuffer;

class CRenderer
{
public:
	CRenderer::CRenderer() = default;
	void CleanUp();
	void Update();
	void Draw();

	void RegisterComponent(class CRenderResource* resource);
	void UnRegisterComponent(class CRenderResource* resource);

protected:
	void DrawToBackbuffer(FDrawBuffer& buffer, int x, int y);

	std::vector<class CRenderResource*> Resources;

};

