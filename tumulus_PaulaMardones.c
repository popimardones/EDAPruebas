//Paula Mardones: 1era Prueba EDA
#include "stdio.h"
#include <stdlib.h>

typedef struct nodeTumulus{
    int num; //numero de elementos almacenados en la pila correspondiente
    struct nodeTumulus *next;//apunta al mismo tipo de struct
    struct nodePila *top;//apunta a otro struct llamado nodePila
}nodeTumulus;

struct nodeTumulus *head_tumulus = NULL;

typedef struct nodePila{
    int data;
    struct nodePila *next;
}nodePila;

void pulsus(int x);
int extractum();
int quaerere(int p);
void ostende(nodeTumulus *head);

int tamanoTumulus; //el usuario define este valor
int overflowCounter = 0;
int nodesTumulusCounter = 0;

int main(void){

    int eleccion = 0; //el usuario define este valor
    int valorNodoPila; //el usuario define este valor -> es el valor que se agrega al tumulus
    int posicionTumulus, topTumulus;

    printf("\nIngrese el tamaño que quiera que sea el Tumulus: ");
    scanf("%d",&tamanoTumulus);

    // printf("\n 1 - Pulsus (insertar #)");
    // printf("\n 2 - Extractum (extraer #)");
    // printf("\n 3 - Quarere (mostrar # en el tope de la pila indicada por el usuario");
    // printf("\n 4 - Ostende (mostrar el número de elementos en cada pila)");
    // printf("\n 5 - Exit");

    while (1)
    {
        printf("\n 1 - Pulsus (insertar #)");
        printf("\n 2 - Extractum (extraer #)");
        printf("\n 3 - Quarere (mostrar # en el tope de la pila indicada por el usuario");
        printf("\n 4 - Ostende (mostrar el número de elementos en cada pila)");
        printf("\n 5 - Exit");
        printf("\nElija una de estas opciones: ");
        scanf("%d", &eleccion);

        int valorExtraido;
        switch (eleccion)
        {
        case 1:
            printf("\nIngrese el valor que quiere agregar al tumulus de tamaño %i: \n",tamanoTumulus);
            scanf("%d", &valorNodoPila);
            pulsus(valorNodoPila);
            break;
        case 2:
            valorExtraido = extractum();
            if (valorExtraido == 0){
              printf("\nNo hay ningún elemento en el tumulus\n");
            }
            else{
              printf("\nEl número que fue eliminado del tumulus fue: %i\n", valorExtraido);
            }
            break;
        case 3:
            printf("\nIngrese el número de la posición:\n");
            scanf("%d", &posicionTumulus);
            topTumulus = quaerere(posicionTumulus);
            if(topTumulus == -1){
              printf("\nIngrese una posición valida! \n  *Acuerdase de primero poblar el Tumulus*\n  *y solamente hacer Quaerere en posiciones que existen*\n");
            }else{
              printf("\nEl valor almacenado en el tope de la pila correspondiente a la posición %i de la lista es %i.\n",posicionTumulus,topTumulus);
            }
            break;
        case 4:
            ostende(head_tumulus);
            break;
        case 5:
            exit(0);
        default :
            printf("Por favor ingrese un número entre 1-5.\n");
            break;
        }
    }
  return 0;
  }

void pulsus(int x){
    //puntero que apunta a un nodo tumulus
    struct nodeTumulus *temp_tumulus= head_tumulus;

    if(head_tumulus == NULL){
      //create nodeTumulus
      nodeTumulus* nuevoNodoTumulus = (nodeTumulus*) malloc(sizeof(nodeTumulus));
      nuevoNodoTumulus->next = NULL;
      nuevoNodoTumulus->top = NULL;
      nuevoNodoTumulus->num = 1;
      //el head ya no apunta a null, sino a donde apunta el puntero nuevoNodoTumulus
      head_tumulus = nuevoNodoTumulus;

      //create nodePila
      nodePila* nueva_pila = (nodePila*) malloc(sizeof(nodePila));
      nueva_pila->data = x;
      nueva_pila->next =NULL;

      //que el top del nuevoNodo apunte a donde apunta el puntero nueva_Pila
      //en vez de la linea de abaho esto tambien funciona, no se por que: head_tumulus->top = nueva_pila;
      nuevoNodoTumulus->top = nueva_pila;
      overflowCounter = 1;
      nodesTumulusCounter = nodesTumulusCounter + 1;
    }
    else{
      if(overflowCounter<tamanoTumulus){

        //create nodePila
        while(temp_tumulus->next!=NULL){
          temp_tumulus = temp_tumulus->next;
        }
        struct nodePila *temp_pila= temp_tumulus->top;
        nodePila* nueva_pila = (nodePila*)malloc(sizeof(nodePila));
        nueva_pila->data = x;

        temp_tumulus->top = nueva_pila;
        nueva_pila->next = temp_pila;

        overflowCounter = overflowCounter + 1;
        temp_tumulus->num = temp_tumulus->num + 1;
      }
      else{

        while(temp_tumulus->next!=NULL){
          temp_tumulus = temp_tumulus->next;
        }
        //create nodeTumulus
        nodeTumulus* nuevoNodoTumulus = (nodeTumulus*)malloc(sizeof(nodeTumulus));
        nuevoNodoTumulus->next = NULL;
        nuevoNodoTumulus->top = NULL;
        nuevoNodoTumulus->num = 1;
        nodesTumulusCounter = nodesTumulusCounter + 1;
        //que el next del tumulus apunte donde apunta el puntero nuevoNodeTumulus
        temp_tumulus->next = nuevoNodoTumulus;

        nodePila* nueva_pila = (nodePila*)malloc(sizeof(nodePila));
        nueva_pila->data = x;
        nueva_pila->next = NULL;

        nuevoNodoTumulus->top = nueva_pila;

        overflowCounter = 1;
        nuevoNodoTumulus->num = 1;
      }
  }
}

