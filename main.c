#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* DEFINICION DEL TAMAÑO DE ARREGLOS
 * (ESTOS SON DINAMICOS PERO DECIDIMOS DEJAR LAS VARIABLES DEFINIDAS
 * PARA EVITAR TRABAJAR CON TAMAÑOS DISTINTOS)
*/

#define MAXPRODUCTOS 10000
#define MAXVENTAS 10000

//Hacerlo a doble asterisco y con 10000
// DEFINICION ESTRUCTURAS //

struct SistemaDercos{
    struct NodoProductos *headMarcas;
    struct  NodoComunas *headComunas;
};

struct NodoComunas // ARBOL COMUNAS //
{
    int id;
    struct  Comuna *datosComuna;
    struct NodoComunas *izq, *der;
};

struct Comuna
{
    char *nombreRegion;
    char *nombreComuna;
    struct NodoSucursales *sucursales;

};

struct NodoSucursales // LISTA DOBLEMENTE ENLAZADA  //
{
    struct Sucursal *datosSucursal;
    struct NodoSucursales *sig, *ant;
};

struct Sucursal
{
    char *nombre;
    struct Ventas **ventasSucursal; // ARREGLO DE VENTAS DINAMICO NO COMPACTO //
    struct NodoStock *stockSucursal;
};

struct Ventas
{
    char *rutCliente;
    float monto;
    struct producto *productoVenta;

};

struct NodoStock  // LISTA CIRCULAR SIMPLEMENTE ENLAZADA //
{
    int cantidadProducto;
    struct producto *marca;
    struct NodoStock *sig;
};

struct NodoProductos // LISTA DOBLEMENTE ENLAZADA //
{
    char *nombreMarca;
    struct producto **productosMarca; // ARREGLO DINAMICO PRODUCTOS DE LA MARCA //
    struct NodoProductos *sig, *ant;
};

struct producto  // ACCESORIOS, AUTOS O REFACCIONES //
{
    char *nombre;
    char *tipoProducto;
    char *proveedor;
    int idProducto;
    int precio;
    int recallProducto;
};
///////////////  AGREGAR, ELIMINAR, BUSCAR, MODIFICAR Y LISTAR DE CADA ESTRUCTURA  /////////////////
////////// NODO PRODUCTOS /////////
//////// MODIFICAR /////////
int modificarNodoProductos (struct NodoProductos *head, char *nombreModificar)
{
    struct NodoProductos *rec;
    if( head != NULL )
    {
        rec = head;
        while (rec != NULL)
        {
            if (strcmp (rec -> nombreMarca, nombreModificar) == 0)
            {
                rec->nombreMarca= nombreModificar;
                return 1; // RETORNA UNO SI SE LOGRO EXITOSAMENTE MODIFICAR, 0 SI NO //
            }
            rec = rec -> sig;
        }
    }
    return 0;
}
/////// ELIMINAR NODO PRODUCTOS ////////
void eliminarNodoProducto(struct NodoProductos **head, char *nombreMarca)
{
    struct NodoProductos *rec;
    if(*head != NULL)
    {
        rec = *head;
        while(rec != NULL)
        {
            if( (strcmp ( rec -> nombreMarca, nombreMarca ) == 0) )
            {
                if(rec == *head) // PRIMER NODO LISTA //
                {
                    *head = rec -> sig;
                    (*head) -> ant = NULL;
                }
                if(rec -> ant && rec -> sig != NULL) // NODO INTERMEDIO //
                {
                    rec -> ant -> sig = rec -> sig;
                    rec -> sig -> ant = rec -> ant;
                }
                else // NODO FINAL LISTA //
                {
                    rec -> ant -> sig = NULL;
                }
            }
            rec = rec -> sig;
        }
        return;
    }

}
/////////// BUSCAR NODO PRODUCTO ///////////
struct NodoProductos *buscarNodoProducto (struct NodoProductos *head, char *nombreMarca)
{
    struct NodoProductos *rec;
    if(head != NULL)
    {
        rec = head;
        while (rec != NULL)
        {
            if (strcmp (rec -> nombreMarca, nombreMarca) == 0)
            {
                return rec;
            }
            rec = rec -> sig;
        }
    }
    return NULL;
}
/////////// AGREGAR NODO PRODUCTO /////////////
struct NodoProductos *crearNodo (char *nombre)
{
    struct NodoProductos *nuevo;
    nuevo =  (struct NodoProductos *) malloc(sizeof(struct NodoProductos));
    nuevo -> nombreMarca = (char *) malloc(sizeof(char) * strlen(nombre));
    strcpy(nuevo -> nombreMarca, nombre);
    nuevo -> ant = NULL;
    nuevo -> sig = NULL;
    nuevo -> productosMarca = (struct producto **)malloc(sizeof(struct producto *) * MAXPRODUCTOS);
    return nuevo;
}
int enlazarNodoProducto(struct NodoProductos **head, struct NodoProductos *nuevo)
{
    if(*head == NULL)
    {
        *head = nuevo;
        return 1;
    }
    else
    {
        struct NodoProductos *rec = *head;
        while(rec != NULL)
        {
            if(rec -> sig == NULL || buscarNodoProducto(*head,nuevo->nombreMarca) == NULL)
            {
                rec -> sig = nuevo;
                rec -> sig -> ant = rec;
                return 1;
            }
            rec = rec -> sig;
        }
    }
    return 0;
}
////////// LISTAR NODO PRODUCTO ///////////
void listarNodoProducto (struct NodoProductos *head)
{
    struct NodoProductos *rec;
    if(head != NULL)
    {
        rec = head;
        while (rec != NULL)
        {
            printf("NOMBRE MARCA = %s\n", rec -> nombreMarca);
            rec = rec -> sig;
        }
    }
}
////////////////////// PRODUCTOS //////////////////////

//////////// BUSCAR PRODUCTO ////////////
struct producto *buscarProducto (struct NodoProductos *head, int idBuscado)
{
    if(head != NULL)
    {
        int i = 0;
        for(i = 0;i < MAXPRODUCTOS; i++)
        {
            if(head -> productosMarca[i] != NULL)
            {
                if (head -> productosMarca[i] -> idProducto == idBuscado)
                {
                    return head -> productosMarca[i];
                }
            }
        }
    }
    return NULL;
}

///////// MODIFICAR PRODUCTOS ////////
//Pedir en main el cambio de datos

void realizarCambios(struct producto **modificar, int desNombre, int desTipo, int desProveedor, int desId, int desRecall, int desPrecio){
    if (desNombre != 0){
        printf("POR FAVOR, INGRESE EL NUEVO NOMBRE DEL PRODUCTO\n");
        scanf("%100[^\n]s", (*modificar) -> nombre);
    }
    if (desTipo != 0){
        printf("POR FAVOR, INGRESE EL NUEVO TIPO DEL PRODUCTO\n");
        scanf("%100[^\n]s", (*modificar) -> tipoProducto);
    }
    if (desProveedor != 0){
        printf("POR FAVOR, INGRESE EL NUEVO PROVEEDOR DEL PRODUCTO\n");
        scanf("%100[^\n]s", (*modificar) -> proveedor);
    }
    if (desId!= 0){
        printf("POR FAVOR, INGRESE LA NUEVA ID DEL PRODUCTO\n");
        scanf("%d", &(*modificar) -> idProducto);
    }
    if (desRecall != 0){
        printf("POR FAVOR, INGRESE LA NUEVA CANTIDAD DE RECALLS DEL PRODUCTO\n");
        scanf("%d", &(*modificar) -> recallProducto);
    }
    if (desPrecio != 0){
        printf("POR FAVOR, INGRESE EL NUEVO PRECIO DEL PRODUCTO\n");
        scanf("%d", &(*modificar) -> precio);
    }
    return;
}

int modificarProducto (struct NodoProductos **ref, int idBuscado) {

    int cambioNombre, cambioTipo, cambioProovedor, cambioId, cambioRecall, cambioPrecio;
    struct producto *aModificar;
    if (*ref){
        aModificar = buscarProducto(*ref, idBuscado);
        if (aModificar){
            printf("SI NO DESEA MODIFICAR EL PARAMETRO CORRESPONDIENTE, INGRESE UN 0 CUANDO CORRESPONDA\n");

            printf("QUIERE CAMBIAR EL NOMBRE DEL PRODUCTO?\n");
            scanf("%d", &cambioNombre);

            printf("QUIERE CAMBIAR EL TIPO DE PRODUCTO?\n");
            scanf("%d", &cambioTipo);

            printf("QUIERE CAMBIAR EL PROOVEDOR DEL PRODUCTO?\n");
            scanf("%d", &cambioProovedor);

            printf("QUIERE CAMBIAR EL ID DEL PRODUCTO?\n");
            scanf("%d", &cambioId);

            printf("QUIERE CAMBIAR LOS RECALLS DEL PRODUCTO?\n");
            scanf("%d", &cambioRecall);

            printf("QUIERE CAMBIAR EL PRECIO DEL PRODUCTO?\n");
            scanf("%d", &cambioPrecio);

            realizarCambios(&aModificar, cambioNombre, cambioTipo, cambioProovedor, cambioId, cambioRecall, cambioPrecio);
            return 1;
        }

    }
    return 0;
}
/////////////// ELIMINAR PRODUCTO /////////////////7
int eliminarProducto(struct NodoProductos *head, int idEliminar)
{
    int i;
    if(head != NULL)
    {

        for(i = 0; i < MAXPRODUCTOS; i++)
        {
            if(head -> productosMarca[i] != NULL)
            {
                if (head-> productosMarca[i] -> idProducto == idEliminar) {
                    head-> productosMarca[i] = NULL;
                    return 1;
                }
            }
        }
    }
    return 0;
}

