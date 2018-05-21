#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#else
#include "GL/gl.h"
#include "GL/glut.h"
#endif

#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include "serpent.h"
typedef struct block{
  int hauteur;
  int bonus;
float obstacle;
float compteur;
float rebond;
}block;
int longueur;
int largeur;

block blocs[100][100];
void dessinBlock(block precedent, block suivant, int pos_largeur,int pos_longueur,int bordure);
void init_plateau();
void dessinPlannete();
