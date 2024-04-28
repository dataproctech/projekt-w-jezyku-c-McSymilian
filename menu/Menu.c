#include "Menu.h"
#include "../data_model/PawnsOnBoard.h"
#include "../archive/GameStateIO.h"
#include <stdbool.h>

#define C1 0xE4C59E
#define C2 0xAF8260 
#define C3 0x803D3B
#define C4 0x322C2B

#define BUTTON_BGCOLOR_HOVER 0x4d4231
#define BUTTON_OUTLINECOLOR_HOVER 0x665d4f
#define FONT 8


void NewGame();
void SaveGame();
void ResumeGame();


void DrawButton(SDL_Surface* screen, int startX, int startY, const char* label, SDL_Surface* charset, bool selected) {
	int stringStartX = startX + (BUTTON_WIDTH - strlen(label) * FONT) / 2;
	int stringStartY = startY + (BUTTON_HEIGHT - FONT) / 2;
	DrawRectangle(screen, startX, startY, BUTTON_WIDTH, BUTTON_HEIGHT, selected ? BUTTON_OUTLINECOLOR_HOVER : C3, selected ? BUTTON_BGCOLOR_HOVER : C1);
	DrawString(screen, stringStartX, stringStartY, label, charset);
}

void DrawMenu(SDL_Surface* screen, SDL_Surface* charset) {
	DrawRectangle(screen, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, C2, C2);
	DrawMenuButtons(screen, charset);
}

void DrawMenuButtons(SDL_Surface* screen, SDL_Surface* charset)
{
	int buttonStartX = (SCREEN_WIDTH - BUTTON_WIDTH) / 2;
	int buttonStartY = (SCREEN_HEIGHT - (4 * BUTTON_HEIGHT + 3 * BUTTON_SPACE_BETWEEN)) / 2;
	const char* buttonLabels[4] = { "CONTINUE GAME", "NEW GAME", "RESUME GAME", "SAVE & EXIT" };
	for (int i = 0; i < 4; i++) {
		int mouseX, mouseY;
		SDL_GetMouseState(&mouseX, &mouseY);
		bool selected = mouseX > buttonStartX && mouseX < buttonStartX + BUTTON_WIDTH && mouseY > buttonStartY && mouseY < buttonStartY + BUTTON_HEIGHT;
		DrawButton(screen, buttonStartX, buttonStartY, buttonLabels[i], charset, selected);
		buttonStartY += BUTTON_HEIGHT + BUTTON_SPACE_BETWEEN;
	}
}

/*
* MenuClick - button click event handling
* 
* @param x - mouse x coordinate of the click
* @param y - mouse y coordinate of the click
* 
* @return 0 - if the menu should hide, 1 - if the game should be saved and exited, 2 - if nothing should happen
*/
int MenuClick(int x, int y)
{
	if (x > (SCREEN_WIDTH - BUTTON_WIDTH) / 2 && x < (SCREEN_WIDTH - BUTTON_WIDTH) / 2 + BUTTON_WIDTH)
	{
		if (y > (SCREEN_HEIGHT - (4 * BUTTON_HEIGHT + 3 * BUTTON_SPACE_BETWEEN)) / 2 && y < (SCREEN_HEIGHT - (4 * BUTTON_HEIGHT + 3 * BUTTON_SPACE_BETWEEN)) / 2 + BUTTON_HEIGHT)
		{
			return 0;
		}
		else if (y > (SCREEN_HEIGHT - (4 * BUTTON_HEIGHT + 3 * BUTTON_SPACE_BETWEEN)) / 2 + BUTTON_HEIGHT + BUTTON_SPACE_BETWEEN && y < (SCREEN_HEIGHT - (4 * BUTTON_HEIGHT + 3 * BUTTON_SPACE_BETWEEN)) / 2 + 2 * BUTTON_HEIGHT + BUTTON_SPACE_BETWEEN)
		{
			NewGame();
			return 0;
		}
		else if (y > (SCREEN_HEIGHT - (4 * BUTTON_HEIGHT + 3 * BUTTON_SPACE_BETWEEN)) / 2 + 2 * BUTTON_HEIGHT + 2 * BUTTON_SPACE_BETWEEN && y < (SCREEN_HEIGHT - (4 * BUTTON_HEIGHT + 3 * BUTTON_SPACE_BETWEEN)) / 2 + 3 * BUTTON_HEIGHT + 2 * BUTTON_SPACE_BETWEEN)
		{
			ResumeGame();
			return 0;
		}
		else if (y > (SCREEN_HEIGHT - (4 * BUTTON_HEIGHT + 3 * BUTTON_SPACE_BETWEEN)) / 2 + 3 * BUTTON_HEIGHT + 3 * BUTTON_SPACE_BETWEEN && y < (SCREEN_HEIGHT - (4 * BUTTON_HEIGHT + 3 * BUTTON_SPACE_BETWEEN)) / 2 + 4 * BUTTON_HEIGHT + 3 * BUTTON_SPACE_BETWEEN)
		{
			SaveGame();
			return 1;
		}
	}
	return 2;

}

void NewGame() {
	resetPawns();
}

void SaveGame() {
	writeGameState(
		getPawnsOnBoard(),
		getBoardSize()
	);
}

void ResumeGame() {
	Board board = readGameState();
	if (board != NULL) {
		getPawnsOnBoard();
		
		upadatePawnsOnBoard(board);
	}	
}
