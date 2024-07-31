// struct gia ton komvo
struct Komvos2 {
    int date;
    double temperature;
    struct Komvos2 *l;
    struct Komvos2 *r;
    int ypsos2;
};

// dimiourgia neou Komvou
struct Komvos2 *newKomvos2(int date, double temperature) {
    struct Komvos2 *komvos = (struct Komvos2 *)malloc(sizeof(struct Komvos2));
    komvos->temperature = temperature;
    komvos->date = date;
    komvos->l = NULL;
    komvos->r = NULL;
    komvos->ypsos2 = 1;
    return (komvos);
}

// euresi elaxistis thermokrasias
struct Komvos2 *minTemperature(struct Komvos2 *komvos) {
    struct Komvos2 *current = komvos;

    while (current->l != NULL)
        current = current->l;

    return current;
}

// euresi megistis thermokrasias
struct Komvos2 *max2Temperature(struct Komvos2 *komvos) {
    struct Komvos2 *current = komvos;

    while (current->r != NULL)
        current = current->r;

    return current;
}

// sinartisi megistou
double max2(double num1, double num2) {
    if (num1>num2) return num1;
    else return num2;
}

// ipologismos ypsoys
int ypsos2(struct Komvos2 *komv) {
  if (komv == NULL)
    return 0;
  return komv->ypsos2;
}

// ypologismos isoropias
int balance2(struct Komvos2 *komv) {
    if (komv == NULL)
        return 0;
    return ypsos2(komv->l) - ypsos2(komv->r);
}

// aristeri apli peristrofi
struct Komvos2 *lRotate2(struct Komvos2 *u) {
    struct Komvos2 *v = u->r;
    struct Komvos2 *subTree = v->l;

    v->l = u;
    u->r = subTree;

    u->ypsos2 = max2(ypsos2(u->l), ypsos2(u->r)) + 1;
    v->ypsos2 = max2(ypsos2(v->l), ypsos2(v->r)) + 1;

    return v;
}

// deksia apli peristrofi
struct Komvos2 *rRotate2(struct Komvos2 *v) {
    struct Komvos2 *u = v->l;
    struct Komvos2 *subTree = u->r;

    u->r = v;
    v->l = subTree;

    v->ypsos2 = max2(ypsos2(v->l), ypsos2(v->r)) + 1;
    u->ypsos2 = max2(ypsos2(u->l), ypsos2(u->r)) + 1;

    return u;
}

// pros8iki kombou
struct Komvos2 *insertKomvos2(struct Komvos2 *komvos, int date, double temperature) {
    // bres tin 8esi en8esis
    if (komvos == NULL) return (newKomvos2(date, temperature));

    if (temperature < komvos->temperature)
        komvos->l = insertKomvos2(komvos->l, date, temperature);
    else if (temperature >= komvos->temperature)
        komvos->r = insertKomvos2(komvos->r, date, temperature);
    else
        return komvos;

    // enimerose tin isoropia ka8e kombou kai isoropise to dedro
    komvos->ypsos2 = 1 + max2(ypsos2(komvos->l), ypsos2(komvos->r));

    int bal = balance2(komvos);
    if ((bal > 1) && (temperature < komvos->l->temperature)) {
        return rRotate2(komvos);
    } 
    if ((bal < -1) && (temperature >= komvos->r->temperature)){
        return lRotate2(komvos);
    }
    if ((bal > 1) && (temperature > komvos->l->temperature)) {
        komvos->l = lRotate2(komvos->l);
        return rRotate2(komvos);
    }
    if ((bal < -1) && (temperature <= komvos->r->temperature)) {
        komvos->r = rRotate2(komvos->r);
        return lRotate2(komvos);
    }

    return komvos;
}

// diagrafi komvou
struct Komvos2 *deleteKomvos2(struct Komvos2 *riza, double temperature, int date) {
    // euresi 8esis komvou kai diagrafi tou komvou
    if (riza == NULL) return riza;

