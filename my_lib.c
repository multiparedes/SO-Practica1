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

char *my_strncpy(char *dest, const char *src, size_t n) {

    for(int longitud = 0; longitud < n; longitud++) {
        *(dest + longitud) = *(src + longitud);
    }

    return dest;
}

char *my_strcat(char *dest, const char *src){

    int lendest = my_strlen(dest);
    int lensrc = my_strlen(src);
    int lentotal = lendest + lensrc + 1;

    for (int i = 0; i < lensrc; ++i) {
        *(dest + lendest + i) = *(src + i);
    }

    *(dest + lentotal - 1) = '\0';

   return dest;
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

struct my_stack *my_stack_init(int size) {

    struct my_stack *p_my_stack;
    p_my_stack = malloc(sizeof(struct my_stack));

    p_my_stack->size = size;
    p_my_stack->top = NULL;

    return p_my_stack;
}

int my_stack_push(struct my_stack *stack, void *data) {

    if(stack == NULL || stack->size <= 0) {
        return -1;
    } else {

        struct my_stack_node *nuevo_nodo;
        nuevo_nodo = malloc(sizeof(struct my_stack_node));

        nuevo_nodo->data = data;
        nuevo_nodo->next = stack->top;

        stack->top = nuevo_nodo;
    }
    return 0;
}

void *my_stack_pop (struct my_stack *stack){
    if(stack->top){
        struct my_stack_node *eliminado = stack->top;
        stack->top = stack->top->next;

        struct my_data *ret = eliminado->data;

        free(eliminado);
        return ret;
    }
    else {return NULL;}
}

int my_stack_len (struct my_stack *stack){

    int longitud = 0;

    struct my_stack_node *nodo;
    nodo = stack->top;

    while(nodo != NULL){
        nodo = nodo->next;
        longitud++;
    }

    return  longitud;
}

int my_stack_purge (struct my_stack *stack){
    int liberados = 0;

    while (stack->top){
        void *data = my_stack_pop(stack);
        liberados = liberados + sizeof(struct my_stack_node) + stack->size;
        free(data);
    }

    free(stack);
    liberados = liberados + sizeof(struct my_stack);

    return liberados;
}

struct my_stack_node *my_stack_seek(struct my_stack *stack, int pos) {

    struct my_stack_node *ret = stack->top;

    for(int i = 0; i < pos; i++) {
        ret = ret->next;
    }

    return ret;
}

int my_stack_write(struct my_stack *stack, char *filename) {

    int contador = 0;
    struct my_stack *pila_aux = my_stack_init(stack->size);

    for(int num_node = 0; num_node < my_stack_len(stack); num_node++) {
        my_stack_push(pila_aux,my_stack_seek(stack,num_node)->data);
    }

    int file = open(filename,O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);

    if(file != -1) {

        int wr = write(file, &(stack->size), sizeof(int));
        if(wr == -1) {
            close(file);
            perror("ERROR: ");
            return -1;
        }

        struct my_stack_node *node_aux = my_stack_pop(pila_aux);

        while(node_aux != NULL) {
            wr = write(file, &(node_aux->data), pila_aux->size);
            if(wr == -1){
                close(file);
                perror("ERROR: ");
                return -1;
            }
            node_aux = my_stack_pop(pila_aux);
            contador++;
        }

        close(file);

    } else {
        perror("ERROR: ");
        return -1;
    }

    return contador;
}


struct my_stack *my_stack_read(char *filename) {

}
