#include "affichage.h"
#include <string.h>


extern float angle;
extern int rotation;

//FONCTION DESSIN DE CHAINE DE CARACTERES
void drawBitmapText(char *string,float x,float y,float z,int sens) {  
  //On pousse la matrice dans la pile pour ne pas perdre notre point de vue
  glPushMatrix();
  glOrtho(0, 800, 600, 0, -1, 1);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glColor3ub(255,150,0); 
  glRasterPos3f(x, y,z);
  //On dessine chaque caractere
  if(sens)
    for (int c=strlen(string); c >= 0; c--) {
      glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[c]);
    }
  else
    for (int c=0; c <= strlen(string); c++) {
      glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[c]);
    }
  glPopMatrix();
  //On remet la matrice precedente
}


//FONCTION QUI AFFICHE LES DIFFERENTES INFOS EN 2D
void menu(){
  int y=0;
  int z;
  
  if(fini==2){
    drawBitmapText("Vous avez perdu... appuyez sur R pour recommencer",-0.5,0,0,0);
  }
  else{
    char phrase[100];
    int x=score;
    char chiffres[10];
    char retourne[10];
    int a=0;
    while (x != 0){
	chiffres[a] = '0'+x % 10;
	a++;
	x /= 10;
    }
    for(z=a;z>0;z--){
      retourne[y]=chiffres[z-1];
      y++;
    }
    retourne[a] = '\0';
    strcpy(phrase, "Bravo! vous avez gagne ");
    strcat(phrase, retourne);
    strcat(phrase, " points!");	
    drawBitmapText(phrase,-0.7,0,0,0);
    if(niveau !=-1)
      drawBitmapText(" Vous pouvez recommencer (R) ou continuer(C)",-0.8,-0.2,0,0);
    else
      drawBitmapText(" Vous pouvez recommencer (R)",-0.8,-0.2,0,0);
  }
}



void Affichage(){
  int z;
  int x=taille;
  int a=0;
  int y=0;
  char chiffres[10];
  char phrase[25];
  char retourne[4];
  
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  glLoadIdentity();
  gluPerspective(70,(double)640/480,1,1000);
  if(!fini){
    if(rotation == 1){
      gluLookAt(40*sin(angle/(2*M_PI))+20,120*cos(angle/(2*M_PI))+60,20,20,20,10,0,0,1);
      drawBitmapText("Appuyez sur P pour lancer!",-0.4,-0.8,0,0);
    }
    else{
      int obs=0;
      if(blocs[(int)snake[0].x/2][(int)(snake[0].y-8)/8].obstacle!=0)
	obs=1;
      gluLookAt(snake[0].x,snake[0].y-8,snake[0].z+4+obs,snake[0].x,snake[0].y,3+snake[0].z,0,0,1);
    }
    //On dessine le score et le nombre de boules restantes
   
    while (x != 0){
	chiffres[a] = '0'+x % 10;
	a++;
	x /= 10;
    }
    chiffres[a] = '\0';
    drawBitmapText(chiffres,0.8,0.8,0,1);

    x=niveau+1;
    a=0;
    strcpy(phrase, "Vous etes au niveau ");
    if(niveau !=-1){
      while (x != 0){
	chiffres[a] = '0'+x % 10;
	a++;
	x /= 10;
      }
      chiffres[a] = '\0';
      for(z=a;z>0;z--){
	retourne[y]=chiffres[z-1];
	y++;
      }
      retourne[a] = '\0';
      strcat(phrase, retourne);
    }else{
      strcat(phrase, "personnalise");
    }
    drawBitmapText(phrase,-0.3,0.8,0,0);

    a=0;
    x=score; 
    while (x != 0){
	chiffres[a] = '0'+x % 10;
	a++;
	x /= 10;
    }
    chiffres[a] = '\0';
    drawBitmapText(chiffres,-0.8,0.8,0,1);
 
    /***** Dessin des blocs *****/
    for(int j=0;j<longueur-1;j++)
      dessinBlock(blocs[0][j],blocs[0][j+1],0,j*8,1);
    
    for(int j=0;j<longueur-1;j++)
      for(int i=1;i<largeur-1;i++)
	dessinBlock(blocs[i][j],blocs[i][j+1],i*2,j*8,0);
    
    for(int j=0;j<longueur-1;j++)
      dessinBlock(blocs[largeur-1][j],blocs[largeur-1][j+1],2*(largeur-1),j*8,1);

    /***** Dessin du serpent *****/
    dessine_snake(snake,taille);
    
    /***** Dessin de planete *****/
    dessinPlannete();
 
  }else
    menu();
  glFlush();
}


