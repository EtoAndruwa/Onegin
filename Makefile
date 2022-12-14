CFLAGS= -g -c -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wno-missing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -Werror=vla -D_DEBUG -D_EJUDGE_CLIENT_SIDE

all: main prog_ex

main: main.o Onegin.o 
	gcc main.o Onegin.o -o Onegin.exe

main.o: main.cpp
	gcc $(CFLAGS) main.cpp

Onegin.o: Onegin.cpp
	gcc $(CFLAGS) Onegin.cpp

prog_ex: 
	valgrind -s --leak-check=full --show-leak-kinds=all --log-file="log_val.txt" ./Onegin.exe

clean: 
	rm -rf *.o main