#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
//Integrantes: Eliana Garcia, Alejandra Pompilio

struct Jugador {

    char alias[5];
    char nombre [20];
    char apellido[20];
    int edad;
    int puntaje=0;
};
///lee y limpia el buffer
void leer_linea(char arr[],int tam);
//GLOBALES
int matriz [4][4];
///Funcion que impime la matriz
void imp_mat();
/// funcion que genera random 2 o 4
void random2_4();
/// Función para realizar movimiento hacia arriba
bool mover_Arriba() ;
/// Función para realizar movimiento hacia abajo
bool mover_Abajo() ;
/// Función para realizar movimiento hacia la derecha
bool mover_Derecha() ;
/// Función para realizar movimiento hacia la izquierda
bool mover_Izquierda();
///se queda con el valor mas alto, este es el puntaje final
int puntos_finales (Jugador jugadores[], int posReg);
///esta funcion  va a recorrer la matriz, fijandose si existe movimiento(es decir si se puede seguir sumando)
///si se puede seguir sumando entonces el juego aun no termina. Esta funcion solo se utiliza cuando esta toda la matriz llena de numeros
int sigo_jugando() ;
///funcion que muestra el dato del jugador con dicho alias
void datos(Jugador jugadores[], int registrados);

void ordenarPuntaje (Jugador arr[], int tam);
///funcion que muestra el menu principal
void menu(Jugador jugadores[],  int &registrados);
///Funcion que comienza el juego
void jugar_2048(Jugador jugadores[], int &registrados);
///Funcion que se utiliza al registrarse, para verificar la existencia del alias. Retorna -1 si no existe jugador con ese alias
int busco_aliasDisp (Jugador jugadores[], int tam, char aliasIngresado[]);
///Registra hasta 10 jugadores, verificando que no se repitan los alias
void registrar(Jugador jugadores[],int &registrados);

int main(){
    printf("BIENVENID@!!");
   int registrados=-1;
   Jugador jugadores[10];

    menu(jugadores, registrados);

    return 0;
}

void leer_linea(char arr[],int tam){
    int pos=-1;
    do{
        if(pos<tam-1)
            pos++;
        arr[pos]=getchar();
    }while(arr[pos]!='\n');
    arr[pos]='\0';
}

void imp_mat(){
    int posX, posY;

    for(posX=0;posX<4;posX++){
        for(posY=0;posY<4;posY++){

            if(matriz[posX][posY]==0){
                printf ("|    ");
            }
            else{
                printf("|%4d",matriz[posX][posY]);
            }
        }
        printf("|\n");
    }
}

void random2_4(){
    int arreglo[2], numero, aGenerar,posX, posY ;
    arreglo[0]=2;
    arreglo[1]=4;
    numero=rand()%2;
    aGenerar=arreglo[numero];
    do{
        posX=rand()%4;
        posY=rand()%4;
    }while(matriz [posX][posY]!=0);
    matriz[posX][posY]=aGenerar;
}

bool mover_Arriba() {
    int posY, posX, filaActual, valorActual, posy0;
    bool huboSuma=0, huboMov=0, resultSyM,sumado=0 ;

    for (posY=0;posY<4;posY++){
        for (posX=1;posX<4;posX++){
            if (matriz[posX][posY]!= 0){
                filaActual=posX;
                valorActual=matriz[filaActual][posY];

                while(filaActual>0 && matriz[filaActual-1][posY]==0) {
                    matriz[filaActual-1][posY]=valorActual;
                    matriz[filaActual][posY]=0;
                    filaActual--;
                    huboMov=1;
                }

                if(filaActual>0 && matriz[filaActual-1][posY]==valorActual && !huboSuma) {
                    matriz[filaActual-1][posY]+=valorActual;
                    matriz[filaActual][posY]=0;
                    huboSuma=1;
                    sumado=1;
                }
            }
        }
        huboSuma=0;
    }

    // Mueve los números hacia arriba
    for (posX=0;posX<4;posX++){
        for (posY=0;posY<3;posY++){
            if (matriz[posY][posX]==0){
                for (posy0=posY;posy0<3;posy0++){
                    matriz[posy0][posX]=matriz[posy0+1][posX];
                }
                matriz[3][posX]=0; //Coloca un cero al final de la columna si queda libre
            }
        }
    }

    if(huboMov==1 || sumado==1){//si sucedio alguna de las dos, va a imprimir 2 o 4
        resultSyM=1;
    }
    else{//si ambas son 0 entonces no imprime 2 o 4
        resultSyM=0;
    }

    return resultSyM;
}

