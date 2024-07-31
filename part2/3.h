#define N 51 

// struct komvou
typedef struct Komvos3{
    int date;
    double temperature;
    struct Komvos3 *next;
} Komvos3;

// find the ascii of the date (without the slashes)
int int_from_str(char* date) {

    int result = 0;
    for (int i = 0; i < 8; i++) {
        result += (int)date[i];
    }
    return result;
}

// pros8iki komvou
Komvos3 *insert(Komvos3 *array, int indx, int date, double temp){
    Komvos3 *nextNode, *currentNode;

    nextNode = (Komvos3*)malloc(sizeof(Komvos3));
    nextNode->date=date;
    nextNode->next=NULL;
    nextNode->temperature=temp;
    
    if(array[indx].next == NULL){
	array[indx].next = nextNode;
	return array;
    }
	
    currentNode = array[indx].next;
    while(currentNode->next != NULL){
	currentNode=currentNode->next;
    }
    currentNode->next = nextNode;
    return array;
}

// initialize the array
Komvos3 *init(Komvos3 *array, int array_size){

    char*** arr_imp = csv_import_u();
    double** arr_double = converter2double_u(arr_imp);

    for(int i=0; i<ROWS; i++){
	    array = insert(array, int_from_str(arr_imp[i][0]) % array_size, (int)arr_double[i][0], arr_double[i][1]);
    }
    return array;
}

// deletion of node given the date 
int deletion(Komvos3 *array, int array_size, int date){

    int asc = 0;
    char* dt = (char*)malloc(sizeof(char)*11);
    sprintf(dt, "%d", date);

    for (int i = 0; i < 8; i++)
        asc += (int)dt[i];

    int index = asc % N;
    
    Komvos3 *prev;
	
    if(array[index].next == NULL) 
        return -1;
    
	
    if(array[index].next->date == date){ 
	array[index].next = array[index].next->next;
	return 0;
    }

    prev = array[index].next;
    while(prev->next!=NULL){
	if(prev->next->date == date){
		prev->next = prev->next->next;
		return 0;
	}
	prev = prev->next;
    }
    
    return -2;
}

// print the chain hashing
void pr_chain(Komvos3 *array, int array_size){
    int i;
    Komvos3* currentNode;
    int k = 0;
    
    for(i = 0; i < array_size; i++){ 
        
	    if(array[i].next == NULL){ 
            printf("Table[%d] is empty!\n\n", i);
		    continue;
	    }
	    currentNode = array[i].next;
        printf("Table[%d]", i);
	    while(currentNode!=NULL){ 
            k++;
            printf("-> %s, %.2f ",date_str_from_int(currentNode->date), currentNode->temperature);
            if (k%5 == 0) printf("\n");
	    	currentNode=currentNode->next; 
	    }
        printf("\n\n");	
    }
}

// search temp given the date
double search_array(Komvos3 *array, int array_size, int date){

    int asc = 0;
    char* dt = (char*)malloc(sizeof(char)*11);
    sprintf(dt, "%d", date);

    for (int i = 0; i < 8; i++)
        asc += (int)dt[i];

    int index = asc % N;
    
    Komvos3 *currentNode;
    
    if(array[index].next == NULL) 
        return -2;
    
    currentNode = array[index].next;
    while(currentNode!=NULL){
	    if(currentNode->date == date){
		    return currentNode->temperature;
	    }
	    currentNode = currentNode->next;
    }

    return -1;
}

// modify temperature given the date 
double modify_array(Komvos3 *array, int array_size, int date, double temp){

    int asc = 0;
    char* dt = (char*)malloc(sizeof(char)*11);
    sprintf(dt, "%d", date);

    for (int i = 0; i < 8; i++)
        asc += (int)dt[i];

    int index = asc % N;
    
    Komvos3 *currentNode;
    
    if(array[index].next == NULL) 
        return -2;
    
    currentNode = array[index].next;
    while(currentNode!=NULL){
	    if(currentNode->date == date){
            currentNode->temperature = temp;
		    return currentNode->temperature;
	    }
	    currentNode = currentNode->next;
    }

    return -1;
}

// menu
int menu3(Komvos3* array) {

    int option;
    
    do {
        printf("Choose an option:\n 1) presentation\n 2) search\n 3) modification\n 4) deletion\n 5) exit\n");
        scanf("%d", &option);

        switch (option){
            case 1:{
                pr_chain(array, N);
                break;}
            case 2:{
                int date = get_date();
                double temp = search_array(array, N, date);
                if (temp == -1.00)
                    printf("Date not found!\n");
                else if (temp == -2.00)
                    printf("Date not found because Table is emtpy!\n");
                else
                    printf("Temperature: %.2f\n", temp);
                break;}
            case 3:{
                int date2 = get_date();
                double temperature;
                printf("Gimme the new temperature: ");
                scanf("%lf", &temperature);
                double temp2 = modify_array(array, N, date2, temperature);
                if (temp2 == -1.00)
                    printf("Date not found!\n");
                else if (temp2 == -2.00)
                    printf("Date not found because Table is emtpy!\n");
                else
                    printf("New temperature: %.2f\n", temp2);
                break;}
            case 4:{
                int date3 = get_date();
                int status = deletion(array, N, date3);
                if (status == 0)
                    printf("Date was found and Deleted!\n");
                else if (status == -1)
                    printf("Date not found cause Table is emtpy!\n");
                else
                    printf("Date was not found in Hasharray!\n");
                break;}
            case 5:
                return -1;
        }
    } while (option != 5);

    return 0;
}

int main3(){

    Komvos3 *array;
    array = (Komvos3*) malloc(N*sizeof(Komvos3));
    for(int i = 0; i < N; i++){
        array[i].next = NULL;
    }
    array = init(array, N);
    menu3(array);

	return 0;
}

