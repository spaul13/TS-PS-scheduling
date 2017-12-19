#include<xinu.h>

pid32 currentpid;

/*uint32 quantum_selection(pri32 priority){

	uint32 ts_quantum;

	if ((priority>=0) && (priority<10)) {
		ts_quantum=200;}
	else if ((priority>=10) && (priority<20)){
		ts_quantum=160;}
	else if ((priority>=20) && (priority<30)){
		ts_quantum=120;}
	else if ((priority>=30) && (priority<40)){
		ts_quantum=80;}
	else if ((priority>=40) && (priority<58)){
		ts_quantum=40;}
	else{
		ts_quantum=20;}

	return ts_quantum;
}*/

	

void tssched(void){
	
	
	struct procent *ptold, *pt_process;
	ptold= &proctab[currpid];
	if (preempt == QUANTUM){
		if ((ptold->prstate == PR_CURR) || (ptold->prstate == PR_READY)){
			kprintf("\n its a CPU Bound process");
			if(ptold->prprio <= 10)
				ptold->prprio=0;
			else
				ptold->prprio=ptold->prprio - 10;
				
	}
	}
	else	{
		kprintf("\n its a I/0 Bound process");
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
	ptold->prstate=PR_READY;
	insert(currpid, readylist, ptold->prprio);
	currpid = dequeue(readylist);


	pt_process=&proctab[currpid];
/*	preempt=quantum_selection(pt_process->prprio);*/
	insert(currpid, readylist, ptold->prprio);

	
	return ;
			
	
}






	/*preempt=quantum_selection(ptold->prprio);
	pri32 priority=0;
	pid=firstid(readylist); 
	struct procent *ptp;
	while(queuetab[pid].qnext != NULL){
		ptp=&proctab[pid];
		if (pt_process->prprio > priority){
			priority=pt_process->prprio;
			currentpid=pid;}	
		pid=queuetab[pid].qnext;}*/



/*	if (ptold->group == 1) {
		kprintf("\n I am entering in to the TS SCheduler with process id =%5d and the process priority =%5d and the process name= %s\n",currpid, ptold->prprio, ptold->prname);
		if ((preempt<=QUANTUM) || ((preempt == QUANTUM) && (ptold->prstate == PR_CURR))){
			kprintf("\n its a CPU Bound process from resched.c \n");
			if(ptold->prprio <= 10){
				ptold->prprio=0;}
			else{
				ptold->prprio=ptold->prprio - 10;}
				
	}
		else	{
			kprintf("\n its a I/0 Bound process from resched.c \n");
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
		kprintf("\n I am exiting from the TS SCheduler with process id =%5d and the process priority =%5d and the process name is =%s \n",currpid, ptold->prprio, ptold->prname);

		}*/
/* if (ptold->group == 1) {
		if (preempt>0){
			if((ptold->prstate==PR_CURR) || (ptold->prstate==PR_READY)){
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
							
	}}
		else	{
			if(ptold->prprio <= 10){
				ptold->prprio=0;}
			else{
				ptold->prprio=ptold->prprio - 10;}

			
}
*/
