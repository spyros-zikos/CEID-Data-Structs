/*               partI erotima 4              */
#include "basic_functions.h"



int BIS(int* arr, int x){
    int left = 0;
    int right = ROWS -1;
    int size = right - left + 1;
    int next = ceil(size*(x - arr[left])/(arr[right]-arr[left])) + 1; 
               
    // if x is out of range return -1 (not found)
    if ((x > arr[right]) || (x < arr[left])) return -1;
    
    // if next is bigger than right make it equal to right
    if (next > right)
        next = right;

    //while x is not found
    int i;
    while (x != arr[next]) {
        i = 1;
        // compute size
        size = right - left + 1;
        // if size is 3 or less do linear search
        if (size <= 3){
            for (int j=left; j<right+1; j++)
                if (arr[j] == x)
                    return j;
            return -1;
        }
        // find right and left so that x is in between using i to increase the step by 1
        if (x >= arr[next]) {
            while (x > arr[next + i*(int)sqrt(size) - 1])
                i++;
            right = next + i*(int)sqrt(size);
            left = next + (i-1)*(int)sqrt(size);
        } else if (x < arr[next]) {
            while (x < arr[next - i*(int)sqrt(size) + 1])
                i++;
            right = next - (i-1)*(int)sqrt(size);
            left = next - i*(int)sqrt(size);
        }
        // compute next
        next = left + ceil((right - left + 1) * (x - arr[left]) / (arr[right] - arr[left])) - 1;
        if (next > right)
            next = right;
    }           
    // if found return it else return -1 (not found)
    if (x == arr[next])
        return next;
    else
        return -1;

}





int BISalt(int* arr, int x){
    int left = 0;
    int right = ROWS -1;
    int size = right - left + 1;
    int next = ceil(size*(x - arr[left])/(arr[right]-arr[left])) + 1;

    if ((x > arr[right]) || (x < arr[left])) return -1;

    if (next > right)
        next = right;

    int i;
    while (x != arr[next]){
        i = 1;
        size = right - left + 1;
        if (size <= 3){
            for (int j=left; j<right+1; j++)
                if (arr[j] == x)
                    return j;
            return -1;
        }
        // find right and left so that x is in between using i to multiply the step by 2
        if (x >= arr[next]){
            while (x > arr[next + i*(int)sqrt(size) - 1])
                i = 2*i;
            right = next + i*(int)sqrt(size);
            left = next + (i-1)*(int)sqrt(size);
        } else if (x < arr[next]) {
            while (x < arr[next - i*(int)sqrt(size) + 1])
                i = 2*i;
            right = next - (i-1)*(int)sqrt(size);
            left = next - i*(int)sqrt(size);
        }

        next = left + ceil((right - left + 1) * (x - arr[left]) / (arr[right] - arr[left])) - 1;
        if (next > right)
            next = right;
    }

    if (x == arr[next])
        return next;
    else
        return -1;
}




// same comments as previous main functions
int main() {
    // <---  BIS  --->
    char*** arr_imp = csv_import_s();
    double** arr_double = converter2double(arr_imp);


    int* arr_bin = (int*)malloc(sizeof(int)*ROWS);
    for(int i=0; i<ROWS; i++)
        arr_bin[i] = (int)arr_double[i][0];


    int date = get_date();


    int result;

    clock_t t_b = clock();
    result = BIS(arr_bin, date);
    sleep(1);
    t_b = clock() - t_b;
    double time_taken_b = ((double)t_b)/CLOCKS_PER_SEC-1;
    

    if (result == -1) 
        printf("NOT FOUND BY BIS!\n");
    else {
        printf("BIS\n    Position: %d\n    Temperature: %.3f\n    Phosphate: %.3f\n", result, arr_double[result][1], arr_double[result][2]);
        printf("BIS took %f seconds to execute.\n", time_taken_b);
    }
    // <---  END BIS  --->
    // <---  BIS ALTERNATIVE  --->

    clock_t t_a = clock();
    result = BISalt(arr_bin, date);
    sleep(1);
    t_a = clock() - t_a;
    double time_taken_a = ((double)t_a)/CLOCKS_PER_SEC-1;
    
	

    if (result == -1) 
        printf("\nNOT FOUND BY BISalt!");
    else{
        printf("\nBIS alteration\n    Position: %d\n    Temperature: %.3f\n    Phosphate: %.3f", result, arr_double[result][1], arr_double[result][2]);
        printf("\nBIS alteration took %f seconds to execute.\n", time_taken_a);
    }
    // <---  END BIS ALTERNATIVE  --->
}
