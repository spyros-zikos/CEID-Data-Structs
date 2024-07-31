#include "1.h"
#include "2.h"
#include "3.h"


int main() {

    int choice;

    do {
        printf("\nSelect from the following representations");
        printf("\n1->AVL tree with date: Press 1\n2->AVL tree with temperature: Press 2\n3->HASHING CHAIN: Press 3\n4->EXIT: Press 4\nSelection: ");       
        scanf("%d", &choice);
        switch(choice){
            case 1:
                main1();
                break;
            case 2:
                main2();
                break;
            case 3:
                main3();
                break;
        }
    } while (choice != 4);
    
    return 0;
}