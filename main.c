#include <SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>

int	main(int argc, char **argv)
{
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	int				quit;
	SDL_Event		e;
	TTF_Font		*font;
	SDL_Color		color;
	SDL_Surface		*surface;
	SDL_Texture		*texture;
	SDL_Rect		textRect;

	(void)argc;
	(void)argv;
	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		fprintf(stderr, "Could not initialize SDL: %s\n", SDL_GetError());
		return (1);
	}
	// Create window
	window = SDL_CreateWindow("Terminal Emulator", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
	if (!window)
	{
		fprintf(stderr, "Could not create window: %s\n", SDL_GetError());
		SDL_Quit();
		return (1);
	}
	// Create renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer)
	{
		fprintf(stderr, "Could not create renderer: %s\n", SDL_GetError());
		SDL_DestroyWindow(window);
		SDL_Quit();
		return (1);
	}
	TTF_Init();
	font = TTF_OpenFont("fonts/Roboto_Mono/static/RobotoMono-Regular.ttf", 24);
	if (!font)
	{
		fprintf(stderr, "Could not load font: %s\n", SDL_GetError());
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return (1);
	}
	// color = {0, 0, 0, 255};
	color.r = 0;
	color.g = 0;
	color.b = 0;
	color.a = 255;
	surface = TTF_RenderText_Solid(font, "Hello, World!", color);
	if (!surface)
	{
		fprintf(stderr, "Could not render text: %s\n", SDL_GetError());
		TTF_CloseFont(font);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return (1);
	}
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (!texture)
	{
		fprintf(stderr, "Could not create texture: %s\n", SDL_GetError());
		SDL_FreeSurface(surface);
		TTF_CloseFont(font);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return (1);
	}
	// Clean up the surface; it's no longer needed after creating the texture
	SDL_FreeSurface(surface);
	// REnder the texture
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	// Main loop flag
	quit = 0;
	// Event handler
	// Main loop
	while (!quit)
	{
		// Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			// User requests quit
			if (e.type == SDL_QUIT)
			{
				quit = 1;
			}
		}
		// Clear screen with white background
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);
		// Render text here (using SDL_ttf)
		surface = TTF_RenderText_Solid(font, "Hello, World!", color);
		if (!surface)
		{
			fprintf(stderr, "Could not render text: %s\n", SDL_GetError());
			break ;
		}
		texture = SDL_CreateTextureFromSurface(renderer, surface);
		if (!texture)
		{
			fprintf(stderr, "Could not create texture: %s\n", SDL_GetError());
			SDL_FreeSurface(surface);
			break ;
		}
		SDL_FreeSurface(surface);
		textRect.x = 50;
		textRect.y = 50;
		SDL_QueryTexture(texture, NULL, NULL, &textRect.w, &textRect.h);
		SDL_RenderCopy(renderer, texture, NULL, &textRect);
		SDL_DestroyTexture(texture);
		// Update screen
		SDL_RenderPresent(renderer);
	}
	// Free resources and close SDL
	SDL_DestroyTexture(texture);
	TTF_CloseFont(font);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return (0);
}
