#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashmap.h"
#include "list.h"
#include "opcion.h"
#include "treemap.h"
//gcc -g main.c hashmap-answer.c list.c opcion.c treemap.c -o tarea_2
/*int lower_than_string(void* key1, void* key2){
    char* k1=(char*) key1;
    char* k2=(char*) key2;
    if(strcmp(k1,k2)<0) return 1;
    return 0;
}*/
/*int lower_than_string(void* key1, void* key2){
    int k1=atoi((char*) key1);
    int k2=atoi((char*) key2);
    if(k1<k2) return 1;
    return 0;
}*/
int lower_than_int(void* key1, void* key2){
    int k1 = *((int*) (key1));
    int k2 = *((int*) (key2));
    return k1<k2;
}
int higher_than_int(void* key1, void* key2){
    int k1 = *((int*) (key1));
    int k2 = *((int*) (key2));
    return k1>k2;
}
int main (void) {
  int op;
  HashMap *MapaNombre=createMap(100);
  HashMap *MapaTipo=createMap(100);
  HashMap *MapaNombreDex=createMap(100);
  HashMap *MapaRegion=createMap(100);
  TreeMap *ArbolDex=createTreeMap(lower_than_int);
  TreeMap *ArbolPc=createTreeMap(higher_than_int);
  TreeMap *ArbolPs=createTreeMap(higher_than_int);
  while (op != 11) {
      /* MENU */ 
        printf("1.- Importar/Exportar desde un archivo CSV\n");              
        printf("2.- Atrapar pokemon\n");
        printf("3.- Buscar mis pokémon por tipo\n");
        printf("4.- Buscar mis pokémon por nombre\n");
        printf("5.- Buscar por nombre en pokédex\n");
        printf("6.- Mostrar todos los pokémon de la pokédex\n");
        printf("7.- Mostrar tus pokémon por mayor PC\n");
        printf("8.- Mostrar pokémon por mayor PS\n");
        printf("9.- Liberar pokémon\n");
        printf("10.- Mostrar pokémon por región\n");
        printf("11.- Salir\n");
        printf("\nIndica la opcion: ");
        scanf("%d", &op);
      if (op == 1) {
          opcion_1(MapaNombre,MapaNombreDex, MapaTipo,ArbolDex,ArbolPc,ArbolPs,MapaRegion); 
      }
      if (op == 2) {
          opcion_2(MapaNombre,MapaNombreDex,MapaTipo,ArbolDex, ArbolPc, ArbolPs, MapaRegion); 
      }
      if (op == 3) {
          opcion_3(MapaTipo);
      }
      if (op == 4) {
          opcion_4(MapaNombre);
      }
      if (op == 5) {
          opcion_5(MapaNombreDex);
      }
      if (op == 6) {
          opcion_6(ArbolDex);
      }
      if (op == 7) {
          opcion_7(ArbolPc);
      }
      if (op == 8) {
          opcion_8(ArbolPs);
      }
      if (op == 9) {
          //opcion_9(MapaNombre,MapaNombreDex,MapaTipo,ArbolDex);
      }
      if (op == 10) {
          opcion_10(MapaRegion);
      }
  }
  return 0;
}
