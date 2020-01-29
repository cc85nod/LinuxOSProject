# LinuxOSProject
modify the kernel

## proj1
**Description** :

Add a new system call void linux_survey_TT(char \*) to your Linux kernel so that you can call it in your program. The system call has the following properties.

1. The system call has a parameter which specifies the address of a memory area that can store all information the system call collects in the kernel. You may need to design the layout of the memory area to store your information.
2. The system call records the virtual address intervals consisting of the user address space of the process executing the system call.
3. The system call records the corresponding physical address intervals used by the above virtual address intervals at the moment that you execute system call void linux_survey_TT().

Write a program test.c as follows to collect the information you need. Execute this program after your start all required programs.

## proj2
**Description** :

1. Write a new system call get_process_zero_session_group(unsigned int \*, int) so that a process can use it to get the global PIDs of all processes that are in the same login session of process 0. If the number of processes in this login session is larger than the value of the second parameter, such as SIZE, you only need to store the PIDs of the first SIZE processes. The return value of this system call is either 0 or a positive value. 0 means that an error occurs when executing this system call. A positive value means the number of processes in this login session. The first argument of this system call is used to store the result of this system call.
2. Write a new system call get_process_session_group(unsigned int \*, int) so that a process can use it to get the local PIDs of all processes that are in the same login session as the process. If the number of processes in this login session is larger than the value of the second parameter, such as SIZE, you only need to store the PIDs of the first SIZE processes. The return value of this system call is either 0 or a positive value. 0 means that an error occurs when executing this system call. A positive value means the number of processes in this login session. The first argument of this system call is used to store the result of this system call.
