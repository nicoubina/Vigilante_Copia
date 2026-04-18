#include <iostream>
#include <unistd.h> // Para utilizar la función sleep
#include <string>
#include <sstream>
#include <fstream>
#include "utils.h"
#include <vector>

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

vector<string> split(const string& str, char delimiter, bool trim) {
    vector<string> parts;
    string part;
    stringstream ss(str);

    while (getline(ss, part, delimiter)) {
        if (trim) {
            parts.push_back(trimSpaces(part));
        } else {
            parts.push_back(part);
        }
    }

    return parts;
}

string readLastLine(ifstream& fileStream) {
    if (!fileStream.is_open()) return "";

    string line;
    string lastLine = "";

    while (getline(fileStream, line)) {
        lastLine = line;
    }

    return lastLine;
}

string boxedText(const string& text) {
    int length = text.length();
    int boxWidth = length + 4; // 2 espacios de margen a cada lado y 2 para los bordes
    stringstream ss;
    ss << "╔";
    for (int i = 0; i < boxWidth - 1; i++) {
        ss << "═";
    }
    ss << "╗\n";
    ss << "║  " << text << "  ║\n";
    ss << "╚";
    for (int i = 0; i < boxWidth - 1; i++) {
        ss << "═";
    }
    ss << "╝\n";
    return ss.str();
}

void welcomeScreen() {
    cout << endl;
    cout << "╔════════════════════════════════════════════════════════════════════════════════════════╗" << endl; 
    cout << "║                                                                                        ║" << endl;
    cout << "║         :::::::::::     :::::::::::     :::                :::         :::    :::      ║" << endl;
    cout << "║            :+:             :+:         :+:              :+: :+:       :+:    :+:       ║" << endl;
    cout << "║           +:+             +:+         +:+             +:+   +:+      +:+    +:+        ║" << endl;
    cout << "║          +#+             +#+         +#+            +#++:++#++:     +#++:++#++         ║" << endl;
    cout << "║         +#+             +#+         +#+            +#+     +#+     +#+    +#+          ║" << endl;
    cout << "║        #+#     #+#     #+#     #+# #+#        #+# #+#     #+# #+# #+#    #+# #+#       ║" << endl;
    cout << "║    ########### ### ########### ### ########## ### ###     ### ### ###    ### ###       ║" << endl;
    cout << "║                                                                                        ║" << endl;
    cout << "╚════════════ Instituto de Investigación y Lanzamiento Aeroespacial Huergo ══════════════╝" << endl;
    cout << endl;

    cout << "[System] Iniciando el programa...\n";
    usleep(SLEEP_TIME);

    cout << "[System] Cargando cálculos de trayectorias...\n";
    usleep(SLEEP_TIME); 

    cout << "[System] Midiendo datos meteorológicos...\n";

    usleep(SLEEP_TIME); 

    cout << "[System] Procedimiento de lanzamiento de " << NUM_SPACESHIPS << " naves espaciales iniciado." << endl;

    usleep(SLEEP_TIME);
}

void failedLaunch(int shipIndex, string details) {
    cout << "[";
    // Cambio color a rojo
    cout << "\033[31m"; // Cambia el color a rojo
    cout << "FAIL";
    cout << "\033[0m"; // Restablece el color
    cout << "] ";
    cout << "Lanzamiento de la nave " << spaceships[shipIndex - 1] << " fallido. " << details << endl;
}

void successfulLaunch(int shipIndex, string details) {
    cout << "[";
    // Cambio color a verde
    cout << "\033[32m"; // Cambia el color a verde
    cout << "SUCCESS";
    cout << "\033[0m"; // Restablece el color
    cout << "] ";
    cout << "Lanzamiento exitoso de la nave " << spaceships[shipIndex - 1] << "! " << details << endl;
}
