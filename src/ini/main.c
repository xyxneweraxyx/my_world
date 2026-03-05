/*
** EPITECH PROJECT, 2025
** my_world
** File description:
** Initializing csfml.
*/

#include "./../../include/myworld.h"

static void ini_textures(main_t *main)
{
    setfml_textureadd(main->setfml, "back_home", AST_BACKHOME);
    setfml_textureadd(main->setfml, "background", AST_BACKGROUND);
    setfml_textureadd(main->setfml, "create_map", AST_CREATEMAP);
    setfml_textureadd(main->setfml, "exit", AST_EXIT);
    setfml_textureadd(main->setfml, "setting", AST_SETTING);
    setfml_textureadd(main->setfml, "editorbackground", AST_EDITORBACKGROUND);
    setfml_textureadd(main->setfml, "grasstexture", AST_GRASSTEXTURE);
    setfml_textureadd(main->setfml, "rocktexture", AST_ROCKTEXTURE);
}

static size_t ini_sprites(main_t *main)
{
    texture_t *txt = setfml_texturefromname(main->setfml, "background", false);
    sprite_t *sprite = NULL;

    if (!txt)
        return (size_t)EXIT_FAIL;
    setfml_spriteadd(main->setfml, "background", txt);
    sprite = setfml_spritefromname(main->setfml, "background", false);
    if (!sprite)
        return (size_t)EXIT_FAIL;
    sfSprite_setScale(sprite->sprite, (sfVector2f){1.25, 1.05});
    txt = setfml_texturefromname(main->setfml, "editorbackground", false);
    setfml_spriteadd(main->setfml, "editorbackground", txt);
    return (size_t)EXIT_SUCC;
}

static void ini_values(main_t *main)
{
        main->state = MYWORLD_MENU;
    main->render.zoom = 50;
    main->render.square_amount_x = 32;
    main->render.square_amount_y = 32;
    main->render.cam_x = (main->render.square_amount_x / 2.0f) * main->render.zoom;
    main->render.cam_y = 700;
    main->render.cam_z = -500;
    main->render.yaw = 0;
    main->render.pitch = 0.6f;
    main->render.fov = 700;
    main->render.height = c_alloc(sizeof(float *),
        main->render.square_amount_y, main->alloc);
    for (size_t i = 0; i < main->render.square_amount_y; i++)
        main->render.height[i] = c_alloc(sizeof(float),
            main->render.square_amount_x, main->alloc);
}

size_t ini_csfml(main_t *main)
{
    ini_values(main);
    setfml_windowcreate(main->setfml);
    ini_textures(main);
    if (ini_sprites(main) == (size_t)EXIT_FAIL)
        return (size_t)EXIT_FAIL;
    if (ini_buttons(main) == (size_t)EXIT_FAIL)
        return (size_t)EXIT_FAIL;
    return (size_t)EXIT_SUCC;
}