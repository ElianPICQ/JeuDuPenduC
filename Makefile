# Makefile pour compiler le pendu
# make ou make all	pour créer l'executable
# make fclean		pour supprimer l'executable

FILES_C = src/pendu.c src/setMotMystere.c src/ep_displayPendu.c src/ep_putchar.c
FILES_O = ep_pendu.o ep_setMotMystere.o ep_displayPendu.o ep_putchar.o
BINARY_NAME = pendu_exec

all:
	gcc -o $(BINARY_NAME) $(FILES_C)

fclean:
	rm $(BINARY_NAME)
