#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Estrutura para armazenar informações de participantes
struct Participante {
    int id;
    string nome;
    int semestre;
    int anoIngresso;
    string curso;
    Participante* proximo;
};

// Estrutura para armazenar informações de contribuições
struct Contribuicao {
    int idParticipante;
    int mes;
    int ano;
    double valor;
    Contribuicao* proximo;
};

// Nó da lista encadeada de participantes
struct Node {
    Participante participante;
    Node* next;
};

// Nó da lista encadeada de contribuições
struct NodeContribuicao {
    Contribuicao contribuicao;
    NodeContribuicao* next;
};

Node* headParticipantes = NULL;
NodeContribuicao* headContribuicoes = NULL;

// Função para inserir participante na lista encadeada
void inserirParticipante(int id, string nome, int semestre, int anoIngresso, string curso) {
    Participante novoParticipante;
    novoParticipante.id = id;
    novoParticipante.nome = nome;
    novoParticipante.semestre = semestre;
    novoParticipante.anoIngresso = anoIngresso;
    novoParticipante.curso = curso;

    Node* novoNode = new Node();
    novoNode->participante = novoParticipante;
    novoNode->next = NULL;

    if (headParticipantes == NULL) {
        headParticipantes = novoNode;
    } else {
        Node* temp = headParticipantes;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = novoNode;
    }

    cout << "Participante inserido com sucesso!" << endl;
}

// Função para verificar se um participante existe
bool participanteExiste(int id) {
    Node* temp = headParticipantes;
    while (temp != NULL) {
        if (temp->participante.id == id) {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

// Função para ler participantes do arquivo e inserir na lista encadeada
void lerParticipantesDoArquivo() {
    ifstream arquivo("participantes.txt");
    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo participantes.txt" << endl;
        return;
    }

    int id, semestre, anoIngresso;
    string nome, curso;

    while (arquivo >> id >> nome >> semestre >> anoIngresso >> curso) {
        inserirParticipante(id, nome, semestre, anoIngresso, curso);
    }

    arquivo.close();
}

// Função para editar participante na lista encadeada
void editarParticipante(int id) {
    Node* temp = headParticipantes;
    while (temp != NULL) {
        if (temp->participante.id == id) {
            string nome, curso;
            int semestre, anoIngresso;

            cout << "Digite o novo nome: ";
            cin >> nome;
            cout << "Digite o novo semestre: ";
            cin >> semestre;
            cout << "Digite o novo ano de ingresso: ";
            cin >> anoIngresso;
            cout << "Digite o novo curso (DSM, SI, GE): ";
            cin >> curso;

            temp->participante.nome = nome;
            temp->participante.semestre = semestre;
            temp->participante.anoIngresso = anoIngresso;
            temp->participante.curso = curso;

            cout << "Participante atualizado com sucesso!" << endl;
            return;
        }
        temp = temp->next;
    }
    cout << "Participante com ID " << id << " não encontrado." << endl;
}

// Função para mostrar todos os participantes cadastrados
void mostrarParticipantes() {
    if (headParticipantes == NULL) {
        cout << "Nenhum participante cadastrado." << endl;
    } else {
        Node* temp = headParticipantes;
        while (temp != NULL) {
            cout << "ID: " << temp->participante.id 
                 << ", Nome: " << temp->participante.nome 
                 << ", Semestre: " << temp->participante.semestre 
                 << ", Ano de Ingresso: " << temp->participante.anoIngresso 
                 << ", Curso: " << temp->participante.curso << endl;
            temp = temp->next;
        }
    }
}

// Função para gravar participantes no arquivo
void gravarParticipantesNoArquivo() {
    ofstream arquivo("participantes.txt");
    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo participantes.txt para escrita." << endl;
        return;
    }

    Node* temp = headParticipantes;
    while (temp != NULL) {
        arquivo << temp->participante.id << " "
                << temp->participante.nome << " "
                << temp->participante.semestre << " "
                << temp->participante.anoIngresso << " "
                << temp->participante.curso << endl;
        temp = temp->next;
    }

    arquivo.close();
    cout << "Dados dos participantes gravados com sucesso em participantes.txt." << endl;
}

// Função para cadastrar contribuição de um participante
void cadastrarContribuicao(int idParticipante, int mes, int ano, double valor) {
    if (!participanteExiste(idParticipante)) {
        cout << "Participante com ID " << idParticipante << " não encontrado. Nenhuma contribuicao cadastrada." << endl;
        return;
    }

    Contribuicao novaContribuicao;
    novaContribuicao.idParticipante = idParticipante;
    novaContribuicao.mes = mes;
    novaContribuicao.ano = ano;
    novaContribuicao.valor = valor;

    NodeContribuicao* novoNode = new NodeContribuicao();
    novoNode->contribuicao = novaContribuicao;
    novoNode->next = NULL;

    if (headContribuicoes == NULL) {
        headContribuicoes = novoNode;
    } else {
        NodeContribuicao* temp = headContribuicoes;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = novoNode;
    }

    cout << "Contribuição cadastrada com sucesso!" << endl;
}

// Função para liberar a memória alocada para participantes
void liberarMemoriaParticipantes() {
    Node* temp = headParticipantes;
    while (temp != NULL ){
        Node* proximo = temp->next;
        delete temp;
        temp = proximo;
    }
}

// Função para liberar a memória alocada para contribuições
void liberarMemoriaContribuicoes() {
    NodeContribuicao* temp = headContribuicoes;
    while (temp != NULL) {
        NodeContribuicao* proximo = temp->next;
        delete temp;
        temp = proximo;
        delete temp;
        temp = proximo;
    }
}

// Função para exibir todas as contribuições cadastradas
void mostrarContribuicoes() {
    if (headContribuicoes == NULL) {
        cout << "Nenhuma contribuição cadastrada." << endl;
    } else {
        NodeContribuicao* temp = headContribuicoes;
        while (temp != NULL) {
            cout << "ID Participante: " << temp->contribuicao.idParticipante
                 << ", Mes: " << temp->contribuicao.mes
                 << ", Ano: " << temp->contribuicao.ano
                 << ", Valor: " << temp->contribuicao.valor << endl;
            temp = temp->next;
        }
    }
}

// Função para gravar contribuições no arquivo
void gravarContribuicoesNoArquivo() {
    ofstream arquivo("contribuicoes.txt");
    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo contribuicoes.txt para escrita." << endl;
        return;
    }

    NodeContribuicao* temp = headContribuicoes;
    while (temp != NULL) {
        arquivo << temp->contribuicao.idParticipante << " "
                << temp->contribuicao.mes << " "
                << temp->contribuicao.ano << " "
                << temp->contribuicao.valor << endl;
        temp = temp->next;
    }

    arquivo.close();
    cout << "Contribuições gravadas com sucesso em contribuicoes.txt." << endl;
}

