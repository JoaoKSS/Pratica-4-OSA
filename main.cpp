#include "Buffer.h"
#include "Registro.h"
#include "Index.h"
#include "Arvore.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

int main() {
    string arquivoCSV = "booksDataset.csv";
    string arquivoBinario = "dadosBinario.bin";
    string arquivoIndex = "Index.txt";

    vector<Registro> Registros;

    // ler arquivo CSV
    if (!Registro::carregarDoCSV(arquivoCSV, Registros)) {
        cerr << "Erro ao carregar registros do CSV." << endl;
        return 1;
    }

    // Salva os registros no formato binário com descritor de tamanho
    Buffer buffer(arquivoBinario, arquivoIndex);
    buffer.escreverDescritor(Registros);

    // Busca Registros
    try {
        //Encontrando registros por id
        cout << endl;
        cout << "+----------------------------------------------------------------+" << endl;
        cout << " Registros buscados e encontrados com sucesso e mostrados abaixo!" << endl;
        cout << "+----------------------------------------------------------------+" << endl << endl;
        buffer.buscarRegistro(105);
        buffer.buscarRegistro(203);
        buffer.buscarRegistro(102005);
    } catch (const runtime_error& e) {
        cerr << e.what() << endl;
    }

    // Adiciona novos registros
    try {
        vector<Registro> novosRegistros = {
            Registro(123457, "Zen and the Art of Guitar", "Harper, James",2010, "Music , Instruction & Study , Techniques"),
            Registro(123458, "Zero Hour: A Novel", "Smith, Caroline", 2018, "Fiction , Thrillers , Action & Adventure"),
            Registro(123459, "Zodiac Signs: An Illustrated Guide", "Moore, Abigail", 2021, "Self-Help , Astrology , Illustrated")
        };

        buffer.adicionarRegistros(novosRegistros);
        cout << endl << endl;
        cout << "+-----------------------------------------------------------------+" << endl;
        cout << " Registros novos foram adicionados com sucesso e mostrados abaixo!" << endl;
        cout << "+-----------------------------------------------------------------+" << endl;
        cout << endl;

        // Busca registros novos inseridos
        for(auto reg : novosRegistros) {
            buffer.buscarRegistro(reg.ID);
        }

    } catch (const std::exception& e) {
        cerr << "Erro ao adicionar registros: " << e.what() << endl;
    }

    cout << endl << "Todas operações concluída com sucesso!\n";
    return 0;
}
