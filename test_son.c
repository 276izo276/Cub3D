#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

#define DELAY_SECONDS 5

int main() {
    pid_t pid;
    pid_t pid1;

    // 1. Crée un nouveau processus
    pid = fork();

    if (pid == -1) {
        perror("fork");
        return 1;
    } else if (pid == 0) {
        // *** Processus Enfant (Child) ***
        // Ce processus DEVIENT VLC, son PID est maintenant le PID de VLC.
        printf("Processus enfant lance VLC via execlp().\n");
		// sleep(2);
        execlp("cvlc", "cvlc", "--play-and-exit", "mp3.mp3", (char *)NULL);
        
        // Si execlp retourne, c'est une erreur.
        perror("Erreur execlp - cvlc non trouve");
        exit(EXIT_FAILURE);
    }

	pid1 = fork();

	if (pid1 == -1) {
        perror("fork");
        return 1;
    } else if (pid1 == 0) {
        // *** Processus Enfant (Child) ***
        // Ce processus DEVIENT VLC, son pid1 est maintenant le pid1 de VLC.
        printf("Processus enfant lance VLC via execlp().\n");
		sleep(2);
        execlp("cvlc", "cvlc", "--play-and-exit", "sound/shoot.mp3", (char *)NULL);
        
        // Si execlp retourne, c'est une erreur.
        perror("Erreur execlp - cvlc non trouve");
        exit(EXIT_FAILURE);
    }
	// *** Processus Parent ***
	printf("Lecture de mp3.mp3 demarree (PID de VLC : %d).\n", pid);

	// Attendre 5 secondes
	printf("Attente de %d secondes avant d'arreter...\n", DELAY_SECONDS);
	sleep(DELAY_SECONDS); 

	// 2. Tuer le PID qui est maintenant VLC
	// SIGTERM demande l'arret. Si cela echoue, essayez SIGKILL.
	if (kill(pid, SIGTERM) == 0) {
		printf("Processus VLC (PID %d) arrete apres %d secondes.\n", pid, DELAY_SECONDS);
	} else {
		perror("kill");
		printf("Erreur lors de la tentative d'arret du processus.\n");
	}

	printf("Programme C termine.\n");

    return 0;
}