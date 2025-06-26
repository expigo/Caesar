#include<stdio.h>
#include<SDL3/SDL.h>

bool is_running = false;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

int window_width = 800;
int window_height = 600;

bool initialize_window(void) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "Failed to initialize SDL: %s", SDL_GetError());
        return false;
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
        return false;
    }
    printf("Window created successfully!\n");

    renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer) {
        fprintf(stderr, "Error creating SDL renderer: %s", SDL_GetError());
        return false;
    }

    return true;

}

void setup(void) {
    // TODO
}

void process_input(void) {
    SDL_Event event;
    
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_EVENT_QUIT:
                is_running = false;
                break;
            case SDL_EVENT_KEY_DOWN:
                if (event.key.key == SDLK_ESCAPE) is_running = false;
                break;
        }
    }
}

void update(void) {
    // TODO
}

void render(void) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0 , 255);
    SDL_RenderClear(renderer);


    SDL_RenderPresent(renderer);
}

void destroy_window(void) {
    SDL_DestroyWindow(window);
    SDL_Quit();
    printf("SDL shut down successfully. All good!\n");
}

int main(void) {
    
    is_running = initialize_window();

    setup();

    while (is_running) {
        process_input();
        update();
        render();
    }

    destroy_window();

    return 0;
}
