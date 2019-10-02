SRCDIR = ./src/
SRCFILENAMES = test.c smoothing_function.c find_amplitude.c
SRCFILES = $(addprefix $(SRCDIR),$(SRCFILENAMES))
program: $(SRCFILES)
	gcc -I./includes -o program $(SRCFILES)

#just linking object files, no compilation
#if object files have changed, link them together
#program: main.o statistics.o
	#gcc -o program main.o statistics.o 
