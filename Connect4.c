#include   <conio.h>
#include   <conio.c>
#include   <ctype.h>
#include   <stdio.h>
#include  <unistd.h>
#include    <time.h>
#include    <math.h>
#include <windows.h>

#define COLUMNAS   7
#define FILAS      6
#define JUGADOR    1
#define COMPUTADOR 2
#define CAIDA  50000
#define POSXINI   41
#define POSYINI   12
#define MAXFICHAS 21

#define DPX      219
#define PXS      223
#define PXI      220
#define BLK      ' '

#define DERECHA   77
#define IZQUIERDA 75
#define ENTER     13
#define ESC       27
#define BACKSPACE  8

int randrange(int,int);
void setcolor(int,int);
void set_unicolor(int);
void tablero(int,int);
void fichas(int,int,int,int);
void winfichas(int,int,int,int);
void defaultcolor();
void game(int,int,int);
int colorsort(char);
void comite(int,int);
void presenta(int,int);
void colordispo(int,int);
int disponible(int[][FILAS],int);
void insertarficha(int,int,int);
int iacomputador(int[][FILAS],int*);
void algcomputador(int[][FILAS],int);
int algvictoria(int[][FILAS],int,int);
void titlescreen(int,int);

/**Main, donde se inicializa una semilla randomizada y se determina el modo de juego y el color del(os) jugador(es), siendo en el caso
  de un juego en solitario se toma un color aleatorio para el computador que sea diferente del tablero LIGHTBLUE y del color del jugador*/

int main(){
   keybd_event(VK_MENU, 0, 0, 0);
   keybd_event(VK_RETURN, 0, 0, 0);
   keybd_event(VK_RETURN, 0, KEYEVENTF_KEYUP, 0);
   keybd_event(VK_MENU, 0, KEYEVENTF_KEYUP, 0);
   srand(time(NULL));
   char tecla;
   comite(58,7);
   presenta(42,31);
   defaultcolor();
   usleep(3600000);
   system("cls");
   do{
      int players = 1;
      int color[2] = {0};
      int cpucolor;
      char teclacolor;
      do{
         _setcursortype(0);
         system("cls");
         titlescreen(34,18);
         gotoxy(60,27);
         printf("Presione Enter para jugar en solitario");
         gotoxy(57,28);
         printf("Presione BACKSPACE para jugar en multijugador");
         gotoxy(67,17);
         printf("Presione ESC para salir");
         tecla = getch();
      }while(tecla != ENTER && tecla != ESC && tecla != BACKSPACE);
      if(tecla != ESC){
         if(tecla == BACKSPACE){
            players = 2;
         }
         for(int ind = 1; ind <= players; ind++){
            do{
               system("cls");
               gotoxy(67,12);
               printf("Jugador %d Escoja su color: ", ind);
               colordispo(41,16);
               teclacolor = getch();
            }while(teclacolor != 'p' &&  teclacolor != 'S'  &&
                   teclacolor != 'b'  && teclacolor != 'g'  &&
                   teclacolor != 'c'  && teclacolor != 'r'  &&
                   teclacolor != 'B'  && teclacolor != 'g'  &&
                   teclacolor != 'm'  && teclacolor != 'Y'  &&
                   teclacolor != 'R' && teclacolor != 'M' &&
                   teclacolor != 'C' && teclacolor != 'G' &&
                   teclacolor != 'w'  && teclacolor != 'y');
            color[ind-1] = colorsort(teclacolor);
            if(color[ind-1] == color[ind-2]){
               ind--;
            }
         }
         _setcursortype(0);
         if(players == 1){
            do{
               cpucolor = randrange(WHITE,BLUE);
            }while(cpucolor == color[0] || cpucolor == LIGHTBLUE);
            game(color[0], cpucolor, players);
         }
         else{
            game(color[0], color[1], players);
         }
      }
   }while(tecla != ESC);
   system("cls");
return 0;}

/**Función trabajada en clase que toma como argumentos un límite superior y un límite inferior para retornar un número pseudo-aleatorio
  dentro del rango que estos abarcan*/

int randrange(int limsup, int liminf){
return rand()%(limsup - liminf+1) + liminf;}

/**Función que toca como argumento un char y retorna el valor correspondiente asignado como color para el display gráfico que se hace
  en el main a la hora de escoger color de fichas*/

int colorsort(char eleccion){
   if(eleccion == 'p'){
      return LIGHTGRAY;
   }
   else if(eleccion == 'S'){
      return DARKGRAY;
   }
   else if(eleccion == 'b'){
      return BLUE;
   }
   else if(eleccion == 'Y'){
      return YELLOW;
   }
   else if(eleccion == 'g'){
      return GREEN;
   }
   else if(eleccion == 'G'){
      return LIGHTGREEN;
   }
   else if(eleccion == 'r'){
      return RED;
   }
   else if(eleccion == 'R'){
      return LIGHTRED;
   }
   else if(eleccion == 'm'){
      return MAGENTA;
   }
   else if(eleccion == 'M'){
      return LIGHTMAGENTA;
   }
   else if(eleccion == 'c'){
      return CYAN;
   }
   else if(eleccion == 'C'){
      return LIGHTCYAN;
   }
   else if(eleccion == 'y'){
      return BROWN;
   }
   else if(eleccion == 'w'){
      return WHITE;
   }
}

/**Función trabajada en clase que toma como argumentos dos enteros, tratados como MACROS del archivo conio.h y establece un color de fondo de texto
  y un color de fuente*/

void setcolor(int ct,int cf){
   textcolor(ct);
   textbackground(cf);
}

void set_unicolor(int color){
   textcolor(color);
   textbackground(color);
}

/**Función trabajada en clase que no tomar argumentos y convierte el color del color de fondo y fuente de texto a los estándar de consola*/

void defaultcolor(){
   textcolor(LIGHTGRAY);
   textbackground(BLACK);
}

/**Función gráfica que toma como argumentos una posición x,y y muestra los posibles colores que se pueden tomar de cada ficha para la partida junto
  al código char que se debe escoger para obtenerlo*/

void colordispo(int posx, int posy){
   fichas(posx,posy,BLACK,BLUE);
   for(int ind = GREEN; ind <= LIGHTGRAY; ind++){
      fichas(posx+12*ind - 12,posy,BLACK,ind);
   }
   for(int ind = DARKGRAY; ind <= WHITE; ind++){
      if(ind < LIGHTBLUE){
         fichas(posx+(ind-LIGHTGRAY)*12 - 12,posy+6,BLACK,ind);
      }
      else if(ind > LIGHTBLUE){
         fichas(posx+(ind-LIGHTGRAY-1)*12 - 12,posy+6,BLACK,ind);
      }
   }
   gotoxy(posx,posy+4);
   printf("(b)lue");
   gotoxy(posx,posy+10);
   printf("(S)teel");
   gotoxy(posx+10,posy+4);
   printf("(g)reen");
   gotoxy(posx+10,posy+10);
   printf("(G)reen");
   gotoxy(posx+24,posy+4);
   printf("(c)yan");
   gotoxy(posx+24,posy+10);
   printf("(C)yan");
   gotoxy(posx+37,posy+4);
   printf("(r)ed");
   gotoxy(posx+37,posy+10);
   printf("(R)ed");
   gotoxy(posx+47,posy+4);
   printf("(m)agenta");
   gotoxy(posx+47,posy+10);
   printf("(M)agenta");
   gotoxy(posx+60,posy+4);
   printf("(y)ellow");
   gotoxy(posx+60,posy+10);
   printf("(Y)ellow");
   gotoxy(posx+71,posy+4);
   printf("(p)latinum");
   gotoxy(posx+72,posy+10);
   printf("(w)hite");
}

/**Función que toma dos argumentos, uno de la matriz que sirve de tablero y otro que representa la fila proporcionada.
  Explora la matriz en la fila dada hasta encontrar el último espacio vacío, de no haber uno se retorna el valor inicial,
  -1*/

int disponible(int matriz[][FILAS],int fila){
   int disponibles = -1;
   for(int ind = 0; ind < FILAS; ind++){
      if(!matriz[fila][ind]){
         disponibles = ind;
      }
   }
return disponibles;}

