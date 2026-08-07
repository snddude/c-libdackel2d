#include "sandbox.h"

#include "test_layer.h"

#include <dackel2d.h>

application_t sandbox_create()
{
    application_t app = application_create();

    window_set_title(&app.main_window, "Sandbox");
    window_set_size(&app.main_window, 1280, 800);

    layer_t test_layer = test_layer_create();
    application_push_layer(&app, test_layer);

    return app;
}
