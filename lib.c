#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/prctl.h>

#define PR_LOCKDOWN_MPROT 48
#define PR_LOCKDOWN_MPROT_X 1
#define PR_LOCKDOWN_MPROT_WX 2

__attribute__((constructor))
void activate_MProtect(void) {
    size_t prot;

    prot = PR_LOCKDOWN_MPROT_WX;
#if DISABLE_EXEC_PAGES
    prot = PR_LOCKDOWN_MPROT_X;
#endif

    prctl(PR_LOCKDOWN_MPROT, prot);
}
