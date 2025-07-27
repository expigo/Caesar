// graphics/primitives.c - Updated for Graphics System
#include "graphics/primitives.h"
#include "graphics/graphics.h"
#include "core/constants.h"

// --------------------------------------------------------------------------------
// Basic Drawing Primitives Implementation
// --------------------------------------------------------------------------------

void draw_pixel(int x, int y, uint32_t color) {
    // Get current buffer dimensions
    int width, height;
    get_color_buffer_dimensions(&width, &height);
    
    // Bounds checking to prevent buffer overflow
    if (x < 0 || x >= width || y < 0 || y >= height) {
        return;
    }
    
    uint32_t* buffer = get_color_buffer();
    if (buffer) {
        buffer[(width * y) + x] = color;
    }
}

void draw_rect(int x, int y, int width, int height, uint32_t color) {
    int buffer_width, buffer_height;
    get_color_buffer_dimensions(&buffer_width, &buffer_height);
    
    // Bounds checking for the rectangle
    if (x >= buffer_width || y >= buffer_height || 
        x + width <= 0 || y + height <= 0) {
        return; // Rectangle is completely outside screen
    }
    
    // Clip rectangle to screen bounds
    int start_x = (x < 0) ? 0 : x;
    int start_y = (y < 0) ? 0 : y;
    int end_x = (x + width > buffer_width) ? buffer_width : x + width;
    int end_y = (y + height > buffer_height) ? buffer_height : y + height;
    
    uint32_t* buffer = get_color_buffer();
    if (!buffer) return;
    
    // Draw the clipped rectangle
    for (int curr_y = start_y; curr_y < end_y; curr_y++) {
        for (int curr_x = start_x; curr_x < end_x; curr_x++) {
            buffer[(buffer_width * curr_y) + curr_x] = color;
        }
    }
}

void draw_grid(void) {
    uint32_t* buffer = get_color_buffer();
    if (!buffer) return;
    
    int buffer_width, buffer_height;
    get_color_buffer_dimensions(&buffer_width, &buffer_height);
    
    // Draw vertical lines
    for (int x = 0; x < buffer_width; x += GRID_SPACING) {
        for (int y = 0; y < buffer_height; y++) {
            buffer[(buffer_width * y) + x] = COLOR_GRID;
        }
    }
    
    // Draw horizontal lines
    for (int y = 0; y < buffer_height; y += GRID_SPACING) {
        for (int x = 0; x < buffer_width; x++) {
            buffer[(buffer_width * y) + x] = COLOR_GRID;
        }
    }
}
