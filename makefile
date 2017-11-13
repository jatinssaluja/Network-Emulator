.PHONY: all bridge station

all: bridge station


bridge:
		gcc -pthread -o bridge bridge.c -std=gnu99 -w

station:
		gcc -o station station.c -std=gnu99 -w


clean:

	rm *.o bridge station
