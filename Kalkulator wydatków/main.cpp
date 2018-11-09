#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <cstdlib>
#include <string>
#include <math.h>
#include <objbase.h>
#include <CommCtrl.h>
#include <fstream>

////////////////////////////////////

#define MENU_ZAMKNIJ 2
#define MENU_WYDATEK 3
#define MENU_DOCHOD 4
#define MENU_POMOC 5
#define MENU_OSIAGNIECIA 6
#define BUTTON_DOCHOD 7
#define BUTTON_WYDATEK 8
#define WYCZYSC_PORTFEL 9


////////////////////////////////////


using namespace std;

void ZapisPortfel();
void ZapisDochody();
void ZapisWydatki();
void HistoriaDochody();
void ZapisHistoriiD();
void ZapisHistoriiW();
fstream plik_portfel;


int liczba_klikow_D;
int liczba_klikow_W;
char tytul[20];
char portfel[10], zmiana[10];
float portfel_f, zmiana_f;



LRESULT CALLBACK WindowProcedure(HWND,UINT,WPARAM,LPARAM);

void DodajObrazki();

void DodajMenu(HWND);

void DodajKontrolki(HWND hWnd);

void DodajComboBox(HWND);

void IlePortfel();



HWND hStan;
HWND hTytul;
HWND hWartosc;
HWND hLogo;
HWND hDochodButton, hWydatekButton;
///////////////////////
HWND hHistoriaW, hHistoriaD;
/////////////////////// DO WYSWIELTANIA HISTORII
HWND hDochod1;
HWND hDochod2;
HWND hDochod3,hDochod4,hDochod5;
HWND hWydatek1,hWydatek2,hWydatek3,hWydatek4,hWydatek5;
HWND hTytulD1,hTytulD2,hTytulD3,hTytulD4,hTytulD5;
HWND hTytulW1,hTytulW2,hTytulW3,hTytulW4,hTytulW5;

/////
//HWND hComboBox;                       <-------- Combobox


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

        CreateWindowW(L"MojeOknoKlasa",L"ZAKUPOHOLIK",WS_OVERLAPPEDWINDOW | WS_VISIBLE,100,100,500,600, NULL,NULL,NULL,NULL);

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
                    GetWindowText(hStan,portfel,10);
                    GetWindowText(hWartosc,zmiana,10);
                    GetWindowText(hTytul, tytul,20);
                    liczba_klikow_D++;
                    for(int i = 0; i<10; i++) // ZAMIANA PRZECINKA NA KROPKĘ
                    {
                        if(zmiana[i] == ',')
                        {
                            zmiana[i] = '.';
                        }
                    }
                    portfel_f = atof(portfel);
                    zmiana_f = atof(zmiana);

                 //FUNKCJA PRZYJMUJĄCA TYLKO CYFRY I ZNAKI , . JAKIŚ PRZYPAU
