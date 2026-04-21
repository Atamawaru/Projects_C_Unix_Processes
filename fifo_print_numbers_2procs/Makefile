all: main1 main2 run

main1: main1.c
	gcc -Werror main1.c -o main1
main2: main2.c
	gcc -Werror main2.c -o main2
run: main1 main2
	./main1
	./main2

