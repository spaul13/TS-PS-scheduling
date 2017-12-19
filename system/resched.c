/* resched.c - resched, resched_cntl */

#include <xinu.h>
#define MAXINT  2147483647
#define MAXLEN 18
uint64 rett;
uint64 Ri=10;
uint32 Total_ticks;
uint32 ts_quantum;
pri32 group_priority[2];
pid32 array[MAXLEN];
int place;
int index=0;

void quantum_selection(pri32 priority){

	if ((priority>=0) && (priority<10)) {
		ts_quantum=200;}
	else if ((priority>=10) && (priority<20)){
		ts_quantum=160;}
	else if ((priority>=20) && (priority<30)){
		ts_quantum=120;}
	else if ((priority>=30) && (priority<40)){
		ts_quantum=80;}
	else if ((priority>=40) && (priority<=58)){
		ts_quantum=40;}
	else{
		ts_quantum=20;}

	return ;
}

/*pid32 select_process(int group_id){
	pri32 priority=0;
	pid32 process_id;
	pid32 pid;
	pid=firstid(readylist);
	struct procent *pt_process;
	while(queuetab[pid].qnext != NULL){
		pt_process=&proctab[pid]; 
		if (pt_process->group==group_id){
			if (pt_process->prprio > priority){
				priority=pt_process->prprio;
				process_id=pid;}	}
		pid=queuetab[pid].qnext;}

	return process_id;	
}*/



struct	defer	Defer;

/*------------------------------------------------------------------------
 *  resched  -  Reschedule processor to highest priority eligible process
 *------------------------------------------------------------------------
 */