///////////// AGREGAR PRODUCTO /////////////
int agregarProducto(struct NodoProductos **head, char *nombreMarca)
{
    struct NodoProductos *ref;
    char buffer[100];
    if (*head != NULL)
    {
        ref = buscarNodoProducto(*head, nombreMarca);
        if(ref != NULL) {
            int i = 0;
            for (i = 0; i < MAXPRODUCTOS; i++) {
                if (ref -> productosMarca[i] == NULL) {

                    printf("INGRESE NOMBRE PRODUCTO\n");
                    scanf("%100[^\n]s", buffer);
                    ref->productosMarca[i]-> nombre = (char *)malloc(sizeof(char) * strlen(buffer));
                    strcpy((ref->productosMarca[i]->nombre), buffer);

                    printf("INGRESE TIPO PRODUCTO\n");
                    scanf("%100[^\n]s", buffer);
                    ref->productosMarca[i]->tipoProducto = (char *)malloc(sizeof(char) * strlen(buffer));
                    strcpy((ref->productosMarca[i]->tipoProducto), buffer);

                    printf("INGRESE PROVEEDOR\n");
                    scanf("%100[^\n]s", buffer);
                    ref->productosMarca[i]->proveedor = (char *)malloc(sizeof(char) * strlen(buffer));
                    strcpy((ref->productosMarca[i]->proveedor), buffer);

                    printf("INGRESE ID PRODUCTO\n");
                    scanf("%d", &(ref->productosMarca[i]->idProducto));
                    printf("INGRESE PRECIO\n");
                    scanf("%d", &(ref->productosMarca[i]->precio));
                    ref->productosMarca[i]->recallProducto = 0;
                    return 1;
                }
            }
        }
    }
    return 0;
}
///////// LISTAR PRODUCTO //////////
void listarProducto(struct NodoProductos *ref)
{
    if(ref != NULL)
    {
        int i = 0;
        for(i = 0; i < MAXPRODUCTOS ; i++)
        {
            if(ref -> productosMarca[i] != NULL)
            {
                printf("%s NOMBRE PRODUCTO: \n", ref->productosMarca[i]->nombre);
                printf("%s TIPO PRODUCTO: \n", ref->productosMarca[i]->tipoProducto);
                printf("%s PROVEEDOR: \n", ref->productosMarca[i]->proveedor);
                printf("%d ID PRODUCTO: \n", ref->productosMarca[i]->idProducto);
                printf("%d PRECIO: \n", ref->productosMarca[i]->precio);
                if (strcmp(ref->productosMarca[i]->tipoProducto, "AUTO") == 0)
                {
                    printf("%d RECALL AUTO: \n", ref->productosMarca[i]->recallProducto);
                }
            }
        }
    }
}
//////////////////////// NODO COMUNAS ////////////////////////
//////////////// BUSCAR NODO COMUNAS ///////////////////////
struct NodoComunas *buscarNodoComuna(struct NodoComunas *rec, int idBuscar) //FUNCION RECURSIVA
{
    if(rec == NULL || rec -> id == idBuscar)
    {
        return rec;
    }
    else
    {
        if(rec -> id > idBuscar)
        {
            return(buscarNodoComuna(rec -> izq, idBuscar));
        }
        else
        {
            return (buscarNodoComuna(rec -> der, idBuscar));
        }
    }
}
///////////////// MODIFICAR NODO COMUNAS ////////////////
int modificarNodoComunas(struct  NodoComunas **head, int idModificar, char *regionModificar, char *comunaModificar) // hay q buscarlo, sacarlo, enlazar y despues agregarlo //
{

    if((*head) != NULL)
    {
        struct NodoComunas *rec = (*head);
        rec = buscarNodoComuna(rec,idModificar);
        rec->datosComuna->nombreRegion = regionModificar;
        rec->datosComuna->nombreComuna = comunaModificar;
        return 1; //  SI LOGRO MODIFICAR
    }
    return 0; // NO LOGRO MODIFICAR
}
//////////////////// ELIMINAR NODO COMUNAS //////////////////
void reemplazarNodoComuna(struct NodoComunas **abb, struct NodoComunas **aux)
{
    if(!((*abb) -> der))
    {
        (*aux) -> id = (*abb) -> id;
        *aux = *abb;
        *abb = (*abb) -> izq;
    }
    else
    {
        reemplazarNodoComuna(&(*abb) -> der, &(*aux));
    }
}
void eliminarNodoComuna (struct NodoComunas **abb, int idEliminar)
{
    struct NodoComunas *aux = NULL;

    if((*abb) == NULL)
    {
        return;
    }
    if((*abb) -> id < idEliminar)
    {
        eliminarNodoComuna(&(*abb) -> der, idEliminar);
    }
    else
    {
        if((*abb) -> id > idEliminar)
        {
            eliminarNodoComuna(&(*abb) -> izq, idEliminar);
        }
        else
        {
            if ((*abb) -> id == idEliminar)
            {
                aux = *abb;
                if (!(*abb) -> izq)
                {
                    *abb = (*abb) -> der;
                }
                else
                {
                    if (!((*abb) -> der))
                    {
                        *abb = (*abb) -> izq;
                    }
                    else
                    {
                        reemplazarNodoComuna(&(*abb) -> izq, &aux);
                    }
                    free(aux);
                }
            }
        }
    }
}
///////////// AGREGAR NODO COMUNAS ///////////////////
//COMO SUPUESTO PARA ESTA FUNCION SI SE QUIERE AGREGAR UNA COMUNA TIENE QUE SER EL ID DE LA COMUNA A AGREGAR TIENE QUE SE UN NUMERO QUE NO SE ENCUENTRE EN MEDIO DE DOS NUMEROS YA EXISTENTES EN EL ID
void agregarNodoComunas (struct NodoComunas **rec, int idAgregar, struct Comuna *datos)
{
    if((*rec) == NULL)
    {
        (*rec) = (struct NodoComunas *) malloc(sizeof(struct NodoComunas));
        (*rec)-> id = idAgregar;
        (*rec)-> izq = NULL;
        (*rec)-> der = NULL;
        (*rec) -> datosComuna = datos;
    }
    else
    {
        if((*rec) -> id != idAgregar) // SI NO ESTA EN EL ARBOL //
        {
            if((*rec) -> id > idAgregar)
            {
                agregarNodoComunas((&(*rec) -> izq), idAgregar, datos);
            }
            else
            {
                agregarNodoComunas((&(*rec) -> der), idAgregar, datos);
            }
        }
    }

}
////////////// LISTAR NODO COMUNAS //////////////////
void listarNodoComuna (struct NodoComunas *rec)
{
    if(rec == NULL)
    {
        return;
    }
    if (rec != NULL) // RECORRIDO PRE ORDEN
    {
        printf("EL ID DE LA COMUNA ES: %d\n",rec -> id);
        printf("EL NOMBRE DE LA REGION ES: %s\n", rec->datosComuna->nombreRegion);
        printf("EL NOMBRE DE LA COMUNA ES: %s\n", rec->datosComuna->nombreComuna);
        listarNodoComuna(rec -> izq);
        listarNodoComuna(rec -> der);
    }
}

//////////// COMUNA //////////////
// AGREGAR COMUNA //
struct Comuna *agregarComuna ()
{
    struct Comuna *nodo = (struct Comuna*)malloc(sizeof (struct Comuna));
    char buffer[100];


    printf("INGRESE NOMBRE REGION\n");
    scanf("%100[^\n]s", buffer);
    nodo -> nombreRegion =  (char *)malloc(sizeof(char) * strlen(buffer));
    strcpy(nodo -> nombreRegion, buffer);

    printf("INGRESE NOMBRE COMUNA\n");
    scanf("%100[^\n]s", buffer);
    nodo -> nombreComuna = (char *)malloc(sizeof(char) * strlen(buffer));
    strcpy(nodo -> nombreComuna, buffer);

    nodo -> sucursales = NULL;
    return nodo;
}
/////////////////////  NODO SUCURSALES /////////////////////
///////////////// MODIFICAR NODO SUCURSALES /////////////////777
int modificarNodoSucursal(struct NodoSucursales **head, char *nombreSucursal, char *nombreNuevo)
{
    struct NodoSucursales *rec;
    if(*head != NULL)
    {
        rec = *head;
        while (rec != NULL)
        {
            if(strcmp(rec -> datosSucursal -> nombre, nombreSucursal) == 0)
            {
                rec -> datosSucursal -> nombre= nombreNuevo;
                return 1;
            }
            rec = rec -> sig;
        }
    }
    return 0;
}
/////////////////// ELIMINAR NODO SUCURSALES/ SUCURSAL ////////////////
void eliminarNodoSucursal(struct NodoSucursales **head, struct  NodoSucursales *rec) // LA REFERENCIA SE LA OTORGA LA FUNCION BUSCAR //
{
    if (head != NULL)
    {
        if (rec == *head) // PRIMER NODO LISTA
        {
            *head = rec -> sig;
            (*head) -> ant = NULL;
            return;
        }
        if (rec -> ant && rec -> sig != NULL) // NODO INTERMEDIO
        {
            rec -> ant -> sig = rec -> sig;
            rec -> sig -> ant = rec -> ant;
            return;
        }
        else // NODO FINAL
        {
            rec -> ant -> sig = NULL;
            return;
        }
    }
}
/////////// BUSCAR NODO SUCURSALES/SUCURSAL /////////////
struct NodoSucursales *buscarNodoSucursal (struct NodoSucursales *head, char *buscado)
{
    struct NodoSucursales *rec;
    if(head != NULL)
    {
        rec = head;
        while (rec != NULL)
        {
            if (strcmp(rec -> datosSucursal -> nombre, buscado) == 0)
            {
                return rec;
            }
            rec = rec -> sig;
        }
    }
    return NULL;
}
///////////// AGREGAR NODO SUCURSALES ////////////
void agregarNodoSucursal(struct NodoSucursales *head, struct Sucursal *datos)
{
    struct NodoSucursales *rec;
    struct NodoSucursales *nuevo;
    nuevo = ((struct NodoSucursales*)malloc(sizeof(struct NodoSucursales)));
    nuevo -> datosSucursal = datos;
    nuevo -> ant = NULL;
    nuevo -> sig = NULL;

    if(head == NULL)
    {
        head = nuevo;
        return;
    }
    else
    {
        rec = head;
        while( rec != NULL )
        {
            if( rec -> sig == NULL)
            {
                rec -> sig = nuevo;
                rec -> sig -> ant = rec;
                return;
            }
            rec = rec -> sig;
        }
    }
}
/////////////// LISTAR NODO SUCURSALES/SUCURSALES ////////////////7
void listarSucursal(struct NodoSucursales *head)
{
    struct NodoSucursales *rec;
    if(head != NULL)
    {
        rec = head;
        while (rec != NULL)
        {
            printf("NOMBRE DE LA SUCURSAL: %s", rec -> datosSucursal -> nombre);
            rec = rec -> sig;
        }
    }
}
/////// AGREGAR SUCURSAL //////////
struct Sucursal *crearSucursal()
{
    struct Sucursal *nuevo;
    char buffer[100];
    nuevo = ((struct Sucursal*)malloc(sizeof(struct Sucursal)));

