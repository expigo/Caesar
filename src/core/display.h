#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdint.h>
#include <stdbool.h>

// --------------------------------------------------------------------------------
// Window Lifecycle
// --------------------------------------------------------------------------------

/**
 * Initialize SDL and create the main window with renderer
 * @return true if initialization succeeded, false otherwise
 */
bool initialize_window(void);

/**
 * Set up the display texture for rendering
 * Must be called after successful initialize_window()
 */
void setup_display(void);

/**
 * Clean up all SDL resources and shut down
 */
void destroy_window(void);

// --------------------------------------------------------------------------------
// Display Properties (Read-only access)
// --------------------------------------------------------------------------------

/**
 * Get current window width
 * @return window width in pixels
 */
int get_window_width(void);

/**
 * Get current window height  
 * @return window height in pixels
 */
int get_window_height(void);

/**
 * Check if display system is properly initialized
 * @return true if ready for rendering operations
 */
bool is_display_ready(void);

// --------------------------------------------------------------------------------
// Rendering Interface (for Graphics System)
// --------------------------------------------------------------------------------

/**
 * Render color buffer data to the screen
 * @param color_data pointer to ARGB8888 pixel data
 * @param width buffer width in pixels
 * @param height buffer height in pixels
 */
void render_color_buffer_data(uint32_t* color_data, int width, int height);

/**
 * Present the rendered frame to screen
 */
void present_frame(void);

#endif
