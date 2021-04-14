utils.o: src/utils.c
	gcc -std=c99 `otf2-config --cflags` \
            -c src/utils.c \
            -o utils.o \
            -I inc

event_callbacks.o: src/event_callbacks.c
	gcc -std=c99 `otf2-config --cflags` \
            -c src/event_callbacks.c \
            -o event_callbacks.o \
            -I inc
     
global_def_callbacks.o: src/global_def_callbacks.c
	gcc -std=c99 `otf2-config --cflags` \
            -c src/global_def_callbacks.c \
            -o global_def_callbacks.o \
            -I inc

barectf.o: src/barectf.c
	gcc -std=c99  \
            -c src/barectf.c \
            -o barectf.o \
            -I inc
         
barectf-platform-linux-fs.o: src/barectf-platform-linux-fs.c
	gcc -std=c99  \
            -c src/barectf-platform-linux-fs.c \
            -o barectf-platform-linux-fs.o \
            -I inc
            
main_functions.o: src/main_functions.c
	gcc -std=c99 `otf2-config --cflags` \
            -c src/main_functions.c \
            -o main_functions.o \
            -I inc         

otf2_converter.o: src/otf2_converter.c
	gcc -std=c99 `otf2-config --cflags` \
            -c src/otf2_converter.c \
            -o otf2_converter.o \
            -I inc

otf2_converter: otf2_converter.o utils.o main_functions.o barectf-platform-linux-fs.o event_callbacks.o barectf.o global_def_callbacks.o
	gcc otf2_converter.o utils.o main_functions.o barectf-platform-linux-fs.o global_def_callbacks.o event_callbacks.o barectf.o\
            `otf2-config --ldflags` \
            `otf2-config --libs` \
            -pthread \
            -I inc \
            -o otf2_converter
