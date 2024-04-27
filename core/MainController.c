#include "MainController.h"

int czarny;
int zielony;
int czerwony;
int niebieski;

void startGame(SDL_Surface* screen, SDL_Surface* charset, SDL_Texture* scrtex, SDL_Renderer* renderer) {
	SDL_Event event;

	bool quit = 0;
	char text[128];
	while (!quit) {
		SDL_FillRect(screen, NULL, czarny);
		DrawBoardAndPawns(screen);
		DrawMenu(screen, charset);
		//// tekst informacyjny / info text
		//DrawRectangle(screen, 4, 4, SCREEN_WIDTH - 8, 36, czerwony, niebieski);

		//sprintf_s(text, 128, "Szablon drugiego zadania");
		//DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 10, text, charset);

		//sprintf_s(text, 128, "Esc - wyjscie, \030 - przyspieszenie, \031 - zwolnienie");
		//DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 26, text, charset);

		SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
		//		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, scrtex, NULL, NULL);
		SDL_RenderPresent(renderer);

		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE) quit = 1;;
				break;
			case SDL_KEYUP:
				break;
			case SDL_QUIT:
				quit = 1;
				break;
			};
		};
	};
}

int closeGame(
	SDL_Surface* screen,
	SDL_Surface* charset,
	SDL_Texture* scrtex,
	SDL_Window* window,
	SDL_Renderer* renderer
) {

	SDL_FreeSurface(screen);
	SDL_FreeSurface(charset);
	SDL_DestroyTexture(scrtex);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}

int windowInit(
	SDL_Surface** screen,
	SDL_Surface** charset,
	SDL_Texture** scrtex,
	SDL_Window** window,
	SDL_Renderer** renderer
) {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("SDL_Init error: %s\n", SDL_GetError());
		return 1;
	}

	int rc = SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0,
		&*window, &*renderer);
	if (rc != 0) {
		SDL_Quit();
		printf("SDL_CreateWindowAndRenderer error: %s\n", SDL_GetError());
		return 1;
	};

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(*renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_SetRenderDrawColor(*renderer, 0, 0, 0, 255);

	SDL_SetWindowTitle(*window, "war_Caby");


	*screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32,
		0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);

	*scrtex = SDL_CreateTexture(*renderer, SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING,
		SCREEN_WIDTH, SCREEN_HEIGHT);


	// wy³¹czenie widocznoœci kursora myszy
	//SDL_ShowCursor(SDL_DISABLE);

	// wczytanie obrazka cs8x8.bmp
	*charset = SDL_LoadBMP("./cs8x8.bmp");
	if (*charset == NULL) {
		printf("SDL_LoadBMP(cs8x8.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(*screen);
		SDL_DestroyTexture(*scrtex);
		SDL_DestroyWindow(*window);
		SDL_DestroyRenderer(*renderer);
		SDL_Quit();
		return 1;
	};
	SDL_SetColorKey(*charset, true, 0x000000);

	czarny = SDL_MapRGB((*screen)->format, 0x00, 0x00, 0x00);
	zielony = SDL_MapRGB((*screen)->format, 0x00, 0xFF, 0x00);
	czerwony = SDL_MapRGB((*screen)->format, 0xFF, 0x00, 0x00);
	niebieski = SDL_MapRGB((*screen)->format, 0x11, 0x11, 0xCC);

	return 0;
}

void war_Caby_init_game() {
	SDL_Surface* screen = 0, * charset = 0;
	SDL_Texture* scrtex = 0;
	SDL_Window* window = 0;
	SDL_Renderer* renderer = 0;

	int init = windowInit(&screen, &charset, &scrtex, &window, &renderer);
	if (init) {
		return;
	};

	startGame(screen, charset, scrtex, renderer);


	closeGame(screen, charset, scrtex, window, renderer);
}