    printf("INGRESE EL NOMBRE DE LA SUCURSAL\n");
    scanf("%100s[^n]", buffer);
    nuevo -> nombre = (char*)malloc(sizeof(char) * strlen(buffer));
    nuevo -> stockSucursal = NULL;
    nuevo -> ventasSucursal = (struct Ventas **)malloc(sizeof(struct Ventas *) * MAXVENTAS);
    return nuevo;
}
/////// STOCK //////////
/////////////// MODIFICAR NODO STOCK ///////////////
int modificarNodoStock (struct NodoStock *head)
{
    struct NodoStock *rec;
    int idModificar = 0;
    if(head != NULL)
    {
        rec = head;
        printf("INGRESE EL ID DEL PRODUCTO EN STOCK\n");
        scanf("%d",&idModificar);
        do
        {
            if(rec -> marca -> idProducto == idModificar)
            {
                printf("INGRESE CANTIDAD A MODIFICAR\n"); //LA CANTIDAD MODIFICADA ES LA CANTIDAD TOTAL QUE EXISTE DEL PRODUCTO
                scanf("%d",&(rec -> cantidadProducto));
                return 1;
            }
            rec = rec -> sig;
        } while (rec != head);
    }
    return 0;
}
/////////////// ELIMINAR  NODO STOCK  ///////////////////

void eliminarNodoStock (struct NodoStock **head, int idEliminar)   // SE ELIMINARA BUSCANDO CON EL ID DEL PRODUCTO//
{
    struct NodoStock *rec;
    if((*head) != NULL)
    {
        rec = *head;
        if (rec->sig == *head && rec->marca->idProducto == idEliminar) {
            *head = NULL;
            return;
        }
        else
        {
            if (rec->marca->idProducto == idEliminar) // PRIMER CASO //
            {
                do
                {
                    rec =rec->sig;
                }while(rec->sig != *head);
                rec->sig= rec->sig->sig;
                return;
            }
            else
            {
                do {
                    if (rec->sig->marca->idProducto == idEliminar) {
                        rec->sig = rec->sig->sig;
                        return;
                    }
                    rec = rec->sig;
                } while (rec->sig != (*head));
            }
        }
    }
}
////////////////// BUSCAR NODO STOCK ///////////////////////////
struct NodoStock *buscarNodoStock (struct NodoStock **head, int  idProducto) // BUSCARA POR EL ID DEL PRODUCTO Y RETORNARA EL NODO STOCK DONDE ESTA //
{
    struct NodoStock *rec;
    if((*head) != NULL)
    {
        rec = *head;
        do
        {
            if(rec -> marca -> idProducto == idProducto)
            {
                return rec;
            }
            rec = rec -> sig;
        } while (rec != (*head));
    }
    return NULL;
}
//////////////// AGREGAR NODO STOCK /////////////////////
int agregarNodoStock (struct NodoStock **head, struct  producto *productos)
{
    struct NodoStock *rec;
    if((*head) == NULL)
    {
        (*head) = (struct NodoStock*)malloc(sizeof(struct NodoStock));
        scanf("CANTIDAD DEL STOCK DEL PRODUCTO: %d",&(*head) -> cantidadProducto);
        (*head) ->marca= productos;
        (*head) -> sig = *head;
        return 1;
    }
    else
    {
        rec = (*head);
        do {
            if(rec->marca->idProducto == productos->idProducto)
            {
                rec->cantidadProducto ++;
                return 1;
            }
            rec = rec -> sig;
        } while (rec -> sig != (*head));

        rec -> sig  = (struct NodoStock*)malloc(sizeof(struct NodoStock));
        scanf("CANTIDAD DEL STOCK DEL PRODUCTO: %d",&(*head) -> cantidadProducto);
        (*head) ->marca= productos;
        rec -> sig -> sig = *head;
        return 1;
    }
    return 0;
}
////////////////////// LISTAR STOCK ///////////////////
void listarNodoStock (struct NodoStock *head)
{
    struct NodoStock *rec;
    if(head != NULL)
    {
        rec = head;
        do
        {
            printf("%d STOCK PRODUCTO: \n",rec -> cantidadProducto);

            // IMPRIME EL STRUCT PRODUCTO DEL STOCK //
            printf("%s NOMBRE PRODUCTO: \n",rec -> marca -> nombre);
            printf("%s TIPO PRODUCTO: \n",rec -> marca-> tipoProducto);
            printf("%s PROVEEDOR: \n",rec -> marca -> proveedor);
            printf("%d ID PRODUCTO: \n",rec -> marca -> idProducto);
            printf("%d PRECIO: \n",rec -> marca -> precio);
            if(strcmp(rec -> marca -> tipoProducto, "AUTO") == 0)
            {
                printf("%d RECALL AUTO: \n",rec -> marca-> recallProducto);
            }
            rec = rec -> sig;
        } while (rec != head);
    }
}
////////////////////// VENTAS //////////////////
////////////////// AGREGAR VENTAS //////////////
int agregarVenta(struct Sucursal *sucursal, struct producto *ref)
{
    char buffer[100];
    if(sucursal != NULL && ref != NULL)
    {
        int i;
        for(i = 0; i < MAXVENTAS; i++)
        {
            if(sucursal -> ventasSucursal[i] == NULL)
            {
                printf("RUT CLIENTE: \n");
                scanf("%100[^\n]s", buffer);
                sucursal -> ventasSucursal[i] -> rutCliente = (char *)malloc(sizeof(char) * strlen(buffer));
                strcpy(sucursal -> ventasSucursal[i] -> rutCliente, buffer);

                printf("MONTO: \n");
                scanf("%f", &sucursal -> ventasSucursal[i] -> monto);
                sucursal -> ventasSucursal[i] -> productoVenta = ref;
                return 1;
            }
        }
    }
    return 0;
}
///////// BUSCAR VENTAS /////////////

struct Ventas *buscarVenta(struct Sucursal *sucursal, char *rutBuscado)
{
    if(sucursal != NULL)
    {
        int i = 0;
        for(i = 0; i < MAXVENTAS; i++)
        {
            if(sucursal -> ventasSucursal[i] != NULL)
            {
                if(strcmp(sucursal -> ventasSucursal[i] -> rutCliente, rutBuscado)==0)
                {
                    return sucursal->ventasSucursal[i];
                }
            }
        }
    }
    return NULL;
}
///////////// ELIMINAR VENTAS /////////////////
int eliminarVenta(struct Sucursal *sucursal, char *rutBuscado)
{
    if(sucursal != NULL)
    {
        int i = 0;

        for( i = 0; i < MAXVENTAS; i++)
        {
            if(sucursal -> ventasSucursal[i] != NULL)
            {
                if(strcmp(sucursal -> ventasSucursal[i] -> rutCliente, rutBuscado)==0)
                {
                    sucursal -> ventasSucursal[i] = NULL;
                    return 1;
                }
            }
        }
    }
    return 0;
}
/////////////// MODIFICAR VENTAS //////////////////
int modificarVenta(struct Sucursal *head, char *rutCliente, struct producto *nuevo)
{
    struct Ventas *ventaBuscada;
    if(head != NULL)
    {
        ventaBuscada = buscarVenta(head,rutCliente);
        if(ventaBuscada)
        {
            printf("INGRESE RUT:\n ");
            scanf("%100[^\n]s", ventaBuscada -> rutCliente);

            printf("INGRESE MONTO:\n ");
            scanf("%f\n", &(ventaBuscada) -> monto);
            ventaBuscada ->productoVenta = nuevo;
            return 1;
        }
    }
    return 0;
}
////////////// LISTAR VENTAS /////////////
void listarVentas(struct Sucursal *sucursal)
{
    if(sucursal != NULL)
    {
        int i = 0;
        for(i = 0; i < MAXVENTAS ; i++)
        {
            if(sucursal -> ventasSucursal[i] != NULL)
            {
                printf("RUT CLIENTE: %s\n", sucursal -> ventasSucursal[i] -> rutCliente);
                printf("MONTO: %f\n", sucursal -> ventasSucursal[i] -> monto);
                printf("NOMBRE: %s\n", sucursal -> ventasSucursal[i] -> productoVenta -> nombre);
                printf("ID DEL PRODUCTO: %d\n", sucursal -> ventasSucursal[i] -> productoVenta -> idProducto);
            }
        }
    }
}
// FUNCION MODELOS Y MARCAS DE AUTOS MAS VENDIDOS POR ZONA //
struct producto  *recorreVentas(struct Sucursal *ref, int *cont)
{
    if(ref != NULL)
    {
        struct producto *mayorVentas=NULL;
        int i, j, aux;
        aux=0;
        for(i=0 ; i<MAXVENTAS; i++)
        {
            cont=0;
            if(strcmp(ref->ventasSucursal[i]->productoVenta->tipoProducto, "AUTO")==0)
            {
                for(j=0 ; j<MAXVENTAS; j++)
                {
                    if(ref->ventasSucursal[i]->productoVenta->idProducto == ref->ventasSucursal[j]->productoVenta->idProducto)
                        (*cont) ++;
                }
                if(*cont >aux)
                    mayorVentas= ref->ventasSucursal[i]->productoVenta;
            }
        }
        *cont = aux;
        return mayorVentas;
    }
    return NULL;
}
// FUNCION MODELOS Y MARCAS DE AUTOS MAS VENDIDOS POR ZONA // por comuna
struct producto *mayorVenta(struct NodoSucursales*head, int *cont)
{
    if(head != NULL)
    {
        struct NodoSucursales*rec=head;
        struct producto *mayor= NULL;
        int aux=0;
        int i;
        while(rec != NULL)
        {
            recorreVentas(rec->datosSucursal,cont);
            if(*cont > aux)
            {
                if(mayor->idProducto == recorreVentas(rec->datosSucursal,cont)->idProducto)
                {
                    aux+=*cont;
                }
                else
                {
                    mayor= recorreVentas(rec->datosSucursal,cont);
                    aux= *cont;
                }
            }
            rec= rec->sig;
        }
        return mayor;
    }
    return NULL;
}
void recorrerABBVendidos(struct NodoComunas *ABB)
{
    if(ABB !=NULL)
    {
        int cont =0;
        recorrerABBVendidos(ABB -> izq);
        if(mayorVenta(ABB->datosComuna->sucursales,&cont)!=NULL)
        {
            printf("El auto mas vendido en la comuna de %s es el modelo %s",ABB->datosComuna->nombreComuna,mayorVenta(ABB->datosComuna->sucursales,&cont)->nombre);//muestra el auto msa vendido en cada comuna
        }
        recorrerABBVendidos(ABB -> der);
    }
}
// FUNCION CLIENTE QUE MAS DINERO GASTA EN LOS PRODUCTOS DE DERCOS DE UNA SUCURSAL ESPECIFICA //

