#pragma once

#include "Renderer.h"
#include "Rendering\RenderResources\RenderResource.h"

static char backBuffer[MAX_X * MAX_Y];
static char frontBuffer[MAX_X * MAX_Y];
static char gBuffer[(MAX_X * MAX_Y) + MAX_Y];

void KRenderer::CleanUp()
{

}

void KRenderer::Update()
{
	for (KRenderResource* res : Resources)
	{
		FDrawBuffer& buffer = res->GetDrawBuffer();
		DrawToBackbuffer(buffer, static_cast<int>(res->GetRenderX()), static_cast<int>(res->GetRenderY()));
	}   
}

void KRenderer::Draw()
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

void KRenderer::RegisterComponent(KRenderResource* resource)
{
	Resources.push_back(resource);
}

void KRenderer::UnRegisterComponent(KRenderResource* resource)
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

void KRenderer::DrawToBackbuffer(FDrawBuffer& buffer, int x, int y)
{
	size_t curOffset = 0;
	for (int curBuffer = 0; curBuffer < buffer.BufferNum; ++curBuffer)
	{
		int bufferY = y + curBuffer;

		if (bufferY >= MAX_Y || bufferY < 0 || x >= MAX_X)
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

		char* dest = static_cast<char*>(backBuffer);
		dest += bufferY * static_cast<int>(MAX_X);
		dest += std::min<int>(MAX_X, std::max<int>(x, 0));

		const void* source = nullptr;
		char* tempBuffer = nullptr;
		if (x >= 0)
		{
			tempBuffer = new char[buffer.BufferSizes[curBuffer]];
			std::memcpy(tempBuffer, buffer.Buffer + curOffset, buffer.BufferSizes[curBuffer]);
			source = static_cast<const void*>(tempBuffer);
		}
		else
		{
			tempBuffer = new char[buffer.BufferSizes[curBuffer]];
			std::memcpy(tempBuffer, buffer.Buffer + curOffset + (x * -1), buffer.BufferSizes[curBuffer] + x);
			source = static_cast<const void*>(tempBuffer);
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

		//if (std::memcmp(dest, source, size) != 0)
		//{
			std::memcpy(dest, source, size);
		//}

		delete tempBuffer;
		curOffset += buffer.BufferSizes[curBuffer];
	}

}