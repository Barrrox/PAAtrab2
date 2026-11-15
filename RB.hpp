#ifndef RB_HPP
#define RB_HPP

#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
using namespace std;

#define VERMELHO true
#define PRETO false


// classe do nó
class nodeRB
{
private:

  nodeRB *esq, *dir;  // ponteiro esquerdo e direito
  int chave;  // dado
  bool cor; // cor (VERMELHO ou PRETO)


public:
  nodeRB(int chave) // construtor
  {
    this->chave = chave;
    esq = NULL;
    dir = NULL;
    cor = VERMELHO;
  }

  int getChave() { return chave; }   // método de acesso a chave
  nodeRB* getEsq() { return esq; }   // método de acesso ao nó esquerdo
  nodeRB* getDir() { return dir; }  // método de acesso ao nó direito
  void setEsq(nodeRB *no) { esq = no;}  // método de definição do nó esquerdo
  void setDir(nodeRB *no) { dir = no; } // método de definição do nó direito
  void setChave(int chave) { this->chave = chave; } // método de definição da chave do nó
  void setCor(bool cor) { this->cor = cor; } // método de definição da cor do nó
  bool getCor(){ return this->cor; } // método de acesso a cor do nó

};





// classe da árvore
class arvoreRB
{
private:
  nodeRB *raiz; // raiz da árvore
public:
  ~arvoreRB(); // destrutor
  void destruirAux(nodeRB* no);
  arvoreRB() { raiz = NULL; }  // construtor
  void inserir(int chave, long long &comparacoes);  // método de inserção na árvore
  nodeRB* inserirAux(nodeRB *no, int chave, long long &comparacoes);  // método de inserção na árvore
  nodeRB *getRaiz() // método de acesso a raiz da arvore
  {
    return raiz;
  }
  void setRaiz(nodeRB *no){ this->raiz = no; }  // método de definição da raiz
  void emOrdem(); // percurso em ordem
  void emOrdemAux(nodeRB* no, int altura);  // percurso em ordem
  bool ehVermelho(nodeRB *no); // método auxiliar de verificação de cor
  nodeRB* rotacaoEsq(nodeRB *no); // método de rotação esquerda
  nodeRB* rotacaoDir(nodeRB *no); // método de rotação direita
  nodeRB* rotacaoDuploEsq(nodeRB *no); // método de rotação Left-right
  nodeRB* rotacaoDuploDir(nodeRB *no);	// método de rotação Right-left
  bool buscar(int chave, long long &comparacoes);

};

bool arvoreRB::ehVermelho(nodeRB *no){
  // nós nulos são considerados pretos
  if (no == NULL)
    return false;
  return no->getCor() == VERMELHO;
}

void arvoreRB::emOrdem(){
  emOrdemAux(this->getRaiz(),0);
}

void arvoreRB::emOrdemAux(nodeRB* no, int altura)
{
  if (no != NULL)
  {
    emOrdemAux(no->getEsq(), altura + 1);
    cout << no->getChave() << "," <<  altura << "," << (no->getCor() == VERMELHO ? "V" : "P") << endl;
    emOrdemAux(no->getDir(), altura + 1);
  }
}



void arvoreRB::inserir(int chave, long long &comparacoes) {

  // promove alterações pela raiz
  raiz = inserirAux(raiz, chave, comparacoes);

  // raiz é sempre preta
  raiz->setCor(PRETO);
}

