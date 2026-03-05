/*
** EPITECH PROJECT, 2025
** my_world
** File description:
** Camera movement callbacks.
*/

#include "./../../include/myworld.h"

static size_t move_forward(setfml_t *setfml, void *userdata)
{
    main_t *main = (main_t *)setfml->userdata;

    if (setfml->event.key.code != sfKeyZ)
        return (size_t)EXIT_SUCC;
    main->render.cam_x += sinf(main->render.yaw) * CAM_SPEED;
    main->render.cam_z += cosf(main->render.yaw) * CAM_SPEED;
    return (size_t)EXIT_SUCC;
}

static size_t move_backward(setfml_t *setfml, void *userdata)
{
    main_t *main = (main_t *)setfml->userdata;

    if (setfml->event.key.code != sfKeyS)
        return (size_t)EXIT_SUCC;
    main->render.cam_x -= sinf(main->render.yaw) * CAM_SPEED;
    main->render.cam_z -= cosf(main->render.yaw) * CAM_SPEED;
    return (size_t)EXIT_SUCC;
}

static size_t move_left(setfml_t *setfml, void *userdata)
{
    main_t *main = (main_t *)setfml->userdata;

    if (setfml->event.key.code != sfKeyQ)
        return (size_t)EXIT_SUCC;
    main->render.cam_x -= cosf(main->render.yaw) * CAM_SPEED;
    main->render.cam_z += sinf(main->render.yaw) * CAM_SPEED;
    return (size_t)EXIT_SUCC;
}

static size_t move_right(setfml_t *setfml, void *userdata)
{
    main_t *main = (main_t *)setfml->userdata;

    if (setfml->event.key.code != sfKeyD)
        return (size_t)EXIT_SUCC;
    main->render.cam_x += cosf(main->render.yaw) * CAM_SPEED;
    main->render.cam_z -= sinf(main->render.yaw) * CAM_SPEED;
    return (size_t)EXIT_SUCC;
}

static size_t move_up(setfml_t *setfml, void *userdata)
{
    main_t *main = (main_t *)setfml->userdata;

    if (setfml->event.key.code != sfKeyA)
        return (size_t)EXIT_SUCC;
    main->render.cam_y += CAM_SPEED;
    return (size_t)EXIT_SUCC;
}

static size_t move_down(setfml_t *setfml, void *userdata)
{
    main_t *main = (main_t *)setfml->userdata;

    if (setfml->event.key.code != sfKeyE)
        return (size_t)EXIT_SUCC;
    main->render.cam_y -= CAM_SPEED;
    return (size_t)EXIT_SUCC;
}

size_t ini_camera_callbacks(main_t *main, void *userdata)
{
    setfml_add(main->setfml, &(setfml_func_comp_t){NULL, &move_forward},
        "move_forward", sfEvtKeyPressed);
    setfml_add(main->setfml, &(setfml_func_comp_t){NULL, &move_backward},
        "move_backward", sfEvtKeyPressed);
    setfml_add(main->setfml, &(setfml_func_comp_t){NULL, &move_left},
        "move_left", sfEvtKeyPressed);
    setfml_add(main->setfml, &(setfml_func_comp_t){NULL, &move_right},
        "move_right", sfEvtKeyPressed);
    setfml_add(main->setfml, &(setfml_func_comp_t){NULL, &move_up},
        "move_up", sfEvtKeyPressed);
    setfml_add(main->setfml, &(setfml_func_comp_t){NULL, &move_down},
        "move_down", sfEvtKeyPressed);
    return (size_t)EXIT_SUCC;
}