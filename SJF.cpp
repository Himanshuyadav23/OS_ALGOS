#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Process {
    int id, arrivalTime, burstTime, waitingTime, turnaroundTime, completionTime;
};

void calculateSJF(vector<Process>& processes) {
    int currentTime = 0, completed = 0;
    double totalWaitingTime = 0, totalTurnaroundTime = 0;
    vector<bool> isCompleted(processes.size(), false);

    while (completed < processes.size()) {
        int minBurstIndex = -1;
        
        for (int i = 0; i < processes.size(); i++) {
            if (processes[i].arrivalTime <= currentTime && !isCompleted[i]) {
                if (minBurstIndex == -1 || processes[i].burstTime < processes[minBurstIndex].burstTime) {
                    minBurstIndex = i;
                }
            }
        }
        
        if (minBurstIndex != -1) {
            currentTime += processes[minBurstIndex].burstTime;
            processes[minBurstIndex].waitingTime = currentTime - processes[minBurstIndex].arrivalTime - processes[minBurstIndex].burstTime;
            processes[minBurstIndex].turnaroundTime = processes[minBurstIndex].waitingTime + processes[minBurstIndex].burstTime;
            processes[minBurstIndex].completionTime = currentTime;
            isCompleted[minBurstIndex] = true;
            completed++;
            totalWaitingTime += processes[minBurstIndex].waitingTime;
            totalTurnaroundTime += processes[minBurstIndex].turnaroundTime;
        } else {
            currentTime++;
        }
    }

    cout << "Process ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\tCompletion Time\n";
    for (const auto& p : processes) {
        cout << p.id << "\t\t" << p.arrivalTime << "\t\t" << p.burstTime << "\t\t" 
             << p.waitingTime << "\t\t" << p.turnaroundTime << "\t\t" << p.completionTime << "\n";
    }

    cout << "Average Waiting Time: " << totalWaitingTime / processes.size() << "\n";
    cout << "Average Turnaround Time: " << totalTurnaroundTime / processes.size() << "\n";
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        cout << "Enter arrival time and burst time for process " << i + 1 << ": ";
        cin >> processes[i].arrivalTime >> processes[i].burstTime;
    }

    calculateSJF(processes);
    return 0;
}
