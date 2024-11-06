#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>  

#include "biblioteca.h"


void gerarArquivos(int tam) {
    FILE *ordenado, *invertido, *randomico;
    int x;
    char nomeArquivo[255];

    sprintf(nomeArquivo, "Ordenado%07d.txt", tam);  
    ordenado = fopen(nomeArquivo, "w");
    for (x = 1; x <= tam; x++) {
        fprintf(ordenado, "%d\n", x);
    }
    fclose(ordenado);
  
    sprintf(nomeArquivo, "Invertido%07d.txt", tam);
    invertido = fopen(nomeArquivo, "w");
    for (x = tam; x >= 1; x--) {
        fprintf(invertido, "%d\n", x);
    }
    fclose(invertido);

    sprintf(nomeArquivo, "Randomico%07d.txt", tam);
    randomico = fopen(nomeArquivo, "w");
    for (x = 1; x <= tam; x++) {
        fprintf(randomico, "%d\n", rand() % tam + 1); 
    }
    fclose(randomico);

    printf("Arquivos para %d registros gerados com sucesso!\n", tam);
}

int* lerArquivo(char *nomeArquivo, int tam) {
    FILE *file;
    int *arr = (int *)malloc(tam * sizeof(int));
    int i = 0;

    file = fopen(nomeArquivo, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo %s.\n", nomeArquivo);
        return NULL;
    }

    while (fscanf(file, "%d", &arr[i]) != EOF && i < tam) {
        i++;
    }

    fclose(file);
    return arr;
}


void medirTempoOrdenacao(int *arr, int tam, void (*sortFunc)(int*, int), const char* algoritmo, const char* tipoArquivo) {
    clock_t inicio, fim;
    double tempoGasto;

    inicio = clock();
    sortFunc(arr, tam);
    fim = clock();

    tempoGasto = ((double) (fim - inicio)) / CLOCKS_PER_SEC;

    printf("%s em arquivo %s com %d registros levou %.5f segundos.\n", algoritmo, tipoArquivo, tam, tempoGasto);
}


void quickSortAdaptado(int *arr, int tam) {
    quickSort(arr, 0, tam - 1);
}

void mergeSortAdaptado(int *arr, int tam) {
    mergeSort(arr, 0, tam - 1);
}

void ordenarArquivo(char *tipoArquivo, int tam, int algoritmo) {
    char nomeArquivo[255];
    sprintf(nomeArquivo, "%s%07d.txt", tipoArquivo, tam);

    int *arr = lerArquivo(nomeArquivo, tam);
    if (arr == NULL) return;

    if (algoritmo == 1) {
        printf("Ordenando com Bubble Sort...\n");
        medirTempoOrdenacao(arr, tam, bubbleSort, "Bubble Sort", tipoArquivo);
    } else if (algoritmo == 2) {
        printf("Ordenando com Insertion Sort...\n");
        medirTempoOrdenacao(arr, tam, insertionSort, "Insertion Sort", tipoArquivo);
    } else if (algoritmo == 3){
        printf("Ordenando com Selection Sort...\n");
        medirTempoOrdenacao(arr, tam, selectionSort, "Selection Sort", tipoArquivo);

    } else if (algoritmo == 4){
        printf("Ordenando com Shell Sort...\n");
        medirTempoOrdenacao(arr, tam, shellSort, "Shell Sort", tipoArquivo);

    } else if(algoritmo == 5){
        printf("Ordenando com Quick Sort...\n");
        medirTempoOrdenacao(arr, tam,quickSortAdaptado, "Quick Sort", tipoArquivo);

    } else if(algoritmo == 6){
        printf("Ordenando com Merge Sort...\n");
        medirTempoOrdenacao(arr, tam, mergeSortAdaptado, "Merge Sort", tipoArquivo);
    }
    else if(algoritmo == 7){
        printf("Ordenando com Heap Sort...\n");
        medirTempoOrdenacao(arr, tam, heapSort, "Heap Sort", tipoArquivo);
    }
    else if(algoritmo == 8){
        printf("Ordenando com Radi Sort...\n");
        medirTempoOrdenacao(arr, tam, radixSort, "Radix Sort", tipoArquivo);
    }

    free(arr);
}

