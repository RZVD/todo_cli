build_and_run:
	gcc src/main.c src/datastructures.c src/datastructures.h -o main
	./main
release:
	gcc src/main.c src/datastructures.c src/datastructures.h -o todo