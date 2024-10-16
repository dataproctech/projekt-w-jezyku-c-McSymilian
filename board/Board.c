#include "Board.h"
#include "Pawns.h"
#include "BoardParameters.h"
#include <stdbool.h>
#include "../utility/Util.h"

#define DARK   0x261203
#define DARK_BORDER   0xcfb29d

#define BRIGHT 0xcfb29d
#define BRIGHT_BORDER 0x261203

#define HOVER 0x9e8d8a
#define HOVER_BORDER 0xf2dad5

#define SELECTED 0xb5ae6e
#define SELECTED_BORDER 0x787348

#define DESTINATION 0xaee6de
#define DESTINATION_BORDER 0x586e6b

#define KNOCKDOWN 0xf72b02
#define KNOCKDOWN_BORDER 0x781602

struct Field_s {
	bool isHover;
	bool isDark;
	bool isSelected;
	bool isDestination;
	bool isKnockDown;
} const Field_default = {false, false, false, false, false};

typedef struct Field_s Field;

static void DrawSquare(int xStart, int yStart, int squareSize, SDL_Surface* screen, Field field) {
	Uint32 bgColor;
	Uint32 borderColor;
	
	if (field.isSelected) {
		bgColor = SELECTED;
		borderColor = SELECTED_BORDER;
	}
	else if (field.isDestination) {
		bgColor = DESTINATION;
		borderColor = DESTINATION_BORDER;
	}
	else if (field.isKnockDown) {
		bgColor = KNOCKDOWN;
		borderColor = KNOCKDOWN_BORDER;
	}
	else if (field.isHover) {
		bgColor = HOVER;
		borderColor = HOVER_BORDER;
	}
	else if (field.isDark) {
		bgColor = DARK;
		borderColor = DARK_BORDER;
	}
	else {
		bgColor = BRIGHT;
		borderColor = BRIGHT_BORDER;
	}

	DrawRectangle(screen, xStart, yStart, squareSize, squareSize, borderColor, bgColor);
}

struct Coordinates_s {
	int x;
	int y;
} Coordinates_default = { -1, -1 };


Coordinates selected = { .x = -1, .y = -1 };
void setSelected(int x, int y) {
	selected.x = x;
	selected.y = y;
}

void clearSelected() {
	selected.x = -1;
	selected.y = -1;
}
static bool isSelected(int x, int y) {
	return selected.x == x && selected.y == y;
}

static Coordinates destinations[14] = { 0 };
static int destinationCount = -1;
void addDestination(int x, int y) {
	++destinationCount;
	destinations[destinationCount].x = x;
	destinations[destinationCount].y = y;
}

void clearDestination() {
	while(destinationCount >= 0) {
		destinations[destinationCount].x = -1;
		destinations[destinationCount].y = -1;
		--destinationCount;
	}
}
bool isDestination(int x, int y) {
	for (int i = 0; i <= destinationCount; i++) 
		if (destinations[i].x == x && destinations[i].y == y) 
			return true;
		
	return false;
}

static Coordinates knockDown[4] = { 0 };
static int knockDownCount = -1;
void addKnockDown(int x, int y) {
	++knockDownCount;
	knockDown[knockDownCount].x = x;
	knockDown[knockDownCount].y = y;
}
void clearKnockDown() {
	while(knockDownCount >= 0) {
		knockDown[knockDownCount].x = -1;
		knockDown[knockDownCount].y = -1;
		--knockDownCount;
	}
}
bool isKnockDown(int x, int y) {
	for (int i = 0; i <= knockDownCount; i++) 
		if (knockDown[i].x == x && knockDown[i].y == y) 
			return true;
		
	return false;
}

static Coordinates hovered = { .x = -1, .y = -1 };
void setHovered(int x, int y) {
	hovered.x = x;
	hovered.y = y;
}
void setDefaultHovered() {
	hovered = Coordinates_default;
}
void clearHovered() {
	hovered.x = -1;
	hovered.y = -1;
}
static bool isHovered(int x, int y) {
	return hovered.x > -1 && hovered.y > -1 && hovered.x == x && hovered.y == y;
}

void DrawBoard(SDL_Surface* screen) {

	DrawSquare(BOARD_START_X, BOARD_START_Y, BOARD_DRAW_SIZE , screen, Field_default);
	DrawSquare(BOARD_START_X + PADDING - 5, BOARD_START_Y + PADDING - 5, SQUARE_SIZE * 8 + 10, screen, (Field){.isDark = true});

	bool color = false;

	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);

	int correctedX = mouseX - BOARD_START_X - PADDING;
	int correctedY = mouseY - BOARD_START_Y - PADDING;

	if (correctedX >= 0 && correctedY >= 0)
		setHovered(correctedX / SQUARE_SIZE, correctedY / SQUARE_SIZE);
	else
		setDefaultHovered();

	for (int x = 0; x < 8; x++) {
		int xStart = BOARD_START_X + PADDING + x * SQUARE_SIZE;
		for (int y = 0; y < 8; y++) {
			Field field = (Field){
				.isDark = color,
				.isSelected = isSelected(x, y),
				.isHover = isHovered(x, y),
				.isDestination = isDestination(x, y),
				.isKnockDown = isKnockDown(x, y)
			};
			
			int yStart = BOARD_START_Y + PADDING + y * SQUARE_SIZE;

			DrawSquare(xStart, yStart, SQUARE_SIZE, screen, field);

			color = !color;
		}
		color = !color;
	}
}

