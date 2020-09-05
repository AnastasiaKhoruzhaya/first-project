//Ввести массивы А и В. В массив С перенести элементы массива А с нечетным значением и элементы масси-ва В с четным значением. 
//Массив С отсортировать по возрастанию, используя алгоритмы сортировок: сорти-ровка слиянием, сортировка Хоара.
#include <iostream>

using namespace std;

int quickSort(int*, int);
void InsOrd(int array[], int sm, int em, int e);
int* Merge(int array[], int sm, int cm, int em);
int* SortMerge(int array[], int lm, int sm = 0);

int main() {
    int* A = new int[1000];  //выделение динамической памяти в куче для трех масcивов
    int* B = new int[1000];
    int* C = new int[1000];
    int sizeA, sizeB, k = 0;

    cout << "Enter size of first array : "; cin >> sizeA;
    cout << "\nFirst array\n";
    for (int i = 0; i < sizeA; i++) {
        A[i] = rand() % 10 + 1;
        cout << A[i] << " ";
    }

    cout << "\n\nEnter size of second array : "; cin >> sizeB;
    cout << "\nSecond array\n";
    for (int i = 0; i < sizeB; i++) {
        B[i] = rand() % 10 + 1;
        cout << B[i] << " ";
    }

    for (int i = 0, j = 0; i < sizeA, j < sizeB; i++, j++) {
        if (A[i] % 2 != 0) {
            C[k] = A[i];
            k++;
        }
        if (B[j] % 2 == 0) {
            C[k] = B[j];
            k++;
        }
    }

    cout << "\n\nNew array\n";
    for (int i = 0; i < k; i++) {
        cout << C[i] << " ";
    }

    int choice, sm = 0;
    cout << "\n\nSelect type of sort : \n 1 - Quick Sorting\n 2 - Sorting Merge\n";//1-хоара,2-слияния
    cout << "\nOur choice : "; cin >> choice;
    switch (choice) {
    case 1:
        quickSort(C, k);
        break;
    case 2:
        SortMerge(C, k);
    default:
        break;
    }

    cout << "\n\nSorted new array\n\n";
    for (int i = 0; i < k; i++) {
        cout << C[i] << " ";
    }
    return 0;
}

int quickSort(int* array, int sizeArray) {
    int mediana = array[sizeArray >> 1];         //побитово получаем середину массива
    int i = 0, j = sizeArray - 1, temporary;
    do {
        while (array[i] < mediana) {//если меньше медианы то добавляем к счётчику
            i++;
        }
        while (array[j] > mediana) {//если больше медианы то отнимаем от счётчика
            j--;
        }
        if (i <= j) {//исходя из значения счётчика перекидываем в правую или левую сторну от медианы
            temporary = array[i];
            array[i] = array[j];
            array[j] = temporary;
            i++;
            j--;
        }
    } while (i <= j);

    if (j > 0) {
        quickSort(array, j);//ркурсивно используем эту же сортировку
    }
    if (sizeArray > i) {
        quickSort(array + 1, sizeArray - i);
        return 1;
    }
}

void InsOrd(int array[], int sm, int em, int e) {//функция перекидовки элементов в одну часть
    int i = sm;
    while (i <= em && array[i] < e) {
        if (i - 1 >= sm) {
            array[i - 1] = array[i];//закидывает по одному
        }
        i++;
    }
    array[i - 1] = e;
}

int* Merge(int array[], int sm, int cm, int em) {//функция слияния
    int buf;
    for (int i = 0; i <= sm; i++) {
        if (array[i] > array[cm + 1]) {//если больше того который был в середине
            buf = array[i];//то записывает в буфер
            array[i] = array[cm + 1];//на его место ставит элемент следующий за тем который в середине
            InsOrd(array, cm + 1, em, buf);//по одному закидывает элементы в одну часть
        }
    }
    return array;
}

int* SortMerge(int array[], int lm, int sm) {//функция сортировки слияния
    if (lm > 1) {
        SortMerge(array, lm / 2, sm);//сортирует 1 часть
        SortMerge(array, lm - lm / 2, sm + lm / 2);//сортирует вторую часть
        Merge(array, sm, sm + lm / 2 - 1, sm + lm - 1);//происходит слияние
    }
    return array;
}
