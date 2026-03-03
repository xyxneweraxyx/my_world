#include "./buttonfml.h"

size_t mouse_moved(setfml_t *setfml, void *userdata)
{
    printf("%d %d\n", setfml->event.mouseMove.x, setfml->event.mouseMove.y);
    return (size_t)SETFML_SUCC;
}

size_t mouse_moved_2(setfml_t *setfml, void *userdata)
{
    printf("this is after the mouse movement!\n");
    return (size_t)SETFML_SUCC;
}

size_t mouse_click(setfml_t *setfml, void *userdata)
{
    printf("mouse click!\n");
    return (size_t)SETFML_SUCC;
}

size_t draw_sprite(setfml_t *setfml, void *userdata)
{
    sprite_t *sprite = setfml_spritefromname(setfml, "test", false);
    sfSprite_setPosition(sprite->sprite, (sfVector2f){100, 100});
    sfRenderWindow_drawSprite(setfml->window, sprite->sprite, NULL);
    return (size_t)SETFML_SUCC;
}

int main(void)
{
    setfml_t *setfml = setfml_ini(NULL);
    buttonfml_t *buttonfml = buttonfml_ini(setfml);

    setfml_fillparams(setfml);

    button_t *button = buttonfml_buttoncreate(buttonfml,
        &(btn_text_t){"./assets/images/thug.png", "./assets/images/thug2.png", ""},
        &(btn_clbck_t){NULL, NULL, NULL},
        "my_button");

    setfml_windowcreate(setfml);
    setfml_windowstart(setfml);

    buttonfml_destroy(buttonfml);
    setfml_destroy(setfml);
}