/**Función gráfica que toma como argumentos la posición en FILA que toma la una ficha dada, el espacio en COLUMNA que ocupa y
  el color de la ficha a insertar. Corre un bucle donde muestra la ficha caer gráficamente hasta su puesto dado a una velocidad
  de 500 milisegundos e imprime una ficha negra en la posición previa cada vez que el bucle aumenta para dar la imagen que cae*/

void insertarficha(int posicion,int espacio,int color){
   for(int ind = 0; ind <= espacio; ind++){
      fichas(POSXINI+10+(9*posicion),POSYINI+(4*ind+1),LIGHTBLUE,color);
      if(ind != espacio){
         usleep(CAIDA);
         fichas(POSXINI+10+(9*posicion),POSYINI+(4*ind+1),LIGHTBLUE,BLACK);
      }
   }
   defaultcolor();
}

/**Función en la cual se evalúan todas las posibles combinaciones en las cuales se pudiese completar un Connect 4, tomando como
  argumentos la matriz y un puntero hacia la ubicación de la fila donde, si encuentra una posible combinación, indica al computador
  a jugar*/

int iacomputador(int matriz[][FILAS], int *fila){
   int jugadores[2] = { JUGADOR, COMPUTADOR };
   int dirs[4][2] = { {1,0}, {0,1}, {1,1}, {1,-1} };

   for(int p = 0; p < 2; p++){
      int actual = jugadores[p];

      for(int x = 0; x < COLUMNAS; x++){
         for(int y = 0; y < FILAS; y++){

            if(matriz[x][y] != actual){
               continue;
            }

            for(int d = 0; d < 4; d++){
               int dx = dirs[d][0];
               int dy = dirs[d][1];

               for(int offset = -3; offset <= 0; offset++){
                  int cx = x + offset * dx;
                  int cy = y + offset * dy;
                  int count = 0;
                  int huecoX = -1;
                  int huecoY = -1;

                  for(int k = 0; k < 4; k++){
                     int nx = cx + k * dx;
                     int ny = cy + k * dy;

                     if(nx < 0 || nx >= COLUMNAS || ny < 0 || ny >= FILAS){
                        count = -1;
                        break;
                     }

                     if(matriz[nx][ny] == actual){
                        count++;
                     }
                     else if(matriz[nx][ny] == 0){
                        huecoX = nx;
                        huecoY = ny;
                     }
                     else{
                        count = -1;
                        break;
                     }
                  }

                  if(count == 3 && huecoX != -1 && disponible(matriz, huecoX) == huecoY){
                     *fila = huecoX;
                     return 1;
                  }
               }
            }
         }
      }
   }

   return 0;
}



/**Función donde se determina dónde jugará el ordenador, que toma como argumento la matriz y el color del computador, para
  Señalar una fila indicada por la función anterior, sino juega una randomizada siempre y cuando esté alguna disponible*/

void algcomputador(int matriz[][FILAS], int color){
   int espacio, posicion;
   if(!iacomputador(matriz,&posicion)){
      do{
         posicion = randrange(COLUMNAS-1,0);
      }while(disponible(matriz,posicion) == -1);
   }
   espacio = disponible(matriz,posicion);
   matriz[posicion][espacio] = COMPUTADOR;
   insertarficha(posicion,espacio,color);
}

/**Funcion que toma como argumentos la matriz, el jugador que se evalua si gano y el color de su ficha, para el caso de que
  alguien gano entonces*/

int algvictoria(int matriz[][FILAS], int jugador){
   int dirs[4][2] = { {1,0}, {0,1}, {1,1}, {1,-1} };

   for(int x = 0; x < COLUMNAS; x++){
      for(int y = 0; y < FILAS; y++){

         if(matriz[x][y] != jugador){
            continue;
         }

         for(int d = 0; d < 4; d++){
            int dx = dirs[d][0];
            int dy = dirs[d][1];

            for(int offset = -3; offset <= 0; offset++){
               int cx = x + offset * dx;
               int cy = y + offset * dy;
               int ok = 1;

               for(int k = 0; k < 4; k++){
                  int nx = cx + k * dx;
                  int ny = cy + k * dy;

                  if(nx < 0 || nx >= COLUMNAS || ny < 0 || ny >= FILAS){
                     ok = 0;
                     break;
                  }

                  if(matriz[nx][ny] != jugador){
                     ok = 0;
                     break;
                  }
               }

               if(ok){
                  return 1;
               }
            }
         }
      }
   }

   return 0;
}



/**Funcion central que toma el color del jugador 1, 2 y el modo de juego, y administra las anteriores funciones, repitiendose hasta
  que alguien gane o hasta que el tablero se llene*/


void game(int color, int cpucolor, int gamemode){
   int matriz[COLUMNAS][FILAS] = {0};
   int posicion = 0;
   char tecla;
   int contador = 0;
   system("cls");
   tablero(POSXINI,POSYINI);
   if(gamemode == 1){
      do{
         fichas(POSXINI+10+(posicion*9),POSYINI-4,BLACK,color);
         do{
            tecla = getch();
         }while (tecla != DERECHA && tecla != IZQUIERDA &&
           tecla != ENTER);
         if(tecla == DERECHA && posicion < 6){
            fichas(POSXINI+10+(posicion*9),POSYINI-4,BLACK,BLACK);
            posicion++;
         }
         else if(tecla == IZQUIERDA && posicion > 0){
            fichas(POSXINI+10+(posicion*9),POSYINI-4,BLACK,BLACK);
            posicion--;
         }
         else if(tecla == ENTER){
            int espacio = disponible(matriz,posicion);
            if(espacio != -1){
               matriz[posicion][espacio] = JUGADOR;
               insertarficha(posicion,espacio,color);
               if(algvictoria(matriz,JUGADOR,color) || algvictoria(matriz,COMPUTADOR,cpucolor)){
                  break;
               }
               usleep(400000);
               algcomputador(matriz,cpucolor);
               contador++;
            }
         }
      }while(!algvictoria(matriz, JUGADOR,color) && !algvictoria(matriz,COMPUTADOR,cpucolor) && contador < MAXFICHAS);
   }
   if(gamemode == 2){
      int colors[2] = {color,cpucolor};
      do{
         for(int turno = JUGADOR; turno <= COMPUTADOR; turno++){
            fichas(POSXINI+10+(posicion*9),POSYINI-4,BLACK,colors[turno-1]);
            do{
               tecla = getch();
            }while (tecla != DERECHA && tecla != IZQUIERDA &&
              tecla != ENTER);
            if(tecla == DERECHA){
               if(posicion < COLUMNAS-1){
                  fichas(POSXINI+10+(posicion*9),POSYINI-4,BLACK,BLACK);
                  posicion++;
               }
               else if(posicion == COLUMNAS-1){
                  fichas(POSXINI+10+(posicion*9),POSYINI-4,BLACK,BLACK);
                  posicion = 0;
               }
               turno--;
            }
            if(tecla == IZQUIERDA){
               if(posicion > 0){
                  fichas(POSXINI+10+(posicion*9),POSYINI-4,BLACK,BLACK);
                  posicion--;
               }
               else if(posicion == 0){
                  fichas(POSXINI+10+(posicion*9),POSYINI-4,BLACK,BLACK);
                  posicion = COLUMNAS-1;
               }
               turno--;
            }
            if(tecla == ENTER){
               int espacio = disponible(matriz,posicion);
               if(espacio != -1){
                  matriz[posicion][espacio] = turno;
                  insertarficha(posicion,espacio,colors[turno-1]);
                  fichas(POSXINI+10+(posicion*9),POSYINI-4,BLACK,BLACK);
                  posicion = 0;
                  if(algvictoria(matriz,JUGADOR,colors[turno-1]) || algvictoria(matriz,COMPUTADOR,colors[turno-1])){
                     break;
                  }
                  contador++;
               }
               else{
                  turno--;
               }
            }
         }
      }while(!algvictoria(matriz, JUGADOR,color) && !algvictoria(matriz,COMPUTADOR,cpucolor) && contador < MAXFICHAS*2 - 1);
   }

   if(algvictoria(matriz, JUGADOR, color)){
      gotoxy(90,4);
      printf("J U G A D O R 1  G A N A");
   }
   if(algvictoria(matriz, COMPUTADOR, cpucolor) && gamemode == 1){
      gotoxy(90,4);
      printf("C O M P U T A D O R  G A N A");
   }
   if(algvictoria(matriz, COMPUTADOR, cpucolor) && gamemode == 2){
      gotoxy(90,4);
      printf("J U G A D O R 2  G A N A");
   }
   if(contador == MAXFICHAS-1 || gamemode == 1 == MAXFICHAS*2 - 5){
      gotoxy(94,4);
      printf("E M P A T E");
   }
   sleep(3);
   char fintecla;
   do{
      gotoxy(90,5);
      printf("Presione Enter Para salir");
      tecla = getch();
   }while(tecla != ENTER);
return;}

