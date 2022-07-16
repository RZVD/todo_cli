build_and_run:
	gcc src/main.c src/datastructures.c src/datastructures.h 
	src/database.c src/database.h -o main
	./main
release:
	gcc src/main.c src/datastructures.c src/datastructures.h -o todo