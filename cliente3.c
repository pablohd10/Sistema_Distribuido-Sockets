#include <stdio.h>
#include "claves.h"


int main(void) {
    /* CLIENTE 3 */
    printf("----------------CLIENTE3-----------------: \n");
    printf("\nINIT\n");
    int status_init1 = init();
    printf("resultado de init1=%d\n", status_init1);

    printf("\nSET_VALUE\n");
    printf("Tratamos de insertar una cadena con mas de 255 caracteres:\n");
    int status_set_value1 = set_value(200, "Esta cadena tiene mas de 255 carceteres. KSJDFHLASHFANFASKJNKFNASNFANFASKLmd,nnsmnfnfnkajaknjnjfknadnkankajdnkasdnfkjafnkjdfnkjaknjfndfknndfknakjsdjknfdalsfnjdanfd.fsananjfan jk.cnv.ds kf.n dsanbfjsdnkdjsnfnafm,nf,mfndfnmdnma,fsm,nfdnfd,mnfsdm,nafm,nfmn,ddfmn,fmn,ma,nfm,fndmn,dfmfnd,aamn,m,dm,fnsmfn,damfn,dfa.mn,fmdn,fm,an.mf,dnmd,nffmdn,am,nf", 2, 3.0);
    printf("resultado de set_value1=%d\n", status_set_value1);

    printf("\nComprobamos que el programa sigue ejecutandose sin verse afectado por el error\n");
    printf("Chequeamos si existe la clave 200:\n");
    int status_exist1_1 = exist(200);
    printf("Resultado de exist clave 200 = %d --> no existe\n", status_exist1_1);


    printf("---------------END CLIENTE3------------------\n");
    return 0;
}

