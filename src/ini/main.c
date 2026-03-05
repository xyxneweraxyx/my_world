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
}

static size_t ini_sprites(main_t *main)
{
    texture_t *txt = setfml_texturefromname(main->setfml, "background", false);

    if (!txt)
        return (size_t)EXIT_FAIL;
    setfml_spriteadd(main->setfml, "background", txt);
    return (size_t)EXIT_SUCC;
}

size_t ini_csfml(main_t *main)
{
    setfml_windowcreate(main->setfml);
    ini_textures(main);
    if (ini_sprites(main) == (size_t)EXIT_FAIL)
        return (size_t)EXIT_FAIL;
    if (ini_buttons(main) == (size_t)EXIT_FAIL)
        return (size_t)EXIT_FAIL;
    return (size_t)EXIT_SUCC;
}