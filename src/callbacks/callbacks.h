/*
** EPITECH PROJECT, 2025
** my_world
** File description:
** Callbacks.
*/

#ifndef CALLBACKS_H
    #define CALLBACKS_H

size_t click_create_map(setfml_t *setfml, void *userdata);
size_t click_exit(setfml_t *setfml, void *userdata);
size_t click_setting(setfml_t *setfml, void *userdata);
size_t menu_frame(setfml_t *setfml, void *userdata);
size_t edit_click(setfml_t *setfml, void *userdata);
size_t click_raise(setfml_t *setfml, void *userdata);
size_t click_lower(setfml_t *setfml, void *userdata);
size_t click_reset(setfml_t *setfml, void *userdata);
size_t editor_frame(setfml_t *setfml, void *userdata);

#endif
