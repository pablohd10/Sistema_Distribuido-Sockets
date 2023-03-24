#include <stdio.h>
#include "claves.h"

int main(void) {
    int init1;
    int set_value1;
    int set_value2;
    int set_value3;
    int set_value4;
    int get_value1;
    int get_value2;
    int get_value3;
    int get_value4;
    int get_value5;
    char value[255];
    int value2;
    double value3;

    printf("Cliente 3:\n\n");
    init1 = init();
    printf("init1=%d\n", init1);

    printf("\nIntentamos obtener los valores de una clave que no está creada:\n");
    get_value5 = get_value(25, value, &value2, &value3);
    printf("get_value5=%d\n", get_value5);

    set_value1 = set_value(1, 2, 3, 4.0);
    printf("set_value1=%d\n", set_value1);
    printf("Clave 1:\n");
    get_value1 = get_value(1, value, &value2, &value3);
    printf("get_value1=%d\n", get_value1);
    printf("value=%d\n", value);
    printf("value2=%d\n", value2);
    printf("value3=%f\n", value3);

    set_value2 = set_value(2, "Hola", "adios", 12.0);
    printf("set_value2=%d\n", set_value2);
    printf("Clave 2:\n");
    get_value2 = get_value(2, value, &value2, &value3);
    printf("get_value2=%d\n", get_value2);
    printf("value=%s\n", value);
    printf("value2=%s\n", value2);
    printf("value3=%f\n", value3);

    set_value3 = set_value(3, "Hola", 3, "string");
    printf("set_value3=%d\n", set_value3);
    printf("Clave 3:\n");
    get_value2 = get_value(3, value, &value2, &value3);
    printf("get_value3=%d\n", get_value3);
    printf("value=%s\n", value);
    printf("value2=%d\n", value2);
    printf("value3=%s\n", value3);

    set_value4 = set_value(4, "Esto deberia ser una cadena con mas de 255 caracteres por lo que nodeberia ser aceptada dentro del mensaje aa aaaaa aaaaaaaaa aaaaaaa aaaaaa aaaaaaaaa aaaaaa aaaaaa aaaaaaa aaaaaaaaaa aaaaaccccc cccccccccc cccccccc cccccccc cccccccccc ccccccccc cccccrrrrrr rrrrrrrrrrr rrrrrrrrr rrrrrrrrrrrrr rrrrrrrrrrr rrrrrrrrrrrrrrr rrrrrrrrrrr rrrrrrrrrrrrrrrrr rrrrr rrrr", 2, 3.0);
    printf("set_value4=%d\n", set_value4);
    printf("Clave 4:\n");
    get_value4 = get_value(4, value, &value2, &value3);
    printf("get_value4=%d\n", get_value4);
    printf("value=%s\n", value);
    printf("value2=%d\n", value2);
    printf("value3=%f\n", value3);

    return 0;
}

