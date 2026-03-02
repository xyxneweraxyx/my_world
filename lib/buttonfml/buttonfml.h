/*
** EPITECH PROJECT, 2025
** buttonfml
** File description:
** Wrapper on the setfml library to create simple buttons easily.
*/

#ifndef BUTTONFML
    #define BUTTONFML

    // Includes
    #include "./../setfml/setfml.h"

    // Return codes
    #define BUTTONFML_SUCC 0
    #define BUTTONFML_FAIL -1


// Enums

typedef enum button_state {
    IDLE,
    HOVERED,
    CLICKED
} button_state_t;

// Structures

typedef struct button_textures {
    texture_t *idle; // The texture used when no interactions are performed.
    texture_t *hover; // The texture used when the button is hovered over.
    texture_t *click; // The texture used on click.
} button_textures_t;

typedef struct button_callbacks {
    size_t (*hover)(setfml_t *setfml, void *userdata); // Triggered on hover.
    size_t (*click)(setfml_t *setfml, void *userdata); // Triggered on click.
    size_t (*frame)(setfml_t *setfml, void *userdata); // Triggered every frame
} button_callbacks_t;

typedef struct button_stats {
    size_t clicked; // Amount of times the button was clicked.
} button_stats_t;

typedef struct button {
    setfml_t *setfml; // The setfml environment the button is linked to.
    sprite_t *button; // The sprite of the button.
    button_textures_t textures; // The textures used for the button.
    button_callbacks_t callbacks; // The functions to be executed on events.
    button_stats_t stats; // Stats of the button at runtime.
    button_state_t state; // The current state of the button.
    bool is_visible; // Is this button drawn?
    bool is_clickable; // Can this button be clicked?
} button_t;

typedef struct buttonfml {

} buttonfml_t;

// Functions

/// Initializing functions

/*
Initializes a new buttonfml environment given a setfml environment.
Returns the buttonfml environment on success, or NULL on fail.
*/
buttonfml_t *buttonfml_ini(setfml_t *setfml);

/*
Destroys a buttonfml environment.
Returns BUTTONFML_SUCC on success, or BUTTONFML_FAIL on failure.
*/
size_t buttonfml_destroy(buttonfml_t *buttonfml);

// Button functions

/*
Creates a new button given a buttonfml environment, textures, callbacks, and a pos
Returns the button on success, or NULL on fail.
*/
button_t *buttonfml_buttoncreate(buttonfml_t *buttonfml, button_textures_t *textures,
    button_callbacks_t *callbacks, sfVector2f position);

/*
Destroys a button and removes its callbacks from its setfml environment.
Setting "destroy_data" to true will also destroy the sprites and textures.
Returns BUTTONFML_SUCC on success, or BUTTONFML_FAIL on failure.
*/
size_t *buttonfml_buttondestroy(button_t *button, bool destroy_data);

#endif