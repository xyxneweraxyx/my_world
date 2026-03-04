#include "./buttonfml.h"

size_t scale_down(setfml_t *setfml, void *userdata)
{
    buttonfml_t *buttonfml = (buttonfml_t *)userdata;
    button_t *button = buttonfml_buttonfromname(buttonfml, "my_button");

    sfSprite_setScale(button->button->sprite, (sfVector2f){0.3, 0.3});
    return (size_t)BUTTONFML_SUCC;
}

size_t scale_up(setfml_t *setfml, void *userdata)
{
    buttonfml_t *buttonfml = (buttonfml_t *)userdata;
    button_t *button = buttonfml_buttonfromname(buttonfml, "my_button");

    sfSprite_setScale(button->button->sprite, (sfVector2f){1, 1});
    return (size_t)BUTTONFML_SUCC;
}

size_t hover(setfml_t *setfml, void *userdata)
{
    printf("exec hover\n");
    return (size_t)BUTTONFML_SUCC;
}

size_t clicked(setfml_t *setfml, void *userdata)
{
    printf("exec click\n");
    return (size_t)BUTTONFML_SUCC;
}

size_t lostfocus(setfml_t *setfml, void *userdata)
{
    printf("lost focus\n");
    return (size_t)BUTTONFML_SUCC;
}

size_t print_coords(setfml_t *setfml, void *userdata)
{
    printf("%d %d\n", setfml->event.mouseMove.x, setfml->event.mouseMove.y);
    return (size_t)BUTTONFML_SUCC;
}


// Je remarque un manque de callbacks
// Y'a frame, hover, click, rel, mais ça serait pas mal d'avoir frame, hover, unhover, hovering (constant pendant l'hover) au total
int main(void)
{
    setfml_t *setfml = setfml_ini(NULL);
    buttonfml_t *buttonfml = buttonfml_ini(setfml);

    setfml_fillparams(setfml);
    setfml_add(setfml, &(setfml_func_comp_t){NULL, &lostfocus}, "lostfocus", sfEvtLostFocus);
    setfml_add(setfml, &(setfml_func_comp_t){NULL, &print_coords}, "print_coords", sfEvtMouseMoved);

    // Attention cet enchainement cause un probleme, click et rel semblent marcher mais le frame et l'hover ont des problemes
    // Surement un probleme de state reset
    button_t *button = buttonfml_buttoncreate(buttonfml,
        &(btn_text_t){"./assets/images/thug.png",
            "./assets/images/thug2.png",
            "./assets/images/traumatisme.png"},
        &(btn_clbck_t){NULL,
            NULL,
            &clicked,
            NULL},
        "my_button");

    setfml_windowcreate(setfml);
    setfml_windowstart(setfml);

    buttonfml_destroy(buttonfml);
    setfml_destroy(setfml);
}