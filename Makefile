all:
	gcc -o main src/main.c src/queue.c src/srtf.c
	./main

clean:
	rm main
