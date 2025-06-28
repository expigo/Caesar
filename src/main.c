#include<stdio.h>
#include<stdint.h>
#include<stdbool.h>
#include<stdlib.h>
#include<SDL3/SDL.h>

bool is_running = false;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

uint32_t* color_buffer = NULL;
SDL_Texture* color_buffer_texture = NULL;

int window_width = 800;
int window_height = 600;

bool initialize_window(void) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "Failed to initialize SDL: %s", SDL_GetError());
        return false;
    }
    printf("SDL initialized successfully!\n");

    const SDL_DisplayMode* display_mode = SDL_GetCurrentDisplayMode(1);
    window_width = display_mode->w;
    window_height = display_mode->h;

    window = SDL_CreateWindow(
            "Caesar",
            window_width,
            window_height,
            SDL_WINDOW_BORDERLESS
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
    color_buffer = (uint32_t*) malloc(sizeof(uint32_t) * window_width * window_height);

    color_buffer_texture = SDL_CreateTexture(
            renderer,
            SDL_PIXELFORMAT_ARGB8888,
            SDL_TEXTUREACCESS_STREAMING,
            window_width,
            window_height
        );
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

void render_color_buffer(void) {
    SDL_UpdateTexture(
            color_buffer_texture,
            NULL,
            color_buffer,
            (int)(window_width * sizeof(uint32_t))
    );
    SDL_RenderTexture(renderer, color_buffer_texture, NULL, NULL);
}

void draw_grid(void) {
    for (int y = 0; y < window_height; y++) {
        for (int x =0; x < window_width; x++) {
            if (x % 10 == 0 || y % 10 == 0) {
                color_buffer[(window_width * y) + x] = 0xFF444444;
            }
        }
    }
}

void draw_rect(int x, int y, int width, int height, uint32_t color) {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            int x_curr = x + i;
            int y_curr = y + j;
            color_buffer[(window_width * y_curr) + x_curr] = color;
        }
    }
}

void clear_color_buffer(uint32_t color) {
    for (int y = 0; y < window_height; y++) {
        for (int x = 0; x < window_width; x++) {
            color_buffer[(window_width * y) + x] = color;
        }
    }
}

void render(void) {

    clear_color_buffer(0xFFFFFF00);
    
    draw_grid();

    draw_rect(400, 300, 300, 100, 0xFFFF00FF);
    render_color_buffer();

    SDL_RenderPresent(renderer);
}

void destroy_window(void) {
    free(color_buffer);
    SDL_DestroyRenderer(renderer);
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
