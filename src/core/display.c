#include "core/display.h"
#include "core/constants.h"
#include <SDL3/SDL.h>
#include <stdio.h>
#include <stdlib.h>

// --------------------------------------------------------------------------------
// Private Display State
// --------------------------------------------------------------------------------
static SDL_Window* window = NULL;
static SDL_Renderer* sdl_renderer = NULL;
static SDL_Texture* display_texture = NULL;
static int window_width = DEFAULT_WINDOW_WIDTH;
static int window_height = DEFAULT_WINDOW_HEIGHT;
static bool is_initialized = false;

// --------------------------------------------------------------------------------
// Window Lifecycle Implementation
// --------------------------------------------------------------------------------
bool initialize_window(void) {
    if (is_initialized) {
        printf("Warning: Display already initialized\n");
        return true;
    }

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "Failed to initialize SDL: %s\n", SDL_GetError());
        return false;
    }
    printf("SDL initialized successfully!\n");

    // Get primary display mode to set the fullscreen desktop  resolution
    const SDL_DisplayMode* display_mode = SDL_GetCurrentDisplayMode(1);
    if (!display_mode) {
        fprintf(stderr, "Could not get display mode: %s. Using fallback values.\n", SDL_GetError());
    } else {
        window_width = display_mode->w;
        window_height = display_mode->h;
        printf("Display resolution: %dx%d\n", window_width, window_height);
    }

    // Create resizable window
    window = SDL_CreateWindow(
        WINDOW_TITLE,
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

    // Create hardware-accelerated renderer
    sdl_renderer = SDL_CreateRenderer(window, NULL);
    if (!sdl_renderer) {
        fprintf(stderr, "Error creating SDL renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }
    printf("SDL Renderer created successfully!\n");

    is_initialized = true;
    return true;
}

void setup_display(void) {
    if (!is_initialized) {
        fprintf(stderr, "Error: Must call initialize_window() first\n");
        return;
    }

    // Create streaming texture for rendering color buffer data
    display_texture = SDL_CreateTexture(
        sdl_renderer,
        SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING,
        window_width,
        window_height
    );
    if (!display_texture) {
        fprintf(stderr, "Error creating display texture: %s\n", SDL_GetError());
        return;
    }
    printf("Display texture created successfully!\n");
}

void destroy_window(void) {
    printf("Shutting down display system...\n");
    
    if (display_texture) {
        SDL_DestroyTexture(display_texture);
        display_texture = NULL;
    }
    
    if (sdl_renderer) {
        SDL_DestroyRenderer(sdl_renderer);
        sdl_renderer = NULL;
    }
    
    if (window) {
        SDL_DestroyWindow(window);
        window = NULL;
    }
    
    SDL_Quit();
    is_initialized = false;
    printf("Display system shut down successfully!\n");
}

// --------------------------------------------------------------------------------
// Display Properties Implementation
// --------------------------------------------------------------------------------
int get_window_width(void) {
    return window_width;
}

int get_window_height(void) {
    return window_height;
}

bool is_display_ready(void) {
    return is_initialized && display_texture != NULL;
}

// --------------------------------------------------------------------------------
// Rendering Interface Implementation
// --------------------------------------------------------------------------------
void render_color_buffer_data(uint32_t* color_data, int width, int height) {
    if (!display_texture || !sdl_renderer || !color_data) {
        fprintf(stderr, "Warning: Invalid render parameters\n");
        return;
    }

    // Verify dimensions match
    if (width != window_width || height != window_height) {
        fprintf(stderr, "Warning: Color buffer dimensions (%dx%d) don't match window (%dx%d)\n",
                width, height, window_width, window_height);
        return;
    }

    // Upload pixel data to GPU texture
    SDL_UpdateTexture(
        display_texture,
        NULL,
        color_data,
        (int)(width * sizeof(uint32_t))
    );

    // Render texture to screen
    SDL_RenderTexture(sdl_renderer, display_texture, NULL, NULL);
}

void present_frame(void) {
    if (!sdl_renderer) {
        fprintf(stderr, "Warning: No renderer available for frame presentation\n");
        return;
    }
    
    SDL_RenderPresent(sdl_renderer);
}
