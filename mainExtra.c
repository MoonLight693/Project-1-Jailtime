#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

void shuffle(int Arr[], int n);         //Function 1: shuffle the 1-100 array
bool findsRoom(int Arr[], int r, int n);//Function 2: true or false if prisoner finds the same number as their room
bool safe(int Arr[], int n);            //Function 3: given a room, will all prisoners find their numbers

//Extra credit functions
void victoryTest(int n);                //copy of main in a function for testing more prisoners
void printing(int Arr[], int n);        //prints table of room array (was for testing shuffle)

int main(void) {
    int n = 100;                        //n is used for number of rooms and for changing to 200, 500, 1000 later
    int rooms[n];                       //start with blank array for rooms

    time_t t;                           //set t to current calendar time
    srand((unsigned) time(&t));         //generate a fresh seed using t

    float victory = 0.0;                //times out of 10000 the prisoners win
    int i = 0;                          
    while (i < 10000)
    {
        shuffle(rooms, n);              //fresh shuffle
        if (safe(rooms, n)) {           //do they live?
            victory += 1.0;             
        }
        i++;
    }

    printf("%d Prisoners win %.10g%% of the time out of 10,000.\n", n, (victory/10000.0) * 100);

    // testing for 200 prisoners
    n = 200;
    victoryTest(n);

    //testing for 500 prisoners
    n = 500;
    victoryTest(n);

    //testing for 1000 prisoners
    n = 1000;
    victoryTest(n);

    return 0;
}

void shuffle(int Arr[], int n) {
    for (int i = 0; i < n; i++) {       //generate the array of rooms
        Arr[i] = i;
    }

    int j = 0;                          //place holder for random position
    int temp = 0;                       //used in switching values
    
    for (int i = 0; i <= n-2; i++) {
        j = (rand() % n);               //generates random position in the scope of the array
        temp = Arr[i];                  //swaps position i for j
        Arr[i] = Arr[j];
        Arr[j] = temp;
    }
}

bool findsRoom(int Arr[], int r, int n){//checks if prisoner finds their room number
    int temp = r;                       //temp for switching current number in chain (r for room number)
    int i = 0;
   
    while (i < n/2) {                   //always have chances equal to half the number of rooms
        if (Arr[temp] == r) {           //if number in box matches return true
            return true;
        }
        else {                          //else move to next box number in chain
            temp = Arr[temp];
            i++;
        }
    }

    return false;                       //return false when run out of tries
}

bool safe(int Arr[], int n) {               //checkes if all prisoners succeed
    int success = 0;
    for (int i = 0; i < n; i++) {
        if (findsRoom(Arr, i, n) == true) { //if prisoner finds room in allowed number of tries
            success++;                      //add one to successes
        }
    }
    
    if (success == n) {                     //if each prisoner succeed, return true
        return true;    
    }
    else {
        return false;                       //if each prisoner failed, return flase
    }
}
    
void victoryTest(int n) {
    int rooms2[n];
    float victory2 = 0.0;                //times out of 10000 the prisoners win
    int i = 0;                          
    while (i < 10000)
    {
        shuffle(rooms2, n);              //fresh shuffle
        if (safe(rooms2, n)) {           //do they live?
            victory2 += 1.0;             
        }
        i++;
    }

    printf("%d Prisoners win %.10g%% of the time out of 10,000.\n", n, (victory2/10000.0) * 100);

}

void printing(int Arr[], int n) {       //prints room array
    for (int i = 0; i < n; i++) {
        if (Arr[i] > 99) {
            printf("%d ", Arr[i]);      //1 space
        }
        else if (Arr[i] > 9) {
            printf("%d  ", Arr[i]);     //2 spaces
        }
        else {
            printf("%d   ", Arr[i]);    //3 spaces
        }

        if (i != 0) {                   //rows of 10
            if (i % 10 == 9) {
                printf("\n");
            }
        }       
    }
}