//                     for(int i = 0;i<10;i++)
//                    {
//                        if(zmiana[i]>=44 && zmiana[i]<=57)
//                        {
//                            continue;
//                        }
//                        else
//                        {
//                            zmiana_f = 0;
//                           SetWindowText(hWartosc,"");
//                        SetWindowText(hStan, portfel);
//                            break;
//                        }
//                    }
                    portfel_f += zmiana_f;
                    sprintf(portfel,"%.2f",portfel_f);
                    SetWindowText(hStan, portfel);
                   // HistoriaDochody();
                    ZapisHistoriiD();
                    ZapisDochody();
                    ZapisPortfel();

                       break;


                case BUTTON_WYDATEK:
                    GetWindowText(hStan,portfel,10);   // Odczyt tekstu z okna Stan Konta:
                    GetWindowText(hWartosc,zmiana,10); // Odczyt wartości wpisanej w okno Kwota
                    GetWindowText(hTytul,tytul,20);
                    liczba_klikow_W++;
                    for(int i = 0; i<10; i++) // ZAMIANA PRZECINKA NA KROPKĘ
                    {
                        if(zmiana[i] == ',')
                        {
                            zmiana[i] = '.';
                        }
                    }
                    portfel_f = atof(portfel);         // Użycie funkcji atof na Stanie Portfela w celu zamiany znaków cyfr na cyfry, aby móc liczyć
                    zmiana_f = atof(zmiana);           // Użycie funkcji atof na Kwocie
                    portfel_f -= zmiana_f;             // Odjęcie Kwoty od Stanu Portfela
                    sprintf(portfel,"%.2f",portfel_f);
                    SetWindowText(hStan, portfel);
                    ZapisHistoriiW();
                    ZapisWydatki();
                    ZapisPortfel();

                       break;

                case WYCZYSC_PORTFEL:
                    portfel_f = 0;
                    sprintf(portfel,"%.2f",portfel_f);
                    SetWindowText(hStan, portfel);
                    break;






            }


        break;
    case WM_CREATE:
        DodajObrazki();
        DodajMenu(hWnd);
        DodajKontrolki(hWnd);
        IlePortfel();
     //   DodajComboBox(hWnd);       <-------- Combobox
        break;
    case WM_DESTROY:
        ZapisPortfel();
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
    AppendMenu(hMenuPlikow,MF_STRING,WYCZYSC_PORTFEL,"Wyczysc");
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
    CreateWindowW(L"Static", L"STAN KONTA", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 200, 25, 100, 50, hWnd, NULL, NULL,NULL);

    hStan = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD  | SS_CENTER, 201, 48, 98, 24, hWnd, NULL, NULL,NULL);

    CreateWindowW(L"Static", L"KWOTA: ", WS_VISIBLE | WS_CHILD | SS_CENTER, 150, 145, 60, 25, hWnd, NULL, NULL,NULL);

    hWartosc = CreateWindowW(L"Edit",L" ", WS_VISIBLE | WS_CHILD | WS_BORDER, 220, 145, 100, 25, hWnd, NULL, NULL, NULL);  // OKIENKO DO WPISYWANIA WARTOŚCI DOCHODU/WYDATKU

    CreateWindowW(L"Static", L"TYTUL: ", WS_VISIBLE | WS_CHILD | SS_CENTER, 150, 180, 60, 25, hWnd, NULL, NULL,NULL);

    hTytul = CreateWindowW(L"Edit",L" ", WS_VISIBLE | WS_CHILD | WS_BORDER, 220, 180, 100, 25, hWnd, NULL, NULL, NULL);

    hWydatekButton = CreateWindowW(L"Button", L"WYDATEK", WS_VISIBLE | WS_CHILD | BS_BITMAP, 35, 225, 75, 50, hWnd, (HMENU)BUTTON_WYDATEK, NULL, NULL);
    SendMessageW(hWydatekButton, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hWydatekObrazek);

    hDochodButton = CreateWindowW(L"Button", L"DOCHOD", WS_VISIBLE | WS_CHILD | BS_BITMAP, 35, 150, 75, 50, hWnd, (HMENU)BUTTON_DOCHOD, NULL, NULL);
    SendMessageW(hDochodButton, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hDochodObrazek);

    hLogo = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD  | SS_BITMAP, 25, 25, 100, 50, hWnd, NULL, NULL,NULL);
    SendMessageW(hLogo, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hDodajObrazki);

    CreateWindowW(L"Static", L"SEPARATOREM JEST KROPKA!!!", WS_VISIBLE | WS_CHILD | SS_CENTER, 125, 230, 250, 50, hWnd, NULL, NULL,NULL);




    //////////////// DOCHODY KWOTA

    hHistoriaD = CreateWindowW(L"Static", L"DOCHODY", WS_VISIBLE | WS_CHILD | SS_CENTER, 25, 325, 200, 25, hWnd, NULL, NULL,NULL);

    hDochod1 = CreateWindowW(L"Static", NULL,  WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 25, 378, 100, 25, hWnd, NULL, NULL,NULL);
    hDochod2 = CreateWindowW(L"Static", NULL,  WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 25, 406, 100, 25, hWnd, NULL, NULL,NULL);
    hDochod3 = CreateWindowW(L"Static", NULL,  WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 25, 434, 100, 25, hWnd, NULL, NULL,NULL);
    hDochod4 = CreateWindowW(L"Static", NULL,  WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 25, 462, 100, 25, hWnd, NULL, NULL,NULL);
    hDochod5 = CreateWindowW(L"Static", NULL,  WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 25, 490, 100, 25, hWnd, NULL, NULL,NULL);

    /////////////////////////////////////// TYTUŁY DOCHODY

    hTytulD1 = CreateWindowW(L"Static", NULL,  WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 128, 378, 100, 25, hWnd, NULL, NULL,NULL);
    hTytulD2 = CreateWindowW(L"Static", NULL,  WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 128, 406, 100, 25, hWnd, NULL, NULL,NULL);
    hTytulD3 = CreateWindowW(L"Static", NULL,  WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 128, 434, 100, 25, hWnd, NULL, NULL,NULL);
    hTytulD4 = CreateWindowW(L"Static", NULL,  WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 128, 462, 100, 25, hWnd, NULL, NULL,NULL);
    hTytulD5 = CreateWindowW(L"Static", NULL,  WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 128, 490, 100, 25, hWnd, NULL, NULL,NULL);

    /////////////////////////////////////////////////// WYDATKI KWOTA

    hHistoriaW = CreateWindowW(L"Static", L"WYDATKI", WS_VISIBLE | WS_CHILD | SS_CENTER, 255, 325, 200, 25, hWnd, NULL, NULL,NULL);
    hWydatek1 = CreateWindowW(L"Static", NULL,  WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 255, 378, 100, 25, hWnd, NULL, NULL,NULL);
    hWydatek2 = CreateWindowW(L"Static", NULL,  WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 255, 406, 100, 25, hWnd, NULL, NULL,NULL);
    hWydatek3 = CreateWindowW(L"Static", NULL,  WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 255, 434, 100, 25, hWnd, NULL, NULL,NULL);
    hWydatek4 = CreateWindowW(L"Static", NULL,  WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 255, 462, 100, 25, hWnd, NULL, NULL,NULL);
    hWydatek5 = CreateWindowW(L"Static", NULL,  WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 255, 490, 100, 25, hWnd, NULL, NULL,NULL);

    ///////////////////////////////////// TYTULY WYDATKI
    hTytulW1 = CreateWindowW(L"Static", NULL,  WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 358, 378, 100, 25, hWnd, NULL, NULL,NULL);
    hTytulW2 = CreateWindowW(L"Static", NULL,  WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 358, 406, 100, 25, hWnd, NULL, NULL,NULL);
    hTytulW3 = CreateWindowW(L"Static", NULL,  WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 358, 434, 100, 25, hWnd, NULL, NULL,NULL);
    hTytulW4 = CreateWindowW(L"Static", NULL,  WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 358, 462, 100, 25, hWnd, NULL, NULL,NULL);
    hTytulW5 = CreateWindowW(L"Static", NULL,  WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 358, 490, 100, 25, hWnd, NULL, NULL,NULL);
}


