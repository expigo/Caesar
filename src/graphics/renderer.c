#include <stdbool.h>
#include "graphics/renderer.h"
#include "graphics/graphics.h"
#include "graphics/primitives.h"
#include "core/display.h"
#include "core/constants.h"

// --------------------------------------------------------------------------------
// High-Level Rendering Implementation
// --------------------------------------------------------------------------------

bool initialize_renderer(void) {
    // Step 1: Initialize display system (window, SDL)
    if (!initialize_window()) {
        return false;
    }
    
    setup_display();
    
    if (!is_display_ready()) {
        return false;
    }
    
    // Step 2: Initialize graphics system (color buffer)
    if (!initialize_graphics()) {
        destroy_window();
        return false;
    }
    
    return true;
}

void render_frame(void) {
    if (!is_graphics_ready()) {
        return;
    }
    
    // 1. Clear the graphics buffer
    clear_color_buffer(COLOR_BACKGROUND);
    
    // 2. Draw all primitives/objects to graphics buffer
    draw_grid();
    
    // Demo rectangles
    int buffer_width, buffer_height;
    get_color_buffer_dimensions(&buffer_width, &buffer_height);
    
    draw_rect(400, 300, 300, 100, COLOR_PRIMITIVE);
    draw_rect(buffer_width / 2 - 50, buffer_height / 2 - 50, 100, 100, COLOR_PRIMITIVE);
    
    // 3. Present graphics buffer to display system
    present_color_buffer();
    present_frame();
}

void shutdown_renderer(void) {
    destroy_graphics();
    destroy_window();
}