bool mover_Abajo() {
    int posY, posX, filaActual, valorActual, posy0; //posy0 evalua desde la posicion que tiene posY sin modificarla
    bool huboSuma=0, huboMov=0,resultSyM,sumado=0 ;//inicializo como que no hubo movimiento ni suma

    for (posY=0;posY<4;posY++){
        for (posX=2;posX>=0;posX--){
            //si hay un numero en esa posicion hace lo siguiente
            if (matriz[posX][posY]!=0) {
                filaActual=posX; //encuentra un num y se guarda esa posicion
                valorActual=matriz[filaActual][posY]; // guardo el valor que este en esa posicion

                while(filaActual<3 && matriz[filaActual+1][posY]==0){ // mientras no se salga de la matriz y en la siguiente pos haya 0
                    matriz[filaActual+1][posY]=valorActual; // a la siguiente pos le pongo ese valor que estaba guardado
                    matriz[filaActual][posY]=0; // y en la pos actual pongo 0

                    filaActual++; //termina de evaluar toda la fila
                    //evaluo si por lo menos hubo un movimiento
                    huboMov=1;
                }
                // si la filactual(pos en la que se encontro el num) no se sale de la matriz,
                //y el siguiente es igual al actual, lo sumara y pondra 0 en pos actual
                if (filaActual<3&& matriz[filaActual+1][posY]==valorActual && !huboSuma) {
                    matriz[filaActual+1][posY]+=valorActual;
                    matriz[filaActual][posY]=0;
                    //evaluo si hubo suma
                    huboSuma=1;
                    sumado=1;
                }
            }
        }
        huboSuma=0;
    }
    // Mueve los números hacia abajo
    for (posX=0;posX<4;posX++){
        for (posY=3;posY>0;posY--){
            if (matriz[posY][posX]==0){
                for (posy0=posY;posy0>0;posy0--){
                    matriz[posy0][posX]=matriz[posy0-1][posX];
                }
                matriz[0][posX]=0; // Coloca un cero al inicio de la columna si queda libre
            }
        }
    }

    if(huboMov==1 || sumado==1){//si sucedio alguna de las dos, va a imprimir 2 o 4
        resultSyM=1;
    }
    else{//si ambas son 0 entonces no imprime 2 o 4
        resultSyM=0;
    }

    return resultSyM;
}

bool mover_Derecha() {
    int posY, posX, columnaActual, valorActual,posx0;
    bool huboSuma=0, huboMov=0,resultSyM,sumado=0 ;

    for(posY=0;posY<4;posY++){
        for(posX=2;posX>=0;posX--){
            if(matriz[posY][posX]!= 0){
                columnaActual=posX;
                valorActual=matriz[posY][columnaActual];

                while(columnaActual<3 && matriz[posY][columnaActual+1]==0){
                    matriz[posY][columnaActual+1]=valorActual;
                    matriz[posY][columnaActual]=0;

                    columnaActual++;
                    huboMov=1;
                }
                if (columnaActual<3 && matriz[posY][columnaActual+1]==valorActual && !huboSuma) {
                    matriz[posY][columnaActual+1]+=valorActual;
                    matriz[posY][columnaActual]=0;
                    huboSuma=1;
                    sumado=1;
                }
            }
        }
        huboSuma=0;
    }

    for (posY=0;posY<4;posY++){
        for (posX=3;posX>0;posX--){
            if (matriz[posY][posX]==0){
                for (posx0=posX;posx0>0;posx0--){
                    matriz[posY][posx0]=matriz[posY][posx0-1];
                }
                matriz[posY][0]=0;
            }
        }
    }

    if(huboMov==1 || sumado==1){
        resultSyM=1;
    }
    else{
        resultSyM=0;
    }

    return resultSyM;
}

