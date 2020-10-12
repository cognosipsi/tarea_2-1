#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "list.h"
#include "opcion.h"
#include "hashmap.h"
#include "treemap.h"
typedef struct {
  int id;        
  char nombre[40];   
  int pc;      
  int ps;      
  char sexo[10];
}pokemon;

typedef struct {
  char nombre[40];
  char tipos[2][40];
  int almacenados;
  char previa[40];
  char posterior[40];
  int numero;
  char region[40];
}pokemon_dex;

int identificacion = 0;

const char *get_csv_field (char * tmp, int k) {
    int open_mark = 0;
    char* ret=(char*) malloc (100*sizeof(char));
    int ini_i=0, i=0;
    int j=0;
    while(tmp[i+1]!='\0'){

        if(tmp[i]== '\"'){
            open_mark = 1-open_mark;
            if(open_mark) ini_i = i+1;
            i++;
            continue;
        }

        if(open_mark || tmp[i]!= ','){
            if(k==j) ret[i-ini_i] = tmp[i];
            i++;
            continue;
        }

        if(tmp[i]== ','){
            if(k==j) {
               ret[i-ini_i] = 0;
               return ret;
            }
            j++; ini_i = i+1;
        }
        i++;
    }

    if(k==j) {
       ret[i-ini_i] = 0;
       return ret;
    }


    return NULL;
}

char *strdup(const char *str) {
    char *aux = (char*) malloc(strlen(str)+1);
    strcpy(aux, str);
    return aux;
}

