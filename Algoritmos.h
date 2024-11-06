#ifndef ALGORITMOS_H
#define ALGORITMOS_H

#include "biblioteca.h"


void bubbleSort(int arr[], int n) {
    int i, j, temp;
    for (i = 0; i < n-1; i++) {
        for (j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

void insertionSort(int arr[], int n) {
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;

       
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void selectionSort(int arr[], int n) {
    int i, j, minIndex, temp;
    for (i = 0; i < n-1; i++) {
        minIndex = i;
        for (j = i+1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        temp = arr[minIndex];
        arr[minIndex] = arr[i];
        arr[i] = temp;
    }
}

void shellSort(int arr[], int n) {
    int i, j, gap, temp;
    for (gap = n/2; gap > 0; gap /= 2) {
        for (i = gap; i < n; i++) {
            temp = arr[i];
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}


void quickSort(int arr[], int low, int high) {
    if (low < high) {
        // Particiona o array
        int pi = partition(arr, low, high);

        // Ordena as subpartes
        quickSort(arr, low, pi - 1);  // Antes do pivô
        quickSort(arr, pi + 1, high); // Depois do pivô
    }
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
int medianOfThree(int arr[], int low, int high) {
    int mid = low + (high - low) / 2;

    if (arr[low] > arr[mid])
        swap(&arr[low], &arr[mid]);

    if (arr[low] > arr[high])
        swap(&arr[low], &arr[high]);

    if (arr[mid] > arr[high])
        swap(&arr[mid], &arr[high]);

    // O pivô é o elemento do meio após essas comparações
    return mid;
}

int partition(int arr[], int low, int high) {
    int pivotIndex = medianOfThree(arr, low, high);
    int pivot = arr[pivotIndex];

    // Mover o pivô para o fim
    swap(&arr[pivotIndex], &arr[high]);

    int i = (low - 1);

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[i + 1], &arr[high]);

    return (i + 1);
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        // Ordena a primeira e segunda metades
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        // Mescla as duas metades ordenadas
        merge(arr, l, m, r);
    }
}

void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    // Arrays temporários
    int* L = (int*)malloc(n1 * sizeof(int));
    int* R = (int*)malloc(n2 * sizeof(int));

    // Copia os dados para os arrays temporários L[] e R[]
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // Junta os arrays temporários de volta no arr[l..r]
    i = 0; // Índice inicial do primeiro subarray
    j = 0; // Índice inicial do segundo subarray
    k = l; // Índice inicial do subarray mesclado
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copia os elementos restantes de L[], se houver
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copia os elementos restantes de R[], se houver
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}


void heapify(int arr[], int n, int i) {
    int largest = i; // Inicializa o maior como o nó raiz
    int left = 2 * i + 1; // Filho à esquerda
    int right = 2 * i + 2; // Filho à direita

    // Se o filho à esquerda é maior que a raiz
    if (left < n && arr[left] > arr[largest])
        largest = left;

    // Se o filho à direita é maior que o maior até agora
    if (right < n && arr[right] > arr[largest])
        largest = right;

    // Se o maior não for a raiz
    if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        // Heapifica o sub-árvore afetada
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    // Constrói o heap (rearranja o array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Extrai os elementos do heap um a um
    for (int i = n - 1; i > 0; i--) {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        // Heapifica o elemento raiz para obter o maior elemento na posição 0
        heapify(arr, i, 0);
    }
}

int getMax(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];
    return max;
}

void countingSort(int arr[], int n, int exp) {
    int *output = (int *)malloc(n * sizeof(int)); // Aloca o array de saída dinamicamente
    int count[10] = {0};

    // Conta o número de ocorrências de cada dígito
    for (int i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;

    // Modifica count[i] para conter a posição de cada dígito no array de saída
    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    // Constroi o array de saída
    for (int i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    // Copia o array de saída para arr[], para que ele contenha os números ordenados por dígito atual
    for (int i = 0; i < n; i++)
        arr[i] = output[i];

    free(output); // Libera a memória alocada dinamicamente
}


void radixSort(int arr[], int n) {
    // Encontra o maior número para saber o número de dígitos
    int max = getMax(arr, n);

    // Executa counting sort para cada dígito
    for (int exp = 1; max / exp > 0; exp *= 10)
        countingSort(arr, n, exp);
}

#endif