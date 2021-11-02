#include "my_lib.h"

//Mi función de strnlen.
size_t my_strlen(const char *str) {
    size_t len = 0;
    //Mientras no encontremos el caracter de escape sigue.
    while(*(str + len) != '\0') {
        //Incrementa la longitud.
        len++;
    }
    //Devolvemos la longitud.
    return len;
}

int my_strcmp(const char *str1, const char *str2) {
    //Variable per detectar la seqüència.
    int resta = 0;
    //Variable que controla la longitud.
    int len = 0;

    //Compara mentres les lletres siguin igual i no acabem ninguna string.
    while(resta == 0 && (*(str1 + len) != '\0' || *(str2 + len) != '\0')) {
        //Feim una resta de caràcters ASCII.
        resta = *(str1 + len) - *(str2 + len);
        len++;
    }

    //Retornam el resultat.
    return resta;
}

char *my_strcpy(char *dest, const char *src) {

    int longitud = 0;

    while(*(src + longitud) != '\0') {
        *(dest + longitud) = *(src + longitud);
        longitud++;
    }

    *(dest + longitud) = '\0';
    return dest;
}

/*FUNCIONA PERUANAMENT - ARREGLAR LONGITUDS*/

char *my_strncpy(char *dest, const char *src, size_t n) {

    for(int longitud = 0; longitud < n; longitud++) {
        *(dest + longitud) = *(src + longitud);
    }
    
    return dest;
}

/*FALLA*/

char *my_strcat(char *dest, const char *src){

    int lendest = my_strlen(dest);
    int lensrc = my_strlen(src);
    int lentotal = lendest + lensrc + 1;

    char *aux = malloc(lentotal * sizeof(char));

    my_strcpy(aux, dest);

    for (int i = 0; i < lensrc; ++i) {
        *(aux + lendest + i) = *(src + i);
    }

    *(aux + lentotal - 1) = '\0';

   return aux;
}

char *my_strchr(const char *str, int c){

    int longitud = 0;

    while(*(str + longitud) != '\0') {
        if(*(str + longitud) == c) {
            return( (char *)(str + longitud) );
        } else {
            longitud++;
        }
    }
    return  NULL;
}   