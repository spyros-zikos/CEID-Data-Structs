/*               partI erotima 2                */
#include "basic_functions.h"

#define RANGE 350 


void heapify(double** arr, int length, int parent) {
    int big = parent;
    int left = 2 * parent + 1;
    int right = 2 * parent + 2;


    // Let the variable big be the index of the biggest value among root, left child and right child
    if (left < length && arr[left][2] > arr[big][2])
        big = left;
    if (right < length && arr[right][2] > arr[big][2])
        big = right;

    // if the element at index parent is not the biggest swap its row with the the 
    //row that the biggest element belongs to
    if (big != parent) {
        for (int k=0; k<COLUMNS; k++){
            double temp = arr[parent][k];
            arr[parent][k] = arr[big][k];
            arr[big][k] = temp;
        }
    // call heapify recursivly downwards
    heapify(arr, length, big);
    }
}


void heapSort(double** arr, int length) {
    // Construct maximum heap
    for (int i = length / 2 - 1; i >= 0; i--)
        heapify(arr, length, i);

    // Heap sort
    // remove the max from the heap and push it to the start 
    // of the sorted array which is at the end of the heap 
    // swaping it with the last element from the heap
    for (int i = length - 1; i >= 0; i--) {
        for (int o=0; o<COLUMNS; o++){
            double temp = arr[0][o];
            arr[0][o] = arr[i][o];
            arr[i][o] = temp;
        }
        // Heapify root to fix the heap structure
        heapify(arr, i, 0);
    }
}
  


 
double**  countingSort(double** arr){

    // duplicate array
    double** arr2 = (double**)malloc(sizeof(double*)*ROWS);
	
    // make the phosphate values without floating part so that 
    //they can be cast to int without loss of info
	for (int i=0; i<ROWS; i++) {
	    arr2[i] = (double*)malloc(sizeof(double)*COLUMNS);
			arr2[i][2] = arr[i][2] * 100;
	}
    //copy the rest values to the array
    for(int i=0; i<ROWS; i++){
        for(int j=0; j<COLUMNS; j++){
            if(j!=2)
                arr2[i][j] = arr[i][j];
        }
    }
	
    // make the final array
    double** arr_b = (double**)malloc(sizeof(double*)*ROWS);
    for(int i=0; i<ROWS; i++){
        arr_b[i] = (double*)malloc(sizeof(double)*COLUMNS);
        for(int j=0; j<COLUMNS; j++){
            arr_b[i][j] = arr[i][j];
        }  
    }

    // make the counting array
    int* arr_c = (int*)malloc(sizeof(int)*RANGE); 

    // initialize the counting array with 0's
    for(int i=0; i<RANGE; i++) 
        arr_c[i] = 0; 

    // count the number of appearances of each phosphate value
    for(int i=0; i<ROWS; i++)
        arr_c[(int)arr2[i][2]]++ ;


    // store the number of the appearances of less or equal phosphate values
    for(int i=1; i<RANGE; i++)
        arr_c[i] += arr_c[i-1];


    //constructing the final sorted array
    for(int i=ROWS-1; i>=0; i--){
        for(int j=0; j<COLUMNS; j++)
            arr_b[arr_c[(int)arr2[i][2]]-1][j] = arr2[i][j];
            arr_c[(int)arr2[i][2]]--;
    }

    // restore the phosphate values to their original ones
    for(int i=0; i<ROWS; i++)
        arr_b[i][2] /= 100;
    
    return arr_b;
}
 
 


int main() {
    //<--- HEAPSORT --->
    char*** arr_imp = csv_import_s();
    double** arr_double = converter2double(arr_imp);

    double** arr_heap = (double**)malloc(sizeof(double*)*ROWS);
    for(int i=0; i<ROWS; i++){
        arr_heap[i] = (double*)malloc(sizeof(double)*COLUMNS);
        for(int j=0; j<COLUMNS; j++)
            arr_heap[i][j] = arr_double[i][j];
    }


    clock_t t_h = clock();
    heapSort(arr_heap, ROWS);
    sleep(1);
    t_h = clock() - t_h;
    double time_taken_h = ((double)t_h)/CLOCKS_PER_SEC-1;
    printf("Heapsort took %f seconds to execute.", time_taken_h);
	

    date_sorting(arr_heap, 2);
    char*** farr_heap = converter2str(arr_heap);
    export_csv(farr_heap, "./heap.csv");
    //<--- END HEAPSORT --->


    //<--- COUNTINGSORT --->
    clock_t t_c = clock();
    double** arr_count = countingSort(arr_double);
    sleep(1);
    t_c = clock() - t_c;
    double time_taken_c = ((double)t_c)/CLOCKS_PER_SEC-1;
    printf("\nCountingsort took %f seconds to execute.", time_taken_c);

  
    date_sorting(arr_count, 2);
    char*** farr_count = converter2str(arr_count);
    export_csv(farr_count, "./count.csv");
    //<--- END COUNTINGSORT --->
}










