gcc main.c -g -O0
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=./valgrind-out.txt ./a.out