void DodajObrazki()
{
        hDodajObrazki = (HBITMAP)LoadImageW(NULL, L"nowelogo.bmp", IMAGE_BITMAP,0,0, LR_LOADFROMFILE);

        hDochodObrazek = (HBITMAP)LoadImageW(NULL, L"dochodbutton.bmp", IMAGE_BITMAP, 0,0, LR_LOADFROMFILE);

        hWydatekObrazek = (HBITMAP)LoadImageW(NULL, L"wydatekbutton.bmp", IMAGE_BITMAP, 0,0, LR_LOADFROMFILE);
}

// <-------- Combobox
//void DodajComboBox(HWND hWnd)
//{
//     hComboBox = CreateWindowW(L"ComboBox", L"HISTORIA", CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE, 200, 300, 100, 100, hWnd, NULL, NULL,NULL);
//
//
//}


void ZapisWydatki()
{
    fstream plik_wydatki;
    plik_wydatki.open("Wydatki.txt", ios::out | ios::app);
    plik_wydatki<<zmiana_f;
    plik_wydatki<<tytul<<endl;
    plik_wydatki.close();
}

//void ZapisDochody() dobra funckja
//{
//    fstream plik_dochody;
//    plik_dochody.open("Dochody.txt", ios::out | ios::app);
//    plik_dochody<<zmiana_f;
//    plik_dochody<<tytul<<endl;
//    plik_dochody.close();
//}

void ZapisDochody()
{
    fstream plik_dochody;
    plik_dochody.open("Dochody.txt", ios::out | ios::app);
    plik_dochody<<zmiana_f<<endl;
    plik_dochody.close();

    fstream plik_dochodytytul;
    plik_dochodytytul.open("DochodyTytuly.txt", ios::out | ios::app);
    plik_dochodytytul<<tytul<<endl;
    plik_dochodytytul.close();
}

void ZapisPortfel()
{
    fstream plik_portfel;
    plik_portfel.open("Stan Konta.txt", ios::out);
    plik_portfel<<portfel<<endl;
    plik_portfel.close();
}

void IlePortfel()
{
    fstream plik_portfel;
    plik_portfel.open("Stan Konta.txt", ios::in);
    if(plik_portfel.good()== false)
    {
        cout << "Nie mozna zaladowac stanu konta!" <<endl;
        exit(0);
    }
    else
    {
            plik_portfel >> portfel;
            SetWindowText(hStan, portfel);
    }
    }




//void HistoriaDochody()
//{
//
//    fstream plik_dochody;
//
//    plik_dochody.open("Dochody.txt", ios::in);
//
//    if(plik_dochody.good()== false)
//        {
//            cout << "Nie mozna zaladowac historii dochodow!" <<endl;
//            exit(0);
//        }
//    else
//        {
//         while(!plik_dochody.eof())
//         {
//            plik_dochody >> dochodzik;
//            SetWindowText(hDochod1, dochodzik);
//         }
//
//        }
//}



