#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#define N 100                           //number of rooms and prisoners

void shuffle(int Arr[], int n);         //Function 1: shuffle the 1-100 array
bool findsRoom(int Arr[], int n);       //Function 2: true or false if prisoner finds the same number as their room
bool safe(int Arr[]);                   //Function 3: given a room, will all prisoners find their numbers

//void printing(int Arr[], int n);      //prints table of room array

int main(void) {
    int rooms[N];                       //start with blank array for rooms

    time_t t;                           //set t to current calendar time
    srand((unsigned) time(&t));         //generate a fresh seed using t

    float victory = 0.0;                //times out of 10000 the prisoners win
    int i = 0;                          
    while (i < 10000)
    {
        shuffle(rooms, N);              //fresh shuffle
        if (safe(rooms)) {              //do they live?
            victory += 1.0;             
        }
        i++;
    }

    printf("Prisoners win %.10g%% of the time out of 10,000.\n", (victory/10000.0) * 100);

    return 0;
}

void shuffle(int Arr[], int n) {
    for (int i = 0; i < N; i++) {       //generate the array of rooms
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

bool findsRoom(int Arr[], int n) {
    int temp = n;
    int i = 0;
   
    while (i < N/2) {
        if (Arr[temp] == n) {
            return true;
        }
        else {
            temp = Arr[temp];
            i++;
        }
    }

    return false;
}

bool safe(int Arr[]) {
    int success = 0;
    for (int i = 0; i < N; i++) {
        if (findsRoom(Arr, i) == true) {
            success++;   
        }
    }
    
    if (success == N) {
        return true;    
    }
    else {
        return false;
    }
}
    

/*void printing(int Arr[], int n) {       //prints room array
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
}*/