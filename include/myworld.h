/*
** EPITECH PROJECT, 2025
** my_world
** File description:
** Main header file.
*/

#ifndef MYWORLD
    #define MYWORLD

    // Includes
    #include <stdio.h>
    #include <stdbool.h>
    #include <stdarg.h>
    #include <stdint.h>
    #include <stdlib.h>
    #include <unistd.h>

    // Includes (CSFML)
    #include <SFML/Audio.h>
    #include <SFML/Config.h>
    #include <SFML/Graphics.h>
    #include <SFML/System.h>
    #include <SFML/Window.h>

    // Includes (Libs)
    #include "./../lib/c_alloc/c_alloc.h"
    #include "./../lib/linkedlist/linkedlist.h"
    #include "./../lib/set_fml/setfml.h"

    // Return codes
    #define EXIT_SUCC 0
    #define EXIT_FAIL 84

    // Hotkeys

// Typedefs

typedef struct csfml {
    sfRenderWindow *window;
    sfVertexArray *array;
    sfEvent event;
} csfml_t;

typedef struct main {
    csfml_t csfml;
    size_t **height;
} main_t;

// Functions

#endif
