#include <mqueue.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include "common.h"

int init(void) {
    mqd_t q_servidor;       /* cola de mensajes del proceso servidor */
    mqd_t q_cliente;        /* cola de mensajes para el proceso cliente */

    struct mensaje msg;     /* petición/mensaje */
    struct respuesta resultado; /* respuesta */
    struct mq_attr attr;
    char queuename[MAX_LENGTH_VALOR1];
    attr.mq_maxmsg = 1;
    attr.mq_msgsize = sizeof(struct respuesta);

    sprintf(queuename,  "/Cola.2-%d", getpid());
    q_cliente = mq_open(queuename, O_CREAT|O_RDONLY, 0700, &attr);
    if (q_cliente == -1) {
        perror("mq_open 1");
        return -1;
    }
    q_servidor = mq_open("/SERVIDOR.2", O_WRONLY);
    if (q_servidor == -1){
        mq_close(q_cliente);
        perror("mq_open 2");
        return -1;
    }


    /* se rellena la petición */
    strcpy(msg.operacion, "init");
    strcpy(msg.q_name, queuename);
    printf("Nombre cola: %s\n", msg.q_name);
    printf("Enviando petición init a servidor\n");
    printf("%s\n", msg.operacion);


    /* se envía la petición al servidor */
    if (mq_send(q_servidor, (const char *)&msg, sizeof(struct mensaje), 0) < 0){
        perror("mq_send");
        return -1;
    }
    if (mq_receive(q_cliente, (char *) &resultado, sizeof(struct respuesta), 0) < 0){
        perror("mq_recv");
        return -1;
    }
    printf("Recibida respuesta de servidor");


    mq_close(q_servidor);
    mq_close(q_cliente);
    mq_unlink(queuename);
    return resultado.status;
}

int set_value(int key, char *value1, int value2, double value3){
    mqd_t q_servidor;       /* cola de mensajes del proceso servidor */
    mqd_t q_cliente;        /* cola de mensajes para el proceso cliente */

    struct mensaje msg;     /* petición/mensaje */
    struct respuesta resultado; /* respuesta */
    struct mq_attr attr;
    char queuename[MAX_LENGTH_VALOR1];

    attr.mq_maxmsg = 1;
    attr.mq_msgsize = sizeof(struct respuesta);

    sprintf(queuename,  "/Cola.2-%d", getpid());
    q_cliente = mq_open(queuename, O_CREAT|O_RDONLY, 0700, &attr);
    if (q_cliente == -1) {
        perror("mq_open 1");
        return -1;
    }
    q_servidor = mq_open("/SERVIDOR.2", O_WRONLY);
    if (q_servidor == -1){
        mq_close(q_cliente);
        perror("mq_open 2");
        return -1;
    }


    /* se rellena la petición */
    strcpy(msg.operacion, "set_value");
    strcpy(msg.q_name, queuename);
    msg.key = key;
    strcpy(msg.value1, value1);
    msg.value2 = value2;
    msg.value3 = value3;

    if (mq_send(q_servidor, (const char *)&msg, sizeof(struct mensaje), 0) < 0){
        perror("mq_send");
        return -1;
    }
    if (mq_receive(q_cliente, (char *) &resultado, sizeof(struct respuesta), 0) < 0){
        perror("mq_recv");
        return -1;
    }


    mq_close(q_servidor);
    mq_close(q_cliente);
    mq_unlink(queuename);
    return resultado.status; 
}

int get_value(int key, char *value1, int *value2, double *value3){
    mqd_t q_servidor;       /* cola de mensajes del proceso servidor */
    mqd_t q_cliente;        /* cola de mensajes para el proceso cliente */

    struct mensaje msg;     /* petición/mensaje */
    struct respuesta resultado; /* respuesta */
    struct mq_attr attr;
    char queuename[MAX_LENGTH_VALOR1];

    attr.mq_maxmsg = 1;
    attr.mq_msgsize = sizeof(struct respuesta);

    sprintf(queuename,  "/Cola.2-%d", getpid());
    q_cliente = mq_open(queuename, O_CREAT|O_RDONLY, 0700, &attr);
    if (q_cliente == -1) {
        perror("mq_open 1");
        return -1;
    }
    q_servidor = mq_open("/SERVIDOR.2", O_WRONLY);
    if (q_servidor == -1){
        mq_close(q_cliente);
        perror("mq_open 2");
        return -1;
    }


    /* se rellena la petición */
    strcpy(msg.operacion, "get_value");
    strcpy(msg.q_name, queuename);
    msg.key = key;
   
    

    if (mq_send(q_servidor, (const char *)&msg, sizeof(struct mensaje), 0) < 0){
        perror("mq_send");
        return -1;
    }
    if (mq_receive(q_cliente, (char *) &resultado, sizeof(struct respuesta), 0) < 0){
        perror("mq_recv");
        return -1;
    }

    // Copiamos los valores de la respuesta en los punteros
    strcpy(value1, resultado.value1);
    *value2 = resultado.value2;
    *value3 = resultado.value3;

   

    mq_close(q_servidor);
    mq_close(q_cliente);
    mq_unlink(queuename);
    return resultado.status;
}

