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
                printf("%d", M[i][j]);
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

        if(no == 0 or no == NULL){
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

void exibirPreOrdem(No *no){
    if(no == NULL){
        return;
    }else{
        printf("%d",no->data);
        printf(", ");
        exibirPreOrdem(no->esquerda);
        exibirPreOrdem(no->direita);
    }
}

void exibirOrdem(No *no){
    if(no == NULL){
        return;
    }else{
        exibirOrdem(no->esquerda);
        printf("%d",no->data);
        printf(", ");
        exibirOrdem(no->direita);
    }
}

void exibirPosOrdem(No *no){
    if(no == NULL){
        return;
    }else{
        exibirPosOrdem(no->esquerda);
        exibirPosOrdem(no->direita);
        printf("%d",no->data);
        printf(", ");
    }
}

No* buscaBinaria(No* no, int valor){
    if(no == 0 or no == NULL){
        return NULL;
    }else if(valor < no->data){
        return buscaBinaria(no->esquerda, valor);
    }else{ if(valor > no->data){
        return buscaBinaria(no->direita, valor);
        }  
    }

    return no;
}

int main()
{
    int opcao;
    Arvore arv;

    while (true) {
        // Exibe o menu
        printf("\n");
        printf("1. Inserir No\n");
        printf("2. Imprimir No\n");
        printf("3. Buscar No\n");
        printf("4. Exibir em Pre Ordem\n");
        printf("5. Exibir em Ordem\n");
        printf("6. Exibir em Pos Ordem\n");
        printf("7. Remover No\n");
        printf("8. Altura da Arvore\n");
        printf("9. Total de Nos da Arvore\n");
        printf("10. Total de filhas da Arvore\n");
        printf("11. Total de Sub-Arvore\n");
        printf("0. Sair\n");
        printf("->");
        scanf("%d", &opcao);
        printf("\n");

        switch(opcao) {
            case 1:
            {
                int valor;
                printf("Digite o valor do No: ");
                while (scanf("%d", &valor) != 1) {
                    printf("Entrada inválida. Por favor, insira um número inteiro: ");
                    while (getchar() != '\n');
                }
                arv.root = inserirNo(arv.root, valor);
                break;
            }
            case 2:
            {
                imprimirArvore(arv);
            }
            case 3:
            {
                int valor;
                printf("Digite o valor do No: ");
                while (scanf("%d", &valor) != 1) {  // Corrigido o scanf
                    printf("Entrada inválida. Por favor, insira um número inteiro: ");
                    while (getchar() != '\n'); // Limpa o buffer de entrada
                }
                No* vl = buscaBinaria(arv.root, valor);

                if(vl != NULL or vl != 0){
                    printf("O valor foi encontrado!\n");
                break;
                }
            }
            case 4:
            {
                exibirPreOrdem(arv.root);
                break;
            }
            case 5:
            {
                exibirOrdem(arv.root);
                break;
            }
            case 6:
            {
                exibirPosOrdem(arv.root);
                break;
            }
            case 7:
            case 8:
            {
                int alturaArvore = altura(arv.root);
                printf("A Arvore tem a altura: %d", alturaArvore);
                break;
            }
            case 0:
                printf("Saindo...\n");
                return 0;
            default:
                printf("Opcao Invalida. Tente novamente!\n");
                break;
        }
    }

    return 0;
}
