#include <iostream>
#include <vector>
using namespace std;

struct Process {
    int id, arrivalTime, burstTime, waitingTime, turnaroundTime, completionTime, remainingTime;
};

void calculateRR(vector<Process>& processes, int quantum) {
    int currentTime = 0, completed = 0;
    double totalWaitingTime = 0, totalTurnaroundTime = 0;
    bool done;

    for (auto& process : processes)
        process.remainingTime = process.burstTime;

    do {
        done = true;
        for (auto& p : processes) {
            if (p.remainingTime > 0) {
                done = false;
                
                if (p.remainingTime > quantum) {
                    currentTime += quantum;
                    p.remainingTime -= quantum;
                } else {
                    currentTime += p.remainingTime;
                    p.waitingTime = currentTime - p.arrivalTime - p.burstTime;
                    p.turnaroundTime = p.waitingTime + p.burstTime;
                    p.completionTime = currentTime;
                    p.remainingTime = 0;
                    completed++;
                    totalWaitingTime += p.waitingTime;
                    totalTurnaroundTime += p.turnaroundTime;
                }
            }
        }
    } while (!done);

    cout << "Process ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\tCompletion Time\n";
    for (const auto& p : processes) {
        cout << p.id << "\t\t" << p.arrivalTime << "\t\t" << p.burstTime << "\t\t" 
             << p.waitingTime << "\t\t" << p.turnaroundTime << "\t\t" << p.completionTime << "\n";
    }

    cout << "Average Waiting Time: " << totalWaitingTime / processes.size() << "\n";
    cout << "Average Turnaround Time: " << totalTurnaroundTime / processes.size() << "\n";
}

int main() {
    int n, quantum;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        cout << "Enter arrival time and burst time for process " << i + 1 << ": ";
        cin >> processes[i].arrivalTime >> processes[i].burstTime;
    }
    
    cout << "Enter the time quantum: ";
    cin >> quantum;

    calculateRR(processes, quantum);
    return 0;
}
