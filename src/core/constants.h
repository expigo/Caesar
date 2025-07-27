#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <stdint.h>

// --------------------------------------------------------------------------------
// Window Configuration
// --------------------------------------------------------------------------------
#define DEFAULT_WINDOW_WIDTH  800
#define DEFAULT_WINDOW_HEIGHT 600
#define WINDOW_TITLE "Caesar 3D Renderer"

// --------------------------------------------------------------------------------
// Color Definitions (ARGB8888 format)
// --------------------------------------------------------------------------------
#define COLOR_BLACK      0xFF000000
#define COLOR_WHITE      0xFFFFFFFF
#define COLOR_RED        0xFFFF0000
#define COLOR_GREEN      0xFF00FF00
#define COLOR_BLUE       0xFF0000FF
#define COLOR_CYAN       0xFF00FFFF
#define COLOR_MAGENTA    0xFFFF00FF
#define COLOR_YELLOW     0xFFFFFF00
#define COLOR_ORANGE     0xFFFF8000
#define COLOR_PURPLE     0xFF8000FF
#define COLOR_GRAY       0xFF808080
#define COLOR_DARK_GRAY  0xFF444444
#define COLOR_LIGHT_GRAY 0xFFCCCCCC

// Semantic color names
#define COLOR_BACKGROUND COLOR_YELLOW
#define COLOR_GRID       COLOR_DARK_GRAY
#define COLOR_PRIMITIVE  COLOR_MAGENTA

// --------------------------------------------------------------------------------
// Rendering Configuration
// --------------------------------------------------------------------------------
#define GRID_SPACING 10

#endif
