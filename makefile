msg:
	gcc msg_send.c error_handler.c -o msgsnd.out
	gcc msg_recv.c error_handler.c -o msgrcv.out

shm:

	gcc shm_snd.c error_handler.c -o shmsnd.out
	gcc shm_rcv.c error_handler.c -o shmrcv.out

sem:

	gcc sem_w.c error_handler.c -o semw.out
	gcc sem_r.c error_handler.c -o semr.out

pipe:

	gcc anon_pipe.c error_handler.c -o anonpipe.out
	gcc anon_pipe_dual.c error_handler.c -o anondual.out
	gcc simple_pipe.c error_handler.c -o simplepipe.out

fifo:
	gcc chatter_1.c error_handler.c -o chat1.out
	gcc chatter_2.c error_handler.c -o chat2.out
	gcc chatter_3.c error_handler.c -o chat3.out
	gcc logging_service.c error_handler.c -o logging.out
