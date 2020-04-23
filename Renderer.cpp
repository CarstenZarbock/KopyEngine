#include "Rendering\Renderer.h"
#include "Rendering\RenderResources\RenderResource.h"

//std::memset((char*)backBuffer, 0, MAX_X* MAX_Y);
//std::memset((char*)frontBuffer, 0, MAX_X* MAX_Y);
//std::memset((char*)gBuffer, 0, (MAX_X* MAX_Y) + MAX_Y);

//void CEngine::DrawImage(_MovingImage& image)
//{
//	DrawImage(image.File, image.CurrentX, image.CurrentY);
//}
//
//void CEngine::DrawImage(std::string file, int x, int y)
//{
//	std::ifstream myfile(file);
//	std::string line;
//	if (myfile.is_open())
//	{
//		int curLine = 0;
//		while (std::getline(myfile, line))
//		{
//			DrawToBackbuffer(line, x, y + curLine);
//			curLine++;
//		}
//		myfile.close();
//	}
//}

//Endscene
//std::memcpy((char*)frontBuffer, (char const*)backBuffer, MAX_X* MAX_Y);
//std::memset((char*)backBuffer, 0, MAX_X* MAX_Y);
//
//char* p_next_write = &gBuffer[0];
//for (int y = 0; y < MAX_Y; ++y)
//{
//	for (int x = 0; x < MAX_X; ++x)
//	{
//		if (gBuffer[(y * MAX_X) + x + y] == frontBuffer[(y * MAX_X) + x])
//		{
//			*p_next_write++;
//			continue;
//		}
//		*p_next_write++ = frontBuffer[(y * MAX_X) + x];
//	}
//	*p_next_write++ = '\n';
//}
//*p_next_write = '\0';
//
//std::cout.write(&gBuffer[0], (MAX_X * MAX_Y) + MAX_Y);
//std::cout.flush();