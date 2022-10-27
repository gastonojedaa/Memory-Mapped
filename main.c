#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

//Casteo de la estructura
typedef struct {
    u_int16_t version;
    u_int16_t drxVersion;
    u_int32_t RESERVED;
    double    initCW; 
    float     azimuth;     
    float     elevation;
    u_int16_t idVolumen;
    u_int16_t idBarrido;
    u_int16_t idCnjunto;
    u_int16_t idGrupo;
    u_int16_t idPulso;
    _Bool     iniBarrido;
    _Bool     finBarrido;
    _Bool     finGrupo;
    _Bool     inhibido;
    u_int16_t validSamples;
    u_int16_t nroAdquisicion;
    u_int16_t RESERVED2;
    u_int32_t nroSecuencia;
    unsigned long int readTime_high;
    unsigned long int readTime_low;
    unsigned long int RESERVED1[8];
}datos;

int main (int argc, char* const argv[]){

    //calculo de tamaño de la estructura
    datos dato;
    printf("\nEl tamaño de la estructura es %lu bytes\n", sizeof(dato));

    //Calculo de tamaño del archivo
    FILE *file;
    file = fopen("rawdata/datos","r");
    fseek(file,0L, SEEK_END);
    printf("El tamaño del archivo es %lu bytes\n", ftell(file));

    //cantidad  de estructuras que entran en el archivo
    uint cantidadstructs = ftell(file)/sizeof(dato);
    printf("Por lo tanto la estructura esta contenida %u veces en el archivo\n", cantidadstructs);
    fclose(file);

    //apertura del archivo a mapear
    int fd;
    void* file_memory;
    datos* structs [cantidadstructs];
      
    //se abre el archivo
    fd = open("rawdata/datos", O_RDWR, S_IRUSR | S_IWUSR);
    
    //se mapea en memoria
    file_memory = mmap(0,sizeof(fd),PROT_READ | PROT_WRITE, MAP_SHARED,fd,0);
    close(fd);

    //Impresion de toda la estructura
    structs[0] = (datos*)file_memory; 
    printf("\n################ Estructura #######################\n");
    printf("version: %d\n", structs[0]->version);
    printf("drxVersion: %d\n", structs[0]->drxVersion);
    printf("RESERVED: %d\n", structs[0]->RESERVED);
    printf("initCW: %f\n", structs[0]->initCW);
    printf("azimuth: %f\n", structs[0]->azimuth);
    printf("elevation: %f\n", structs[0]->elevation);
    printf("idVolumen: %d\n", structs[0]->idVolumen);
    printf("idBarrido: %d\n", structs[0]->idBarrido);
    printf("idCnjunto: %d\n", structs[0]->idCnjunto);
    printf("idGrupo: %d\n", structs[0]->idGrupo);
    printf("idPulso: %d\n", structs[0]->idPulso);
    printf("iniBarrido: %d\n", structs[0]->iniBarrido);
    printf("finBarrido: %d\n", structs[0]->finBarrido);
    printf("finGrupo: %d\n", structs[0]->finGrupo);
    printf("inhibido: %d\n", structs[0]->inhibido);
    printf("validSamples: %d\n", structs[0]->validSamples);
    printf("nroAdquisicion: %d\n", structs[0]->nroAdquisicion);
    printf("RESERVED: %d\n",structs[0]->RESERVED2);
    printf("nroSecuencia: %d\n", structs[0]->nroSecuencia);
    printf("readTime_high: %lu\n", structs[0]->readTime_high);
    printf("readTime_low: %lu\n", structs[0]->readTime_low);
    printf("RESERVED: %lu\n",structs[0]->RESERVED1[0]);
    printf("RESERVED: %lu\n",structs[0]->RESERVED1[1]);
    printf("RESERVED: %lu\n",structs[0]->RESERVED1[2]);
    printf("RESERVED: %lu\n",structs[0]->RESERVED1[3]);
    printf("RESERVED: %lu\n",structs[0]->RESERVED1[4]);
    printf("RESERVED: %lu\n",structs[0]->RESERVED1[5]);
    printf("RESERVED: %lu\n",structs[0]->RESERVED1[6]);
    printf("RESERVED: %lu\n",structs[0]->RESERVED1[7]);   
    printf("######################################################\n\n"); 


    float media=0;
    //se accede a la variable validSamples en cada estructura para calcular la media
    for(int i=0; i<cantidadstructs;i++){
        structs[i] = (datos*)file_memory + i;
        printf("Valor de validSamples en la estructura %d: %d\n",i,structs[i]->validSamples);
        media += structs[i]->validSamples;
    }
    
    printf("Tomando las %d estructuras la media de validSamples es de %f\n",cantidadstructs,media /= cantidadstructs);

    return 0;
   
    
}
