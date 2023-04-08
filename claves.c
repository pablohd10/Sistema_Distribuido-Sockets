#include <stdio.h>
#include <netdb.h>
#include <strings.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdlib.h>
#include "lines.h"

#define MAX_LENGTH_NOMBRE_OPERACION 16
#define MAX_LENGTH_VALOR1 255
#define MAX_LENGTH_INT 11
#define MAX_LENGTH_DOUBLE 20

int init(void) {
    char resultado[2]; // 0 o 1 + '\0' = 2
    char operacion[MAX_LENGTH_NOMBRE_OPERACION];
    int sd; // descriptor del socket
    struct sockaddr_in server_addr; // se define la estructura para la dirección del servidor
    struct hostent *hp;
    char *hostname;

    sd = socket(AF_INET, SOCK_STREAM, 0); // se crea el socket
    bzero((char *)&server_addr, sizeof(server_addr)); // se rellena de 0's

    hostname = getenv("IP_TUPLAS"); // se obtiene la dirección del servidor desde la variable de entorno IP_TUPLAS
    hp = gethostbyname(hostname);
    if (hp == NULL){
        printf("Variable de entorno IP_TUPLAS no definida\n");
        return -1;
    }

    char* puerto_str = getenv("PORT_TUPLAS"); // se obtiene el puerto del servidor desde la variable de entorno PORT_TUPLAS
    if (puerto_str == NULL){
        printf("Variable de entorno PORT_TUPLAS no definida\n");
        return -1;
    }
    int puerto = atoi(puerto_str); // se convierte el puerto a int

    memcpy (&(server_addr.sin_addr), hp->h_addr, hp->h_length); // se copia la dirección del servidor
    server_addr.sin_family = AF_INET; // se indica que es una dirección de internet
    server_addr.sin_port = htons(puerto); // se indica el puerto del servidor (se convierte a formato de red)

    // se establece la conexión
    connect(sd, (struct sockaddr *) &server_addr,sizeof(server_addr));

    strcpy(operacion, "init");
    sendMessage(sd, operacion, strlen(operacion)+1); // envía la operacion

    readLine(sd, resultado, 2); // recibe la respuesta
    close (sd);
    return(atoi(resultado));

}

int set_value(int key, char *value1, int value2, double value3){
    char resultado[2]; // 0 o 1 + '\0' = 2
    char operacion[MAX_LENGTH_NOMBRE_OPERACION];
    char key_str[MAX_LENGTH_INT];
    char valor1_str[MAX_LENGTH_VALOR1];
    char valor2_str[MAX_LENGTH_INT];
    char valor3_str[MAX_LENGTH_DOUBLE];
    int sd; // descriptor del socket
    struct sockaddr_in server_addr; // se define la estructura para la dirección del servidor
    struct hostent *hp;
    char *hostname;


    sd = socket(AF_INET, SOCK_STREAM, 0); // se crea el socket
    bzero((char *)&server_addr, sizeof(server_addr)); // se rellena de 0's

    hostname = getenv("IP_TUPLAS"); // se obtiene la dirección del servidor desde la variable de entorno IP_TUPLAS
    hp = gethostbyname(hostname);
    if (hp == NULL){
        printf("Variable de entorno IP_TUPLAS no definida\n");
        return -1;
    }

    char* puerto_str = getenv("PORT_TUPLAS"); // se obtiene el puerto del servidor desde la variable de entorno PORT_TUPLAS
    if (puerto_str == NULL){
        printf("Variable de entorno PORT_TUPLAS no definida\n");
        return -1;
    }
    int puerto = atoi(puerto_str); // se convierte el puerto a int

    memcpy (&(server_addr.sin_addr), hp->h_addr, hp->h_length); // se copia la dirección del servidor
    server_addr.sin_family = AF_INET; // se indica que es una dirección de internet
    server_addr.sin_port = htons(puerto); // se indica el puerto del servidor (se convierte a formato de red)

    // se establece la conexión
    connect(sd, (struct sockaddr *) &server_addr,sizeof(server_addr));

    strcpy(operacion, "set_value");
    sprintf(key_str, "%d", key);
    strcpy(valor1_str, value1);
    sprintf(valor2_str, "%d", value2);
    sprintf(valor3_str, "%f", value3);
    sendMessage(sd, operacion, strlen(operacion)+1); // envía la operacion
    sendMessage(sd, key_str, strlen(key_str)+1); // envía la key
    sendMessage(sd, valor1_str, strlen(valor1_str)+1); // envía el valor1
    sendMessage(sd, valor2_str, strlen(valor2_str)+1); // envía el valor2
    sendMessage(sd, valor3_str, strlen(valor3_str)+1); // envía el valor3

    readLine(sd, resultado, 2); // recibe la respuesta
    close (sd);
    return(atoi(resultado));
}

