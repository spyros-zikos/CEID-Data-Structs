#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>

#define ROWS_INIT 1405
#define ROWS 1316
#define COLUMNS 8
#define STR_LENGTH 11


char*** csv_import_init(){

    char*** arr2d = (char***)malloc(ROWS_INIT * sizeof(char**));
    for (int i = 0; i < ROWS_INIT; i++){
        arr2d[i] = (char**)malloc(COLUMNS * sizeof(char*));
		for (int j=0; j<COLUMNS; j++)
		   arr2d[i][j] = (char*)malloc(sizeof(char*)*STR_LENGTH);
	}


	FILE* fpoint = fopen("./ocean.csv", "r");

	if (!fpoint)
		printf("File cannot be openned\n");

	else {

		char buf[2000];
		int row = 0;
		int col = 0;

		while (fgets(buf, 2000, fpoint)) {            
			col = 0;
			row++;

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

char*** csv_import_s(){

    char*** arr2d = (char***)malloc(ROWS_INIT * sizeof(char**));
    for (int i = 0; i < ROWS_INIT; i++){
        arr2d[i] = (char**)malloc(COLUMNS * sizeof(char*));
		for (int j=0; j<COLUMNS; j++)
		   arr2d[i][j] = (char*)malloc(sizeof(char*)*STR_LENGTH);
	}

	FILE* fpoint = fopen("./ocean_s.csv", "r");

	if (!fpoint)
		printf("File cannot be openned\n");

	else {

		char buf[2000];
		int row = 0;
		int col = 0;

		while (fgets(buf, 2000, fpoint)) {            
			col = 0;
			row++;

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


char*** csv_import_u(){

    char*** arr2d = (char***)malloc(ROWS * sizeof(char**));
    for (int i = 0; i < ROWS; i++){
        arr2d[i] = (char**)malloc(COLUMNS * sizeof(char*));
		for (int j=0; j<COLUMNS; j++)
		    arr2d[i][j] = (char*)malloc(sizeof(char*)*STR_LENGTH);
	}

	FILE* fpoint = fopen("./unique.csv", "r");

	if (!fpoint)
	    printf("File cannot be openned\n");

	else {

		char buf[2000];
		int row = 0;
		int col = 0;

		while (fgets(buf, 2000, fpoint)) {            
			col = 0;
			row++;

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


void export_csv_init(char*** arr, char* fname){

	FILE* fpoint = fopen(fname, "w");

	if(fpoint == NULL)
   {
      printf("Error!");   
      exit(1);             
   }

   fprintf(fpoint, "Date,T_degC,PO4uM,SiO3uM,NO2uM,NO3uM,Salnty,O2ml_L\n");
   
	for (int i=0; i<ROWS_INIT; i++){
		for (int j=0; j<COLUMNS; j++){
			fprintf(fpoint, "%s", arr[i][j]);
			if (j!=COLUMNS-1) fprintf(fpoint, ",");
		}
		fprintf(fpoint, "\n");
	}

	fclose(fpoint);
}


void print_arr2d_str(char*** arr2d) {
    for(int i=0; i<ROWS; i++){
		printf("\n");
        for (int j=0; j<COLUMNS; j++){ 
            printf("\t%s", arr2d[i][j]);
		}
    }
}


void print_arr2d_double(double** arr2d) {
    for(int i=0; i<ROWS; i++){
		printf("\n");
        for (int j=0; j<COLUMNS; j++){ 
            printf("\t%.3f", arr2d[i][j]);
		}
    }
}


double** converter2double_init(char*** arr2d){
	double** arr = (double**)malloc(ROWS_INIT * sizeof(double*));
    for (int i = 0; i < ROWS_INIT; i++){
        arr[i] = (double*)malloc(COLUMNS * sizeof(double));
	}
     
	char** month = (char**)malloc(sizeof(char*)*ROWS_INIT);
	for(int i=0; i<ROWS_INIT; i++) month[i] = (char*)malloc(sizeof(char)*5);
	
	char** day = (char**)malloc(sizeof(char*)*ROWS_INIT);
	for(int i=0; i<ROWS_INIT; i++) day[i] = (char*)malloc(sizeof(char)*5);

	char** year = (char**)malloc(sizeof(char*)*ROWS_INIT);
	for(int i=0; i<ROWS_INIT; i++) year[i] = (char*)malloc(sizeof(char)*5);
	
	for (int i=0; i<ROWS_INIT; i++){
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
	
	for (int i=0; i<ROWS_INIT; i++){
		char* str = (char*)malloc(sizeof(char)*10);
		strcpy(str, year[i]);  
		strcat(str, month[i]);
		strcat(str, day[i]);
		strcpy(arr2d[i][0], str);
	}

	for (int i=0; i<ROWS_INIT; i++){
		for (int j=0; j<COLUMNS; j++){
			//arr[i][j] = atof(arr2d[i][j]);
			arr[i][j] = strtod(arr2d[i][j],NULL);       
		}
	}

	return arr;
}


double** converter2double_u(char*** arr2d){
	double** arr = (double**)malloc(ROWS * sizeof(double*));
    for (int i = 0; i < ROWS; i++){
        arr[i] = (double*)malloc(COLUMNS * sizeof(double));
	}
     
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
	
	for (int i=0; i<ROWS; i++){
		char* str = (char*)malloc(sizeof(char)*10);
		strcpy(str, year[i]);  
		strcat(str, month[i]);
		strcat(str, day[i]);
		strcpy(arr2d[i][0], str);
	}

	for (int i=0; i<ROWS; i++){
		for (int j=0; j<COLUMNS; j++){
			//arr[i][j] = atof(arr2d[i][j]);
			arr[i][j] = strtod(arr2d[i][j],NULL);       
		}
	}

	return arr;
}


char*** converter2str_init(double** arr2d){

    char*** arr = (char***)malloc(ROWS_INIT * sizeof(char**));
    for (int i = 0; i < ROWS_INIT; i++){
        arr[i] = (char**)malloc(COLUMNS * sizeof(char*));
		for (int j=0; j<COLUMNS; j++)
		   arr[i][j] = (char*)malloc(sizeof(char*)*STR_LENGTH);
	}

	for (int i = 0; i < ROWS_INIT; i++){
		for (int j=0; j<COLUMNS; j++)
			sprintf(arr[i][j], "%.3f", arr2d[i][j]);
	}    

	char** dates = (char**)malloc(sizeof(char*)*ROWS_INIT);
	for (int i=0; i<ROWS_INIT; i++){
		dates[i] = (char*)malloc(sizeof(char)*STR_LENGTH);
	}
	
	for (int i=0; i<ROWS_INIT; i++){
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

	for (int i=0; i<ROWS_INIT; i++){
		arr[i][0] = dates[i];
	}

	return arr;
}


// for sorted_unique.c
char*** converter2str_u(double** arr2d){

    char*** arr = (char***)malloc(ROWS * sizeof(char**));
    for (int i = 0; i < ROWS; i++){
        arr[i] = (char**)malloc(COLUMNS * sizeof(char*));
		for (int j=0; j<COLUMNS; j++)
		   arr[i][j] = (char*)malloc(sizeof(char*)*STR_LENGTH);
	}

	for (int i = 0; i < ROWS; i++){
		for (int j=0; j<COLUMNS; j++)
			sprintf(arr[i][j], "%.3f", arr2d[i][j]);
	}    

	char** dates = (char**)malloc(sizeof(char*)*ROWS);
	for (int i=0; i<ROWS; i++){
		dates[i] = (char*)malloc(sizeof(char)*STR_LENGTH);
	}
	
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

	for (int i=0; i<ROWS; i++){
		arr[i][0] = dates[i];
	}

	return arr;
}


// for sorted_unique.c
void export_csv2(char*** arr, char* fname){

	FILE* fpoint = fopen(fname, "w");

	if(fpoint == NULL)
   {
      printf("Error!");   
      exit(1);             
   }

   fprintf(fpoint, "Date,T_degC,PO4uM,SiO3uM,NO2uM,NO3uM,Salnty,O2ml_L\n");
   
	for (int i=0; i<ROWS; i++){
		for (int j=0; j<COLUMNS; j++){
			fprintf(fpoint, "%s", arr[i][j]);
			if (j!=COLUMNS-1) fprintf(fpoint, ",");
		}
		fprintf(fpoint, "\n");
	}

	fclose(fpoint);
}


int get_date(){

    printf("Gimme a date in format mm/dd/yyyy: ");
    char* date_char = (char*)malloc(sizeof(char)*STR_LENGTH);
    scanf("%s", date_char);

    char day[3], month[3], year[5];

	char* str = strtok(date_char, "/");
	int c = 0;
	while (str) {
		if (c==0) strcpy(month, str);
		if (c==1) strcpy(day, str);
		if (c==2) strcpy(year, str);
		str = strtok(NULL, "/");
		c++;
	}

    char str2[STR_LENGTH] = " ";
    strcpy(str2, year);
    strcat(str2, month);
    strcat(str2, day);

    int date_int = atof(str2);

    return date_int;
}