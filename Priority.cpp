#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Process {
    int id, arrivalTime, burstTime, priority, waitingTime, turnaroundTime, completionTime;
};

void calculatePriorityScheduling(vector<Process>& processes) {
    int currentTime = 0, completed = 0;
    double totalWaitingTime = 0, totalTurnaroundTime = 0;

    while (completed < processes.size()) {
        int highestPriorityIndex = -1;

        for (int i = 0; i < processes.size(); i++) {
            if (processes[i].arrivalTime <= currentTime && processes[i].completionTime == 0) {
                if (highestPriorityIndex == -1 || processes[i].priority < processes[highestPriorityIndex].priority) {
                    highestPriorityIndex = i;
                }
            }
        }

        if (highestPriorityIndex != -1) {
            currentTime += processes[highestPriorityIndex].burstTime;
            processes[highestPriorityIndex].waitingTime = currentTime - processes[highestPriorityIndex].arrivalTime - processes[highestPriorityIndex].burstTime;
            processes[highestPriorityIndex].turnaroundTime = processes[highestPriorityIndex].waitingTime + processes[highestPriorityIndex].burstTime;
            processes[highestPriorityIndex].completionTime = currentTime;
            completed++;
            totalWaitingTime += processes[highestPriorityIndex].waitingTime;
            totalTurnaroundTime += processes[highestPriorityIndex].turnaroundTime;
        } else {
            currentTime++;
        }
    }

    cout << "Process ID\tArrival Time\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\tCompletion Time\n";
    for (const auto& p : processes) {
        cout << p.id << "\t\t" << p.arrivalTime << "\t\t" << p.burstTime << "\t\t" 
             << p.priority << "\t\t" << p.waitingTime << "\t\t" << p.turnaroundTime << "\t\t" << p.completionTime << "\n";
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
        cout << "Enter arrival time, burst time, and priority for process " << i + 1 << ": ";
        cin >> processes[i].arrivalTime >> processes[i].burstTime >> processes[i].priority;
    }

    calculatePriorityScheduling(processes);
    return 0;
}
