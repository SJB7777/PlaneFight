#ifndef __SCREEN_H__
#define __SCREEN_H__

#include "raylib.h"

namespace Screen {


	void DimScreen(float alpha = 0.75f);
	void SetButton(float x, float y, Color color, const char* text);
	
};

#endif
