#include <iostream>
using namespace std;

int main() {
    int noOfProcesses;
    cout << "Enter number of processes : ";
    cin >> noOfProcesses;
    
    int* arrivalTime = new int[noOfProcesses];
    cout << "Enter arrival time of " << noOfProcesses << " processes : ";
    for(int i = 0; i < noOfProcesses; i++){
        cin >> arrivalTime[i];
    }
    
    int* burstTime = new int[noOfProcesses];
    cout << "Enter burst time of " << noOfProcesses << " processes : ";
    for(int i = 0; i < noOfProcesses; i++){
        cin >> burstTime[i];
    }
    
    int* completingTime = new int[noOfProcesses];
    for(int i = 0; i < noOfProcesses; i++){
        if(i == 0){
            completingTime[i] = burstTime[i];
        }else{
            completingTime[i] = burstTime[i] + completingTime[i-1];
        }
    }
    
    int* turnAroundTime = new int[noOfProcesses];
    int* waitingTime = new int[noOfProcesses];
    float sumTAT = 0;
    float sumWT = 0;
    for(int i = 0; i < noOfProcesses; i++){
        turnAroundTime[i] = completingTime[i] - arrivalTime[i];
        waitingTime[i] = turnAroundTime[i] - burstTime[i];
        sumTAT += turnAroundTime[i];
        sumWT += waitingTime[i];
    }
    
    cout << "Process \tArrival Time \tBurst Time \tCompletion Time \tTurnaround Time \tWaiting Time" << endl;  
    for(int i = 0; i < noOfProcesses; i++){
        cout << i+1 << "\t\t" << arrivalTime[i] << "\t\t" << burstTime[i] << "\t\t" << completingTime[i] << "\t\t\t" << turnAroundTime[i] << "\t\t\t" << waitingTime[i] << endl;
    }

    cout << "\nAverage Turnaround Time = " << (sumTAT/noOfProcesses) << endl;
    cout << "Average Waiting Time = " << (sumWT/noOfProcesses) << endl;
    
    return 0;
}