void opcion_1(HashMap *MapaNombre, HashMap *MapaNombreDex, HashMap *MapaTipo,TreeMap *ArbolDex, TreeMap *ArbolPc, TreeMap *ArbolPs, HashMap *MapaRegion) {
    FILE *fp = fopen ("pokemon Archivo1.csv", "r");
    char linea[1024];
    int i;
    int j;
    int l;
    int k=0;
    char region[40];
    int a;
    pokemon *info;
    pokemon_dex *infodex,*comprobardex;
    const char *aux;
    char *tmp;
    List *ListaNombre;
    fgets (linea, 1023, fp);
    int o;
    scanf("%d", &o);
    while (fgets (linea, 1023, fp) != NULL) {
        info=(pokemon*)malloc(sizeof(pokemon));
        infodex=(pokemon_dex*)malloc(sizeof(pokemon_dex));
        j=0;
        l=0;
        a=0;
        for(i=0;i<10;i++){
            infodex->almacenados=1;
            tmp = strdup(linea);
            aux = get_csv_field(tmp, i);
            free(tmp);
            if(i==0) {
              identificacion++;
              info->id=identificacion;
            }if(i==1) {
              strcpy(info->nombre, aux);
              strcpy(infodex->nombre, aux);
            }if(i==2){
                while(aux[j]!=',' && aux[j]!='\0'){
                    infodex->tipos[0][j]=aux[j];
                    j++;
                }
                infodex->tipos[0][j]='\0';
                if(aux[j]==','){
                    j+=2;
                    while(aux[j]==' ' || isalpha(aux[j])){
                        infodex->tipos[1][l]=aux[j];
                        j++;
                        l++;
                    }
                    infodex->tipos[1][l]='\0';
                }
            }if(i==3) {
              info->pc=atoi(aux); 
            }if(i==4) {
              info->ps=atoi(aux); 
            }if(i==5) {
              strcpy(info->sexo, aux);
            }if(i==6) {
              strcpy(infodex->previa, aux);
            }if(i==7) {
              strcpy(infodex->posterior, aux);
            }if(i==8) {
              infodex->numero=atoi(aux); 
            }if(i==9) {
              /*while(isalpha(aux[a])!=0) {
                infodex->region[a]=aux[a];
                a++;
              }
              infodex->region[a+1]='\0';*/
              strcpy(infodex->region,aux);
            }
        }
        if(searchMap(MapaNombre,info->nombre)==NULL) {
          ListaNombre=create_list();
          push_back(ListaNombre, info);
          insertMap(MapaNombre,info->nombre, ListaNombre);
        }else {
          push_back(searchMap(MapaNombre,info->nombre), info);
        }
        
        if(searchMap(MapaTipo,infodex->tipos[0])==NULL) {
          ListaNombre=create_list();
          push_back(ListaNombre, info);
          insertMap(MapaTipo,infodex->tipos[0], ListaNombre);  
        }else {
          push_back(searchMap(MapaTipo,infodex->tipos[0]), info);
        }
        if(searchMap(MapaTipo,infodex->tipos[1])==NULL) {
          ListaNombre=create_list();
          push_back(ListaNombre, info);
          insertMap(MapaTipo,infodex->tipos[1], ListaNombre);  
        }else {
          push_back(searchMap(MapaTipo,infodex->tipos[1]), info);
        }
        comprobardex=(pokemon_dex*)malloc(sizeof(pokemon_dex));
        comprobardex=searchMap(MapaNombreDex,infodex->nombre);
        if(comprobardex==NULL) {
          insertMap(MapaNombreDex,infodex->nombre, infodex);
        }else {
          comprobardex->almacenados++;
        }
        if(searchTreeMap(ArbolPc,&info->pc)==NULL) {
          ListaNombre=create_list();
          push_back(ListaNombre,info);
          insertTreeMap(ArbolPc,&info->pc,ListaNombre);
        }else {
          push_back(searchTreeMap(ArbolPc,&info->pc),info);
        }
        if(searchTreeMap(ArbolPs,&info->ps)==NULL) {
          ListaNombre=create_list();
          push_back(ListaNombre,info);
          insertTreeMap(ArbolPs,&info->ps,ListaNombre);
        }else {
          push_back(searchTreeMap(ArbolPs,&info->ps),info);
        }
    }
    infodex=firstMap(MapaNombreDex);
    while(infodex!=NULL) { 
      insertTreeMap(ArbolDex,&infodex->numero, infodex);
      infodex=nextMap(MapaNombreDex); 
    }
    
    infodex=firstMap(MapaNombreDex);
    while(infodex!=NULL) {
      if(searchMap(MapaRegion,infodex->region)==NULL) {
        ListaNombre=create_list();
        push_back(ListaNombre, infodex);
        insertMap(MapaRegion,infodex->region, ListaNombre);
      }else {
        push_back(searchMap(MapaRegion,infodex->region), infodex);
      }
      infodex=nextMap(MapaNombreDex);
    }
    ListaNombre=firstMap(MapaRegion);
    while(ListaNombre!=NULL) {
      first(ListaNombre);
      infodex = first(ListaNombre);
      while (infodex != NULL) {
        printf(" %s ",infodex->nombre);
        printf("%d ",infodex->almacenados);
        printf("%s ", infodex->tipos[0]);
        if(infodex->tipos[1] != NULL){
          printf("%s ",infodex->tipos[1]);
        }
        printf("%s ",infodex->previa);
        printf("%s ",infodex->posterior);
        printf("%d ",infodex->numero);
        printf("%s ",infodex->region);
        printf("\n");
        infodex = next(ListaNombre);
      }
      ListaNombre=nextMap(MapaRegion);
    }

    ListaNombre=firstMap(MapaNombre);
    pokemon *iterador;
    while(ListaNombre!=NULL) {
      iterador=(pokemon*)malloc(sizeof(pokemon));
      iterador = first(ListaNombre);
      while (iterador != NULL) {
        printf("%d ",iterador->id);
        printf("%s ",iterador->nombre);
        printf("%d ",iterador->pc);
        printf("%d ",iterador->ps);
        printf("%s ",iterador->sexo);
        printf("\n");
        iterador = next(ListaNombre);
      }
      ListaNombre=nextMap(MapaNombre);
    }
    ListaNombre=firstMap(MapaTipo);
    while(ListaNombre!=NULL) {
      first(ListaNombre);
      iterador=(pokemon*)malloc(sizeof(pokemon));
      iterador = first(ListaNombre);
      while (iterador != NULL) {
        printf("%d ",iterador->id);
        printf("%s ",iterador->nombre);
        printf("%d ",iterador->pc);
        printf("%d ",iterador->ps);
        printf("%s ",iterador->sexo);
        printf("\n");
        iterador = next(ListaNombre);
      }
      ListaNombre=nextMap(MapaTipo);
    }
    pokemon_dex *iterador2=(pokemon_dex*)malloc(sizeof(pokemon_dex));
    iterador2=firstMap(MapaNombreDex);
    while(iterador2!=NULL) {
        printf(" %s ",iterador2->nombre);
        printf("%d ",iterador2->almacenados);
        printf("%s ",iterador2->tipos[0]);
        if(iterador2->tipos[1]!=NULL){
          printf("%s ",iterador2->tipos[1]);
        }
        printf("%s ",iterador2->previa);
        printf("%s ",iterador2->posterior);
        printf("%d ",iterador2->numero);
        printf("%s ",iterador2->region);
        printf("\n");
        iterador2=nextMap(MapaNombreDex);
    }
}

