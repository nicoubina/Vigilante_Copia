#ifndef UTILS_H
#define UTILS_H

#include <string>

struct DatosNave {
    std::string nombre;
    std::string ciudad;
    std::string destino;
    std::string condiciones;
    double temperatura = 0.0;
    double humedad = 0.0;
    double viento = 0.0;
    double visibilidad = 0.0;
    double capacidadCarga = 0.0;
    double combustible = 0.0;
    double duracion = 0.0;
};

bool leerInfo(const std::string& path, DatosNave& d);

#endif
