#Vraj Shah

#Makefile for lab 6.  You need to add you name to this file in the comments
# You will need to add a entry to create your zip file

#change the last dependency for each new lab
all:  tags headers exptest mtest lab6

# the three drivers for lab 6

exptest: exptest.o expand.s ex_shim.o
	gcc -g -o $@ $^

mtest: mtest.o expand.s middle.s ex_shim.o m_shim.o print.o
	gcc -g -o $@ $^

lab6: lab6.o expand.s middle.s search.s ex_shim.o m_shim.o s_shim.o print.o
	gcc -g -o $@ $^

#this is where you create an entry to build yuour zip file
#it will also update with new labs
# YOU MUST SELF-TEST THE ABOVE TRAGETS OR YOUR LAB IS LATE

lab6.zip: makefile README_LAB6 *.c *.h *.s *.o
	zip $@ $^
	rm -rf install
	unzip $@ -d install
	make -C install lab6
	make -C install mtest
	make -C install exptest
	rm -rf install

# used to create the zip of files for lab5 - this is not what students
# build, it's what students consume.

l6files.zip: makefile shims.h exptest.c mtest.c lab6.c *.out.txt s_shim.o m_shim.o ex_shim.o
	zip $@ $^

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


