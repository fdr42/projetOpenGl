#include "plateau.h"
#include <time.h>
int rotation;
void dessinBlock(block actuel, block suivant, int pos_largeur,int pos_longueur,int bordure){
  /***** Gestion des bonus *****/
  if(actuel.bonus){
    float delta_y=suivant.hauteur-actuel.hauteur;
    GLUquadric* boule =gluNewQuadric();
    glPushMatrix();
    //On se met au milieu du block et on dessine la boule avec z depends du compteur de rebond
    glTranslatef(pos_largeur+1,pos_longueur+3,delta_y/2+actuel.hauteur+actuel.compteur+.3);
    glColor3ub(rand()%255,rand()%255,rand()%255);
    gluSphere(boule,.5,15,15);
    glPopMatrix();	
  }

  /***** Dessin de bordure de blocs *****/
  glLineWidth(3.5);
  glBegin(GL_LINES);
  glColor3ub(255,255,255);

  //Ariere droit
  glVertex3d(2+pos_largeur,0+pos_longueur,actuel.hauteur+bordure+actuel.obstacle/3);
  glVertex3d(2+pos_largeur,0+pos_longueur,0+bordure);
  //Arriere gauche
  glVertex3d(0+pos_largeur,0+pos_longueur,0+bordure);
  glVertex3d(0+pos_largeur,0+pos_longueur,actuel.hauteur+bordure+actuel.obstacle/3);
  //Arriere haut
  glVertex3d(0+pos_largeur,0+pos_longueur,actuel.hauteur+bordure+actuel.obstacle/3);
  glVertex3d(2+pos_largeur,0+pos_longueur,actuel.hauteur+bordure+actuel.obstacle/3);
  //Arriere bas
  glVertex3d(0+pos_largeur,0+pos_longueur,0+bordure);
  glVertex3d(2+pos_largeur,0+pos_longueur,0+bordure);
  //Gauche haut
  glVertex3d(0+pos_largeur,0+pos_longueur,actuel.hauteur+bordure+actuel.obstacle/3);
  glVertex3d(0+pos_largeur,8+pos_longueur,suivant.hauteur+bordure+actuel.obstacle/3);
  //Droite haut
  glVertex3d(2+pos_largeur,0+pos_longueur,actuel.hauteur+bordure+actuel.obstacle/3);
  glVertex3d(2+pos_largeur,8+pos_longueur,suivant.hauteur+bordure+actuel.obstacle/3);
  //Gauche bas
  glVertex3d(0+pos_largeur,0+pos_longueur,0+bordure);
  glVertex3d(0+pos_largeur,8+pos_longueur,0+bordure);
  //Droite bas
  glVertex3d(2+pos_largeur,0+pos_longueur,0+bordure);
  glVertex3d(2+pos_largeur,8+pos_longueur,0+bordure);
  
  //Dessin d'une croix pour les obstacles
  if(actuel.obstacle!=0){
    glVertex3d(pos_largeur,pos_longueur,actuel.hauteur+actuel.obstacle/3);
    glVertex3d(2+pos_largeur,pos_longueur,actuel.hauteur);
    glVertex3d(2+pos_largeur,pos_longueur,actuel.hauteur+actuel.obstacle/3);
    glVertex3d(pos_largeur,pos_longueur,actuel.hauteur);
  } 
  glEnd();

  
  /***** Dessin des face des blocs *****/
  glBegin(GL_QUADS);
  glColor3ub(30,30,30);

  
  glVertex3d(2+pos_largeur,8+pos_longueur,0);
  glVertex3d(2+pos_largeur,0+pos_longueur,0);
  glVertex3d(0+pos_largeur,0+pos_longueur,0);
  glVertex3d(0+pos_largeur,8+pos_longueur,0);


  glVertex3d(2+pos_largeur,0+pos_longueur,actuel.hauteur+bordure+actuel.obstacle/3);
  glVertex3d(2+pos_largeur,8+pos_longueur,suivant.hauteur+bordure+actuel.obstacle/3);
  glVertex3d(0+pos_largeur,8+pos_longueur,suivant.hauteur+bordure+actuel.obstacle/3);
  glVertex3d(0+pos_largeur,0+pos_longueur,actuel.hauteur+bordure+actuel.obstacle/3);
        

  glColor3ub(50,50,50); 

  
  glVertex3d(0+pos_largeur,0+pos_longueur,actuel.hauteur+bordure+actuel.obstacle/3);
  glVertex3d(0+pos_largeur,0+pos_longueur,0);
  glVertex3d(2+pos_largeur,0+pos_longueur,0);
  glVertex3d(2+pos_largeur,0+pos_longueur,actuel.hauteur+bordure+actuel.obstacle/3);

  
  glVertex3d(2+pos_largeur,8+pos_longueur,suivant.hauteur+bordure+actuel.obstacle/3);
  glVertex3d(2+pos_largeur,8+pos_longueur,0+bordure);
  glVertex3d(0+pos_largeur,8+pos_longueur,0+bordure);
  glVertex3d(0+pos_largeur,8+pos_longueur,suivant.hauteur+bordure+actuel.obstacle/3);
  
 
  glVertex3d(0+pos_largeur,8+pos_longueur,suivant.hauteur+bordure+actuel.obstacle/3);
  glVertex3d(0+pos_largeur,8+pos_longueur,0);
  glVertex3d(0+pos_largeur,0+pos_longueur,0);
  glVertex3d(0+pos_largeur,0+pos_longueur,actuel.hauteur+bordure+actuel.obstacle/3);

  
  glVertex3d(2+pos_largeur,0+pos_longueur,actuel.hauteur+bordure+actuel.obstacle/3);
  glVertex3d(2+pos_largeur,0+pos_longueur,0);
  glVertex3d(2+pos_largeur,8+pos_longueur,0);
  glVertex3d(2+pos_largeur,8+pos_longueur,suivant.hauteur+bordure+actuel.obstacle/3);


  glEnd();
  glPopMatrix();
}

