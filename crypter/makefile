#makefile for crypter
all: encrypt decrypt runtest

clean:
	rm -ff crypto.o crypto
	rm -ff crypto-test.o run-test
	rm -ff encrypt.o encrypt
	rm -ff decrypt.o decrypt
	rm -ff executable.o

runtest: crypto-test.o
	cc -o run-test crypto.o crypto-test.o

crypto-test.o: crypto-test.c
	cc -Wall -c crypto-test.c
	
crypto.o: crypto.c
	cc -Wall -c crypto.c

executable.o: executable.c
	cc -Wall -c executable.c

encrypt.o: encrypt.c
	cc -Wall -c encrypt.c

decrypt.o: decrypt.c
	cc -Wall -c decrypt.c

encrypt: crypto.o encrypt.o executable.o
	cc -o encrypt crypto.o encrypt.o executable.o

decrypt: crypto.o decrypt.o executable.o
	cc -o decrypt crypto.o decrypt.o executable.o
