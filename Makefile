BIN_FILES = cliente1.o cliente2.o claves.o servidor.o implementacion.o cliente1 cliente2 servidor libclaves.so


CC = gcc



CPPFLAGS = -I$(INSTALL_PATH)/include -Wall




all: $(BIN_FILES)
.PHONY: all

cliente1: cliente1.o libclaves.so
	$(CC) $(CFLAGS) -o $@ $^ -lclaves -lrt -L.

cliente2: cliente2.o libclaves.so
	$(CC) $(CFLAGS) -o $@ $^ -lclaves -lrt -L.

servidor: servidor.o implementacion.o
	$(CC) $(CFLAGS)  -o $@ $^ -lrt -lpthread

libclaves.so: claves.o
	$(CC) $(CFLAGS) -shared -o $@ $^


%o: %c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< 




clean:
	rm -f $(BIN_FILES) *.o

.SUFFIXES:
.PHONY: clean
