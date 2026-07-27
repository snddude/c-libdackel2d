#include "sandbox.h"

int main(void)
{
    Application *sandbox = sandbox_create();

    if (sandbox == NULL)
        return 1;

    application_run(sandbox);
    application_destroy(sandbox);

    return 0;
}
