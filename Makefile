all:
	gcc -o main src/main.c src/queue.c src/fcfs.c
	./main

clean:
	rm main