void opcion_2(HashMap *MapaNombre, HashMap *MapaNombreDex, HashMap *MapaTipo,TreeMap *ArbolDex, TreeMap *ArbolPc, TreeMap *ArbolPs, HashMap *MapaRegion){
    char nombre[40];
    int n;
    char tipos[2][40];
    int PC;
    int PS;
    char sexo[10];
    char previa[40];
    char posterior[40];
    int numero;
    char region[40];
    List *ListaNombre;
    pokemon_dex *comprobardex;
    pokemon *pkm = (pokemon *) malloc(sizeof(pokemon));
    pokemon_dex *dex = (pokemon_dex *) malloc(sizeof(pokemon_dex));

    printf("Ingrese nombre\n");
    scanf("%s", nombre);
    strcpy(pkm->nombre, nombre);

    printf("Ingrese cantidad de tipos\n");
    scanf("%d", &n);
    printf("Ingrese un tipo\n");
    scanf("%s", tipos[0]);
    strcpy(dex->tipos[0], tipos[0]);

    if (n == 2) {
        printf("Ingrese un tipo\n");
        scanf("%s", tipos[1]);
        strcpy(dex->tipos[1], tipos[1]);
    }
    
    printf("Ingrese PC\n");  //Se guardan los datos del pokemon
    scanf("%d", &PC);
    pkm->pc = PC;

    printf("Ingrese PS\n");
    scanf("%d", &PS);
    pkm->ps = PS;
    if (searchTreeMap(ArbolPs, &pkm->ps) == NULL) {
        ListaNombre = create_list();
        push_back(ListaNombre, pkm);
        insertTreeMap(ArbolPs, &pkm->ps, ListaNombre);
    }
    else {
        push_back(searchTreeMap(ArbolPs, &pkm->ps), pkm);
    }

    printf("Ingrese sexo\n");
    scanf("%s", sexo);
    strcpy(pkm->sexo, sexo);
    
    printf("Ingrese evolucion previa\n");
    scanf("%s", previa);
    strcpy(dex->previa, previa);
    
    printf("Ingrese evolucion posterior\n");
    scanf("%s", posterior);
    strcpy(dex->posterior, posterior);

    printf("Ingrese numero de la pokedex\n");
    scanf("%d", &numero);
    dex->numero = numero;
    
    printf("Ingrese region\n");
    scanf("%s", region);
    strcpy(dex->region, region);
    
    identificacion++;
    pkm->id=identificacion;
    if (searchMap(MapaNombre, nombre) == NULL) {
        List *L = create_list();
        push_back(L, pkm);
        insertMap(MapaNombre,pkm->nombre, L);
    }
    else {
        push_back(searchMap(MapaNombre,pkm->nombre), pkm);
    }
    
    if (searchMap(MapaNombre,pkm->nombre) == NULL) {
        ListaNombre = create_list();
        push_back(ListaNombre, pkm);
        insertMap(MapaNombre, pkm->nombre, ListaNombre);
    }
    else {
        push_back(searchMap(MapaNombre, pkm->nombre), pkm);
    }

    if (searchMap(MapaTipo, dex->tipos[0]) == NULL) {
        ListaNombre = create_list();
        push_back(ListaNombre, pkm);
        insertMap(MapaTipo, dex->tipos[0], ListaNombre);  
    }
    else {
        push_back(searchMap(MapaTipo, dex->tipos[0]), pkm);
    }

    if (searchMap(MapaTipo, dex->tipos[1]) == NULL) {
        ListaNombre = create_list();
        push_back(ListaNombre, pkm);
        insertMap(MapaTipo, dex->tipos[1], ListaNombre);  
    }
    else {
        push_back(searchMap(MapaTipo, dex->tipos[1]), pkm);
    }
    
    comprobardex = (pokemon_dex*) malloc(sizeof(pokemon_dex));
    comprobardex = searchMap(MapaNombreDex, dex->nombre);
    if (comprobardex == NULL) {
        insertMap(MapaNombreDex, dex->nombre, dex);
    }
    else {
        comprobardex->almacenados++;
    }

    if (searchTreeMap(ArbolPc, &pkm->pc) == NULL) {
        ListaNombre = create_list();
        push_back(ListaNombre, pkm);
        insertTreeMap(ArbolPc, &pkm->pc, ListaNombre);
    }
    else {
        push_back(searchTreeMap(ArbolPc, &pkm->pc), pkm);
    }

    
    if (searchMap(MapaNombre, pkm->nombre) == NULL) {
      ListaNombre = create_list();
      push_back(ListaNombre, pkm);
      insertMap(MapaNombre, pkm->nombre, ListaNombre);
    }
    else {
      push_back(searchMap(MapaNombre, pkm->nombre), pkm);
    }
    
    dex = firstMap(MapaNombreDex);//ATENCION
    while (dex != NULL) { //ATENCION
      insertTreeMap(ArbolDex, &dex->numero, dex);
      dex = nextMap(MapaNombreDex); //ATENCION
    }

    dex = firstMap(MapaNombreDex);
    while(dex != NULL) {
      if (searchMap(MapaRegion, dex->region) == NULL) {
        ListaNombre = create_list();
        push_back(ListaNombre, dex);
        insertMap(MapaRegion, dex->region, ListaNombre);
      }else {
        push_back(searchMap(MapaRegion, dex->region), dex);
      }
      dex = nextMap(MapaNombreDex);
    }

    ListaNombre = firstMap(MapaNombre);
    pokemon *iterador;
    while (ListaNombre != NULL) {
      first(ListaNombre);
      iterador = (pokemon*)malloc(sizeof(pokemon));
      iterador = first(ListaNombre);
      while (iterador != NULL) {
        iterador = next(ListaNombre);
      }
      ListaNombre = nextMap(MapaNombre);
    }

    ListaNombre = firstMap(MapaTipo);
    while (ListaNombre != NULL) {
      first(ListaNombre);
      iterador = (pokemon*)malloc(sizeof(pokemon));
      iterador = first(ListaNombre);
      while (iterador != NULL) {
        iterador = next(ListaNombre);
      }
      ListaNombre = nextMap(MapaTipo);
    }

    pokemon_dex *iterador2 = (pokemon_dex*)malloc(sizeof(pokemon_dex));
    iterador2 = firstMap(MapaNombreDex);
    while (iterador2!=NULL) {
        iterador2 = nextMap(MapaNombreDex);
    }
}

