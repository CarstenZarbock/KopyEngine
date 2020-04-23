#include "Renderer.h"
#include "Rendering\RenderResources\RenderResource.h"

static char backBuffer[MAX_X * MAX_Y];
static char frontBuffer[MAX_X * MAX_Y];
static char gBuffer[(MAX_X * MAX_Y) + MAX_Y];

void CRenderer::CleanUp()
{

}

void CRenderer::Update()
{
	for (CRenderResource* res : Resources)
	{
		FDrawBuffer& buffer = res->GetDrawBuffer();
		DrawToBackbuffer(buffer, static_cast<int>(res->GetX()), static_cast<int>(res->GetY()));
	}   
}

void CRenderer::Draw()
{
	std::memcpy((char*)frontBuffer, (char const*)backBuffer, MAX_X* MAX_Y);
	std::memset((char*)backBuffer, 0, MAX_X* MAX_Y);

	char* p_next_write = &gBuffer[0];
	for (int y = 0; y < MAX_Y; ++y)
	{
		for (int x = 0; x < MAX_X; ++x)
		{
			if (gBuffer[(y * MAX_X) + x + y] == frontBuffer[(y * MAX_X) + x])
			{
				*p_next_write++;
				continue;
			}
			*p_next_write++ = frontBuffer[(y * MAX_X) + x];
		}
		*p_next_write++ = '\n';
	}
	*p_next_write = '\0';
	
	std::cout.write(&gBuffer[0], (MAX_X * MAX_Y) + MAX_Y);
	std::cout.flush();
}

void CRenderer::RegisterComponent(CRenderResource* resource)
{
	Resources.push_back(resource);
}

void CRenderer::UnRegisterComponent(CRenderResource* resource)
{
	for (int idx = 0; idx < Resources.size(); ++idx)
	{
		if (Resources[idx] == resource)
		{
			Resources.erase(Resources.begin() + idx);
			return;
		}
	}
}

void CRenderer::DrawToBackbuffer(FDrawBuffer& buffer, int x, int y)
{
	size_t curOffset = 0;
	for (int curBuffer = 0; curBuffer < buffer.BufferNum; ++curBuffer)
	{
		int bufY = y + curBuffer;

		if (bufY >= MAX_Y || bufY < 0 || x >= MAX_X)
		{
			curOffset += buffer.BufferSizes[curBuffer];
			continue;
		}

		if (x < 0)
		{
			if (static_cast<int>(buffer.BufferSizes[curBuffer]) + x <= 0)
			{
				curOffset += buffer.BufferSizes[curBuffer];
				continue;
			}
		}

		char* dest;
		dest = (char*)(DWORD)(backBuffer);
		dest += (bufY * MAX_X);
		dest += std::min<int>(MAX_X, std::max<int>(x, 0));

		const void* source = nullptr;
		char* temp = nullptr;
		if (x >= 0)
		{
			temp = new char[buffer.BufferSizes[curBuffer]];
			std::memcpy(temp, buffer.Buffer + curOffset, buffer.BufferSizes[curBuffer]);
			source = static_cast<const void*>(temp);
		}
		else
		{
			temp = new char[buffer.BufferSizes[curBuffer]];
			std::memcpy(temp, buffer.Buffer + curOffset + (x * -1), buffer.BufferSizes[curBuffer] + x);
			source = static_cast<const void*>(temp);
		}

		size_t size;
		if (x >= 0)
		{
			size = std::min<int>(buffer.BufferSizes[curBuffer], MAX_X - x);
		}
		else
		{
			size = std::min<int>(buffer.BufferSizes[curBuffer] + x, MAX_X);
		}

		if (std::memcmp(dest, source, size) != 0)
		{
			std::memcpy(dest, source, size);
		}

		delete temp;
		curOffset += buffer.BufferSizes[curBuffer];
	}

}