///////////////////////////////////////////////////////////// WYSWIETLANIE HISTORII DOCHODOW
void ZapisHistoriiD()
{

            switch(liczba_klikow_D)
            {
            case 1:
                GetWindowText(hWartosc, zmiana,10);
                GetWindowText(hTytul, tytul,20);
                for(int i = 0; i<10; i++) // ZAMIANA PRZECINKA NA KROPKĘ
                    {
                        if(zmiana[i] == ',')
                        {
                            zmiana[i] = '.';
                        }
                    }
                SetWindowText(hDochod1, zmiana);
                SetWindowText(hTytulD1, tytul);
                break;

            case 2:
                GetWindowText(hWartosc, zmiana,10);
                GetWindowText(hTytul, tytul,20);
                for(int i = 0; i<10; i++) // ZAMIANA PRZECINKA NA KROPKĘ
                    {
                        if(zmiana[i] == ',')
                        {
                            zmiana[i] = '.';
                        }
                    }
                SetWindowText(hDochod2, zmiana);
                SetWindowText(hTytulD2, tytul);
                break;
            case 3:
                GetWindowText(hWartosc, zmiana,10);
                GetWindowText(hTytul, tytul,20);
                for(int i = 0; i<10; i++) // ZAMIANA PRZECINKA NA KROPKĘ
                    {
                        if(zmiana[i] == ',')
                        {
                            zmiana[i] = '.';
                        }
                    }
                SetWindowText(hDochod3, zmiana);
                SetWindowText(hTytulD3, tytul);
                break;
            case 4:
                GetWindowText(hWartosc, zmiana,10);
                GetWindowText(hTytul, tytul,20);
                for(int i = 0; i<10; i++) // ZAMIANA PRZECINKA NA KROPKĘ
                    {
                        if(zmiana[i] == ',')
                        {
                            zmiana[i] = '.';
                        }
                    }
                SetWindowText(hDochod4, zmiana);
                SetWindowText(hTytulD4, tytul);
                break;
            case 5:
                GetWindowText(hWartosc, zmiana,10);
                GetWindowText(hTytul, tytul,20);
                for(int i = 0; i<10; i++) // ZAMIANA PRZECINKA NA KROPKĘ
                    {
                        if(zmiana[i] == ',')
                        {
                            zmiana[i] = '.';
                        }
                    }
                SetWindowText(hDochod5, zmiana);
                SetWindowText(hTytulD5, tytul);
                liczba_klikow_D = 0;

                break;

            }
        }
/////////////////////////////////////////////////////////////  WYSWIETLANIE HISTORII WYDATKOW
void ZapisHistoriiW()
{

            switch(liczba_klikow_W)
            {
            case 1:
                GetWindowText(hWartosc, zmiana,10);
                GetWindowText(hTytul, tytul,20);
                for(int i = 0; i<10; i++) // ZAMIANA PRZECINKA NA KROPKĘ
                    {
                        if(zmiana[i] == ',')
                        {
                            zmiana[i] = '.';
                        }
                    }
                SetWindowText(hWydatek1, zmiana);
                SetWindowText(hTytulW1, tytul);
                break;

            case 2:
                GetWindowText(hWartosc, zmiana,10);
                GetWindowText(hTytul, tytul,20);
                for(int i = 0; i<10; i++) // ZAMIANA PRZECINKA NA KROPKĘ
                    {
                        if(zmiana[i] == ',')
                        {
                            zmiana[i] = '.';
                        }
                    }
                SetWindowText(hWydatek2, zmiana);
                SetWindowText(hTytulW2, tytul);
                break;
            case 3:
                GetWindowText(hWartosc, zmiana,10);
                GetWindowText(hTytul, tytul,20);
                for(int i = 0; i<10; i++) // ZAMIANA PRZECINKA NA KROPKĘ
                    {
                        if(zmiana[i] == ',')
                        {
                            zmiana[i] = '.';
                        }
                    }
                SetWindowText(hWydatek3, zmiana);
                SetWindowText(hTytulW3, tytul);
                break;
            case 4:
                GetWindowText(hWartosc, zmiana,10);
                GetWindowText(hTytul, tytul,20);
                for(int i = 0; i<10; i++) // ZAMIANA PRZECINKA NA KROPKĘ
                    {
                        if(zmiana[i] == ',')
                        {
                            zmiana[i] = '.';
                        }
                    }
                SetWindowText(hWydatek4, zmiana);
                SetWindowText(hTytulW4, tytul);
                break;
            case 5:
                GetWindowText(hWartosc, zmiana,10);
                GetWindowText(hTytul, tytul,20);
                for(int i = 0; i<10; i++) // ZAMIANA PRZECINKA NA KROPKĘ
                    {
                        if(zmiana[i] == ',')
                        {
                            zmiana[i] = '.';
                        }
                    }
                SetWindowText(hWydatek5, zmiana);
                SetWindowText(hTytulW5, tytul);
                liczba_klikow_W = 0;

                break;

            }
        }



//void ZamianaPrzecinka()
//{
//  string przecinek(" , ");
//przecinek.replace(1,3, " . ");
//}
