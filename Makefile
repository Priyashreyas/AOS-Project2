all:
	gcc -o main src/main.c src/queue.c src/hpf.c
	./main

clean:
	rm main
