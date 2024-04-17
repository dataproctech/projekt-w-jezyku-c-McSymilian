#include "Menu.h"

#define C1 0xE4C59E
#define C2 0xAF8260 
#define C3 0x803D3B
#define C4 0x322C2B
#define FONT 8

void DrawButton(SDL_Surface* screen, int startX, int startY, const char* label, SDL_Surface* charset) {
	int stringStartX = startX + (BUTTON_WIDTH - strlen(label) * FONT) / 2;
	int stringStartY = startY + (BUTTON_HEIGHT - FONT) / 2;
	DrawRectangle(screen, startX, startY, BUTTON_WIDTH, BUTTON_HEIGHT, C3, C1);
	DrawString(screen, stringStartX, stringStartY, label, charset);
}

void DrawMenu(SDL_Surface* screen, SDL_Surface* charset) {
	DrawRectangle(screen, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, C2, C2);
	int buttonStartX = (SCREEN_WIDTH - BUTTON_WIDTH) / 2;
	int buttonStartY = (SCREEN_HEIGHT - (3 * BUTTON_HEIGHT + 2 * BUTTON_SPACE_BETWEEN)) / 2;
	const char* buttonLabels[3] = { "NEW GAME", "CONTINUE GAME", "SAVE & EXIT"};
	for (int i = 0; i < 3; i++) {
		DrawButton(screen, buttonStartX, buttonStartY, buttonLabels[i], charset);
		buttonStartY += BUTTON_HEIGHT + BUTTON_SPACE_BETWEEN;
	}
}