// Função para gravar contribuições por curso nos arquivos separados
string getCursoById(int id) {
    Node* temp = headParticipantes;
    while (temp != NULL) {
        if (temp->participante.id == id) {
            return temp->participante.curso;
        }
        temp = temp->next;
    }
    
}

void gravarContribuicoesPorCurso() {
    // Abre os arquivos em modo sobrescrever (overwrite)
    ofstream arquivoDSM("contribuintes_DSM.txt");
    ofstream arquivoSI("contribuintes_SI.txt");
    ofstream arquivoGE("contribuintes_GE.txt");

    // Verifica se os arquivos foram abertos corretamente
    if (!arquivoDSM.is_open() || !arquivoSI.is_open() || !arquivoGE.is_open()) {
        cout << "Erro ao abrir arquivos de saída." << endl;
        return;
    }

    NodeContribuicao* temp = headContribuicoes;
    while (temp != NULL) {
        if (temp->contribuicao.idParticipante != -1) {
            std::string curso = getCursoById(temp->contribuicao.idParticipante);

            if (curso == "DSM") {
                arquivoDSM << temp->contribuicao.idParticipante << " "
                           << temp->contribuicao.mes << " "
                           << temp->contribuicao.ano << " "
                           << temp->contribuicao.valor << endl;
            } else if (curso == "SI") {
                arquivoSI << temp->contribuicao.idParticipante << " "
                          << temp->contribuicao.mes << " "
                          << temp->contribuicao.ano << " "
                          << temp->contribuicao.valor << endl;
            } else if (curso == "GE") {
                arquivoGE << temp->contribuicao.idParticipante << " "
                          << temp->contribuicao.mes << " "
                          << temp->contribuicao.ano << " "
                          << temp->contribuicao.valor << endl;
            } else {
                cout << "Curso desconhecido para o ID: " << temp->contribuicao.idParticipante << endl;
            }
        }
        temp = temp->next;
    }

    arquivoDSM.close();
    arquivoSI.close();
    arquivoGE.close();

    cout << "Contribuições gravadas com sucesso:" << endl;
    cout << " - contribuintes_DSM.txt" << endl;
    cout << " - contribuintes_SI.txt" << endl;
    cout << " - contribuintes_GE.txt" << endl;
}


