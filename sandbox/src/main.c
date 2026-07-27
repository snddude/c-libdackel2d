#include <dackel2d.h>

#include "test_layer.h"

int main(void)
{
    Application *app = application_create();

    if (app == NULL)
        return 1;

    Layer test_layer = test_layer_create();
    application_push_layer(app, test_layer);

    application_run(app);
    application_destroy(app);

    return 0;
}
