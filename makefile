signalTest: signal.c
	gcc signal.c -o signalTest

run: signalTest
	./signalTest

