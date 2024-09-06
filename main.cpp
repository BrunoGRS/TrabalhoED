#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int max(int a, int b)
{
  return (a > b) ? a : b;
}

class No
{
public:
  int data;
  No *esquerda, *direita;

  No(int data)
  {
    this->data = data;
    esquerda = direita = NULL;
  }
};

class Arvore
{
public:
  No *root;

  Arvore()
  {
    this->root = NULL;
  }
};

int altura(No *root)
{
  if (root == NULL)
    return 0;

  return max(altura(root->esquerda), altura(root->direita)) + 1;
}

int getcol(int h)
{
  if (h == 1)
    return 1;

  return getcol(h - 1) + getcol(h - 1) + 1;
}

void imprimirNo(int **M, No *root, int col, int row, int altura)
{
  if (root == NULL)
    return;

  M[row][col] = root->data;
  imprimirNo(M, root->esquerda, col - pow(2, altura - 2), row + 1, altura - 1);
  imprimirNo(M, root->direita, col + pow(2, altura - 2), row + 1, altura - 1);
};

void imprimirArvore(Arvore arvore)
{
  int h = altura(arvore.root);
  int col = getcol(h);
  int **M = new int *[h];

  for (int i = 0; i < h; i++)
  {
    M[i] = new int[col];
    for (int j = 0; j < col; j++)
    {
      M[i][j] = 0;
    }
  }

  imprimirNo(M, arvore.root, col / 2, 0, h);

  for (int i = 0; i < h; i++)
  {
    for (int j = 0; j < col; j++)
    {
      if (M[i][j] == 0)
      {
        printf(" ");
      }
      else
      {
        printf("%d", M[i][j]);
      }
    }

    printf("\n");
  }
};

No *inserirNo(No *no, int valor)
{
  if (no == NULL)
  {
    no = new No(valor);
  }
  else if (valor < no->data)
  {
    no->esquerda = inserirNo(no->esquerda, valor);
  }
  else
  {
    no->direita = inserirNo(no->direita, valor);
  }
  return no;
}

void exibirPreOrdem(No *no)
{
  if (no == NULL)
    return;

  printf("%d ", no->data);
  exibirPreOrdem(no->esquerda);
  exibirPreOrdem(no->direita);
}

void exibirOrdem(No *no)
{
  if (no == NULL)
    return;

  exibirOrdem(no->esquerda);
  printf("%d ", no->data);
  exibirOrdem(no->direita);
}

void exibirPosOrdem(No *no)
{
  if (no == NULL)
    return;

  exibirPosOrdem(no->esquerda);
  exibirPosOrdem(no->direita);
  printf("%d ", no->data);
}

No *buscaBinaria(No *no, int valor)
{
  if (no == NULL)
    return NULL;

  if (valor < no->data)
    return buscaBinaria(no->esquerda, valor);
  else if (valor > no->data)
    return buscaBinaria(no->direita, valor);

  return no;
}

// Função para buscar um valor na árvore e exibir informações sobre o nó
void buscarNo(No *root, int valor, No *pai = NULL)
{
  // Se o nó atual for nulo, o valor não foi encontrado
  if (root == NULL)
  {
    printf("Valor %d não encontrado na árvore.\n", valor);
    return;
  }

  // Se encontramos o valor
  if (root->data == valor)
  {
    // Exibe o valor encontrado
    printf("Valor %d encontrado.\n", valor);

    // Se o nó é a raiz
    if (pai == NULL)
    {
      printf("Valor solicitado é o nó raiz.\n");
    }
    else
    {
      // Exibe quem é o nó pai
      printf("O valor %d tem como pai o valor %d.\n", valor, pai->data);
    }

    // Exibe os nós filhos, se existirem
    if (root->esquerda != NULL)
    {
      printf("Filho à esquerda: %d\n", root->esquerda->data);
    }
    else
    {
      printf("Não há filho à esquerda.\n");
    }

    if (root->direita != NULL)
    {
      printf("Filho à direita: %d\n", root->direita->data);
    }
    else
    {
      printf("Não há filho à direita.\n");
    }

    return;
  }

  // Se o valor é menor que o nó atual, vá para a subárvore à esquerda
  if (valor < root->data)
  {
    buscarNo(root->esquerda, valor, root);
  }
  // Se o valor é maior que o nó atual, vá para a subárvore à direita
  else
  {
    buscarNo(root->direita, valor, root);
  }
}

// Função auxiliar para encontrar o menor valor de uma subárvore (sucessor in-order)
No *minValueNode(No *node)
{
  No *current = node;

  // Encontra o nó mais à esquerda, que será o menor valor
  while (current && current->esquerda != NULL)
    current = current->esquerda;

  return current;
}

No *removerNo(No *root, int valor)
{
  // Se a árvore está vazia
  if (root == NULL)
    return root;

  // Se o valor a ser removido for menor que o valor da raiz, ele estará à esquerda
  if (valor < root->data)
  {
    root->esquerda = removerNo(root->esquerda, valor);
  }
  // Se o valor a ser removido for maior que o valor da raiz, ele estará à direita
  else if (valor > root->data)
  {
    root->direita = removerNo(root->direita, valor);
  }
  // Se o valor for o mesmo que o valor da raiz, esse é o nó a ser removido
  else
  {
    // Caso 1: Nó com um ou nenhum filho
    if (root->esquerda == NULL)
    {
      No *temp = root->direita;
      delete root;
      return temp;
    }
    else if (root->direita == NULL)
    {
      No *temp = root->esquerda;
      delete root;
      return temp;
    }

    // Caso 2: Nó com dois filhos
    // Pegue o sucessor in-order (menor valor na subárvore direita)
    No *temp = minValueNode(root->direita);

    // Copie o valor do sucessor in-order para o nó atual
    root->data = temp->data;

    // Remova o sucessor in-order
    root->direita = removerNo(root->direita, temp->data);
  }

  return root;
}

