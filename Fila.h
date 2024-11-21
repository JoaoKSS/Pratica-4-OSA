/*****************************************************
 * IMPLEMENTAÇÃO DO TAD - Alocação dinâmica
 *****************************************************
 * TAD FILA IMPLEMENTADO UTILIZANDO ENCADEAMENTO DE NÓS
  *****************************************************/
// diretiva de pré-compilação para evitar a redefinição do tipo
#ifndef FILA_H
#define FILA_H

#include <cstdlib> // para usar o apontador NULL
#include <iostream>
#include <cassert>
using namespace std;

// implementação de uma classe para representação dos nós da FILA
template <class T>
class NodeFila
{
    public:
        T item;
        NodeFila<T>* prox;
        // construtor default
        NodeFila(){ prox = NULL;}
        // construtor com um parametro
        NodeFila(T it){item =it; prox =NULL;}
};

// Declaração da classe FILA, seus atributos e métodos.
template <class TIPO>
class Fila
{
    private:
        NodeFila<TIPO>* head; // apontador para o início da fila
        NodeFila<TIPO>* tail; // apontador para o final da fila
    public:
        Fila(); // construtor do TAD fila
        Fila(const Fila<TIPO>&); // construtor de cópia
        void Enfileirar(TIPO); // método para enfileirar dados no final da fila
        TIPO  Desenfileirar(); // método para desenfileirar dados do inicio da fila
        bool Vazia(); // método para verificar se um fila está vazia
        ~Fila(); // destrutor
        void Imprimir();
        Fila<TIPO>& operator=(const Fila<TIPO>&);
};

// construtor do TAD fila
template <class T>
Fila<T>::Fila()
{
    head = NULL;
    tail = NULL;
}

// construtor de cópia
template <class T>
Fila<T>::Fila(const Fila<T>& f)
{
    NodeFila<T> *aux = f.head;
    head = tail = NULL;
    while ( aux != NULL )
    {
        this->Enfileirar(aux->item);
        aux = aux->prox;
    }
}


// método para enfileirar dados no final da fila
template <class T>
void Fila<T>::Enfileirar(T item)
{
    // criar um novo nó contendo o item e apontando o prox para NULL (veja construtor do Node)
    NodeFila<T>* aux = new NodeFila<T>(item);

    // verifica se a Fila está vazia (head==NULL) e,
    // caso afirmativo, aponta head para o novo nó (aux)...
    if( head == NULL )
        head = aux;
    else // caso contrário, o prox do final da fila aponta para aux.
        tail->prox = aux;
    // faz aux ser o final da fila (tail aponta para aux)
    tail = aux;
}

// método para desenfileirar dados do inicio da fila
template <class T>
T  Fila<T>::Desenfileirar()
{
    assert ( !Vazia() );

    T aux = head->item; // recupera o elemento que está no início da fila
    NodeFila<T>* tmp = head; // armazena o endereço de head em tmp
    head = head->prox; // atualiza head para o próximo da fila
    delete tmp;   // remove da fila o nó que estava no início da fila
    return aux;   // retorna o resultado
}

// método para verificar se um fila está vazia
template <class T>
bool Fila<T>::Vazia()
{
    return head == NULL;
}

template <class T>
void Fila<T>::Imprimir()
{
    NodeFila<T> *aux = head;
    while (aux!=NULL)
    {
        cout<<aux->item<<"->";
        aux = aux->prox;
    }
}

template <class T>
Fila<T>::~Fila()
{
    NodeFila<T> *tmp, *aux = head;
    while (aux != NULL )
    {
        tmp = aux->prox;
        delete aux;
        aux = tmp;
    }
}

template <class T>
Fila<T>& Fila<T>::operator=(const Fila<T>& f)
{
    NodeFila<T> *aux = f.head;
    head = tail = NULL;
    while ( aux != NULL )
    {
        this->Enfileirar(aux->item);
        aux = aux->prox;
    }
    return *this;
}



#endif