bool mover_Izquierda() {
    int posY, posX, columnaActual, valorActual, posx0;
    bool huboMov=0, huboSuma=0,resultSyM, sumado=0; //inicializo como que no hubo movimiento ni suma

    for (posY=0;posY<4;posY++){
        for (posX=1;posX<4;posX++){
            // Si hay un número en esa posición
            if (matriz[posY][posX]!=0){
                columnaActual=posX; // Encuentra un número y guarda esa posición
                valorActual=matriz[posY][columnaActual]; // Guarda el valor que está en esa posición

                while (columnaActual>0 && matriz[posY][columnaActual-1]==0){ // Mientras no se salga de la matriz y en la posición anterior haya 0
                    matriz[posY][columnaActual-1]=valorActual; // A la posición anterior le pone ese valor que estaba guardado
                    matriz[posY][columnaActual]=0; // Y en la posición actual pone 0

                    columnaActual--; // Termina de evaluar toda la columna
                    huboMov=1;
                }

                // Si la columnaActual (pos en la que se encontró el número) no se sale de la matriz y el anterior es igual al actual, lo suma y pone 0
                if (columnaActual>0 && matriz[posY][columnaActual-1]==valorActual && !huboSuma){
                    matriz[posY][columnaActual-1]+=valorActual;
                    matriz[posY][columnaActual]=0;
                    huboSuma=1;
                    sumado=1;
                }
            }
        }
        huboSuma=0;
    }

    // Desplaza los numeros hacia la izquierda
    for (posY=0;posY<4;posY++){
        for (posX=0;posX<3;posX++){//va desde el 0 al 2, el 3 no lo evalua ya que es el tope
            if (matriz[posY][posX]==0){
                // Desplaza los elementos hacia la izquierda
                for (posx0=posX;posx0<3;posx0++) {
                    matriz[posY][posx0]=matriz[posY][posx0+1];
                }
                matriz[posY][3]=0; // Coloca un cero al final de la fila
            }
        }
    }

    if(huboMov==1 || sumado==1){
        resultSyM=1;
    }
    else{
        resultSyM=0;
    }

    return resultSyM;
}

int puntos_finales (Jugador jugadores[], int posReg){
    int puntos,posX,posY;
    puntos=matriz[0][0];
    for(posX=0;posX<4;posX++){
        for(posY=0;posY<4;posY++){
            if (matriz[posX][posY]>puntos){
                puntos=matriz[posX][posY];
            }
        }
    }

   return puntos;
}

int sigo_jugando() {
    // inicializo como que no se puede seguir jugando
    int sigo = 0, cont = 0, posX, posY;
    // Me fijo si hay celdas libres con la vaiable cont
    for (posX=0; posX<4; posX++) {
        for (posY=0; posY<4; posY++) {
            if (matriz[posX][posY]==0) {
                cont++;
            }
        }
    }
    // Si la matriz está llena, verifico si puedo sumar
    if (cont==0) {
        // Recorro la matriz
        for (posX=0; posX<4 && sigo==0; posX++) {
            for (posY=0; posY<4 && sigo==0; posY++) {
                // Evaluo que no se salga de los límites
                if ((posX>=0 && posX<4) && (posY>=0 && posY<4)) {
                    // Me fijo en las cuatro direcciones de la ubicación actual
                    if ((posX-1 >=0 && matriz[posX-1][posY]==matriz[posX][posY]) || (posX+1 <4 && matriz[posX+1][posY]==matriz[posX][posY])||
                        (posY- 1 >=0 && matriz[posX][posY-1] == matriz[posX][posY]) || (posY+1<4 && matriz[posX][posY+1]==matriz[posX][posY])) {
                        sigo=1;
                    }
                }
            }
        }
    } else {
        sigo = 1; // Si hay celdas libres, se puede seguir jugando
    }

    return sigo;
}

