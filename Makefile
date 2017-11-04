#### oldsce  1994/02/16 Hiroyuki Ogasawara (COR.)
####
#### -- UNIX
#CC	= cc
#CFLAGS	= -O -DBIGENDIAN -DUNIX
#CFLAGS	= -O -DLITTLEENDIAN -DUNIX
#PROG	= oldsce
#AWK	= awk
#### -- Human68k
CC	= gcc
CFLAGS	= -O -DBIGENDIAN -DHUMAN -fstrength-reduce -fomit-frame-pointer \
		-finline-functions -fforce-addr -fforce-mem -fcombine-regs
PROG	= oldsce.x
AWK	= jgawk
####

LDFLGA	= -s
OBJ	= main.o run.o opexec.o hexfile.o sysio.o fncsys.o \
		sc_add.o sc_jmp.o sc_ld.o sc_sft.o sc_stack.o sc_io.o sc_mv.o
SCSRC	= sc_add.c sc_jmp.c sc_ld.c sc_sft.c sc_stack.c sc_io.c sc_mv.c

all: $(PROG) syscall.hed

$(PROG): $(OBJ)
	$(CC) $(LDFLAG) -o $@ $(OBJ)

sc_add.o:	sc_add.c reg.h
sc_jmp.o:	sc_jmp.c reg.h
sc_ld.o:	sc_ld.c reg.h
sc_sft.o:	sc_sft.c reg.h
sc_stack.o:	sc_stack.c reg.h
sc_mv.o:	sc_mv.c reg.h
sc_io.o:	sc_io.c reg.h
main.o:		main.c reg.h
hexfile.o:	hexfile.c reg.h
sysio.o:	sysio.c
fncsys.o:	fncsys.c
run.o:		run.c reg.h opexec.h
opexec.o:	opexec.c opexec.h extern.h

%.o::%.c
	$(CC) $(CFLAGS) -c $< -o $@
###
extern.h: $(SCSRC)
	$(AWK) '/^f_/{printf("extern %s);\n", $$1)}' sc_*.c > $@
###
clean:
	rm -f *.o *.bak oldsce
###
lha:
	lha a oldsce00.lzh oldsce.doc oldsce.x \
	sysinit monitor asmsmpl cmd type ls saikoro asm.hed syscall.hed \
	makefile main.c hexfile.c sysio.c fncsys.c run.c opexec.c \
	sc_add.c sc_jmp.c sc_ld.c sc_sft.c sc_stack.c sc_mv.c sc_io.c \
	reg.h opexec.h makesys.pl
###
syscall.hed: sysinit
	jperl makesys.pl > systemp.tmp
	rm -f syscall.bak
	mv syscall.hed syscall.bak
	mv systemp.tmp syscall.hed
