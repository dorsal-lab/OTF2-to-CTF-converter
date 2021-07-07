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
            
attribute_callbacks.o: src/attribute_callbacks.c
	gcc -std=c99 `otf2-config --cflags` \
            -c src/attribute_callbacks.c \
            -o attribute_callbacks.o \
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
            
utilities_functions.o: src/utilities_functions.c
	gcc -std=c99 `otf2-config --cflags` \
            -c src/utilities_functions.c \
            -o utilities_functions.o \
            -I inc         

main.o: src/main.c
	gcc -std=c99 `otf2-config --cflags` \
            -c src/main.c \
            -o main.o \
            -I inc

otf2_converter: main.o utilities_functions.o barectf-platform-linux-fs.o event_callbacks.o barectf.o global_def_callbacks.o attribute_callbacks.o
	gcc main.o utilities_functions.o barectf-platform-linux-fs.o global_def_callbacks.o event_callbacks.o attribute_callbacks.o barectf.o\
            `otf2-config --ldflags` \
            `otf2-config --libs` \
            -pthread \
            -I inc \
            -o otf2_converter
