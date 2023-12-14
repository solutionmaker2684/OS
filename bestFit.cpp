#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int main()
{
    int noOfProcesses;
    cout << "Enter number of processes : ";
    cin >> noOfProcesses;

    int noOfBlocks;
    cout << "Enter number of blocks : ";
    cin >> noOfBlocks;

    vector<int> processesSize(noOfProcesses);
    vector<int> blocksSize(noOfBlocks);

    cout << "Enter size of Processes : ";
    for (int i = 0; i < noOfProcesses; i++)
    {
        cin >> processesSize[i];
    }

    cout << "Enter size of blocks : ";
    for (int i = 0; i < noOfBlocks; i++)
    {
        cin >> blocksSize[i];
    }

    vector<int> memoryAllocated(noOfProcesses, -1);

    for (int i = 0; i < noOfProcesses; i++)
    {
        int sizeOfCurrentProcess = processesSize[i];
        vector<int> helpingVector(noOfBlocks, INT_MAX);
        for (int j = 0; j < noOfBlocks; j++)
        {
            int sizeOfCurrentBlock = blocksSize[j];
            if (sizeOfCurrentProcess <= sizeOfCurrentBlock)
            {
                helpingVector[j] = sizeOfCurrentBlock - sizeOfCurrentProcess;
            }
        }
        int minIndex = -1;
        int minValue = INT_MAX;
        for (int j = 0; j < noOfBlocks; j++)
        {
            if (helpingVector[j] < minValue)
            {
                minIndex = j;
                minValue = helpingVector[j];
            }
        }
        if (minIndex != -1)
        {
            blocksSize[minIndex] -= sizeOfCurrentProcess;
            memoryAllocated[i] = minIndex + 1;
        }
    }

    cout << "Process size\t"
         << "Block allocated" << endl;
    for (int i = 0; i < noOfProcesses; i++)
    {
        cout << processesSize[i] << "\t\t" << memoryAllocated[i] << endl;
    }
    cout << endl;
    return 0;
}