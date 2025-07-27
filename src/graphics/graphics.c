#include "graphics/graphics.h"
#include "core/display.h"
#include <stdio.h>
#include <stdlib.h>

// --------------------------------------------------------------------------------
// Private Graphics State
// --------------------------------------------------------------------------------
static uint32_t* color_buffer = NULL;
static int buffer_width = 0;
static int buffer_height = 0;
static bool is_initialized = false;

// --------------------------------------------------------------------------------
// Graphics System Lifecycle Implementation
// --------------------------------------------------------------------------------
bool initialize_graphics(void) {
    if (is_initialized) {
        printf("Warning: Graphics system already initialized\n");
        return true;
    }

    // Graphics system depends on display system being ready
    if (!is_display_ready()) {
        fprintf(stderr, "Error: Display system must be initialized first\n");
        return false;
    }

    // Get buffer dimensions from display system
    buffer_width = get_window_width();
    buffer_height = get_window_height();

    // Allocate the color buffer
    size_t buffer_size = sizeof(uint32_t) * buffer_width * buffer_height;
    color_buffer = (uint32_t*)malloc(buffer_size);

    if (!color_buffer) {
        fprintf(stderr, "Error allocating color buffer of size %zu bytes!\n", buffer_size);
        return false;
    }

    printf("Graphics system initialized: %dx%d color buffer (%zu KB)\n", 
           buffer_width, buffer_height, buffer_size / 1024);

    is_initialized = true;
    return true;
}

void destroy_graphics(void) {
    if (!is_initialized) {
        return;
    }

    printf("Shutting down graphics system...\n");
    
    if (color_buffer) {
        free(color_buffer);
        color_buffer = NULL;
    }
    
    buffer_width = 0;
    buffer_height = 0;
    is_initialized = false;
    
    printf("Graphics system shut down successfully!\n");
}

bool is_graphics_ready(void) {
    return is_initialized && color_buffer != NULL;
}

// --------------------------------------------------------------------------------
// Color Buffer Management Implementation
// --------------------------------------------------------------------------------
uint32_t* get_color_buffer(void) {
    return color_buffer;  // Can return NULL if not initialized
}

void get_color_buffer_dimensions(int* width, int* height) {
    if (width) *width = buffer_width;
    if (height) *height = buffer_height;
}

void clear_color_buffer(uint32_t color) {
    if (!color_buffer) {
        fprintf(stderr, "Warning: Attempted to clear uninitialized color buffer\n");
        return;
    }
    
    int total_pixels = buffer_width * buffer_height;
    for (int i = 0; i < total_pixels; i++) {
        color_buffer[i] = color;
    }
}

void present_color_buffer(void) {
    if (!is_graphics_ready()) {
        fprintf(stderr, "Warning: Graphics system not ready for presentation\n");
        return;
    }

    // Send color buffer to display system for rendering
    render_color_buffer_data(color_buffer, buffer_width, buffer_height);
}
