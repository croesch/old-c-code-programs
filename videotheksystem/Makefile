FILENAME = videothek.elf

compile:
	gcc -Wall *.c -o $(FILENAME)

execute: compile
	./$(FILENAME)

memory-check: compile
	valgrind ./$(FILENAME)

clean:
	rm -v $(FILENAME)
