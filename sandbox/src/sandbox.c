#include "sandbox.h"

#include <dackel2d.h>
#include "test_layer.h"

application_t sandbox_create()
{
    application_t app = application_create();
    Window *window = application_get_main_window(&app);

    window_set_title(window, "Sandbox");
    window_set_size(window, 1280, 800);

    Layer test_layer = test_layer_create();
    application_push_layer(&app, test_layer);

    return app;
}
