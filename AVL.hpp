#ifndef AVL_HPP
#define AVL_HPP

#include <iostream>
#include <sstream>
#include <algorithm>
using namespace std;


// classe do nó
class node
{
private:

  node *esq, *dir;  // ponteiro esquerdo e direito
  int chave;  // dado
  int altura; // altura


public:
  node(int chave) // construtor
  {
    this->chave = chave;
    esq = NULL;
    dir = NULL;
    altura = 1;
  }

  int getChave() { return chave; }   // método de acesso a chave
  node* getEsq() { return esq; }   // método de acesso ao nó esquerdo
  node* getDir() { return dir; }  // método de acesso ao nó direito
  void setEsq(node *no) { esq = no;}  // método de definição do nó esquerdo
  void setDir(node *no) { dir = no; } // método de definição do nó direito
  void setChave(int chave) { this->chave = chave; } // método de definição da chave do nó
  void setAltura(){ // método de definição da altura do nó 
    int alturaEsq = esq ? esq->getAltura() : 0;
    int alturaDir = dir ? dir->getAltura() : 0;
    altura = 1 + max(alturaEsq, alturaDir);
  }
  int getAltura(){ return this->altura; } // método de acesso a altura do nó

};





// classe da árvore 
class arvoreAVL
{
private:
  node *raiz; // raiz da árvore
public:
  ~arvoreAVL(); // destrutor
  void destruirAux(node* no);
  arvoreAVL() { raiz = NULL; }  // construtor
  void inserir(int chave, long long &comparacoes);  // método de inserção na árvore
  node* inserirAux(node *no, int chave, long long &comparacoes);  // método de inserção na árvore
  node *getRaiz() // método de acesso a raiz da arvore
  {
    return raiz;
  }
  void setRaiz(node *no){ this->raiz = no; }  // método de definição da raiz 
  void emOrdem(); // percurso em ordem
  void emOrdemAux(node* no, int altura);  // percurso em ordem
  void remover(int chave);  // método de remoção de nó
  node* remocao(node *no, int chave); // método de remoção de nó
  node* sucessor(node* no); // método auxiliar de busca de sucessor
  node* antecessor(node *no); // método auxiliar de busca de antecessor
  node* rotacaoEsq(node *no); // método de rotação esquerda
  node* rotacaoDir(node *no); // método de rotação direita
  node* rotacaoDuploEsq(node *no); // método de rotação Left-right
  node* rotacaoDuploDir(node *no);	// método de rotação Right-left
  bool buscar(int chave, long long &comparacoes);

};

void arvoreAVL::remover(int chave){
  raiz = remocao(raiz, chave);
}

node* arvoreAVL::remocao(node* no, int chave) {
  // Caso base: árvore nula
  if (no == NULL)
    return no;

  // Verifica se valor é menor
  if (chave < no->getChave()) {
    no->setEsq(remocao(no->getEsq(), chave));
  } 
  // Verifica se valor é maior
  else if (chave > no->getChave()) {
    no->setDir(remocao(no->getDir(), chave));
  } 
  else {
    // Caso 01: Nó folha
    if (no->getEsq() == NULL && no->getDir() == NULL) {
      delete no;
      return NULL;
    }
    // Caso 02: Nó com um único filho
    if (no->getEsq() == NULL) {
      node* temp = no->getDir();
      delete no;
      return temp;
    } 
    else if (no->getDir() == NULL) {
      node* temp = no->getEsq();
      delete no;
      return temp;
    }

    // Caso 03: Nó com dois filhos
    node* s = antecessor(no);
    no->setChave(s->getChave());
    no->setEsq(remocao(no->getEsq(), s->getChave()));
  }

  // Atualizar altura do nó
  int alturaEsq = no->getEsq() ? no->getEsq()->getAltura() : 0;
  int alturaDir = no->getDir() ? no->getDir()->getAltura() : 0;
  no->setAltura();

  // Recalcular o fator de balanceamento (FB)
  int FB = alturaDir - alturaEsq; // Slides: SAD - SAE

  // Desbalanceado para a esquerda (FB < -1)
  if (FB < -1) {
      int altEsqEsq = no->getEsq()->getEsq() ? no->getEsq()->getEsq()->getAltura() : 0;
      int altEsqDir = no->getEsq()->getDir() ? no->getEsq()->getDir()->getAltura() : 0;
      int FBEsq = altEsqDir - altEsqEsq;

      if (FBEsq <= 0) {
          return rotacaoDir(no);      // Rotação simples à direita
      } else {
          return rotacaoDuploDir(no); // Rotação dupla (Esq no filho + Dir no pivô)
      }
  }

  // Desbalanceado para a direita (FB > 1)
  if (FB > 1) {
      int altDirEsq = no->getDir()->getEsq() ? no->getDir()->getEsq()->getAltura() : 0;
      int altDirDir = no->getDir()->getDir() ? no->getDir()->getDir()->getAltura() : 0;
      int FBDir = altDirDir - altDirEsq;

      if (FBDir >= 0) {
          return rotacaoEsq(no);      // Rotação simples à esquerda
      } else {
          return rotacaoDuploEsq(no); // Rotação dupla (Dir no filho + Esq no pivô)
      }
  }

  return no;
}



