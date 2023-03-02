#include <stdio.h>
#include <stdlib.h>
typedef struct tipono *apont;

typedef struct tipono {
    int reg;
    apont esq, dir;
} tipono;

void cria(apont *p) {
    *p = NULL;
}

void insere(int chave, apont *p) {//função responsavel por inserir o valor na lista
    if (*p == NULL) {
        *p = (apont) malloc(sizeof (tipono));
        (*p)->reg = chave;
        (*p)->esq = NULL;
        (*p)->dir = NULL;
        return;
    }
    if (chave < (*p)->reg) {
        insere(chave, &(*p)->esq);
        return;
    }
    if (chave > (*p)->reg) {
        insere(chave, &(*p)->dir);
    } else {
        printf("ERRO: Registro já existe na arvore\n");
    }
}

void pesquisa(apont *p, int x) {//pesquisa o numero na lista, encontra em qual nivel ele está e interage com o usuario mostrando os dados 
    int cont = 0;
    apont aux = *p;
    while (aux != NULL && aux->reg != x) {
        if (aux->reg < x) {
            aux = aux->dir;
        } else {
            if (aux->reg > x) {
                aux = aux->esq;
            }
        }
        cont++;
    }
    if (aux == NULL) {
        printf("\nValor não encontrado\n");
    } else {
        printf("\nValor encontrado: %d, ele está no nivel: %d da arvore", aux->reg, cont);
        return;
    }

}

void Antecessor(apont q, apont *r) {// encontra o antecessor, usado no retira
    if ((*r)->dir != NULL) {
        Antecessor(q, &(*r)->dir);
        return;
    }
    q->reg = (*r)->reg;
    q = *r;
    *r = (*r)->esq;
    free(q);
}

void retira(apont *p, int x) {// retira um valor da arvore
    apont aux;
    if (*p == NULL) {
        printf("ERRO: Registro não está na arvore\n");
        return;
    }
    if (x < (*p)->reg) {
        retira(&(*p)->esq, x);
        return;
    }
    if (x > (*p)->reg) {
        retira(&(*p)->dir, x);
        return;
    }
    if ((*p)->dir == NULL) {
        aux = *p;
        *p = (*p)->esq;
        free(aux);
        return;
    }
    if ((*p)->esq != NULL) {
        Antecessor(*p, &(*p)->esq);
        return;
        free(aux);
    }
}

void imprimeOrd(apont p) {//imprime de forma ordenada
    if (p == NULL) {
        return;
    }
    imprimeOrd(p->esq);
    printf("%d, ", p->reg);
    imprimeOrd(p->dir);
}

void imprimepre(apont p) {//imprime sempre de acorco com o nivel da arvore, quanto mais procimo da raiz, mais a frente ele será printado
    if (p == NULL) {
        return;
    }
    printf("%d, ", p->reg);
    imprimeOrd(p->esq);
    imprimeOrd(p->dir);
}

void imprimepos(apont p) {
    if (p == NULL) {
        return;
    }
    imprimeOrd(p->esq);
    imprimeOrd(p->dir);
    printf("%d, ", p->reg);
}

void contaNo(apont p, int *cont) {//conta a quantidade de nos da arvore
    if (p == NULL) {
        return;
    }
    *cont = *cont + 1;
    contaNo(p->esq, cont);
    contaNo(p->dir, cont);
}

void imprimeEstremo(apont p) {//imprime o maior e menor valor da arvore! não e recursivo
    apont aux = p;
    if (p->esq != NULL) {
        while (aux->esq != NULL) {
            aux = aux->esq;
        }
        printf("O valor menor é:%d ", aux->reg);
    }else{
        printf("O valor menor é:%d ", aux->reg);
    }
    aux = p;
    if (p->dir != NULL) {
        while (aux->dir != NULL) {
            aux = aux->dir;
        }
        printf("O  valor maior é: %d", aux->reg);
    }else{
         printf("O  valor maior é: %d", aux->reg);
    }
}

void imprimeFolha(apont p) {//imprime todos os valores folhas(que dua direita e esquerda são NULL)
    if (p == NULL) {
        return;
    }
    if (p->dir == NULL && p->esq == NULL) {
        printf("%d, ", p->reg);
    }
    imprimeFolha(p->esq);
    imprimeFolha(p->dir);
}

int main(int argc, char** argv) {
    apont no;
    cria(&no);
    int op = 0;

    while (op != 10) {
        printf("\n=================MENU========================");
        printf("\n1-insere\n 2-Pesquisa em que nivel se encontra o nó\n 3-retira elemento\n 4-imprime em ordem\n 5-imprime em pré-ordem\n 6-imprime em pós-ordem\n 7-Numero de Nó da arvore\n"
                " 8-Mostrar menor e maior valor armazenado na árvore\n 9-Imprime os nós Folhas\n 10-EXIT\n");
        printf("=============================================\n");
        printf("Digite o que vc deseja fazer:\n");
        scanf("%d", &op);
        if (op < 11) {
            switch (op){
                case 1:
                    printf("Digite o valor: ");
                    int valor;
                    scanf("%d", &valor);
                    insere(valor, &no);
                    printf("\nconteudo da arvore:");
                    imprimeOrd(no);
                    break;

                case 2:
                    int valor2;
                    printf("\nDigite qual numero vc deseja buscar: ");
                    scanf("%d", &valor2);
                    pesquisa(&no, valor2);
                    break;
                case 3:
                    int valor3;
                    printf("\nDigite qual numero vc deseja retirar: ");
                    scanf("%d", &valor3);
                    retira(&no, valor3);
                    printf("\nconteudo da arvore:");
                    imprimeOrd(no);
                    break;
                case 4:
                        printf("\nImprimindo em ordem: ");
                        imprimeOrd(no);
                        break;
                case 5:
                        printf("\nImprimindo em  pré-ordem: ");
                        imprimepre(no);
                        break;
                case 6:
                        printf("\nImprimindo em pós-ordem: ");
                        imprimepos(no);
                        break;
                case 7:
                        int cont = 0;
                        contaNo(no, &cont);
                        printf("\nA arvore tem %d nós", cont);
                        break;
                case 8:
                        imprimeEstremo(no);
                        break;
                case 9:
                        printf("As folhas das arvores são: ");
                        imprimeFolha(no);
                        break;
            }
        }else{
            printf("Valor não listado!\n");
        }
    }
    return (EXIT_SUCCESS);
}