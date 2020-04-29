#pragma once

#include "stdafx.h"

enum class EAlignment : uint8_t
{
	LEFT,
	CENTER,
	RIGHT
};

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

	FDrawBuffer(std::vector<std::string>& vecStrSource, bool useAlpha = false, char alphaChar = char(' '))
	{
		UseAlpha = useAlpha;
		AlphaChar = alphaChar;

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
	bool UseAlpha = false;
	char AlphaChar = char(' ');
};

class KRenderResource
{
public:
	KRenderResource() = default;
	~KRenderResource()
	{
		delete Buffer;
	}

	virtual FDrawBuffer& GetDrawBuffer() { return *Buffer; }
	virtual void SetLocation(float x, float y)
	{
		X = x;
		Y = y;
	}
	size_t GetMaxBufferSize()
	{
		size_t maxSize = 0;
		for (int i = 0; i < Buffer->BufferNum; ++i)
		{
			if (Buffer->BufferSizes[i] > maxSize)
			{
				maxSize = Buffer->BufferSizes[i];
			}
		}
		return maxSize;
	}

	virtual const float GetX()
	{
		return X;
	}

	virtual const float GetY()
	{
		return Y;
	}

	virtual const float GetRenderX()
	{
		switch (Alignment)
		{
		case EAlignment::LEFT:
			return X;
		case EAlignment::CENTER:
			return X - (GetMaxBufferSize() / 2.f);
		case EAlignment::RIGHT:
			return X - GetMaxBufferSize();
		default:
			return X;
		}
	}

	virtual const float GetRenderY()
	{
		return Y;
	}

protected:
	float X = 0;
	float Y = 0;

	FDrawBuffer* Buffer = nullptr;

	EAlignment Alignment = EAlignment::LEFT;
};

class KRenderResourceText : public KRenderResource
{
public:
	KRenderResourceText::KRenderResourceText() = default;
	KRenderResourceText::KRenderResourceText(std::string& text, float x, float y)
	{
		Buffer = new FDrawBuffer(text);
		X = x;
		Y = y;
	}

	KRenderResourceText::KRenderResourceText(std::string& text, float x, float y, EAlignment alignment)
	{
		Buffer = new FDrawBuffer(text);
		X = x;
		Y = y;
		Alignment = alignment;
	}

	void ChangeText(std::string& text)
	{
		delete Buffer;
		Buffer = new FDrawBuffer(text);
	}
};

class KRenderResourceImage : public KRenderResource
{
public:
	KRenderResourceImage::KRenderResourceImage() = default;
	KRenderResourceImage::KRenderResourceImage(std::vector<std::string> vecBuffer, float x, float y, bool useAlpha = false, char alphaChar = char(' '))
	{
		Buffer = new FDrawBuffer(vecBuffer, useAlpha, alphaChar);
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