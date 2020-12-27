#include "RestaurantOrganizer.h"

using namespace std;

RestaurantOrganizer::RestaurantOrganizer(const vector<int>& tableCapacityInput){
    numberOfTables = tableCapacityInput.size();
    for(int i=0; i<numberOfTables; i++){
        tableCapacity[i] = tableCapacityInput[i];
        heap[i] = i;
        heapUp(i);
    }
}

void RestaurantOrganizer::addNewGroup(int groupSize, ofstream& outFile){
    int max = tableCapacity[0];
    if (groupSize> max){
        outFile << "-1"<< endl;
        return;
    }
    tableCapacity[0] -= groupSize;
    outFile << heap[0]<< endl;
    heapDown(0);

}

void RestaurantOrganizer::heapUp(int index){
    if(index != 0) {
        if (tableCapacity[index] > tableCapacity[(index - 1) / 2]) {
            swap(tableCapacity[index], tableCapacity[(index - 1) / 2]);
            swap(heap[index],heap[(index-1)/2]);
            heapUp((index - 1) / 2);

        }
        else if(tableCapacity[index] == tableCapacity[(index - 1) / 2]) {
            if ( heap[index] < heap[(index-1)/2]){
                swap(tableCapacity[index], tableCapacity[(index - 1) / 2]);
                swap(heap[index],heap[(index-1)/2]);
                heapUp((index - 1) / 2);
            }
        }
    }
}

void RestaurantOrganizer::heapDown(int index){
    if (index*2 + 1 < numberOfTables -1){
         int x = 0;
         if (tableCapacity[index*2 + 1] == tableCapacity[index*2 +2]){
             x= (heap[index*2 +1] < heap[index*2+2])?0:1;
         }
         else {
             x =(tableCapacity[index*2 + 1] > tableCapacity[index*2 +2])?0:1;
         }

         if(tableCapacity[index] == tableCapacity[index*2+1 +x]){
             if (heap[index] > heap[index*2+1+x]){
                 swap(tableCapacity[index*2+1 + x ], tableCapacity[index]);
                 swap(heap[index], heap[index*2+1 + x]);
                 heapDown(index*2+1 + x);
             }
             else return;
         }
         else if (tableCapacity[index] < tableCapacity[index*2+1 +x]) {
             swap(tableCapacity[index*2+1 + x ], tableCapacity[index]);
             swap(heap[index], heap[index*2+1 + x]);
             heapDown(index*2+1 + x);
         }
         else return;

    }
    else if (index*2+1 == numberOfTables -1 ){
        if (tableCapacity[index*2+1] > tableCapacity[index]){
            swap(tableCapacity[index], tableCapacity[index*2+1]);
            swap(heap[index], heap[index*2+1]);
        }
    }
}

void RestaurantOrganizer::printSorted(ofstream& outFile){
    for ( int i = 0; i< numberOfTables; i++){
        int max = tableCapacity[0];
        outFile << max << " ";
        tableCapacity[0] = 0;
        heapDown(0);
    }

}

// YOU CAN ADD YOUR HELPER FUNCTIONS

void swap(int &a, int &b ){
    int c = a;
    a=b;
    b=c;
}
