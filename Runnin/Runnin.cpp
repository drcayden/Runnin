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

using namespace std;

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
            std::cout << "Info: Reinstall Microsoft Windows to fix this problem" << std::endl;
            nRetCode = 1;
        }
        else
        {
            // TODO: code your application's behavior here.
            std::cout << "Info: MFC initializtion succeeded" << std::endl;

            int count = 0;

            CFile fileRead;
            CFile fileWrite;

            fileRead.Open(L"count.rin", CFile::modeRead);
            if (fileRead) {
                CArchive arWrite(&fileRead, CArchive::load);

                arWrite >> count;

                arWrite.Close();
                fileRead.Close();
            }
            else {
                wprintf(L"Fatal Error: Failed to open count.rin\n");
                nRetCode = 1;
            }

            fileWrite.Open(L"count.rin", CFile::modeCreate | CFile::modeWrite);
            CArchive arRead(&fileWrite, CArchive::store);
            arRead << count + 8;

            arRead.Close();
            fileWrite.Close();

            std::cout << count << std::endl;
        }
    }
    else
    {
        // TODO: change error code to suit your needs
        wprintf(L"Fatal Error: GetModuleHandle failed\n");
        std::cout << "Info: Reinstall Microsoft Windows to fix this problem" << std::endl;
        nRetCode = 1;
    }

    return nRetCode;
}
