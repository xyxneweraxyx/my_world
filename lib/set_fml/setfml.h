/*
** EPITECH PROJECT, 2025
** setfml
** File description:
** Tired of initializing csfml? Up your workflow with this simple wrapper.
*/

#ifndef SET_FML
    #define SET_FML

    // Includes
    #include <SFML/Audio.h>
    #include <SFML/Config.h>
    #include <SFML/Graphics.h>
    #include <SFML/System.h>
    #include <SFML/Window.h>
    #include "./../c_alloc/c_alloc.h" // MUST INCLUDE
    #include "./../linkedlist/linkedlist.h" // MUST INCLUDE

    // Return codes
    #define SETFML_SUCC 0
    #define SETFML_FAIL 84

    // Buffer lengths
    #define BUFF_FUNC_NAME 32
    #define BUFF_SPRITE_NAME 32
    #define BUFF_TEXT_NAME 32
    #define BUFF_TEXT_PATH 128

// Typedefs
typedef struct win_params {
    sfVideoMode *mode;
    const char *title;
    sfContextSettings *settings;
    sfUint32 style;
} win_params_t;

typedef struct params {
    win_params_t *win_params;
    size_t fps;
    uint16_t min_scr_res[2];
    uint16_t max_scr_res[2];
} params_t;

typedef struct state {
    loop_t current_loop;
    uint32_t frame;
} state_t;

typedef struct function {
    char name[BUFF_FUNC_NAME];
    size_t (*function)(setfml_t *setfml);
    struct function *next;
    size_t return_code;
    bool paused;
} function_t;

typedef struct sprite {
    char name[BUFF_SPRITE_NAME];
    sfSprite *sprite;
    texture_t *texture;
} sprite_t;

typedef struct texture {
    char name[BUFF_TEXT_NAME];
    char path[BUFF_TEXT_PATH];
    sfTexture *texture;
} texture_t;

typedef struct setfml {
    params_t *params;
    state_t *state;
    sfRenderWindow *window;
    sprite_t **sprites;
    texture_t **textures;
    function_t **functions[4];
    void *userdata; // par exemple pour moi ça serait l'addresse de mon main
} setfml_t;

// Enums

typedef enum loop {
    EVENT,
    DATA,
    RENDER,
    DRAW
} loop_t;

// Functions
setfml_t *setfml_ini(void *userdata);
size_t setfml_destroy(setfml_t *setfml);

size_t setfml_spriteAdd(char name[BUFF_SPRITE_NAME], texture_t *texture);
size_t setfml_spriteDel(char name[BUFF_SPRITE_NAME]);
size_t setfml_textureAdd(char name[BUFF_TEXT_NAME], char path[BUFF_TEXT_PATH]);
size_t setfml_textureDel(char name[BUFF_TEXT_NAME]);

size_t setfml_add(loop_t event, size_t (*callback)(setfml_t *setfml));
size_t setfml_del(loop_t event, size_t (*callback)(setfml_t *setfml));
size_t setfml_pause(loop_t event, size_t (*callback)(setfml_t *setfml));
size_t setfml_resume(loop_t event, size_t (*callback)(setfml_t *setfml));

#endif