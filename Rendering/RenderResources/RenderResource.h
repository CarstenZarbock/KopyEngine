#pragma once

#include "stdfx.h"

struct FDrawBuffer
{
public:
	FDrawBuffer() = default;
	~FDrawBuffer()
	{
		delete[] Buffer;
		delete[] BufferSizes;
	}

	FDrawBuffer(std::string& textSource)
	{
		BufferNum = 1;
		BufferSizes = new size_t[BufferNum];
		BufferSizes[0] = textSource.length();

		Buffer = new char[BufferSizes[0]];
		std::memcpy(Buffer, textSource.c_str(), BufferSizes[0]);
	}

	FDrawBuffer(std::vector<std::string>& vecStrSource)
	{
		BufferNum = vecStrSource.size();
		BufferSizes = new size_t[BufferNum];

		int index = 0;
		size_t totalSize = 0;
		for (std::string& source : vecStrSource)
		{
			BufferSizes[index] = source.length();
			totalSize += BufferSizes[index];
			index++;
		}

		Buffer = new char[totalSize];
		size_t curOff = 0;
		index = 0;
		for (std::string& source : vecStrSource)
		{
			size_t buffSize = BufferSizes[index];
			std::memcpy(Buffer + curOff, source.c_str(), buffSize);
			curOff += buffSize;
			index++;
		}
	}

	FDrawBuffer(char* buffer, size_t size)
	{
		Buffer = buffer;
		BufferNum = 1;
		BufferSizes = new size_t[1];
		BufferSizes[0] = size;
	}

	char* Buffer = nullptr;
	int BufferNum = 0;
	size_t* BufferSizes = nullptr;
};

class CRenderResource
{
public:
	CRenderResource() = default;
	~CRenderResource()
	{
		delete Buffer;
	}

	virtual FDrawBuffer& GetDrawBuffer() { return *Buffer; }
	virtual const float GetX() const { return X; }
	virtual const float GetY() const { return Y; }
	virtual void SetLocation(float x, float y) { X = x; Y = y; }

protected:
	float X = 0;
	float Y = 0;

	FDrawBuffer* Buffer = nullptr;
};

class CRenderResourceText : public CRenderResource
{
public:
	CRenderResourceText::CRenderResourceText() = default;
	CRenderResourceText::CRenderResourceText(std::string& text, float x, float y)
	{
		Buffer = new FDrawBuffer(text);
		X = x;
		Y = y;
	}
};

class CRenderResourceImage : public CRenderResource
{
public:
	CRenderResourceImage::CRenderResourceImage() = default;
	CRenderResourceImage::CRenderResourceImage(std::vector<std::string> vecBuffer, float x, float y)
	{
		Buffer = new FDrawBuffer(vecBuffer);
		X = x;
		Y = y;
	}

	static std::vector<std::string> LoadImage(std::string resourceAsset)
	{
		std::vector<std::string> bufferResult;
		std::ifstream resource(resourceAsset);
		std::string line;
		if (resource.is_open())
		{
			int curLine = 0;
			while (std::getline(resource, line))
			{
				bufferResult.push_back(line);
				curLine++;
			}
			resource.close();
		}
		return bufferResult;
	}
};