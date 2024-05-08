#include "MainController.h"
#include"../SDL2-2.0.10/include/SDL_video.h"
//#include"../SDL2-2.0.10/include/SDL_image.h"

int czarny;
//int zielony;
//int czerwony;
//int niebieski;

static void startGame(SDL_Surface* screen, SDL_Surface* charset, SDL_Texture* scrtex, SDL_Renderer* renderer) {
	SDL_Event event;

	bool quit = 0;
	char text[128];
	bool isMenuTop = true;
	while (!quit) {
		SDL_FillRect(screen, NULL, czarny);

		if (isMenuTop)
			DrawMenu(screen, charset);
		else
			DrawBoardAndPawns(screen);

		SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
		//		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, scrtex, NULL, NULL);
		SDL_RenderPresent(renderer);

		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE) isMenuTop = !isMenuTop;;
				break;
			case SDL_MOUSEBUTTONDOWN:
				int x, y;
				SDL_GetMouseState(&x, &y);
	
				if (isMenuTop) {
					int action = MenuClick(x, y);

					if (action == 1) 
						quit = 1;
					
					else if (action == 0) 
						isMenuTop = false;
					
				}
				else BoardClick(x, y);
				break;
			case SDL_QUIT:
				quit = 1;
				break;
			};
		};
	};
}

static int closeGame(
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

static int windowInit(
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

	//SDL_Surface* loadedSurface = IMG_Load("./war_Caby.png");
	//SDL_SetWindowIcon(*window, loadedSurface);

	czarny = SDL_MapRGB((*screen)->format, 0x00, 0x00, 0x00);
	//zielony = SDL_MapRGB((*screen)->format, 0x00, 0xFF, 0x00);
	//czerwony = SDL_MapRGB((*screen)->format, 0xFF, 0x00, 0x00);
	//niebieski = SDL_MapRGB((*screen)->format, 0x11, 0x11, 0xCC);

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

