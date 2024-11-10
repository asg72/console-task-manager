#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

void addSentence()
{
    // Connecting out to sample file
    ofstream out("sampleFile.txt", ios::app);

    string st;
    cout << "Enter a task: " << endl;

    // To add full sentence
    getline(cin, st); // cin>>st;
    // cin.ignore();
    out << st << endl;
    out.close();
}

void viewContent()
{
    cout << "\nDisplaying your task:\n";

    ifstream in("sampleFile.txt");
    string st2;

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
}

void removeContent(const string &taskToRemove)
{
    ifstream in("sampleFile.txt");
    if (!in)
    {
        cerr << "Error: Could not open file for reading!" << endl;
        return;
    }

    vector<string> tasks;
    string task;
    bool found = false; // To track if the task was found

    // Read all tasks into the vector
    while (getline(in, task))
    {
        if (task != taskToRemove) // Skip the task we want to remove
        {
            tasks.push_back(task); // Keep task if it's not the one to remove
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

    for (const auto &t : tasks)
    {
        out << t << endl; // Write remaining tasks back to the file
    }
    out.close(); // Close the file after writing

    cout << "Task removed successfully!" << endl;
}

int main()
{
    int choice;
    string taskToRemove;
    do
    {
        cout << "\nMenu:\n";
        cout << "1. Add a task\n";
        cout << "2. View all tasks\n";
        cout << "3. Remove a task\n";
        cout << "4. Clear all tasks\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
        case 1:
            addSentence();
            cout << "Task added!" << endl;
            break;

        case 2:
            viewContent();
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
                removeContent(taskToRemove);
                cout << "Updated task list: " << endl;
                viewContent();
            }
            break;

        case 4:
            clearAll();
            cout << "All tasks has been cleared!\n";
            break;

        case 5:
            cout << "Exiting the program." << endl;
            break;

        default:
            cout << "Invalid choice, please try again." << endl;
            break;
        }
    } while (choice != 5);

    return 0;
}
