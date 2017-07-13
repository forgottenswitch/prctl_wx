#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/prctl.h>

#include <linux/prctl.h>

__attribute__((constructor))
void activate_MProtect(void) {
    size_t prot;

    prot = PR_LOCKDOWN_MPROT_WX;
#if DISABLE_EXEC_PAGES
    prot = PR_LOCKDOWN_MPROT_X;
#endif

    prctl(PR_LOCKDOWN_MPROT, prot);

    /* Stripping should be performed after the lockdown.  */

    prot = PR_LOCKDOWN_MPROT_STRIP_WX_W;
#if DISABLE_EXEC_PAGES
    prot = PR_LOCKDOWN_MPROT_STRIP_WX_X;
#endif

    prctl(PR_LOCKDOWN_MPROT, prot);

    /* Make fetch faults fatal.  */

    prot = PR_LOCKDOWN_MPROT_NX_FATAL;

    prctl(PR_LOCKDOWN_MPROT, prot);
}
