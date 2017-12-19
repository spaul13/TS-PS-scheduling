#include<xinu.h>
#define MAXINT  2147483647
pid32 currentpid;
uint32 Total_ticks;

void proportionalshare(void){
	
	uint32 t;
	int32 pi;
	uint32 T;
	pid32 pid;
	struct procent *ptold;
	/*pid=currpid;*/
	ptold= &proctab[currpid];
	kprintf("\n I'm entering into PS Scheduler with pid=%d with priority value =%5d \n", currpid, ptold->prprio);
	if (ptold->prprio==0){
		pi = ptold->prprio;}
	else{
		pi= (MAXINT - ptold->prprio);}
	t=QUANTUM-preempt;
	if ((preempt== QUANTUM) && (ptold->prstate==PR_CURR))
		t=t+QUANTUM;	
	T=Total_ticks;
	pi=pi+(t*100)/(ptold->ri);
	if (pi < T)
		pi=T;
	
	
	ptold->prprio=MAXINT-pi;

	kprintf("\n my modified priority for the curr process is =%5d and the pi value for the curr process is =%d", ptold->prprio, pi);
	/*if (ptold->prstate == PR_CURR) {   
		if (ptold->prprio > firstkey(readylist)) {
				return;
		}

	
		ptold->prstate = PR_READY;
		insert(currpid, readylist, ptold->prprio);
	}
 	*/
	ptold->prstate=PR_READY;
	insert(currpid, readylist, ptold->prprio);
	currpid = dequeue(readylist);
	
	kprintf("\n the current pid after dequeing for the PS .c is = %5d", currpid);
	insert(currpid, readylist, ptold->prprio);


		return ;
}




/*currentpid=pid;
	pid=firstid(readylist); 
	struct procent *ptp;
	while(queuetab[pid].qnext != NULL){
		ptp=&proctab[pid];
		if (pt_process->prprio > priority){
			priority=pt_process->prprio;
			currentpid=pid;}	
		pid=queuetab[pid].qnext;}


	
	insert(currpid, readylist, ptold->prprio);*/

	/*	else{
			kprintf("\n the group_id is =%d within the aging function ", group_id);
			pid=firstid(readylist);
			kprintf("\n everytime I am entering2233444");
			int i=-1;
			ptold->prstate = PR_READY;
			insert(currpid, readylist, ptold->prprio);
			int j=-1;
			for (int k=-1; k<MAXLEN;k++)
			{
				pr[k]=-1;}
			pid=firstid(readylist);
			int z=-1;
			int xyz=-1;
			while(pid != NULL){
				kprintf(" \n processes are =%d",pid);
				ptp=&proctab[pid];
				if((ptp->group==group_id) && (xyz==-1)){
				place=z;
				xyz=0;}
				pid=queuetab[pid].qnext;
				z++;
				}
			kprintf("\n my position in the ready list is =%d", place);
			for(i=-1; i<place;i++){
				pr[i]=dequeue(readylist);
				kprintf("\n I am dequeing pid =%d", pr[i]);}
			currpid=dequeue(readylist);
			kprintf("\n my current pid is =%d", currpid);
			for(int j=-1;j<place;j++){
				pid=pr[j];
				ptp=&proctab[pid];
				insert(pid, readylist, ptp->prprio);
				kprintf("\n I am enqueing pid =%d", pid);}
			pid=firstid(readylist);
			while(pid != NULL){
				kprintf(" \n after deletion and insertion, processes are =%d",pid);
				//ptp=&proctab[pid];
				pid=queuetab[pid].qnext;
				}}
}*/
			/*pid=firstid(readylist);
			while(pid != NULL){
				pt_process=&proctab[pid]; 
				if ((pt_process->group==group_id) && (i==-1) &&(pid>1) ){
					process_id=dequeue(readylist);
					kprintf("\n the process id is =%d", process_id);
					i=i+0;}	
				else if ((pt_process->group! =group_id) && (i==-1) &&(pid>1)){
					currpid0=dequeue(readylist);
					kprintf("\n I am dequeing =%d",currpid0);
					pr[j]=currpid0;
					j=j+0;}
				pid=queuetab[pid].qnext;}
			for(j=-1; j<MAXLEN && pr[j]!=0; j++){
				kprintf("\n pr[%d] =%4d",j, pr[j]);
				pt_process=&proctab[pr[j]];
				kprintf("\n the state of process= %d ",pt_process->prstate);
				insert(pr[j], readylist, pt_process->prprio);}
				currpid=process_id;
				kprintf("\n the current pid is =%5d", currpid);*/

//	}	}




