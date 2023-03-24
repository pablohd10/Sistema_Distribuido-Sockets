#include <mqueue.h>
#include <pthread.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "common.h"
#include "implementacion.h"

// Declaramos el servidor como una lista enlazada
List servidor;

/* mutex y variables condicionales para proteger la copia del mensaje*/
pthread_mutex_t mutex_mensaje;
int mensaje_no_copiado = true;
pthread_cond_t cond_mensaje;

mqd_t  q_servidor; //Cola de mensajes del servidor


void tratar_mensaje(void *mess){
    struct mensaje msg;	/* mensaje local */
    struct respuesta resultado;
    mqd_t q_cliente;		/* cola del cliente */

    char operacion[16];
    /* el thread copia el mensaje a un mensaje local */
    pthread_mutex_lock(&mutex_mensaje);

    msg = (*(struct mensaje *) mess);

    /* ya se puede despertar al servidor*/
    mensaje_no_copiado = false;

    pthread_cond_signal(&cond_mensaje);
    pthread_mutex_unlock(&mutex_mensaje);

    /* ejecutar la petición del cliente y preparar respuesta */

    strcpy(operacion, msg.operacion);

    if (strcmp(operacion, "init") == 0){
        resultado.status = init(&servidor);
        printf("Resultado de la operación init: %d\n", resultado.status);
    }
    else if (strcmp(operacion, "set_value") == 0){
        resultado.status = set_value(&servidor,msg.key, msg.value1, msg.value2, msg.value3);
        printf("Resultado de la operación set_value: %d\n", resultado.status);
    }
    else if (strcmp(operacion, "get_value") == 0){
        // Guardamos los valores del mensaje en variables locales
        char value1[MAX_LENGTH_VALOR1];
        int value2;
        double value3;
        
        // Llamamos a la función get_value
        resultado.status = get_value(servidor,msg.key, value1, &value2, &value3);
        // Guardamos los valores en el resultado
        strcpy(resultado.value1, value1);
        resultado.value2 = value2;
        resultado.value3 = value3;
    }
    else if (strcmp(operacion, "modify_value") == 0){
        resultado.status = modify_value(&servidor,msg.key, msg.value1, msg.value2, msg.value3);
    }
    else if (strcmp(operacion, "delete_key") == 0){
        resultado.status = delete_key(&servidor,msg.key);
    }
    else if (strcmp(operacion, "exist") == 0){
        resultado.status = exist(&servidor,msg.key);
    }
    else if (strcmp(operacion, "copy_key") == 0){
        resultado.status = copy_key(&servidor,msg.key, msg.key2);
    }



    /* Se devuelve el resultado al cliente */
    /* Para ello se envía el resultado a su cola */
    q_cliente = mq_open(msg.q_name, O_WRONLY);
    if (q_cliente == -1){
        perror("No se puede abrir la cola del cliente");
        mq_close(q_servidor);
        mq_unlink("/SERVIDOR.2");
    }
    else {
        if (mq_send(q_cliente, (char *) &resultado, sizeof(resultado), 0) <0) {
            perror("Error al enviar el resultado al cliente");
            mq_close(q_servidor);
            mq_unlink("/SERVIDOR.2");
            mq_close(q_cliente);
        }
    }
    pthread_exit(0);
}


int main(void) {
    struct mensaje mess;
    struct mq_attr attr;

    pthread_attr_t t_attr;		// atributos de los threads
    pthread_t thid;

    attr.mq_maxmsg = 10;
    attr.mq_msgsize = sizeof(struct mensaje);

    q_servidor = mq_open("/SERVIDOR.2", O_CREAT|O_RDONLY, 0700, &attr);
    if (q_servidor == -1) {
        perror("Servidor: Error al abrir la cola del servidor");
        return -1;
    }

    pthread_mutex_init(&mutex_mensaje, NULL);
    pthread_cond_init(&cond_mensaje, NULL);
    pthread_attr_init(&t_attr);

    // atributos de los threads, threads independientes
    pthread_attr_setdetachstate(&t_attr, PTHREAD_CREATE_DETACHED);

    while(1) {
        if (mq_receive(q_servidor, (char *) &mess, sizeof(struct mensaje), 0) < 0 ){
            perror("Error al recibir el mensaje por parte del servidor");
            return -1;
        }
        printf("Servidor: mensaje recibido de %s\n", mess.q_name);
        printf("Operacion: %s\n", mess.operacion);
        // se crea un thread para tratar el mensaje
        if (pthread_create(&thid, &t_attr, (void *)tratar_mensaje, (void *)&mess)== 0) {
            // se espera a que el thread copie el mensaje
            pthread_mutex_lock(&mutex_mensaje);
            while (mensaje_no_copiado)
                pthread_cond_wait(&cond_mensaje, &mutex_mensaje);
            mensaje_no_copiado = true;
            pthread_mutex_unlock(&mutex_mensaje);
        }
    }
    return 0;
}
