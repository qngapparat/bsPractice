# bsPractice
Practising IPC in C, including pipes, signals, shared memory and semaphores.
Filenames: r = read, w = write, rcv = receive, snd = send.

#### simple_pipe.c
create am unnamed pipe between related processes used to send string.
#### anon_pipe.c and anon_pipe_dual.c
create one (anon_pipe.c) or two (anon_pipe_dual.c) unnamed pipes between related processes executing shell programs. For anon_pipe_dual.c, an arbitrary task is selected.
#### popen_r.c and popen_w.c
execute shell programs using popen() and pclose() which write to / read from a FILE*
popen_r.c illustrates how to read from the FILE*, where the stdout of "ls -l" is saved. Data is piped from stdout of the shell program to FILE*.
popen_r.c illustrates how to write to the FILE*, where "grep <keyword>" is waiting for stdin. Data is piped from FILE* to stdin of the shell programm.
#### sig.c
sending, catching and handling signals (SIGUSR1, SIGUSR2 and SIGINT) between multiple processes.
#### msg_recv.c and msg_send.c using System V
creating a public message queue (char array) to pass informations between processes.
#### logging_service.c with chatter_1.c thru chatter_3.c
three "chatters" creating a fifos to they each write strings. logging_service.c watches all three using select(), and prints messages of all three fifos.
#### shm_rcv.c and shm_snd.c using System V
creating a shared memory segment and writing / reading a string.
Note: To signal the sender that the signal was received and the shared memory can be deleted by the sender, the first character is set to " * " by the receiver. The sender waits in a loop until this is the case, and then deletes the segment and terminates.
#### sem_r.c and sem_w using System V
creating a public semaphore and using it to control access to one critical region per program.
#### posix_shm.c
using POSIX shared memory to store and change an integer over different processes.
