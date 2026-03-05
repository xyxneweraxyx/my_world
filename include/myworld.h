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
    #include "./../lib/setfml/setfml.h"
    #include "./../lib/buttonfml/buttonfml.h"

    // Return codes
    #define EXIT_SUCC 0
    #define EXIT_FAIL 84

    // Hotkeys

    // Image paths
    #define AST_BACKHOME "./assets/images/back_home.png"
    #define AST_BACKGROUND "./assets/images/background.png"
    #define AST_CREATEMAP "./assets/images/create_map.png"
    #define AST_EXIT "./assets/images/exit.png"
    #define AST_SETTING "./assets/images/setting.png"

// Typedefs

typedef struct csfml {
    sfRenderWindow *window;
    sfVertexArray *array;
    sfEvent event;
} csfml_t;

typedef struct main {
    c_alloc_t *alloc;
    setfml_t *setfml;
    buttonfml_t *buttonfml;
    size_t **height;
    csfml_t csfml;
} main_t;

// Functions

size_t ini_csfml(main_t *main);
size_t ini_buttons(main_t *main);
size_t ini_callbacks(main_t *main);

#endif
