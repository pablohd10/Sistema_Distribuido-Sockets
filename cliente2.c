#include <stdio.h>
#include "claves.h"


int main(void) {
    /* CLIENTE 2. ¡¡¡EJECUTAR ESTE CLIENTE CUANDO EL CLIENTE1 ESTÉ DORMIDO!!! */
    printf("----------------CLIENTE 2-----------------: \n");
    printf("---------------EXIST------------------\n");
    printf("Comprobamos que existen las claves 10 y 11. Estas claves han sido creadas e insertadas en el servidor por el cliente 1.\n");
    int status_exist2_1 = exist(10);
    printf("Resultado de exist clave 10 = %d\n", status_exist2_1);
    int status_exist2_2 = exist(11);
    printf("Resultado de exist clave 11 = %d\n", status_exist2_2);


    printf("-----------------DELETE_KEY------------------\n");
    printf("Eliminamos las claves 10 y 11:\n");
    int status_delete_key2_1 = delete_key(10);
    printf("Resultado de delete_key 10=%d\n", status_delete_key2_1);
    int status_delete_key2_2 = delete_key(11);
    printf("Resultado de delete_key 11=%d\n", status_delete_key2_2);

    printf("---------------END CLIENTE 2------------------\n");
    return 0;
}

