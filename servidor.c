#include <pthread.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "implementacion.h"
#include "lines.h"


#define MAX_LENGTH_NOMBRE_OPERACION 16
#define MAX_LENGTH_VALOR1 255
#define MAX_LENGTH_INT 11
#define MAX_LENGTH_DOUBLE 20

// Declaramos el servidor como una lista enlazada
List servidor;

/* mutex y variables condicionales para proteger la copia del mensaje*/
pthread_mutex_t mutex_mensaje;
int mensaje_no_copiado = true;
pthread_cond_t cond_mensaje;

/* mutex y variables condicionales para proteger el acceso al servidor --> operaciones atomicas*/
pthread_mutex_t mutex_servidor;


void tratar_mensaje(int *s){
    int s_local;

    /* el thread copia el descriptor de socket a una variable local */
    pthread_mutex_lock(&mutex_mensaje);
    s_local = (* (int *) s); /* copiar el descriptor*/
    /* ya se puede despertar al servidor*/
    pthread_mutex_unlock(&mutex_mensaje);


    char operacion[MAX_LENGTH_NOMBRE_OPERACION];
    int status;
    char resultado[2]; // 0 o 1 + '\0' = 2


    readLine(s_local, operacion, MAX_LENGTH_NOMBRE_OPERACION); // recibe la operación
    printf("Operación recibida: %s \n", operacion);



    if (strcmp(operacion, "init") == 0){
        pthread_mutex_lock(&mutex_servidor);
        status = init(&servidor); // Llamamos a la función init
        pthread_mutex_unlock(&mutex_servidor);

        printf("Resultado de la operación init: %d\n", status);
        sprintf(resultado, "%d", status); // Guardamos el resultado como una cadena en la variable resultado
        sendMessage(s_local, resultado, strlen(resultado)+1); // Enviamos el resultado al cliente
    }
    else if (strcmp(operacion, "set_value") == 0){
        // Declaramos los valores que vamos a recibir y van a ser introducidos en la función del servidor
        int key;
        char value1[MAX_LENGTH_VALOR1];
        int value2;
        double value3;
        // Reservamos memoria para recibir los valores (strings)
        char key_str[MAX_LENGTH_INT];
        char value1_str[MAX_LENGTH_VALOR1];
        char value2_str[MAX_LENGTH_INT];
        char value3_str[MAX_LENGTH_DOUBLE];
        // Recibimos los valores
        readLine(s_local, key_str, MAX_LENGTH_INT);
        readLine(s_local, value1_str, MAX_LENGTH_VALOR1);
        readLine(s_local, value2_str, MAX_LENGTH_INT);
        readLine(s_local, value3_str, MAX_LENGTH_DOUBLE);
        // Guardamos los valores --> los transformamos de string a los tipos que necesitamos
        key = atoi(key_str);
        strcpy(value1, value1_str);
        value2 = atoi(value2_str);
        value3 = atof(value3_str);
        // Llamamos a la función set_value
        pthread_mutex_lock(&mutex_servidor);
        status = set_value(&servidor,key, value1, value2, value3);
        pthread_mutex_unlock(&mutex_servidor);

        printf("Resultado de la operación set_value: %d\n", status);
        sprintf(resultado, "%d", status); // Guardamos el resultado como una cadena en la variable resultado
        sendMessage(s_local, resultado, strlen(resultado)+1); // Enviamos el resultado al cliente
    }
    else if (strcmp(operacion, "get_value") == 0){
        // Guardamos los valores del mensaje en variables locales
        int key;
        char value1[MAX_LENGTH_VALOR1];
        int value2;
        double value3;

        // Recibimos el valor de key
        char key_str[MAX_LENGTH_INT];
        if (readLine(s_local, key_str, MAX_LENGTH_INT) == -1){
            printf("Error al recibir el valor de key");
        }
        printf("Valor de key recibido: %s", key_str);

        // Guardamos los valores --> los transformamos de string a los tipos que necesitamos
        if ((key = atoi(key_str)) == -1){
            printf("Error al transformar el valor de key a entero");
        }
        
        // Llamamos a la función get_value
        pthread_mutex_lock(&mutex_servidor);
        status = get_value(servidor,key, value1, &value2, &value3);
        pthread_mutex_unlock(&mutex_servidor);
        printf("Resultado de la operación get_value: %d\n", status);

        // Reservamos memoria para almacenar los valores en cadenas y mandarlos al cliente
        char value1_str[MAX_LENGTH_VALOR1];
        char value2_str[MAX_LENGTH_INT];
        char value3_str[MAX_LENGTH_DOUBLE];

        // Guardamos los valores en cadenas
        if (sprintf(value1_str, "%s", value1) == -1){
            printf("Error al guardar el valor de value1 en una cadena");
        }
        if (sprintf(value2_str, "%d", value2) == -1){
            printf("Error al guardar el valor de value2 en una cadena");
        }
        if (sprintf(value3_str, "%f", value3) == -1){
            printf("Error al guardar el valor de value3 en una cadena");
        }

        // Enviamos el resultado al cliente
        sprintf(resultado, "%d", status); // Guardamos el resultado como una cadena en la variable resultado
        sendMessage(s_local, resultado, strlen(resultado)+1);
        sendMessage(s_local, value1_str, strlen(value1_str)+1);
        sendMessage(s_local, value2_str, strlen(value2_str)+1);
        sendMessage(s_local, value3_str, strlen(value3_str)+1);

    }

    else if (strcmp(operacion, "modify_value") == 0){
        // Declaramos los valores que vamos a recibir y van a ser introducidos en la función del servidor
        int key;
        char value1[MAX_LENGTH_VALOR1];
        int value2;
        double value3;
        // Reservamos memoria para recibir los valores (strings)
        char key_str[MAX_LENGTH_INT];
        char value1_str[MAX_LENGTH_VALOR1];
        char value2_str[MAX_LENGTH_INT];
        char value3_str[MAX_LENGTH_DOUBLE];
        // Recibimos los valores
        readLine(s_local, key_str, MAX_LENGTH_INT);
        readLine(s_local, value1_str, MAX_LENGTH_VALOR1);
        readLine(s_local, value2_str, MAX_LENGTH_INT);
        readLine(s_local, value3_str, MAX_LENGTH_DOUBLE);
        // Guardamos los valores --> los transformamos de string a los tipos que necesitamos
        key = atoi(key_str);
        strcpy(value1, value1_str);
        value2 = atoi(value2_str);
        value3 = atof(value3_str);
        // Llamamos a la función modify_value
        pthread_mutex_lock(&mutex_servidor);
        status = modify_value(&servidor,key, value1, value2, value3);
        pthread_mutex_unlock(&mutex_servidor);
        printf("Resultado de la operación modify_value: %d\n", status);

        sprintf(resultado, "%d", status); // Guardamos el resultado como una cadena en la variable resultado
        sendMessage(s_local, resultado, strlen(resultado)+1); // Enviamos el resultado al cliente
    }
    else if (strcmp(operacion, "delete_key") == 0){
        // Guardamos los valores del mensaje en variables locales
        int key;

        // Recibimos el valor de key
        char key_str[MAX_LENGTH_INT];
        readLine(s_local, key_str, MAX_LENGTH_INT);

        // Guardamos el valor de la key --> la transformamos de string a int
        key = atoi(key_str);

        // Enviamos el resultado al cliente
        pthread_mutex_lock(&mutex_servidor);
        status = delete_key(&servidor,key);
        pthread_mutex_unlock(&mutex_servidor);
        printf("Resultado de la operación delete_key: %d\n", status);
        sprintf(resultado, "%d", status); // Guardamos el resultado como una cadena en la variable resultado
        sendMessage(s_local, resultado, strlen(resultado)+1); // Enviamos el resultado al cliente
    }
    else if (strcmp(operacion, "exist") == 0){
        // Guardamos los valores del mensaje en variables locales
        int key;

        // Recibimos el valor de key
        char key_str[MAX_LENGTH_INT];
        readLine(s_local, key_str, MAX_LENGTH_INT);

        // Guardamos el valor de la key --> la transformamos de string a int
        key = atoi(key_str);

        // Enviamos el resultado al cliente
        pthread_mutex_lock(&mutex_servidor);
        status = exist(&servidor,key);
        pthread_mutex_unlock(&mutex_servidor);
        printf("Resultado de la operación exist: %d\n", status);
        sprintf(resultado, "%d", status); // Guardamos el resultado como una cadena en la variable resultado
        sendMessage(s_local, resultado, strlen(resultado)+1); // Enviamos el resultado al cliente
    }
    else if (strcmp(operacion, "copy_key") == 0){
        char resultado[2]; // 0 o 1 + '\0' = 2
        // Guardamos los valores del mensaje en variables locales
        int key1;
        int key2;

        // Recibimos el valor de key
        char key1_str[MAX_LENGTH_INT];
        char key2_str[MAX_LENGTH_INT];
        readLine(s_local, key1_str, MAX_LENGTH_INT);
        readLine(s_local, key2_str, MAX_LENGTH_INT);

        // Guardamos el valor de la key --> la transformamos de string a int
        key1 = atoi(key1_str);
        key2 = atoi(key2_str);

        // Enviamos el resultado al cliente
        pthread_mutex_lock(&mutex_servidor);
        status =copy_key(&servidor,key1, key2);
        pthread_mutex_unlock(&mutex_servidor);
        printf("Resultado de la operación copy_key: %d\n", status);
        sprintf(resultado, "%d", status); // Guardamos el resultado como una cadena en la variable resultado
        sendMessage(s_local, resultado, strlen(resultado)+1); // Enviamos el resultado al cliente
    }
    printf("Cerrando conexión con el cliente: operacion terminada\n");
    close(s_local);  // Cerramos el socket
    pthread_exit(0); // Salimos del thread
}


