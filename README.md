# bsPractice
Practising IPC in C, including pipes, signals, shared memory and semaphores.
Filenames: r = read, w = write, rcv = receive, snd = send.
#### popen_r.c and popen_w.c
execute shell programs using popen() and pclose() which write to / read from a FILE*

popen_r.c illustrates how to read from the FILE*, where the stdout of "ls -l" is saved. Data is piped from stdout of the shell program to FILE*.

popen_r.c illustrates how to write to the FILE*, where "grep <keyword>" is waiting for stdin. Data is piped from FILE* to stdin of the shell programm.
#### msg_recv.c and msg_send.c using System V
creating a public message queue (char array) to pass informations between processes.
#### shm_rcv.c and shm_snd.c using System V
creatiing a shared memory segment and writing / reading a string.

Note: To signal the sender that the signal was received and the shared memory can be deleted by the sender, the first character is set to " * " by the receiver. The sender waits in a loop until this is the case, and then deletes the segment and terminates.
#### sem_r.c and sem_w using System V
creating a public semaphore and using it to control access to one critical region per program.
