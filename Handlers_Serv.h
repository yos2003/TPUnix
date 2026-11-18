
#ifndef HANDLERS_SERV_H
#define HANDLERS_SERV_H

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

extern volatile sig_atomic_t reveil;

void hand_reveil(int sig)
{
    reveil = 1;
}

void fin_serveur(int sig)
{
    printf("Arret du serveur\n");
    exit(0);
}

#endif
