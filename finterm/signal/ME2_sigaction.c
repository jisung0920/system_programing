#include <stdio.h>
#include <sys/types.h>//
#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>//
#include <unistd.h>
int pid;
static char *chdargv[] = {
	"p1", "p2", (char *)0
}
;
static char *chdenv[4];
int main (int argc, char *argv[]) {
	int i, cpid1, cpid2, cpid3;
	struct sigaction action, old_action;
	void wakeup(), handler(), trapper(int), parent(int);
	sigset_t sigmask;
	/* a process-wide signal mask */
	sigemptyset(&sigmask);
	/* to empty bits in sigmask */
	sigprocmask(SIG_SETMASK, &sigmask, 0);
	/* to initialize signal mask */
	action.sa_flags = 0;
	/* to init signal flags */
	action.sa_handler = SIG_IGN;
	/* to ignore signal */
	sigemptyset(&action.sa_mask);
	/* zero out sa_mask */
	if (!(cpid1 = fork())) {
		/* 1st child */
		pid = cpid1 = getpid();
		/* get pid for child 1 */
		printf("\nCPID1 = %d", cpid1);
		for (i = 1; i < NSIG; i++)
		sigaction(i, &action, &old_action);
		/* ignore all signals */
		sigaddset(&action.sa_mask, SIGINT);
		/* add SIGINT to sa_mask **
** implicitly done, not needed, just for illustration purpose */
		action.sa_flags |= SA_RESTART;
		/* sys calls auto restart */
		action.sa_handler = handler;
		/* user-defined sig handler */
		sigaction(SIGINT, &action, &old_action);
		/* SIGINT is also blocked */
		sigaddset(&action.sa_mask, SIGALRM);
		/* again, for illustration */
		action.sa_handler = wakeup;
		/* another user-defined */
		sigaction(SIGALRM, &action, &old_action);
		/* SIGALRM is also blocked */
		alarm((unsigned)2);
		/* set alarm for 2 secs */
		for (;;)
		pause();
		/* wait for signals */
		printf(" -- CPID1 (%d) terminates\n", cpid2);
		/* never gets here */
		exit(0);
	} else {
		if (!(cpid2 = fork())) {
			/* 2nd child */
			pid = cpid2 = getpid();
			/* get pid for child 2 */
			printf("\n\tCPID2 = %d", cpid2);
			action.sa_handler = trapper;
			/* one more user-defined */
			for (i = 1; i < NSIG; i++)
			sigaction(i, &action, &old_action);
			pause();
			printf(" -- CPID2 (%d) terminates\n", cpid2);
			exit(0);
		} else {
			if (!(cpid3 = fork())) {
				/* 3rd child */
				pid = cpid3 = getpid();
				/* get pid for child 3 */
				printf("\n\t\tCPID3 = %d ", cpid3);
				sigaddset(&action.sa_mask, SIGUSR2);
				/* block sig SIGUSR2 */
				action.sa_handler = trapper;
				sigaction(SIGUSR2, &action, &old_action);
				chdenv[0] = "HOME=here";
				chdenv[1] = "PATH=/bin";
				chdenv[2] = "MAILX=/usr/lib/xxx";
				chdenv[3] = (char *)0 ;
				pause();
				printf(" -- CPID3 (%d) terminates\n",cpid3);/////#########33
				exit(0);
      }
				pid = getpid();
				/* pid for parent */
				sleep(3);
				/* to let child run first
printf("\nThis is parent process (pid = %d)\n", pid);
sigfillset(&action.sa_mask);
/* to block all signals */
				action.sa_handler = parent;
				/* all goes to parent */
				for (i = 1; i < NSIG; i++)
				sigaction(i, &action, &old_action);
				/* catch all signals */
				printf("\n\tSend SIGBUS(%d) to CPID1 (%d)", SIGBUS, cpid1);
				kill(cpid1, SIGBUS);
				printf("\n\tSend SIGINT(%d) to CPID1 (%d)", SIGINT, cpid1);
				kill(cpid1, SIGINT);
				printf("\n\t\tSend SIGBUS(%d) to CPID2 (%d)", SIGBUS, cpid2);
				kill(cpid2, SIGBUS);
				printf("\n\t\tSend SIGTERM(%d) to CPID2 (%d)", SIGTERM, cpid2);
				kill(cpid2, SIGTERM);
				printf("\n\t\tSend SIGUSR1(%d) to CPID2 (%d)", SIGUSR1, cpid2);
				kill(cpid2, SIGUSR1);
				printf("\n\t\t\tSend SIGUSR2(%d) to CPID3 (%d)", SIGUSR1, cpid3);
				kill(cpid3, SIGUSR2);
				wait((int *)0);
			}
		}
		return(0);
	}
	/* main */

	void wakeup() {
		printf("\nI (pid = %d) am up now\n", pid);
	}
	/* wakeup */
	void handler() {
		printf("\nI (pid = %d) got an interrupt; will continue\n", pid);
	}
	/* handler */
	void trapper(int i) {
		/* No reset is needed any more */
		if (i == SIGUSR1) {
			printf("\n\tGot SIGUSR1(%d); process(%d) will terminate\n", i, pid);
			exit(2);
		} else {
			if (i == SIGUSR2) {
				printf("\n\t\t(%d) got SIGUSR2(%d); execs a new program", i, pid);
				execve("./sigexec", chdargv, chdenv);
				perror("\nTHIS LINE SHOULDN'T BE HERE\n");
			} else
			printf("\n\tGot a signal(%d); process(%d) continues\n", i, pid);
		}
	}
	/* trapper */
	void parent(int sig) {
		printf("\nSignal (%d) received by parent (%d)", sig, pid);
	}
	/* parent */
