# Trabalho - Pilha de Chamadas de Emergencia (versao com lista encadeada, malloc, free)

 Aqui a grande diferença é que em vez de usar um vetor fixo, cada chamada vira um "no"
    alocado na hora com malloc. O topo da pilha agora e um
    PONTEIRO pro primeiro no da lista, nao e mais um indice.

   Empilhar (registrar) = malloc de um no novo, e ele aponta pro
    no que era o topo antes. O no novo vira o topo.

   Desempilhar (atender) = guardo o no do topo numa variavel
    auxiliar, ando o topo pro proximo no, e so DEPOIS disso eu
    dou free no no antigo (se der free antes de andar o topo, eu
    perco o ponteiro pro resto da lista).

   Pilha vazia agora e topo == NULL (nao existe mais topo == -1).
    Tambem nao tem mais "pilha cheia" com MAX, porque a lista
    cresce conforme malloc vai alocando memoria.
# Motivo da escolha

Escolhi esse tema principalmente por ser algo bem direto e estar mais proximos do meu
conhecimento em pilhas, todo conceito de lifo que ja estou familiarizado.

#FEEDBACK PARA PROFESSOR

professor so queria informar q estou ciente dos prazos apertados e a questão de não ter aula e tal, 
contudo um trabalho dessa magnitude é inviável limitar apenas 10 minutos por video, acaba gerando 
um corte no conteudo e todo potencial que o trabalho propõe, tivemos q cortar diversas partes do video
para se limitar aos 10 minutos, tendo q priorizar algumas coisas e não podendo explicar todas as funções 
do codigo e mostrar no terminal. Fora isso, gostei bastante da proposta, principalmente pela divisao dos
grupos e os 3 temas pois trouxe uma facilidade na hora de decidir funções de cada um.
