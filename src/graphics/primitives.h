#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include <stdint.h>

// --------------------------------------------------------------------------------
// Basic Drawing Primitives
// --------------------------------------------------------------------------------

/**
 * Draw a single pixel at the specified coordinates
 * @param x X coordinate
 * @param y Y coordinate  
 * @param color ARGB8888 color value
 */
void draw_pixel(int x, int y, uint32_t color);

/**
 * Draw a filled rectangle
 * @param x Top-left X coordinate
 * @param y Top-left Y coordinate
 * @param width Rectangle width in pixels
 * @param height Rectangle height in pixels
 * @param color ARGB8888 color value
 */
void draw_rect(int x, int y, int width, int height, uint32_t color);

/**
 * Draw a debug grid across the entire screen
 * Useful for coordinate system visualization
 */
void draw_grid(void);

#endif