int get_value(int key, char *value1, int *value2, double *value3){
    char resultado[2]; // 0 o 1 + '\0' = 2
    char operacion[MAX_LENGTH_NOMBRE_OPERACION];
    char key_str[MAX_LENGTH_INT];
    char valor1_str[MAX_LENGTH_VALOR1];
    char valor2_str[MAX_LENGTH_INT];
    char valor3_str[MAX_LENGTH_DOUBLE];
    int sd; // descriptor del socket
    struct sockaddr_in server_addr; // se define la estructura para la dirección del servidor
    struct hostent *hp;
    char *hostname;


    sd = socket(AF_INET, SOCK_STREAM, 0); // se crea el socket
    bzero((char *)&server_addr, sizeof(server_addr)); // se rellena de 0's

    hostname = getenv("IP_TUPLAS"); // se obtiene la dirección del servidor desde la variable de entorno IP_TUPLAS
    hp = gethostbyname(hostname);
    if (hp == NULL){
        printf("Variable de entorno IP_TUPLAS no definida\n");
        return -1;
    }

    char* puerto_str = getenv("PORT_TUPLAS"); // se obtiene el puerto del servidor desde la variable de entorno PORT_TUPLAS
    if (puerto_str == NULL){
        printf("Variable de entorno PORT_TUPLAS no definida\n");
        return -1;
    }
    int puerto = atoi(puerto_str); // se convierte el puerto a int

    memcpy (&(server_addr.sin_addr), hp->h_addr, hp->h_length); // se copia la dirección del servidor
    server_addr.sin_family = AF_INET; // se indica que es una dirección de internet
    server_addr.sin_port = htons(puerto); // se indica el puerto del servidor (se convierte a formato de red)

    // se establece la conexión
    connect(sd, (struct sockaddr *) &server_addr,sizeof(server_addr));

    strcpy(operacion, "get_value");
    sprintf(key_str, "%d", key);
    sendMessage(sd, operacion, strlen(operacion)+1); // envía la operacion
    sendMessage(sd, key_str, strlen(key_str)+1); // envía la key

    readLine(sd, resultado, 2); // recibe la respuesta
    readLine(sd, valor1_str, MAX_LENGTH_VALOR1); // recibe el valor1
    strcpy(value1, valor1_str);
    readLine(sd, valor2_str, MAX_LENGTH_INT); // recibe el valor2
    readLine(sd, valor3_str, MAX_LENGTH_DOUBLE); // recibe el valor3
    *value2 = atoi(valor2_str); // convierte el valor2 a int
    *value3 = atof(valor3_str); // convierte el valor3 a double

    close (sd);
    return(atoi(resultado));
}

