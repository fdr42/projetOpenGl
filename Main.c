#include "affichage.h"
//#include "SDL/SDL.h"

#define nbpix_x 20
#define nbpix_y 20
#define nbpix_y 20
void tourner(int boule){
  if(boule==1){
    if(snake[boule-1].atourner<snake[boule-1].nb_tour){
      if(snake[boule-1].tab_tour[snake[boule-1].atourner].pos_x>0)
	snake[boule].direction.x+=0.05;
      else
	snake[boule].direction.x-=0.05;
      snake[boule-1].tab_tour[snake[boule-1].atourner].compteur=0;
      snake[boule-1].atourner++;
    }
  }else if(snake[boule-1].atourner<=snake[boule-1].nb_tour ){
    if(snake[boule-1].atourner!=0){
      if(snake[boule-1].tab_tour[snake[boule-1].atourner].pos_x>0)
	snake[boule].direction.x+=0.05;
      else
	snake[boule].direction.x-=0.05;
      snake[boule-1].tab_tour[snake[boule-1].atourner].compteur=0;
    }
    snake[boule-1].atourner++;
  }
 
}

void Animer(){
  usleep(1000);
if(blocs[snake[0].block_x][snake[0].block_y-1].obstacle>0){
	for(int k=0;k<TAILLE_MAX-taille_tir;k++)
 		snake[k].direction.y=0;
if(taille>blocs[snake[0].block_x][snake[0].block_y-1].obstacle){
if(++snake[0].compteur_colli>=40){
blocs[snake[0].block_x][snake[0].block_y-1].obstacle--;
taille--;
snake[0].compteur_colli=0;
}
}
}else{
snake[0].compteur_colli=0;
for(int k=0;k<TAILLE_MAX-taille_tir;k++)
 		snake[k].direction.y=vitesse;
}


	if(blocs[snake[0].block_x][snake[0].block_y-1].bonus && snake[0].y-((snake[0].block_y-1)*6)>2.3 && snake[0].y-((snake[0].block_y-1)*6)<3){
		taille++;
blocs[snake[0].block_x][snake[0].block_y-1].bonus=0;
}


/******************Animation des boules******************/
for(int x=0;x<largeur;x++)
	for(int y=0;y<longueur;y++){
	if(blocs[x][y].compteur>.5)	
		blocs[x][y].rebond=-.01;
else if(blocs[x][y].compteur<0)
blocs[x][y].rebond=.01;
blocs[x][y].compteur+=blocs[x][y].rebond;
}

  float pente;
  float delta_y;
  float delta_x;
  for(int i=0;i<TAILLE_MAX;i++){
    //Les boules qui vont trop loin sont supprimés
if(snake[i].y>6*(longueur-1)){
snake[i].direction.y=0;
snake[i].tir=0;
}
if(snake[i].tir)
	if(blocs[snake[i].block_x][snake[i].block_y-1].obstacle>0){
blocs[snake[i].block_x][snake[i].block_y-1].obstacle--;
snake[i].tir=0;
}
	

/************trouver comment optimiser les deplacements********************
	if(snake[i].atourner>=snake[i].nb_tour && snake[i].nb_tour!=0 ){
		snake[i].atourner=0;
snake[i].nb_tour=0;
}
    *************Mise a jour des positions************************/
    snake[i].y+=snake[i].direction.y;
    snake[i].x+=snake[i].direction.x;
    int test=0;
    if(i>0){
      for(int t=0;t<snake[i-1].atourner;t++){
	if(snake[i-1].tab_tour[t].compteur>-1 && snake[i-1].tab_tour[t].compteur<9){
	  tourne=0;
	  snake[i-1].tab_tour[t].compteur++;
	  test=1;
	}
	
      }
      if(test==0){
	snake[i].direction.x=0;
	tourne=1;
      }
    }
    if(i>0 && i<TAILLE_MAX-taille_tir)
      if(tourne && snake[i-1].tab_tour[snake[i-1].atourner].pos_y-.5<=snake[i].y)
	tourner(i);
    if(snake[i].y+0.4>=(snake[i].block_y)*6)
      snake[i].block_y++;

    snake[i].block_x=snake[i].x/2;
    delta_y=blocs[2][snake[i].block_y].hauteur-blocs[2][snake[i].block_y-1].hauteur;
    delta_x= 6;
    pente=delta_y/delta_x;
    snake[i].z+=pente*snake[i].direction.y;
      
  }



  
  glutPostRedisplay();
}
/******************Fin mise a jour des positions**********************/


        
void click(unsigned char touche, int x, int y){

  //d permet de ourner a droite
  if(touche=='d'){
    if(snake[0].x+0.5<=largeur*2-2.2 && (blocs[(int)((snake[0].x+0.5)/2)][snake[0].block_y-1].obstacle==0 || snake[0].direction.y==0)){
      int nb_tour;	  
      for(int i=0;i<TAILLE_MAX;i++){
	if(i==0)
	  nb_tour=snake[0].nb_tour;
	else
	  nb_tour=snake[i-1].nb_tour;

	snake[i].tab_tour[nb_tour].pos_y=snake[0].y;
	snake[i].tab_tour[nb_tour].pos_x=+0.5;
	snake[i].nb_tour++;
      }
      snake[0].x+=0.5;
    }
  }  
  //Q permet de tourner a gauche
  if(touche=='q'){
         
    if(snake[0].x-0.5>=2.5 && (blocs[(int)((snake[0].x-0.5)/2)][snake[0].block_y-1].obstacle==0
|| snake[0].direction.y==0)){
      int nb_tour;	  
      for(int i=0;i<TAILLE_MAX;i++){
	if(i==0)
	  nb_tour=snake[0].nb_tour;
	else
	  nb_tour=snake[i-1].nb_tour;

	snake[i].tab_tour[nb_tour].pos_y=snake[0].y;
	snake[i].tab_tour[nb_tour].pos_x=-0.5;
	snake[i].nb_tour++;
      }
      snake[0].x-=0.5;
          
    }

  
  }
  //a permet de tirer
  if(touche=='a'){
    //la derniere boule du serpent est alors projetée

      if(taille-1>0){
	snake[TAILLE_MAX-taille_tir]=snake[0];
snake[TAILLE_MAX-taille_tir].tir=1;
	snake[TAILLE_MAX-taille_tir].direction.y+=0.1;
      taille_tir++;
taille--;
      }

    
  }

  
      
  Affichage();
}


int main(int argc, char *argv[]){
if(argc!=4){
printf("veuillez entrer ./troisd <longueur> <largeur> <vitesse> \n");
exit(-1);
}
     longueur=atoi(argv[1]);
    largeur=atoi(argv[2]);
vitesse=atof(argv[3]);
  init_plateau();
  taille=9;
  taille_tir=1;
srand(time(NULL));
  tourne=1;
  init_serpent(snake);
  glutInit(&argc,argv);
  // glutInitDisplayMode(GLUT_RGBA);
  glutInitWindowSize(800,600);
  glutInitWindowPosition(50,50);
  glutCreateWindow("une fenetre");
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glMatrixMode(GL_MODELVIEW);
  glEnable(GL_DEPTH_TEST);
  glutKeyboardFunc(click);
  glutIdleFunc(Animer);
  glutDisplayFunc(Affichage);
  glutMainLoop();



    
  return 0;
}

