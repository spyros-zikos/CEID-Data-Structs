#include "basic_functions.h"

// struct gia ton komvo
struct Komvos {
  int date;
  double temperature;
  struct Komvos *l;
  struct Komvos *r;
  int ypsos;
};


// dimiourgia neou Komvou
struct Komvos *newKomvos(int date, double temperature) {
  struct Komvos *komvos = (struct Komvos *)malloc(sizeof(struct Komvos));
  komvos->date = date;
  komvos->temperature = temperature;
  komvos->l = NULL;
  komvos->r = NULL;
  komvos->ypsos = 1;
  return (komvos);
}


// euresi elaxistis imerominias
struct Komvos *minDate(struct Komvos *komvos) {
    struct Komvos *current = komvos;

    while (current->l != NULL)
        current = current->l;

    return current;
}



// sinartisi megistou
double max(double num1, double num2) {
    if (num1>num2) return num1;
    else return num2;
}



// ipologismos ypsoys
int ypsos(struct Komvos *komv) {
    if (komv == NULL) return 0;
    return komv->ypsos;
}



// ypologismos isoropias
int balance(struct Komvos *komv) {
    if (komv == NULL)
        return 0;
    return ypsos(komv->l) - ypsos(komv->r);
}



// aristeri apli peristrofi
struct Komvos *lRotate(struct Komvos *u) {
    struct Komvos *v = u->r;
    struct Komvos *subTree = v->l;

    v->l = u;
    u->r = subTree;

    u->ypsos = max(ypsos(u->l), ypsos(u->r)) + 1;
    v->ypsos = max(ypsos(v->l), ypsos(v->r)) + 1;

    return v;
}


// deksia apli peristrofi
struct Komvos *rRotate(struct Komvos *v) {
    struct Komvos *u = v->l;
    struct Komvos *subTree = u->r;

    u->r = v;
    v->l = subTree;

    v->ypsos = max(ypsos(v->l), ypsos(v->r)) + 1;
    u->ypsos = max(ypsos(u->l), ypsos(u->r)) + 1;

    return u;
}


// eyresi kombou
struct Komvos* search(struct Komvos* riza, int date) {
    // an i riza einai keni h i imerominia tis rizas ine auti pou psaxno
    if (riza == NULL || riza->date == date)
       return riza;
    
    if (riza->date < date)
       return search(riza->r, date);

    return search(riza->l, date);
}




// pros8iki kombou
struct Komvos *insertKomvos(struct Komvos *komvos, int date, double temperature) {
    // bres tin 8esi en8esis
    if (komvos == NULL) return (newKomvos(date, temperature));

    if (date < komvos->date)
        komvos->l = insertKomvos(komvos->l, date, temperature);
    else if (date > komvos->date)
        komvos->r = insertKomvos(komvos->r, date, temperature);
    else
        return komvos;


    // enimerose tin isoropia ka8e kombou kai isoropise to dedro
    komvos->ypsos = 1 + max(ypsos(komvos->l), ypsos(komvos->r));

    int bal = balance(komvos);
    if ((bal > 1) && (date < komvos->l->date)) {
        return rRotate(komvos);
    }
    if ((bal < -1) && (date > komvos->r->date)){
        return lRotate(komvos);
    }
    if ((bal > 1) && date > (komvos->l->date)) {
        komvos->l = lRotate(komvos->l);
        return rRotate(komvos);
    }

    if ((bal < -1) && (date < komvos->r->date)) {
        komvos->r = rRotate(komvos->r);
        return lRotate(komvos);
    }

    return komvos;
}



// diagrafi komvou
struct Komvos *deleteKomvos(struct Komvos *riza, int date) {
  // euresi 8esis komvou kai diagrafi tou komvou
    if (riza == NULL) return riza;

    if (date < riza->date)
        riza->l = deleteKomvos(riza->l, date);

    else if (date > riza->date)
        riza->r = deleteKomvos(riza->r, date);

