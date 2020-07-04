EXERCISES	+= emu
CLEAN_FILES	+= emu emu.o $(addsuffix .o, $(basename ${SRCS.emu}))
SRCS.emu	 = # emu.c  ##  for various reasons, this automatically appears
SRCS.emu	+= ram.c registers.c execute_instruction.c print_instruction.c
SRCS.emu	+= # <<< if you add C files, add them to the list here.

# Force only .c -> executable compilations (to preserve dcc analysis).
.SUFFIXES:
.SUFFIXES: .c

emu:			${SRCS.emu}
emu.o:			emu.c emu.h ram.h registers.h
ram.o:			ram.c emu.h ram.h
registers.o:		registers.c registers.h
execute_instruction.o:	execute_instruction.c emu.h
print_instruction.o:	print_instruction.c emu.h
