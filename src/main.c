#include<stdio.h>
#include<SDL3/SDL.h>

SDL_Window* window = NULL;

int window_width = 800;
int window_height = 600;

int main(void) {
    
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "Failed to initialize SDL: %s", SDL_GetError());
        return 1;
    }
    printf("SDL initialized successfully!\n");

    window = SDL_CreateWindow(
            "Caesar",
            window_width,
            window_height,
            0
        );

    if (!window) {
        fprintf(stderr, "Could not create window: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    printf("Window created successfully!\n");

    SDL_Delay(2000);

    SDL_DestroyWindow(window);
    SDL_Quit();

    printf("SDL shut down successfully. All good!\n");

    return 0;
}
