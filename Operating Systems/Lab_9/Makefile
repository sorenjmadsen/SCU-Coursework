all: step1.c step2.c step3.c step4.c
	gcc -o step1 step1.c
	gcc -o step2 step2.c
	gcc -o step3 step3.c
	gcc -o step4 step4.c -lpthread

one: step1.c
	gcc -o step1 step1.c

two: step2.c
	gcc -o step2 step2.c

three: step3.c
	gcc -o step3 step3.c

four: step4.c
	gcc -o step4 step4.c -lpthread

clean:; rm -f step1 step2 step3 step4