// Função para liberar toda a memória alocada
void liberarMemoria() {
    liberarMemoriaParticipantes();
    liberarMemoriaContribuicoes();
}
void lerRelatorioContribuintesPorCurso() {
    ifstream arquivoDSM("contribuintes_DSM.txt");
    ifstream arquivoSI("contribuintes_SI.txt");
    ifstream arquivoGE("contribuintes_GE.txt");

    // Verifica se os arquivos foram abertos corretamente
    if (!arquivoDSM.is_open()) {
        cout << "Erro ao abrir arquivo contribuintes_DSM.txt" << endl;
    } else {
        string linha;
        cout << "\nContribuintes do curso DSM:" << endl;
        while (getline(arquivoDSM, linha)) {
            cout << linha << endl;
        }
        arquivoDSM.close();
    }

    if (!arquivoSI.is_open()) {
        cout << "Erro ao abrir arquivo contribuintes_SI.txt" << endl;
    } else {
        string linha;
        cout << "\nContribuintes do curso SI:" << endl;
        while (getline(arquivoSI, linha)) {
            cout << linha << endl;
        }
        arquivoSI.close();
    }

    if (!arquivoGE.is_open()) {
        cout << "Erro ao abrir arquivo contribuintes_GE.txt" << endl;
    } else {
        string linha;
        cout << "\nContribuintes do curso GE:" << endl;
        while (getline(arquivoGE, linha)) {
            cout << linha << endl;
        }
        arquivoGE.close();
    }
}


// Função principal
int main() {
    int opcao;

    do {
        cout << "\nMenu Principal Cafezinho\n";
        cout << "1. Inserir novo participante\n";
        cout << "2. Mostrar todos os participantes\n";
        cout << "3. Editar participante\n";
        cout << "4. Ler participantes do arquivo\n";
        cout << "5. Salvar participantes no arquivo\n";
        cout << "6. Cadastrar contribuição\n";
        cout << "7. Mostrar todas as contribuições\n";
        cout << "8. Gravar contribuições no arquivo\n";
        cout << "9. Gravar contribuições por curso\n";
        cout << "10.Ler relatorio de contribuintes por curso\n"; 
        cout << "0. Sair\n";
        cout << "Escolha uma opção: ";
        cin >> opcao;

        switch (opcao) {
            case 1: {
                int id, semestre, anoIngresso;
                string nome, curso;

                cout << "Digite o ID: ";
                cin >> id;
                cout << "Digite o nome: ";
                cin.ignore(); // Limpar o buffer de entrada
                getline(cin, nome);
                cout << "Digite o semestre: ";
                cin >> semestre;
                cout << "Digite o ano de ingresso: ";
                cin >> anoIngresso;
                cout << "Digite o curso (DSM, SI, GE): ";
                cin.ignore(); // Limpar o buffer de entrada
                getline(cin, curso);

                inserirParticipante(id, nome, semestre, anoIngresso, curso);
                break;
            }
            case 2:
                mostrarParticipantes();
                break;
            case 3: {
                int id;
                cout << "Digite o ID do participante a ser editado: ";
                cin >> id;
                editarParticipante(id);
                break;
            }
            case 4:
                lerParticipantesDoArquivo();
                break;
            case 5:
                gravarParticipantesNoArquivo();
                break;
            case 6: {
                int idParticipante, mes, ano;
                double valor;

                cout << "Digite o ID do participante: ";
                cin >> idParticipante;
                cout << "Digite o mes da contribuicao (1 a 12): ";
                cin >> mes;
                cout << "Digite o ano da contribuicao (>= 2024): ";
                cin >> ano;
                cout << "Digite o valor da contribuicao: ";
                cin >> valor;

                cadastrarContribuicao(idParticipante, mes, ano, valor);
                break;
            }
            case 7:
                mostrarContribuicoes();
                break;
            case 8:
                gravarContribuicoesNoArquivo();
                break;
            case 9:
                gravarContribuicoesPorCurso();
                break;
            case 10:
			    lerRelatorioContribuintesPorCurso();  // Chama a nova função
                break;
    
            case 0:
                cout << "Saindo..." << endl;
                break;
            default:
                cout << "Opcao invalida!" << endl;
        }
    } while (opcao != 0);

    liberarMemoria();

    return 0;
}

