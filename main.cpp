#include "utils/utils.h"
#include "launch/launch.h"
#include <iostream>
#include <string>
#include <vector>
#include <unistd.h> // Para utilizar la función sleep y fork
#include <wait.h> // Para utilizar la función wait
#include <fstream>

using namespace std;

static int countShipsInInfoFolder() {
    int count = 0;

    for (int i = 1; ; i++) {
        string infoPath = "info/nave_" + to_string(i) + "/info.txt";
        ifstream file(infoPath);
        if (!file.is_open()) {
            break;
        }
        file.close();
        count++;
    }

    return count;
}

int main() {
    welcomeScreen();

    int shipsToLaunch = countShipsInInfoFolder();
    if (shipsToLaunch == 0) {
        cerr << "No se encontraron carpetas nave_i dentro de /info" << endl;
        return 1;
    }

    for(int i = 1; i <= shipsToLaunch; i++) {
        pid_t shipPID = fork();

        if (shipPID < 0) {
            cerr << "Error al crear el proceso para la nave " << i << endl;
            cerr << "Se abortará la misión" << i << endl;
            exit(1);
        } else if (shipPID == 0) {
            shipLaunchChecks(i);
            exit(0);
        }
    }

    while (wait(NULL) > 0);

    for(int i = 1; i <= shipsToLaunch; i++) {
        usleep(SLEEP_TIME);
        string logFilePath = "info/nave_" + to_string(i) + "/log.txt";
        ifstream logFile(logFilePath);

        if (!logFile.is_open()) {
            failedLaunch(i, "No se pudo abrir el archivo de log. Asumimos que el lanzamiento falló.");
            logFile.close();
            continue;
        }

        string line = readLastLine(logFile);

        if (line == "SUCCESS") {
            successfulLaunch(i);
        } else if (line == "FAIL") {
            failedLaunch(i, "Verifique el log para más información.");
        } else {
            failedLaunch(i, "Estado desconocido. Asumimos que el lanzamiento falló.");
        }

        logFile.close();
    }

    return 0;
}
