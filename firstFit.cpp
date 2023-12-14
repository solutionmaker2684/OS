#include <iostream>
#include <vector>
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
        for(int j = 0; j < noOfBlocks; j++){
            int sizeOfCurrentBlock = blocksSize[j];
            if(sizeOfCurrentProcess <= sizeOfCurrentBlock){
                blocksSize[j] -= sizeOfCurrentProcess;
                memoryAllocated[i] = j + 1;
                break;
            }
        }
    }

    cout << "Process size\t" << "Block allocated" << endl;
    for(int i = 0; i < noOfProcesses; i++){
        cout << processesSize[i] << "\t\t" << memoryAllocated[i] << endl;
    }
    cout << endl;

    return 0;
}