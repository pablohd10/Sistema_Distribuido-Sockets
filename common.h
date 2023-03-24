#define MAX_LENGTH_VALOR1 255
#define MAX_LENGTH_NOMBRE_OPERACION 16
#define MAX_LENGTH_Q_NAME 256

struct mensaje{
    int key;
    char value1[MAX_LENGTH_VALOR1];
    int value2;
    double value3;
    char operacion[MAX_LENGTH_NOMBRE_OPERACION]; // Nombre de la operacion
    int key2; // Para la operacion copy_key
    char q_name[256]; // Nombre de la cola del cliente
};

struct respuesta{
    int status; // 0 si todo ha ido bien, -1 si ha habido algun error
    char value1[MAX_LENGTH_VALOR1];
    int value2;
    double value3;
};






