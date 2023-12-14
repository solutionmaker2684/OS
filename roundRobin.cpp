#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

class Process{
    public:
    int processNo;
    int arrivalTime;
    int burstTime;
    int completionTime;
    int turnAroundTime;
    int waitingTime;
    int remainingTime;
};

bool compareArrivalTime(Process P1, Process P2){
    return P1.arrivalTime < P2.arrivalTime;
}

bool compareProcessNo(Process P1, Process P2){
    return P1.processNo < P2.processNo;
}

int main(){
    int noOfProcesses;
    cout << "Enter number of processes : ";
    cin >> noOfProcesses;

    vector<Process> processes(noOfProcesses);
    vector<Process> result;
    cout << "Enter arrival time of " << noOfProcesses << " processes : ";
    for(int i = 0; i < noOfProcesses; i++){
        processes[i].processNo = i + 1;
        cin >> processes[i].arrivalTime;
    }

    cout << "Enter burst time of " << noOfProcesses << " processes : ";
    for(int i = 0; i < noOfProcesses; i++){
        cin >> processes[i].burstTime;
        processes[i].remainingTime = processes[i].burstTime;
    }

    int timeQuantum;
    cout << "Enter time quantum : ";
    cin >> timeQuantum;

    sort(processes.begin(), processes.end(), compareArrivalTime);

    int currentTime = 0;

    queue<Process> readyQueue;
    queue<Process> helpingQueue;

    while(!processes.empty() || !readyQueue.empty()){
        while(!processes.empty() && processes.front().arrivalTime <= currentTime){
            readyQueue.push(processes.front());
            processes.erase(processes.begin());
        }

        if(!helpingQueue.empty()){
            readyQueue.push(helpingQueue.front());
            helpingQueue.pop();
        }

        if(readyQueue.empty()){
            currentTime++;
            continue;
        }

        Process currentProcess = readyQueue.front();
        readyQueue.pop();

        if(currentProcess.remainingTime - timeQuantum > 0){
            currentTime += timeQuantum;
            currentProcess.remainingTime -= timeQuantum;
            helpingQueue.push(currentProcess);
        }else{
            currentTime += currentProcess.remainingTime;
            currentProcess.remainingTime = 0;
            currentProcess.completionTime = currentTime;
            currentProcess.turnAroundTime = currentProcess.completionTime - currentProcess.arrivalTime;
            currentProcess.waitingTime = currentProcess.turnAroundTime - currentProcess.burstTime;
            result.push_back(currentProcess);
        }
    }

    sort(result.begin(), result.end(), compareProcessNo);
    
    cout << "Process \tArrival Time \tBurst Time \tCompletion Time \tTurnaround Time \tWaiting Time" << endl;  
    for(int i = 0; i < noOfProcesses; i++){
        cout << result[i].processNo << "\t\t" << result[i].arrivalTime << "\t\t" << result[i].burstTime << "\t\t" << result[i].completionTime << "\t\t\t" << result[i].turnAroundTime << "\t\t\t" << result[i].waitingTime << endl;
    }

    float sumTAT = 0;
    float sumWT = 0;
    for(int i = 0; i < noOfProcesses; i++){
        sumTAT += result[i].turnAroundTime;
        sumWT += result[i].waitingTime;
    }

    cout << "Average Turn Around Time = " << sumTAT / noOfProcesses << endl;
    cout << "Average Waiting Time = " << sumWT / noOfProcesses << endl;

    return 0;
}