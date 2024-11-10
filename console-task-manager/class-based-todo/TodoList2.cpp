#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
using namespace std;

class fileManager
{
    vector<string> tasks;
    string st, st2, task;

public:
    void addSentence()
    {
        ofstream out("sampleFile.txt", ios::app);
        if (!out)
        {
            cerr << "Error: Could not open file for writing!" << endl;
            return;
        }

        cout << "Enter a task: " << endl;
        getline(cin, st); 
        out << st << endl;
        out.close();
        tasks.push_back(st); // Keep task in vector as well
    }
    void viewContent()
    {
        cout << "\nDisplaying your task:\n";
        ifstream in("sampleFile.txt");

        while (getline(in, st2)) // in>>st2;
        {
            cout << "- " << st2 << endl;
        }
        in.close();
    }

    void clearAll()
    {
        ofstream out("sampleFile.txt", ios::trunc);
        if (!out)
        {
            cerr << "Error: Could not open file for writing!" << endl;
            return;
        }
        out.close();
        tasks.clear(); // Clear tasks in the vector as well
    }

    void removeContent(const string &taskToRemove);
};

void fileManager::removeContent(const string &taskToRemove)
{
    ifstream in("sampleFile.txt");
    if (!in)
    {
        cerr << "Error: Could not open file for reading!" << endl;
        return;
    }

    vector<string> tempTasks;
    bool found = false; // To track if the task was found

    // Read all tasks into the vector
    while (getline(in, task))
    {
        if (task != taskToRemove) // Skip the task we want to remove
        {
            tempTasks.push_back(task); // Keep task if it's not the one to remove
        }
        else
        {
            found = true; // Task was found and skipped
        }
    }
    in.close(); // Close the file after reading

    if (!found)
    {
        cout << "The task not found in this file!" << endl;
        return;
    }

    // Open the file for writing to overwrite with updated tasks
    ofstream out("sampleFile.txt");
    if (!out)
    {
        cerr << "Error: Could not open file for writing!" << endl;
        return;
    }

    for (const auto &t : tempTasks)
    {
        out << t << endl; // Write remaining tasks back to the file
    }
    out.close(); // Close the file after writing

    // Update the vector tasks
    // tasks.clear();     // Clear current tasks
    tasks = tempTasks; // Copy updated tasks from tempTasks

    cout << "Task removed successfully!" << endl;
}

int menu()
{
    int choice;
    cout << "\nMenu:\n";
    cout << "1. Add a task\n";
    cout << "2. View all tasks\n";
    cout << "3. Remove a task\n";
    cout << "4. Clear all tasks\n";
    cout << "5. Exit\n";
    cout << "Enter your choice: ";
    cin >> choice;
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input, please enter a number.\n";
        return 0;
    }
    cin.ignore();

    return choice;
}

int main()
{
    fileManager list;
    string taskToRemove;
    int option;
    do
    {
        option = menu();
        switch (option)
        {
        case 1:
            list.addSentence();
            cout << "Task added!" << endl;
            break;
        case 2:
            list.viewContent();
            break;
        case 3:
            cout << "Enter the exact task to remove:\n";
            getline(cin, taskToRemove);
            if (taskToRemove.empty())
            {
                cout << "You must enter a task to remove." << endl;
            }
            else
            {
                list.removeContent(taskToRemove);
                cout << "Updated task list: " << endl;
                list.viewContent();
            }
            break;
        case 4:
            list.clearAll();
            cout << "All tasks has been cleared!\n";
            break;
        case 5:
            cout << "Exiting the program." << endl;
            break;

        default:
            cout << "Invalid choice, please try again." << endl;
            break;
        }
    } while (option != 5);

    return 0;
}