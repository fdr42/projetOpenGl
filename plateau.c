#include "plateau.h"
#include <time.h>
void dessinBlock(block precedent, block suivant, int pos_largeur,int pos_longueur,int bordure){
// dessin des obstacles

if(precedent.bonus){

 float delta_y=suivant.hauteur-precedent.hauteur;
GLUquadric* boule =gluNewQuadric();
glPushMatrix();
 glLoadIdentity();
    gluPerspective(70,(double)740/480,1,1000);
   	 	gluLookAt(snake[0].x,snake[0].y-4,snake[0].z+3,snake[0].x,snake[0].y,snake[0].z,0,0,1);
glTranslatef(pos_largeur+1,pos_longueur+3,delta_y/2+precedent.hauteur+precedent.compteur+.3);
    glColor3ub(255,0,0);
      gluSphere(boule,.5,30,30);
 glPopMatrix();	
}
  glBegin(GL_QUADS);


  glColor3ub(255,0,0); //face rouge

  glVertex3d(2+pos_largeur,6+pos_longueur,suivant.hauteur+bordure+precedent.obstacle/3);

  glVertex3d(2+pos_largeur,6+pos_longueur,0+bordure);

  glVertex3d(0+pos_largeur,6+pos_longueur,0+bordure);

  glVertex3d(0+pos_largeur,6+pos_longueur,suivant.hauteur+bordure+precedent.obstacle/3);


  glColor3ub(0+pos_largeur,255,0); //face verte

  glVertex3d(2+pos_largeur,0+pos_longueur,precedent.hauteur+bordure+precedent.obstacle/3);

  glVertex3d(2+pos_largeur,0+pos_longueur,0);

  glVertex3d(2+pos_largeur,6+pos_longueur,0);

  glVertex3d(2+pos_largeur,6+pos_longueur,suivant.hauteur+bordure+precedent.obstacle/3);


  glColor3ub(0+pos_largeur,0+pos_longueur,255); //face bleue

  glVertex3d(0+pos_largeur,0+pos_longueur,precedent.hauteur+bordure+precedent.obstacle/3);

  glVertex3d(0+pos_largeur,0+pos_longueur,0);

  glVertex3d(2+pos_largeur,0+pos_longueur,0);

  glVertex3d(2+pos_largeur,0+pos_longueur,precedent.hauteur+bordure+precedent.obstacle/3);


  glColor3ub(255,255,0); //face jaune

  glVertex3d(0+pos_largeur,6+pos_longueur,suivant.hauteur+bordure+precedent.obstacle/3);

  glVertex3d(0+pos_largeur,6+pos_longueur,0);

  glVertex3d(0+pos_largeur,0+pos_longueur,0);

  glVertex3d(0+pos_largeur,0+pos_longueur,precedent.hauteur+bordure+precedent.obstacle/3);


  glColor3ub(255,0,255); //face magenta

  glVertex3d(2+pos_largeur,6+pos_longueur,0);

  glVertex3d(2+pos_largeur,0+pos_longueur,0);

  glVertex3d(0+pos_largeur,0+pos_longueur,0);

  glVertex3d(0+pos_largeur,6+pos_longueur,0);
        

  if(((pos_largeur/2)%2==1) && (pos_longueur/6)%2==1)
    glColor3ub(100,100,100); //face blanche
  else if(((pos_largeur/2)%2==0) && (pos_longueur/6)%2==0)
    glColor3ub(100,100,100); //face blanche
  else
    glColor3ub(130,130,130);
  if(bordure)
    glColor3ub(255,255,255);
               

  glVertex3d(2+pos_largeur,0+pos_longueur,precedent.hauteur+bordure+precedent.obstacle/3);

  glVertex3d(2+pos_largeur,6+pos_longueur,suivant.hauteur+bordure+precedent.obstacle/3);

  glVertex3d(0+pos_largeur,6+pos_longueur,suivant.hauteur+bordure+precedent.obstacle/3);

  glVertex3d(0+pos_largeur,0+pos_longueur,precedent.hauteur+bordure+precedent.obstacle/3);


  glEnd();

}

void init_plateau(){

  block base;
   

  for(int j=0;j<longueur;j++){
base.compteur=0;
base.rebond=.01;
    if(j<2)
      base.hauteur=1;
    else
      base.hauteur=rand()%(4);
    for(int i=0;i<largeur;i++){
	base.bonus=0;
      blocs[i][j]=base;
}
  }
int compteur=0;
do{
compteur=0;
if(rand()%(8)==3)
	blocs[1+rand()%(largeur-2)][rand()%(longueur)].bonus=1;
for(int i=0;i<largeur;i++)
	for(int j=0;j<longueur;j++){
		if(blocs[i][j].bonus)	
			compteur++;
blocs[i][j].obstacle=0;
}
		



}while(compteur<20);
do{
compteur=0;
if(rand()%(10)==5){
	int i=2+rand()%(longueur-2);
for(int j=1;j<largeur-1;j++){
blocs[j][i].obstacle=rand()%(6)+1;
}
}
for(int i=0;i<largeur;i++)
	for(int j=0;j<longueur;j++)
		if(blocs[i][j].obstacle>0)	
			compteur++;

}while(compteur<2*(longueur+largeur));
}

