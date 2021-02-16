#include <iostream>
#include <vector>
#include <thread>
#include <windows.h>

using namespace std;
void runExe(LPCTSTR lpApplicationName);


void runExe(LPCTSTR lpApplicationName)  {
    //string msg = to_string(n) + " : " + str + "\n";
    //cout << msg  << endl;
    
    // Startup information
    STARTUPINFO si;  
    ZeroMemory( &si, sizeof(si) );
    si.cb = sizeof(si);

    // Process information
    PROCESS_INFORMATION pi;
    ZeroMemory( &pi, sizeof(pi) );

    // start the program up
    CreateProcess( lpApplicationName,   // the path
        NULL,//argv[1], // Command line
        NULL,           // Process handle not inheritable
        NULL,           // Thread handle not inheritable
        FALSE,          // Set handle inheritance to FALSE
        0,              // No creation flags
        NULL,           // Use parent's environment block
        NULL,           // Use parent's starting directory 
        &si,            // Pointer to STARTUPINFO structure
        &pi             // Pointer to PROCESS_INFORMATION structure (removed extra parentheses)
    );
    
    // Close process and thread handles. 
    CloseHandle( pi.hProcess );
    CloseHandle( pi.hThread );
}
 
int main(int argc, char* argv[]) {
    vector<string> filepaths = {
        "C:/Users/Lee/Desktop/CS776-GA-Project/GA_dalponte2016/ga.exe",
        "C:/Users/Lee/Desktop/CS776-GA-Project/GA_li2012/ga.exe",
        "C:/Users/Lee/Desktop/CS776-GA-Project/GA_silva2016/ga.exe",
        "C:/Users/Lee/Desktop/CS776-GA-Project/GA_watershed/ga.exe",
    };
    //vector<thread> threads;
 
    for (int i = 0; i < filepaths.size(); i++) {
        //threads.push_back(thread(runExe, filepaths[i].c_str()));
        cout << "Running on thread " << i << " : " << filepaths[i] << endl;

        // Startup information
        STARTUPINFO si;  
        ZeroMemory( &si, sizeof(si) );
        si.cb = sizeof(si);

        // Process information
        PROCESS_INFORMATION pi;
        ZeroMemory( &pi, sizeof(pi) );

        // start the program up
        CreateProcess( 
            filepaths[i].c_str(),   // File Path
            NULL,           // Command line
            NULL,           // Process handle not inheritable
            NULL,           // Thread handle not inheritable
            FALSE,          // Set handle inheritance to FALSE
            0,              // No creation flags
            NULL,           // Use parent's environment block
            NULL,           // Use parent's starting directory 
            &si,            // Pointer to STARTUPINFO structure
            &pi             // Pointer to PROCESS_INFORMATION structure (removed extra parentheses)
        );
        
        // Close process and thread handles. 
        CloseHandle( pi.hProcess );
        CloseHandle( pi.hThread );
        
    }

    //for (auto &th : threads) {th.join();}
    return 0;
}