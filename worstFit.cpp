#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int main(){
    int noOfProcesses;
    cout << "Enter number of processes : ";
    cin >> noOfProcesses;

    int noOfBlocks;
    cout << "Enter number of blocks : ";
    cin >> noOfBlocks;

    vector<int> processesSize(noOfProcesses);
    vector<int> blocksSize(noOfBlocks);

    cout << "Enter size of Processes : ";
    for(int i = 0; i < noOfProcesses; i++){
        cin >> processesSize[i];
    }

    cout << "Enter size of blocks : ";
    for(int i = 0; i < noOfBlocks; i++){
        cin >> blocksSize[i];
    }

    vector<int> memoryAllocated(noOfProcesses, -1);

    for(int i = 0; i < noOfProcesses; i++){
        int sizeOfCurrentProcess = processesSize[i];
        vector<int> helpingVector(noOfBlocks, INT_MIN);
        for(int j = 0; j < noOfBlocks; j++){
            int sizeOfCurrentBlock = blocksSize[j];
            if(sizeOfCurrentProcess <= sizeOfCurrentBlock){
                helpingVector[j] = sizeOfCurrentBlock - sizeOfCurrentProcess;
            }
        }
        int maxIndex = -1;
        int maxValue = INT_MIN;
        for(int j = 0; j < noOfBlocks; j++){
            if(helpingVector[j] > maxValue){
                maxIndex = j;
                maxValue = helpingVector[j];
            }
        }
        if(maxIndex != -1){
            blocksSize[maxIndex] -= sizeOfCurrentProcess;
            memoryAllocated[i] = maxIndex + 1;
        }   
    }

    cout << "Process size\t" << "Block allocated" << endl;
    for(int i = 0; i < noOfProcesses; i++){
        cout << processesSize[i] << "\t\t" << memoryAllocated[i] << endl;
    }
    cout << endl;
    
    return 0;
}