int modify_value(int key, char *value1, int value2, double value3){
    char resultado[2]; // 0 o 1 + '\0' = 2
    char operacion[MAX_LENGTH_NOMBRE_OPERACION];
    char key_str[MAX_LENGTH_INT];
    char valor1_str[MAX_LENGTH_VALOR1];
    char valor2_str[MAX_LENGTH_INT];
    char valor3_str[MAX_LENGTH_DOUBLE];
    int sd; // descriptor del socket
    struct sockaddr_in server_addr; // se define la estructura para la dirección del servidor
    struct hostent *hp;
    char *hostname;


    sd = socket(AF_INET, SOCK_STREAM, 0); // se crea el socket
    bzero((char *)&server_addr, sizeof(server_addr)); // se rellena de 0's

    hostname = getenv("IP_TUPLAS"); // se obtiene la dirección del servidor desde la variable de entorno IP_TUPLAS
    hp = gethostbyname(hostname);
    if (hp == NULL){
        printf("Variable de entorno IP_TUPLAS no definida\n");
        return -1;
    }

    char* puerto_str = getenv("PORT_TUPLAS"); // se obtiene el puerto del servidor desde la variable de entorno PORT_TUPLAS
    if (puerto_str == NULL){
        printf("Variable de entorno PORT_TUPLAS no definida\n");
        return -1;
    }
    int puerto = atoi(puerto_str); // se convierte el puerto a int

    memcpy (&(server_addr.sin_addr), hp->h_addr, hp->h_length); // se copia la dirección del servidor
    server_addr.sin_family = AF_INET; // se indica que es una dirección de internet
    server_addr.sin_port = htons(puerto); // se indica el puerto del servidor (se convierte a formato de red)

    // se establece la conexión
    connect(sd, (struct sockaddr *) &server_addr,sizeof(server_addr));

    strcpy(operacion, "modify_value");
    sprintf(key_str, "%d", key);
    strcpy(valor1_str, value1);
    sprintf(valor2_str, "%d", value2);
    sprintf(valor3_str, "%f", value3);
    sendMessage(sd, operacion, strlen(operacion)+1); // envía la operacion
    sendMessage(sd, key_str, strlen(key_str)+1); // envía la key
    sendMessage(sd, valor1_str, strlen(valor1_str)+1); // envía el valor1
    sendMessage(sd, valor2_str, strlen(valor2_str)+1); // envía el valor2
    sendMessage(sd, valor3_str, strlen(valor3_str)+1); // envía el valor3

    readLine(sd, resultado, 2); // recibe la respuesta
    close (sd);
    return(atoi(resultado));
}

int delete_key(int key){
    char resultado[2]; // 0 o 1 + '\0' = 2
    char operacion[MAX_LENGTH_NOMBRE_OPERACION];
    char key_str[MAX_LENGTH_INT];
    int sd; // descriptor del socket
    struct sockaddr_in server_addr; // se define la estructura para la dirección del servidor
    struct hostent *hp;
    char *hostname;


    sd = socket(AF_INET, SOCK_STREAM, 0); // se crea el socket
    bzero((char *)&server_addr, sizeof(server_addr)); // se rellena de 0's

    hostname = getenv("IP_TUPLAS"); // se obtiene la dirección del servidor desde la variable de entorno IP_TUPLAS
    hp = gethostbyname(hostname);
    if (hp == NULL){
        printf("Variable de entorno IP_TUPLAS no definida\n");
        return -1;
    }

    char* puerto_str = getenv("PORT_TUPLAS"); // se obtiene el puerto del servidor desde la variable de entorno PORT_TUPLAS
    if (puerto_str == NULL){
        printf("Variable de entorno PORT_TUPLAS no definida\n");
        return -1;
    }
    int puerto = atoi(puerto_str); // se convierte el puerto a int

    memcpy (&(server_addr.sin_addr), hp->h_addr, hp->h_length); // se copia la dirección del servidor
    server_addr.sin_family = AF_INET; // se indica que es una dirección de internet
    server_addr.sin_port = htons(puerto); // se indica el puerto del servidor (se convierte a formato de red)

    // se establece la conexión
    connect(sd, (struct sockaddr *) &server_addr,sizeof(server_addr));

    strcpy(operacion, "delete_key");
    sprintf(key_str, "%d", key);
    sendMessage(sd, operacion, strlen(operacion)+1); // envía la operacion
    sendMessage(sd, key_str, strlen(key_str)+1); // envía la key

    readLine(sd, resultado, 2); // recibe la respuesta

    close (sd);
    return(atoi(resultado));
}

