#ifndef LIVRO_H
#define LIVRO_H
#include<string>
#include<cstddef>
#include<stdint.h>
#include <string>
#include <sstream>
using namespace std;

class Livro{
    public:
        int id;
        string title;
        int anoPublicacao;
        string categoria;

        Livro(int id,const string &title,int anoPublicacao, const string &categoria);

        string packDelimited() const;
        //string pack() const;

        void unpackDelimited(const string& buffer);
        //void unpackDescritor(const string& buffer);
};
#endif