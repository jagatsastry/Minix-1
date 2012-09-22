#ifndef GLO_H
#define GLO_H

/* Global variables used in the kernel. This file contains the declarations;
 * storage space for the variables is allocated in table.c, because EXTERN is
 * defined as extern unless the _TABLE definition is seen. We rely on the 
 * compiler's default initialization (0) for several global variables. 
 */
#ifdef _TABLE
#undef EXTERN
#define EXTERN
#endif

#include <minix/config.h>
#include "config.h"

/* Variables relating to shutting down MINIX. */
EXTERN char kernel_exception;        /* TRUE after system exceptions */
EXTERN char shutdown_started;        /* TRUE after shutdowns / reboots */

/* Kernel information structures. This groups vital kernel information. */
EXTERN phys_bytes aout;             /* address of a.out headers */
EXTERN struct kinfo kinfo;          /* kernel information for users; Me: kinfo is defined in include/minix/type.h */
EXTERN struct machine machine;      /* machine information for users; Me: machine is defined in include/minix/type.h  */
EXTERN struct kmessages kmess;      /* diagnostic messages in kernel; Me: kmessages is defined in kernel/type.h */
EXTERN struct randomness krandom;   /* gather kernel random information; Me: krandomness is defined in kernel/type.h */


/* Me:
 * prev_ptr, proc_ptr, and next_ptr point to the process table entries
 * of the previous, current, and next processes to run. Bill_ptr also
 * points to a process table entry; it shows which process is currently
 * being billed for clock ticks used. When a user process calls the
 * file system, and the file system is running, proc_ptr points to the
 * file system process.
 * k_reenter, is used to count nested executions of kernel code, such as
 * when an interrupt occurs when the kernel itself, rather than a user
 * process, is running.
 * See page 149, Operating System Design and Implementation 3 ed
 */
/* Process scheduling information and the kernel reentry count. */
EXTERN struct proc *prev_ptr;   /* previously running process; Me: proc is defined in kernel/proc.h */
EXTERN struct proc *proc_ptr;   /* pointer to currently running process */
EXTERN struct proc *next_ptr;   /* next process to run after restart() */
EXTERN struct proc *bill_ptr;   /* process to bill for clock ticks */
EXTERN char k_reenter;          /* kernel reentry count (entry count less 1) */
EXTERN unsigned lost_ticks;     /* clock ticks counted outside clock task */

/* Interrupt related variables. */
EXTERN irq_hook_t irq_hooks[NR_IRQ_HOOKS];          /* hooks for general use */
EXTERN irq_hook_t *irq_handlers[NR_IRQ_VECTORS];    /* list of IRQ handlers */
EXTERN int irq_actids[NR_IRQ_VECTORS];              /* IRQ ID bits active */
EXTERN int irq_use;                                 /* map of all in-use irq's */

/* Miscellaneous. */
EXTERN reg_t mon_ss, mon_sp;    /* boot monitor stack */
EXTERN int mon_return;          /* true if we can return to monitor */

/* Me:
 * Tasks that run in kernel space, currently just the clock task and the
 * system task, have their own stacks within t_stack. During interrupt
 * handling, the kernel uses a separate stack, but it is not declared here,
 * since it is only accessed by the assembly language level routine that
 * handles interrupt processing, and does not need to be known globally.
 */
/* Variables that are initialized elsewhere are just extern here. */
extern struct boot_image image[];   /* system image processe; Me: boot_image is defined in kernel/type.h */
extern char *t_stack[];             /* task stack space; Me: t_stack is defined in kernel/table.c */
extern struct segdesc_s gdt[];      /* global descriptor table; Me: segdesc_s is defined in kernel/type.h */

EXTERN _PROTOTYPE( void (*level0_func), (void) );

#endif /* GLO_H */
