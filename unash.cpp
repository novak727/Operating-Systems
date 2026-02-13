//unashSkeleton.cpp -- the basic skeleton for a unash (UNA shell) program

#include <iostream>
#include <string>

// additional libraries
#include <vector>
#include <sstream>
#include <cstring>
#include <unistd.h>
#include <sys/wait.h>
using namespace std;

string readLine();
char** tokenize(string);
void printTest(char**);
bool execute(char**);

int main()
{
    bool flag=1;
    string line;
    char** argList;

    while(flag)
    {
        cout<<"csis> ";

        line = readLine();
        argList = tokenize(line);
        //IMPORTANT: comment the next line out when done testing tokenize().
        //printTest(argList);
        //***
        flag = execute(argList);
    }

}
/*
char** tokenize(string)
    This function is responsible for accepting the command string as a parameter.
    It returns a char** pointer.  The function dynamically allocates an array of 
    char* pointers equal to the number of (space delimited) words in the command string.
    Each char* pointer is dynamically allocated to exactly store one word from the command.
    Make the string pointed to by each char* pointer is NULL terminated (C-strings).
    Make sure the array of char* pointers pointed to by the char** pointer is NULL terminated.
    (This is what will be expected by the execvp function.)    
*/
char** tokenize(string line)
{
    vector<string> tokens; // store each token
    string tempWord = ""; // placeholder variable for reading in from line with stringstream
    stringstream ss(line); // stringstream to read each word of line

    // read in each word from line into tempWord, add to tokens vector
    while (ss >> tempWord)
    {
        tokens.push_back(tempWord);
    }

    // char** from vector, +1 for null terminator
    char** args = new char*[tokens.size() + 1];

    for (int i = 0; i < tokens.size(); i++)
    {
        args[i] = new char[tokens[i].length() + 1];
        strncpy(args[i], tokens[i].c_str(), tokens[i].length()); // safe copy
        args[i][tokens[i].length()] = '\0';
    }

    // null terminate array w/ nullptr
    args[tokens.size()] = nullptr;

    return args;
}

/*
bool execute(char** args)
    This function accepts the char** that points to the array of pointers to C-strings.  
    This function uses the fork() command to fork a brand new copy of itself.
    Then, for the child process, it makes use of execvp() to overwrite itself
    with a new program.  Call execvp properly making use of the char**.
    For the parent process (still running the shell program), it waits until
    the child process is terminated.  Make use of waitpid for this. 
*/
bool execute(char** args)
{
    // for empty input
    if (args[0] == nullptr)
    {
        delete[] args;
        return true;
    }

    int i;

    // Handle exit command
    if (strncmp(args[0], "exit\0", 4) == 0)
    {
        // deallocate memory
        i = 0;
        while (args[i] != nullptr)
        {
            delete[] args[i];
            i++;
        }
        delete[] args;
        return false;
    }

    // fork process
    pid_t process = fork();

    if (process < 0)
    {
        cerr << "Fork failed" << endl;
        return true;
    }
    else if (process == 0)
    {
        int err = execvp(args[0],args);
        // execvp only returns when an error occurs
        if (err)
        {
            // deallocate memory
            i = 0;
            while (args[i] != nullptr)
            {
                delete[] args[i];
                i++;
            }
            delete[] args;
            return false;
        }
    }
    else
    {
        // parent is waiting on child
        waitpid(WAIT_MYPGRP,0,0);
    }

    // deallocate each char*
    i = 0;
    while (args[i] != nullptr)
    {
        delete[] args[i];
        i++;
    }

    // deallocate char**
    delete[] args;
    return true;
}
string readLine()
{
    string line;
    getline(cin, line);
    return line;
}
void printTest(char** temp)
{
    int counter = 0;
    while(temp[counter]!=nullptr)
    {
        cout<<temp[counter]<<endl;
        counter++;
    }
}