void gerarArquivoTeste() {
    FILE *arquivoTeste;
    char nomeArquivo[255];
    int x;

    // Gera um arquivo com 50 números aleatórios
    sprintf(nomeArquivo, "Teste50.txt");
    arquivoTeste = fopen(nomeArquivo, "w");
    for (x = 1; x <= 50; x++) {
        fprintf(arquivoTeste, "%d\n", rand() % 51);  
    }
    fclose(arquivoTeste);

    printf("Arquivo de teste 'Teste50.txt' com 50 registros gerado!\n");
}

void testarOrdenacao(void (*algoritmo)(int[], int), const char* nomeAlgoritmo) {
    FILE *arquivoTeste;
    int arr[50];
    int i = 0;
    char nomeArquivo[] = "Teste50.txt";
    
    // Abre o arquivo gerado e carrega os números no array
    arquivoTeste = fopen(nomeArquivo, "r");
    if (arquivoTeste == NULL) {
        printf("Erro ao abrir o arquivo de teste.\n");
        return;
    }

    while (fscanf(arquivoTeste, "%d", &arr[i]) != EOF && i < 50) {
        i++;
    }
    fclose(arquivoTeste);

    // Exibe o array original
    printf("\nArray original (50 registros):\n");
    for (i = 0; i < 50; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Aplica o algoritmo de ordenação
    algoritmo(arr, 50);

    // Exibe o array ordenado
    printf("\nArray ordenado usando %s:\n", nomeAlgoritmo);
    for (i = 0; i < 50; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void carregarArquivoTeste(int arr[], int tamanho) {
    // Exemplo de leitura de arquivo para carregar os 50 registros
    FILE *file = fopen("Teste50.txt", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de teste.\n");
        return;
    }
    
    for (int i = 0; i < tamanho; i++) {
        fscanf(file, "%d", &arr[i]); // Lê os valores do arquivo e coloca no array
    }
    
    fclose(file);
}

void imprimirArray(int arr[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void testarOrdenacaoMergeQuick(void (*funcaoOrdenacao)(int[], int, int), const char* nomeAlgoritmo) {
    int arr[50];
    carregarArquivoTeste(arr, 50);  // Assumindo que você já tem essa função para carregar o arquivo de teste

    printf("\nTestando %s com 50 registros:\n", nomeAlgoritmo);
    
    printf("Array original:\n");
    imprimirArray(arr, 50);  

    // Executa o algoritmo de ordenação fornecido
    funcaoOrdenacao(arr, 0, 49);

    // Assumindo que você já tenha uma função para imprimir o array
    imprimirArray(arr, 50);  
}



int main() {
    int opcao;

    do {
        printf("\n=== Menu ===\n");
        printf("1. Gerar arquivo\n");
        printf("2. Bubble Sort\n");
        printf("3. Insertion Sort\n");
        printf("4. Selection Sort\n");
        printf("5. Shell Sort\n");
        printf("6. Quick Sort\n");
        printf("7. Merge Sort\n");
        printf("8. Heap Sort\n");
        printf("9. Radix Sort\n");
        printf("10.Testar Algoritmos\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 0:
                printf("Saindo...\n");
                break;

            case 1: {  //Gerar Arquivo
                int op;
                do {
                    printf("\n=== Opcoes de Arquivo ===\n");
                    printf("1. Gerar arquivo com 500 mil registros\n");
                    printf("2. Gerar arquivo com 750 mil registros\n");
                    printf("3. Gerar arquivo com 1 milhao de registros\n");
                    printf("4. Gerar arquivo com 5 milhoes de registros\n");
                    printf("5. Gerar arquivo com 10 milhoes de registros\n");
                    printf("10. Gerar arquivo de teste com 50 registros\n");
                    printf("0. Voltar\n");
                    printf("Escolha uma opcao: ");
                    scanf("%d", &op);

                    switch (op) {
                        case 0:
                            break;
                        case 1:
                            gerarArquivos(500000);
                            break;
                        case 2:
                            gerarArquivos(750000);
                            break;
                        case 3:
                            gerarArquivos(1000000);
                            break;
                        case 4:
                            gerarArquivos(5000000);
                            break;
                        case 5:
                            gerarArquivos(10000000);
                            break;
                        case 10:
                            gerarArquivoTeste();
                            break;
                        default:
                            printf("Opcao invalida! Tente novamente.\n");
                    }
                } while (op != 0);
                break;
            }

            case 2: { //Bubble Sort
                int op;
                do {
                    printf("\n=== Bubble Sort ===\n");
                    printf("1. Ordenar arquivo Ordenado\n");
                    printf("2. Ordenar arquivo Aleatório\n");
                    printf("3. Ordenar arquivo Invertido\n");
                    printf("0. Voltar\n");
                    printf("Escolha uma opcao: ");
                    scanf("%d", &op);

                    switch (op) {
                        case 0:
                            break;
                        case 1:
                            ordenarArquivo("Ordenado", 500000, 1);
                            ordenarArquivo("Ordenado", 750000, 1);
                            ordenarArquivo("Ordenado", 1000000, 1);
                            
                            break;
                        case 2:
                            ordenarArquivo("Randomico", 500000, 1);
                            ordenarArquivo("Randomico", 750000, 1);
                            ordenarArquivo("Randomico", 1000000, 1);
                            break;
                        case 3:
                            ordenarArquivo("Invertido", 500000, 1);
                            ordenarArquivo("Invertido", 750000, 1);
                            ordenarArquivo("Invertido", 1000000, 1);
                            break;
                        default:
                            printf("Opcao invalida! Tente novamente.\n");
                    }
                } while (op != 0);
                break;
            }

            case 3: { //Insertion Sort
                int op;
                do {
                    printf("\n=== Insertion Sort ===\n");
                    printf("1. Ordenar arquivo Ordenado\n");
                    printf("2. Ordenar arquivo Aleatorio\n");
                    printf("3. Ordenar arquivo Invertido\n");
                    printf("0. Voltar\n");
                    printf("Escolha uma opcao: ");
                    scanf("%d", &op);

                    switch (op) {
                        case 0:
                            break;
                        case 1:
                            ordenarArquivo("Ordenado", 500000, 2);
                            ordenarArquivo("Ordenado", 750000, 2);
                            ordenarArquivo("Ordenado", 1000000, 2);
                            ordenarArquivo("Ordenado", 5000000, 2);
                            break;
                        case 2:
                            ordenarArquivo("Randomico", 500000, 2);
                            ordenarArquivo("Randomico", 750000, 2);
                            ordenarArquivo("Randomico", 1000000, 2);
                            ordenarArquivo("Randomico", 5000000, 2);
                            break;
                        case 3:
                            ordenarArquivo("Invertido", 500000, 2);
                            ordenarArquivo("Invertido", 750000, 2);
                            ordenarArquivo("Invertido", 1000000, 2);
                            ordenarArquivo("Invertido", 5000000, 2);
                            break;
                        default:
                            printf("Opcao invalida! Tente novamente.\n");
                    }
                } while (op != 0);
                break;
            }

            case 4:{ //Selection Sort
                int op;
                do {
                    printf("\n=== Selection Sort ===\n");
                    printf("1. Ordenar arquivo Ordenado\n");
                    printf("2. Ordenar arquivo Aleatorio\n");
                    printf("3. Ordenar arquivo Invertido\n");
                    printf("0. Voltar\n");
                    printf("Escolha uma opcao: ");
                    scanf("%d", &op);

                    switch (op) {
                        case 0:
                            break;
                        case 1:
                            // ordenarArquivo("Ordenado", 500000, 3);
                            // ordenarArquivo("Ordenado", 750000, 3);
                            // ordenarArquivo("Ordenado", 1000000, 3);
                            ordenarArquivo("Ordenado", 5000000, 3);
                            break;
                        case 2:
                            // ordenarArquivo("Randomico", 500000, 3);
                            // ordenarArquivo("Randomico", 750000, 3);
                            // ordenarArquivo("Randomico", 1000000, 3);
                            ordenarArquivo("Randomico", 5000000, 3);
                            break;
                        case 3:
                            // ordenarArquivo("Invertido", 500000, 3);
                            // ordenarArquivo("Invertido", 750000, 3);
                            // ordenarArquivo("Invertido", 1000000, 3);
                            ordenarArquivo("Invertido", 5000000, 3);
                            break;
                        default:
                            printf("Opcao invalida! Tente novamente.\n");
                    }
                } while (op != 0);
                break;
            }

            case 5:{ //Shell Sort
                int op;
                do {
                    printf("\n=== Selection Sort ===\n");
                    printf("1. Ordenar arquivo Ordenado\n");
                    printf("2. Ordenar arquivo Aleatorio\n");
                    printf("3. Ordenar arquivo Invertido\n");
                    printf("0. Voltar\n");
                    printf("Escolha uma opcao: ");
                    scanf("%d", &op);

                    switch (op) {
                        case 0:
                            break;
                        case 1:
                            ordenarArquivo("Ordenado", 500000, 4);
                            ordenarArquivo("Ordenado", 750000, 4);
                            ordenarArquivo("Ordenado", 1000000, 4);
                            ordenarArquivo("Ordenado", 5000000, 4);
                            break;
                        case 2:
                            ordenarArquivo("Randomico", 500000, 4);
                            ordenarArquivo("Randomico", 750000, 4);
                            ordenarArquivo("Randomico", 1000000, 4);
                            ordenarArquivo("Randomico", 5000000, 4);
                            break;
                        case 3:
                            ordenarArquivo("Invertido", 500000, 4);
                            ordenarArquivo("Invertido", 750000, 4);
                            ordenarArquivo("Invertido", 1000000, 4);
                            ordenarArquivo("Invertido", 5000000, 4);
                            break;
                        default:
                            printf("Opcao invalida! Tente novamente.\n");
                    }
                } while (op != 0);
                break;
            }

            case 6: { //Quick Sort
                int op;
                do {
                    printf("\n=== Quick Sort ===\n");
                    printf("1. Ordenar arquivo Ordenado\n");
                    printf("2. Ordenar arquivo Aleatorio\n");
                    printf("3. Ordenar arquivo Invertido\n");
                    printf("0. Voltar\n");
                    printf("Escolha uma opcao: ");
                    scanf("%d", &op);

                    switch (op) {
                        case 0:
                            break;
                        case 1:
                          
                            ordenarArquivo("Ordenado", 5000000, 5);
                            //ordenarArquivo("Ordenado", 10000000, 5);
                            break;
                        case 2:
                            
                            ordenarArquivo("Randomico", 5000000, 5);
                           // ordenarArquivo("Randomico", 10000000, 5);
                            break;
                        case 3:
                            
                           ordenarArquivo("Invertido", 5000000, 5);
                           // ordenarArquivo("Invertido", 10000000, 5);
                            break;
                        default:
                            printf("Opcao invalida! Tente novamente.\n");
                    }
                } while (op != 0);
                break;
            }

            case 7:{   //Merge Sort
                int op;
                do {
                    printf("\n=== Merge Sort ===\n");
                    printf("1. Ordenar arquivo Ordenado\n");
                    printf("2. Ordenar arquivo Aleatorio\n");
                    printf("3. Ordenar arquivo Invertido\n");
                    printf("0. Voltar\n");
                    printf("Escolha uma opcao: ");
                    scanf("%d", &op);

                    switch (op) {
                        case 0:
                            break;
                        case 1:
                           
                            ordenarArquivo("Ordenado", 5000000, 6);
                           // ordenarArquivo("Ordenado", 10000000, 6);
                            break;
                        case 2:
                            
                            ordenarArquivo("Randomico", 5000000, 6);
                           // ordenarArquivo("Randomico", 10000000, 6);
                            break;
                        case 3:
                            
                            ordenarArquivo("Invertido", 5000000, 6);
                          //  ordenarArquivo("Invertido", 10000000, 6);
                            break;
                        default:
                            printf("Opcao invalida! Tente novamente.\n");
                    }
                } while (op != 0);
                break;
            }
    
            case 8:{   //Heap Sort
                int op;
                do {
                    printf("\n=== Heap Sort ===\n");
                    printf("1. Ordenar arquivo Ordenado\n");
                    printf("2. Ordenar arquivo Aleatorio\n");
                    printf("3. Ordenar arquivo Invertido\n");
                    printf("0. Voltar\n");
                    printf("Escolha uma opcao: ");
                    scanf("%d", &op);

                    switch (op) {
                        case 0:
                            break;
                        case 1:
                           
                            ordenarArquivo("Ordenado", 5000000, 7);
                           // ordenarArquivo("Ordenado", 10000000, 6);
                            break;
                        case 2:
                            
                            ordenarArquivo("Randomico", 5000000, 7);
                           // ordenarArquivo("Randomico", 10000000, 6);
                            break;
                        case 3:
                            
                            ordenarArquivo("Invertido", 5000000, 7);
                          //  ordenarArquivo("Invertido", 10000000, 6);
                            break;
                        default:
                            printf("Opcao invalida! Tente novamente.\n");
                    }
                } while (op != 0);
                break;
            }
    
            case 9:{   //Radiz Sort
                int op;
                do {
                    printf("\n=== Radix Sort ===\n");
                    printf("1. Ordenar arquivo Ordenado\n");
                    printf("2. Ordenar arquivo Aleatorio\n");
                    printf("3. Ordenar arquivo Invertido\n");
                    printf("0. Voltar\n");
                    printf("Escolha uma opcao: ");
                    scanf("%d", &op);

                    switch (op) {
                        case 0:
                            break;
                        case 1:
                           
                            ordenarArquivo("Ordenado", 5000000, 8);
                           // ordenarArquivo("Ordenado", 10000000, 6);
                            break;
                        case 2:
                            
                            ordenarArquivo("Randomico", 5000000, 8);
                           // ordenarArquivo("Randomico", 10000000, 6);
                            break;
                        case 3:
                            
                            ordenarArquivo("Invertido", 5000000, 8);
                          //  ordenarArquivo("Invertido", 10000000, 6);
                            break;
                        default:
                            printf("Opcao invalida! Tente novamente.\n");
                    }
                } while (op != 0);
                break;
            }
    
            case 10:{ //Testar Algoritmos
              //gerarArquivoTeste();  
    
                int escolhaAlgoritmo;
                printf("\n=== Testar Algoritmos de Ordenacao com 50 registros ===\n");
                printf("1. Bubble Sort\n");
                printf("2. Insertion Sort\n");
                printf("3. Selection Sort\n");
                printf("4. Shell Sort\n");
                printf("5. Quick Sort\n");
                printf("6. Merge Sort\n");
                printf("7. Heap Sort\n");
                printf("8. Radix Sort\n");
                printf("Escolha um algoritmo: ");
                scanf("%d", &escolhaAlgoritmo);

                switch (escolhaAlgoritmo) {
                    case 1:
                        testarOrdenacao(bubbleSort, "Bubble Sort");
                        break;
                    case 2:
                        testarOrdenacao(insertionSort, "Insertion Sort");
                        break;
                    case 3:
                        testarOrdenacao(selectionSort, "Selection Sort");
                        break;
                    case 4:
                        testarOrdenacao(shellSort, "Shell Sort");
                        break;
                    case 5:
                        testarOrdenacaoMergeQuick(quickSort, "Quick Sort");
                        break;
                    case 6:
                        testarOrdenacaoMergeQuick(mergeSort, "Merge Sort");
                        break;
                    case 7:
                        testarOrdenacao(heapSort, "Heap Sort");
                        break;
                    case 8:
                        testarOrdenacao(radixSort, "Radix Sort");
                        break;

                    default:
                        printf("Opcao invalida! Tente novamente.\n");
                }
                break;
            }
            
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}
