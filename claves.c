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
#define MAX_LENGTH_INT 12
#define MAX_LENGTH_DOUBLE 30

int init(void) {
    char resultado[3];
    char operacion[MAX_LENGTH_NOMBRE_OPERACION];
    int sd; // descriptor del socket
    struct sockaddr_in server_addr; // se define la estructura para la dirección del servidor
    struct hostent *hp;
    char *hostname;

    // Creamos el socket
    sd = socket(AF_INET, SOCK_STREAM, 0); // se crea el socket
    bzero((char *)&server_addr, sizeof(server_addr)); // se rellena de 0's
    hostname = getenv("IP_TUPLAS"); // se obtiene el nombre del servidor desde la variable de entorno IP_TUPLAS
    hp = gethostbyname(hostname); // se obtiene la dirección del servidor
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

    // Establecemos la conexión TCP con el servidor
    if (connect(sd, (struct sockaddr *) &server_addr,sizeof(server_addr)) == -1) {
        printf("Error al establecer la conexión con el servidor\n");
        return -1;
    }

    // Enviamos la operación
    strcpy(operacion, "init");
    if (sendMessage(sd, operacion, strlen(operacion)+1)  == -1) {
        printf("Error al enviar la operacion init al servidor\n");
        return -1;
    }

    if (readLine(sd, resultado, 3) == -1){ // se lee la respuesta del servidor
        printf("Error al recibir la respuesta del servidor");
        return -1;
    }
    close (sd); // se cierra el socket
    return(atoi(resultado)); // se devuelve el resultado de la operación
}

int set_value(int key, char *value1, int value2, double value3){
    char resultado[3];
    char operacion[MAX_LENGTH_NOMBRE_OPERACION];
    char key_str[MAX_LENGTH_INT];
    char valor1_str[MAX_LENGTH_VALOR1];
    char valor2_str[MAX_LENGTH_INT];
    char valor3_str[MAX_LENGTH_DOUBLE];
    int sd; // descriptor del socket
    struct sockaddr_in server_addr; // se define la estructura para la dirección del servidor
    struct hostent *hp;
    char *hostname;

    // Comprobamos que el valor1 no sea demasiado largo (255 caracteres)
    if (strlen(value1) > MAX_LENGTH_VALOR1){
        printf("Error: el valor1 es demasiado largo. Máximo 255 caracteres\n");
        return(-1);
    }


    // Creamos el socket
    sd = socket(AF_INET, SOCK_STREAM, 0); // se crea el socket
    bzero((char *)&server_addr, sizeof(server_addr)); // se rellena de 0's
    hostname = getenv("IP_TUPLAS"); // se obtiene el nombre del servidor desde la variable de entorno IP_TUPLAS
    hp = gethostbyname(hostname); // se obtiene la dirección del servidor
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

    // Establecemos la conexión TCP con el servidor
    if (connect(sd, (struct sockaddr *) &server_addr,sizeof(server_addr)) == -1) {
        printf("Error al establecer la conexión con el servidor\n");
        return -1;
    }

    // Guardamos los datos en strings para enviarlos por el socket al servidor
    strcpy(operacion, "set_value");
    sprintf(key_str, "%d", key);
    strcpy(valor1_str, value1);
    sprintf(valor2_str, "%d", value2);
    if (sprintf(valor3_str, "%f", value3) == -1){ // Comprobamos que se ha convertido correctamente
        printf("Error al convertir el valor3 a string");
        return -1;
    }

    // Enviamos los datos al servidor
    if (sendMessage(sd, operacion, strlen(operacion)+1) == -1){  // envía la operación
        printf("Error al enviar la operacion set_value al servidor");
        return -1;
    }
    if (sendMessage(sd, key_str, strlen(key_str)+1) == -1){  // envía la key
        printf("Error al enviar la key al servidor");
        return -1;
    }
    if (sendMessage(sd, valor1_str, strlen(valor1_str)+1) == -1){  // envía el valor1
        printf("Error al enviar el valor1 al servidor");
        return -1;
    }
    if (sendMessage(sd, valor2_str, strlen(valor2_str)+1) == -1){  // envía el valor2
        printf("Error al enviar el valor2 al servidor");
        return -1;
    }
    if (sendMessage(sd, valor3_str, strlen(valor3_str)+1) == -1){  // envía el valor3
        printf("Error al enviar el valor3 al servidor");
        return -1;
    }

    if (readLine(sd, resultado, 3) == -1){ // recibe la respuesta
        printf("Error al recibir la respuesta del servidor");
        return -1;
    }
    close (sd);
    return(atoi(resultado));
}

