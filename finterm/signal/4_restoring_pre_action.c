#include <signal.h>

static struct sigaction act,oact;

sigaction(SIGTERM,NULL,&oact);
sigaction(SIGTERM,&act,NULL);
sigaction(SIGTERM,&oact,NULL);
