/* 
 * File:   main.c
 * Author: christian
 *
 * Created on 11. Januar 2010, 09:26
 */

#include <stdio.h>
#include <stdlib.h>

void gibArrayAus(int arr[],int l);
void schreibQuadrate(int arr[], int l);
int vergleicheArrays(int arr1[], int arr2[], int elements);
void verdoppele(int arr1[], int arr2[], int elements);
void ausgeben(int *zahl);
void aendereIntPtr(int i, int *ptr);

/*
 * 
 */
int main() {

    int Array1[100] = { 0 };
    int Array2[100] = { -2 };
    int Array3[100] = { 4 };

    schreibQuadrate(Array2,50);
    schreibQuadrate(Array1,100);
    gibArrayAus(Array1,100);
    gibArrayAus(Array2,100);
    verdoppele(Array2,Array3,100);
    gibArrayAus(Array3,100);
    if(vergleicheArrays(Array1,Array2,100)){
	printf("Array1 und Array2 sind ungleich!\n");
    } else {
	printf("Array1 und Array2 sind gleich!\n");
    }

    int x = 100;
    int *y = &x;
    aendereIntPtr(14,y);
    printf("x = %i; y = %i",x,*y);

    return (EXIT_SUCCESS);
}

void aendereIntPtr(int i, int *ptr){
    *ptr = i;
}


void verdoppele(int arr1[], int arr2[], int elements){
    int i;
    for(i = 0; i < elements; ++i){
	arr2[i] = 2*arr1[i];
    }
}


int vergleicheArrays(int arr1[], int arr2[], int elements){
    int i;
    for(i = 0; i < elements; ++i){
	if(arr1[i] != arr2[i]){
	    return 1;
	}
    }
    return 0;
}


void schreibQuadrate(int arr[], int l){
    int i;
    for(i = 0; i < l; i++){
	arr[i] = (i+1)*(i+1);
    }
}

void ausgeben(int *zahl){
    printf("Wert: %i\n",*zahl);
}

void gibArrayAus(int arr[],int l){
    int i;
    for(i = 0; i < l; i++){
	int *ptr = &arr[i];
	ausgeben(ptr);

    }
}