void opcion_3(HashMap *MapaTipo){
    char tipo[40];
    scanf("%s", tipo);
    List *L=searchMap(MapaTipo, tipo);
    if(L == NULL) {
        printf(" No se encontro \n");
        return;
    }
    pokemon *iterador = first(L);
    while (iterador != NULL) {
        printf("%d ",iterador->id);
        printf("%s ",iterador->nombre);
        printf("%d ",iterador->pc);
        printf("%d ",iterador->ps);
        printf("%s ",iterador->sexo);
        printf("\n");
        iterador = next(L);
    }
} 

void opcion_4(HashMap *MapaNombre){
    char nombre[40];
    scanf("%s", nombre);
    List *L=searchMap(MapaNombre, nombre);
    if(L == NULL) {
        printf(" No se encontro \n");
        return;
    }
    pokemon *iterador = first(L);
    while (iterador != NULL) {
        printf("%d ",iterador->id);
        printf("%s ",iterador->nombre);
        printf("%d ",iterador->pc);
        printf("%d ",iterador->ps);
        printf("%s ",iterador->sexo);
        printf("\n");
        iterador = next(L);
    }
}

void opcion_5(HashMap *MapaNombreDex){
    char nombre[40];
    pokemon_dex *dex_ite=(pokemon_dex*)malloc(sizeof(pokemon_dex));
    dex_ite = firstMap(MapaNombreDex);
    bool no_exist = true;
    printf("Ingrese el nombre \n");
    scanf("%s", nombre); //preguntar al profe
    while (dex_ite != NULL){
        if(strcmp(dex_ite->nombre, nombre) == 0){
          printf("%s ", dex_ite->nombre);
          printf("%s ", dex_ite->tipos[0]);
          if(dex_ite->tipos[1] != NULL){
            printf("%s ",dex_ite->tipos[1]);
          }
          printf("%d ", dex_ite->almacenados);
          printf("%s ", dex_ite->previa);
          printf("%s ", dex_ite->posterior);
          printf("%d ", dex_ite->numero);
          printf("%s ", dex_ite->region);
          printf("\n");
          no_exist = false;
        }
        dex_ite = nextMap(MapaNombreDex);
    }
    if (no_exist == true){
        printf (" No se encontro ningun resultado \n");
    }
}

