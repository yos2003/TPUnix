
#include "serv_cli_fifo.h"
#include "Handlers_Cli.h"

volatile sig_atomic_t reveil = 0;

int main(int argc, char *argv[])
{
    int fd1, fd2, i;
    pid_t pid_serv;
    Question q;
    Reponse r;

    sigset_t ens, ancien;

    /* Recuperer le PID du serveur */
    if (argc != 2)
    {
        printf("Utilisation : ./client PID_SERVEUR\n");
        exit(1);
    }

    pid_serv = atoi(argv[1]);

    /* Ouverture des tubes */
    fd1 = open(fifo1, O_WRONLY);
    fd2 = open(fifo2, O_RDONLY);

    if (fd1 == -1 || fd2 == -1)
    {
        perror("open");
        exit(1);
    }

    /* Installation du handler */
    signal(SIGUSR1, hand_reveil);

    /* Bloquer SIGUSR1 */
    sigemptyset(&ens);
    sigaddset(&ens, SIGUSR1);
    sigprocmask(SIG_BLOCK, &ens, &ancien);

    /* Construction de la question */
    srand(getpid());

    q.pid = getpid();
    q.n = rand() % NMAX + 1;

    printf("Je demande %d nombres\n", q.n);

    /* Envoi de la question */
    write(fd1, &q, sizeof(Question));

    /* Attente de la reponse */
    while (reveil == 0)
        sigsuspend(&ancien);

    /* Lecture de la reponse */
    if (read(fd2, &r, sizeof(Reponse)) == sizeof(Reponse))
    {
        if (r.pid == getpid())
        {
            printf("Reponse recue :\n");

            for (i = 0; i < r.n; i++)
                printf("%d ", r.nombres[i]);

            printf("\n");

            /* Confirmation au serveur */
            kill(pid_serv, SIGUSR1);
        }
    }

    close(fd1);
    close(fd2);

    return 0;
}
