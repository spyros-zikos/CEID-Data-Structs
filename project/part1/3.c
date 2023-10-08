/*               partI erotima 3               */
#include "basic_functions.h"



int binarySearch(int* arr, int key){
    int right = ROWS-1;
    int left = 0;
    // choose next as the median of left and right
    int next = (int)((left+right)/2);
   
   // choose one half of the array
    while ((key!=arr[next]) && (left<right)) {
        if(key<=arr[next])
            right = next-1;
        else 
            left = next+1;
        next = (int)((left+right)/2);
    }
    //check if the element is in index 'next' of the array (check if the element is found)
    if (key==arr[next])
        return next;
    else return -1;
}



int interpolationSearch(int* arr, int key){
    int low = 0; 
    int high = ROWS - 1;
    int next;

    // while key is between arr[high] and arr[low] find a smaller area of the array to search
    while ((arr[high] >= key) && (key > arr[low])) {
        next = low + ((key-arr[low])/(arr[high]-arr[low]))*(high-low); 
        if (key > arr[next])
            low = next+1;
        else if (key < arr[next])
            high = next-1;
        else
            low = next;
    }
    // if the key is found return its index else return -1
    if (key == arr[low])
        return low;
    else
        return -1;
}



// same comments as previous main functions will not be included
int main(){
    //<---  BS  --->
    char*** arr_imp = csv_import_s();
    double** arr_double = converter2double(arr_imp);


    int* arr_bin = (int*)malloc(sizeof(int)*ROWS);
    for(int i=0; i<ROWS; i++)
        arr_bin[i] = (int)arr_double[i][0];

    // get the date from the user
    int date = get_date();

    int result;

    clock_t t_b = clock();
    result = binarySearch(arr_bin, date);
    sleep(1);
    t_b = clock() - t_b;
    double time_taken_b = ((double)t_b)/CLOCKS_PER_SEC-1;
    

    if (result == -1) 
        printf("NOT FOUND!");
    else {
        printf("Binary search\n    Position: %d\n    Temperature: %.3f\n    Phosphate: %.3f\n", result, arr_double[result][1], arr_double[result][2]);
        printf("Binary Search took %f seconds to execute.\n", time_taken_b);
        }
    //<---  END BS  --->
    //<---  INTERPOLATION SEARCH --->

    clock_t t_i = clock();
    result = interpolationSearch(arr_bin, date);
    sleep(1);
    t_i = clock() - t_i;
    double time_taken_i = ((double)t_i)/CLOCKS_PER_SEC-1;
    
	

    if (result == -1) 
        printf("NOT FOUND!");
    else{
        printf("\nInterpolation search\n    Position: %d\n    Temperature: %.3f\n    Phosphate: %.3f", result, arr_double[result][1], arr_double[result][2]);
        printf("\nInterpolation Search took %f seconds to execute.\n", time_taken_i);
    }
    //<---  END INTERPOLATION SEARCH --->
}
