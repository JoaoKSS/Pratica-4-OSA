#ifndef BUFFER_H
#define BUFFER_H
#include "Registro.h"
#include <fstream>
#include <stdexcept>
using namespace std;

class Buffer {
public:
    string nomeArquivo;

    Buffer(const string& nomeArquivo);

    Registro lerDelimitado();
    Registro lerDescritor();

    void escreverDelimitado(const Registro& reg);
    void escreverDescritor(const Registro& reg);
};

#endif
