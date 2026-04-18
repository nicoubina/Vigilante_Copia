#include "utils.h"

#include <fstream>
#include <string>

namespace {

bool parseDouble(const std::string& value, double& out) {
    try {
        size_t idx = 0;
        out = std::stod(value, &idx);
        return idx == value.size();
    } catch (...) {
        return false;
    }
}

}  // namespace

bool leerInfo(const std::string& path, DatosNave& d) {
    std::ifstream archivo(path);
    if (!archivo.is_open()) {
        return false;
    }

    std::string linea;
    while (std::getline(archivo, linea)) {
        if (linea.empty()) {
            continue;
        }

        const std::size_t pos = linea.find('=');
        if (pos == std::string::npos) {
            continue;
        }

        const std::string clave = linea.substr(0, pos);
        const std::string valor = linea.substr(pos + 1);

        if (clave == "nombre") {
            d.nombre = valor;
        } else if (clave == "ciudad") {
            d.ciudad = valor;
        } else if (clave == "destino") {
            d.destino = valor;
        } else if (clave == "condiciones") {
            d.condiciones = valor;
        } else if (clave == "temperatura") {
            parseDouble(valor, d.temperatura);
        } else if (clave == "humedad") {
            parseDouble(valor, d.humedad);
        } else if (clave == "viento") {
            parseDouble(valor, d.viento);
        } else if (clave == "visibilidad") {
            parseDouble(valor, d.visibilidad);
        } else if (clave == "capacidadCarga") {
            parseDouble(valor, d.capacidadCarga);
        } else if (clave == "combustible") {
            parseDouble(valor, d.combustible);
        } else if (clave == "duracion") {
            parseDouble(valor, d.duracion);
        }
    }

    return true;
}
