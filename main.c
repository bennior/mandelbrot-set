#include <stdio.h>
#include <SDL3/SDL.h>

#define WIDTH 1000 
#define HEIGHT 1000
#define DELAY 3000

int main () {
		SDL_Window *window = NULL;
		SDL_Renderer *renderer = NULL;

		if (!SDL_Init(SDL_INIT_VIDEO)) {
				fprintf(stderr, "SDL failed to initialise: %s\n", SDL_GetError());
				return 1;
		}

		/* Creates a SDL window */
		window = SDL_CreateWindow("Mandelbrot set", WIDTH, HEIGHT, 0);

		if (window == NULL) {
				fprintf(stderr, "SDL window failed to initialise: %s\n", SDL_GetError());
				return 1;
		}

		renderer = SDL_CreateRenderer(window, NULL);

		if(renderer == NULL) {
				fprintf(stderr, "SDL renderer failed to initialise: %s\n", SDL_GetError());
				return 1;
		}


		/* Renders Rectangle*/
		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0x00);
		SDL_RenderClear(renderer);

		//screen center
		int scr_center_x = WIDTH / 1.5;
		int scr_center_y = HEIGHT / 2;

		int iterations = 100;


		const double a = 3.0 / WIDTH;
		const double b = 3.0 / HEIGHT;
		double cx = 0, cy = 0;

		for(int i = 0; i < WIDTH; i++) {
				for(int j = HEIGHT; j > 0; j--) {

						int scr_i = i - scr_center_x;
						int scr_j = j - scr_center_y;

						cx = (double) scr_i * a;
						cy = (double) scr_j * b;

						double zx = 0, zy = 0;
						int n = 0;
						while(n < iterations) {
								//complex squaring of z_n
								double tx = zx*zx - zy*zy; //temporary x component
								double ty = 2*zx*zy; //temporary y component
								
								//complex addition of z_n+1
								zx = tx + cx; //x componenent of z_n+1
								zy = ty + cy; //y component of z_n+1
								
								if(zx*zx + zy*zy >= 4) {
										double v = (double)n / iterations;

										Uint8 red = (Uint8)(9 * (1 - v) * v * v * v * 255);
										Uint8 green = (Uint8)(15 * (1 - v) * (1 - v) * v * v * 255);
										Uint8 blue = (Uint8)(8.5 * (1 - v) * (1 - v) * (1 - v) * v * 255);

										SDL_SetRenderDrawColor(renderer, red, green, blue, 0xFF);
										break;
								}
								SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
								n++;
						}
						const SDL_FRect pixel = {i, HEIGHT - j, 1, 1};
						SDL_RenderFillRect(renderer, &pixel);
				}
		}

		SDL_RenderPresent(renderer);

		/* Pauses all SDL subsystems for a variable amount of milliseconds */
		SDL_Delay(DELAY);

		/* Frees memory */
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
  
		/* Shuts down all SDL subsystems */
		SDL_Quit(); 
  
return 0;
}