int contarNos(No *root)
{
  if (root == NULL)
    return 0;

  // Retorna 1 (o nó atual) + o total de nós da subárvore esquerda + o total de nós da subárvore direita
  return 1 + contarNos(root->esquerda) + contarNos(root->direita);
}

int contarFolhas(No *root)
{
  // Se a árvore estiver vazia, retorna 0
  if (root == NULL)
    return 0;

  // Se o nó é uma folha (não tem filhos)
  if (root->esquerda == NULL && root->direita == NULL)
    return 1;

  // Senão, conta as folhas das subárvores esquerda e direita
  return contarFolhas(root->esquerda) + contarFolhas(root->direita);
}

int contarSubArvores(No *root)
{
  // Se o nó for nulo, não é uma subárvore
  if (root == NULL)
    return 0;

  // Se o nó não tem filhos, não conta como subárvore com filhos
  if (root->esquerda == NULL && root->direita == NULL)
    return 0;

  // Contabiliza a subárvore atual se o nó tiver filhos
  return 1 + contarSubArvores(root->esquerda) + contarSubArvores(root->direita);
}

void limparConsole()
{
#if defined(_WIN32)
  system("cls");
#else
  system("clear");
#endif
}

int main()
{
  int opcao;
  Arvore arv;

  while (true)
  {
    limparConsole(); // Limpa o console antes de exibir o menu

    // Exibe o menu
    printf("\n");
    printf("1. Inserir No\n");
    printf("2. Exibir árvore\n");
    printf("3. Buscar No\n");
    printf("4. Exibir em Pré-ordem\n");
    printf("5. Exibir em Ordem\n");
    printf("6. Exibir em Pós-ordem\n");
    printf("7. Remover No\n");
    printf("8. Altura da árvore\n");
    printf("9. Total de nós da árvore\n");
    printf("10. Total de folhas da árvore\n");
    printf("11. Total de sub-árvore\n");
    printf("12. Buscar No detalhado\n");
    printf("0. Sair\n");
    printf("-> ");
    scanf("%d", &opcao);

    limparConsole(); // Limpa o console antes de executar a tarefa

    switch (opcao)
    {
    case 1:
    {
      int valor;
      printf("Digite o valor do No: ");
      while (scanf("%d", &valor) != 1)
      {
        printf("Entrada inválida. Por favor, insira um número inteiro: ");
        while (getchar() != '\n')
          ; // Limpa o buffer
      }
      arv.root = inserirNo(arv.root, valor);
      break;
    }
    case 2:
    {
      imprimirArvore(arv);
      break;
    }
    case 3:
    {
      int valor;
      printf("Digite o valor do No: ");
      while (scanf("%d", &valor) != 1)
      {
        printf("Entrada inválida. Por favor, insira um número inteiro: ");
        while (getchar() != '\n')
          ; // Limpa o buffer de entrada
      }
      No *vl = buscaBinaria(arv.root, valor);

      if (vl != NULL)
      {
        printf("O valor foi encontrado!\n");
      }
      else
      {
        printf("Valor não encontrado.\n");
      }
      break;
    }
    case 4:
    {
      exibirPreOrdem(arv.root);
      printf("\n");
      break;
    }
    case 5:
    {
      exibirOrdem(arv.root);
      printf("\n");
      break;
    }
    case 6:
    {
      exibirPosOrdem(arv.root);
      printf("\n");
      break;
    }
    case 7:
    {
      int valor;
      printf("Digite o valor do No para remover: ");
      while (scanf("%d", &valor) != 1)
      {
        printf("Entrada inválida. Por favor, insira um número inteiro: ");
        while (getchar() != '\n')
          ; // Limpa o buffer
      }
      arv.root = removerNo(arv.root, valor);
      break;
    }
    case 8:
    {
      int alturaArvore = altura(arv.root);
      printf("A Arvore tem a altura: %d\n", alturaArvore);
      break;
    }
    case 9:
    {
      int totalnos = contarNos(arv.root);
      printf("O total de nós é de: %d\n", totalnos);
      break;
    }
    case 10:
    {
      int totalfolhas = contarFolhas(arv.root);
      printf("O total de folhas é de: %d\n", totalfolhas);
      break;
    }
    case 11:
    {
      int totalsubarvores = contarSubArvores(arv.root);
      printf("O total de Sub-árvores é de: %d\n", totalsubarvores);
      break;
    }
    case 12:
    {

      int valor;
      printf("Digite o valor do No: ");
      while (scanf("%d", &valor) != 1)
      {
        printf("Entrada inválida. Por favor, insira um número inteiro: ");
        while (getchar() != '\n')
          ; // Limpa o buffer de entrada
      }
      buscarNo(arv.root, valor);

      break;
    }
    case 0:
      printf("Saindo...\n");
      return 0;
    default:
      printf("Opcao Invalida. Tente novamente!\n");
      break;
    }

    if (opcao < 13 && opcao >= 0)
    {
      printf("\nPressione Enter para continuar...");
      getchar();
      getchar();
    }
  }

  return 0;
}