/**Funcion grafica que muestra las fichas cuando estan conectadas, vacias por dentro*/

void winfichas(int posx, int posy, int cf, int ct){
   setcolor(ct,cf);
   gotoxy(posx,posy);
   printf("  %c%c%c",PXI,PXI,PXI);
   gotoxy(posx,posy+1);
   printf("%c",PXI);
   setcolor(BLACK,ct);
   printf("%c",PXI);
   for(int ind = 0; ind < 3; ind++){
      printf("%c",DPX);
   }
   printf("%c",PXI);
   setcolor(ct,cf);
   printf("%c",PXI);
   gotoxy(posx,posy+2);
   printf("%c",DPX);
   setcolor(BLACK,ct);
   for(int ind = 0; ind < 5; ind++){
      printf("%c",DPX);
   }
   setcolor(ct,cf);
   printf("%c",DPX);
   gotoxy(posx,posy+3);
   printf(" %c",PXS);
   setcolor(BLACK,ct);
   printf("%c%c%c",PXS,PXS,PXS);
   setcolor(ct,cf);
   printf("%c",PXS);
   defaultcolor();
}

/**Funcion grafica que muestra las fichas*/

void fichas(int posx, int posy, int cf, int ct){
   setcolor(ct,cf);
   gotoxy(posx,posy);
   printf("  %c%c%c",PXI,PXI,PXI);
   gotoxy(posx,posy+1);
   printf("%c",PXI);
   for(int ind = 0; ind < 5; ind++){
      printf("%c",DPX);
   }
   printf("%c",PXI);
   gotoxy(posx,posy+2);
   for(int ind = 0; ind < 7; ind++){
      printf("%c",DPX);
   }
   gotoxy(posx,posy+3);
   printf(" %c%c%c%c%c", PXS,DPX,DPX,DPX,PXS);
   defaultcolor();
}

void tablero(int posx, int posy){
   setcolor(LIGHTBLUE,BLACK);
   gotoxy(posx,posy);
   printf("    %c%c",PXI,PXI);
   for(int ind = 0; ind < 69; ind++){
      printf("%c",DPX);
   }
   printf("%c%c",PXI,PXI);
   gotoxy(posx,posy+1);
   printf(" %c",PXI);
   for(int ind = 0; ind < 77; ind++){
      printf("%c",DPX);
   }
   printf("%c",PXI);
   gotoxy(posx,posy+2);
   printf("%c",PXI);
   for(int ind = 0; ind < 79; ind++){
      printf("%c",DPX);
   }
   printf("%c",PXI);
   for(int ind = 0; ind < 23; ind++){
      gotoxy(posx,posy+ind+3);
      for(int indint = 0; indint < 81; indint++){
         printf("%c",DPX);
      }
   }
   gotoxy(posx,posy+25);
   printf("%c",PXS);
   for(int ind = 0; ind < 79; ind++){
      printf("%c",DPX);
   }
   printf("%c",PXS);
   gotoxy(posx,posy+26);
   printf(" %c",PXS);
   for(int ind = 0; ind < 77; ind++){
      printf("%c",DPX);
   }
   printf("%c",PXS);
   gotoxy(posx,posy+27);
   printf("    %c%c",PXS,PXS);
   for(int ind = 0; ind < 69; ind++){
      printf("%c",DPX);
   }
   printf("%c%c",PXS,PXS);
   //ESPACIOS DE FICHA
   for(int indext = 0; indext < 6; indext++){
      fichas(posx+10,posy+4*indext+1,LIGHTBLUE,BLACK);
      for(int indint = 1; indint < 7; indint++){
         fichas(posx+10+9*indint,posy+4*indext+1,LIGHTBLUE,BLACK);
      }
   }
   defaultcolor();
return;}

/**Funcion grafica que muestra la pantalla de inicio*/