int get_value(int key, char *value1, int *value2, double *value3){
    char resultado[3];
    char operacion[MAX_LENGTH_NOMBRE_OPERACION];
    char key_str[MAX_LENGTH_INT];
    char valor1_str[MAX_LENGTH_VALOR1];
    char valor2_str[MAX_LENGTH_INT];
    char valor3_str[MAX_LENGTH_DOUBLE];
    int sd; // descriptor del socket
    struct sockaddr_in server_addr; // se define la estructura para la dirección del servidor
    struct hostent *hp;
    char *hostname;

    // Comprobamos que el valor1 no sea demasiado largo (255 caracteres)
    if (strlen(value1) > MAX_LENGTH_VALOR1){
        printf("Error: el valor1 es demasiado largo. Máximo 255 caracteres\n");
        return(-1);
    }

    // Creamos el socket
    sd = socket(AF_INET, SOCK_STREAM, 0); // se crea el socket
    bzero((char *)&server_addr, sizeof(server_addr)); // se rellena de 0's
    hostname = getenv("IP_TUPLAS"); // se obtiene el nombre del servidor desde la variable de entorno IP_TUPLAS
    hp = gethostbyname(hostname); // se obtiene la dirección del servidor
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

    // Establecemos la conexión TCP con el servidor
    if (connect(sd, (struct sockaddr *) &server_addr,sizeof(server_addr)) == -1) {
        printf("Error al establecer la conexión con el servidor\n");
        return -1;
    }

    // Guardamos los datos en strings para enviarlos por el socket al servidor
    strcpy(operacion, "get_value");
    sprintf(key_str, "%d", key);
    // Enviamos los datos al servidor
    if (sendMessage(sd, operacion, strlen(operacion)+1) == -1){  // envía la operación
        printf("Error al enviar la operacion get_value al servidor");
        return -1;
    }
    if (sendMessage(sd, key_str, strlen(key_str)+1) == -1){  // envía la key
        printf("Error al enviar la key al servidor");
        return -1;
    }

    if (readLine(sd, resultado, 3) == -1){ // recibe la respuesta
        printf("Error al recibir la respuesta del servidor");
        return -1;
    }
    if (readLine(sd, valor1_str, MAX_LENGTH_VALOR1) == -1){ // recibe el valor1
        printf("Error al recibir el valor1 del servidor");
        return -1;
    }
    strcpy(value1, valor1_str); // copia el valor1 en el puntero value1
    if (readLine(sd, valor2_str, MAX_LENGTH_INT) == -1){ // recibe el valor2
        printf("Error al recibir el valor2 del servidor");
        return -1;
    }
    if (readLine(sd, valor3_str, MAX_LENGTH_DOUBLE) == -1){ // recibe el valor3
        printf("Error al recibir el valor3 del servidor");
        return -1;
    }
    *value2 = atoi(valor2_str); // convierte el valor2 a int y lo guarda en el puntero value2
    *value3 = atof(valor3_str); // convierte el valor3 a double y lo guarda en el puntero value3

    close (sd); // se cierra el socket
    return(atoi(resultado)); // devuelve el resultado de la operación
}