void	resched(void)		/* Assumes interrupts are disabled	*/
{
	struct procent *ptold;	/* Ptr to table entry for old process	*/
	struct procent *ptnew,*ptp;	/* Ptr to table entry for new process	*/

	/* If rescheduling is deferred, record attempt and return */

	if (Defer.ndefers > 0) {
		Defer.attempt = TRUE;
		return;
	}

	chgprio(0,INITIAL_PRIORITY);
	chgprio(1,INITIAL_PRIORITY);

	/* Point to process table entry for the current (old) process */
	/*kprintf("\n the current process name is = %s and its process id = %5d, the priority of the process = %5d and the process belongs to group =%d", ptnew->prname, currpid, ptnew->prprio, ptnew->group);*/
	pid32 pid1;
	ptold = &proctab[currpid];
	pid1=currpid;
	int group_id, gid;
	if (ptold->group == 0) {
	 	uint32 t;
		pri32 pi;
		uint32 T;
		//kprintf("\n I'm entering into PS Scheduler with pid=%d with priority value =%5d and the total_ticks are =%6d\n", currpid, ptold->prprio, Total_ticks);
		pi= (MAXINT - ptold->prprio);
		t=QUANTUM-preempt;
		//kprintf("\n the value of preempt is %5d and QUANTUM is =%5d \n", preempt, QUANTUM);
		if ((preempt== QUANTUM) && (ptold->prstate==PR_CURR))
			t=t+QUANTUM;	
		T=Total_ticks;
		pi=pi+(t*100)/(ptold->ri);
		if (pi < T){
			pi=T;}
	
		ptold->prprio=MAXINT-pi;
}
	if (ptold->group == 1) {
		if ((preempt>0) && ((ptold->prstate!=PR_CURR) || (ptold->prstate!=PR_READY))){
			if ((ptold->prprio >=0) && (ptold->prprio < 10)){
				ptold->prprio =50;}
			else if ((ptold->prprio >=10) && (ptold->prprio < 20)){
				ptold->prprio = 51;}	 	
			else if ((ptold->prprio >=20) && (ptold->prprio < 30)){
				ptold->prprio = 52;}
			else if ((ptold->prprio >=30) && (ptold->prprio < 35)){
				ptold->prprio = 53;}
			else if ((ptold->prprio >=35) && (ptold->prprio < 40)){
				ptold->prprio = 54;}
			else if ((ptold->prprio >=40) && (ptold->prprio < 45)){
				ptold->prprio=55;}
			else if (ptold->prprio ==45){
				ptold->prprio=56;}
			else if (ptold->prprio ==46){
				ptold->prprio=57;}
			else if ((ptold->prprio >=47) && (ptold->prprio < 59)){
				ptold->prprio=58;}
			else{
				ptold->prprio=59;}
							
	}
		else	{
			if(ptold->prprio <= 10){
				ptold->prprio=0;}
			else{
				ptold->prprio=ptold->prprio - 10;}

			
}}
	
/* Aging starts here*/	
	pid32 gd;		
	uint32 PS_count=0;
	uint32 TS_count=0;
	pri32 PS_priority, TS_priority;
	pid32 pid, process_id;
	kprintf("\n At first ready list \n");
	pid=firstid(readylist);
	while(pid!=NULL){
		kprintf(" %5d", pid);
		if((pid==3) && (index==0)){
			currpid=3;
			ptp=&proctab[currpid];
			ptp->prstate=PR_CURR;
			index+=1;
			return ;}
	/*	if (pid==gd){
			kprintf("\n we will be getting same pid \n");
			return SYSERR;}*/
		gd=pid;
		pid=queuetab[pid].qnext;
				}

	pri32 priority;
	int indicator;
	pid=firstid(readylist); 
	struct procent *pt_process;
	
	/*chgprio (0, INITIAL_PRIORITY);
	chgprio (1,INITIAL_PRIORITY); */
	do{
		pt_process=&proctab[pid];
		//kprintf("\n pids are= %d",pid);
		if ((pt_process->group==0) ) {
			PS_count+=1;
			}
		else if((pt_process->group==1)){
			TS_count+=1;
			}
		pid=queuetab[pid].qnext;

	}while(pid!=NULL);
	chgprio (0, group_priority[0]+PS_count);
	chgprio (1,group_priority[1]+TS_count) ; 

	PS_priority=group_priority[0];
	TS_priority=group_priority[1];
//	kprintf("\n the number of processes in the PS group =%5d, PS_priority =%5d and the number of processes in TS group =%5d, the priority of TS group=%5d",PS_count, PS_priority, TS_count, TS_priority);
	if (PS_priority >= TS_priority){
		group_id=0;}
	else if (PS_priority < TS_priority){
		group_id=1;}
	if ((TS_count==0) ||(PS_count ==0)){
		indicator=1;
	if (ptold->prstate == PR_CURR) {   
		if (ptold->prprio > firstkey(readylist)) {
			if(ptold->group == 1){
				quantum_selection(ptold->prprio);
				preempt=ts_quantum;}
			/*else {
			preempt = QUANTUM;}*/
			chgprio(ptold->group, INITIAL_PRIORITY);
			return;
		}

	
		ptold->prstate = PR_READY;
		insert(currpid, readylist, ptold->prprio);
	}

	/* Force context switch to highest priority ready process */
	currpid = dequeue(readylist);
	/*kprintf("\n the current pid after dequeing for the resched .c is = %5d \n", currpid);
	kprintf("\n the first process id in ready list=%5d after dequeuing \n", pid);*/
	struct procent *ptp;
}
	
	pid32 currpid1;
	pid=firstid(readylist);
	int place;
	kprintf("\n now the TS count %d and TS_priority =%d and PS count is %d and PS_priority=%d \n", TS_count, TS_priority, PS_count, PS_priority); 
	if ((TS_count >0) && (PS_count >0) && (indicator==0)){
		if ((ptold->prstate == PR_CURR) && (ptold->group==group_id) && (ptold->prprio >firstkey(readylist))){
			if(ptold->group == 1){
				quantum_selection(ptold->prprio);
				preempt=ts_quantum;}
			/*	else {
			preempt = QUANTUM;}*/

			chgprio(ptold->group, INITIAL_PRIORITY);
			return;
		}

		else{
			kprintf("\n before inserting the previous pid to ready list \n");
			pid=firstid(readylist);
			while(pid!=NULL){
				kprintf(" %5d", pid);
				pid=queuetab[pid].qnext;
				}
			struct procent *ptxtra;
			ptxtra=&proctab[pid1];
			ptxtra->prstate = PR_READY;
			if (PS_priority >= TS_priority){
				group_id=0;}
			else if (PS_priority < TS_priority){
				group_id=1;}
			insert(pid1, readylist, ptxtra->prprio);
			kprintf("\n our currpid was =%d and pid1=%d", currpid, pid1);
			kprintf("\n the goup id needs to be selected =%d \n after inserting the previous pid to ready list \n",group_id);
			pid=firstid(readylist);
			while(pid!=NULL){
				kprintf(" %5d", pid);
				pid=queuetab[pid].qnext;
				}

			pid32 process_id;
			int i;
			int j=0;
			pid=firstid(readylist); 
			priority=0;
			while(pid != NULL){
				pt_process=&proctab[pid]; 
				if ((pt_process->group==group_id)&& (pid>3)){
					if (pt_process->prprio > priority){
					process_id=pid;
					priority=pt_process->prprio;
					}
				}	
				pid=queuetab[pid].qnext;}
			currpid=process_id;
			getitem(process_id);
			kprintf("\n the current pid is =%5d\t process id=%5d",currpid,process_id);

			/*for(int l=0; l<MAXLEN; l++)
				{
					array[l]=0;}
			place=0;
			i=0;
			while(pid != NULL){
				pt_process=&proctab[pid]; 
				if ((pt_process->group==group_id) && (i==0)){
					process_id=pid;
					i=i+1;
					}
				if (i==0){
					place+=1;}	
				pid=queuetab[pid].qnext;}
			kprintf("\n printing the array...  ");
			for(j=0; j<place; j++){
				array[j]=dequeue(readylist);
				kprintf("%5d",array[j]);
				}
			currpid=dequeue(readylist);
			kprintf("\n the current process is =%d and the readylist after dequeing and the value of place is=%d\n",currpid,place);
			pid=firstid(readylist);
			while(pid!=NULL){
				kprintf(" %5d", pid);
				pid=queuetab[pid].qnext;
				}
			for(int k=0; k<place ;k++)
				{
				pid=array[k];
				pt_process=&proctab[pid];
				insert(pid,readylist,pt_process->prprio);}
			kprintf("\n the readylist after enqueing \n");
			pid=firstid(readylist);
			while(pid!=NULL){
				kprintf(" %5d", pid);
				pid=queuetab[pid].qnext;
				}*/
			
			/*pid=firstid(readylist);
			kprintf("\n current pid will be =%d and process-id =%d \n readylist before get item() \n",currpid, process_id);
			while(pid!=NULL){
				kprintf(" %5d", pid);
				pid=queuetab[pid].qnext;
				}
			currpid=getitem(process_id);
			pid=firstid(readylist);
			kprintf("\n readylist after get item() \n");
			while(pid!=NULL){
				kprintf(" %5d", pid);
				pid=queuetab[pid].qnext;
				}
			kprintf("\n the current process id is= %d", currpid);
			i=1;
			place=0;
			pid=firstid(readylist);*/
			}}
 
	ptnew = &proctab[currpid];
	ptnew->prstate = PR_CURR;
	chgprio(ptnew->group, INITIAL_PRIORITY);
	//kprintf("\n \n the current process name is = %s and its process id = %5d, the priority of the process = %5d and the process belongs to group =%5d \n ", ptnew->prname, currpid, ptnew->prprio, ptnew->group);
	if(ptnew->group == 1){
		quantum_selection(ptnew->prprio);
		preempt=ts_quantum;
		//kprintf("\n my new priority is =%5d and corresponding time quantum is =%5d \n", ptnew->prprio, preempt);
}
	else{
		preempt=QUANTUM;}
        ptold=&proctab[pid1];
		/* Reset time slice for process	*/
	ctxsw(&ptold->prstkptr, &ptnew->prstkptr);

	/* Old process returns here when resumed */

	return;
}

/*------------------------------------------------------------------------
 *  resched_cntl  -  Control whether rescheduling is deferred or allowed
 *------------------------------------------------------------------------
 */
status	resched_cntl(		/* Assumes interrupts are disabled	*/
	  int32	defer		/* Either DEFER_START or DEFER_STOP	*/
	)
{
	switch (defer) {

	    case DEFER_START:	/* Handle a deferral request */

		if (Defer.ndefers++ == 0) {
			Defer.attempt = FALSE;
		}
		return OK;

	    case DEFER_STOP:	/* Handle end of deferral */
		if (Defer.ndefers <= 0) {
			return SYSERR;
		}
		if ( (--Defer.ndefers == 0) && Defer.attempt ) {
			resched();
		}
		return OK;

	    default:
		return SYSERR;
	}
}
