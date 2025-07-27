#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <stdint.h>
#include <stdbool.h>

// --------------------------------------------------------------------------------
// Graphics System Lifecycle
// --------------------------------------------------------------------------------

/**
 * Initialize the graphics system
 * Must be called after display system is initialized
 * @return true if initialization succeeded, false otherwise
 */
bool initialize_graphics(void);

/**
 * Clean up all graphics resources
 */
void destroy_graphics(void);

/**
 * Check if graphics system is ready for rendering
 * @return true if ready for graphics operations
 */
bool is_graphics_ready(void);

// --------------------------------------------------------------------------------
// Color Buffer Management
// --------------------------------------------------------------------------------

/**
 * Get direct access to the color buffer for performance-critical operations
 * @return pointer to color buffer, or NULL if not initialized
 * @note Use with caution - prefer graphics drawing functions when possible
 */
uint32_t* get_color_buffer(void);

/**
 * Get color buffer dimensions
 * @param width pointer to store buffer width (can be NULL)
 * @param height pointer to store buffer height (can be NULL)
 */
void get_color_buffer_dimensions(int* width, int* height);

/**
 * Clear the entire color buffer to a specific color
 * @param color ARGB8888 color value
 */
void clear_color_buffer(uint32_t color);

/**
 * Copy the color buffer to the display system for presentation
 */
void present_color_buffer(void);

#endif
