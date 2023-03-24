#include <stdio.h>
#include "claves.h"

int main(void) {
    int init1;
    int set_value1;
    int set_value2;
    int modify_value1;
    int delete_key1;
    int get_value1;
    int get_value2;
    int exist1;
    int copy_key1;
    char value[255];
    int value2;
    double value3;

    /* Aqui vamos a establecer clientes que se encargaran de probar que todo
    el programa funcione correctamente */

    printf("Cliente 1:\n\n");
    init1 = init();
    printf("init1=%d\n", init1);
    printf("Extablecemos valores para la clave 1 y 2:\n");
    set_value1 = set_value(1, "hola", 2, 3.0);
    printf("set_value1=%d\n", set_value1);
    set_value2 = set_value(2, "adios", 4, 5.0);
    printf("set_value2=%d\n", set_value2);

    printf("Clave 1:\n");
    get_value1 = get_value(1, value, &value2, &value3);
    printf("get_value1=%d\n", get_value1);
    printf("value=%s\n", value);
    printf("value2=%d\n", value2);
    printf("value3=%f\n", value3);

    printf("Clave 2:\n");
    get_value2 = get_value(2, value, &value2, &value3);
    printf("get_value2=%d\n", get_value2);
    printf("value=%s\n", value);
    printf("value2=%d\n", value2);
    printf("value3=%f\n", value3);

    printf("\nModificamos la clave 1:\n");
    modify_value1 = modify_value(1, "modificado", 6, 12.0);
    printf("modify_value1=%d\n", modify_value1);

    printf("\nClave 1 modificada:\n");
    get_value1 = get_value(1, value, &value2, &value3);
    printf("get_value1=%d\n", get_value1);
    printf("value=%s\n", value);
    printf("value2=%d\n", value2);
    printf("value3=%f\n", value3);

    printf("\nComprobamos que existe la clave, por ejemplo la 1:\n");
    exist1 = exist(1);
    printf("Existe clave 1 = %d\n", exist1);

    printf("\nEliminamos la clave 1:\n");
    delete_key1 = delete_key(1);
    printf("delete_key1=%d\n", delete_key1);
    
    printf("\nVolvemos a  que existe la clave 1:\n");
    exist1 = exist(1);
    printf("exist1=%d\n", exist1);

    printf("\nCopiamos las clave 2 en la 1:\n");
    copy_key1 = copy_key(2, 1);
    printf("copy_key1=%d\n", copy_key1);
   
    printf("\nA continuación obtendremos valores de la clave 1:\n");
    get_value1 = get_value(1, value, &value2, &value3);
    printf("get_value1=%d\n", get_value1);
    printf("value=%s\n", value);
    printf("value2=%d\n", value2);
    printf("value3=%f\n", value3);

    printf("\nIntentamos obtener los valores de una clave que no está creada:\n");
    get_value1 = get_value(30, value, &value2, &value3);
    printf("get_value1=%d\n", get_value1);
    
    return 0;
}

