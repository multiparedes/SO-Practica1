#include "my_lib.h"

//Mi función strnlen.
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

//Mi función strcmp.
int my_strcmp(const char *str1, const char *str2) {
    //Variable para almacenar la resta ASCII.
    int resta = 0;
    //Variable que controla la longitud.
    int longitud = 0;
    //Comparar mientras les lletres sean iguales y no acabemos ningun string.
    while(resta == 0 && (*(str1 + longitud) != '\0' || *(str2 + longitud) != '\0')) {
        //Hacemos la resta de caracteres ASCII.
        resta = *(str1 + longitud) - *(str2 + longitud);
        //Avanzamos al siguiente ASCII.
        longitud++;
    }
    //Retornamos la resta.
    return resta;
}

//Mi función strcpy.
char *my_strcpy(char *dest, const char *src) {
    //Variable que controla la longitud.
    int longitud = 0;
    //Mientras la cadena src no haya acabado sigue.
    while(*(src + longitud) != '\0') {
        //Copiamos el ASCII de src + posición en
        //la posición de destino correspondiente.
        *(dest + longitud) = *(src + longitud);
        //Avanzamos al siguiente ASCII.
        longitud++;
    }
    //Añadimos el caracter de final.
    *(dest + longitud) = '\0';
    //Retornamos el puntero a la dirección copiada.
    return dest;
}

//Mi función strncpy.
char *my_strncpy(char *dest, const char *src, size_t n) {
    //Mientras longitud sea menor al número de caracteres a copiar sigue.
    for(int longitud = 0; longitud < n; longitud++) {
        //Copiamos el ASCII de src + posición en
        //la posición de destino correspondiente.
        *(dest + longitud) = *(src + longitud);
    }
    //Retornamos el puntero a la dirección copiada.
    return dest;
}

//Mi función strcat. 
char *my_strcat(char *dest, const char *src){
    //Guardamos las longitudes de los string.
    int lendest = my_strlen(dest);
    int lensrc = my_strlen(src);
    int lentotal = lendest + lensrc + 1;
    //Copiamos los caracteres de src al final de dst.
    for (int i = 0; i < lensrc; ++i) {
        *(dest + lendest + i) = *(src + i);
    }
    //Añadimos el caracter de final.
    *(dest + lentotal - 1) = '\0';
    //Retornamos el puntero.
    return dest;
}

//Mi función strchr.
char *my_strchr(const char *str, int c){
    //Variable que controla la longitud.
    int longitud = 0;
    //Mientras la cadena no haya terminado sigue.
    while(*(str + longitud) != '\0') {
        //Si el caracter coincide con el parametros sal.
        if(*(str + longitud) == c) {
            //Hacemos el casteo para retornar el puntero adecuado.
            return((char *)(str + longitud));
        } else {
            //Si no incrementa la longitud 
            //para apuntar al siguiente char.
            longitud++;
        }
    }
    //Si al acabar la cadena no ha encontrado el caracter devolvemos NULL.
    return  NULL;
}   

// < PARTE 2> //

//Función para inicializar una pila.
struct my_stack *my_stack_init(int size) {
    //Creamos el puntero de pila y le reservamos memoria.
    struct my_stack *p_my_stack = malloc(sizeof(struct my_stack));
    //Assignamos el size passado por parámetro y ponemos top a NULL.
    p_my_stack->size = size; 
    p_my_stack->top = NULL;
    //Retornamos el puntero a la pila.
    return p_my_stack;
}

//Función para añadir un nodo a la pila. 
int my_stack_push(struct my_stack *stack, void *data) {
    //Si no existe el stack o este no puede almacenar retornamos error (-1).
    if(stack == NULL || stack->size <= 0) {
        return -1;
    } else {
        //Creamos el puntero al nodo y le reservamos memória.
        struct my_stack_node *nuevo_nodo;
        nuevo_nodo = malloc(sizeof(struct my_stack_node));
        //Assignamos el valor data dado por parámetro.
        nuevo_nodo->data = data;    
        //Reorganizamos los enlaces de los nodos.
        nuevo_nodo->next = stack->top;
        stack->top = nuevo_nodo;
    }
    //Si no ha habido ningún error retornamos 0.
    return 0;
}

