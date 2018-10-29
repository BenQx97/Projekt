#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <cstdlib>
////////////////////////////////////

#define MENU_ZAMKNIJ 2
#define MENU_WYDATEK 3
#define MENU_DOCHOD 4
#define MENU_POMOC 5
#define MENU_OSIAGNIECIA 6
#define BUTTON_DOCHOD 7
#define BUTTON_WYDATEK 8


////////////////////////////////////


using namespace std;

//double dochod;

//char wartosc[30];
// portfel = 0;
//char portfel_char[100] = {0};

/////

char portfel[10], zmiana[10];
float portfel_f, zmiana_f;



LRESULT CALLBACK WindowProcedure(HWND,UINT,WPARAM,LPARAM);

void DodajObrazki();

void DodajMenu(HWND);

void DodajKontrolki(HWND hWnd);


HWND hKwota;
HWND hStan;
HWND hWartosc;
HWND hLogo;
HWND hDochodButton, hWydatekButton;

HBITMAP hDodajObrazki, hDochodObrazek,hWydatekObrazek;


HMENU hMenu;

int WINAPI WinMain(HINSTANCE hInst , HINSTANCE hPrevInst, LPSTR args, int ncmdshow)
{
    WNDCLASSW wc = {0};
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW ;
    wc.hCursor = LoadCursor(NULL,IDC_ARROW);
    wc.hInstance = hInst;
    wc.lpszClassName = L"MojeOknoKlasa"; // dla lpsz zawsze L z prefixem
    wc.lpfnWndProc = WindowProcedure;

    if(!RegisterClassW(&wc))
        return -1;

        CreateWindowW(L"MojeOknoKlasa",L"ZAKUPOHOLIK",WS_OVERLAPPEDWINDOW | WS_VISIBLE,100,100,500,500, NULL,NULL,NULL,NULL);

        MSG msg = {0};


        while( GetMessage(&msg,NULL,NULL,NULL) )
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    MessageBox(NULL,"DO NASTEPNEGO RAZU!","Kalkulator wydatkow",MB_OK); // OKNO POJAWIAJĄCE SIĘ PO ZAKOŃCZENIU PROGRAMU
    return 0;
}

///////////////////////////////////////////////////////////////////////// FUNKCJONALNOŚĆ PROGRAMU

