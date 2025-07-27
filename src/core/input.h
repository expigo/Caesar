#ifndef INPUT_H
#define INPUT_H

#include <stdbool.h>

// --------------------------------------------------------------------------------
// Global Input State
// --------------------------------------------------------------------------------
extern bool is_running;

// --------------------------------------------------------------------------------
// Input Processing
// --------------------------------------------------------------------------------

/**
 * Process all pending SDL events
 * Updates is_running flag based on quit events or ESC key
 */
void process_input(void);

#endif
