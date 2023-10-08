#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>

#define ROWS 1405
#define COLUMNS 8
#define STR_LENGTH 11


// import the initial csv file to a 2d string array
char*** csv_import_init(){

	//create an empty 2d string dynamic array
    char*** arr2d = (char***)malloc(ROWS * sizeof(char**));
    for (int i = 0; i < ROWS; i++){
        arr2d[i] = (char**)malloc(COLUMNS * sizeof(char*));
		for (int j=0; j<COLUMNS; j++)
		   arr2d[i][j] = (char*)malloc(sizeof(char*)*STR_LENGTH);
	}

	// create a stream pointer to csv file
	FILE* fpoint = fopen("./ocean.csv", "r");

	if (!fpoint)
		printf("File cannot be openned\n");

	else {
		//create a buffer for the contents of the file to be read at
		char buf[2000];
		int row = 0;
		int col = 0;

		// transfer each csv box to the array
		while (fgets(buf, 2000, fpoint)) {            
			col = 0;
			row++;
			// remove headers
			if (row == 1)
				continue;

			char* str = strtok(buf, ",");

			while (str) {
				strcpy(arr2d[row-2][col], str);
				str = strtok(NULL, ",");
				col++;
			}
		}
		fclose(fpoint);
	return arr2d;
    }
}

// import the sorted csv file to a 2d string array
char*** csv_import_s(){

	//create an empty 2d string dynamic array
    char*** arr2d = (char***)malloc(ROWS * sizeof(char**));
    for (int i = 0; i < ROWS; i++){
        arr2d[i] = (char**)malloc(COLUMNS * sizeof(char*));
		for (int j=0; j<COLUMNS; j++)
		   arr2d[i][j] = (char*)malloc(sizeof(char*)*STR_LENGTH);
	}

	// create a stream pointer to csv file
	FILE* fpoint = fopen("./ocean_s.csv", "r");

	if (!fpoint)
		printf("File cannot be openned\n");

	else {
		//create a buffer for the contents of the file to be read at
		char buf[2000];
		int row = 0;
		int col = 0;

		// transfer each csv box to the array
		while (fgets(buf, 2000, fpoint)) {            
			col = 0;
			row++;
			// remove headers
			if (row == 1)
				continue;

			char* str = strtok(buf, ",");

			while (str) {
				strcpy(arr2d[row-2][col], str);
				str = strtok(NULL, ",");
				col++;
			}
		}
		fclose(fpoint);
	return arr2d;
    }
}


// export the 2d string array to an csv file
void export_csv(char*** arr, char* fname){

	// create stream pointer for the csv file
	FILE* fpoint = fopen(fname, "w");

	if(fpoint == NULL)
   	{
      	printf("Error!");   
      	exit(1);             
   	}
	// add the headers
   	fprintf(fpoint, "Date,T_degC,PO4uM,SiO3uM,NO2uM,NO3uM,Salnty,O2ml_L\n");
   
	// tranfer the strings to the csv
    for (int i=0; i<ROWS; i++){
		for (int j=0; j<COLUMNS; j++){
			fprintf(fpoint, "%s", arr[i][j]);
			if (j!=COLUMNS-1) fprintf(fpoint, ",");
		}
		fprintf(fpoint, "\n");
	}

	fclose(fpoint);
}



// take a 2d string array and convert it into a double 2d array
double** converter2double(char*** arr2d){
	// make an empty double 2d array
    double** arr = (double**)malloc(ROWS * sizeof(double*));
    for (int i = 0; i < ROWS; i++){
        arr[i] = (double*)malloc(COLUMNS * sizeof(double));
    }
    
	// convert dates
	// split dates into months, days and years
    char** month = (char**)malloc(sizeof(char*)*ROWS);
    for(int i=0; i<ROWS; i++) month[i] = (char*)malloc(sizeof(char)*5);
	
    char** day = (char**)malloc(sizeof(char*)*ROWS);
    for(int i=0; i<ROWS; i++) day[i] = (char*)malloc(sizeof(char)*5);

    char** year = (char**)malloc(sizeof(char*)*ROWS);
    for(int i=0; i<ROWS; i++) year[i] = (char*)malloc(sizeof(char)*5);
	
    for (int i=0; i<ROWS; i++){
        char* str = strtok(arr2d[i][0], "/");
        int c = 0;
        while (str) {
            if (c==0) strcpy(month[i], str);
            if (c==1) strcpy(day[i], str);
            if (c==2) strcpy(year[i], str);
            str = strtok(NULL, "/");
            c++;
        }
    }

	// rebuild dates into double format (yyyymmdd)
	//so that they can be comparable with each other
	for (int i=0; i<ROWS; i++){
		char* str = (char*)malloc(sizeof(char)*10);
		strcpy(str, year[i]);  
		strcat(str, month[i]);
		strcat(str, day[i]);
		strcpy(arr2d[i][0], str);
	}
	// convert the 2d string array to the 2d double array
	for (int i=0; i<ROWS; i++){
		for (int j=0; j<COLUMNS; j++){
			//arr[i][j] = atof(arr2d[i][j]);
			arr[i][j] = strtod(arr2d[i][j],NULL);       
		}
    }

    return arr;
}


