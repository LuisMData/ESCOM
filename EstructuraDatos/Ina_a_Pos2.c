#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include".\Elem\ElemChar.h"
#include".\Pila\Pila.h"
int EsLetra(Elem e){return (((e>='a')&&(e<='z'))||((e>='A')&&(e<='Z')));}
int EsDigito(Elem e){return ((e>='0')&&(e<='9'));}
int EsParI(Elem e){return SonIguales(e,'(');}
int EsParD(Elem e){return SonIguales(e,')');}
int EsOperando(Elem e){return (EsLetra(e)||EsDigito(e));}
int Prec(Elem e){
    switch (e){
       case '+': case '-': return 1;
       case '*': case '/': return 2;
       case '!': return 3;
    }
}

void In_a_Pos(Elem *in, Elem *post){
     Pila ops=empty();
     int i=0, j=0;
     Elem c;

     while(in[i]!='\0'){
        putchar(in[i]);
        fflush(stdin);
        getchar();
        if(EsOperando(in[i]))
            post[j++]=in[i];
        else if(EsParI(in[i]))
                ops=push(in[i],ops);
             else if(EsParD(in[i])){
                      while(!EsParI(top(ops))){
                         post[j++]=top(ops);
                         ops=pop(ops);
                      }
                      ops=pop(ops);
                  }else if(Prec(in[i])>Prec(top(ops)))
                            ops=push(in[i],ops);
                        else{
                            while(!isempty(ops)&&EsMoI(Prec(in[i]),Prec(top(ops)))){
                                  post[j++]=top(ops);
                                  ops=pop(ops);
                            }
                            ops=push(in[i],ops);
                        }

     i++;
     }
     while(!isempty(ops)){
        post[j++]=top(ops);
        ops=pop(ops);
     }
     post[j]='\0';
}

int main(int argc, char *argv[]){
    Elem *post=(char*)malloc(strlen(*(argv+1))+1);
    In_a_Pos(*(argv+1),post);
//    printf("%s equivale a %s.\n",*(argv+1),post);

    return 0;
}

/*
1.- Crear una pila vac�a llamada pilaOperadores
 para almacenar los operadores. Crear una
 lista vac�a para almacenar la salida.

2.- Corvertir la cadena de entrada de notaci�n
infija a una lista, usando el m�todo split.

3.- Recorrer la lista de s�mbolos de izquierda a derecha:
    Si el s�mbolo es un operando,
    agregarlo al final de la lista de salida.

    Si el s�mbolo es un par�ntesis izquierdo,
    enviarlo a pilaOperadores.

    Si el s�mbolo es un par�ntesis derecho,
    extraer de pilaOperadores hasta que el
    correspondiente par�ntesis izquierdo
    se haya extra�do. Agregar cada operador
    al final de la lista de salida.

    Si el s�mbolo es un operador *, /, +, � -,
    incluirlo en pilaOperadores. No obstante,
    extraer previamente de la pila los operadores
    que tengan mayor o igual precedencia y
    agregarlos a la lista de salida.

4.- Cuando la expresi�n de entrada ha sido
procesada completamente, verificar
pilaOperadores. Todos los operadores que
a�n est�n almacenados en ella se deben enviar
a la lista de salida.

*/
