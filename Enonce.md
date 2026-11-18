explique l'enoncé :                                                                                                                                                                                             Oo                                                                                     !            "   # $                                             %                      #                                                                &'                       (           #  OS
)                     !  Programmation sous Unix
                           Université Virtuelle de Tunis
*                      +         &    (  La communication par tubes nommés(fifo)
Généralités
*     +                                         +                                                         Les tubes nommés ont les caractéristiques des tubes de communications, avec la propriété de posséder des                     -                  &             +                          .    / (  références dans le systéme de fichiers (ils sont visibles par la commande shell : Is -!)
>   >  0                                                                  %              +         #  Des processus sans lien de parenté particulier peuvent communiquer a l'aide des tubes nommés. 
Création d’un tube nommé
```
#include <sys/types.h>
```
```
#include <sys/stat.h>
```
```
int mkfifo (const char *ref, mode_t mode)
```
. `ref`                                 +    désigne le chemin d’accés au tube
. `mode`                            désigne le droit d’accés <u>       </u> Exemple
```
  mode_t mode=S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR | S_IWGRP | S_IWOTH;
```
™ *                    /'                  La primitive renvoie -1 en cas d’erreur
Suppression d’un tube nommé
```
#include <unistd.h>
```
```
int unlink (const char *ref)
```
. `ref`                                 +    désigne le chemin d’accés au tube
Ouverture et fermeture d’un tube
<u>                </u> La fonction open
```
#include<sys/types.h>
```
```
#include<sys/stat.h>
```
```
#include<fcntl.h>
```
```
int open(const char* ref, int oflag [, int mode])
```
. `ref`                                        désigne le chemin d’accés au fichier
. `oflag`                                                  détermine pour quelle opération il est ouvert
. `mode`                                                paramétre optionnel désigne le droit d’accés
<u>                                        </u> Les valeurs possibles du paramétre oflaq
         O_RDONLY                              ouvre en lecture seulement
         O_WRONLY                               ouvre en écriture seulement
>                       <u>Mr Ezzeddine Zagrouba</u> 
,
)                     !  Programmation sous Unix
                           Université Virtuelle de Tunis
*                      +         &    (  La communication par tubes nommés(fifo)
<u>                  La fonction close</u>
<u>                  La fonction close</u>
```
#include<unistd.h>
```
```
int close(int fd)
```
. `fd`                                   descripteur d’un fichier ouvert
Exercices
<u>  EXERCICE           1:   </u>
2                            -                        Nous souhaitons réaliser un systeme de communication `client/serveur` #                      -       . V'architecture de ce systeme                                      .                                                      +         correspond au schéma général suivant : Un serveur attend des questions de clients dans un tube nommé `fifo1` #  .                          %                        Une question corresponde a la demande d’envoi de `n`     +                                 & nombres tirés au sort par le serveur( `n`            +    est un nombre                          aléatoire compris entre `1`      et `NMAX`                             (# 0                                                 tiré au sort par le client). Dans sa question, le client envoie également son                                                                                       numéro de telle sorte que le serveur peut le réveiller par l’intermédiaire du signal `SIGUSR1`                       quand il a écrit la        #                                    3                                   3     +         réponse. En effet plusieurs clients pouvant étre en attente de réponse dans le méme tube nommé `fifo2` ,ilest                                                                                                                #           nécessaire de définir un protocole assurant que chaque client lit les réponses qui lui sont destinées. Le client                 3                                               #  avertit par ce méme signal le serveur quand il a lu les réponses.
'( 0                            4 Donner le contenu du fichier « `serv_cli_fifo.h»`                %                  .  qui corresponda la définition de :   -    3                  -                   5  entétes des fichiers systemes nécessaires ;   -                                  !              !          & constantes et macros communes aux clients et aux serveurs ( `NMAX`    , `fifo1`    , `fifo2` pe)  6 ( 5     -                                                                    #  structures des données pour représenter une question et une réponse.
,( 0                            4  Donner le contenu du fichier « `Handlers_Serv.h`  7                           !                          » contenant les codes de deux handlers correspondants   ! .  aux:   -                         %                         réveil du serveur suite a la réception du signal `SIGUSR1`  .   : `void hand_reveil(int sig)`
  -                      %                                     .  fin du serveur suite a la réception d’un signal quelconque : `void fin_serveur(int sig)`
1(                                                                  /        .  Ecrire le programme du serveur en suivant les étapes indiquées ci-dessous :
>                       <u>Mr Ezzeddine Zagrouba</u> 
1
)                     !  Programmation sous Unix
                           Université Virtuelle de Tunis
*                      +         &    (  La communication par tubes nommés(fifo)
```
#include "serv_cli_fifo.h"
#include "Handlers_Serv.h"
main(){
/*Déclarations */
 …
/* Création des tubes nommés  */
 …
/*initialisation du générateur de nombres aléatoires*/
srand(getpid());
/* Ouverture des tubes nommés  */
 …
/* Installation des Handlers */
 …
while(1){
   /* lecture d’une question */
 …
   /* construction de la réponse */
…
   /* envoi de la réponse */
 …
   /* envoi du signal SIGUSR1 au client concerné */
 …
}
}
```
>                       <u>Mr Ezzeddine Zagrouba</u> 
8
)                     !  Programmation sous Unix
                           Université Virtuelle de Tunis
*                      +         &    (  La communication par tubes nommés(fifo)
8( 0                            4  Donner le contenu du fichier « `Handlers_Cli.h`  7                                                          » contenant le code du handler correspondant au réveil du              %                         client suite a la réception du signal `SIGUSR1`  .   : `void hand_reveil(int sig)`
9(                                                                              /        .  Ecrire le programme d’un client quelconque en suivant les étapes indiquées ci-dessous :
```
#include "serv_cli_fifo.h"
#include "Handlers_Cli.h"
main(){
/* Déclarations */
 …
/* Ouverture des tubes nommés  */
 …
/* Installation des Handlers */
 …
/* Construction et envoi d’une question */
 …
/* Attente de la réponse */
 …
/* Lecture de la réponse */
 …
/* Envoi du signal SIGUSR1 au serveur */
 …
 /* Traitement local de la réponse */
 …
}
```