    if (temperature < riza->temperature)
        riza->l = deleteKomvos2(riza->l, temperature, date);

    else if (temperature > riza->temperature)
        riza->r = deleteKomvos2(riza->r, temperature, date);
    else if (date != riza->date){
        if (riza->l != NULL)
            riza->l = deleteKomvos2(riza->l, temperature, date);
        if (riza->r != NULL)
            riza->r = deleteKomvos2(riza->r, temperature, date);
    }
    else {
        if ((riza->l == NULL) || (riza->r == NULL)) {
            struct Komvos2 *temporary;
            if (riza->l) temporary = riza->l;
            else temporary = riza->r;

            if (temporary == NULL) {
                temporary = riza;
                riza = NULL;
            } else
                *riza = *temporary;
                free(temporary);
        } else {
            struct Komvos2 *temporary = minTemperature(riza->r);

            riza->temperature = temporary->temperature;
            riza->date = temporary->date;

            riza->r = deleteKomvos2(riza->r, temporary->temperature, temporary->date);
        }
    }

    if (riza == NULL) return riza;

    // enimerose tin isoropia ka8e kombou kai isoropise to dedro
    riza->ypsos2 = 1 + max2(ypsos2(riza->l), ypsos2(riza->r));

    int bal = balance2(riza);
    if ((bal > 1) && (balance2(riza->l) >= 0)) {
        return rRotate2(riza);
    }
    if ((bal > 1) && (balance2(riza->l) < 0)) {
        riza->l = lRotate2(riza->l);
        return rRotate2(riza);
    }
    if ((bal < -1) && (balance2(riza->r) <= 0)) {
        return lRotate2(riza);
    }
    if ((bal < -1) && (balance2(riza->r) > 0)) {
        riza->r = rRotate2(riza->r);
        return lRotate2(riza);
    }

    return riza;
}

// allagi tou format tis imerominias
char* date_str_from_int2(int date){
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
void pr_tree2(struct Komvos2 *riza) {
    if (riza != NULL) {
        printf("Temp:%.2lf->Date:%s\n", riza->temperature, date_str_from_int2(riza->date));
        pr_tree2(riza->l);
        pr_tree2(riza->r);
  }
}

// menu
void menu2(struct Komvos2* riza) {

    int option;
    do {
        printf("Choose an option:\n 1) Find date with min temperature\n 2) Find date with max temperature\n 3) exit\n");
        scanf("%d", &option);
        
        switch (option){

            case 1:{
                struct Komvos2* komvos = minTemperature(riza);
                printf("Date(s) with minimum temperature: %s\n", date_str_from_int2(komvos->date));
                double t = komvos->temperature;

                while (1 == 1) {
                    komvos = deleteKomvos2(riza, komvos->temperature, komvos->date);
                    komvos = minTemperature(riza);
                    if (komvos->temperature == t)
                        printf("%s\n", date_str_from_int2(komvos->date));
                    else
                        break;
                }
                break;}

            case 2:{
                struct Komvos2* komvos2 = max2Temperature(riza);
                printf("Date(s) with minimum temperature: %s\n", date_str_from_int2(komvos2->date));
                double t2 = komvos2->temperature;

                while (1 == 1) {
                    komvos2 = deleteKomvos2(riza, komvos2->temperature, komvos2->date);
                    komvos2 = max2Temperature(riza);
                    if (komvos2->temperature == t2)
                        printf("%s\n", date_str_from_int2(komvos2->date));
                    else
                        break;
                }
                break;}
                
            case 3:
                break;
        }
    } while (option != 3);
}

int main2() {
    char*** arr_imp = csv_import_u();
    double** arr_double = converter2double_u(arr_imp);

    struct Komvos2 *riza = NULL;

    for (int i=0; i<ROWS; i++) {
        riza = insertKomvos2(riza, (int)arr_double[i][0], arr_double[i][1]);
    }
    
    pr_tree2(riza);
    menu2(riza);

    return 0;
}