int exist(int key){
    char resultado[2]; // 0 o 1 + '\0' = 2
    char operacion[MAX_LENGTH_NOMBRE_OPERACION];
    char key_str[MAX_LENGTH_INT];
    int sd; // descriptor del socket
    struct sockaddr_in server_addr; // se define la estructura para la dirección del servidor
    struct hostent *hp;
    char *hostname;


    sd = socket(AF_INET, SOCK_STREAM, 0); // se crea el socket
    bzero((char *)&server_addr, sizeof(server_addr)); // se rellena de 0's

    hostname = getenv("IP_TUPLAS"); // se obtiene la dirección del servidor desde la variable de entorno IP_TUPLAS
    hp = gethostbyname(hostname);
    if (hp == NULL){
        printf("Variable de entorno IP_TUPLAS no definida\n");
        return -1;
    }

    char* puerto_str = getenv("PORT_TUPLAS"); // se obtiene el puerto del servidor desde la variable de entorno PORT_TUPLAS
    if (puerto_str == NULL){
        printf("Variable de entorno PORT_TUPLAS no definida\n");
        return -1;
    }
    int puerto = atoi(puerto_str); // se convierte el puerto a int

    memcpy (&(server_addr.sin_addr), hp->h_addr, hp->h_length); // se copia la dirección del servidor
    server_addr.sin_family = AF_INET; // se indica que es una dirección de internet
    server_addr.sin_port = htons(puerto); // se indica el puerto del servidor (se convierte a formato de red)

    // se establece la conexión
    connect(sd, (struct sockaddr *) &server_addr,sizeof(server_addr));

    strcpy(operacion, "exist");
    sprintf(key_str, "%d", key);
    sendMessage(sd, operacion, strlen(operacion)+1); // envía la operacion
    sendMessage(sd, key_str, strlen(key_str)+1); // envía la key

    readLine(sd, resultado, 2); // recibe la respuesta

    close (sd);
    return(atoi(resultado));
}

int copy_key( int key1, int key2){
    char resultado[2]; // 0 o 1 + '\0' = 2
    char operacion[MAX_LENGTH_NOMBRE_OPERACION];
    char key1_str[MAX_LENGTH_INT];
    char key2_str[MAX_LENGTH_INT];
    int sd; // descriptor del socket
    struct sockaddr_in server_addr; // se define la estructura para la dirección del servidor
    struct hostent *hp;
    char *hostname;


    sd = socket(AF_INET, SOCK_STREAM, 0); // se crea el socket
    bzero((char *)&server_addr, sizeof(server_addr)); // se rellena de 0's

    hostname = getenv("IP_TUPLAS"); // se obtiene la dirección del servidor desde la variable de entorno IP_TUPLAS
    hp = gethostbyname(hostname);
    if (hp == NULL){
        printf("Variable de entorno IP_TUPLAS no definida\n");
        return -1;
    }

    char* puerto_str = getenv("PORT_TUPLAS"); // se obtiene el puerto del servidor desde la variable de entorno PORT_TUPLAS
    if (puerto_str == NULL){
        printf("Variable de entorno PORT_TUPLAS no definida\n");
        return -1;
    }
    int puerto = atoi(puerto_str); // se convierte el puerto a int

    memcpy (&(server_addr.sin_addr), hp->h_addr, hp->h_length); // se copia la dirección del servidor
    server_addr.sin_family = AF_INET; // se indica que es una dirección de internet
    server_addr.sin_port = htons(puerto); // se indica el puerto del servidor (se convierte a formato de red)

    // se establece la conexión
    connect(sd, (struct sockaddr *) &server_addr,sizeof(server_addr));

    strcpy(operacion, "copy_key");
    sprintf(key1_str, "%d", key1);
    sprintf(key2_str, "%d", key2);
    sendMessage(sd, operacion, strlen(operacion)+1); // envía la operacion
    sendMessage(sd, key1_str, strlen(key1_str)+1); // envía la key1
    sendMessage(sd, key2_str, strlen(key2_str)+1); // envía la key2


    readLine(sd, resultado, 2); // recibe la respuesta

    close (sd);
    return(atoi(resultado));
}