nodeRB* arvoreRB::inserirAux(nodeRB* no, int chave, long long &comparacoes) {
  if (no == NULL)
      return new nodeRB(chave);

  comparacoes++;
  // valor é menor que o nó
  if (chave < no->getChave()) {
      no->setEsq(inserirAux(no->getEsq(), chave, comparacoes));
  }
  // valor é maior que o nó
  else {
      comparacoes++;
      if (chave > no->getChave()) {
          no->setDir(inserirAux(no->getDir(), chave, comparacoes));
      } else {
          return no; // Chave duplicada
      }
  }

  // Filho esquerdo e neto vermelhos (violação à esquerda)
  if (ehVermelho(no->getEsq()) && (ehVermelho(no->getEsq()->getEsq()) || ehVermelho(no->getEsq()->getDir()))) {

      // Caso 01: Tio vermelho, apenas recolore
      if (ehVermelho(no->getDir())) {
          no->setCor(VERMELHO);
          no->getEsq()->setCor(PRETO);
          no->getDir()->setCor(PRETO);
          return no;
      }

      // Caso 02: Tio preto
      if (ehVermelho(no->getEsq()->getEsq())) {
          return rotacaoDir(no);      // Rotação simples à direita
      } else {
          return rotacaoDuploDir(no); // Rotação dupla (Esq no filho + Dir no pivô)
      }
  }

  // Filho direito e neto vermelhos (violação à direita)
  if (ehVermelho(no->getDir()) && (ehVermelho(no->getDir()->getDir()) || ehVermelho(no->getDir()->getEsq()))) {

      // Caso 01: Tio vermelho, apenas recolore
      if (ehVermelho(no->getEsq())) {
          no->setCor(VERMELHO);
          no->getEsq()->setCor(PRETO);
          no->getDir()->setCor(PRETO);
          return no;
      }

      // Caso 02: Tio preto
      if (ehVermelho(no->getDir()->getDir())) {
          return rotacaoEsq(no);      // Rotação simples à esquerda
      } else {
          return rotacaoDuploEsq(no); // Rotação dupla (Dir no filho + Esq no pivô)
      }
  }

  return no;
}

nodeRB* arvoreRB::rotacaoEsq(nodeRB* no) {
    nodeRB* novaRaiz = no->getDir();
    no->setDir(novaRaiz->getEsq());
    novaRaiz->setEsq(no);

    novaRaiz->setCor(PRETO);
    no->setCor(VERMELHO);

    return novaRaiz;
}

nodeRB* arvoreRB::rotacaoDir(nodeRB* no) {
  nodeRB* novaRaiz = no->getEsq();
  no->setEsq(novaRaiz->getDir());
  novaRaiz->setDir(no);

  novaRaiz->setCor(PRETO);
  no->setCor(VERMELHO);

  return novaRaiz;
}

nodeRB* arvoreRB::rotacaoDuploEsq(nodeRB* no) {
  no->setDir(rotacaoDir(no->getDir()));
  return rotacaoEsq(no);
}

nodeRB* arvoreRB::rotacaoDuploDir(nodeRB* no) {
  no->setEsq(rotacaoEsq(no->getEsq()));
  return rotacaoDir(no);
}

arvoreRB::~arvoreRB() {
  destruirAux(raiz);
}

void arvoreRB::destruirAux(nodeRB* no) {
  if (no != NULL) {
    destruirAux(no->getEsq());
    destruirAux(no->getDir());
    delete no;
  }
}

bool arvoreRB::buscar(int chave, long long &comparacoes) {
  nodeRB* atual = raiz;
  while (atual != NULL) {
    comparacoes++;
    if (chave < atual->getChave()) {
      atual = atual->getEsq();
    } else {
      comparacoes++;
      if (chave > atual->getChave()) {
        atual = atual->getDir();
      } else {
        return true; // Encontrou
      }
    }
  }
  return false; // Não existe na árvore
}

arvoreRB* ConstruirRB(const vector<int>& entrada, long long &comparacoes) {
  arvoreRB* arvore = new arvoreRB();
  comparacoes = 0;

  for (int valor : entrada) {
    arvore->inserir(valor, comparacoes);
  }

  return arvore;
}

long long ConsultarRB(arvoreRB* arvore, const vector<int>& entrada) {
  long long comparacoes = 0;
  if (arvore == NULL) return comparacoes;

  for (int valor : entrada) {
    arvore->buscar(valor, comparacoes);
  }

  return comparacoes;
}

#endif