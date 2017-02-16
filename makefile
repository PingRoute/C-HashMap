all:order_book 

order_book: project4.c readBinary.c readBinary.h hashmap.c hashmap.h internalstorage.h makefile internalstorage.c market.h libmarket32.a SSO.c SSO.h
	gcc -m32 -o order_book project4.c readBinary.c hashmap.c SSO.c internalstorage.c market.h -pthread -L. libmarket32.a 
clean: 
	rm -f order_book

