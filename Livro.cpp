#include "Livro.h"
#include <cstring>
#include<string>
#include<sstream>
using namespace std;

Livro::Livro(int id, const string &title, int anoPublicacao, const string &categoria)
    : id(id), title(title), anoPublicacao(anoPublicacao), categoria(categoria) {}

string Livro::packDelimited() const{
    
}