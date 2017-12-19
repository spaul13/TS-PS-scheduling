/* chprio.c - chprio */

#include <xinu.h>

pri32 group_priority[2];
/*------------------------------------------------------------------------
 *  chprio  -  Change the scheduling priority of a process
 *------------------------------------------------------------------------
 */
void	chgprio(
	  int		 group,	/* ID of group to change	*/
	  pri32		 newprio		/* New priority			*/
	)
{
	intmask	mask;			/* Saved interrupt mask		*/
	group_priority[group]=newprio;	
	restore(mask);
	return ;
}