void opcion_6 (TreeMap *ArbolDex) {
  pokemon_dex *dex_ite=(pokemon_dex*)malloc(sizeof(pokemon_dex));
  dex_ite=firstTreeMap(ArbolDex);    
  while (dex_ite != NULL){
      printf("%s ", dex_ite->nombre);
      printf("%s ", dex_ite->tipos[0]);
      if(dex_ite->tipos[1] != NULL){
        printf("%s ",dex_ite->tipos[1]);
      }
      printf("%d ", dex_ite->almacenados);
      printf("%s ", dex_ite->previa);
      printf("%s ", dex_ite->posterior);
      printf("%d ", dex_ite->numero);
      printf("%s ", dex_ite->region);
      printf("\n");
      dex_ite = nextTreeMap(ArbolDex);
  }
}
void opcion_7(TreeMap *ArbolPc){
  pokemon *iterador=(pokemon*)malloc(sizeof(pokemon));
  List *L = firstTreeMap(ArbolPc);
  while (L != NULL) {
    iterador=first(L);
    while(iterador != NULL) {
      printf("%d ",iterador->id);
      printf("%s ",iterador->nombre);
      printf("%d ",iterador->pc);
      printf("%d ",iterador->ps);
      printf("%s ",iterador->sexo);
      printf("\n");
      iterador = next(L);
    }
    L = nextTreeMap(ArbolPc);
  }
}
void opcion_8(TreeMap *ArbolPs) {
  pokemon *iterador=(pokemon*)malloc(sizeof(pokemon));
  List *L = firstTreeMap(ArbolPs);
  while (L != NULL) {
    iterador=first(L);
    while(iterador != NULL) {
      printf("%d ",iterador->id);
      printf("%s ",iterador->nombre);
      printf("%d ",iterador->pc);
      printf("%d ",iterador->ps);
      printf("%s ",iterador->sexo);
      printf("\n");
      iterador = next(L);
    }
    L = nextTreeMap(ArbolPs);
  }
}
void opcion_9 (HashMap *MapaNombre,HashMap *MapaNombreDex, HashMap *MapaTipo,TreeMap *ArbolDex, TreeMap *ArbolPs, TreeMap *ArbolPc, int id){
    List *L;
    L=firstMap(MapaNombre);
    pokemon *iterador;
    while(L!=NULL) {
      iterador=(pokemon*)malloc(sizeof(pokemon));
      iterador = first(L);
      while (iterador != NULL) {
        if(iterador->id==id) {
          
        }
        iterador = next(L);
      }
      L=nextMap(MapaNombre);
    }  
}

void opcion_10(HashMap *MapaRegion){
    /*char region[40];
    int total=0;
    printf("Escribe la region \n");
    scanf("%s",region);
    List *L=searchMap(MapaRegion, region);
    pokemon_dex *iterador =(pokemon_dex*)malloc(sizeof(pokemon_dex));
    if(L == NULL) {
        printf("No existe ningun pokemon de la region %s\n",region);
        return;
    }
    iterador = first(L);
    while (iterador!=NULL) {
        printf("%s ",iterador->nombre);
        printf("%d ",iterador->almacenados);
        printf("%s ", iterador->tipos[0]);
        if(iterador->tipos[1] != NULL){
          printf("%s ",iterador->tipos[1]);
        }
        printf("%s ",iterador->previa);
        printf("%s ",iterador->posterior);
        printf("%d ",iterador->numero);
        printf("%s ",iterador->region);
        printf("\n");
        total=total+iterador->almacenados;
        iterador=next(L);       
    }
    printf("Pokemons totales de la region %s: %d\n",region,total);*/
    char region[40];
    pokemon_dex *aux =(pokemon_dex*)malloc(sizeof(pokemon_dex));
    int total=0;
    int a=0;
    printf("Escribe la region \n");
    scanf("%s",region);
    List *L;//=searchMap(MapaRegion, region);
    L=firstMap(MapaRegion);
    while(L!=NULL) {
      a=0;
      aux=first(L);
      while(isalpha(region[a])!=0) {
        if(aux->region[a]!=region[a]) {
          break;
        }else a++;
      }
      if(isalpha(region[a])==0) {
        break;
      } 
      L=nextMap(MapaRegion);
    }
    pokemon_dex *iterador =(pokemon_dex*)malloc(sizeof(pokemon_dex));
    if(isalpha(region[a])!=0) {
        printf("No existe ningun pokemon de la region %s\n",region);
        return;
    }
    iterador = first(L);
    while (iterador!=NULL) {
        printf(" %s ",iterador->nombre);
        printf("%d ",iterador->almacenados);
        printf("%s ", iterador->tipos[0]);
        if(iterador->tipos[1] != NULL){
          printf("%s ",iterador->tipos[1]);
        }
        printf("%s ",iterador->previa);
        printf("%s ",iterador->posterior);
        printf("%d ",iterador->numero);
        printf("%s ",iterador->region);
        printf("\n");
        total=total+iterador->almacenados;
        iterador = next(L);       
    }
    printf("Pokemons totales de la region %s: %d\n",region,total);
}