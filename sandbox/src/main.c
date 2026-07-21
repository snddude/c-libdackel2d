#include <dackel2d.h>

int main(void)
{
    Application *app = application_create();

    application_run(app);
    application_destroy(app);

    return 0;
}
