#include "sandbox.h"

int main(void)
{
    application_t sandbox;

    if (!sandbox_init(&sandbox))
        return 1;

    application_run(&sandbox);
    application_destroy(&sandbox);

    return 0;
}
