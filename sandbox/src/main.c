#include "sandbox.h"

int main(void)
{
    application_t sandbox = sandbox_create();

    application_run(&sandbox);
    application_destroy(&sandbox);

    return 0;
}
