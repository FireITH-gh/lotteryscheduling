#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <random>
#include <set>

class Process {
    public:

        // Create a process with an id
        Process(int id) {
            this->id = id;
            tickets;
        }

        // Assign a lottery ticket to the process
        void AssignTicket(int ticket) {
            tickets.insert(ticket);
        }

        // Get a process's ID
        int GetId() {
            return id;
        }

        // Check if the process is the winner of the lottery
        bool IsWinner(int ticket) {

            // If the find() function returns the end, the ticket was not found. Otherwise, the process is a winner
            return tickets.find(ticket) != tickets.end();
        }


    private:
        int id;
        std::set<int> tickets;
};


class Scheduler {
    public:

        // Create the scheduler
        Scheduler() {
            totalTickets = 0;
            queue;
        }


        // Add a process to the scheduling queue
        void AddProcess(int id) {
            queue.push_back(Process(id));
        }

        // Allocate a given number of tickets to each process
        void AllocateTickets(int numTickets) {

            for (int i = 0; i < queue.size(); ++i) {
                for (int j = 0; j < numTickets; ++j) {

                    // Assign a ticket to a process, and increment the counter for the total number of tickets
                    queue.at(i).AssignTicket(totalTickets);
                    ++totalTickets;

                }
            }
        }

        // Allocate a given number of tickets to a specific process id
        void AllocateTicketsToID(int numTickets, int id) {
            for (int i = 0; i < numTickets; ++i) {
                queue.at(id - 1).AssignTicket(totalTickets);
                ++totalTickets;
            }
        }

        // Select the next process to run
        void RunLottery() {

            std::cout << std::endl << "Running lottery..." << std::endl;

            // Generate the winning lottery number
            int winner = rand() % totalTickets;

            std::cout << "Total number of processes: " << queue.size() << std::endl;
            std::cout << "Total number of tickets: " << totalTickets << std::endl;
            std::cout << "Winning number: " << winner << std::endl << std::endl;

            // Check each process to see if it is the winner
            for (int i = 0; i < queue.size(); ++i) {

                // Check if the process is the winner and print a message if it is
                if (queue.at(i).IsWinner(winner)) {
                    std::cout << "Process " << queue.at(i).GetId() << " wins the lottery!" << std::endl;
                    break;
                }
            }
        }

        int GetSize() {
            return queue.size();
        }

    private:
        std::vector<Process> queue;
        int totalTickets;

};

int main() {
    // Get the number of processes from the user
    int numProcesses;
    std::cout << "Choose the number of processes: ";
    std::cin >> numProcesses;

    // Get the number of tickets from the user
    int numTickets;
    std::cout << "Choose the number of tickets for each process: ";
    std::cin >> numTickets;

    // Add the processes to the queue
    Scheduler scheduler;
    for (int i = 1; i <= numProcesses; ++i) {
        scheduler.AddProcess(i);
    }

    // Allocate the tickets to each process
    scheduler.AllocateTickets(numTickets);

    // Query the user about running the lottery immediately
    char response;
    std::cout << "Run the lottery? Y/N: ";
    std::cin >> response;
    if (response == 'Y' || response == 'y'){
        scheduler.RunLottery();
    } else if  (response == 'N' || response == 'n') {
        std::cout << "Continuing..." << std::endl;
    } else {
        std::cerr << "Unexpected response, lottery will not run.";
    }

    int choice;

    // Main menu loop
    do {

        // Get choice from user
        std::cout << std::endl << std::endl << "1: Add more processes\n2: Add more tickets\n3: Run the lottery\n4: Add tickets to a specific process\n5: Exit\n\nChoose an option: ";
        std::cin >> choice;

        switch (choice) {
            case 1: { 
                // Get number of processes to add and add them to the queue
                int numProcesses;
                std::cout << "Choose the number of processes to add: ";
                std::cin >> numProcesses;
                for (int i = 1; i <= numProcesses; ++i) {
                    scheduler.AddProcess(1 + scheduler.GetSize());
                }     
                std::cout << std::endl << numProcesses << " processes added." << std::endl; 

                // Add tickets to each added process
                int numTickets;
                std::cout << "Choose the number of tickets to add for each process: ";
                std::cin >> numTickets;    
                for (int i = 0; i < numProcesses; ++i) {
                    scheduler.AllocateTicketsToID(numTickets, scheduler.GetSize() - i);
                }
                std::cout << std::endl << numTickets * numProcesses << " tickets added." << std::endl;

                break;
            }

            case 2: {
                // Get number of tickets to add and add that amount to each process in the queue
                int numTickets;
                std::cout << "Choose the number of tickets to add for each process: ";
                std::cin >> numTickets;    
                scheduler.AllocateTickets(numTickets);
                std::cout << std::endl << numTickets * numProcesses << " tickets added." << std::endl;
                break;  
            }  

            case 3: {
                // Run the lottery!
                scheduler.RunLottery();
                break;
            }

            case 4: {
                // Add a given number of tickets to a specific existing process
                int id;
                std::cout << "Choose process id to give tickets: ";
                std::cin >> id;
                int numTickets;
                std::cout << "Choose the number of tickets to add: ";
                std::cin >> numTickets;
                scheduler.AllocateTicketsToID(numTickets, id);
                std::cout << std::endl << numTickets << " tickets added to process " << id << "." << std::endl;
                break;
            }

            case 5: {
                std::cout << "Exiting..." << std::endl;
                break;  
            }  

            default: {
                std::cerr << "Invalid selection, please try again." << std::endl;
            }
        }
    } while (choice != 5);

}