void init_plateau(){
  block base;
  int compteur=0;
  int i,j;
  
  for(j=0;j<longueur;j++){
    base.compteur=0;
    base.rebond=.01;
    if(j<2)
      base.hauteur=1;
    else
      base.hauteur=1+rand()%(5);
    for(i=0;i<largeur;i++){
      base.bonus=0;
      blocs[i][j]=base;
    }
  }  
  do{
    compteur=0;
    if(rand()%(8)==3)
      blocs[1+rand()%(largeur-2)][rand()%(longueur-1)].bonus=1;
    for(i=0;i<largeur;i++)
      for(j=0;j<longueur;j++){
	if(blocs[i][j].bonus)	
	  compteur++;
	blocs[i][j].obstacle=0;
      }
  }while(compteur<longueur+niveau);
  
  do{
    compteur=0;
    if(rand()%(10)==5){
      i=2+rand()%(longueur-2);
      if((blocs[2][i-1].obstacle==0 && blocs[2][i-2].obstacle==0 )|| blocs[2][i-2].obstacle==0){
	for(j=1;j<largeur-1;j++){
	  blocs[j][i].obstacle=rand()%(7)+1;
	}
      }
    }
    for(i=0;i<largeur;i++)
      for(j=0;j<longueur;j++)
	if(blocs[i][j].obstacle>0)	
	  compteur++;
  }while(compteur<2*(longueur+largeur-10+niveau));
}


void init_decor(){
  int i;
  planete boule;
  for(i=0;i<100;i++){
    boule.x=-250+rand()%500;
    boule.y=rand()%600;
    boule.z=-50+rand()%200;
    
    boule.direction.x=0;
    boule.direction.y=0;
    boule.direction.z=0;
    
    if(rand()%10>5){
      boule.direction.x=(float)(-10+rand()%20)/160;
      boule.direction.y=(float)(-10+rand()%20)/160;
      boule.direction.z=(float)(-10+rand()%20)/160;
    }
    
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
