/*               partI erotima 1                */
#include "basic_functions.h"



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
		//while the row's temperature is less than the previous temperatures move them to the right by 1
		for (i=j; i>=0 && key[column] < arr2[i][column]; i--){    
			for (int o=0; o<COLUMNS; o++){
				double temp = arr2[i+1][o];
				arr2[i+1][o] = arr2[i][o];
				arr2[i][o] = temp;
			}
		}
		//make the last temperature to be moved equal to the key's
		for(int k=0; k<COLUMNS; k++){
			arr2[i+1][k] = key[k];
		}
	}

	return arr2; 
}



void quicksort(double** arr, int first, int last){

	int left, right, pivot;
	double* temp = (double*)malloc(sizeof(double)*COLUMNS);
	
	if(first < last){
		//the choosen pivot temperature is the first index of the array
		pivot = first;
		//left and right represent the left and left index pointers
		left = first;
		right = last;

		while(left<right){
			//when the value at the index indicated by left is bigger 
			//than the value at pivot stop increasing left
			while(arr[left][1] <= arr[pivot][1]&&left<last) left++;
			//when the value at the index indicated by right is smaller 
			//than the value at pivot stop decreasing right
			while(arr[right][1] > arr[pivot][1]) right--;
			//if left<right swap the rows with index left and right
			if(left<right){
				for(int k=0; k<COLUMNS; k++){
					temp[k]=arr[left][k];
					arr[left][k]=arr[right][k];
					arr[right][k]=temp[k];
				}
			}
		}

		//swap the element with index pivot and the element with index right 
		//so the pivot is its correct final index in the array
		for (int k=0; k<COLUMNS; k++){
			temp[k]=arr[pivot][k];
			arr[pivot][k]=arr[right][k];
			arr[right][k]=temp[k];
		}

		//call the algorithm recursivly to the two halfs
		quicksort(arr,first,right-1);
		quicksort(arr,right+1,last);
	}
}




int main(){
    //<--- INSERTIONSORT --->

	//import the csv file into a 2d string array
    char*** arr_imp = csv_import_s();
	//convert the 2d string array into a 2d double array
	double** arr_double = converter2double(arr_imp);
 
	//time the performance of the algorithm
    clock_t t_i = clock();
	double **arr_ins = insertionsort(arr_double, 1);
	sleep(1);
    t_i = clock() - t_i;
    double time_taken_i = ((double)t_i)/CLOCKS_PER_SEC-1;
	printf("Insertionsort took %f seconds to execute.", time_taken_i);
	


	//sort the dates with the same temperature in a trivial way
	date_sorting(arr_ins, 1);
	//convert the sorted double 2d array into a 2d string array
	char*** farr_ins = converter2str(arr_ins);
	//export the 2d string array into a csv file
	export_csv(farr_ins, "./ins.csv");

	//<--- END INSERTIONSORT --->



	//<--- QUICKSORT --->
	//make a duplicate array to feed to quicksort
	double** arr_quick = (double**)malloc(sizeof(double*)*(ROWS + 2));
	for (int i=0; i<ROWS+2; i++) {
	    arr_quick[i] = (double*)malloc(sizeof(double)*COLUMNS);
	}

	for(int i=0; i<ROWS; i++){
		for (int j=0; j<COLUMNS; j++){
			arr_quick[i+1][j] = arr_double[i][j];
			//add 2 extra rows which will be inf and -inf (?) (eixame stili mail) (to eidame apto biblio)
			arr_quick[0][j] = -1;
			arr_quick[ROWS+1][j] = 1000;
		}
	}


	//time performance
    clock_t t_q = clock();
    quicksort(arr_quick, 0, ROWS+1);
	sleep(1);
	t_q = clock() - t_q;
    double time_taken_q = ((double)t_q)/CLOCKS_PER_SEC-1;
	printf("\nQuicksort took %f seconds to execute.", time_taken_q);
	


	//make duplicate array without the 2 extra rows
	double** arr_quick2 = (double**)malloc(sizeof(double*)*ROWS);
	for (int i=0; i<ROWS; i++) {
	    arr_quick2[i] = (double*)malloc(sizeof(double)*COLUMNS);
		for (int j=0; j<COLUMNS; j++){
			arr_quick2[i][j] = arr_quick[i+1][j];
		}
	}

	//sort the dates with the same temperature in a trivial way
	date_sorting(arr_quick2, 1);

	//convert the sorted double 2d array into a 2d string array
  	char*** farr_quick = converter2str(arr_quick2);
	//export the 2d string array into a csv file
	export_csv(farr_quick, "./quick.csv");
	//<--- END QUICKSORT --->

    return 0;
}
