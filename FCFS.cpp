#include <iostream>
#include <vector>
using namespace std;

struct Process {
    int id, arrivalTime, burstTime, waitingTime, turnaroundTime, completionTime;
};

void calculateFCFS(vector<Process>& processes) {
    int currentTime = 0;
    double totalWaitingTime = 0, totalTurnaroundTime = 0;

    for (auto& process : processes) {
        if (currentTime < process.arrivalTime)
            currentTime = process.arrivalTime;
        
        process.waitingTime = currentTime - process.arrivalTime;
        process.turnaroundTime = process.waitingTime + process.burstTime;
        process.completionTime = currentTime + process.burstTime;

        currentTime += process.burstTime;
        totalWaitingTime += process.waitingTime;
        totalTurnaroundTime += process.turnaroundTime;
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

    calculateFCFS(processes);
    return 0;
}
