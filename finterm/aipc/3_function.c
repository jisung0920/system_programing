#include <string.h>
#include "q.h"
static int s_qid = -1; /*message queue identifier*/
int enter(char *objname, int priority)
{
int len;
struct q_entry s_entry; /*structure to hold message*/
/*validate name length, priority level*/
if ((len = strlen(objname)) > MAXOBN) {
fprintf(stderr, "name too logn");
return (-1);
}
if (priority > MAXPRIOR || priority < 0) {
fprintf(stderr, "invalid priority level");
return (-1);
}
/*initial message queue as necessary*/
if (s_qid == -1 && (s_qid = init_queue()) == -1)
return (-1);
/* initialize s_entry */
s_entry.mtype = (long) priority;
strncpy(s_entry.mtext, objname, MAXOBN);
/*send message, waiting if necessary*/
if (msgsnd(s_qid, &s_entry, len, 0) == -1) {
perror("msgsnd failed");
return (-1);
}
else
return (0);
}

int init_queue(void)
{
int queue_id;
/*attemp to create message queue*/
if ((queue_id = msgget(QKEY, IPC_CREAT|QPERM)) == -1)
perror("msgget failed");
return (queue_id);
}
static int r_qid = -1;
Int proc_obj(struct q_entry *msg)
{
printf("\npriority: %ld name: %s\n", msg->mtype, msg->mtext);
}
int serve(void)
{
struct q_entry r_entry;
int mlen;
/*initialize queue as necessary*/
if (r_qid == -1 && (r_qid = init_queue()) == -1)
return (-1);
/*get and process next message, waiting if necessary*/
for(;;) {
if ((mlen = msgrcv(r_qid, &r_entry, MAXOBN, (long) -1*MAXPRIOR,
MSG_NOERROR)) == -1) {
perror(“msgrcv failed”);
return (-1);
}
else {
/*make sure we've a string*/
r_entry.mtext[mlen] = '\0';
/*print object name*/
proc_obj(&r_entry);
}
}
}
