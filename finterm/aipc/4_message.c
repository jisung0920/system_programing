/* showmsg -- show message queue details */
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <time.h>
#include <stdio.h>
void mqstat_print(int mqid, struct msqid_ds *mstat)
{
printf("\nmsg_qid %d\n\n", mkey, mqid);
printf("%d message(s) on queue\n\n", mstat->msg_qnum);
printf("Last send by proc %d at %s\n", mstat->msg_lspid, ctime(&(mstat-
>msg_stime)));
printf("Last recv by proc %d at %s\n", mstat->msg_lrpid, ctime(&(mstat-
>msg_stime)));
}
int main(int argc, char *argv[])
{
int msq_id;
struct msqid_ds msq_status;
if(argc != 2) {
fprintf(stderr, "usage:showmsg keyval\n");
exit(1);
}
/*get message queue identifier*/
msq_id = atoi(argv[1]);
/*get status information*/
if (msgctl(msq_id, IPC_STAT, &msq_status) < 0) {
perror("msgctl failed");
exit(3);
}
/*print out status infromation*/
mqstat_print(msq_id, &msq_status);
exit(0);
}
