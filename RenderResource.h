#pragma once

class RenderResource
{

};

//struct _MovingImage
//{
//	float CurrentDelta = 0;
//	float ImageSpeed = 100.f;
//	int CurrentX = 0;
//	int CurrentY = 0;
//
//	int TargetX = 0;
//	int TargetY = 0;
//
//	std::string File = "";
//
//	_MovingImage() = default;
//	_MovingImage(std::string file, float speed, int x, int y, int xT, int yT)
//		: File(file),
//		ImageSpeed(speed),
//		CurrentX(x),
//		CurrentY(y),
//		TargetX(xT),
//		TargetY(yT)
//	{
//
//	}
//
//	void Move(float deltaTime)
//	{
//		CurrentDelta += 1.f * deltaTime;
//		if (CurrentDelta > (1.f / ImageSpeed))
//		{
//			CurrentX += TargetX > CurrentX ? 1 : -1;
//			CurrentY += TargetY > CurrentY ? 1 : -1;
//
//			CurrentDelta -= (1.f / ImageSpeed);
//		}
//	}
//};
//
//struct _MovingText
//{
//public:
//	float CurrentDelta = 0;
//	float TextSpeed = 100.f;
//	int CurrentCharRight = 0;
//	int MaxCharsShown = 0;
//
//	std::string Text;
//
//	_MovingText() = default;
//	_MovingText(std::string text)
//		: Text(text)
//	{
//		MaxCharsShown = text.length();
//	}
//
//	_MovingText(std::string text, float speed)
//		: Text(text),
//		TextSpeed(speed)
//	{
//		MaxCharsShown = text.length();
//	}
//
//	_MovingText(std::string text, float speed, int maxChars)
//		: Text(text),
//		TextSpeed(speed),
//		MaxCharsShown(maxChars)
//	{
//
//	}
//
//	void MoveText(float deltaTime)
//	{
//		CurrentDelta += 1.f * deltaTime;
//		if (CurrentDelta > (1.f / TextSpeed))
//		{
//			CurrentCharRight += 1;
//			if (CurrentCharRight > Text.length())
//			{
//				CurrentCharRight = 0;
//			}
//			CurrentDelta -= (1.f / TextSpeed);
//		}
//	}
//
//	std::string GetText()
//	{
//		return std::string(Text.substr(CurrentCharRight, Text.length() - CurrentCharRight)
//			+ " "
//			+ Text.substr(0, CurrentCharRight)).substr(0, MaxCharsShown);
//	}
//
//};