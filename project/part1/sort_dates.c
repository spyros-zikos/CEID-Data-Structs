#include "basic_functions.h"

// sort the dates so that the search algorithms can use sorted data


// created to sort dates from small to big
double** insertionsort(double** arr, int column){

	//create a duplicate array
	double** arr2 = (double**)malloc(sizeof(double*)*ROWS);
	
	for (int i=0; i<ROWS; i++) {
	    arr2[i] = (double*)malloc(sizeof(double)*COLUMNS);
		for (int j=0; j<COLUMNS; j++)
			arr2[i][j] = arr[i][j];
	}
	
	int i, j;
	double* key = (double*)malloc(sizeof(double)*COLUMNS);

	for (j=0; j<ROWS-1; j++){ //iterate through each row
		//store the next row in variable key
		for(int k=0; k<COLUMNS; k++){
			key[k] = arr2[j+1][k];
		}
		//while the row's element is less than the previous element move them to the right by 1
		for (i=j; i>=0 && key[column] < arr2[i][column]; i--){    
			for (int o=0; o<COLUMNS; o++){
				double temp = arr2[i+1][o];
				arr2[i+1][o] = arr2[i][o];
				arr2[i][o] = temp;
			}
		}
		//make the last element to be moved equal to the key's
		for(int k=0; k<COLUMNS; k++){
			arr2[i+1][k] = key[k];
		}
	}

	return arr2; 
}



int main(){
    //<--- INSERTIONSORT --->

	//import the csv file into a 2d string array
    char*** arr_imp = csv_import_init();
	//convert the 2d string array into a 2d double array
	double** arr_double = converter2double(arr_imp);
 
	double **arr_ins = insertionsort(arr_double, 0);

	//convert the sorted double 2d array into a 2d string array
	char*** farr_ins = converter2str(arr_ins);
	//export the 2d string array into a csv file
	export_csv(farr_ins, "./ocean_s.csv");

	//<--- END INSERTIONSORT --->


    return 0;
}
