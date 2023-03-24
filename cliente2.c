#include <stdio.h>
#include "claves.h"

int main(void) {
    int init1;
    int set_value3;
    int set_value4;
    int get_value3;
    int get_value4;
    int exist3;
    int exist4;
    char value[255];
    int value2;
    double value3;

    /* Aqui vamos a establecer clientes que se encargaran de probar que todo
    el programa funcione correctamente */

    printf("Cliente 2:\n\n");
    init1 = init();
    printf("init1=%d\n", init1);
    printf("Extablecemos valores para la clave 3 y 4:\n");
    set_value3 = set_value(3, "Prueba de string", 10, 30.0);
    printf("set_value1=%d\n", set_value3);
    set_value4 = set_value(4, "La siguiente prueba", 4, 5.0);
    printf("set_value2=%d\n", set_value4);

    printf("Clave 3:\n");
    get_value3 = get_value(3, value, &value2, &value3);
    printf("get_value3=%d\n", get_value3);
    printf("value=%s\n", value);
    printf("value2=%d\n", value2);
    printf("value3=%f\n", value3);

    printf("Clave 4:\n");
    get_value4 = get_value(4, value, &value2, &value3);
    printf("get_value4=%d\n", get_value4);
    printf("value=%s\n", value);
    printf("value2=%d\n", value2);
    printf("value3=%f\n", value3);

    printf("\nComprobamos que existe la clave, por ejemplo la 1:\n");
    exist3 = exist(3);
    printf("Existe clave 3 = %d\n", exist3);

    printf("\nComprobamos que existe la clave, por ejemplo la 1:\n");
    exist4 = exist(4);
    printf("Existe clave 4 = %d\n", exist4);
    
    return 0;
}

