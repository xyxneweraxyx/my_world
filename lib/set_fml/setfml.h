/*
** EPITECH PROJECT, 2025
** setfml
** File description:
** Tired of initializing csfml? Up your workflow with this simple wrapper.
*/

#ifndef SET_FML
    #define SET_FML

    // Includes
    #include <time.h>
    #include <SFML/Audio.h>
    #include <SFML/Config.h>
    #include <SFML/Graphics.h>
    #include <SFML/System.h>
    #include <SFML/Window.h>
    #include "./../c_alloc/c_alloc.h" // MUST INCLUDE
    #include "./../linkedlist/linkedlist.h" // MUST INCLUDE
    #include "./../str/str.h" // MUST INCLUDE

    // Return codes
    #define SETFML_SUCC 0
    #define SETFML_FAIL 84

    // Buffer lengths
    #define BUFF_FUNC_NAME 32
    #define BUFF_SPRITE_NAME 32
    #define BUFF_TEXT_NAME 32
    #define BUFF_TEXT_PATH 128

    // Time definitions
    #define SEC_TO_NANO 1000000000
    #define SEC_TO_MICRO 1000000
    #define SEC_TO_MILLI 1000
    #define MILLI_TO_MICRO 1000
    #define MILLI_TO_NANO 1000000
    #define MICRO_TO_NANO 1000

    // Hardcoded values
    #define C_ALLOC_BASE 512

// Enums

typedef enum loop {
    LOOP_EVENT,
    LOOP_DATA,
    LOOP_RENDER,
    LOOP_DRAW
} loop_t;

// Typedefs

typedef struct window_params {
    const char *title;
    sfContextSettings *settings;
    uint16_t min_scr_res[2];
    uint16_t max_scr_res[2];
    sfUint32 style;
    uint8_t fps;
} window_params_t;

typedef struct time_params {
    size_t event; // In nanoseconds
    size_t data; // In nanoseconds
    size_t render; // In nanoseconds
    size_t draw; // In nanoseconds
} time_params_t;

typedef struct time_elapsed {
    struct timespec event;
    struct timespec data;
    struct timespec render;
    struct timespec draw;
} time_elapsed_t;

typedef struct loop_exec {
    bool event;
    bool data;
    bool render;
    bool draw;
} loop_exec_t;

typedef struct params {
    window_params_t window;
    time_params_t time;
} params_t;

typedef struct state {
    uint32_t frame;
    time_elapsed_t time_elapsed;
    time_elapsed_t last_exec;
    loop_exec_t to_exec;
} state_t;

typedef struct texture {
    char name[BUFF_TEXT_NAME];
    char path[BUFF_TEXT_PATH];
    sfTexture *texture;
} texture_t;

typedef struct sprite {
    char name[BUFF_SPRITE_NAME];
    sfSprite *sprite;
    texture_t *texture;
} sprite_t;

typedef struct setfml {
    c_alloc_t *alloc;
    sfRenderWindow *window;
    linkedlist_t *sprites;
    linkedlist_t *textures;
    linkedlist_t *functions[4];
    void *userdata; // par exemple pour moi ça serait l'addresse de mon main
    params_t params;
    state_t state;
} setfml_t;

typedef struct function {
    char name[BUFF_FUNC_NAME];
    size_t (*function)(setfml_t *setfml);
    size_t return_code;
    bool paused;
} function_t;

// Functions
setfml_t *setfml_ini(void *userdata);
size_t setfml_destroy(setfml_t *setfml);
void setfml_fillparams(setfml_t *setfml);

size_t setfml_windowcreate(setfml_t *setfml);
size_t setfml_windowstart(setfml_t *setfml);
size_t setfml_windowclose(setfml_t *setfml);
size_t setfml_windowdelete(setfml_t *setfml);
void setfml_iteration(setfml_t *setfml);

size_t setfml_spriteadd(char name[BUFF_SPRITE_NAME], texture_t *texture);
size_t setfml_spritedel(char name[BUFF_SPRITE_NAME]);
size_t setfml_textureadd(char name[BUFF_TEXT_NAME], char path[BUFF_TEXT_PATH]);
size_t setfml_texturedel(char name[BUFF_TEXT_NAME]);

size_t setfml_add_event(setfml_t *setfml, size_t (*f_before)(setfml_t *setfml),
    char name[BUFF_FUNC_NAME], size_t (*callback)(setfml_t *setfml));
size_t setfml_add_data(setfml_t *setfml, size_t (*f_before)(setfml_t *setfml),
    char name[BUFF_FUNC_NAME], size_t (*callback)(setfml_t *setfml));
size_t setfml_add_render(setfml_t *setfml, size_t (*f_before)(setfml_t *setfml),
    char name[BUFF_FUNC_NAME], size_t (*callback)(setfml_t *setfml));
size_t setfml_add_draw(setfml_t *setfml, size_t (*f_before)(setfml_t *setfml),
    char name[BUFF_FUNC_NAME], size_t (*callback)(setfml_t *setfml));

size_t setfml_del(setfml_t *sketfml, char name[BUFF_FUNC_NAME]);
size_t setfml_pause(setfml_t *setfml, char name[BUFF_FUNC_NAME]);
size_t setfml_resume(setfml_t *setfml, char name[BUFF_FUNC_NAME]);

function_t *setfml_getFunctionByName(setfml_t *setfml,
    char name[BUFF_FUNC_NAME]);

#endif