// take a double 2d array and convert it into a 2d string array
char*** converter2str(double** arr2d){

	// make an empty 2d string array
    char*** arr = (char***)malloc(ROWS * sizeof(char**));
    for (int i = 0; i < ROWS; i++){
        arr[i] = (char**)malloc(COLUMNS * sizeof(char*));
		for (int j=0; j<COLUMNS; j++)
		   arr[i][j] = (char*)malloc(sizeof(char*)*STR_LENGTH);
	}
	
	// stores double array to string array
	for (int i = 0; i < ROWS; i++){
		for (int j = 0; j < COLUMNS; j++)
			sprintf(arr[i][j], "%.3f", arr2d[i][j]);
	}    
    // make an emty 1d string array to store dates
	char** dates = (char**)malloc(sizeof(char*)*ROWS);
	for (int i=0; i<ROWS; i++){
		dates[i] = (char*)malloc(sizeof(char)*STR_LENGTH);
	}
	// recreate the initial format of the dates
	for (int i=0; i<ROWS; i++){
		dates[i][0] = arr[i][0][4];
		dates[i][1] = arr[i][0][5];
		dates[i][2] = '/';
		dates[i][3] = arr[i][0][6];
		dates[i][4] = arr[i][0][7];
		dates[i][5] = '/';
		dates[i][6] = arr[i][0][0];
		dates[i][7] = arr[i][0][1];
		dates[i][8] = arr[i][0][2];
		dates[i][9] = arr[i][0][3];
		dates[i][10] = '\0';
	}
    // copy the dates to the final 2d string array
	for (int i=0; i<ROWS; i++){
		arr[i][0] = dates[i];
	}

	return arr;
}



// sorting the dublicate dates which have same temperature or phosphate value 
// from smaller to bigger
void date_sorting(double** arr, int column){

	// pinakas pou dixni tin arxi kai to telos ton hmeromhnion me idia 8ermokrasia h phosphoro
	int* pos = (int*)malloc(sizeof(int)*ROWS);
	for (int i = 0; i < ROWS; i++) pos[i] = 0;

	int f = 0;      // dixni an exis brei tin arxi mias seiras idion 8ermokrasion h phosphoron
	for (int i = 0; i < ROWS-1; i++) {
		
		if ((arr[i][column] == arr[i+1][column]) && (f==0)) {
			f = 1;
			pos[i] = 1;
		} else if ((arr[i][column] != arr[i+1][column]) && (f==1)) {
			pos[i] = 2;
			f = 0;
		}

		if ((f == 1) && (i == ROWS-2)) pos[i+1] = 2;
	}

	int set = 0;
	for (int i = 0; i < ROWS; i++) {
		int k, l;

		if ((pos[i] == 1) && (set == 0)) {
			k = i;
			continue;
		} else if ((pos[i] == 2) && (set == 0)) {
			l = i;
			set = 1;
		}

		if (set == 1) {
			int change = 1;
			while (change == 1) {
				change = 0;
				for (int j = k; j < l; j++) {
					if (arr[j][0] > arr[j+1][0]) {
						double* temp = (double*)malloc(sizeof(double)*COLUMNS);
						for (int o=0; o<COLUMNS; o++){
							temp[o] = arr[j][o];
							arr[j][o] = arr[j+1][o];
							arr[j+1][o] = temp[o];
						} 
						free(temp);
						change = 1;
					}
				}
			}
			set = 0;
		}
	}
}




// getting date from the user and transforming to double
int get_date(){

    printf("Gimme a date in format mm/dd/yyyy: ");
    char* date_char = (char*)malloc(sizeof(char)*STR_LENGTH);
    scanf("%s", date_char);
    
    // separate date to day, month, year
    char day[3], month[3], year[5];

	// split the date
	char* str = strtok(date_char, "/");
	int c = 0;
	while (str) {
		if (c==0) strcpy(month, str);
		if (c==1) strcpy(day, str);
		if (c==2) strcpy(year, str);
		str = strtok(NULL, "/");
		c++;
	}
    // make a string in format yyyymmdd 
    char str2[STR_LENGTH] = " ";
    strcpy(str2, year);
    strcat(str2, month);
    strcat(str2, day);
    // cast string date to int
    int date_int = atof(str2);

    return date_int;
}

