#include<stdio.h>
#include<stdint.h>
#include<stdbool.h>
#include<stdlib.h>
#include<SDL3/SDL.h>

// -------------------------------------------------------------------------------- 
// Global Variables
// -------------------------------------------------------------------------------- 
bool is_running = false;
SDL_Window* window = NULL;
SDL_Renderer* sdl_renderer = NULL;
uint32_t* color_buffer = NULL;
SDL_Texture* color_buffer_texture = NULL;
int window_width = 800;
int window_height = 600;

// -------------------------------------------------------------------------------- 
// Function Prototypes
// -------------------------------------------------------------------------------- 
bool initialize_window(void);
void setup(void);
void process_input(void);
void update(void);
void render(void);
void destroy_window(void);
void clear_color_buffer(uint32_t color);
void draw_grid(void);
void draw_rect(int x, int y, int width, int height, uint32_t color);

// -------------------------------------------------------------------------------- 
// Main Function
// -------------------------------------------------------------------------------- 
int main(void) {
    
    is_running = initialize_window();
    
    if (is_running) {
        setup();
    }

    while (is_running) {
        process_input();
        update();
        render();
    }

    destroy_window();
    return 0;
}

// -------------------------------------------------------------------------------- 
// Setup Functions
// -------------------------------------------------------------------------------- 
bool initialize_window(void) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "Failed to initialize SDL: %s\n", SDL_GetError());
        return false;
    }
    printf("SDL initialized successfully!\n");

    // Get a primary display mode to set the fullscreen desktop resolution
    const SDL_DisplayMode* display_mode = SDL_GetCurrentDisplayMode(1);
    if (!display_mode) {
        fprintf(stderr, "Could not get display mode: %s. Using fallback values.\n", SDL_GetError());
    } else {
        window_width = display_mode->w;
        window_height = display_mode->h;
    }

    window = SDL_CreateWindow(
            "Caesar 3D Renderer",
            window_width,
            window_height,
            SDL_WINDOW_RESIZABLE
    );
    if (!window) {
        fprintf(stderr, "Could not create window: %s\n", SDL_GetError());
        SDL_Quit();
        return false;
    }
    // Set to truly fullscreen borderless after creation
    if (!SDL_SetWindowFullscreen(window, true)) {
        printf("Warning: Could not set window to fullscreen: %s\n", SDL_GetError());
    }
    printf("Window created successfully!\n");

    sdl_renderer = SDL_CreateRenderer(window, NULL);
    if (!sdl_renderer) {
        fprintf(stderr, "Error creating SDL renderer: %s\n", SDL_GetError());
        return false;
    }
    printf("SDL Renderer  created successfully!\n");

    return true;

}

void setup(void) {
    // Allocate the total amount of bytes in memory to hold the color buffer
    color_buffer = (uint32_t*) malloc(sizeof(uint32_t) * window_width * window_height);

    if (!color_buffer) {
        fprintf(stderr, "Error allocating color buffer!\n");
        is_running = false;
        return;
    }

    // Create an SDL texture that is used to display the color buffer
    color_buffer_texture = SDL_CreateTexture(
            sdl_renderer,
            SDL_PIXELFORMAT_ARGB8888,
            SDL_TEXTUREACCESS_STREAMING,
            window_width,
            window_height
        );
    if (!color_buffer_texture) {
        fprintf(stderr, "Error creating SDL texture: %s\n", SDL_GetError());
        is_running = false;
    }
}
 
void destroy_window(void) {
    printf("Shutting down...\n");
    free(color_buffer);
    SDL_DestroyTexture(color_buffer_texture);
    SDL_DestroyRenderer(sdl_renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    printf("SDL shut down successfully. All good!\n");
}

// --------------------------------------------------------------------------------
// Input and Update
// --------------------------------------------------------------------------------
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

// --------------------------------------------------------------------------------
// Rendering Functions
// --------------------------------------------------------------------------------

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

void render_color_buffer(void) {
    SDL_UpdateTexture(
            color_buffer_texture,
            NULL,
            color_buffer,
            (int)(window_width * sizeof(uint32_t))
    );
    SDL_RenderTexture(sdl_renderer, color_buffer_texture, NULL, NULL);
}


void clear_color_buffer(uint32_t color) {
    for (int y = 0; y < window_height; y++) {
        for (int x = 0; x < window_width; x++) {
            color_buffer[(window_width * y) + x] = color;
        }
    }
}

void render(void) {

    // 1. Clear the buffer
    clear_color_buffer(0xFFFFFF00);
    
    // 2. Draw stuff
    draw_grid();
    draw_rect(400, 300, 300, 100, 0xFFFF00FF);
    draw_rect(window_width / 2 - 50, window_height / 2 - 50, 100, 100, 0xFFFF00FF);

    // 3. Render the buffer to the screen
    render_color_buffer();

    // 4. Present the back buffer
    SDL_RenderPresent(sdl_renderer);
}