int contarRuts(struct Ventas **array){
    //CONTAR CUANTAS VENTAS EN TOTAL SE HICIERON
    int i;
    int cont = 0;
    for (i = 0; i < MAXVENTAS; i++){
        if (array[i]) cont++;
    }
    return cont;
}

int noEsta(char **arrayRuts, int totalRuts, char *rutBuscado){
    int i;
    for (i = 0; i < totalRuts; i++){
        if (strcmp(arrayRuts[i], rutBuscado) == 0) return 0;
    }
    return 1;
}

void rellenarArrayRUTS(char **arrayRUTS, int *totalRuts, struct Ventas **array){
    int i;
    int rutsUnicos = 0;
    for (i = 0; i < MAXVENTAS; i++){
        if (noEsta(arrayRUTS, *totalRuts, array[i] -> rutCliente)){
            strcpy(arrayRUTS[rutsUnicos], array[i] -> rutCliente);
            rutsUnicos++;
        }
    }
    (*totalRuts) = rutsUnicos;
}

float contarGastosCliente(struct Ventas **array, char *cliente){
    float gastado = 0;
    int i;
    for (i = 0; i < MAXVENTAS; i++){
        if (strcmp(cliente, array[i] ->rutCliente) == 0) gastado += array[i] -> monto;
    }
    return gastado;
}

char *buscarClienteMasPudiente(struct Ventas **array){
    int i;
    int totalRuts = contarRuts(array);
    char * *arrayRUTS = NULL;
    char *masPudiente = NULL;
    float gastosMasPudiente;
    arrayRUTS = (char **)malloc(sizeof(char *) * totalRuts);
    rellenarArrayRUTS(arrayRUTS, &totalRuts, array);

    for (i = 0; i < totalRuts; i++){
        if (!masPudiente || contarGastosCliente(array, arrayRUTS[i]) > gastosMasPudiente){
            gastosMasPudiente = contarGastosCliente(array, arrayRUTS[i]);
            strcpy(masPudiente, arrayRUTS[i]);
        }
    }
    return masPudiente;
}

char *mayorClienteSucursal(struct NodoSucursales *head, char *nombreSucursal)
{
    char *mayor= NULL;
    struct NodoSucursales *rec;
    if (head){
        rec = head;
        do{
            if (strcmp(rec ->datosSucursal ->nombre, nombreSucursal) == 0){
                mayor = buscarClienteMasPudiente(rec ->datosSucursal ->ventasSucursal);
                return mayor;
            }
            rec = rec -> sig;
        }while (rec != head);
    }
    return mayor;
}

// FUNCION PLANTA CON MAYOR DISTRIBUCION //
struct Sucursal *calcularMayorVenta(struct NodoSucursales *head, int *cont)
{
    if(head != NULL)
    {
        struct NodoSucursales *rec= head;
        struct Sucursal *mayor=NULL;
        int i, acumulador=0;
        while(rec != NULL)
        {
            for(i=0; i<MAXVENTAS ;i++)
            {
                *cont=0;
                if(rec->datosSucursal->ventasSucursal[i] != NULL)
                {
                    acumulador ++;
                }
            }
            if(acumulador > *cont)
            {
                *cont= acumulador;
                mayor = rec->datosSucursal;
            }
            rec=rec->sig;
        }
        return mayor;
    }
    return NULL;
}
void recorrerABBDistribucion(struct NodoComunas *ABB)
{
    struct Sucursal *mayor= NULL;
    if(ABB !=NULL)
    {
        recorrerABBDistribucion(ABB -> izq);
        int cont = 0;
        mayor= calcularMayorVenta(ABB->datosComuna->sucursales, &cont);
        recorrerABBDistribucion(ABB -> der);
    }
    //AQUI VA EL PRINT DE LA MAYOR CREO
    printf("la Distribuidora con mas ventas es: %s", mayor->nombre);
}
// AUTO CON MAS RECALLS //
int autoMasRecalls(struct NodoProductos *head)
{
    if(head != NULL)
    {
        struct NodoProductos *rec= head;
        struct producto *mayorRecall =NULL;
        int i, j, cont=0, aux=0;
        while(rec != NULL)
        {
            for(i=0; i<MAXPRODUCTOS; i++)
            {
                if(strcmp(rec->productosMarca[i]->tipoProducto,"AUTO")==0) {
                    for (j = 0; j < MAXPRODUCTOS; j++)
                    {
                        if(rec->productosMarca[i]->idProducto == rec->productosMarca[j]->idProducto)
                            cont++;
                    }
                    if(cont > aux)
                    {
                        mayorRecall = rec->productosMarca[i];
                        aux= cont;
                        cont=0;
                    }
                }
            }
            rec= rec->sig;
        }
        printf("EL AUTO CON MAS RECALLS ES %s", mayorRecall->nombre);
        return 1;
    }
    return 0;
}
// 2 FUNCIONES EXTRA //

float calcularGananciasSucursal(struct Ventas **array){
    int i;
    float contador = 0;
    for (i = 0; i < MAXVENTAS; i++){
        if (array[i]){
            contador += array[i] -> monto;
        }
    }
    return contador;
}

float calcularGananciasComuna(struct NodoSucursales *head){
    float contador = 0;
    struct NodoSucursales *rec;
    if (head){
        rec = head;
        do{
            contador += calcularGananciasSucursal(rec -> datosSucursal -> ventasSucursal);
            rec = rec -> sig;
        }while (rec != head);
    }
    return contador;
}

void comunaMasRentable(struct NodoComunas *raiz, struct Comuna **buscada, float *gananciaMasRentable){
    float gananciaComuna;
    if (!raiz) return;

    comunaMasRentable(raiz -> izq, buscada, gananciaMasRentable);
    comunaMasRentable(raiz -> der, buscada, gananciaMasRentable);

    if (raiz -> datosComuna){
        gananciaComuna = calcularGananciasComuna(raiz -> datosComuna -> sucursales);
        if (!(*buscada) || gananciaComuna > (*gananciaMasRentable)){
            (*buscada) = raiz -> datosComuna;
            (*gananciaMasRentable) = gananciaComuna;
        }
    }

}

