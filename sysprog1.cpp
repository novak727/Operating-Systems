#include <sys/types.h>
#include <sys/sysctl.h>
#include <err.h>
#include <iostream>

using namespace std;


//printNumCPUs prints out the number of CPUs: sysctl HW_NCPU
void printNumCPUs(int[], size_t&); //I HAVE PROVIDED THIS FUNCTION

/************
 * The below function declarations are given and may not be changed.
 * Your assignment is to provide the implementations for these.
*/
//printPageSize prints out the software page size: sysctl HW_PAGESIZE
void printPageSize(int[], size_t&);

//printPhysicalMem prints out the total physical memory: sysctl HW_PHYSMEM
void printPhysicalMem(int[], size_t&);

//printMachineClass print out the machine class: sysctl HW_MACHINE
void printMachineClass(int[], size_t&, char*);

//printModel prints out the machine model: sysctl HW_MODEL
void printModel(int[], size_t&, char*);

//Do not change the main()
int main()
{
    int mib[2];
    size_t len;
    int choice=0;
    char* p;
    
    while(choice != 6)
    {
        cout<<"Options List: "<<endl;
        cout<<"  1: Number of CPUs"<<endl;
         cout<<"  2: Page Size"<<endl;
        cout<<"  3: Total Physical Memory (bytes)"<<endl;
        cout<<"  4: Machine Class"<<endl;
        cout<<"  5: Model"<<endl;    
        cout<<"  6: Quit"<<endl;
        cout<<"Make Selection: ";
        cin>>choice;
        
        switch(choice)
        {
            case 1:
                printNumCPUs(mib, len);
                break;
            case 2: 
                printPageSize(mib, len);
                break;
            case 3:
                printPhysicalMem(mib, len);
                break;
            case 4: 
                printMachineClass(mib, len, p);
                break;
            case 5:
                printModel(mib, len, p);
                break;
            default:
                cout<<endl;
                cout<<"Good bye!"<<endl;
        }
    }
}

void printNumCPUs(int mib[], size_t& len)
{
    int cpuCount;
    
    mib[0] = CTL_HW;
    mib[1] = HW_NCPU;
    
    len = sizeof cpuCount;
    
    if(sysctl(mib, 2, &cpuCount, &len, nullptr, 0) == -1)
    {
        err(1, "sysctl");
    }
    else
    {
        cout<<endl;
        cout<<"********"<<endl;
        cout<<"Number of CPUs: "<< cpuCount << endl;
        cout<<endl;
    }
    return;
}
void printPageSize(int mib[], size_t& len)
{
    int pageSize;

    mib[0] = CTL_HW;
    mib[1] = HW_PAGESIZE;

    len = sizeof pageSize;

    if(sysctl(mib, 2, &pageSize, &len, nullptr, 0) == -1)
    {
        err(1, "sysctl");
    }
    else
    {
        cout << endl;
        cout << "********" << endl;
        cout << "Software Page Size: " << pageSize << endl;
        cout << endl;
    }
    return;
}
void printPhysicalMem(int mib[], size_t& len)
{
    int64_t physMem;

    mib[0] = CTL_HW;
    mib[1] = HW_PHYSMEM64;

    len = sizeof physMem;

    if(sysctl(mib, 2, &physMem, &len, nullptr, 0) == -1)
    {
        err(1, "sysctl");
    }
    else
    {
        cout << endl;
        cout << "********" << endl;
        cout << "Total Physical Memory (in bytes): " << physMem << endl;
        cout << endl;
    }
    return;
}
void printMachineClass(int mib[], size_t& len, char* p)
{
    mib[0] = CTL_HW;
    mib[1] = HW_MACHINE;

    if (sysctl(mib, 2, nullptr, &len, nullptr, 0) == -1)
    {
        err(1, "sysctl");
    }
    else
    {
        p = (char*)malloc(len);

        if(sysctl(mib, 2, p, &len, nullptr, 0) == -1)
        {
            err(1, "sysctl");
        }
        else
        {
            cout << endl;
            cout << "********" << endl;
            cout << "Machine Class: " << p << endl;
            cout << endl;
        }
        free(p);
    }
    return;
}
void printModel(int mib[], size_t& len, char* p)
{
    mib[0] = CTL_HW;
    mib[1] = HW_MODEL;

    if (sysctl(mib, 2, nullptr, &len, nullptr, 0) == -1)
    {
        err(1, "sysctl");
    }
    else
    {
        p = (char*)malloc(len);

        if(sysctl(mib, 2, p, &len, nullptr, 0) == -1)
        {
            err(1, "sysctl");
        }
        else
        {
            cout << endl;
            cout << "********" << endl;
            cout << "Machine Model: " << p << endl;
            cout << endl;
        }
        free(p);
    }
    return;
}