int modify_value(int key, char *value1, int value2, double value3){
    char resultado[3];
    char operacion[MAX_LENGTH_NOMBRE_OPERACION];
    char key_str[MAX_LENGTH_INT];
    char valor1_str[MAX_LENGTH_VALOR1];
    char valor2_str[MAX_LENGTH_INT];
    char valor3_str[MAX_LENGTH_DOUBLE];
    int sd; // descriptor del socket
    struct sockaddr_in server_addr; // se define la estructura para la dirección del servidor
    struct hostent *hp;
    char *hostname;

    // Comprobamos que el valor1 no sea demasiado largo (255 caracteres)
    if (strlen(value1) > MAX_LENGTH_VALOR1){
        printf("Error: el valor1 es demasiado largo. Máximo 255 caracteres\n");
        return(-1);
    }

    // Creamos el socket
    sd = socket(AF_INET, SOCK_STREAM, 0); // se crea el socket
    bzero((char *)&server_addr, sizeof(server_addr)); // se rellena de 0's
    hostname = getenv("IP_TUPLAS"); // se obtiene el nombre del servidor desde la variable de entorno IP_TUPLAS
    hp = gethostbyname(hostname); // se obtiene la dirección del servidor
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

    // Establecemos la conexión TCP con el servidor
    if (connect(sd, (struct sockaddr *) &server_addr,sizeof(server_addr)) == -1) {
        printf("Error al establecer la conexión con el servidor\n");
        return -1;
    }

    strcpy(operacion, "modify_value");
    sprintf(key_str, "%d", key);
    strcpy(valor1_str, value1);
    sprintf(valor2_str, "%d", value2);
    if (sprintf(valor3_str, "%f", value3) == -1){ // Comprobamos que se ha convertido correctamente
        printf("Error al convertir el valor3 a string");
        return -1;
    }
    // Enviamos los datos al servidor
    if (sendMessage(sd, operacion, strlen(operacion)+1) == -1){  // envía la operación
        printf("Error al enviar la operacion set_value al servidor");
        return -1;
    }
    if (sendMessage(sd, key_str, strlen(key_str)+1) == -1){  // envía la key
        printf("Error al enviar la key al servidor");
        return -1;
    }
    if (sendMessage(sd, valor1_str, strlen(valor1_str)+1) == -1){  // envía el valor1
        printf("Error al enviar el valor1 al servidor");
        return -1;
    }
    if (sendMessage(sd, valor2_str, strlen(valor2_str)+1) == -1){  // envía el valor2
        printf("Error al enviar el valor2 al servidor");
        return -1;
    }
    if (sendMessage(sd, valor3_str, strlen(valor3_str)+1) == -1){  // envía el valor3
        printf("Error al enviar el valor3 al servidor");
        return -1;
    }

    // Recibimos la respuesta del servidor
    if (readLine(sd, resultado, 3) == -1){ // recibe la respuesta
        printf("Error al recibir la respuesta del servidor");
        return -1;
    }
    close (sd); // se cierra el socket
    return(atoi(resultado)); // devuelve el resultado de la operación
}

int delete_key(int key){
    char resultado[3];
    char operacion[MAX_LENGTH_NOMBRE_OPERACION];
    char key_str[MAX_LENGTH_INT];
    int sd; // descriptor del socket
    struct sockaddr_in server_addr; // se define la estructura para la dirección del servidor
    struct hostent *hp;
    char *hostname;


    // Creamos el socket
    sd = socket(AF_INET, SOCK_STREAM, 0); // se crea el socket
    bzero((char *)&server_addr, sizeof(server_addr)); // se rellena de 0's
    hostname = getenv("IP_TUPLAS"); // se obtiene el nombre del servidor desde la variable de entorno IP_TUPLAS
    hp = gethostbyname(hostname); // se obtiene la dirección del servidor
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

    // Establecemos la conexión TCP con el servidor
    if (connect(sd, (struct sockaddr *) &server_addr,sizeof(server_addr)) == -1) {
        printf("Error al establecer la conexión con el servidor\n");
        return -1;
    }

    // Enviamos los datos al servidor
    strcpy(operacion, "delete_key");
    sprintf(key_str, "%d", key);
    if (sendMessage(sd, operacion, strlen(operacion)+1) == -1){  // envía la operación
        printf("Error al enviar la operacion delete_key al servidor");
        return -1;
    }
    if (sendMessage(sd, key_str, strlen(key_str)+1) == -1){  // envía la key
        printf("Error al enviar la key al servidor");
        return -1;
    }

    // Recibimos la respuesta del servidor
    if (readLine(sd, resultado, 3) == -1){ // recibe la respuesta
        printf("Error al recibir la respuesta del servidor");
        return -1;
    }

    close (sd); // se cierra el socket
    return(atoi(resultado)); // devuelve el resultado de la operación
}

