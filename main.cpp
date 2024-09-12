// 50, 67, 15, 52, 70 10, 16, 8, 76
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

void buscarNo(No *root, int valor, No *pai = NULL)
{
  if (root == NULL)
  {
    printf("Valor %d não encontrado na árvore.\n", valor);
    return;
  }

  if (root->data == valor)
  {
    printf("Valor %d encontrado.\n", valor);

    if (pai == NULL)
    {
      printf("Valor solicitado é o nó raiz.\n");
    }
    else
    {
      printf("O valor %d tem como pai o valor %d.\n", valor, pai->data);
    }

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

  if (valor < root->data)
  {
    buscarNo(root->esquerda, valor, root);
  }
  else
  {
    buscarNo(root->direita, valor, root);
  }
}

No *minValueNode(No *node)
{
  No *current = node;

  while (current && current->esquerda != NULL)
    current = current->esquerda;

  return current;
}

No *removerNo(No *root, int valor)
{
  if (root == NULL)
    return root;

  if (valor < root->data)
  {
    root->esquerda = removerNo(root->esquerda, valor);
  }
  else if (valor > root->data)
  {
    root->direita = removerNo(root->direita, valor);
  }
  else
  {
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

    No *temp = minValueNode(root->direita);

    root->data = temp->data;

    root->direita = removerNo(root->direita, temp->data);
  }

  return root;
}

int contarNos(No *root)
{
  if (root == NULL)
    return 0;

  return 1 + contarNos(root->esquerda) + contarNos(root->direita);
}

int contarFolhas(No *root)
{
  if (root == NULL)
    return 0;

  if (root->esquerda == NULL && root->direita == NULL)
    return 1;

  return contarFolhas(root->esquerda) + contarFolhas(root->direita);
}

int contarSubArvores(No *root)
{
  if (root == NULL)
    return 0;

  if (root->esquerda == NULL && root->direita == NULL)
    return 0;

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
    limparConsole();
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

    limparConsole();
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
          ;
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
          ;
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
      int alturaArvore = altura(arv.root) - 1;
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
      int totalsubarvores = contarSubArvores(arv.root) - 1;
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