LRESULT CALLBACK WindowProcedure(HWND hWnd,UINT msg,WPARAM wp,LPARAM lp)
{
    switch (msg)
    {
    case WM_COMMAND:

            switch(wp)
            {

                case MENU_ZAMKNIJ:
                    DestroyWindow(hWnd);
                    break;

                case MENU_WYDATEK:
                    MessageBeep(MB_ICONINFORMATION);
                    break;

                case MENU_DOCHOD:
                    MessageBeep(MB_APPLMODAL);
                    break;

                case MENU_POMOC:
                    MessageBeep(MB_CUR_MAX);
                    break;

                case BUTTON_DOCHOD:
                  //  char portfel[10], zmiana[10];
                 //   float portfel_f, zmiana_f;
                    GetWindowText(hStan,portfel,10);
                    GetWindowText(hWartosc,zmiana,10);
                    portfel_f = atof(portfel);
                    zmiana_f = atof(zmiana);
                    portfel_f += zmiana_f;
                    sprintf(portfel,"%.2f",portfel_f);
                    SetWindowText(hStan, portfel);

                       break;


                case BUTTON_WYDATEK:
                  //  char portfel[10], zmiana[10];
                 //   float portfel_f, zmiana_f;
                    GetWindowText(hStan,portfel,10);
                    GetWindowText(hWartosc,zmiana,10);
                    portfel_f = atof(portfel);
                    zmiana_f = atof(zmiana);
                    portfel_f -= zmiana_f;
                    sprintf(portfel,"%.2f",portfel_f);
                    SetWindowText(hStan, portfel);

                       break;





                       /*) char kwota[30], stan[30];
                        GetWindowText(hKwota, kwota, 30);

                        strcpy(stan, kwota);
                        strcat(stan, " zl");

                        SetWindowText(hStan, stan); *
                        break; */



            }


        break;
    case WM_CREATE:
        DodajObrazki();
        DodajMenu(hWnd);
        DodajKontrolki(hWnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProcW(hWnd,msg,wp,lp);
    }
}


void DodajMenu(HWND hWnd)
{
    hMenu = CreateMenu();
    HMENU hMenuPlikow = CreateMenu();
    HMENU hDrugieMenu = CreateMenu();
    HMENU hRankingD = CreateMenu();
    HMENU hRankingW = CreateMenu();

    AppendMenu(hMenuPlikow,MF_STRING,MENU_WYDATEK,"Wydatek");
    AppendMenu(hMenuPlikow,MF_SEPARATOR,NULL,NULL);
    AppendMenu(hMenuPlikow,MF_STRING,MENU_DOCHOD,"Dochod");
    AppendMenu(hMenuPlikow,MF_SEPARATOR,NULL,NULL);

    //////////////////////////////////////////////////////////

    AppendMenu(hDrugieMenu,MF_POPUP,(UINT_PTR)hRankingW,"Wydatki");

    AppendMenu(hRankingW,MF_STRING,NULL, "Ogolny");

    AppendMenu(hRankingW,MF_STRING,NULL, "Dzienny");

    AppendMenu(hDrugieMenu,MF_POPUP,(UINT_PTR)hRankingD,"Dochody");

    AppendMenu(hRankingD,MF_STRING,NULL, "Ogolny");

    AppendMenu(hRankingD,MF_STRING,NULL, "Dzienny");





   //////////////////////////////////////////////


    AppendMenu(hMenuPlikow,MF_SEPARATOR,NULL,NULL);

    AppendMenu(hMenu,MF_POPUP,(UINT_PTR)hMenuPlikow,"Portfel");

    AppendMenu(hMenu,MF_POPUP,(UINT_PTR)hDrugieMenu,"Ranking");

    AppendMenu(hMenu,MF_STRING,MENU_OSIAGNIECIA,"Osiagniecia");

    AppendMenu(hMenu,MF_STRING,MENU_POMOC,"Pomoc");

    AppendMenu(hMenu,MF_STRING,MENU_ZAMKNIJ,"Zamknij");

    SetMenu(hWnd, hMenu);
}

void DodajKontrolki(HWND hWnd)
{
    CreateWindowW(L"Static", L"STAN KONTA", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 200, 85, 100, 50, hWnd, NULL, NULL,NULL);

    hStan = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD  | SS_CENTER, 201, 110, 98, 24, hWnd, NULL, NULL,NULL);

    hWartosc = CreateWindowW(L"Edit",L" ", WS_VISIBLE | WS_CHILD, 200, 145, 100, 25, hWnd, NULL, NULL, NULL);  // OKIENKO DO WPISYWANIA WARTOŚCI DOCHODU/WYDATKU

    hWydatekButton = CreateWindowW(L"Button", L"WYDATEK", WS_VISIBLE | WS_CHILD | BS_BITMAP, 150, 205, 75, 50, hWnd, (HMENU)BUTTON_WYDATEK, NULL, NULL);
    SendMessageW(hWydatekButton, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hWydatekObrazek);

    hDochodButton = CreateWindowW(L"Button", L"DOCHOD", WS_VISIBLE | WS_CHILD | BS_BITMAP, 275, 205, 75, 50, hWnd, (HMENU)BUTTON_DOCHOD, NULL, NULL);
    SendMessageW(hDochodButton, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hDochodObrazek);

    hLogo = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD  | SS_BITMAP, 150, 15, 100, 50, hWnd, NULL, NULL,NULL);
    SendMessageW(hLogo, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hDodajObrazki);

    CreateWindowW(L"Static", L"SEPARATOREM JEST KROPKA!!!", WS_VISIBLE | WS_CHILD | SS_CENTER, 125, 350, 250, 50, hWnd, NULL, NULL,NULL);

}


void DodajObrazki()
{
        hDodajObrazki = (HBITMAP)LoadImageW(NULL, L"logoapki.bmp", IMAGE_BITMAP,0,0, LR_LOADFROMFILE);

        hDochodObrazek = (HBITMAP)LoadImageW(NULL, L"dochodbutton.bmp", IMAGE_BITMAP, 0,0, LR_LOADFROMFILE);

        hWydatekObrazek = (HBITMAP)LoadImageW(NULL, L"wydatekbutton.bmp", IMAGE_BITMAP, 0,0, LR_LOADFROMFILE);
}
