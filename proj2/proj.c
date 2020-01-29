#include <linux/syscalls.h>
#include <linux/kernel.h>

SYSCALL_DEFINE2(get_process_zero_session_group, unsigned int *, results, int, size)
{
	
	// Results index
	int results_idx = 0;

	// process 0
	struct task_struct *process_zero = init_task;
	// Get process_zero's pid
	struct pid *p = process_zero->pids[ PIDTYPE_PID ].pid;
	// Get process_zero's node
	struct hlist_node *node = p->tasks[ PIDTYPE_SID ].first;

	// Traverse processes which are in the same login session of process 0
	struct task_struct *t;

	while(node && results_idx < size) {
		t = hlist_entry(node, struct task_struct, pids[ PIDTYPE_SID ]);
		results[ results_idx ] = t->pid;
		results_idx++;
		
		node = node->next;
	}

	return results_idx;
}

SYSCALL_DEFINE2(get_process_session_group, unsigned int *, results, int, size)
{
	// Results index
	int results_idx = 0;
	int local_pid;
	unsigned int local_level;

	// Get leader process's pid
	struct pid *p = current->pids[ PIDTYPE_SID ].pid;
	// Get leader process's node
	struct hlist_node *node = p->tasks[ PIDTYPE_SID ].first;

	// Traverse processes which are in the same login session as current process
	struct task_struct *t;
	
	while(node && results_idx < size) {
		t = hlist_entry(node, struct task_struct, pids[ PIDTYPE_SID ]);
		local_level = t->pids[ PIDTYPE_PID ].pid->level;
		local_pid = t->pids[ PIDTYPE_PID ].pid->numbers[ local_level ].nr;
		results[ results_idx ] = local_pid;
		results_idx++;
		
		node = node->next;
	}

	return results_idx;
}