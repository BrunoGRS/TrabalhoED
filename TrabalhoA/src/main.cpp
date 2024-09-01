#include <stdio.h>
#include <math.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

class No{
    
    public:
        int data;
        No *esquerda, *direita;
        
    No(int data){
        this->data = data;
        esquerda = direita = NULL;
    }
};

class Arvore{
    
    public:
        No *root;
        
    Arvore(){
        this->root = root;
    }
};

int altura(No *root) {
    if (root == NULL)
        return 0;
    
    return max(altura(root->esquerda), altura(root->direita)) + 1;
}

int getcol(int h) {
    if (h == 1)
        return 1;
        
    return getcol(h - 1) + getcol(h - 1) + 1;
}

void imprimirNo(int **M, No *root, int col, int row, int altura) {
    if (root == NULL)
        return;
    
    M[row][col] = root->data;
    imprimirNo(M, root->esquerda, col - pow(2, altura -2), row + 1, altura -1);
    imprimirNo(M, root->direita, col + pow(2, altura -2), row + 1, altura -1);
};

void imprimirArvore(Arvore arvore) {
    int h = altura(arvore.root);
    int col = getcol(h);
    int **M = new int*[h];
    
    for (int i = 0; i < h; i++) {
        M[i] = new int[col];
    }
    
    imprimirNo(M, arvore.root, col / 2, 0, h);
    
    for (int i =0; i < h; i++) {
        for (int j = 0; j < col; j++) {
            if (M[i][j] == 0) {
                printf(" ");
            } else {
                printf("%d", M[i][j], " ");
            }
        }
        
        printf("\n");
    }
};

void inserirNoEsquerda(No *no, int valor){
        if(!valor){
            return;
        }
        if(no->esquerda == NULL){
            no->esquerda = new No(valor);
        }else{
            inserirNoEsquerda(no->esquerda, valor);
        }
};

void inserirNoDireta(No *no, int valor){
        if(!valor){
            return;
        }
        if(no->direita == NULL){
            no->direita = new No(valor);
        }else{
            inserirNoDireta(no->direita, valor);
        }
};

No* inserirNo(No* no, int valor){
     
        if(no == NULL){
            no = new No(valor);
            no->data = valor;
            no->esquerda = no->direita = NULL;
            }else if(valor < no->data){
                no->esquerda = inserirNo(no->esquerda, valor);
            }else{
                no->direita = inserirNo(no->direita, valor);
            }
            return no;
        
        while (getchar() != '\n');
}

No* buscaBinaria(No* no, int valor){
    if(no == NULL){
        return NULL;
    }else if(valor < no->data){
        return buscaBinaria(no->esquerda, valor);
    }else{ if(valor > no->data){
        return buscaBinaria(no->direita, valor);
    }else{
        return no;
        }   
    }
}

int main()
{
   int opcao;
    Arvore arv;

    while (1) {
        // Exibe o menu
        printf("1. Inserir Nó\n");
        scanf("%d",&opcao);

        switch(opcao) {
            case 1:
                int valor;
                
                printf("\n");
                printf("Digite o valor do No: ");
                    while (scanf("%d", valor) != 1) {
                        printf("Entrada inválida. Por favor, insira um número inteiro: ");
                        while (getchar() != '\n');
                            }

                inserirNo(arv.root, valor);
                break;
            case 3:
                imprimirArvore(arv);
                break;
            case 4:
                imprimirArvore(arv);
                break;
            case 5:
                imprimirArvore(arv);
                break;
            case 6:
                imprimirArvore(arv);
                break;
            case 7:
                imprimirArvore(arv);
                break;
            case 8:
                imprimirArvore(arv);
                break;
            case 0:
                printf("Saindo...");
                return 0;
            default:
                printf("Opção Inválida. Tente novamente!");
                break;
        }
    }

    return 0;
}