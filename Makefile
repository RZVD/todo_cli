build_and_run:
	$(CC) src/main.c src/datastructures.c src/datastructures.h -o main
	./main
release:
	 $(CC) src/main.c src/datastructures.c src/datastructures.h -o todo