int busco_aliasDisp (Jugador jugadores[], int tam, char aliasIngresado[]){

    int aliasDisp=0;
    while(aliasDisp<tam && (strncmp(aliasIngresado, jugadores[aliasDisp].alias, 5)!=0)){
        aliasDisp++;
    }
    //si termino de recorrer el arreglo y no encontro coincidencias lo deja en -1
    if(aliasDisp==tam){
        aliasDisp=-1;
    }
    return aliasDisp;
}

void registrar(Jugador &jug, Jugador jugadores[], int &registrados){
    printf("REGISTRAR:\n");
    int aliasDisp;
    if(registrados<10){
        printf("Alias: ");
        leer_linea(jug.alias,5);

        aliasDisp=busco_aliasDisp(jugadores, registrados, jug.alias);

        //Si aliasDisp es -1 es porque no existe ese alias, por lo tanto lo puedo registrar
        if(aliasDisp== -1){
            printf("Nombre: ");
            leer_linea(jug.nombre,20);
            printf("Apellido: ");
            leer_linea(jug.apellido,20);
            printf("Edad: ");
            scanf("%d", &jug.edad);
            getchar();
        }
        else{
            printf("El alias ya existe");
        }
    }
    else{
        printf("Problema: se ha superado el maximo de jugadores");
    }
}

void datos(Jugador jugadores[],int registrados){
    printf("DATOS REGISTRADOS:\n");
    char buscoDatos[5];
    int pos=0;
    printf ("Ingrese el alias a buscar: ");
    leer_linea(buscoDatos,5);

    //Nos guardamos la posicion si se encuentra el alias
    while(pos< registrados && (strncmp(buscoDatos,jugadores[pos].alias,5)!=0)){
        pos++;
    }

    if(strncmp(buscoDatos,jugadores[pos].alias,5)!=0){
        printf ("Problema! El alias ingresado no existe ");
    }
    else{
        printf ("Nombre: %s\n",jugadores[pos].nombre);
        printf ("Apellido: %s\n",jugadores[pos].apellido);
        printf ("Edad: %d\n",jugadores[pos].edad);
        printf ("Puntaje: %d\n",jugadores[pos].puntaje);
    }

}

