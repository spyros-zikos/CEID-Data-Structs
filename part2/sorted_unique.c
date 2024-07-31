#include "basic_functions.h"
#define ROWS_S 1405


int main(){

    char*** arr_imp = csv_import_s();
    double** arr_double = converter2double_init(arr_imp);

    double** arr_un = (double**)malloc(sizeof(double*)*ROWS_S);
    for (int i = 0; i < ROWS_S; i++)
        arr_un[i] = (double*)malloc(sizeof(double)*COLUMNS);

    double last = -1;
    int k = 0;

    for (int i = 0; i < ROWS_S; i++) {
        
        if (arr_double[i][0] != last) {
            for (int j = 0; j < COLUMNS; j++) {
                arr_un[k][j] = arr_double[i][j];
            }
            last = arr_un[k][0];
            k++;
        }
    }
	printf("Unique entries: %d",k);
    // you can use k for the count of the columns
	// of the csv file with unique entries

    char*** farr = converter2str_u(arr_un);
    export_csv2(farr, "./unique.csv");

    return 0;
}

