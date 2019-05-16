#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
enum op {SYNCH, DOOR, LIGHT, EMIT, KEYPAD, RUN,COOKTIME };

int displayMenu();
int normCook();
int foodMenu();
//function sleep declaration

int main() {
    key_t key;
    int shm_id;
    int *shm;
    int doorstat;
    int oc;


    char cookTime[4];
    int powerlevel;

    key=0x520260A;
    //key = ftok("/home/kosuke/IPU", 'a' );
    printf("key= %x\n", key);
    shm_id = shmget(key, sizeof(int)*10, 0666);

    printf(" shm_id = %d\n", shm_id);
    shm = shmat(shm_id,0,0);
    printf("waiting for GO.\n");
    while ( *(shm+SYNCH) == 0 );

    // start application

    int option = 0;

    while(option != 4) {
        option = displayMenu();
        if(option == 1) {
            // assume power level 100, ask for time

            normCook();
        }
        else if(option == 2) {
            // ask for power level, time
            printf("Enter power level: %d", powerlevel);
            printf("Enter time: %s", &cookTime);
            //timer(CookTime);

        }
        else if(option == 3) {
            // show list of popcorn, pork, chicken, beef, 1 cup water
        foodMenu();

        if (foodchoice ==1)
            printf("You chose popcorn");
            normCook();
        else if (foodchoice ==2)
            printf("You chose pork");
            normCook();

        else if (foodchoice ==3)
        printf("You chose Chicken");
        normCook();
        
        }

    }
    printf("goodbye. \n");
}//end main






int displayMenu() {
    int choice = 0;
    printf("Welcome to Microwave 9000! \n");
    printf("Please select an option: \n");
    printf("1. quick cook \n");
    printf("2. set power level and cook \n");
    printf("3. cook by item \n");
    printf("4. quit \n");
    scanf("%d", &choice);
    return choice;

}

int normCook() {
    char cookTime[4];
    //char ch[] = {' '};
    // call to keypad.c
    printf("How long to cook for?");
    scanf("%s", &cookTime);

    //timer(cookTime);
    for(int i = 1; i <= cookTime; i++) {
        printf("%d \n", i);
        // ch = i;
        // write(0, &i, 1);
        sleep(1);
    }
}

int foodMenu(){
    int foodchoice;
    printf("Choose a food option ");
    printf("1.Popcorn");
    printf("2.Pork");
    printf("3.Chicken");
    scanf("%d", &foodchoice);
    return foodchoice;

}
