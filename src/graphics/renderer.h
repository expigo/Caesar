#ifndef RENDERER_H
#define RENDERER_H

// --------------------------------------------------------------------------------
// High-Level Rendering Interface
// --------------------------------------------------------------------------------

/**
 * Initialize the entire rendering system
 * Sets up window, display, and graphics subsystems
 * @return true if initialization succeeded, false otherwise
 */
bool initialize_renderer(void);

/**
 * Perform a complete frame render
 * Clears buffers, draws all objects, and presents to screen
 */
void render_frame(void);

/**
 * Clean up the entire rendering system
 */
void shutdown_renderer(void);

#endif
