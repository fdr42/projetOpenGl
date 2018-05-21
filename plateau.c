#include "plateau.h"
#include <time.h>
void dessinBlock(block actuel, block suivant, int pos_largeur,int pos_longueur,int bordure){
  // dessin des obstacles
  /********Gestion des bonus******/
  if(actuel.bonus){

    float delta_y=suivant.hauteur-actuel.hauteur;
    GLUquadric* boule =gluNewQuadric();
    glPushMatrix();
    //On se met au milieu du block et on dessine la boule avec z depends du compteur de rebond
    glTranslatef(pos_largeur+1,pos_longueur+3,delta_y/2+actuel.hauteur+actuel.compteur+.3);
    glColor3ub(255,0,0);
    gluSphere(boule,.5,30,30);
    glPopMatrix();	
  }
  glBegin(GL_QUADS);


  glColor3ub(255,0,0); //face rouge

  glVertex3d(2+pos_largeur,6+pos_longueur,suivant.hauteur+bordure+actuel.obstacle/3);

  glVertex3d(2+pos_largeur,6+pos_longueur,0+bordure);

  glVertex3d(0+pos_largeur,6+pos_longueur,0+bordure);

  glVertex3d(0+pos_largeur,6+pos_longueur,suivant.hauteur+bordure+actuel.obstacle/3);


  glColor3ub(0+pos_largeur,255,0); //face verte

  glVertex3d(2+pos_largeur,0+pos_longueur,actuel.hauteur+bordure+actuel.obstacle/3);

  glVertex3d(2+pos_largeur,0+pos_longueur,0);

  glVertex3d(2+pos_largeur,6+pos_longueur,0);

  glVertex3d(2+pos_largeur,6+pos_longueur,suivant.hauteur+bordure+actuel.obstacle/3);


  glColor3ub(0+pos_largeur,0+pos_longueur,255); //face bleue

  glVertex3d(0+pos_largeur,0+pos_longueur,actuel.hauteur+bordure+actuel.obstacle/3);

  glVertex3d(0+pos_largeur,0+pos_longueur,0);

  glVertex3d(2+pos_largeur,0+pos_longueur,0);

  glVertex3d(2+pos_largeur,0+pos_longueur,actuel.hauteur+bordure+actuel.obstacle/3);


  glColor3ub(255,255,0); //face jaune

  glVertex3d(0+pos_largeur,6+pos_longueur,suivant.hauteur+bordure+actuel.obstacle/3);

  glVertex3d(0+pos_largeur,6+pos_longueur,0);

  glVertex3d(0+pos_largeur,0+pos_longueur,0);

  glVertex3d(0+pos_largeur,0+pos_longueur,actuel.hauteur+bordure+actuel.obstacle/3);


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
               

  glVertex3d(2+pos_largeur,0+pos_longueur,actuel.hauteur+bordure+actuel.obstacle/3);

  glVertex3d(2+pos_largeur,6+pos_longueur,suivant.hauteur+bordure+actuel.obstacle/3);

  glVertex3d(0+pos_largeur,6+pos_longueur,suivant.hauteur+bordure+actuel.obstacle/3);

  glVertex3d(0+pos_largeur,0+pos_longueur,actuel.hauteur+bordure+actuel.obstacle/3);


  glEnd();
  glPopMatrix();

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



void dessinPlannete(int posx, int posy){
  GLUquadric* boule =gluNewQuadric();
  int transx;
  int i;
  glPushMatrix();
  glTranslatef(20,20,20);
  for(i = 0; i < 100; i++){
    if(i%2){
      transx = -30;
    }
    else{
      transx = 30;
    }
    glTranslatef(transx,15,0);
     glColor3ub(130,130,130);
    gluSphere(boule,5,30,30);
     glColor3ub(150,150,150);
    glutSolidTorus(1, 10, 5, 30);
  }
  glPopMatrix();
  
  
}