void titlescreen(int px, int py){
   int color;
   do{
      color = randrange(WHITE,BLUE);
   }while(color == LIGHTBLUE || color == WHITE);
   setcolor(WHITE,BLACK);
   //LETRA C
   gotoxy(px,py);
   printf("   ");
   for(int ind = 0; ind < 5; ind++){
      printf("%c",PXI);
   }
   gotoxy(px,py+1);
   printf(" %c",PXI);
   for(int ind = 0; ind < 7; ind++){
      printf("%c",DPX);
   }
   printf("%c",PXI);
   for(int indext = 0; indext < 4; indext++){
      gotoxy(px,py+2+indext);
      for(int ind = 0; ind < 11; ind++){
         printf("%c",DPX);
      }
   }
   gotoxy(px,py+6);
   printf("%c",PXS);
   for(int ind = 0; ind < 9; ind++){
      printf("%c",DPX);
   }
   printf("%c",PXS);
   gotoxy(px,py+7);
   printf("  %c",PXS);
   for(int ind = 0; ind < 5; ind++){
      printf("%c",DPX);
   }
   printf("%c",PXS);
   //LETRA O
   gotoxy(px+12,py+1);
   printf("   ");
   for(int ind = 0; ind < 5; ind++){
      printf("%c",PXI);
   }
   gotoxy(px+12,py+2);
   printf(" %c",PXI);
   for(int ind = 0; ind < 7; ind++){
      printf("%c",DPX);
   }
   printf("%c",PXI);
   for(int indext = 0; indext < 2; indext++){
      gotoxy(px+12,py+3+indext);
      for(int ind = 0; ind < 11; ind++){
         printf("%c",DPX);
      }
   }
   gotoxy(px+12,py+5);
   printf("%c",PXS);
   for(int ind = 0; ind < 9; ind++){
      printf("%c",DPX);
   }
   printf("%c",PXS);
   gotoxy(px+12,py+6);
   printf("  %c",PXS);
   for(int ind = 0; ind < 5; ind++){
      printf("%c",DPX);
   }
   printf("%c",PXS);
   //Centro entre la C y O
   fichas(px+2,py+2,WHITE,color);
   fichas(px+14,py+2,WHITE,color);
   gotoxy(px+9,py+3);
   setcolor(color,WHITE);
   printf("%c%c",PXI,PXI);
   setcolor(color,BLACK);
   printf("%c",PXI);
   setcolor(color,WHITE);
   printf("%c%c",PXI,PXI);
   gotoxy(px+9,py+4);
   printf("%c%c%c%c%c",DPX,DPX,DPX,DPX,DPX);
   setcolor(WHITE,BLACK);
   //Letra N
   gotoxy(px+24,py+1);
   printf("%c%c%c     %c%c%c",PXI,PXI,PXI,PXI,PXI,PXI);
   gotoxy(px+24,py+2);
   for(int ind = 0; ind < 4; ind++){
      printf("%c",DPX);
   }
   printf("%c   %c%c%c",PXI,DPX,DPX,DPX);
   gotoxy(px+24,py+3);
   for(int ind = 0; ind < 6; ind++){
      printf("%c",DPX);
   }
   printf("%c %c%c%c",PXI,DPX,DPX,DPX);
   gotoxy(px+24,py+4);
   printf("%c%c%c %c",DPX,DPX,DPX,PXS);
   for(int ind = 0; ind < 6; ind++){
      printf("%c",DPX);
   }
   gotoxy(px+24,py+4);
   printf("%c%c%c %c",DPX,DPX,DPX,PXS);
   for(int ind = 0; ind < 6; ind++){
      printf("%c",DPX);
   }
   gotoxy(px+24,py+5);
   printf("%c%c%c   %c",DPX,DPX,DPX,PXS);
   for(int ind = 0; ind < 4; ind++){
      printf("%c",DPX);
   }
   gotoxy(px+24,py+6);
   printf("%c%c%c     %c%c%c",DPX,DPX,DPX,PXS,DPX,DPX);
   //Letra N
   gotoxy(px+36,py+1);
   printf("%c%c%c     %c%c%c",PXI,PXI,PXI,PXI,PXI,PXI);
   gotoxy(px+36,py+2);
   for(int ind = 0; ind < 4; ind++){
      printf("%c",DPX);
   }
   printf("%c   %c%c%c",PXI,DPX,DPX,DPX);
   gotoxy(px+36,py+3);
   for(int ind = 0; ind < 6; ind++){
      printf("%c",DPX);
   }
   printf("%c %c%c%c",PXI,DPX,DPX,DPX);
   gotoxy(px+36,py+4);
   printf("%c%c%c %c",DPX,DPX,DPX,PXS);
   for(int ind = 0; ind < 6; ind++){
      printf("%c",DPX);
   }
   gotoxy(px+36,py+4);
   printf("%c%c%c %c",DPX,DPX,DPX,PXS);
   for(int ind = 0; ind < 6; ind++){
      printf("%c",DPX);
   }
   gotoxy(px+36,py+5);
   printf("%c%c%c   %c",DPX,DPX,DPX,PXS);
   for(int ind = 0; ind < 4; ind++){
      printf("%c",DPX);
   }
   gotoxy(px+36,py+6);
   printf("%c%c%c     %c%c%c",DPX,DPX,DPX,PXS,DPX,DPX);
   //Letra E
   gotoxy(px+48,py+1);
   printf(" ");
   for(int ind = 0; ind < 9; ind++){
      printf("%c",PXI);
   }
   gotoxy(px+48,py+2);
   for(int ind = 0; ind < 11; ind++){
      printf("%c",DPX);
   }
   gotoxy(px+48,py+3);
   printf("%c%c%c",DPX,DPX,DPX);
   for(int ind = 0; ind < 8; ind++){
      printf("%c",PXI);
   }
   gotoxy(px+48,py+4);
   for(int ind = 0; ind < 11; ind++){
      printf("%c",DPX);
   }
   gotoxy(px+48,py+5);
   printf("%c%c%c",DPX,DPX,DPX);
   for(int ind = 0; ind < 8; ind++){
      printf("%c",PXI);
   }
   gotoxy(px+48,py+6);
   printf("%c",PXS);
   for(int ind = 0; ind < 9; ind++){
      printf("%c",DPX);
   }
   printf("%c",PXS);
   //LETRA O
   gotoxy(px+60,py+1);
   printf("   ");
   for(int ind = 0; ind < 5; ind++){
      printf("%c",PXI);
   }
   gotoxy(px+60,py+2);
   printf(" %c",PXI);
   for(int ind = 0; ind < 7; ind++){
      printf("%c",DPX);
   }
   printf("%c",PXI);
   for(int indext = 0; indext < 2; indext++){
      gotoxy(px+60,py+3+indext);
      for(int ind = 0; ind < 11; ind++){
         printf("%c",DPX);
      }
   }
   gotoxy(px+60,py+5);
   printf("%c",PXS);
   for(int ind = 0; ind < 9; ind++){
      printf("%c",DPX);
   }
   printf("%c",PXS);
   gotoxy(px+60,py+6);
   printf("  %c",PXS);
   for(int ind = 0; ind < 5; ind++){
      printf("%c",DPX);
   }
   printf("%c",PXS);
   //Letra T
   gotoxy(px+72,py+1);
   printf(" ");
   for(int ind = 0; ind < 9; ind++){
      printf("%c",PXI);
   }
   gotoxy(px+72,py+2);
   for(int ind = 0; ind < 11; ind++){
      printf("%c",DPX);
   }
   for(int ind = 0; ind < 4; ind++){
      gotoxy(px+72,py+3+ind);
      printf("    %c%c%c", DPX, DPX, DPX);
   }
   //Centro entre la C y T
   fichas(px+62,py+2,WHITE,color);
   gotoxy(px+69,py+3);
   setcolor(color,WHITE);
   printf("%c%c",PXI,PXI);
   setcolor(color,BLACK);
   printf("%c%c%c%c%c",PXI,PXI,PXI,PXI,PXI);
   gotoxy(px+69,py+4);
   printf("%c%c%c%c%c%c%c",DPX,DPX,DPX,DPX,DPX,DPX,DPX);
   //Numero 4
   gotoxy(px+84,py-3+1);
   printf("%c%c%c     %c%c%c",PXI,DPX,DPX,DPX,DPX,PXI);
   for(int ind = 0; ind < 4; ind++){
      gotoxy(px+84,py-1+ind);
      if(ind != 2){
         printf("%c%c%c     %c%c%c",DPX,DPX,DPX,DPX,DPX,DPX);
      }
      else{
         printf("%c%c%c%c%c%c%c%c%c%c%c",DPX,DPX,DPX,PXI,PXI,PXI,PXI,PXI,DPX,DPX,DPX);
      }
   }
   gotoxy(px+84,py+2);
   printf("%c",PXS);
   for(int ind = 0; ind < 9; ind++){
      printf("%c",DPX);
   }
   for(int ind = 0; ind < 4; ind++){
      gotoxy(px+84,py+3+ind);
      printf("        %c%c%c",DPX,DPX,DPX);
   }
   gotoxy(px+84,py+7);
   printf("        %c%c%c",DPX,DPX,PXS);
   defaultcolor();
}