node* arvoreAVL::sucessor(node* no)
{
  // sucessor, nó mais a esquerda da subárvore da direita
  //sucessor nunca tem filho esquerdo!
  no = no->getDir();
  while(no != NULL && no->getEsq() != NULL)
    no = no->getEsq();
  return no;
}

node* arvoreAVL::antecessor(node *no)
{
  //antecessor o nó mais a direita da subárvore esquerda
  no = no->getEsq();
  while(no != NULL && no->getDir() != NULL)
    no = no->getDir();
  return no;
}

void arvoreAVL::emOrdem(){
  emOrdemAux(this->getRaiz(),0);
}
  
void arvoreAVL::emOrdemAux(node* no, int altura)
{
  if (no != NULL)
  {
    emOrdemAux(no->getEsq(), altura + 1);
    cout << no->getChave() << "," <<  altura << endl;
    emOrdemAux(no->getDir(), altura + 1);
  }
}



void arvoreAVL::inserir(int chave, long long &comparacoes) {

  // promove alterações pela raiz
  raiz = inserirAux(raiz, chave, comparacoes);
}

node* arvoreAVL::inserirAux(node* no, int chave, long long &comparacoes) {
  
  if (no == NULL)
      return new node(chave);
  
  comparacoes++;
  // valor é menor que o nó
  if (chave < no->getChave()) {
      no->setEsq(inserirAux(no->getEsq(), chave, comparacoes));
  } 
  // valor é maior que o nó
  else {
      if (chave > no->getChave()) {
          no->setDir(inserirAux(no->getDir(), chave, comparacoes));
      } else {
          return no; // Chave duplicada
      }
  }
  
  // Fator de balanceamento do nó
  int FB;
  no->setAltura();
  int alturaEsq = no->getEsq() ? no->getEsq()->getAltura() : 0;
  int alturaDir = no->getDir() ? no->getDir()->getAltura() : 0;
  FB = alturaDir - alturaEsq; // Slides: SAD - SAE

  // Desbalanceado para a esquerda (FB < -1)
  if (FB < -1) {
      int altEsqEsq = no->getEsq()->getEsq() ? no->getEsq()->getEsq()->getAltura() : 0;
      int altEsqDir = no->getEsq()->getDir() ? no->getEsq()->getDir()->getAltura() : 0;
      int FBEsq = altEsqDir - altEsqEsq;

      if (FBEsq <= 0) {
          return rotacaoDir(no);      // Rotação simples à direita
      } else {
          return rotacaoDuploDir(no); // Rotação dupla (Esq no filho + Dir no pivô)
      }
  }

  // Desbalanceado para a direita (FB > 1)
  if (FB > 1) {
      int altDirEsq = no->getDir()->getEsq() ? no->getDir()->getEsq()->getAltura() : 0;
      int altDirDir = no->getDir()->getDir() ? no->getDir()->getDir()->getAltura() : 0;
      int FBDir = altDirDir - altDirEsq;

      if (FBDir >= 0) {
          return rotacaoEsq(no);      // Rotação simples à esquerda
      } else {
          return rotacaoDuploEsq(no); // Rotação dupla (Dir no filho + Esq no pivô)
      }
  }

  return no;
}

node* arvoreAVL::rotacaoEsq(node* no) {
    node* novaRaiz = no->getDir();
    no->setDir(novaRaiz->getEsq());
    novaRaiz->setEsq(no);

    no->setAltura();
    novaRaiz->setAltura();

    return novaRaiz;
}

node* arvoreAVL::rotacaoDir(node* no) {
  node* novaRaiz = no->getEsq();
  no->setEsq(novaRaiz->getDir());
  novaRaiz->setDir(no);

  no->setAltura();
  novaRaiz->setAltura();

  return novaRaiz;
}

node* arvoreAVL::rotacaoDuploEsq(node* no) {
  no->setDir(rotacaoDir(no->getDir()));
  return rotacaoEsq(no);
}

node* arvoreAVL::rotacaoDuploDir(node* no) {
  no->setEsq(rotacaoEsq(no->getEsq()));
  return rotacaoDir(no);
}

arvoreAVL::~arvoreAVL() {
  destruirAux(raiz);
}

void arvoreAVL::destruirAux(node* no) {
  if (no != NULL) {
    destruirAux(no->getEsq());
    destruirAux(no->getDir());
    delete no;
  }
}

bool arvoreAVL::buscar(int chave, long long &comparacoes) {
  node* atual = raiz;
  while (atual != NULL) {
    comparacoes++;
    if (chave < atual->getChave()) {
      atual = atual->getEsq();
    } else {
      if (chave > atual->getChave()) {
        atual = atual->getDir();
      } else {
        return true; // Encontrou
      }
    }
  }
  return false; // Não existe na árvore
}

arvoreAVL* ConstruirAVL(const vector<int>& entrada, long long &comparacoes) {
  arvoreAVL* arvore = new arvoreAVL();
  comparacoes = 0;

  for (int valor : entrada) {
    arvore->inserir(valor, comparacoes);
  }

  return arvore;
}

long long ConsultarAVL(arvoreAVL* arvore, const vector<int>& entrada) {
  long long comparacoes = 0;
  if (arvore == NULL) return comparacoes;

  for (int valor : entrada) {
    arvore->buscar(valor, comparacoes);
  }

  return comparacoes;
}

#endif