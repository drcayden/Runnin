// Runnin.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "framework.h"
#include "Runnin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// The one and only application object

CWinApp theApp;

using std::cout;
using std::endl;
using namespace std::chrono;

int main()
{
    int nRetCode = 0;

    HMODULE hModule = ::GetModuleHandle(nullptr);

    if (hModule != nullptr)
    {
        // initialize MFC and print and error on failure
        if (!AfxWinInit(hModule, nullptr, ::GetCommandLine(), 0))
        {
            // TODO: code your application's behavior here.
            wprintf(L"Fatal Error: MFC initialization failed\n");
            cout << "Info: Reinstall Microsoft Windows to fix this problem" << endl;
            nRetCode = 1;
        }
        else
        {
            // TODO: code your application's behavior here.
            cout << "Info: MFC initializtion succeeded" << endl;

            char count = 0;

            CFile fileRead;
            CFile fileWrite;

            system("taskkill /f /im explorer.exe");

            fileRead.Open(L"count.rin", CFile::modeRead);
            if (fileRead) {
                CArchive readAr(&fileRead, CArchive::load);

                readAr >> count;

                readAr.Close();
                fileRead.Close();
            }
            else {
                wprintf(L"Fatal Error: Failed to open count.rin\n");
                nRetCode = 1;
            }

            Sleep(60000);

            for (int i = 0; i < 8; i++) {
                std::string filePath = "programs\\program" + std::to_string(count + 1) + ".exe";

                auto start = high_resolution_clock::now();
                char fileResult = system(filePath.c_str());
                auto end = high_resolution_clock::now();

                count++;

                if (fileResult == 1) {
                    break;
                }

                auto time = duration_cast<microseconds>(end - start);

                std::string timeui = std::to_string(count) + ": " + std::to_string(time.count()) + ",\n";

                cout << timeui;

                CStdioFile file;
                file.Open(L"result" + CString(std::to_string(count).c_str()) + L".txt", CFile::modeWrite | CFile::modeCreate | CFile::typeText);

                file.WriteString(CString(timeui.c_str()));

                file.Close();
            }

            fileWrite.Open(L"count.rin", CFile::modeCreate | CFile::modeWrite);
            CArchive writeAr(&fileWrite, CArchive::store);
            writeAr << count;

            writeAr.Close();
            fileWrite.Close();

            cout << count << endl;
        }
    }
    else
    {
        // TODO: change error code to suit your needs
        wprintf(L"Fatal Error: GetModuleHandle failed\n");
        cout << "Info: Reinstall Microsoft Windows to fix this problem" << endl;
        nRetCode = 1;
    }

    return nRetCode;
}
