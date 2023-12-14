#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

class Process{
    public:
    int processNo;
    int priority;
    int arrivalTime;
    int burstTime;
    int completionTime;
    int turnAroundTime;
    int waitingTime;
    int remainingTime;
};

class Comp{
    public:
    bool operator()(Process P1, Process P2){
        if(P1.priority == P2.priority){
            if(P1.arrivalTime == P2.arrivalTime){
                return P1.processNo > P2.processNo;
            }
            return P1.arrivalTime > P2.arrivalTime;
        }
        return P1.priority > P2.priority;
    }
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

    cout << "Enter priorities of " << noOfProcesses << " processes : ";
    for(int i = 0; i < noOfProcesses; i++){
        processes[i].processNo = i + 1;
        cin >> processes[i].priority;
    }

    cout << "Enter arrival time of " << noOfProcesses << " processes : ";
    for(int i = 0; i < noOfProcesses; i++){
        cin >> processes[i].arrivalTime;
    }

    cout << "Enter burst time of " << noOfProcesses << " processes : ";
    for(int i = 0; i < noOfProcesses; i++){
        cin >> processes[i].burstTime;
        processes[i].remainingTime = processes[i].burstTime;
    }

    sort(processes.begin(), processes.end(), compareArrivalTime);

    int currentTime = 0;

    priority_queue<Process, vector<Process>, Comp> readyQueue;

    while(!processes.empty() || !readyQueue.empty()){
        while(!processes.empty() && processes.front().arrivalTime <= currentTime){
            readyQueue.push(processes.front());
            processes.erase(processes.begin());
        }

        if(readyQueue.empty()){
            currentTime++;
            continue;
        }

        Process currentProcess = readyQueue.top();
        readyQueue.pop();
        if(currentProcess.remainingTime == 0){
            currentProcess.completionTime = currentTime;
            currentProcess.turnAroundTime = currentProcess.completionTime - currentProcess.arrivalTime;
            currentProcess.waitingTime = currentProcess.turnAroundTime - currentProcess.burstTime;
            result.push_back(currentProcess);
        }else{
            currentProcess.remainingTime--;
            readyQueue.push(currentProcess);
            currentTime++;
        }
    }

    sort(result.begin(), result.end(), compareProcessNo);
    
    cout << "Process \tPriority \tArrival Time \tBurst Time \tCompletion Time \tTurnaround Time \tWaiting Time" << endl;  
    for(int i = 0; i < noOfProcesses; i++){
        cout << result[i].processNo << "\t\t" << result[i].priority << "\t\t" << result[i].arrivalTime << "\t\t" << result[i].burstTime << "\t\t" << result[i].completionTime << "\t\t\t" << result[i].turnAroundTime << "\t\t\t" << result[i].waitingTime << endl;
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