#include "plateau.h"
#include <time.h>
int rotation;
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
    gluSphere(boule,.5,15,15);
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
      base.hauteur=1+rand()%(5);
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
		



  }while(compteur<longueur);
  do{
    compteur=0;
    if(rand()%(10)==5){
      int i=2+rand()%(longueur-2);
      for(int j=1;j<largeur-1;j++){
	blocs[j][i].obstacle=rand()%(8)+1;
      }
    }
    for(int i=0;i<largeur;i++)
      for(int j=0;j<longueur;j++)
	if(blocs[i][j].obstacle>0)	
	  compteur++;

  }while(compteur<2*(longueur+largeur));

}
void init_decor(){
for(int i=0;i<100;i++){
planete boule;
boule.x=-250+rand()%500;
boule.y=rand()%600;
boule.z=-50+rand()%200;

boule.direction.x=0;
boule.direction.y=0;
boule.direction.z=0;

boule.direction.x=(-40+rand()%80)/50;
boule.direction.y=(-40+rand()%80)/50;
boule.direction.z=(-40+rand()%80)/50;

boule.r=rand()%255;
boule.g=rand()%255;
boule.b=rand()%255;
boule.taille=rand()%10;

boule.anneau=0;
if(rand()%10>4)
boule.anneau=1;
	
decor[i]=boule;

}


}

void dessinPlannete(){
  GLUquadric* boule =gluNewQuadric();
  int i;
 
  for(i = 0; i <100; i++){
 glPushMatrix();
    glTranslatef(decor[i].x,decor[i].y,decor[i].z);
    glColor3ub(decor[i].r,decor[i].g,decor[i].b);
    gluSphere(boule,decor[i].taille,10,20);
   glColor3ub(decor[i].g,decor[i].b,decor[i].r);
if(decor[i].anneau==1)
 glutSolidTorus(1, decor[i].taille+5, 8, 10);
if(!rotation){
decor[i].x+=decor[i].direction.x;
decor[i].y+=decor[i].direction.y;
decor[i].z+=decor[i].direction.z;
}
  glPopMatrix();
   
  }

  
}
