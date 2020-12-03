all:
	$(CC) main.c generation.c field.c -lpng
test:
	$(CC) tests.c generation.c field.c -lpng
clean:
	-rm a.out out/output.*
