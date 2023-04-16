#include <stdio.h>
#include "claves.h"


int main(void) {
    /* CLIENTE 4 */
    printf("----------------CLIENTE4-----------------: \n");


    printf("\nSET_VALUE\n");
    printf("Establecemos valores para dos claves: 40 Y 400 utilizando la funcion set_value:\n");
    int status_set_value1 = set_value(40, "hola", 2, 3.0);
    printf("Clave 1: (1,'hola', 2, 3.0) -->resultado de set_value1=%d\n", status_set_value1);
    int status_set_value2 = set_value(400, "adios", 4, 5.0);
    printf("Clave 2: (2, 'adios', 4, 5.0) -->resultado de set_value2=%d\n", status_set_value2);

    printf("\nGET_VALUE\n");
    char value1[255];
    int value2;
    double value3;
    printf("Obtenemos los valores de las claves 1 y 2 utilizando la funcion get_value:\n");
    int status_get_value1 = get_value(1, value1, &value2, &value3);
    printf("Clave 1: resultado = %d, value1 = %s, value2 = %d, value3 = %f \n", status_get_value1, value1, value2, value3);
    int status_get_value2 = get_value(2, value1, &value2, &value3);
    printf("Clave 2: resultado = %d, value1 = %s, value2 = %d, value3 = %f \n", status_get_value2, value1, value2, value3);


    printf("\nMODIFY_VALUE\n");
    int status_modify_value1 = modify_value(1, "modificado", 6, 12.0);
    printf("Modificamos la clave 1 con la siguiente tupla (1, 'modificado', 6, 12.0)\n");
    printf("Resultado de modify_value1=%d\n", status_modify_value1);

    printf("Ahora vamos a comprobar que se ha modificado la clave 1 mediante la funcion get_value:\n");
    int status_get_value3 = get_value(1, value1, &value2, &value3);
    printf("Clave 1 modificada: resultado = %d, value1 = %s, value2 = %d, value3 = %f \n", status_get_value3, value1, value2, value3);

    printf("\nEXIST\n");
    printf("Comprobamos que existe la clave 2:\n");
    int status_exist1 = exist(2);
    printf("Resultado de exist clave 2 = %d\n", status_exist1);

    printf("\nDELETE_KEY\n");
    printf("Eliminamos la clave 1:\n");
    int status_delete_key1 = delete_key(1);
    printf("Resultado de delete_key 1=%d\n", status_delete_key1);

    printf("Comprobamos que no existe la clave 1:\n");
    int status_exist2 = exist(1);
    printf("Resultado de exist = %d\n", status_exist2);

    printf("\nCOPY_KEY\n");
    printf("Creamos e insertamos la clave3 con los valores de clave 2:\n");
    int status_copy_key1 = copy_key(2, 3);
    printf("Resultado de copy_key = %d\n", status_copy_key1);
    printf("Comprobamos que se ha insertado y creado correctamente la clave 3 obteniendo sus valores con get_value:\n");
    int status_get_value4 = get_value(3, value1, &value2, &value3);
    printf("Clave 3: resultado = %d, value1 = %s, value2 = %d, value3 = %f \n", status_get_value4, value1, value2, value3);

    printf("---------------END CLIENTE4------------------\n");
    return 0;
}

