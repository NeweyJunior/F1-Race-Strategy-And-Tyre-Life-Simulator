main.exe: main.c src/*.c
	gcc -Wall -Wextra -O3 main.c src/*.c -o main.exe