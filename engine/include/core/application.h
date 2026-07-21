#pragma once

typedef struct application Application;

Application *application_create();
void application_destroy(Application *application);

void application_run(Application *application);
