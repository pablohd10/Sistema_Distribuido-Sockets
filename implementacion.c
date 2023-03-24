#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "implementacion.h"



// Función que inicializa la lista
int init(List *l) {
    List aux;
    while (*l != NULL) {
        aux = *l;
        *l = aux->next;
        free(aux);
    }
    *l = NULL;
    return (0);
}

// Función que inserta un elemento en la lista (al principio)
int set_value(List *l, int key, char *value1, int value2, double value3){
    struct Node *ptr;
    ptr = (struct Node *) malloc(sizeof(struct Node)); // new element
    if (ptr == NULL){ // no memory
        return -1;
    }
    if (*l == NULL) { // emtpy list
        ptr->key = key;
        strcpy(ptr->value1, value1);
        ptr->value2 = value2;
        ptr->value3 = value3;
        ptr->next = NULL;
        *l = ptr;

    }
    else {
        // insert in head
        ptr->key = key;
        strcpy(ptr->value1, value1);
        ptr->value2 = value2;
        ptr->value3 = value3;
        ptr->next = *l;
        *l = ptr;
    }
    return 0;
}

int get_value(List l, int key, char *value1, int *value2, double *value3){
    List aux;
    aux = l;
    while (aux!=NULL) {
        if (aux->key == key) {
            strcpy(value1, aux->value1);
            *value2 = aux->value2;
            *value3 = aux->value3;
            return 0; // found
        }
        else{
            aux = aux->next; // next element
        }
    }
    return -1; // not found
}

int modify_value(List *l, int key, char *value1, int value2, double value3){
    List aux;
    aux = *l;
    while (aux!=NULL) {
        if (aux->key == key) {
            strcpy(aux->value1, value1);
            aux->value2 = value2;
            aux->value3 = value3;
            return 0; // found
        }
        else{
            aux = aux->next; // next element
        }
    }
    return -1; // not found
}

int printList(List l){
    List aux;
    aux = l;
    while(aux != NULL){
        printf("Key=%d     value1=%s    value2=%d   value3=%f\n", aux->key, aux->value1, aux->value2, aux->value3);
        aux = aux->next;
    }
    return 0;
}

int delete_key(List *l, int key) {
    List aux, back;
    if (*l == NULL) // lista vacia
        return -1;
    // primer elemento de la lista
    if ((*l)->key == key) {
        aux = *l;
        *l = (*l)->next;
        free(aux);
        return 0;
    }
    // elemento intermedio o final
    aux = *l;
    back = *l;
    // recorremos la lista
    while (aux != NULL) {
        // si encontramos el elemento
        if (aux->key == key) {
            // lo eliminamos
            back->next = aux->next;
            free(aux);
            return 0;
        }
            // si no, seguimos buscando
        else {
            // avanzamos en la lista
            back = aux;
            aux = aux->next;
        }
    }
    return -1;
}

int exist(List *l, int key) {
    List aux;
    aux = *l;
    while (aux!=NULL) {
        if (aux->key == key) {
            return 1; // found
        }
        else{
            aux = aux->next; // next element
        }
    }
    return 0; // not found
}

int copy_key(List *l, int key1, int key2){
    List aux;
    aux = *l;
    // Recorremos la lista
    while (aux!=NULL) {
        // Si encontramos el elemento key1
        if (aux->key == key1) {
            // Si existe el elemento key2, lo modificamos
            if (exist(l, key2) == 1){
                modify_value(l, key2, aux->value1, aux->value2, aux->value3); // Si existe, lo modificamos con los valores de key1
                return 0; // found key1 and key2
            }
            set_value(l, key2, aux->value1, aux->value2, aux->value3); // Si no existe, lo creamos con los valores de key1
            return 0; // found key1
        }
        else{
            aux = aux->next; // next element
        }
    }
    return -1; // not found
}



/*

int main(void){
    List l;
    int init1;
    int set_value1;
    int set_value2;
    int modify_value1;
    int delete_key1;
    int get_value1;
    int exist1;
    int copy_key1;
    int init2;
    char value[MAX_LENGTH_VALOR1];
    int value2;
    double value3;

    init1 = init(&l);
    printf("init1=%d\n", init1);
    set_value1 = set_value(&l, 1, "hola", 2, 3.0);
    printf("set_value1=%d\n", set_value1);
    set_value2 = set_value(&l, 2, "adios", 4, 5.0);
    printf("set_value2=%d\n", set_value2);
    modify_value1 = modify_value(&l, 1, "hola", 2, 3.0);
    printf("modify_value1=%d\n", modify_value1);
    printList(l);
    delete_key1 = delete_key(&l, 1);
    printf("delete_key1=%d\n", delete_key1);
    exist1 = exist(&l, 1);
    printf("exist1=%d\n", exist1);
    copy_key1 = copy_key(&l, 2, 1);
    printf("copy_key1=%d\n", copy_key1);
    printList(l);
   
 

    get_value1 = get_value(l, 1, value, &value2, &value3);
    printf("get_value1=%d\n", get_value1);
    printf("value=%s\n", value);
    printf("value2=%d\n", value2);
    printf("value3=%f\n", value3);

    init2 = init(&l);
    printf("init2=%d\n", init2);
    printList(l);


}


*/
