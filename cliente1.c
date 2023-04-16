#include <stdio.h>
#include "claves.h"
#include <unistd.h>


int main(void) {
    /* CLIENTE 1 */
    printf("----------------CLIENTE 1-----------------: \n");
    printf("INIT\n");
    int status_init1 = init();
    printf("resultado de init1=%d\n", status_init1);

    printf("SET_VALUE\n");
    printf("Establecemos valores para dos claves: 10 y 11 utilizando la funcion set_value:\n");
    int status_set_value1 = set_value(10, "hola", 2, 3.0);
    printf("Clave : (10,'hola', 2, 3.0) -->resultado de set_value1=%d\n", status_set_value1);
    int status_set_value2 = set_value(11, "adios", 4, 5.0);
    printf("Clave 2: (11, 'adios', 4, 5.0) -->resultado de set_value2=%d\n", status_set_value2);

    printf("Durmiendo el cliente 1 por 15 segundos...\n");
    fflush(stdout); // Vacía el búfer de salida para que se muestre el mensaje antes de dormir el proceso
    sleep(15);

    printf("\nEXIST\n");
    printf("Comprobamos que existen las claves 10 y 11. Si se ha ejecutado el cliente 2 mientras este cliente estaba dormido, las claves han debido de ser eliminadas y el resultado de exist deberia ser 0. Si no se ha ejecutado el cliente2 el resultado de exist es 1\n");
    printf("Comprobamos que existe la clave 10:\n");
    int status_exist1_1 = exist(10);
    printf("Resultado de exist clave 10 = %d\n", status_exist1_1);
    printf("Comprobamos que existe la clave 11:\n");
    int status_exist1_2 = exist(10);
    printf("Resultado de exist clave 11 = %d\n", status_exist1_2);

    printf("---------------END CLIENTE 1------------------\n");
    return 0;
}

