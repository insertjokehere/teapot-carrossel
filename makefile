all: *.cpp *.h
	g++ -lglut -lGLU -lm -Wall -ggdb *.cpp -o Assignment1
	#create external debug symbols for use with gdb
	#keeps the binary small
	strip Assignment1 --only-keep-debug -o Assignment1.dbg
	strip Assignment1
