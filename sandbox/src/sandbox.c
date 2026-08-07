#include "sandbox.h"

#include "test_layer.h"

bool sandbox_init(application_t *self)
{
    if (!application_init(self))
        return false;

    window_set_title(&self->main_window, "Sandbox");
    window_set_size(&self->main_window, 1280, 800);

    layer_t test_layer = test_layer_create();
    application_push_layer(self, test_layer);

    return true;
}
