// core/input.c
#include "core/input.h"
#include <SDL3/SDL.h>

// --------------------------------------------------------------------------------
// Global Variables
// --------------------------------------------------------------------------------
bool is_running = false;

// --------------------------------------------------------------------------------
// Input Processing Implementation
// --------------------------------------------------------------------------------
void process_input(void) {
    SDL_Event event;
    
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_EVENT_QUIT:
                is_running = false;
                break;
                
            case SDL_EVENT_KEY_DOWN:
                if (event.key.key == SDLK_ESCAPE) {
                    is_running = false;
                }
                break;
        }
    }
}
