#include <iostream>
#include "../utils/utils.h"
#include <fstream>
#include <vector>
#include <unistd.h> // Para utilizar la función fork
#include <wait.h> // Para utilizar la función wait

using namespace std;

void readLaunchInfo(int shipIndex, string& name, string& city, string& planet, int& temperature, int& humidity, int& wind, string& conditions, int& visibility, int& loadCapacity, int& fuelAmount, int& duration) {
    // Recopilar información del lanzamiento
    // Esta información se encuentra en el archivo "info/nave_<shipIndex>/info.txt"
    // Para el formato específico del archivo, revisar la consigna
    
    throw runtime_error("Not Implemented: No se ha implementado la función readLaunchInfo.");
}

void meteorologicalChecks(int shipIndex, int temperature, int humidity, int wind, string conditions, int visibility) {
    // Aquí se pueden realizar los chequeos meteorológicos necesarios
    // Recuerden que deben guardar la información en el archivo "info/nave_<shipIndex>/meteorologic.txt"
    // El formato del archivo es el siguiente:
    // - Si TODAS las condiciones son adecuadas, escribir en la última línea "SUCCESS"
    // - Si alguna de las condiciones no es adecuada, escribir en la última línea "FAIL"
    // Adicionalmente, pueden agregar información a lo largo del chequeo
    // para que quede registrado en el archivo de log

    // NO OLVIDEN QUE LA ÚLTIMA LÍNEA DEL ARCHIVO DEBE SER "SUCCESS" O "FAIL"
    // NO AGREGAR UN SALTO DE LÍNEA DESPUÉS DE "SUCCESS" O "FAIL"

    throw runtime_error("Not Implemented: No se ha implementado la función meteorologicalChecks.");
}

void flightChecks(int shipIndex, int loadCapacity, int fuelAmount, int duration) {
    // Aquí se pueden realizar los chequeos de vuelo necesarios
    // Recuerden que deben guardar la información en el archivo "info/nave_<shipIndex>/flight.txt"
    // El formato del archivo es el siguiente:
    // - Si TODOS los chequeos son exitosos, escribir en la última línea "SUCCESS"
    // - Si alguno de los chequeos no es exitoso, escribir en la última línea "FAIL"
    // Adicionalmente, pueden agregar información a lo largo del chequeo
    // para que quede registrado en el archivo de log

    // NO OLVIDEN QUE LA ÚLTIMA LÍNEA DEL ARCHIVO DEBE SER "SUCCESS" O "FAIL"
    // NO AGREGAR UN SALTO DE LÍNEA DESPUÉS DE "SUCCESS" O "FAIL"

    throw runtime_error("Not Implemented: No se ha implementado la función flightChecks.");
}

void shipLaunchChecks(int shipIndex) {
    // Leemos la información del archivo de información de la nave
    // Tenemos la función readLaunchInfo que recibe el índice de la nave y 
    // referencias a las variables donde se guardará la información
    string name, city, planet, conditions;
    int temperature, humidity, wind, visibility, loadCapacity, fuelAmount, duration;
    readLaunchInfo(shipIndex, name, city, planet, temperature, humidity, wind, conditions, visibility, loadCapacity, fuelAmount, duration);

    string messageStart = "[" + name + "] ";
    
    // Abrimos un archivo de log para guardar la información del lanzamiento
    // El archivo se guardará en "info/nave_<shipIndex>/log.txt"
    ofstream log("info/nave_" + to_string(shipIndex) + "/log.txt");
    if (!log.is_open()) exit(1);

    log << messageStart << city << " \u21E8 " << planet << endl;
    log << messageStart << "Comenzando preparación para el lanzamiento..." << endl;
    
    log << messageStart << "Iniciando sensores meteorológicos..." << endl;

    // A partir de aquí, tienen que completar el código

    // Recuerden verificar si el fork() fue exitoso o no
    // Si el fork() no fue exitoso, el valor de retorno será negativo

    // Reucerden que el log debe tener como última línea "SUCCESS" o "FAIL", 
    // sin salto de línea después de "SUCCESS" o "FAIL"

    // Una recomendación es que loggeen todo lo que pasa, esto les permitirá
    // ver qué está pasando en cada momento y si algo falla, podrán saber dónde

    // Les dejo un órden de ejecución sugerido:

    // 1. Forkeo para el chequeo meteorológico
    // 2. En el hijo, se ejecuta la función meteorologicalChecks, 
    //    NO OLVIDEN TERMINAR EL PROCESO HIJO DESPUÉS DE EJECUTAR LA FUNCIÓN
    // 3. En el padre, forkeo para el chequeo de vuelo
    // 4. En el hijo, se ejecuta la función flightChecks
    //    NO OLVIDEN TERMINAR EL PROCESO HIJO DESPUÉS DE EJECUTAR LA FUNCIÓN
    // 5. Esperar a que ambos hijos terminen. Recuerden que no queremos forzar un órden
    //    entre los dos hijos, ya que son chequeos que pueden hacerse en "paralelo".
    // 6. En el padre, chequear los logs correspondientes a cada chequeo (meteorológico y de vuelo)
    // 7. Si ambos chequeos son exitosos, escribir en el log del padre "SUCCESS"
    //    Si alguno de los chequeos falla, escribir "FAIL"
    // 8. Cerrar el log del padre
}