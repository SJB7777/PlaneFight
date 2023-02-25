#include "screen.h"

void Screen::DimScreen(float alpha) {
	DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), ColorAlpha(BLACK, alpha));
}



void Screen::SetButton(float x, float y, Color color, const char* text) {}