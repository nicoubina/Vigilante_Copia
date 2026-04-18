#include <iostream>
#include "../utils/utils.h"
#include <fstream>
#include <vector>
#include <unistd.h> // Para utilizar la función fork
#include <wait.h> // Para utilizar la función wait

using namespace std;

static string trimSpaces(const string& s) {
    size_t start = 0;
    while (start < s.size() && (s[start] == ' ' || s[start] == '\t' || s[start] == '\r' || s[start] == '\n')) {
        start++;
    }

    if (start == s.size()) return "";

    size_t end = s.size() - 1;
    while (end > start && (s[end] == ' ' || s[end] == '\t' || s[end] == '\r' || s[end] == '\n')) {
        end--;
    }

    return s.substr(start, end - start + 1);
}

static int extractNumber(const string& text) {
    string number = "";
    bool started = false;

    for (size_t i = 0; i < text.size(); i++) {
        char c = text[i];
        if ((c >= '0' && c <= '9') || (c == '-' && !started)) {
            number += c;
            started = true;
        } else if (started) {
            break;
        }
    }

    if (number.empty() || number == "-") return 0;
    return stoi(number);
}

void readLaunchInfo(int shipIndex, string& name, string& city, string& planet, int& temperature, int& humidity, int& wind, string& conditions, int& visibility, int& loadCapacity, int& fuelAmount, int& duration) {
    string filePath = "info/nave_" + to_string(shipIndex) + "/info.txt";
    ifstream file(filePath);

    if (!file.is_open()) {
        throw runtime_error("No se pudo abrir: " + filePath);
    }

    string line;
    while (getline(file, line)) {
        if (line.find("Nombre de la nave:") != string::npos) {
            name = trimSpaces(line.substr(line.find(':') + 1));
        } else if (line.find("Ciudad de lanzamiento:") != string::npos) {
            city = trimSpaces(line.substr(line.find(':') + 1));
        } else if (line.find("Destino:") != string::npos) {
            planet = trimSpaces(line.substr(line.find(':') + 1));
        } else if (line.find("Temperatura:") != string::npos) {
            temperature = extractNumber(line);
        } else if (line.find("Humedad:") != string::npos) {
            humidity = extractNumber(line);
        } else if (line.find("Viento:") != string::npos) {
            wind = extractNumber(line);
        } else if (line.find("Condiciones:") != string::npos) {
            conditions = trimSpaces(line.substr(line.find(':') + 1));
        } else if (line.find("Visibilidad:") != string::npos) {
            visibility = extractNumber(line);
        } else if (line.find("Capacidad de carga:") != string::npos) {
            loadCapacity = extractNumber(line);
        } else if (line.find("Combustible:") != string::npos) {
            fuelAmount = extractNumber(line);
        } else if (line.find("Duración del viaje:") != string::npos) {
            duration = extractNumber(line);
        }
    }

    file.close();
}

void meteorologicalChecks(int shipIndex, int temperature, int humidity, int wind, string conditions, int visibility) {
    string filePath = "info/nave_" + to_string(shipIndex) + "/meteorologic.txt";
    ofstream file(filePath);
    if (!file.is_open()) exit(1);

    bool okConditions = (conditions == "Despejado" || conditions == "despejado");
    bool okTemperature = (temperature >= 0 && temperature <= 25);
    bool okHumidity = (humidity >= 15 && humidity <= 85);
    bool okWind = (wind <= 45);
    bool okVisibility = (visibility >= 5);

    bool success = okConditions && okTemperature && okHumidity && okWind && okVisibility;

    file << "Chequeo meteorológico nave " << shipIndex << "\n";
    file << "Condiciones: " << conditions << "\n";
    file << "Temperatura: " << temperature << "\n";
    file << "Humedad: " << humidity << "\n";
    file << "Viento: " << wind << "\n";
    file << "Visibilidad: " << visibility << "\n";

    if (success) file << "SUCCESS";
    else file << "FAIL";

    file.close();
}

void flightChecks(int shipIndex, int loadCapacity, int fuelAmount, int duration) {
    string filePath = "info/nave_" + to_string(shipIndex) + "/flight.txt";
    ofstream file(filePath);
    if (!file.is_open()) exit(1);

    bool rule1 = (loadCapacity >= 2 * (fuelAmount * 0.81));
    bool rule2 = (fuelAmount >= duration * 8);
    bool success = rule1 && rule2;

    file << "Chequeo de vuelo nave " << shipIndex << "\n";
    file << "Capacidad de carga: " << loadCapacity << "\n";
    file << "Combustible: " << fuelAmount << "\n";
    file << "Duración: " << duration << "\n";

    if (success) file << "SUCCESS";
    else file << "FAIL";

    file.close();
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

    log << messageStart << city << " ⇨ " << planet << endl;
    log << messageStart << "Comenzando preparación para el lanzamiento..." << endl;
    
    log << messageStart << "Iniciando sensores meteorológicos..." << endl;

    pid_t meteoPID = fork();
    if (meteoPID < 0) {
        log << messageStart << "Error al crear proceso meteorológico." << endl;
        log << "FAIL";
        log.close();
        exit(1);
    }

    if (meteoPID == 0) {
        meteorologicalChecks(shipIndex, temperature, humidity, wind, conditions, visibility);
        exit(0);
    }

    log << messageStart << "Iniciando cálculos de vuelo..." << endl;

    pid_t flightPID = fork();
    if (flightPID < 0) {
        log << messageStart << "Error al crear proceso de vuelo." << endl;
        log << "FAIL";
        log.close();
        exit(1);
    }

    if (flightPID == 0) {
        flightChecks(shipIndex, loadCapacity, fuelAmount, duration);
        exit(0);
    }

    waitpid(meteoPID, NULL, 0);
    waitpid(flightPID, NULL, 0);

    ifstream meteoFile("info/nave_" + to_string(shipIndex) + "/meteorologic.txt");
    ifstream flightFile("info/nave_" + to_string(shipIndex) + "/flight.txt");

    string meteoResult = readLastLine(meteoFile);
    string flightResult = readLastLine(flightFile);

    meteoFile.close();
    flightFile.close();

    log << messageStart << "Recopilando información..." << endl;

    if (meteoResult == "SUCCESS" && flightResult == "SUCCESS") {
        log << messageStart << "Condiciones adecuadas para el lanzamiento." << endl;
        log << "SUCCESS";
    } else {
        log << messageStart << "Condiciones no adecuadas." << endl;
        log << "FAIL";
    }

    log.close();
}