void jugar_2048(Jugador jugadores[], int &registrados){
    srand(time(NULL));
    int posX, posY, randY,randX,posXF,posYF,lim=3,cant2s=0, puntos=0,pos, sigo=1, posReg=-1;
    char mov, letra2, aliasIngresado[5], letrasIng[50];//alisIngresdo es para corroborar si existe en el registro
    bool retorno;
    printf("JUGAR:\n");
    printf("Ingresa tu alias: ");
    leer_linea(aliasIngresado,5);

    while(posReg<=registrados && (strncmp(aliasIngresado, jugadores[posReg].alias, 5)!=0) ){

        posReg++;
        strncmp(aliasIngresado, jugadores[posReg].alias, 5);
    }

    //Corroboramos de que exista el alias asi puede jugar
    if( strncmp(aliasIngresado, jugadores[posReg].alias, 5)==0){
        printf("Suerte %s %s!! \n", jugadores[posReg].nombre,jugadores[posReg].apellido);

        //inicializo la matriz con ceros y  cuatro cifras
        for(posX=0; posX <4; posX++){
            for(posY=0; posY<4; posY++){
                matriz[posX][posY]= 0;
            }
        }
        //dos numeros 2 aleatorios.
        do{
            posX=rand()%4;
            posY=rand()%4;
            if (matriz[posX][posY] == 0) {
                matriz[posX][posY] = 2;
                cant2s++;
            }
        }while(cant2s<2);

        //imprimimos la matriz por primera vez
        imp_mat();

        //Mientras no gane y haya movimientos disponibles, va a seguir pidiendo movimiento
        while(puntos!=2048 && sigo==1){
            printf ("\nNuevo movimiento, Subir(W), Bajar(S), Izquierda(A), Derecha(D), Rendirse (R):\n");
            leer_linea(letrasIng,50);

            mov= letrasIng[0];
            letra2= letrasIng[1];

            if(letra2!='\0'){
                mov= 'z';
            }

            switch(mov){
                case 'W': case 'w':
                    retorno= mover_Arriba();
                    if(retorno==1){//si lo que retorna la funcion es 1 entonces llama la funcion de imprimir 2o4
                        random2_4();
                    }
                break;
                case 'A': case 'a':
                    retorno= mover_Izquierda();
                    if(retorno==1){
                        random2_4();
                    }

                break;
                case 'S': case 's':
                    retorno= mover_Abajo();
                    if(retorno==1){
                        random2_4();
                    }

                break;
                case 'D': case 'd':
                   retorno= mover_Derecha();
                   if(retorno==1){
                        random2_4();
                    }

                break;
                case 'R': case 'r':
                    sigo=0;

                break;
                default:
                    printf ("Entrada invalida, vuelva a intentarlo\n");

                break;
            }

            if(sigo!=0){
                imp_mat();
                sigo=sigo_jugando();// Evalua constantemente si hay movimiento disponible
                puntos=puntos_finales(jugadores, posReg); //Evalua constantemente los puntos, si llega a 2048 finaliza el while
            }
            if(puntos==2048){
            printf("Ganaste, lograste un puntaje de 2048");
            jugadores[posReg].puntaje+=puntos;
            }
            if(sigo==0){//si se rinde, que los puntos obtenidos de ese jugador
                puntos=puntos_finales(jugadores, posReg); //Evalua constantemente los puntos, si llega a 2048 finaliza el while
                printf("Perdiste, lograste un puntaje de %d", puntos);
                jugadores[posReg].puntaje+=puntos;
            }
        }
    }
    else{
        printf("Problema: No se ha registrado ningun jugador con este alias");
        menu(jugadores, registrados);
    }
}

///Funcion que se utiliza para ordenar los jugadores segun su puntaje en el listado
void ordenarPuntaje (Jugador arr[], int tam){
    int pos, veces;
    Jugador actual;

    for(veces=0; veces < tam; veces++){

        for(pos=0; pos < tam; pos++){

            if(arr[pos+1].puntaje> arr[pos].puntaje){
                actual= arr[pos];
                arr[pos]=arr[pos+1];
                arr[pos+1]=actual;
            }
        }
    }
}

//Imprime su alias y su puntaje
void listado (Jugador jugadores[], int registrados){
    int pos;
    printf("LISTADO:\n");
    ordenarPuntaje(jugadores,registrados);

    if(registrados!=-1){
        for(pos=0;pos<=registrados;pos++){
        printf("Alias: %5s   Puntaje: %4d \n",jugadores[pos].alias, jugadores[pos].puntaje);
        }
    }
    else{
        printf("Problema: No existen jugadores aun\n");
    }
}

void menu(Jugador jugadores[], int &registrados){
    char letra2, opcion;
    bool ingMenu=1;//Booleano que cambia si la opcion es salir
    char letrasIng[50];

    while(ingMenu ==1){
        printf ("\nMenu: (R)egistrar, (L)istado, (J)ugar, (D)atos, (s)alir: ");

        leer_linea(letrasIng,50);

        opcion= letrasIng[0];
        letra2= letrasIng[1];

        if(letra2!='\0'){
            opcion= 'z';
        }

        switch(opcion){
            case 'R': case 'r':
                registrados++;
                registrar(jugadores[registrados],jugadores,registrados);

            break;
            case 'L': case 'l':
                listado(jugadores, registrados);

            break;
            case 'J': case 'j':
                jugar_2048(jugadores, registrados);

            break;
            case 'D': case 'd':
                datos(jugadores, registrados);

            break;
            case 'S': case 's':
                printf("SALIR:\n");
                printf ("Regresa pronto, que tengas un buen dia n.n");
                ingMenu=0;

            break;
            default:
                printf ("Entrada invalida, vuelva a intentarlo\n");
            break;

        }
    }

}

