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

    // Return codes
    #define EXIT_SUCC 0
    #define EXIT_FAIL 84

// Typedefs
typedef struct params {
    sfVideoMode *mode;
    const char *title;
    sfContextSettings *settings;
    sfUint32 style;
} params_t;

typedef struct csfml {
    sfRenderWindow *window;
    sfEvent event;
} csfml_t;

// Functions
size_t setfml_ini();
size_t setfml_destroy();

size_t setfml_spriteAdd();
size_t setfml_spriteDel();
size_t setfml_textureAdd();
size_t setfml_textureDel();

size_t setfml_eventAdd();
size_t setfml_eventDel();
size_t setfml_eventPause();
size_t setfml_eventResume();

size_t setfml_dataAdd();
size_t setfml_dataDel();
size_t setfml_dataPause();
size_t setfml_dataResume();

size_t setfml_renderAdd();
size_t setfml_renderDel();
size_t setfml_renderPause();
size_t setfml_renderResume();

size_t setfml_drawAdd();
size_t setfml_drawDel();
size_t setfml_drawPause();
size_t setfml_drawResume();

#endif