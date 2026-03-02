#include "./buttonfml.h"

int main(void)
{
    setfml_t *setfml = setfml_ini(NULL);
    setfml_fillparams(setfml);

    buttonfml_t *buttonfml = buttonfml_ini(setfml);
    buttonfml_destroy(buttonfml);
    setfml_destroy(setfml);
}