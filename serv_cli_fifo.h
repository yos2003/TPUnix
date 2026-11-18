
#ifndef SERV_CLI_FIFO_H
#define SERV_CLI_FIFO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>

#define NMAX 10

#define fifo1 "fifo1"
#define fifo2 "fifo2"

typedef struct
{
    pid_t pid;
    int n;
} Question;

typedef struct
{
    pid_t pid;
    int nombres[NMAX];
    int n;
} Reponse;

#endif
