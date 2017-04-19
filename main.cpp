/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: IT10
 *
 * Created on April 3, 2017, 3:51 PM
 */

//#include "stdafx.h"
#include "windows.h"
#include "iostream"
#include "Shellapi.h"

int main() {
    using namespace std;

    HWND hwnd;
    HWND element;
    HWND browseWindow;
    HWND okButton;
    HWND browseButton;
    HWND openButton;
    HWND hwndTest;
    HWND parentWin;
    HWND desktop;
    HWND pathBox;
    char p[100];
    char name[100];
    char className[100];

    void click(HWND hwnd);
    HWND getHandleByText(HWND hwnd, char text[]);

    // Launch installer
    string s = "autocad_architecture_2012_sp2_64bit.msp";
        ::ShellExecute(0, NULL, s.c_str(), NULL, NULL, SW_RESTORE);
        if (GetLastError == 0) {
            HWND h = GetNextWindow(h, GW_HWNDNEXT);
            SetWindowPos(h, 0, 500, 10, 300, 800, SWP_SHOWWINDOW);
        }
    // /Launch installer

    hwnd = FindWindow(0, "AutoCAD Architecture 2012");

    while (hwnd == 0) {
        hwnd = FindWindow(0, "AutoCAD Architecture 2012");
        Sleep(500);
    }

    parentWin = GetParent(hwnd);

    while (parentWin == 0) {
        hwnd = FindWindow(0, "AutoCAD Architecture 2012");
        Sleep(500);
        parentWin = GetParent(hwnd);
    }

    GetWindowText(hwnd, p, 100);


    element = GetWindow(hwnd, GW_CHILD);
    

    while (element != 0) {
        GetWindowText(element, p, 100);

        cout << "label: " << p << endl;

        if (stricmp(p, "Ok") == 0 || stricmp(p, "&Ok") == 0) {
            okButton = element;
        }

        if (stricmp(p, "Browse...") == 0 || stricmp(p, "&Browse...") == 0) {
            browseButton = element;
        }

        GetClassName(element, className, 100);

        if (stricmp(className, "ComboBox") == 0) {
            pathBox = element;
      
            // path = "\\\\nasnipi\\Volume_1\\distrib\\Autodesk\\ADT_2012_64_32_Orig.Disk\\ACA2012\\x64\\ACA";
            
            while (SendMessage(pathBox, CB_DELETESTRING, 0, 0) >= 0) {
                Sleep(500);
            }
            Sleep(500);

/*
            //            SendMessage(element, WM_SETTEXT, 0, LPARAM(LPCTSTR("\\\\nasnipi\\Volume_1\\distrib\\Autodesk\\ADT_2012_64_32_Orig.Disk\\ACA2012\\x64\\ACA\\ACA.msi")));
            SendMessage(pathBox, CB_ADDSTRING, 0, LPARAM(LPCTSTR("\\\\200.200.200.194\\Volume_1\\distrib\\Autodesk\\5\\ADT_2012_64_32_Orig.Disk\\ACA2012\\x64\\ACA\\")));
            SendMessage(pathBox, CB_SELECTSTRING, 0, LPARAM(LPCTSTR("\\\\200.200.200.194\\Volume_1\\distrib\\Autodesk\\5\\ADT_2012_64_32_Orig.Disk\\ACA2012\\x64\\ACA\\")));
//            SendMessage(pathBox, WM_SETTEXT, 0, LPARAM(LPCTSTR("\\\\200.200.200.194\\Volume_1\\distrib\\Autodesk\\5\\ADT_2012_64_32_Orig.Disk\\ACA2012\\x64\\ACA\\ACA.msi")));
            
//            SendMessage(pathBox, CB_)
            SendMessage(element, CB_SETCURSEL, 0, 0);
//            WPARAM param = MAKEWPARAM(GetDlgCtrlID(pathBox), CBN_SELENDOK);
            SendMessage(hwnd, WM_COMMAND, MAKEWPARAM(GetDlgCtrlID(pathBox), CBN_SELCHANGE), (LPARAM) pathBox);
            SendMessage(hwnd, WM_COMMAND, MAKEWPARAM(GetDlgCtrlID(pathBox), CBN_SELENDOK), (LPARAM) pathBox);

            cout << "CLICK!=============" << endl;
*/
            GetWindowText(pathBox, p, 100);

            cout << p << endl;

            //            SendMessage(element, WM_COMMAND, MAKEWPARAM(1000, BN_CLICKED), (LPARAM)okButton);
            //            Sleep(5000);

            
            
            
// ClipBoard            
            
        char* source = "\\\\nasnipi\\Volume_1\\distrib\\Autodesk\\ADT_2012_64_32_Orig.Disk\\ACA2012\\x64\\ACA"; //в эту переменную нужно записать текст, который в дальнейшем поместится в буфер обмена
        //запись текста в буфер обмена
        if(OpenClipboard(hwnd) == TRUE)//открываем буфер обмена
        {
           HGLOBAL hgBuffer;
           char* chBuffer;
           EmptyClipboard(); //очищаем буфер
           hgBuffer= GlobalAlloc(GMEM_DDESHARE, strlen(source)+1);//выделяем память
           chBuffer= (char*)GlobalLock(hgBuffer); //блокируем память
           strcpy(chBuffer, source);
           GlobalUnlock(hgBuffer);//разблокируем память
           SetClipboardData(CF_TEXT, hgBuffer);//помещаем текст в буфер обмена
           CloseClipboard(); //закрываем буфер обмена
           
           cout << "sizeof(source): " << strlen(source) << endl;
           cout << "source: " << source << endl;
           cout << "chBuffer: " << chBuffer << endl;
        }
            

            SetFocus(pathBox);
        
            keybd_event(VK_LCONTROL,MapVirtualKeyA(VK_CONTROL,0),0,0);
            keybd_event('V',MapVirtualKeyA('V',0),0,0);
            Sleep(10);
            keybd_event('V',MapVirtualKeyA('V',0),KEYEVENTF_KEYUP,0);
            keybd_event(VK_LCONTROL,MapVirtualKeyA(VK_CONTROL,0),KEYEVENTF_KEYUP,0);
//            Sleep(1000);
            SendMessage(element, WM_SETTEXT, 0, LPARAM(LPCTSTR("\\\\nasnipi\\Volume_1\\distrib\\Autodesk\\ADT_2012_64_32_Orig.Disk\\ACA2012\\x64\\ACA\\")));
            click(okButton);
            cout << "/CLICK===============" << endl;

            //            Sleep(1000);
            break;
        }

        element = GetWindow(element, GW_HWNDNEXT);
    }

}

void click(HWND hwnd) {
    PostMessage(hwnd, WM_ACTIVATE, WA_ACTIVE, NULL);
    PostMessage(hwnd, WM_LBUTTONDOWN, 0, 0);
    PostMessage(hwnd, WM_LBUTTONUP, 0, 0);
}

HWND getHandleByText(HWND parent, char text[]) {
    using namespace std;

    HWND result;
    char txt[100];

    if (parent != 0) {
        result = GetWindow(parent, GW_CHILD);
    } else {
        result = GetDesktopWindow();
        result = GetWindow(result, GW_CHILD);
    }
    while (result != 0) {
        GetWindowText(result, txt, 100);

        cout << "txt: " << txt << endl;

        if (stricmp(txt, text) == 0)
            break;

        result = GetWindow(result, GW_HWNDNEXT);
    }

    return result;
}