int extractum(){
    struct nodeTumulus *tempQueRecorre_tumulus,*tempPrevio_tumulus;

    struct nodePila *tempQueBorra_pila = NULL;

    int ultElementoInsertado;

    if(head_tumulus == NULL){
        free(head_tumulus);
        overflowCounter = 0;
        return 0;
    }else{
        tempQueRecorre_tumulus = head_tumulus;
        tempPrevio_tumulus = head_tumulus;
        //recorrer hasta el final de la linked list tumulus:
        while(tempQueRecorre_tumulus->next != NULL){
          tempPrevio_tumulus = tempQueRecorre_tumulus;
          tempQueRecorre_tumulus = tempQueRecorre_tumulus->next;
         }

         if(tempQueRecorre_tumulus->top->next == NULL){//borrar nodo_tumulus y nodo_pila

          tempQueBorra_pila = tempQueRecorre_tumulus -> top;
          ultElementoInsertado = tempQueRecorre_tumulus->top->data;
          tempQueRecorre_tumulus->top = NULL;
          //borra de la memoria el ultimo nodo_pila
          free(tempQueBorra_pila);

          while(tempQueRecorre_tumulus->next != NULL)
          {
              tempPrevio_tumulus = tempQueRecorre_tumulus;
              tempQueRecorre_tumulus = tempQueRecorre_tumulus->next;
          }
          if(tempQueRecorre_tumulus == head_tumulus){
              head_tumulus = NULL;
          }
          else{//desconecta el nodo previo al ultimo
              tempPrevio_tumulus->next = NULL;
          }
          //borra de la memoria el ultimo nodo_tumulus
          free(tempQueRecorre_tumulus);

          nodesTumulusCounter = nodesTumulusCounter - 1;

          return ultElementoInsertado;

      }else{//borrar nodo_pila

          //tempQueBorra_pila apunte al top
          tempQueBorra_pila = tempQueRecorre_tumulus -> top;
          ultElementoInsertado = tempQueBorra_pila-> data;
          tempQueRecorre_tumulus->num = tempQueRecorre_tumulus->num - 1;
          //que el top apunte al nodo siguente al que se va a borrar
          tempQueRecorre_tumulus->top = tempQueRecorre_tumulus->top->next;
          //que el next del nodo_pila que se va borrar sea nulo
          tempQueRecorre_tumulus->top->next = NULL;
          free(tempQueBorra_pila);

          return ultElementoInsertado;
      }
    }
}


int quaerere(int p){
//esta función retorna el valor almacenado en el tope de la pila correspondiente
//a la posición p de la lista

    if (p > nodesTumulusCounter || p<=0){
    return -1;
    }
    else{
    struct nodeTumulus* tempQueRecorre_tumulus = head_tumulus;
    int count = 1;
    while (tempQueRecorre_tumulus != NULL)
    {
       if (count == p)
          return(tempQueRecorre_tumulus->top->data);
       count++;
       tempQueRecorre_tumulus = tempQueRecorre_tumulus->next;
    }
    return -1;

  }
}

void ostende(nodeTumulus *head){
//esta función muestra el número de elementos almacenados en cada pila de la lista
//apuntada por head
  struct nodeTumulus *tempQueRecorre_tumulus;
  tempQueRecorre_tumulus = head;

  int posicionNodoTumulus = 1;
    if(head == NULL){
      printf("El tumulus esta vacío\n");
    }
    else{
        while (tempQueRecorre_tumulus != NULL)
        {
          int numAlmacenadosEnUnNodoTumulus;
          numAlmacenadosEnUnNodoTumulus = tempQueRecorre_tumulus->num;
          printf("El número de elementos almacenados en el %i° nodo-tumulus es %i.\n",posicionNodoTumulus,numAlmacenadosEnUnNodoTumulus);
          posicionNodoTumulus = posicionNodoTumulus + 1;
          tempQueRecorre_tumulus = tempQueRecorre_tumulus->next;
        }
  }
}