void comite(int px, int py)
{
    gotoxy(px + 14, py + 0);
    setcolor(BLACK, WHITE);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", PXS, PXS, PXS, BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK, PXS, PXS, PXS);

    gotoxy(px + 10, py + 1);
    setcolor(BLACK, WHITE);
    printf("%c%c%c%c%c", PXS, PXS, BLK, BLK, BLK);
    setcolor(WHITE, CYAN);
    printf("%c%c%c%c%c%c%c", PXS, PXS, PXS, DPX, BLK, BLK, BLK);
    set_unicolor(BROWN);
    printf("%c", BLK);
    set_unicolor(CYAN);
    printf("%c%c%c", BLK, BLK, BLK);
    setcolor(WHITE, BROWN);
    printf("%c", PXS);
    setcolor(WHITE, CYAN);
    printf("%c%c%c%c%c", PXS, PXS, PXS, DPX, DPX);
    setcolor(BLACK, WHITE);
    printf("%c%c", PXS, PXS);

    gotoxy(px + 8, py + 2);
    setcolor(BLACK, WHITE);
    printf("%c%c%c", PXS, BLK, BLK);
    setcolor(WHITE, CYAN);
    printf("%c%c%c%c%c%c%c%c%c%c%c", PXS, PXS, BLK, DPX, BLK, BLK, BLK, DPX, BLK, BLK, BLK);
    set_unicolor(BROWN);
    printf("%c", BLK);
    set_unicolor(CYAN);
    printf("%c%c%c", BLK, BLK, BLK);
    set_unicolor(BROWN);
    printf("%c", BLK);
    set_unicolor(CYAN);
    printf("%c%c%c", BLK, BLK, BLK);
    set_unicolor(BROWN);
    printf("%c", BLK);
    set_unicolor(CYAN);
    printf("%c", BLK);
    setcolor(WHITE, CYAN);
    printf("%c%c%c", PXS, DPX, DPX);
    setcolor(BLACK, WHITE);
    printf("%c", PXS);

    gotoxy(px + 6, py + 3);
    setcolor(BLACK, WHITE);
    printf("%c%c", PXS, BLK);
    setcolor(WHITE, CYAN);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c", PXS, PXS, DPX, BLK, BLK, BLK, DPX, BLK, BLK, BLK, DPX, BLK, BLK, BLK);
    set_unicolor(BROWN);
    printf("%c", BLK);
    set_unicolor(CYAN);
    printf("%c%c%c", BLK, BLK, BLK);
    set_unicolor(BROWN);
    printf("%c", BLK);
    set_unicolor(CYAN);
    printf("%c%c%c", BLK, BLK, BLK);
    set_unicolor(BROWN);
    printf("%c", BLK);
    set_unicolor(CYAN);
    printf("%c%c%c", BLK, BLK, BLK);
    setcolor(WHITE, BROWN);
    printf("%c", PXS);
    setcolor(WHITE, CYAN);
    printf("%c%c", PXS, DPX);
    setcolor(BLACK, WHITE);
    printf("%c", PXS);

    gotoxy(px + 4, py + 4);
    setcolor(BLACK, WHITE);
    printf("%c%c%c", PXS, BLK, BLK);
    set_unicolor(CYAN);
    printf("%c%c%c", BLK, BLK, BLK);
    set_unicolor(WHITE);
    printf("%c", BLK);
    set_unicolor(CYAN);
    printf("%c%c%c", BLK, BLK, BLK);
    set_unicolor(WHITE);
    printf("%c", BLK);
    set_unicolor(CYAN);
    printf("%c%c%c", BLK, BLK, BLK);
    set_unicolor(WHITE);
    printf("%c", BLK);
    set_unicolor(CYAN);
    printf("%c%c%c", BLK, BLK, BLK);
    set_unicolor(BROWN);
    printf("%c", BLK);
    set_unicolor(CYAN);
    printf("%c%c%c", BLK, BLK, BLK);
    set_unicolor(BROWN);
    printf("%c", BLK);
    set_unicolor(CYAN);
    printf("%c%c%c", BLK, BLK, BLK);
    set_unicolor(BROWN);
    printf("%c", BLK);
    set_unicolor(CYAN);
    printf("%c%c%c", BLK, BLK, BLK);
    set_unicolor(BROWN);
    printf("%c", BLK);
    set_unicolor(CYAN);
    printf("%c%c", BLK, BLK);
    setcolor(WHITE, CYAN);
    printf("%c%c", PXS, DPX);
    setcolor(BLACK, WHITE);
    printf("%c", PXS);

    gotoxy(px + 3, py + 5);
    set_unicolor(WHITE);
    printf("%c%c", PXS, BLK);
    setcolor(WHITE, CYAN);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", PXS, DPX, BLK, BLK, BLK, DPX, BLK, BLK, BLK, DPX, BLK, BLK, BLK, DPX, BLK, BLK, BLK);
    set_unicolor(BROWN);
    printf("%c", BLK);
    set_unicolor(CYAN);
    printf("%c%c%c", BLK, BLK, BLK);
    set_unicolor(BROWN);
    printf("%c", BLK);
    set_unicolor(CYAN);
    printf("%c%c%c", BLK, BLK, BLK);
    set_unicolor(BROWN);
    printf("%c", BLK);
    set_unicolor(CYAN);
    printf("%c%c%c", BLK, BLK, BLK);
    set_unicolor(BROWN);
    printf("%c", BLK);
    set_unicolor(CYAN);
    printf("%c%c%c", BLK, BLK, BLK);
    set_unicolor(WHITE);
    printf("%c%c%c", BLK, BLK, BLK);

    gotoxy(px + 2, py + 6);
    set_unicolor(WHITE);
    printf("%c%c", BLK, BLK);
    set_unicolor(CYAN);
    printf("%c%c", BLK, BLK);
    set_unicolor(WHITE);
    printf("%c", BLK);
    set_unicolor(CYAN);
    printf("%c%c%c", BLK, BLK, BLK);
    set_unicolor(WHITE);
    printf("%c", BLK);
    set_unicolor(CYAN);
    printf("%c%c%c", BLK, BLK, BLK);
    set_unicolor(WHITE);
    printf("%c", BLK);
    set_unicolor(CYAN);
    printf("%c%c%c", BLK, BLK, BLK);
    set_unicolor(WHITE);
    printf("%c", BLK);
    set_unicolor(CYAN);
    printf("%c%c%c", BLK, BLK, BLK);
    set_unicolor(BROWN);
    printf("%c", BLK);
    set_unicolor(CYAN);
    printf("%c%c%c", BLK, BLK, BLK);
    set_unicolor(BROWN);
    printf("%c", BLK);
    set_unicolor(CYAN);
    printf("%c%c%c", BLK, BLK, BLK);
    set_unicolor(BROWN);
    printf("%c", BLK);
    set_unicolor(CYAN);
    printf("%c%c%c", BLK, BLK, BLK);
    set_unicolor(BROWN);
    printf("%c", BLK);
    set_unicolor(CYAN);
    printf("%c%c%c", BLK, BLK, BLK);
    set_unicolor(WHITE);
    printf("%c", BLK);
    set_unicolor(CYAN);
    printf("%c", BLK);
    set_unicolor(WHITE);
    printf("%c%c", BLK, BLK);

    gotoxy(px + 1, py + 7);
    set_unicolor(WHITE);
    printf("%c%c", BLK, BLK);
    set_unicolor(CYAN);
    printf("%c%c%c", BLK, BLK, BLK);
    set_unicolor(WHITE);
    printf("%c", BLK);
    set_unicolor(CYAN);
    printf("%c%c%c", BLK, BLK, BLK);
    set_unicolor(WHITE);
    printf("%c", BLK);
    setcolor(CYAN, WHITE);
    printf("%c%c%c%c%c%c%c%c%c%c%c", PXS, PXS, PXS, PXI, DPX, DPX, PXS, PXI, DPX, DPX, DPX);
    set_unicolor(BROWN);
    printf("%c", DPX);
    setcolor(CYAN, BROWN);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", PXS, PXS, PXS, PXI, DPX, DPX, DPX, BLK, PXS, PXS, PXS, PXI, DPX, DPX, DPX);
    set_unicolor(WHITE);
    printf("%c", DPX);
    set_unicolor(CYAN);
    printf("%c%c", DPX, BLK);
    set_unicolor(WHITE);
    printf("%c%c", BLK, BLK);

    gotoxy(px + 0, py + 8);
    setcolor(BLACK, WHITE);
    printf("%c%c", PXS, BLK);
    setcolor(WHITE, CYAN);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", PXS, BLK, BLK, BLK, DPX, BLK, BLK, DPX, DPX, DPX, DPX, DPX, DPX, BLK, PXS, PXI, PXS, BLK, BLK);
    set_unicolor(BROWN);
    printf("%c%c%c%c%c%c", BLK, BLK, BLK, BLK, BLK, BLK);
    set_unicolor(CYAN);
    printf("%c%c", BLK, BLK);
    set_unicolor(BROWN);
    printf("%c%c%c%c%c%c", BLK, BLK, BLK, BLK, BLK, BLK);
    set_unicolor(CYAN);
    printf("%c%c%c", BLK, BLK, BLK);
    set_unicolor(WHITE);
    printf("%c", BLK);
    set_unicolor(CYAN);
    printf("%c%c", BLK, BLK);
    setcolor(WHITE, CYAN);
    printf("%c%c", PXS, DPX);
    setcolor(BLACK, WHITE);
    printf("%c", PXS);

    gotoxy(px + 0, py + 9);
    set_unicolor(WHITE);
    printf("%c%c", PXS, BLK);
    set_unicolor(CYAN);
    printf("%c%c%c%c", BLK, BLK, BLK, BLK);
    set_unicolor(WHITE);
    printf("%c", BLK);
    set_unicolor(CYAN);
    printf("%c", BLK);
    set_unicolor(WHITE);
    printf("%c%c", BLK, BLK);
    setcolor(WHITE, CYAN);
    printf("%c%c%c%c%c%c%c%c%c%c", PXS, BLK, BLK, PXS, DPX, BLK, PXI, PXI, PXI, BLK);
    set_unicolor(BROWN);
    printf("%c%c", BLK, BLK);
    setcolor(BROWN, CYAN);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", PXS, BLK, BLK, PXS, DPX, BLK, DPX, DPX, PXS, BLK, BLK, PXS, DPX, BLK, BLK);
    setcolor(WHITE, CYAN);
    printf("%c%c%c%c%c%c%c", PXS, PXI, PXS, BLK, BLK, DPX, DPX);

    gotoxy(px + 0, py + 10);
    set_unicolor(WHITE);
    printf("%c%c", DPX, BLK);
    set_unicolor(CYAN);
    printf("%c%c", BLK, BLK);
    setcolor(CYAN, WHITE);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", PXS, PXI, DPX, DPX, BLK, BLK, DPX, DPX, DPX, DPX, DPX, DPX, BLK, BLK, BLK, DPX);
    set_unicolor(BROWN);
    printf("%c%c", DPX, BLK);
    set_unicolor(CYAN);
    printf("%c%c%c%c%c%c", BLK, BLK, BLK, BLK, BLK, BLK);
    set_unicolor(BROWN);
    printf("%c%c", BLK, BLK);
    set_unicolor(CYAN);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c", BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK);
    set_unicolor(WHITE);
    printf("%c%c", BLK, BLK);

    gotoxy(px + 0, py + 11);
    set_unicolor(WHITE);
    printf("%c%c", BLK, BLK);
    set_unicolor(CYAN);
    printf("%c", BLK);
    setcolor(CYAN, WHITE);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", PXS, PXI, DPX, DPX, DPX, BLK, BLK, DPX, DPX, DPX, DPX, DPX, DPX, BLK, BLK, BLK, DPX);
    set_unicolor(BROWN);
    printf("%c%c", DPX, BLK);
    set_unicolor(CYAN);
    printf("%c%c%c%c%c%c", BLK, BLK, BLK, BLK, BLK, BLK);
    set_unicolor(BROWN);
    printf("%c%c", BLK, BLK);
    set_unicolor(CYAN);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c", BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK);
    set_unicolor(WHITE);
    printf("%c%c", BLK, BLK);

    gotoxy(px + 0, py + 12);
    set_unicolor(WHITE);
    printf("%c%c", BLK, BLK);
    setcolor(WHITE, CYAN);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", PXS, BLK, BLK, PXI, PXS, PXI, DPX, DPX, PXI, BLK, BLK, PXI, DPX, BLK, DPX, DPX, DPX, BLK);
    set_unicolor(BROWN);
    printf("%c%c", BLK, BLK);
    setcolor(CYAN, BROWN);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", PXS, DPX, DPX, PXS, BLK, DPX, BLK, BLK, PXS, DPX, DPX, PXS, BLK, DPX, DPX, DPX, DPX, DPX, DPX, DPX);
    set_unicolor(WHITE);
    printf("%c%c", DPX, BLK);

    gotoxy(px + 0, py + 13);
    setcolor(WHITE, BLACK);
    printf("%c%c%c", PXS, DPX, DPX);
    set_unicolor(CYAN);
    printf("%c%c%c", DPX, BLK, BLK);
    set_unicolor(WHITE);
    printf("%c", BLK);
    set_unicolor(CYAN);
    printf("%c", BLK);
    setcolor(WHITE, CYAN);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c", PXS, DPX, DPX, DPX, DPX, DPX, DPX, BLK, DPX, DPX, DPX, BLK);
    setcolor(BROWN, CYAN);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", PXS, DPX, DPX, DPX, DPX, DPX, DPX, BLK, PXS, DPX, DPX, DPX, DPX, DPX, DPX, BLK, BLK, BLK, BLK, BLK, BLK);
    setcolor(CYAN, WHITE);
    printf("%c%c", PXS, BLK);
    setcolor(WHITE, BLACK);
    printf("%c", PXS);

    gotoxy(px + 1, py + 14);
    set_unicolor(WHITE);
    printf("%c%c", PXS, BLK);
    set_unicolor(CYAN);
    printf("%c%c%c", BLK, BLK, BLK);
    set_unicolor(WHITE);
    printf("%c", BLK);
    set_unicolor(CYAN);
    printf("%c%c%c", BLK, BLK, BLK);
    set_unicolor(WHITE);
    printf("%c", BLK);
    setcolor(WHITE, CYAN);
    printf("%c%c%c%c%c%c%c%c%c%c%c", PXS, PXS, PXS, PXI, BLK, BLK, PXS, PXI, BLK, BLK, BLK);
    set_unicolor(BROWN);
    printf("%c", BLK);
    setcolor(BROWN, CYAN);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", PXS, PXS, PXS, PXI, BLK, BLK, BLK, PXS, DPX, PXS, PXS, BLK, PXS, PXI, BLK, BLK, BLK, BLK);
    set_unicolor(WHITE);
    printf("%c%c", BLK, BLK);

    gotoxy(px + 2, py + 15);
    set_unicolor(WHITE);
    printf("%c%c", BLK, BLK);
    set_unicolor(CYAN);
    printf("%c%c", BLK, BLK);
    set_unicolor(WHITE);
    printf("%c", BLK);
    set_unicolor(CYAN);
    printf("%c%c%c", BLK, BLK, BLK);
    set_unicolor(WHITE);
    printf("%c", BLK);
    set_unicolor(CYAN);
    printf("%c%c%c", BLK, BLK, BLK);
    set_unicolor(WHITE);
    printf("%c", BLK);
    set_unicolor(CYAN);
    printf("%c%c%c", BLK, BLK, BLK);
    set_unicolor(WHITE);
    printf("%c", BLK);
    set_unicolor(CYAN);
    printf("%c%c%c", BLK, BLK, BLK);
    set_unicolor(BROWN);
    printf("%c", BLK);
    set_unicolor(CYAN);
    printf("%c%c%c", BLK, BLK, BLK);
    set_unicolor(BROWN);
    printf("%c", BLK);
    set_unicolor(CYAN);
    printf("%c%c", BLK, BLK);
    setcolor(CYAN, BROWN);
    printf("%c%c%c%c%c%c%c%c%c%c%c", PXS, PXI, DPX, DPX, PXS, DPX, DPX, DPX, PXI, PXS, DPX);
    set_unicolor(WHITE);
    printf("%c%c", DPX, BLK);

    gotoxy(px + 3, py + 16);
    set_unicolor(WHITE);
    printf("%c%c", BLK, BLK);
    setcolor(CYAN, WHITE);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", PXS, BLK, DPX, DPX, DPX, BLK, DPX, DPX, DPX, BLK, DPX, DPX, DPX, BLK, DPX, DPX, DPX);
    set_unicolor(BROWN);
    printf("%c", DPX);
    set_unicolor(CYAN);
    printf("%c%c%c", DPX, BLK, BLK);
    set_unicolor(BROWN);
    printf("%c", BLK);
    setcolor(CYAN, BROWN);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c", PXS, PXI, DPX, DPX, PXS, PXI, DPX, PXI, PXS, DPX, DPX, DPX);
    set_unicolor(WHITE);
    printf("%c%c", DPX, BLK);

    gotoxy(px + 4, py + 17);
    setcolor(WHITE, BLACK);
    printf("%c%c%c", PXS, DPX, DPX);
    set_unicolor(CYAN);
    printf("%c%c%c", DPX, BLK, BLK);
    set_unicolor(WHITE);
    printf("%c", BLK);
    set_unicolor(CYAN);
    printf("%c%c%c", BLK, BLK, BLK);
    set_unicolor(WHITE);
    printf("%c", BLK);
    set_unicolor(CYAN);
    printf("%c%c%c", BLK, BLK, BLK);
    set_unicolor(WHITE);
    printf("%c", BLK);
    set_unicolor(CYAN);
    printf("%c%c%c", BLK, BLK, BLK);
    set_unicolor(BROWN);
    printf("%c", BLK);
    set_unicolor(CYAN);
    printf("%c%c%c", BLK, BLK, BLK);
    set_unicolor(BROWN);
    printf("%c", BLK);
    set_unicolor(CYAN);
    printf("%c%c", BLK, BLK);
    setcolor(CYAN, BROWN);
    printf("%c%c%c", PXS, PXI, DPX);
    setcolor(CYAN, WHITE);
    printf("%c%c%c%c", PXS, PXI, PXS, DPX);
    setcolor(BROWN, CYAN);
    printf("%c", PXS);
    setcolor(CYAN, WHITE);
    printf("%c%c", PXS, BLK);
    setcolor(WHITE, BLACK);
    printf("%c", PXS);

    gotoxy(px + 6, py + 18);
    set_unicolor(WHITE);
    printf("%c%c", PXS, BLK);
    setcolor(CYAN, WHITE);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c", PXS, PXS, BLK, DPX, DPX, DPX, BLK, DPX, DPX, DPX, BLK, DPX, DPX, DPX);
    set_unicolor(BROWN);
    printf("%c", DPX);
    set_unicolor(CYAN);
    printf("%c%c%c", DPX, BLK, BLK);
    set_unicolor(BROWN);
    printf("%c", BLK);
    set_unicolor(CYAN);
    printf("%c%c", BLK, BLK);
    set_unicolor(BROWN);
    printf("%c", BLK);
    set_unicolor(CYAN);
    printf("%c%c%c", BLK, BLK, BLK);
    set_unicolor(WHITE);
    printf("%c", BLK);
    setcolor(CYAN, WHITE);
    printf("%c%c%c%c", PXS, PXS, BLK, BLK);

    gotoxy(px + 8, py + 19);
    setcolor(WHITE, BLACK);
    printf("%c%c%c", PXS, DPX, DPX);
    setcolor(CYAN, WHITE);
    printf("%c%c%c%c%c%c%c%c%c%c%c", PXS, PXS, DPX, BLK, DPX, DPX, DPX, BLK, DPX, DPX, DPX);
    set_unicolor(BROWN);
    printf("%c", DPX);
    set_unicolor(CYAN);
    printf("%c%c%c", DPX, BLK, BLK);
    set_unicolor(BROWN);
    printf("%c", BLK);
    set_unicolor(CYAN);
    printf("%c%c", BLK, BLK);
    set_unicolor(BROWN);
    printf("%c", BLK);
    set_unicolor(CYAN);
    printf("%c%c", BLK, BLK);
    setcolor(CYAN, WHITE);
    printf("%c%c%c", PXS, BLK, BLK);
    setcolor(WHITE, BLACK);
    printf("%c", PXS);

    gotoxy(px + 10, py + 20);
    setcolor(WHITE, BLACK);
    printf("%c%c%c%c%c", PXS, PXS, DPX, DPX, DPX);
    setcolor(CYAN, WHITE);
    printf("%c%c%c%c%c%c%c", PXS, PXS, PXS, BLK, DPX, DPX, DPX);
    set_unicolor(BROWN);
    printf("%c", DPX);
    set_unicolor(CYAN);
    printf("%c%c%c", DPX, BLK, BLK);
    setcolor(BROWN, WHITE);
    printf("%c", PXS);
    setcolor(CYAN, WHITE);
    printf("%c%c", PXS, PXS);
    setcolor(BROWN, WHITE);
    printf("%c%c%c", PXS, BLK, BLK);
    setcolor(WHITE, BLACK);
    printf("%c%c", PXS, PXS);

    gotoxy(px + 14, py + 21);
    setcolor(WHITE, BLACK);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", PXS, PXS, PXS, DPX, DPX, DPX, DPX, DPX, DPX, DPX, DPX, DPX, DPX, PXS, PXS, PXS);
}

