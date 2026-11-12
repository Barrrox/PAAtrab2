# Todo

- Implementar Estururas de Dados
    - [] Arvore Rubro Negra
    - [] Arovre AVL
- Implementar Funções
    - [] ConstruirAVL(entradaConstr);
        - Recebe vetor de inteiros entrada
        - Retorna o pair [arvoreAVL, compConstrucaoAVL] em que arvoreAVL é um ponteiro para a arvore e compConstrucaoAVL é um inteiro com o número de comparações feitas
    - [] ConstruirArvoreRN(entradaConstr)
        - Recebe vetor de inteiros de entrada
        - Retorna o pair [arvoreRN, compConstrucaoRN] em que arvoreRN é um ponteiro para a arvore e compConstrucaoRN é um inteiro com o número de comparações feitas
    - [] ConsultarAVL(arvoreAVL, entradaConsul)
        - Recebe o ponteiro para a arvoreAVL e o vetor de inteiros da entrada.
        - Retorna o número de comparações feitas.
    - [] ConsultarArvoreRN(arvoreRN, entradaConsul)
        - Recebe o ponteiro para a arvoreRN e o vetor de inteiros da entrada.
        - Retorna o número de comparações feitas.
- Main
    - [X] Execução dos métodos
    - [X] Calculo de tempo
    - [X] Salvar resultados em csv
    - [] Testar
- Arquivo .hpp

Observações:
- Para as consultas, lembrar que podem ter elementos na entrada que não estão na árvore e deve haver lógica para lidar com isso.
- Lembrar de usar as mesmas ténicas e otimizações nas duas árvores, quando for possível.