int agregarOeliminarRecalls (struct NodoProductos *head, char *nombreMarc, int id, int opcion, int cantidad)
{
    struct NodoProductos *rec;
    if(head != NULL)
    {
        rec = head;
        while (rec != NULL)
        {
            if(strcmp(rec-> nombreMarca,nombreMarc)==0)
            {
                int i = 0;
                for (i = 0; i < MAXPRODUCTOS; i ++)
                {
                    if(rec -> productosMarca[i] -> idProducto == id)
                    {
                        if(strcmp(rec -> productosMarca[i] -> tipoProducto,"AUTO")==0)
                        {
                            if(opcion == 1) // agrega //
                            {
                                rec -> productosMarca[i] -> recallProducto += cantidad;
                                return 1;
                            }
                            else // elimina //
                            {
                                rec -> productosMarca[i] -> recallProducto -= cantidad;
                                return 1;
                            }
                        }
                    }
                }
            }
            rec = rec -> sig;
        }
    }
    return 0;
}
// FUNCION PARA SABER EL STOCK //
int BuscarEnSucursales(struct NodoSucursales *head, int *cont, int id)
{
    if(head != NULL)
    {
        struct NodoSucursales *rec= head;
        struct NodoStock*recStock= head->datosSucursal->stockSucursal;
        while(rec!= NULL)
        {
            if(recStock != NULL)
            {
                do
                {
                    if(recStock->marca->idProducto == id)
                    {
                        cont= cont + recStock->cantidadProducto;
                    }
                    recStock= recStock->sig;
                }while(recStock != head->datosSucursal->stockSucursal);
            }

            rec= rec->sig;
        }
        return 1;
    }
    return 0;
}
void recorrerABB(struct NodoComunas *ABB, int *cont, int id)
{
    if(ABB !=NULL)
    {
        recorrerABB(ABB -> izq, cont, id);
        cont= cont+(BuscarEnSucursales(ABB->datosComuna->sucursales, cont, id));
        recorrerABB(ABB -> der, cont, id);
    }

}
int stockProducto(struct NodoComunas**ABB, int idBuscado)
{
    if(ABB != NULL)
    {
        int cont=0;
        recorrerABB(*ABB,&cont,idBuscado);
        if(cont == 0)
        {
            printf("NO HAY STOCK EN NINGUNA SUCURSAL");//O EL ELEMENTO NO EXISTE
        }
        else
        {
            printf("STOCK GLOBAL: %d", cont);
        }
        return 1;
    }
    return 0;
}
/////// MENU ////////
////// AGREGAR /////////
void opcionesAgregar(struct SistemaDercos *SD)
{
    int opcion = 0,id=0;
    char buffer[100];

    struct NodoProductos *nodoProducto = SD -> headMarcas;
    struct NodoComunas *nodoComuna= SD -> headComunas;
    struct NodoSucursales *sucursalBuscada;
    struct producto *aAgregar;

    printf("SI  DESEA AGREGAR EN NODO COMUNA PRESIONE [1]\n");
    printf("SI  DESEA AGREGAR EN NODO SUCURSALES PRESIONE [2]\n");
    printf("SI  DESEA AGREGAR EN NODO SUCURSAL PRESIONE [3]\n");
    printf("SI  DESEA AGREGAR EN VENTAS PRESIONE [4]\n");
    printf("SI  DESEA AGREGAR EN NODO STOCK PRESIONE [5]\n");
    printf("SI  DESEA AGREGAR EN NODO PRODUCTOS PRESIONE [6]\n");
    printf("SI  DESEA AGREGAR EN PRODUCTO PRESIONE [7]\n");
    printf("SI NO DESEA EDITAR ALGUNA FUNCIONALIDAD PRESIONE [8] PARA SALIR DEL SISTEMA\n");
    do
    {
        scanf("%d", &opcion);
        switch (opcion)
        {
            // AGREGAR EN NODO COMUNAS //
            case 1:
                printf("HA SELECCIONADO AGREGAR EN NODO COMUNAS \n");//
                printf("INGRESE EL ID DESEA AGREGAR ");
                int idComuna = 0;
                scanf("%d",&idComuna);
                agregarNodoComunas(&nodoComuna,idComuna, agregarComuna());  // FUNCION RECURSIVA ABB //
                break;
                // AGREGAR  EN NODO SUCURSALES //
            case 2:
                printf("HA SELECCIONADO AGREGAR EN NODO SUCURSAL \n");
                printf("INGRESE EL ID DE LA COMUNA DONDE QUIERE AGREGAR SUCURSAL\n");
                scanf("%d", &id);
                if((buscarNodoComuna(nodoComuna, id))!= NULL)
                {
                    agregarNodoSucursal(nodoComuna->datosComuna->sucursales, crearSucursal());
                }
                break;

                // AGREGAR EN SUCURSAL //
            case 3:
                printf("HA SELECCIONADO AGREGAR EN SUCURSAL \n");
                crearSucursal();
                break;

                // AGREGAR VENTAS //
            case 4:
                printf("HA SELECCIONADO AGREGAR EN VENTAS \n");
                printf("INGRESE LA MARCA DEL PRODUCTO\n");
                scanf("%100[^\n]s", buffer);
                if((buscarNodoProducto(nodoProducto, buffer)))
                {
                    printf("INGRESE ID DEL PRODUCTO\n");
                    scanf("%d", &id);
                    aAgregar = buscarProducto(buscarNodoProducto(nodoProducto,buffer), id);
                    if(aAgregar)
                    {
                        printf("INGRESE ID DE LA COMUNA\n");
                        scanf("%d", &id);
                        if((buscarNodoComuna(nodoComuna,id))!= NULL)
                        {

                            printf("INGRESE EL NOMBRE DE LA SUCURSAL\n");
                            scanf("%100[^\n]s", buffer);
                            sucursalBuscada = buscarNodoSucursal(nodoComuna->datosComuna->sucursales,buffer);
                            if(sucursalBuscada){
                                if(agregarVenta(sucursalBuscada->datosSucursal, aAgregar) ==1)
                                {
                                    printf("SE AGREGO LA VENTA EXITOSAMENTE\n");
                                }
                                else
                                {
                                    printf("NO SE AGREGO LA VENTA\n");
                                }
                            }
                        }
                    }
                }
                break;
                // AGREGAR EN NODO STOCK //
            case 5:
                printf("HA SELECCIONADO AGREGAR EN NODO STOCK \n");


                printf("INGRESE LA MARCA DEL PRODUCTO\n");
                scanf("%100[^\n]s", buffer);
                if((buscarNodoProducto(nodoProducto,buffer))!= NULL)
                {
                    printf("INGRESE ID DEL PRODUCTO\n");
                    scanf("%d", &id);
                    aAgregar = buscarProducto(buscarNodoProducto(nodoProducto,buffer), id);
                    if(aAgregar)
                    {
                        printf("INGRESE ID DE LA COMUNA\n");
                        scanf("%d", &id);
                        if((buscarNodoComuna(nodoComuna,id))!= NULL)
                        {

                            printf("INGRESE EL NOMBRE DE LA SUCURSAL\n");
                            scanf("%100[^\n]s", buffer);
                            sucursalBuscada = buscarNodoSucursal(nodoComuna->datosComuna->sucursales,buffer);
                            if(sucursalBuscada)
                            {

                                if(((agregarNodoStock(&sucursalBuscada->datosSucursal->stockSucursal,aAgregar), id))==1)
                                {
                                    printf("SE AGREGO AL STOCK\n");
                                }
                                else
                                {
                                    printf("NO SE AGREGO AL STOCK\n");
                                }
                            }
                        }
                    }
                }
                break;
                // AGREGAR EN NODO PRODUCTOS //
            case 6:
                printf("HA SELECCIONADO AGREGAR EN NODO PRODUCTOS \n");
                printf("");

                printf("INGRESE EL NOMBRE DE LA MARCA: ");
                scanf("%100[^\n]s", buffer);
                if(enlazarNodoProducto(&nodoProducto,crearNodo(buffer))==1)
                {
                    printf("SE AGREGO CON EXITO LA MARCA.\n");
                }
                else
                {
                    printf("NO SE PUDO AGREGAR LA MARCA.\n");
                }
                break;
                // AGREGAR EN PRODUCTO //
            case 7:
                printf("HA SELECCIONADO AGREGAR EN PRODUCTO \n");

                scanf("%100[^\n]s",buffer);
                if((agregarProducto(&nodoProducto,buffer))==1)
                {
                    printf("EL PRODUCTO SE AGREGO EXITOSAMENTE.\n");
                }
                else
                {
                    printf("EL PRODUCTO NO SE AGREGO.\n");
                }
                break;
                // SALIR DEL PROGRAMA //
            case 8:
                printf("HA DECIDIDO SALIR DEL PROGRAMA \n");
                return ;
            default:
                printf("NUMERO INVALIDO, PORFAVOR INGRESE UN NUMERO ENTRE 1 - 8: ");
                break;
        }
    } while (opcion != 8);
}
//////// MODIFICAR ////////
void opcionesModificar(struct SistemaDercos *SD)
{
    int opcion = 0;
    struct NodoProductos *nodoProducto=SD->headMarcas;
    struct NodoComunas *nodoComuna= SD->headComunas;
    struct NodoComunas *comunaBuscada;
    struct NodoProductos *marcaATrabajar;
    struct producto *productoBuscado;
    struct NodoSucursales *sucursalBuscada;
    char buffer1[100];
    char buffer2[100];
    int id;
    printf("SI  DESEA MODIFICAR EN NODO COMUNA PRESIONE [1]\n");
    printf("SI  DESEA MODIFICAR EN NODO SUCURSALES PRESIONE [2]\n");
    printf("SI  DESEA MODIFICAR EN VENTAS PRESIONE [3]\n");
    printf("SI  DESEA MODIFICAR EN NODO STOCK PRESIONE [4]\n");
    printf("SI  DESEA MODIFICAR EN NODO PRODUCTOS PRESIONE [5]\n");
    printf("SI  DESEA MODIFICAR EN PRODUCTO PRESIONE [6]\n");
    printf("SI NO DESEA EDITAR ALGUNA FUNCIONALIDAD PRESIONE [7] PARA SALIR DEL SISTEMA\n");
    do
    {
        scanf("%d", &opcion);
        switch (opcion)
        {
            // MODIFICAR EN NODO COMUNAS //
            case 1:
                printf("HA SELECCIONADO MODIFICAR EN NODO COMUNAS \n");


                printf("INGRESE ID DE LA COMUNA\n");
                scanf("%d", &id);
                printf("INGRESE NOMBRE DE LA REGION\n");
                scanf("%100[^\n]s" ,buffer1);
                printf("INGRESE NOMBRE DE LA COMUNA\n");
                scanf("%100[^\n]s" ,buffer2);
                if((modificarNodoComunas(&nodoComuna, id,buffer1, buffer2))==1)
                {
                    printf("MODIFICO CORRECTAMENTE TODO.\n");
                }
                else
                {
                    printf("NO SE LOGRO MODIFICAR LOS DATOS DE LA COMUNA.\n");
                }// FUNCION RECURSIVA ABB //
                break;
                // MODIFICAR  EN NODO SUCURSALES //
            case 2:
                printf("HA SELECCIONADO MODIFICAR EN NODO SUCURSAL \n");
                printf("INGRESE ID DE LA COMUNA\n");
                scanf("%d", &id);
                comunaBuscada = buscarNodoComuna(nodoComuna,id);
                if(comunaBuscada)
                {

                    printf("INGRESE EL NOMBRE DE LA SUCURSAL A MODIFICAR\n");
                    scanf("%100[^\n]s", buffer1);
                    printf("INGRESE EL NUEVO NOMBRE DE LA SUCURSAL\n");
                    scanf("%100[^\n]s", buffer2);
                    if((modificarNodoSucursal(&comunaBuscada->datosComuna->sucursales,buffer1, buffer2))==1)
                    {
                        printf("SUCURSAL MODIFICADA EXITOSAMENTE\n");
                    }
                    else
                    {
                        printf("NO SE PUDO MODIFICAR LA SUCURSAL\n");
                    }
                }
                break;
                // MODIFICAR VENTAS //
            case 3:
                printf("HA SELECCIONADO MODIFICAR EN VENTAS \n");

                printf("INGRESE LA MARCA DEL PRODUCTO\n");
                scanf("%100[^\n]s", buffer1);
                marcaATrabajar = buscarNodoProducto(nodoProducto,buffer1);
                if(marcaATrabajar)
                {
                    printf("INGRESE ID DEL PRODUCTO\n");
                    scanf("%d", &id);
                    productoBuscado = buscarProducto(marcaATrabajar, id);
                    if(productoBuscado)
                    {
                        printf("INGRESE ID DE LA COMUNA\n");
                        scanf("%d", &id);
                        if((buscarNodoComuna(nodoComuna,id))!= NULL)
                        {
                            printf("INGRESE EL NOMBRE DE LA SUCURSAL\n");
                            scanf("%100[^\n]s", buffer1);
                            sucursalBuscada = buscarNodoSucursal(nodoComuna->datosComuna->sucursales, buffer1);
                            if(sucursalBuscada){

                                printf("INGRESE RUT DE VENTA A MODIFICAR\n");
                                scanf("%100[^\n]s", buffer1);
                                modificarVenta((sucursalBuscada -> datosSucursal),buffer1, productoBuscado);
                            }
                        }
                    }
                }
                break;
                // MODIFICAR EN NODO STOCK //
            case 4:
                printf("HA SELECCIONADO MODIFICAR EN NODO STOCK \n");

                printf("INGRESE LA MARCA DEL PRODUCTO\n");
                scanf("%100[^\n]s", buffer1);
                marcaATrabajar = buscarNodoProducto(nodoProducto, buffer1);
                if(marcaATrabajar)
                {
                    printf("INGRESE ID DEL PRODUCTO\n");
                    scanf("%d", &id);
                    productoBuscado = buscarProducto(marcaATrabajar, id);
                    if(productoBuscado)
                    {
                        printf("INGRESE ID DE LA COMUNA\n");
                        scanf("%d", &id);
                        if((buscarNodoComuna(nodoComuna,id))!= NULL)
                        {

                            printf("INGRESE EL NOMBRE DE LA SUCURSAL\n");
                            scanf("%100[^\n]s", buffer1);
                            sucursalBuscada = buscarNodoSucursal(nodoComuna->datosComuna->sucursales,buffer1);
                            if(sucursalBuscada)
                            {

                                if(modificarNodoStock(sucursalBuscada->datosSucursal->stockSucursal)==1)
                                {
                                    printf("SE AGREGO AL STOCK\n");
                                }
                                else
                                {
                                    printf("NO SE AGREGO AL STOCK\n");
                                }
                            }
                        }
                    }
                }
                break;
                // MODIFICAR EN NODO PRODUCTOS //
            case 5:
                printf("HA SELECCIONADO MODIFICAR EN NODO PRODUCTOS \n");

                printf("INGRESE EL NOMBRE DE LA MARCA\n");
                scanf("%100[^\n]s", buffer1);
                if((modificarNodoProductos(nodoProducto, buffer1))==1)
                {
                    printf("SE MODIFICO EXITOSAMENTE.\n");
                }
                else
                {
                    printf("NO SE PUDO MODIFICAR.\n");
                }
                break;
                // MODIFICAR EN PRODUCTO //
            case 6:
                printf("HA SELECCIONADO MODIFICAR EN PRODUCTO \n");

                printf("INGRESE MARCA DEL PRODUCTO\n");
                scanf("%100[^\n]s", buffer1);
                marcaATrabajar = buscarNodoProducto(nodoProducto, buffer1);
                if(marcaATrabajar)
                {
                    int idProducto =0;
                    printf("INGRESE ID DEL PRODUCTO\n");
                    scanf("%d", &idProducto);
                    if((modificarProducto(&marcaATrabajar,idProducto))==1)
                    {
                        printf("SE MODIFICO EL PRODUCTO EXITOSAMENTE.\n");
                    }
                    else
                    {
                        printf("NO SE LOGRO MODIFICAR EL PRODUCTO.\n");
                    }
                }
                break;
                // SALIR DEL PROGRAMA //
            case 7:
                printf("HA DECIDIDO SALIR DEL PROGRAMA \n");
                return ;
            default:
                printf("NUMERO INVALIDO, PORFAVOR INGRESE UN NUMERO ENTRE 1 - 7: ");
                break;
        }
    } while (opcion != 7);
}
/////// ELIMINAR ///////
void opcionesEliminar(struct SistemaDercos *SD)
{
    int opcion = 0, id = 0;
    char buffer1[100];
    struct NodoProductos *nodoProducto = SD->headMarcas;
    struct NodoComunas *nodoComuna= SD->headComunas;
    struct NodoSucursales *sucursalBuscada;
    struct NodoProductos *marcaATrabajar;
    struct producto *productoBuscado;
    printf("SI  DESEA ELIMINAR EN COMUNA PRESIONE [1]\n");
    printf("SI  DESEA  ELIMINAR EN NODO SUCURSALES PRESIONE [2]\n");
    printf("SI  DESEA  ELIMINAR  EN VENTAS PRESIONE [3]\n");
    printf("SI  DESEA ELIMINAR EN NODO STOCK PRESIONE [4]\n");
    printf("SI  DESEA ELIMINAR EN NODO PRODUCTOS PRESIONE [5]\n");
    printf("SI  DESEA ELIMINAR EN PRODUCTO PRESIONE [6]\n");
    printf("SI NO DESEA  ELIMINAR ALGUNA FUNCIONALIDAD PRESIONE [7] PARA SALIR DEL SISTEMA\n");
    do
    {
        scanf("%d", &opcion);
        switch (opcion)
        {
            // ELIMINAR EN NODO COMUNAS //
            case 1:
                printf("HA SELECCIONADO ELIMINAR EN COMUNAS \n");
                printf("INGRESE EL ID DESEA ELIMINAR \n");
                scanf("%d",&id);
                eliminarNodoComuna(&nodoComuna,id);  // FUNCION RECURSIVA ABB //
                break;
                // ELIMINAR EN NODO SUCURSALES //
            case 2:
                printf("HA SELECCIONADO ELIMINAR EN NODO SUCURSAL \n");
                printf("INGRESE ID DE LA COMUNA\n");
                scanf("%d", &id);
                if((buscarNodoComuna(nodoComuna,id))!= NULL)
                {

                    printf("INGRESE EL MOMBRE DE LA SUCURSAL\n");
                    scanf("%100[^\n]s", buffer1);
                    sucursalBuscada = buscarNodoSucursal(nodoComuna->datosComuna->sucursales,buffer1);
                    if(sucursalBuscada)
                    {
                        eliminarNodoSucursal(&nodoComuna->datosComuna->sucursales, sucursalBuscada);
                    }

                }
                break;
                // ELIMINAR VENTAS //
            case 3:
                printf("HA SELECCIONADO ELIMINAR EN VENTAS \n");

                printf("INGRESE LA MARCA DEL PRODUCTO\n");
                scanf("%100[^\n]s", buffer1);
                marcaATrabajar = buscarNodoProducto(nodoProducto,buffer1);
                if(marcaATrabajar)
                {
                    printf("INGRESE ID DEL PRODUCTO\n");
                    scanf("%d", &id);
                    productoBuscado = buscarProducto(marcaATrabajar, id);
                    if (productoBuscado)
                    {
                        printf("INGRESE ID DE LA COMUNA\n");
                        scanf("%d", &id);
                        if ((buscarNodoComuna(nodoComuna, id)) != NULL)
                        {

                            printf("INGRESE EL NOMBRE DE LA SUCURSAL\n");
                            scanf("%100[^\n]s", buffer1);
                            sucursalBuscada = buscarNodoSucursal(nodoComuna->datosComuna->sucursales,buffer1);
                            if (sucursalBuscada)
                            {

                                printf("INGRESE RUT DEL CLIENTE\n");
                                scanf("%100[^\n]s", buffer1);
                                if((eliminarVenta(sucursalBuscada->datosSucursal, buffer1))==1)
                                {
                                    printf("VENTA ELIMINADA CON EXITO\n");
                                }
                                else
                                {
                                    printf("NO SE PUDO ELIMINAR LA VENTA\n");
                                }
                            }
                        }
                    }
                }
                break;
                // ELIMINAR EN NODO STOCK //
            case 4:
                printf("HA SELECCIONADO MODIFICAR EN NODO STOCK \n");

                printf("INGRESE LA MARCA DEL PRODUCTO\n");
                scanf("%100[^\n]s", buffer1);
                marcaATrabajar = buscarNodoProducto(nodoProducto,buffer1);
                if (marcaATrabajar)
                {
                    printf("INGRESE ID DEL PRODUCTO\n");
                    scanf("%d", &id);
                    productoBuscado = buscarProducto(marcaATrabajar, id);
                    if(productoBuscado)
                    {
                        printf("INGRESE ID DE LA COMUNA\n");
                        scanf("%d", &id);
                        if((buscarNodoComuna(nodoComuna,id))!= NULL)
                        {

                            printf("INGRESE EL NOMBRE DE LA SUCURSAL\n");
                            scanf("%100[^\n]s", buffer1);
                            sucursalBuscada = buscarNodoSucursal(nodoComuna->datosComuna->sucursales,buffer1);
                            if(sucursalBuscada)
                            {

                                printf("INGRESE EL ID A ELIMINAR\n");
                                scanf("%d", &id);
                                eliminarNodoStock(&sucursalBuscada->datosSucursal->stockSucursal, id);
                            }
                        }
                    }
                }
                break;
                // ELIMINAR EN NODO PRODUCTOS //
            case 5:
                printf("HA SELECCIONADO ELIMINAR EN NODO PRODUCTOS \n");

                printf("NOMBRE DE LA MARCA A ELIMINAR\n");
                scanf("%100[^\n]s", buffer1);
                eliminarNodoProducto(&nodoProducto, buffer1);
                break;
                // ELIMINAR EN PRODUCTO //
            case 6:
                printf("HA SELECCIONADO ELIMINAR EN PRODUCTO \n");
                printf("INGRESE MARCA DEL PRODUCTO");
                scanf("%100[^\n]s", buffer1);
                marcaATrabajar =buscarNodoProducto(nodoProducto, buffer1);
                if(marcaATrabajar)
                {

                    printf("INGRESE ID DEL PROUCTO\n");
                    scanf("%d", &id);
                    if((eliminarProducto(nodoProducto, id))==1)
                    {
                        printf("PRODUCTO SE ELIMINO CON EXITO\n");
                    }
                    else
                    {
                        printf("PRODUCTO NO PUDO SER ELIMINADO\n");
                    }
                }
                break;
                // SALIR DEL PROGRAMA //
            case 7:
                printf("HA DECIDIDO SALIR DEL PROGRAMA \n");
                return ;
            default:
                printf("NUMERO INVALIDO, PORFAVOR INGRESE UN NUMERO ENTRE 1 - 7: ");
                break;
        }
    } while (opcion != 7);
}
///// BUSCAR /////
void opcionesBuscar(struct SistemaDercos *SD)
{
    int opcion = 0, id = 0;
    char buffer[100];
    struct NodoProductos *nodoProducto = SD->headMarcas;
    struct NodoComunas *nodoComuna= SD->headComunas;
    struct NodoProductos *marcaATrabajar;
    struct NodoSucursales *sucursalBuscada;
    struct NodoComunas *comunaATrabajar;
    struct producto *productoBuscado;
    printf("SI  DESEA BUSCAR EN COMUNA PRESIONE [1]\n");
    printf("SI  DESEA BUSCAR EN NODO SUCURSALES PRESIONE [2]\n");
    printf("SI  DESEA BUSCAR EN VENTAS PRESIONE [3]\n");
    printf("SI  DESEA BUSCAR EN NODO STOCK PRESIONE [4]\n");
    printf("SI  DESEA BUSCAR EN NODO PRODUCTOS PRESIONE [5]\n");
    printf("SI  DESEA BUSCAR EN PRODUCTO PRESIONE [6]\n");
    printf("SI NO DESEA EDITAR ALGUNA FUNCIONALIDAD PRESIONE [7] PARA SALIR DEL SISTEMA\n");
    do
    {
        scanf("%d", &opcion);
        switch (opcion)
        {
            // BUSCAR EN NODO COMUNAS //
            case 1:
                printf("HA SELECCIONADO BUSCAR EN NODO COMUNAS \n");
                printf("INGRESE EL ID QUE BUSCA");
                scanf("%d",&id);

                buscarNodoComuna(nodoComuna,id);  // FUNCION RECURSIVA ABB //
                break;
                // BUSCAR EN NODO SUCURSALES //
            case 2:
                printf("HA SELECCIONADO BUSCAR EN NODO SUCURSAL \n");
                printf("INGRESE ID DE LA COMUNA\n");
                scanf("%d", &id);
                comunaATrabajar = buscarNodoComuna(nodoComuna,id);
                if (comunaATrabajar) {

                    printf("INGRESE EL MOMBRE DE LA SUCURSAL\n");
                    scanf("%100[^\n]s", buffer);
                    sucursalBuscada = buscarNodoSucursal(comunaATrabajar -> datosComuna -> sucursales, buffer);

                    if(sucursalBuscada)
                    {
                        printf("SE ENCONTRO LA SUCURSAL\n");
                    }
                    else
                    {
                        printf("NO SE ENCONTRO LA SUCURSAL\n");
                    }
                }
                break;
                // BUSCAR VENTAS //
            case 3:
                printf("HA SELECCIONADO BUSCAR EN VENTAS \n");

                printf("INGRESE LA MARCA DEL PRODUCTO\n");
                scanf("%100[^\n]s", buffer);
                marcaATrabajar = buscarNodoProducto(nodoProducto,buffer);
                if(marcaATrabajar)
                {
                    printf("INGRESE ID DEL PRODUCTO\n");
                    scanf("%d", &id);
                    productoBuscado = buscarProducto(marcaATrabajar, id);
                    if (productoBuscado)
                    {
                        printf("INGRESE ID DE LA COMUNA\n");
                        scanf("%d", &id);
                        if ((buscarNodoComuna(nodoComuna, id)) != NULL)
                        {

                            printf("INGRESE EL NOMBRE DE LA SUCURSAL\n");
                            scanf("%100[^\n]s", buffer);
                            sucursalBuscada = buscarNodoSucursal(nodoComuna->datosComuna->sucursales,buffer);
                            if (sucursalBuscada)
                            {

                                printf("INGRESE RUT DE VENTA A MODIFICAR\n");
                                scanf("%100[^\n]s", buffer);
                                if((buscarVenta(sucursalBuscada->datosSucursal, buffer)))
                                {
                                    printf("VENTA ENCONTRADA\n");
                                }
                                else
                                {
                                    printf("VENTA NO ENCONTRADA\n");
                                }
                            }
                        }
                    }
                }
                break;
                // BUSCAR EN NODO STOCK //
            case 4:
                printf("HA SELECCIONADO BUSCAR EN NODO STOCK \n");

                printf("INGRESE LA MARCA DEL PRODUCTO\n");
                scanf("%100[^\n]s", buffer);
                marcaATrabajar = buscarNodoProducto(nodoProducto, buffer);
                if(marcaATrabajar)
                {
                    printf("INGRESE ID DEL PRODUCTO\n");
                    scanf("%d", &id);
                    productoBuscado = buscarProducto(marcaATrabajar, id);
                    if(productoBuscado)
                    {
                        printf("INGRESE ID DE LA COMUNA\n");
                        scanf("%d", &id);
                        if((buscarNodoComuna(nodoComuna,id))!= NULL)
                        {

                            printf("INGRESE EL NOMBRE DE LA SUCURSAL\n");
                            scanf("%100[^\n]s", buffer);
                            sucursalBuscada = buscarNodoSucursal(nodoComuna->datosComuna->sucursales,buffer);
                            if(sucursalBuscada)
                            {

                                printf("INGRESE EL ID A BUSCAR\n");
                                scanf("%d", &id);
                                buscarNodoStock(&sucursalBuscada->datosSucursal->stockSucursal, id);
                            }
                        }
                    }
                }
                break;
                // BUSCAR EN NODO PRODUCTOS //
            case 5:
                printf("HA SELECCIONADO BUSCAR EN NODO PRODUCTOS \n");

                printf("INGRESE NOMBRE DE LA MARCA\n");
                scanf("%100[^\n]s", buffer);
                marcaATrabajar = buscarNodoProducto(nodoProducto, buffer);
                if(marcaATrabajar)
                {
                    printf("SE ENCONTRO LA MARCA QUE BUSCABA\n");
                }
                else
                {
                    printf("NO SE ENCONTRO LA MARCA INGRESADA\n");
                }
                break;
                // BUSCAR EN PRODUCTO //
            case 6:
                printf("HA SELECCIONADO BUSCAR EN PRODUCTO \n");

                scanf("%100[^\n]s", buffer);
                marcaATrabajar = buscarNodoProducto(nodoProducto, buffer);
                if(marcaATrabajar)
                {

                    printf("INGRESE ID PRODUCTO\n");
                    scanf("%d", &id);
                    if(buscarProducto(marcaATrabajar, id))
                    {
                        printf("EL PRODUCTO FUE ENCONTRADO.\n");
                    }
                    else
                    {
                        printf("NO SE LOGRO ENCONTRAR EL PRODUCTO.\n");
                    }
                }
                break;
                // SALIR DEL PROGRAMA //
            case 7:
                printf("HA DECIDIDO SALIR DEL PROGRAMA \n");
                return ;
            default:
                printf("NUMERO INVALIDO, PORFAVOR INGRESE UN NUMERO ENTRE 1 - 7: ");
                break;
        }
    } while (opcion != 7);
}
///////// LISTAR //////////////
void opcionesListar(struct SistemaDercos *SD)
{
    int opcion = 0, id=0;
    struct NodoProductos *nodoProducto = SD->headMarcas;
    struct NodoComunas *nodoComuna= SD->headComunas;
    struct NodoSucursales *sucursalBuscada;
    struct NodoProductos *marcaATrabajar;
    struct producto *productoBuscado;
    char buffer[100];
    printf("SI  DESEA LISTAR EN COMUNA PRESIONE [1]\n");
    printf("SI  DESEA LISTAR EN NODO SUCURSALES PRESIONE [2]\n");
    printf("SI  DESEA LISTAR EN VENTAS PRESIONE [3]\n");
    printf("SI  DESEA LISTAR EN NODO STOCK PRESIONE [4]\n");
    printf("SI  DESEA LISTAR EN NODO PRODUCTOS PRESIONE [5]\n");
    printf("SI  DESEA LISTAR EN PRODUCTO PRESIONE [6]\n");
    printf("SI NO DESEA EDITAR ALGUNA FUNCIONALIDAD PRESIONE [7] PARA SALIR DEL SISTEMA\n");
    do
    {
        scanf("%d", &opcion);
        switch (opcion)
        {
            // LISTAR EN COMUNAS //
            case 1:
                printf("HA SELECCIONADO LISTAR EN COMUNAS \n");
                listarNodoComuna(nodoComuna);  // FUNCION RECURSIVA ABB //
                break;
                // LISTAR EN NODO SUCURSALES //
            case 2:
                printf("HA SELECCIONADO LISTAR EN NODO SUCURSAL \n");
                printf("INGRESE ID DE LA COMUNA\n");
                scanf("%d", &id);
                if(buscarNodoComuna(nodoComuna, id)!= NULL)
                {
                    listarSucursal(buscarNodoComuna(nodoComuna, id)->datosComuna->sucursales);
                }
                break;
                // LISTAR VENTAS //
            case 3:
                printf("HA SELECCIONADO LISTAR EN VENTAS \n");

                printf("INGRESE LA MARCA DEL PRODUCTO\n");
                scanf("%100[^\n]s", buffer);
                marcaATrabajar = buscarNodoProducto(nodoProducto,buffer);
                if(marcaATrabajar)
                {
                    printf("INGRESE ID DEL PRODUCTO\n");
                    scanf("%d", &id);
                    productoBuscado = buscarProducto(marcaATrabajar, id);
                    if (productoBuscado)
                    {
                        printf("INGRESE ID DE LA COMUNA\n");
                        scanf("%d", &id);
                        if ((buscarNodoComuna(nodoComuna, id)) != NULL)
                        {

                            printf("INGRESE EL NOMBRE DE LA SUCURSAL\n");
                            scanf("%100[^\n]s", buffer);
                            sucursalBuscada = buscarNodoSucursal(nodoComuna->datosComuna->sucursales,buffer);
                            if (sucursalBuscada)
                            {
                                listarVentas(sucursalBuscada ->datosSucursal);
                            }
                        }
                    }
                }
                break;
                // LISTAR EN NODO STOCK //
            case 4:
                printf("HA SELECCIONADO LISTAR EN NODO STOCK \n");

                printf("INGRESE LA MARCA DEL PRODUCTO\n");
                scanf("%100[^\n]s", buffer);
                marcaATrabajar = buscarNodoProducto(nodoProducto,buffer);
                if(marcaATrabajar)
                {
                    printf("INGRESE ID DEL PRODUCTO\n");
                    scanf("%d", &id);
                    productoBuscado = buscarProducto(marcaATrabajar, id);
                    if (productoBuscado)
                    {
                        printf("INGRESE ID DE LA COMUNA\n");
                        scanf("%d", &id);
                        if ((buscarNodoComuna(nodoComuna, id)) != NULL)
                        {

                            printf("INGRESE EL NOMBRE DE LA SUCURSAL\n");
                            scanf("%100[^\n]s", buffer);
                            sucursalBuscada = buscarNodoSucursal(nodoComuna->datosComuna->sucursales,buffer);
                            if (sucursalBuscada)
                            {
                                listarNodoStock(sucursalBuscada->datosSucursal->stockSucursal);
                            }
                        }
                    }
                }
                break;
                // LISTAR EN NODO PRODUCTOS //
            case 5:
                printf("HA SELECCIONADO LISTAR EN NODO PRODUCTOS \n");
                listarNodoProducto(nodoProducto);
                break;
                // LISTAR EN PRODUCTO //
            case 6:
                printf("HA SELECCIONADO LISTAR EN PRODUCTO \n");

                printf("INGRESE NOMBRE DE LA MARCA A LISTAR\n");
                scanf("%100[^\n]s", buffer);
                marcaATrabajar = buscarNodoProducto(nodoProducto, buffer);
                if(marcaATrabajar)
                {
                    listarProducto(marcaATrabajar);
                }
                break;
                // SALIR DEL PROGRAMA //
            case 7:
                printf("HA DECIDIDO SALIR DEL PROGRAMA \n");
                return ;
            default:
                printf("NUMERO INVALIDO, PORFAVOR INGRESE UN NUMERO ENTRE 1 - 7: ");
                break;
        }
    } while (opcion != 7);
}
void opcionesExtras(struct SistemaDercos *SD)
{
    int id, cantRecalls, opcionRecall, eleccionCliente;
    struct NodoProductos * nodoProducto = SD->headMarcas;
    struct NodoComunas * nodoComuna = SD->headComunas;
    struct Comuna *masRentable;
    struct NodoComunas *comunaBuscada;
    float gananciaDeLaMasRentable;
    char buffer[100];
    char *clienteMasPudiente;


    printf("  DESEA AGREGAR O ELIMINAR RECALLS [1]\n");
    printf("  CLIENTE QUE MAS DINERO GASTA POR ZONA [2]\n");
    printf("  MODELO Y MARCA DE AUTO MAS VENDIDO POR ZONA [3]\n");// LA ZONA CONSIDERA LA COMUNA
    printf("  AUTO CON MAS RECALLS [4]\n");
    printf("  STOCK TOTAL DE PRODUCTO [5]\n");
    printf("  PLANTA MAYOR DISTRIBUCION[6]\n");
    printf("  COMUNA MAS RENTABLE [7]\n");
    printf("  NO DESEA EDITAR ALGUNA FUNCIONALIDAD PRESIONE [8] PARA SALIR DEL SISTEMA\n");

    do
    {
        scanf("%d", &eleccionCliente);
        switch (eleccionCliente)
        {
            case 1:
                printf("INGRESE NOMBRE MARCA\n");
                scanf("%100[^\n]s", buffer);
                printf("INGRESE ID DEL PRODUCTO\n");
                scanf("%d", &id);
                printf("INGRESE CANTIDAD DEL PRODUCTO\n");
                scanf("%d", &cantRecalls);
                printf("INGRESE OPCION[1=SUMA  0=RESTA]\n");
                scanf("%d", &opcionRecall);
                agregarOeliminarRecalls (nodoProducto,buffer, id, opcionRecall, cantRecalls);
                break;
            case 2:
                printf("INGRESE ID PARA VER STOCK\n");
                scanf("%d", &id);
                stockProducto(&nodoComuna, id);
                break;
            case 3:
                autoMasRecalls(nodoProducto);
                break;
            case 4:
                recorrerABBDistribucion(nodoComuna);
                break;
            case 5:
                printf("INGRESE EL ID DE LA COMUNA DONDE SE BUSCARA AL CLIENTE\n");
                scanf("%d", &id);
                comunaBuscada = buscarNodoComuna(nodoComuna, id);
                if (comunaBuscada){
                    printf("INGRESE EL NOMBRE DE LA SUCURSAL DONDE SE BUSCARA AL CLIENTE\n");
                    scanf("%100[^\n]s", buffer);
                    clienteMasPudiente = mayorClienteSucursal(comunaBuscada ->datosComuna ->sucursales, buffer);
                    if (clienteMasPudiente){
                        printf("EL CLIENTE QUE MAS GASTA EN LA SUCURSAL %s, TIENE COMO RUT EL NUMERO %s\n", buffer, clienteMasPudiente);
                    }
                    printf("LO SENTIMOS, AL PARECER NO EXISTE LA SUCURSAL QUE INGRESO EN NUESTRA BASE DE DATOS, POR FAVOR INTENTE NUEVAMENTE");
                }
                else{
                    printf("LO SENTIMOS, EL ID DE LA COMUNA QUE INGRESO NO EXISTE EN NUESTRA BASE DE DATOS, POR FAVOR INTETEN NUEVAMENTE\n");
                }
                break;
            case 6:
                recorrerABBVendidos(nodoComuna);
                break;
            case 7:
                comunaMasRentable(nodoComuna, &masRentable, &gananciaDeLaMasRentable);
                if (masRentable){
                    printf("LA COMUNA MAS RENTABLE ES %s\n", masRentable -> nombreComuna);
                    printf("ESTA SE ENCUENTRA EN LA REGION DE %s\n", masRentable -> nombreRegion);
                    printf("LAS GANANCIAS DE ESTA COMUNA SON DE UN TOTAL DE %.0f", gananciaDeLaMasRentable);
                }
                else{
                    printf("LO SENTIMOS, AL PARECER OCURRIO UN ERROR O NO HAY COMUNAS DISPONIBLES EN EL SISTEMA, POR FAVOR INTENTELO NUEVAMENTE\n");
                }
                break;
            case 8:
                printf("HA DECIDIDO SALIR DEL PROGRAMA \n");
                return ;
            default:
                printf("NUMERO INVALIDO, PORFAVOR INGRESE UN NUMERO ENTRE 1 - 8: ");
                break;
        }
    }while(eleccionCliente != 8);
}
int main()
{
    // SE DA MEMORIA AL SISTEMA //
    struct SistemaDercos *SD = NULL;
    SD = (struct SistemaDercos*)malloc(sizeof(struct SistemaDercos));
    struct NodoProductos *nodoProducto = NULL;
    struct NodoComunas *nodoComuna = NULL;
    // SE INICIALIZA LA VARIABLE DE OPCIONES //
    int opcion = 0;
    printf("-----------------BIENVENIDO AL MENU--------------------\n");
    printf("SI  DESEA AGREGAR ALGUNA FUNCIONALIDAD PRESIONE [1]\n");
    printf("SI  DESEA MODIFICAR ALGUNA FUNCIONALIDAD PRESIONE [2]\n");
    printf("SI  DESEA ELIMINAR ALGUNA FUNCIONALIDAD PRESIONE [3]\n");
    printf("SI  DESEA BUSCAR ALGUNA FUNCIONALIDAD PRESIONE [4]\n");
    printf("SI  DESEA LISTAR ALGUNA FUNCIONALIDAD PRESIONE [5]\n");
    printf("SI  DESEA ACCEDER A LAS FUNCIONES EXTRAS PRESIONE [6]\n");
    printf("SI NO DESEA EDITAR ALGUNA FUNCIONALIDAD PRESIONE [7] PARA SALIR DEL SISTEMA\n");
    do
    {
        scanf("%d", &opcion);
        switch (opcion)
        {
            // AGREGAR //
            case 1:
                printf("HA SELECCIONADO AGREGAR \n");
                opcionesAgregar(SD);
                break;
                // MODIFICAR //
            case 2:
                printf("HA SELECCIONADO MODIFICAR \n");
                opcionesModificar(SD);
                break;
                // ELIMINAR //
            case 3:
                printf("HA SELECCIONADO ELIMINAR \n");
                opcionesEliminar(SD);
                break;
                // BUSCAR //
            case 4:
                printf("HA SELECCIONADO BUSCAR \n");
                opcionesBuscar(SD);
                break;
                // LISTAR //
            case 5:
                printf("HA SELECCIONADO LISTAR \n");
                opcionesListar(SD);
                break;
                // FUNCIONES EXTRAS //
            case 6:
                printf("HA SELECCIONADO FUNCIONES EXTRAS \n");
                opcionesExtras(SD);
                break;
                // SALIR DEL PROGRAMA //
            case 7:
                printf("HA DECIDIDO SALIR DEL PROGRAMA \n");
                return 0;
            default:
                printf("NUMERO INVALIDO, PORFAVOR INGRESE UN NUMERO ENTRE 1 - 7: ");
                break;
        }
    } while (opcion != 7);
    return 0;
}