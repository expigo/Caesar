#include <stdio.h>
#include "core/input.h"
#include "graphics/renderer.h"

// TODO
void update(void);

// --------------------------------------------------------------------------------
// Main Function
// --------------------------------------------------------------------------------
int main(void) {
    printf("============ Caesar 3D Renderer ===========");
    printf("===========================================\n");
    
    // Initialize the rendering system (display + graphics)
    is_running = initialize_renderer();
    
    if (!is_running) {
        printf("Failed to initialize renderer. Exiting.\n");
        return 1;
    }
    
    printf("Renderer initialized successfully. Starting main loop...\n");

    // Main game loop
    while (is_running) {
        process_input();
        update();
        render_frame();
    }

    // Clean shutdown
    printf("Shutting down...\n");
    shutdown_renderer();
    printf("Goodbye!\n");
    
    return 0;
}

// --------------------------------------------------------------------------------
// Update Function
// --------------------------------------------------------------------------------
void update(void) {
    // TODO: Future 3D transformations, physics, game logic
}
