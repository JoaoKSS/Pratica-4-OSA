#include "Registro.h"
#include <cstring>
#include <sstream>
// função que conta o número de aspas

Registro::Registro() : ID(0), title(""), authors(""), publishYear(0), category("") {}

Registro::Registro(int ID, const string& title, const string& authors, int publishYear, const string& category)
    : ID(ID), title(title), authors(authors), publishYear(publishYear), category(category) {}

// Empacota os dados do registro em um formato com descritor de tamanho.
string Registro::packDescritor() const {
    string linha = to_string(ID) + "|" + title + "|" + authors + "|" + to_string(publishYear) + "|" + category + "\n";

    int tamanho = linha.size();
    string buffer(sizeof(int), '\0');
    memcpy(&buffer[0], &tamanho, sizeof(int));
    buffer += linha;
    return buffer;
}

void Registro::unpackDelimited(const string& buffer) {
    stringstream stream(buffer);
    string ID_str;
    getline(stream, ID_str, ';');
    ID = stoi(ID_str);
    getline(stream, authors, ';');
    string publishYear_str;
    getline(stream, publishYear_str, ';');
    publishYear = stoi(publishYear_str);
    getline(stream, category, '\n');
}

void Registro::unpackDelimitedBinary(const string& buffer) {
    stringstream stream(buffer);
    string ID_str;
    getline(stream, ID_str, '|');
    ID = stoi(ID_str);
    getline(stream, title, '|');
    getline(stream, authors, '|');
    string publishYear_str;
    getline(stream, publishYear_str, '|');
    publishYear = stoi(publishYear_str);
    getline(stream, category, '\n');
}

// Desempacota os dados de um registro no formato com descritor de tamanho.
void Registro::unpackDescritor(const string& buffer) {
    int tamanho;
    memcpy(&tamanho, buffer.data(), sizeof(int));
    unpackDelimitedBinary(buffer.substr(sizeof(int), tamanho));
}
