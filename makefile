#make file - compile source files 

all:		#recordKeeper - compile all
	gcc recordKeeper.c record.c filestream.c utils.c -o rk

recordKeeper:	#recordKeeper - compile recordKeeper.c
	gcc recordKeeper.c -o rk

record:		#recordKeeper - compile record.c
	gcc record.c -o rk

filestream:	#recordKeeper - compile filestream.c
	gcc filestream.c -o rk

utils:		#recordKeeper - compile utils.c
	gcc utils.c -o rk