    else {
        if ((riza->l == NULL) || (riza->r == NULL)) {
        struct Komvos *temporary;
            if (riza->l) temporary = riza->l;
            else temporary = riza->r;

            if (temporary == NULL) {
                temporary = riza;
                riza = NULL;
            } else
                *riza = *temporary;
                free(temporary);
        } else {
            struct Komvos *temporary = minDate(riza->r);
            
            riza->date = temporary->date;

            riza->r = deleteKomvos(riza->r, temporary->date);
        }
    }

    if (riza == NULL) return riza;

    // enimerose tin isoropia ka8e kombou kai isoropise to dedro
    riza->ypsos = 1 + max(ypsos(riza->l), ypsos(riza->r));

    int bal = balance(riza);
    if (bal > 1 && balance(riza->l) >= 0)
        return rRotate(riza);

    if (bal > 1 && balance(riza->l) < 0) {
        riza->l = lRotate(riza->l);
        return rRotate(riza);
    }

    if (bal < -1 && balance(riza->r) <= 0)
        return lRotate(riza);

    if (bal < -1 && balance(riza->r) > 0) {
        riza->r = rRotate(riza->r);
        return lRotate(riza);
    }

    return riza;
}



// allagi tou format tis imerominias
char* date_str_from_int(int date){
    char* datestr = (char*)malloc(sizeof(char)*STR_LENGTH);
    sprintf(datestr, "%d", date);
    char* final_date = (char*)malloc(sizeof(char)*STR_LENGTH);
    final_date[0] = datestr[4];
    final_date[1] = datestr[5];
    final_date[2] = '/';
    final_date[3] = datestr[6];
    final_date[4] = datestr[7];
    final_date[5] = '/';
    final_date[6] = datestr[0];
    final_date[7] = datestr[1];
    final_date[8] = datestr[2];
    final_date[9] = datestr[3];
    final_date[10] = '\0';

    return final_date;
}


// ektipose to dedro
void pr_tree(struct Komvos *riza) {
    if (riza != NULL) {
        printf("Date:%s->Temp:%.2f\n", date_str_from_int(riza->date), riza->temperature);
        pr_tree(riza->l);
        pr_tree(riza->r);
    }
}



// menu
void menu1(struct Komvos* riza){

    int option;

    do {
        printf("Choose an option:\n 1) presentation\n 2) search\n 3) modification\n 4) deletion\n 5) exit\n");
        scanf("%d", &option);
        
        switch (option){
            case 1:{
                pr_tree(riza);
                break;}
            case 2:{
                int date = get_date();
                struct Komvos * k = search(riza, date);
                if (k == NULL) printf("NOT FOUND\n");
                else printf("Temperature: %.3f\n", k->temperature);
                break;}
            case 3:{
                int date2 = get_date();
                struct Komvos* komvos = search(riza, date2);

                if (komvos == NULL) printf("NOT FOUND SO YOU CANT MODIFY IT\n");
                else {
                    printf("What do you want the temperature of this date to be?\n");
                    double input ;
                    scanf("%lf", &input);
                    komvos->temperature = input;
                    printf("\nThe new temperature of the selected day now is: %.3f\n", komvos->temperature);
                }
                break;}
            case 4:{
                int date3 = get_date();
                struct Komvos* riza2 = deleteKomvos(riza, date3);
                if (riza2 == NULL) printf("NOT FOUND SO YOU CANT DELETE IT\n");
                else {
                    pr_tree(riza2);
                    printf("\nSuccessfully deleted!\n");
                }
                break;}
            case 5:
                break;
        }
    } while (option != 5);
}


int main1() {
    char*** arr_imp = csv_import_u();
    double** arr_double = converter2double_u(arr_imp);


    struct Komvos *riza = NULL;
    for(int i=0; i<ROWS; i++){
        riza = insertKomvos(riza, arr_double[i][0], arr_double[i][1]);
    }

    menu1(riza);

    return 0;
}