
#include "serv_cli_fifo.h"
#include "Handlers_Serv.h"
#include <errno.h>

volatile sig_atomic_t reveil = 0;

int main()
{
    int fd1, fd2, i;
    Question q;
    Reponse r;

    sigset_t ens, ancien;

    /* Creation des tubes */
    if (mkfifo(fifo1, 0666) == -1 && errno != EEXIST)
    {
        perror("mkfifo fifo1");
        exit(1);
    }

    if (mkfifo(fifo2, 0666) == -1 && errno != EEXIST)
    {
        perror("mkfifo fifo2");
        exit(1);
    }

    srand(getpid());
    printf("PID serveur = %d\n", getpid());
    fflush(stdout);

    /* Ouverture des tubes */
    fd1 = open(fifo1, O_RDONLY);
    fd2 = open(fifo2, O_WRONLY);

    if (fd1 == -1 || fd2 == -1)
    {
        perror("open");
        exit(1);
    }

    /* Installation des handlers */
    signal(SIGUSR1, hand_reveil);
    signal(SIGINT, fin_serveur);
    signal(SIGTERM, fin_serveur);

    /* Bloquer SIGUSR1 */
    sigemptyset(&ens);
    sigaddset(&ens, SIGUSR1);
    sigprocmask(SIG_BLOCK, &ens, &ancien);

    while (1)
    {
        /* Lecture de la question */
        if (read(fd1, &q, sizeof(Question)) != sizeof(Question))
            continue;

        /* Construction de la reponse */
        r.pid = q.pid;
        r.n = q.n;

        for (i = 0; i < q.n; i++)
            r.nombres[i] = rand() % 100;

        reveil = 0;

        /* Envoi de la reponse */
        write(fd2, &r, sizeof(Reponse));

        /* Reveiller le client */
        kill(q.pid, SIGUSR1);

        /* Attendre la confirmation */
        while (reveil == 0)
            sigsuspend(&ancien);
    }

    close(fd1);
    close(fd2);

    return 0;
}
