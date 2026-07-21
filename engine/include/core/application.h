#pragma once

#include "core/window.h"

typedef struct application Application;

Application *application_create();
void application_destroy(Application *application);

void application_run(Application *application);

Window *application_get_main_window(Application *application);
