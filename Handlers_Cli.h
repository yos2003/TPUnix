
#ifndef HANDLERS_CLI_H
#define HANDLERS_CLI_H

#include <signal.h>

extern volatile sig_atomic_t reveil;

void hand_reveil(int sig)
{
    reveil = 1;
}

#endif