int exist(int key){
    char resultado[3];
    char operacion[MAX_LENGTH_NOMBRE_OPERACION];
    char key_str[MAX_LENGTH_INT];
    int sd; // descriptor del socket
    struct sockaddr_in server_addr; // se define la estructura para la dirección del servidor
    struct hostent *hp;
    char *hostname;


    // Creamos el socket
    sd = socket(AF_INET, SOCK_STREAM, 0); // se crea el socket
    bzero((char *)&server_addr, sizeof(server_addr)); // se rellena de 0's
    hostname = getenv("IP_TUPLAS"); // se obtiene el nombre del servidor desde la variable de entorno IP_TUPLAS
    hp = gethostbyname(hostname); // se obtiene la dirección del servidor
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

    // Establecemos la conexión TCP con el servidor
    if (connect(sd, (struct sockaddr *) &server_addr,sizeof(server_addr)) == -1) {
        printf("Error al establecer la conexión con el servidor\n");
        return -1;
    }

    // Enviamos los datos al servidor
    strcpy(operacion, "exist");
    sprintf(key_str, "%d", key);
    if (sendMessage(sd, operacion, strlen(operacion)+1) == -1){  // envía la operación
        printf("Error al enviar la operacion exist al servidor");
        return -1;
    }
    if (sendMessage(sd, key_str, strlen(key_str)+1) == -1){  // envía la key
        printf("Error al enviar la key al servidor");
        return -1;
    }

    if (readLine(sd, resultado, 3) == -1){ // recibe la respuesta
        printf("Error al recibir la respuesta del servidor");
        return -1;
    }

    close (sd); // se cierra el socket
    return(atoi(resultado)); // devuelve el resultado de la operación
}

int copy_key(int key1, int key2){
    char resultado[3];
    char operacion[MAX_LENGTH_NOMBRE_OPERACION];
    char key1_str[MAX_LENGTH_INT];
    char key2_str[MAX_LENGTH_INT];
    int sd; // descriptor del socket
    struct sockaddr_in server_addr; // se define la estructura para la dirección del servidor
    struct hostent *hp;
    char *hostname;


    // Creamos el socket
    sd = socket(AF_INET, SOCK_STREAM, 0); // se crea el socket
    bzero((char *)&server_addr, sizeof(server_addr)); // se rellena de 0's
    hostname = getenv("IP_TUPLAS"); // se obtiene el nombre del servidor desde la variable de entorno IP_TUPLAS
    hp = gethostbyname(hostname); // se obtiene la dirección del servidor
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

    // Establecemos la conexión TCP con el servidor
    if (connect(sd, (struct sockaddr *) &server_addr,sizeof(server_addr)) == -1) {
        printf("Error al establecer la conexión con el servidor\n");
        return -1;
    }

    strcpy(operacion, "copy_key");
    sprintf(key1_str, "%d", key1);
    sprintf(key2_str, "%d", key2);
    if (sendMessage(sd, operacion, strlen(operacion)+1) == -1){  // envía la operación
        printf("Error al enviar la operacion copy_key al servidor");
        return -1;
    }
    if (sendMessage(sd, key1_str, strlen(key1_str)+1) == -1){  // envía la key1
        printf("Error al enviar la key1 al servidor");
        return -1;
    }
    if (sendMessage(sd, key2_str, strlen(key2_str)+1) == -1){  // envía la key2
        printf("Error al enviar la key2 al servidor");
        return -1;
    }


    if (readLine(sd, resultado, 3) == -1){ // recibe la respuesta
        printf("Error al recibir la respuesta del servidor");
        return -1;
    }

    close (sd); // se cierra el socket
    return(atoi(resultado)); // devuelve el resultado de la operación
}