//Función para eliminar un nodo de la pila. 
void *my_stack_pop (struct my_stack *stack){
    //Si el top no es NULL entra.
    if(stack->top){
        //Creamos el puntero al nodo y le reservamos memória.
        struct my_stack_node *eliminado = stack->top;
        stack->top = stack->top->next;
        //Creamos un puntero tipo void con la data del nodo a eliminar.
        struct my_data *ret = eliminado->data;  
        //Liberamos la memória ocupada por el nodo.
        free(eliminado);
        //Retornamos el puntero tipo void con los datos del nodo.
        return ret; 
    }
    //Si el top es NULL retorna NULL.
    else {return NULL;}   
}

//Función para determinar la longitud de una pila.
int my_stack_len (struct my_stack *stack){
    //Variable que controla la longitud.
    int longitud = 0;
    //Creamos un puntero a nodo y le assignamos el top.
    struct my_stack_node *nodo;
    nodo = stack->top;
    //Mientras el nodo no sea NULL sigue.
    while(nodo != NULL){
        //Apuntamos al siguiente nodo.
        nodo = nodo->next;
        //Incrementamos la longitud.
        longitud++;
    }
    //Retornamos la longitud de la pila.
    return  longitud;
}

//Función para liberar la memória asociada a una pila.
int my_stack_purge(struct my_stack *stack){
    //Variable que controla el numero de bytes liberados.
    int liberados = 0;
    //Mientras el top no sea NULL sigue.
    while (stack->top){
        //Sacamos el nodo de la pila y guardamos su campo data.
        void *data = my_stack_pop(stack);
        //Incrementamos el número de bytes liberados.
        liberados = liberados + sizeof(struct my_stack_node) + stack->size;
        //Liberamos de memória el campo data.
        free(data);        
    }
    //Liberamos el puntero a la pila.
    free(stack);
    //Incrementamos el número de bytes liberados.
    liberados = liberados + sizeof(struct my_stack);
    //Retornamos el número de bytes liberados.
    return liberados;
}

//Método própio para devolver un nodo dada una posición.
//Lo usamos para crear la pila auxiliar.
struct my_stack_node *my_stack_seek(struct my_stack *stack, int pos) {
    //Creamos un puntero a nodo y le assignamos el top de la pila (pos = 0).
    struct my_stack_node *ret = stack->top;
    //Avanzamos X nodos en la pila.
    for(int i = 0; i < pos; i++) {
        //Apuntamos al siguiente nodo.
        ret = ret->next;
    }
    //Retornamos el nodo pedidio.
    return ret;
}

int my_stack_write(struct my_stack *stack, char *filename) {
    
    int contador = 0;
    struct my_stack *pila_aux = my_stack_init(stack->size);

    for(int num_node = 0; num_node < my_stack_len(stack); num_node++) {
        my_stack_push(pila_aux,my_stack_seek(stack,num_node)->data);
    }
    
    int file = open(filename,O_WRONLY|O_CREAT|O_TRUNC,S_IRUSR|S_IWUSR);

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
    int file = open(filename,O_RDONLY);
    int val_size;
    void *val_data;

    struct my_stack *stack;    

    if(file != -1) {
        int wr = read(file,&val_size,sizeof(int));
        
        if(wr == -1) {
            close(file);
            perror("ERROR: ");
            return NULL;
        }

        stack = my_stack_init(val_size);
        val_data = malloc(val_size);
        wr = read(file,val_data,stack->size);

        if(wr == -1) {
            close(file);
            perror("ERROR");
            return NULL;
        }

        while(wr > 0) {
            my_stack_push(stack,val_data);

            val_data = malloc(val_size);
            wr = read(file,val_data,stack->size);
            
            if(wr == -1) {
                close(file);
                perror("ERROR");
                return NULL;
            }
        }

    } else {
        close(file);
        perror("ERROR: ");
        return NULL;
    }
    close(file);
    return stack;
}