void presenta(int px, int py)
{
    gotoxy(px + 1, py + 0);
    setcolor(BLACK, WHITE);
    printf("%c%c%c%c", PXS, PXS, PXS, PXS);
    setcolor(BLACK, LIGHTGRAY);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", PXS, DPX, DPX, DPX, DPX, PXS, PXS, PXS, PXS, PXS, PXS, DPX, DPX, DPX, DPX, DPX, PXS, PXS);
    setcolor(BLACK, WHITE);
    printf("%c%c%c%c%c%c%c%c%c", PXS, PXS, PXS, PXS, PXS, PXS, DPX, DPX, DPX);
    setcolor(BLACK, LIGHTGRAY);
    printf("%c%c%c%c%c%c%c%c%c%c%c", PXS, PXS, PXS, PXS, PXS, PXS, DPX, DPX, DPX, PXS, PXS);
    setcolor(BLACK, WHITE);
    printf("%c%c%c%c%c%c%c%c", PXS, PXS, PXS, PXS, PXS, PXS, DPX, DPX);
    setcolor(BLACK, LIGHTGRAY);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", PXS, DPX, DPX, DPX, DPX, DPX, DPX, PXS, DPX, DPX, PXS, PXS, PXS, PXS, PXS, PXS, PXS, PXS, PXS, DPX, DPX, DPX, DPX);
    setcolor(BLACK, WHITE);
    printf("%c%c", PXS, PXS);
    setcolor(BLACK, DARKGRAY);
    printf("%c", PXS);

    gotoxy(px + 1, py + 1);
    setcolor(WHITE, DARKGRAY);
    printf("%c%c%c", PXS, DPX, DPX);
    setcolor(WHITE, BLACK);
    printf("%c%c%c%c%c", PXS, PXS, DPX, DPX, BLK);
    setcolor(WHITE, DARKGRAY);
    printf("%c%c%c", PXS, DPX, PXS);
    setcolor(WHITE, BLACK);
    printf("%c%c%c", PXS, PXS, PXS);
    setcolor(WHITE, LIGHTGRAY);
    printf("%c%c%c", PXS, DPX, PXI);
    set_unicolor(BLACK);
    printf("%c%c%c", PXI, BLK, BLK);
    set_unicolor(WHITE);
    printf("%c%c", BLK, BLK);
    setcolor(WHITE, BLACK);
    printf("%c", PXS);
    setcolor(LIGHTGRAY, BLACK);
    printf("%c%c%c%c%c%c", PXS, BLK, BLK, BLK, BLK, BLK);
    setcolor(BLACK, WHITE);
    printf("%c%c", PXS, BLK);
    setcolor(WHITE, DARKGRAY);
    printf("%c", PXS);
    setcolor(WHITE, BLACK);
    printf("%c%c%c%c%c", PXS, PXS, PXS, PXS, PXS);
    setcolor(LIGHTGRAY, BLACK);
    printf("%c%c%c", PXS, BLK, DPX);
    set_unicolor(WHITE);
    printf("%c%c", DPX, BLK);
    setcolor(WHITE, BLACK);
    printf("%c", PXS);
    setcolor(LIGHTGRAY, BLACK);
    printf("%c%c%c%c%c%c", PXS, BLK, BLK, BLK, BLK, BLK);
    set_unicolor(WHITE);
    printf("%c%c", BLK, BLK);
    setcolor(LIGHTGRAY, WHITE);
    printf("%c", PXS);
    set_unicolor(BLACK);
    printf("%c%c%c%c", PXS, BLK, BLK, BLK);
    setcolor(DARKGRAY, WHITE);
    printf("%c%c", PXS, BLK);
    setcolor(LIGHTGRAY, BLACK);
    printf("%c%c", PXS, PXS);
    setcolor(WHITE, BLACK);
    printf("%c%c%c%c", PXS, PXS, DPX, DPX);
    setcolor(WHITE, LIGHTGRAY);
    printf("%c", PXS);
    setcolor(WHITE, BLACK);
    printf("%c%c%c%c", PXS, PXS, PXS, PXS);
    setcolor(LIGHTGRAY, BLACK);
    printf("%c%c", PXS, BLK);
    setcolor(BLACK, WHITE);
    printf("%c", PXS);
    setcolor(DARKGRAY, WHITE);
    printf("%c", PXS);
    setcolor(WHITE, BLACK);
    printf("%c%c", PXS, DPX);
    setcolor(WHITE, DARKGRAY);
    printf("%c", PXS);

    gotoxy(px + 1, py + 2);
    set_unicolor(WHITE);
    printf("%c%c", PXS, BLK);
    setcolor(BLACK, WHITE);
    printf("%c%c", PXS, PXS);
    setcolor(LIGHTGRAY, WHITE);
    printf("%c%c", PXS, BLK);
    setcolor(WHITE, BLACK);
    printf("%c%c", PXS, BLK);
    setcolor(DARKGRAY, WHITE);
    printf("%c%c%c", PXS, BLK, PXS);
    setcolor(BLACK, WHITE);
    printf("%c%c", PXS, PXS);
    setcolor(LIGHTGRAY, WHITE);
    printf("%c%c", PXS, BLK);
    setcolor(WHITE, BLACK);
    printf("%c%c%c%c%c%c", PXS, PXS, BLK, BLK, DPX, DPX);
    setcolor(WHITE, LIGHTGRAY);
    printf("%c", PXS);
    setcolor(WHITE, BLACK);
    printf("%c%c%c%c%c%c%c%c", PXS, PXS, PXS, PXS, PXS, BLK, BLK, PXS);
    setcolor(WHITE, LIGHTGRAY);
    printf("%c%c%c", PXS, DPX, PXI);
    setcolor(BLACK, WHITE);
    printf("%c%c", PXS, PXS);
    setcolor(BLACK, LIGHTGRAY);
    printf("%c%c%c%c", PXS, DPX, DPX, PXS);
    set_unicolor(WHITE);
    printf("%c%c", PXS, BLK);
    setcolor(WHITE, BLACK);
    printf("%c%c%c%c%c%c%c", PXS, PXS, PXS, PXS, PXS, PXS, BLK);
    setcolor(DARKGRAY, WHITE);
    printf("%c%c", PXS, BLK);
    setcolor(WHITE, LIGHTGRAY);
    printf("%c%c%c", PXS, DPX, PXI);
    setcolor(BLACK, LIGHTGRAY);
    printf("%c%c", PXS, DPX);
    setcolor(LIGHTGRAY, WHITE);
    printf("%c%c", PXS, BLK);
    setcolor(DARKGRAY, BLACK);
    printf("%c%c%c%c%c", PXS, BLK, BLK, BLK, PXI);
    set_unicolor(WHITE);
    printf("%c", PXI);
    setcolor(WHITE, LIGHTGRAY);
    printf("%c", PXS);
    set_unicolor(BLACK);
    printf("%c%c%c%c%c", PXS, BLK, BLK, BLK, BLK);
    setcolor(BLACK, WHITE);
    printf("%c%c%c%c%c%c%c", PXS, BLK, BLK, DPX, PXS, BLK, BLK);
    setcolor(LIGHTGRAY, WHITE);
    printf("%c", PXS);

    gotoxy(px + 0, py + 3);
    set_unicolor(WHITE);
    printf("%c%c", PXS, BLK);
    setcolor(WHITE, BLACK);
    printf("%c%c", PXS, PXS);
    setcolor(LIGHTGRAY, BLACK);
    printf("%c%c%c%c", PXS, BLK, BLK, BLK);
    setcolor(DARKGRAY, WHITE);
    printf("%c%c", PXS, BLK);
    setcolor(LIGHTGRAY, BLACK);
    printf("%c", PXS);
    setcolor(WHITE, BLACK);
    printf("%c%c", PXS, DPX);
    setcolor(DARKGRAY, WHITE);
    printf("%c", PXS);
    setcolor(BLACK, LIGHTGRAY);
    printf("%c%c%c%c%c", PXS, DPX, DPX, DPX, DPX);
    setcolor(LIGHTGRAY, DARKGRAY);
    printf("%c", PXS);
    set_unicolor(WHITE);
    printf("%c", PXS);
    setcolor(WHITE, DARKGRAY);
    printf("%c", PXS);
    set_unicolor(BLACK);
    printf("%c", PXS);
    setcolor(BLACK, LIGHTGRAY);
    printf("%c", PXS);
    setcolor(BLACK, WHITE);
    printf("%c", PXS);
    setcolor(DARKGRAY, WHITE);
    printf("%c", PXS);
    setcolor(LIGHTGRAY, WHITE);
    printf("%c%c%c", PXS, PXS, PXS);
    set_unicolor(BLACK);
    printf("%c%c%c%c%c%c", PXS, BLK, BLK, BLK, BLK, BLK);
    set_unicolor(WHITE);
    printf("%c%c", BLK, BLK);
    set_unicolor(DARKGRAY);
    printf("%c", BLK);
    set_unicolor(BLACK);
    printf("%c", BLK);
    setcolor(LIGHTGRAY, DARKGRAY);
    printf("%c", PXS);
    set_unicolor(WHITE);
    printf("%c", PXS);
    setcolor(DARKGRAY, LIGHTGRAY);
    printf("%c", PXS);
    set_unicolor(BLACK);
    printf("%c", PXS);
    setcolor(BLACK, DARKGRAY);
    printf("%c", PXS);
    setcolor(BLACK, WHITE);
    printf("%c", PXS);
    setcolor(DARKGRAY, WHITE);
    printf("%c", PXS);
    set_unicolor(LIGHTGRAY);
    printf("%c", PXS);
    set_unicolor(BLACK);
    printf("%c", PXS);
    setcolor(LIGHTGRAY, WHITE);
    printf("%c%c", PXS, BLK);
    setcolor(LIGHTGRAY, BLACK);
    printf("%c%c%c", PXS, BLK, BLK);
    setcolor(WHITE, BLACK);
    printf("%c", PXS);
    setcolor(WHITE, DARKGRAY);
    printf("%c%c%c", PXS, DPX, DPX);
    setcolor(DARKGRAY, BLACK);
    printf("%c%c%c%c", PXS, BLK, BLK, BLK);
    setcolor(BLACK, LIGHTGRAY);
    printf("%c", PXS);
    set_unicolor(WHITE);
    printf("%c", PXS);
    setcolor(WHITE, DARKGRAY);
    printf("%c", PXS);
    set_unicolor(BLACK);
    printf("%c%c%c", PXS, BLK, BLK);
    setcolor(BLACK, LIGHTGRAY);
    printf("%c", PXS);
    setcolor(BLACK, WHITE);
    printf("%c%c", PXS, BLK);
    setcolor(WHITE, LIGHTGRAY);
    printf("%c", PXS);
    setcolor(WHITE, BLACK);
    printf("%c%c%c", PXS, PXS, PXS);
    setcolor(WHITE, LIGHTGRAY);
    printf("%c%c", PXS, DPX);
    setcolor(DARKGRAY, LIGHTGRAY);
    printf("%c", PXS);

    gotoxy(px + 0, py + 4);
    setcolor(WHITE, BLACK);
    printf("%c%c%c%c%c%c%c%c%c", PXS, PXS, BLK, BLK, BLK, BLK, BLK, BLK, PXS);
    setcolor(DARKGRAY, BLACK);
    printf("%c%c%c%c", PXS, BLK, BLK, BLK);
    setcolor(WHITE, BLACK);
    printf("%c%c%c%c%c%c", PXS, PXS, PXS, PXS, BLK, BLK);
    setcolor(LIGHTGRAY, BLACK);
    printf("%c", PXS);
    setcolor(WHITE, BLACK);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", PXS, PXS, PXS, PXS, PXS, BLK, BLK, PXS, PXS, PXS, PXS, PXS, PXS, PXS, PXS, PXS);
    setcolor(DARKGRAY, BLACK);
    printf("%c%c%c", PXS, BLK, BLK);
    setcolor(LIGHTGRAY, BLACK);
    printf("%c", PXS);
    setcolor(WHITE, BLACK);
    printf("%c%c%c%c%c%c%c%c", PXS, PXS, PXS, PXS, PXS, BLK, BLK, BLK);
    setcolor(WHITE, DARKGRAY);
    printf("%c", PXS);
    setcolor(WHITE, BLACK);
    printf("%c%c%c%c%c%c", PXS, BLK, BLK, BLK, BLK, BLK);
    setcolor(WHITE, DARKGRAY);
    printf("%c", PXS);
    setcolor(WHITE, BLACK);
    printf("%c%c%c%c%c%c%c%c%c%c", PXS, BLK, BLK, BLK, BLK, PXS, PXS, BLK, BLK, BLK);
    set_unicolor(DARKGRAY);
    printf("%c", BLK);
    setcolor(WHITE, LIGHTGRAY);
    printf("%c", PXS);
    setcolor(WHITE, BLACK);
    printf("%c", PXS);
    setcolor(LIGHTGRAY, BLACK);
    printf("%c%c%c%c%c%c", PXS, BLK, BLK, BLK, BLK, BLK);
    setcolor(WHITE, LIGHTGRAY);
    printf("%c%c", PXS, DPX);

}
