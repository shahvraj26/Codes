#Vraj Shah

#Makefile for lab 1-4.  You need to add you name to this file in the comments
# You will need to add a entry to create your zip file

#change the last dependency for each new lab
all:  tags headers lab4 lab4u pSort pIterate pInsert pDeleteSome

#this entry has to change for lab 2 - 4
# NEVER compile .c files with this rule - it lacks needed compile time flags
# There is an entry below that turns .c files into .o files

#lab4 with reliable.o
lab4: lab4.o bits.o input.o memory.o output.o physics.o sim.o linklist.o reliable.o n2.o
	gcc -g -o $@ $^ -lm -L. -lpb -lncurses

#lab4 with unreliable.o
lab4u: lab4.o bits.o input.o memory.o output.o physics.o sim.o linklist.o unreliable.o n2.o
	gcc -g -o $@ $^ -lm -L. -lpb -lncurses

#this is where you create an entry to build yuour zip file
#it will also update with new labs

#Iterate Prototype linked list
pIterate: pIterate.o
	gcc -g -o $@ $^  -lm

#Insert Prototype linked list
pInsert: pInsert.o
	gcc -g -o $@ $^ -lm

#Sort prototype linked list
pSort: pSort.o
	gcc -g -o $@ $^ -lm

#DeleteSome prototype linked list
pDeleteSome: pDeleteSome.o
	gcc -g -o $@ $^ -lm

lab4.zip: makefile README_LAB4 *.c *.h reliable.o unreliable.o n2.o libpb.a
	zip $@ $^
	rm -rf install
	unzip $@ -d install
	make -C install lab4
	make -C install lab4u
	make -C install pIterate
	make -C install pInsert
	make -C install pSort
	make -C install pDeleteSome
	rm -rf install

#this entry stays for C code labs
tags: *.c
	ctags -R .

# this entry stays for C code labs
headers: *.c tags
	headers.sh


# this entry takes care of C files depending on header files
# It has the flags for compiling the c code
# It you don't like makefiles, consider typing the following line a few
# thousand times this semester and reconsider.
# Be sure that this one doesn't get an inserted line break anywhere
%.o:%.c *.h
	gcc -std=c99 -pedantic -Wformat -Wreturn-type -g -c $< -o $@


