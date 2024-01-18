#include <iostream>
#include <chrono>
#include <queue>
#include <string>
#include <ctime>
#include <iomanip>
#include <algorithm> 

using namespace std;

class Costumer {
public:
    int ticketNumber;
    chrono::time_point<chrono::system_clock> timeArrival;
    string costumerName;

    Costumer(int ticket, const string& costumer) : ticketNumber(ticket), costumerName(costumer) {
        
        transform(costumerName.begin(), costumerName.end(), costumerName.begin(), ::toupper);
        timeArrival = chrono::system_clock::now();
    }
};

class Hospital {
private:
    queue<Costumer> inQueue;

public:
    void newCoustumer(const string& costumerName) {
        static int ticketNumber = 1;
        Costumer newCoustumer(ticketNumber++, costumerName);
        inQueue.push(newCoustumer);
        cout<< "Patient : "<< newCoustumer.costumerName<< ", with queue number "<< newCoustumer.ticketNumber<< ", has been added in queue\n";
    }

    void nextNewCostumer() {
        if (!inQueue.empty()) {
            cout<< "Patients in the queue:\n";
            int position = 1;

            queue<Costumer> tempQueue = inQueue;

            while (!tempQueue.empty()) {
                const Costumer& patient = tempQueue.front();
                auto currentTime = chrono::system_clock::now();
                chrono::duration<double> inQueueTime = currentTime - patient.timeArrival;

                time_t timeArrival = chrono::system_clock::to_time_t(patient.timeArrival);
                cout <<position++ <<". Patient " <<patient.costumerName <<" Queue number: " <<patient.ticketNumber
                     <<" has been waiting for " <<fixed <<setprecision(2) <<inQueueTime.count() <<" seconds since "
                     <<std::put_time(std::localtime(&timeArrival), "%Y-%m-%d %H:%M:%S") <<endl;

                tempQueue.pop();
            }
        } 
        else {
            cout <<"No patient in queue\n";
        }
    }

    void callNextInQueue() {
        if (!inQueue.empty()) {
            Costumer calledPatient = inQueue.front();
            inQueue.pop();

            cout <<"Patient " <<calledPatient.costumerName <<" Queue number: " <<calledPatient.ticketNumber
                 <<" has been called and removed from the queue.\n";

           
            if (!inQueue.empty()) {
                Costumer nextPatient = inQueue.front();
                cout <<"Next patient in the queue is now at the front: " <<nextPatient.costumerName 
                <<" Queue number: " <<nextPatient.ticketNumber <<"\n";
            } 
            else {
                cout<< "No more patients in the queue.\n";
            }
        } 
        else {
            cout << "No patient in queue\n";
        }
    }
};

int main() {
    Hospital hospital;
    string costumerName;

    while (1) {
        cout <<"Press key 1, 2, 3 to choose\n";
        cout <<"1. New patient\n";
        cout <<"2. Show patients and how long they have been waiting\n";
        cout <<"3. Call the next patient in queue\n";
        cout <<"4. END\n";

        int adminChoice;
        cin>> adminChoice;
        switch (adminChoice) {
            case 1:
                cout <<"Patient's Name: ";
                cin>> costumerName;
                hospital.newCoustumer(costumerName);
                break;

            case 2:
                hospital.nextNewCostumer();
                break;

            case 3:
                hospital.callNextInQueue();
                break;

            case 4:
                cout<< "Thank you for today! :)\n";
                return 0;

            default:
                cout<< "Press key 1, 2, 3, or 4 to choose an alternative\n";
        }
    }

    return 0;
}