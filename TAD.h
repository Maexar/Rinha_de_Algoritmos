#ifndef TAD_H
#define TAD_H

void bubbleSort(int arr[], int n);

void insertionSort(int arr[], int n);

void selectionSort(int arr[], int n);

void shellSort(int arr[], int n);

void quickSort(int arr[], int low, int high);
void swap(int* a, int* b);
int medianOfThree(int arr[], int low, int high);
int partition(int arr[], int low, int high);

void mergeSort(int arr[], int l, int r);
void merge(int arr[], int l, int m, int r);

void heapify(int arr[], int n, int i);
void heapSort(int arr[], int n);

int getMax(int arr[], int n);
void countingSort(int arr[], int n, int exp);
void radixSort(int arr[], int n);


#endif