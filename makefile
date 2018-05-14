CC= gcc -Wall

compil:
	gcc -Wall Main.c serpent.c plateau.c affichage.c -o troisd -lGLU -lglut -lGL -lm
