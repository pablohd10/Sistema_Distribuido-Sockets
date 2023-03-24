#define MAX_LENGTH_VALOR1 255

//Estructura del los elementos del servidor (lista enlazada)
struct Node{
    int key;
    char value1[MAX_LENGTH_VALOR1];
    int value2;
    double value3;
    struct Node *next;
};

typedef struct Node * List;
int init(List *l);
int set_value(List *l, int key, char *value1, int value2, double value3);
int get_value(List l, int key, char *value1, int *value2, double *value3);
int modify_value(List *l, int key, char *value1, int value2, double value3);
int printList(List l);
int delete_key(List *l, int key);
int exist(List *l, int key);
int copy_key(List *l, int key1, int key2);
int destroy(List *l);