int modify_value(int key, char *value1, int value2, double value3){
    mqd_t q_servidor;       /* cola de mensajes del proceso servidor */
    mqd_t q_cliente;        /* cola de mensajes para el proceso cliente */

    struct mensaje msg;     /* petición */
    struct respuesta resultado; /* respuesta */
    struct mq_attr attr;
    char queuename[MAX_LENGTH_VALOR1];

    attr.mq_maxmsg = 1;
    attr.mq_msgsize = sizeof(struct respuesta);

    sprintf(queuename,  "/Cola.2-%d", getpid());
    q_cliente = mq_open(queuename, O_CREAT|O_RDONLY, 0700, &attr);
    if (q_cliente == -1) {
        perror("mq_open 1");
        return -1;
    }
    q_servidor = mq_open("/SERVIDOR.2", O_WRONLY);
    if (q_servidor == -1){
        mq_close(q_cliente);
        perror("mq_open 2");
        return -1;
    }


    /* se rellena la petición */
    strcpy(msg.operacion, "modify_value");
    strcpy(msg.q_name, queuename);
    msg.key = key;
    strcpy(msg.value1, value1);
    msg.value2 = value2;
    msg.value3 = value3;

    if (mq_send(q_servidor, (const char *)&msg, sizeof(struct mensaje), 0) < 0){
        perror("mq_send");
        return -1;
    }
    if (mq_receive(q_cliente, (char *) &resultado, sizeof(struct respuesta), 0) < 0){
        perror("mq_recv");
        return -1;
    }


    mq_close(q_servidor);
    mq_close(q_cliente);
    mq_unlink(queuename);
    return resultado.status;
}

int delete_key(int key){
    mqd_t q_servidor;       /* cola de mensajes del proceso servidor */
    mqd_t q_cliente;        /* cola de mensajes para el proceso cliente */

    struct mensaje msg;     /* petición */
    struct respuesta resultado; /* respuesta */
    struct mq_attr attr;
    char queuename[MAX_LENGTH_VALOR1];

    attr.mq_maxmsg = 1;
    attr.mq_msgsize = sizeof(struct respuesta);

    sprintf(queuename,  "/Cola.2-%d", getpid());
    q_cliente = mq_open(queuename, O_CREAT|O_RDONLY, 0700, &attr);
    if (q_cliente == -1) {
        perror("mq_open 1");
        return -1;
    }
    q_servidor = mq_open("/SERVIDOR.2", O_WRONLY);
    if (q_servidor == -1){
        mq_close(q_cliente);
        perror("mq_open 2");
        return -1;
    }


    /* se rellena la petición */
    strcpy(msg.operacion, "delete_key");
    strcpy(msg.q_name, queuename);
    msg.key = key;

    if (mq_send(q_servidor, (const char *)&msg, sizeof(struct mensaje), 0) < 0){
        perror("mq_send");
        return -1;
    }
    if (mq_receive(q_cliente, (char *) &resultado, sizeof(struct respuesta), 0) < 0){
        perror("mq_recv");
        return -1;
    }


    mq_close(q_servidor);
    mq_close(q_cliente);
    mq_unlink(queuename);
    return resultado.status;
}

int exist(int key){
    mqd_t q_servidor;       /* cola de mensajes del proceso servidor */
    mqd_t q_cliente;        /* cola de mensajes para el proceso cliente */

    struct mensaje msg;     /* petición */
    struct respuesta resultado; /* respuesta */
    struct mq_attr attr;
    char queuename[MAX_LENGTH_VALOR1];

    attr.mq_maxmsg = 1;
    attr.mq_msgsize = sizeof(struct respuesta);

    sprintf(queuename,  "/Cola.2-%d", getpid());
    q_cliente = mq_open(queuename, O_CREAT|O_RDONLY, 0700, &attr);
    if (q_cliente == -1) {
        perror("mq_open 1");
        return -1;
    }
    q_servidor = mq_open("/SERVIDOR.2", O_WRONLY);
    if (q_servidor == -1){
        mq_close(q_cliente);
        perror("mq_open 2");
        return -1;
    }


    /* se rellena la petición */
    strcpy(msg.operacion, "exist");
    strcpy(msg.q_name, queuename);
    msg.key = key;

    if (mq_send(q_servidor, (const char *)&msg, sizeof(struct mensaje), 0) < 0){
        perror("mq_send");
        return -1;
    }
    if (mq_receive(q_cliente, (char *) &resultado, sizeof(struct respuesta), 0) < 0){
        perror("mq_recv");
        return -1;
    }


    mq_close(q_servidor);
    mq_close(q_cliente);
    mq_unlink(queuename);
    return resultado.status;
}

int copy_key( int key1, int key2){
    mqd_t q_servidor;       /* cola de mensajes del proceso servidor */
    mqd_t q_cliente;        /* cola de mensajes para el proceso cliente */

    struct mensaje msg;     /* petición */
    struct respuesta resultado; /* respuesta */
    struct mq_attr attr;
    char queuename[MAX_LENGTH_VALOR1];

    attr.mq_maxmsg = 1;
    attr.mq_msgsize = sizeof(struct respuesta);

    sprintf(queuename,  "/Cola.2-%d", getpid());
    q_cliente = mq_open(queuename, O_CREAT|O_RDONLY, 0700, &attr);
    if (q_cliente == -1) {
        perror("mq_open 1");
        return -1;
    }
    q_servidor = mq_open("/SERVIDOR.2", O_WRONLY);
    if (q_servidor == -1){
        mq_close(q_cliente);
        perror("mq_open 2");
        return -1;
    }


    /* se rellena la petición */
    strcpy(msg.operacion, "copy_key");
    strcpy(msg.q_name, queuename);
    msg.key = key1;
    msg.key2 = key2;


    if (mq_send(q_servidor, (const char *)&msg, sizeof(struct mensaje), 0) < 0){
        perror("mq_send");
        return -1;
    }
    if (mq_receive(q_cliente, (char *) &resultado, sizeof(struct respuesta), 0) < 0){
        perror("mq_recv");
        return -1;
    }


    mq_close(q_servidor);
    mq_close(q_cliente);
    mq_unlink(queuename);
    return resultado.status;
}