int main(int argc, char *argv[]) {
    // Comprobamos que se ha introducido el puerto
    if (argc != 2) {
        printf("Uso: %s <puerto>", argv[0]);
        return -1;}
    int puerto = atoi(argv[1]);

    // Declaración threads
    pthread_attr_t t_attr;
    pthread_t thid;

    // Declaración sockets
    struct sockaddr_in server_addr, client_addr;
    socklen_t size;
    int sd, sc;
    int val, err;

    // Atributos de los threads
    pthread_mutex_init(&mutex_mensaje, NULL);
    pthread_mutex_init(&mutex_servidor, NULL);
    pthread_cond_init(&cond_mensaje, NULL);
    pthread_attr_init(&t_attr);

    // atributos de los threads, threads independientes
    pthread_attr_setdetachstate(&t_attr, PTHREAD_CREATE_DETACHED);

    // Creamos el socket
    if ((sd = socket(AF_INET, SOCK_STREAM, 0))<0){
        printf ("SERVER: Error en el socket");
        return (0);
    }
    val = 1;
    // Permitimos que el socket se pueda reutilizar
    err = setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, (char *) &val,
                     sizeof(int));
    // Comprobamos que no haya habido errores
    if (err < 0) {
        perror("Error in socket's options");
        exit(1);
    }
    // Asignamos el puerto al socket
    bzero((char *)&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET; // AF_INET --> IPv4
    server_addr.sin_addr.s_addr = INADDR_ANY; // INADDR_ANY --> escucha en todas las interfaces
    server_addr.sin_port = htons(puerto); // puerto --> argumento del programa, lo pasamos a formato de red
    bind(sd, (const struct sockaddr *)&server_addr,
         sizeof(server_addr));

    listen(sd, SOMAXCONN); // SOMAXCONN --> número máximo de conexiones que se pueden encolar
    size = sizeof(client_addr);

    // Bucle infinito para aceptar conexiones
    while(1) {
        printf("esperando conexion\n");
        sc = accept(sd, (struct sockaddr *) &client_addr, (socklen_t *) &size); // Aceptamos la conexión
        printf("conexion aceptada\n");

        // se crea un thread para tratar la información contenida en el socket
        if (pthread_create(&thid, &t_attr, (void *)tratar_mensaje, (int *)&sc)== 0) {
            // se espera a que el thread copie el descriptor
            pthread_mutex_lock(&mutex_mensaje);
            while (mensaje_no_copiado)
                pthread_cond_wait(&cond_mensaje, &mutex_mensaje);
            mensaje_no_copiado = true;
            pthread_mutex_unlock(&mutex_mensaje);
        }
        else {
            printf("Error al crear el thread\n");
            close(sc);
        }
    }
    return 0;
}
