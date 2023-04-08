BIN_FILES = cliente1.o cliente2.o claves.o servidor.o implementacion.o cliente1 cliente2 servidor libclaves.so lines.o


CC = gcc



CPPFLAGS = -I$(INSTALL_PATH)/include -Wall




all: $(BIN_FILES)
.PHONY: all

cliente1: cliente1.o libclaves.so
	$(CC) $(CFLAGS) -o $@ $^ -lclaves -L.

cliente2: cliente2.o libclaves.so
	$(CC) $(CFLAGS) -o $@ $^ -lclaves -L.

servidor: servidor.o implementacion.o lines.o
	$(CC) $(CFLAGS)  -o $@ $^ -lpthread

libclaves.so: claves.o lines.o
	$(CC) $(CFLAGS) -shared -o $@ $^


%o: %c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< 




clean:
	rm -f $(BIN_FILES) *.o

.SUFFIXES:
.PHONY: clean
