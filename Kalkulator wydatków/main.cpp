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

void DodajDochod();  // PĘTLA DO ZAPISYWANIA DOCHODÓW W HISTORII
void DodajWydatek(); // PĘTLA DO ZAPISYWANIA WYDATKÓW W HISTORII


void ZapiszDochody(); //FUNKCJA ZAPISUJĄCA DOCHODY I TYTUŁY Z HISTORII DO PLIKU.TXT


void ZapisPortfel(); //
void ZapisDochody();
void ZapisWydatki();
void PokazDochody();
void ZapisHistoriiD();
void ZapisHistoriiW();
fstream plik_portfel;

string dochodzik1, dochodzik2, dochodzik3, dochodzik4, dochodzik5;

void PokazOsiagi(HWND);

void DodajObrazkiOsiagniecia();


char czarodziejski[20];
int wiersz;

void registerOsiagiClass(HINSTANCE hInst);


int liczba_klikow_D;
int liczba_klikow_W;
char tytul[20];
char portfel[10], zmiana[10];
float portfel_f, zmiana_f;
HWND oknoD[5], oknoW[5], oknoTD[5], oknoTW[5];

LRESULT CALLBACK WindowProcedure(HWND,UINT,WPARAM,LPARAM);
LRESULT CALLBACK DialogProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);

void DodajObrazki();
void ObrazkiOsiagniecia();

void DodajMenu(HWND);



void DodajKontrolki(HWND hWnd);

//void DodajComboBox(HWND);

void IlePortfel();

HWND hO2000N,hO2000T;

HWND hOsiagi;
HWND hStan;
HWND hTytul;
HWND hWartosc;
HWND hLogo;
HWND hDochodButton, hWydatekButton;
///////////////////////
HWND hHistoriaW, hHistoriaD;
/////////////////////// DO WYSWIELTANIA HISTORII
HWND hDochod1,hDochod2,hDochod3,hDochod4,hDochod5;
HWND hWydatek1,hWydatek2,hWydatek3,hWydatek4,hWydatek5;
HWND hTytulD1,hTytulD2,hTytulD3,hTytulD4,hTytulD5;
HWND hTytulW1,hTytulW2,hTytulW3,hTytulW4,hTytulW5;

//HWND hComboBox;                       <-------- Combobox


HBITMAP hDodajObrazki, hDochodObrazek,hWydatekObrazek, hOsiag2000N,hOsiag2000T;


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

        registerOsiagiClass(hInst);

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

                case MENU_OSIAGNIECIA:
                    PokazOsiagi(hWnd);
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


                    portfel_f += zmiana_f;
                    sprintf(portfel,"%.2f",portfel_f);
                    SetWindowText(hStan, portfel);
                    DodajDochod();
                   // ZapisHistoriiD();
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
                    DodajWydatek();
                    //ZapisHistoriiW();
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
        ZapiszDochody();
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


    AppendMenu(hMenuPlikow,MF_STRING,WYCZYSC_PORTFEL,"Wyczysc");


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



    //////////////// DOCHODY KWOTA

    hHistoriaD = CreateWindowW(L"Static", L"DOCHODY", WS_VISIBLE | WS_CHILD | SS_CENTER, 25, 325, 200, 25, hWnd, NULL, NULL,NULL);

    /*hDochod1*/ oknoD[0] = CreateWindowW(L"Static", NULL,  WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 25, 378, 100, 25, hWnd, NULL, NULL,NULL);
    /*hDochod2*/ oknoD[1] = CreateWindowW(L"Static", NULL,  WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 25, 406, 100, 25, hWnd, NULL, NULL,NULL);
    /*hDochod3*/ oknoD[2] = CreateWindowW(L"Static", NULL,  WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 25, 434, 100, 25, hWnd, NULL, NULL,NULL);
    /*hDochod4*/ oknoD[3] = CreateWindowW(L"Static", NULL,  WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 25, 462, 100, 25, hWnd, NULL, NULL,NULL);
    /*hDochod5*/ oknoD[4] = CreateWindowW(L"Static", NULL,  WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 25, 490, 100, 25, hWnd, NULL, NULL,NULL);

    /////////////////////////////////////// TYTUŁY DOCHODY

   /* hTytulD1*/ oknoTD[0] = CreateWindowW(L"Static", NULL,  WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 128, 378, 100, 25, hWnd, NULL, NULL,NULL);
   /* hTytulD2*/ oknoTD[1] = CreateWindowW(L"Static", NULL,  WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 128, 406, 100, 25, hWnd, NULL, NULL,NULL);
    /*hTytulD3*/ oknoTD[2] = CreateWindowW(L"Static", NULL,  WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 128, 434, 100, 25, hWnd, NULL, NULL,NULL);
   /* hTytulD4*/ oknoTD[3] = CreateWindowW(L"Static", NULL,  WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 128, 462, 100, 25, hWnd, NULL, NULL,NULL);
    /*hTytulD5*/ oknoTD[4] = CreateWindowW(L"Static", NULL,  WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 128, 490, 100, 25, hWnd, NULL, NULL,NULL);

    /////////////////////////////////////////////////// WYDATKI KWOTA

    hHistoriaW = CreateWindowW(L"Static", L"WYDATKI", WS_VISIBLE | WS_CHILD | SS_CENTER, 255, 325, 200, 25, hWnd, NULL, NULL,NULL);
   /* hWydatek1*/ oknoW[0] = CreateWindowW(L"Static", NULL,  WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 255, 378, 100, 25, hWnd, NULL, NULL,NULL);
    /*hWydatek2*/ oknoW[1] = CreateWindowW(L"Static", NULL,  WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 255, 406, 100, 25, hWnd, NULL, NULL,NULL);
   /* hWydatek3*/ oknoW[2] = CreateWindowW(L"Static", NULL,  WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 255, 434, 100, 25, hWnd, NULL, NULL,NULL);
   /* hWydatek4*/ oknoW[3] = CreateWindowW(L"Static", NULL,  WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 255, 462, 100, 25, hWnd, NULL, NULL,NULL);
   /* hWydatek5*/ oknoW[4] = CreateWindowW(L"Static", NULL,  WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 255, 490, 100, 25, hWnd, NULL, NULL,NULL);

    ///////////////////////////////////// TYTULY WYDATKI
    /*hTytulW1*/ oknoTW[0] = CreateWindowW(L"Static", NULL,  WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 358, 378, 100, 25, hWnd, NULL, NULL,NULL);
   /* hTytulW2*/ oknoTW[1] = CreateWindowW(L"Static", NULL,  WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 358, 406, 100, 25, hWnd, NULL, NULL,NULL);
   /* hTytulW3*/ oknoTW[2] = CreateWindowW(L"Static", NULL,  WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 358, 434, 100, 25, hWnd, NULL, NULL,NULL);
   /* hTytulW4*/ oknoTW[3] = CreateWindowW(L"Static", NULL,  WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 358, 462, 100, 25, hWnd, NULL, NULL,NULL);
   /* hTytulW5*/ oknoTW[4] = CreateWindowW(L"Static", NULL,  WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 358, 490, 100, 25, hWnd, NULL, NULL,NULL);
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

/////////////////////////////////////////////





/////////////////////////////////////////////


void ZapisWydatki()
{
    fstream plik_wydatki;
    plik_wydatki.open("Wydatki.txt", ios::out | ios::app);
    plik_wydatki<<zmiana_f;
    plik_wydatki<<tytul<<endl;
    plik_wydatki.close();
}


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
    }
    else
    {
            plik_portfel >> portfel;
            SetWindowText(hStan, portfel);
    }
}

//////////////////////////////////////////////////////////////
void ZapiszDochody()
{


    fstream plik_dochodyhistoria;
    plik_dochodyhistoria.open("Dochody His.txt", ios::out);
   for(int i=0;i<5;i++)
   {
      plik_dochodyhistoria<<&oknoD[i]<<endl;

   }

}
//void PokazDochody()////////////////////////DO ZROBIENIA NA CITO
//{
//    string dochodzik;
//    int i=0;
//    int wiersz;
//    char czarodziejski[20];
//    dochodzik = czarodziejski;
////    int *wskazuje;
////    wskazuje = dochodzik;
//    fstream plik_dochodyhistoria;
//    plik_dochodyhistoria.open("Dochody His.txt", ios::in);
//    if(plik_dochodyhistoria.good()== false)
//    {
//        cout << "Nie mozna zaladowac historii dochodow!" <<endl;
//
//    }
//    else
//    {
//
//
//        while(!plik_dochodyhistoria.eof())
//        {
//            for(i=0;i<5;i++)
//            plik_dochodyhistoria.getline(oknoD[i], 20);
//
//        }
//
//
//
//        while(getline(plik_dochodyhistoria,dochodzik))
//        {
////            for(wiersz = 1; wiersz<11; wiersz++)
////            {
////                if(wiersz%2 == 1)
////                {
////                    for(int j = 0;j<6;j++)
////                    {
////                        czarodziejski[wiersz] = oknoD[j];
////                        wiersz++;
////                    }
////
////                }
////
////            }




//while(getlin(plik_dochodyhistoria, dochodzik))
//{
//   for(int i=0;i<5;i++)
//    {
//       &oknoD[i] << dochodzik <<endl;
//    }
//}
//
//
//
//
//
//
//
//
//
//
//
//GetWindowTexT(oknoD[0], )
//switch(wiersz)
//{
//   case 1:
//        oknoD[0] = dochodzik;
//        break;
//    case 3:
//        oknoD[1] = dochodzik;
//        break;
//    case 5:
//        oknoD[2] = dochodzik;LRESULT CALLBACK DialogProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
//        break;
//    case 7:
//        oknoD[3] = dochodzik;
//        break;
//    case 9:
//        oknoD[4] = dochodzik;
//        break;
//    case 2:
//        oknoTD[0] = dochodzik;
//        break;
//    case 4:
//        oknoTD[1] = dochodzik;
//        break;
//    case 6:
//        oknoTD[2] = dochodzik;
//        break;
//    case 8:
//        oknoTD[3] = dochodzik;
//        break;
//    case 10:
//        oknoTD[4] = dochodzik;
//        break;
//
//}
//wiersz++;
//       }
//        }
//

//void Zapisik()
//{
//    GetWindowText(hDochod1, dochodzik1,10);
//    GetWindowText(oknoD[1], dochodzik2,10);
//    GetWindowText(oknoD[2], dochodzik3,10);
//    GetWindowText(oknoD[3], dochodzik4,10);
//    GetWindowText(oknoD[4], dochodzik5,10);
//}








//
//            for(wiersz = 1; wiersz<11; wiersz++)
//            {
//
//                {
//                    SetWindowText(oknoD[i],czarodziejski[20]);
//                    i++;
//                }
//                else
//                {
//                    SetWindowText(oknoTD[i],czarodziejski[20]);
//                    i++;
//                }
//            }
//


//        }
//
//
//    }
//}
////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////// WYSWIETLANIE HISTORII DOCHODOW

void DodajDochod()
{
    if(liczba_klikow_D == 6)
    {
        liczba_klikow_D = 1;
    }

    GetWindowText(hWartosc, zmiana,10);
    GetWindowText(hTytul, tytul,20);
    for(int i = 0; i<10; i++) // ZAMIANA PRZECINKA NA KROPKĘ
                    {
                        if(zmiana[i] == ',')
                        {
                            zmiana[i] = '.';
                        }
                    }

    SetWindowText(oknoD[liczba_klikow_D -1],zmiana);
    SetWindowText(oknoTD[liczba_klikow_D -1],tytul);

}


void DodajWydatek()
{
    if(liczba_klikow_W ==6)
    {
        liczba_klikow_W = 1;
    }
    GetWindowText(hWartosc, zmiana,10);
    GetWindowText(hTytul, tytul,20);
    for(int i = 0; i<10; i++) // ZAMIANA PRZECINKA NA KROPKĘ
                    {
                        if(zmiana[i] == ',')
                        {
                            zmiana[i] = '.';
                        }
                    }

    SetWindowText(oknoW[liczba_klikow_W -1],zmiana);
    SetWindowText(oknoTW[liczba_klikow_W -1],tytul);
}


/////////////////////////////////////////////////////////////
LRESULT CALLBACK DialogProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
    switch(msg)
    {
    case WM_COMMAND:
        switch(wp)
        {
        case 1:
            DestroyWindow(hWnd);
            break;
        }
    case WM_CLOSE:
            DestroyWindow(hOsiagi);
            break;
    case WM_CREATE:
        //    ObrazkiOsiagniecia();
          //  PokazOsiagi(hOsiagi);
        break;

        default:
            return DefWindowProcW(hWnd,msg,wp,lp);

    }
}

void registerOsiagiClass(HINSTANCE hInst)
{
    WNDCLASSW dialog = {0};
    dialog.hbrBackground = (HBRUSH)COLOR_WINDOW ;
    dialog.hCursor = LoadCursor(NULL,IDC_CROSS);
    dialog.hInstance = hInst;
    dialog.lpszClassName = L"MojeOsiagiKlasa"; // dla lpsz zawsze L z prefixem
    dialog.lpfnWndProc = DialogProcedure;

    RegisterClassW(&dialog);


}




void PokazOsiagi(HWND hWnd)
{
    HWND hOsiagi = CreateWindowW(L"MojeOsiagiKlasa",L"OSIAGNIECIA", WS_VISIBLE | WS_OVERLAPPEDWINDOW, 400, 400, 500, 300, hWnd, NULL, NULL, NULL);

    CreateWindowW(L"Button",L"Zamknij", WS_VISIBLE | WS_CHILD,380,220,100,40, hOsiagi,(HMENU)1,NULL,NULL);

    hO2000N = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD  | SS_BITMAP, 400, 400, 100, 50, hOsiagi,NULL, NULL,NULL);
    SendMessageW(hO2000N, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hOsiag2000N);

   // wylaczenie okienka EnableWindow(hWnd, false);
}


void ObrazkiOsiagniecia()
{
    hOsiag2000N = (HBITMAP)LoadImageW(NULL, L"o2000zlN.bmp", IMAGE_BITMAP,0,0, LR_LOADFROMFILE);
    hOsiag2000T = (HBITMAP)LoadImageW(NULL, L"o2000zlT.bmp", IMAGE_BITMAP,0,0, LR_LOADFROMFILE);


}



/////////////////////////////////////////////////////////////
//void ZapisHistoriiD()
//{
//
//            switch(liczba_klikow_D)
//            {
//            case 1:
//                GetWindowText(hWartosc, zmiana,10);
//                GetWindowText(hTytul, tytul,20);
//                for(int i = 0; i<10; i++) // ZAMIANA PRZECINKA NA KROPKĘ
//                    {
//                        if(zmiana[i] == ',')
//                        {
//                            zmiana[i] = '.';
//                        }
//                    }
//                SetWindowText(hDochod1, zmiana);
//                SetWindowText(hTytulD1, tytul);
//                break;
//
//            case 2:
//                GetWindowText(hWartosc, zmiana,10);
//                GetWindowText(hTytul, tytul,20);
//                for(int i = 0; i<10; i++) // ZAMIANA PRZECINKA NA KROPKĘ
//                    {
//                        if(zmiana[i] == ',')
//                        {
//                            zmiana[i] = '.';
//                        }
//                    }
//                SetWindowText(hDochod2, zmiana);
//                SetWindowText(hTytulD2, tytul);
//                break;
//            case 3:
//                GetWindowText(hWartosc, zmiana,10);
//                GetWindowText(hTytul, tytul,20);
//                for(int i = 0; i<10; i++) // ZAMIANA PRZECINKA NA KROPKĘ
//                    {
//                        if(zmiana[i] == ',')
//                        {
//                            zmiana[i] = '.';
//                        }
//                    }
//                SetWindowText(hDochod3, zmiana);
//                SetWindowText(hTytulD3, tytul);
//                break;
//            case 4:
//                GetWindowText(hWartosc, zmiana,10);
//                GetWindowText(hTytul, tytul,20);
//                for(int i = 0; i<10; i++) // ZAMIANA PRZECINKA NA KROPKĘ
//                    {
//                        if(zmiana[i] == ',')
//                        {
//                            zmiana[i] = '.';
//                        }
//                    }
//                SetWindowText(hDochod4, zmiana);
//                SetWindowText(hTytulD4, tytul);
//                break;
//            case 5:
//                GetWindowText(hWartosc, zmiana,10);
//                GetWindowText(hTytul, tytul,20);
//                for(int i = 0; i<10; i++) // ZAMIANA PRZECINKA NA KROPKĘ
//                    {
//                        if(zmiana[i] == ',')
//                        {
//                            zmiana[i] = '.';
//                        }
//                    }
//                SetWindowText(hDochod5, zmiana);
//                SetWindowText(hTytulD5, tytul);
//                liczba_klikow_D = 0;
//
//                break;
//
//            }
//        }
///////////////////////////////////////////////////////////////  WYSWIETLANIE HISTORII WYDATKOW
//void ZapisHistoriiW()
//{
//
//            switch(liczba_klikow_W)
//            {
//            case 1:
//                GetWindowText(hWartosc, zmiana,10);
//                GetWindowText(hTytul, tytul,20);
//                for(int i = 0; i<10; i++) // ZAMIANA PRZECINKA NA KROPKĘ
//                    {
//                        if(zmiana[i] == ',')
//                        {
//                            zmiana[i] = '.';
//                        }
//                    }
//                SetWindowText(hWydatek1, zmiana);
//                SetWindowText(hTytulW1, tytul);
//                break;
//
//            case 2:
//                GetWindowText(hWartosc, zmiana,10);
//                GetWindowText(hTytul, tytul,20);
//                for(int i = 0; i<10; i++) // ZAMIANA PRZECINKA NA KROPKĘ
//                    {
//                        if(zmiana[i] == ',')
//                        {
//                            zmiana[i] = '.';
//                        }
//                    }
//                SetWindowText(hWydatek2, zmiana);
//                SetWindowText(hTytulW2, tytul);
//                break;
//            case 3:
//                GetWindowText(hWartosc, zmiana,10);
//                GetWindowText(hTytul, tytul,20);
//                for(int i = 0; i<10; i++) // ZAMIANA PRZECINKA NA KROPKĘ
//                    {
//                        if(zmiana[i] == ',')
//                        {
//                            zmiana[i] = '.';
//                        }
//                    }
//                SetWindowText(hWydatek3, zmiana);
//                SetWindowText(hTytulW3, tytul);
//                break;
//            case 4:
//                GetWindowText(hWartosc, zmiana,10);
//                GetWindowText(hTytul, tytul,20);
//                for(int i = 0; i<10; i++) // ZAMIANA PRZECINKA NA KROPKĘ
//                    {
//                        if(zmiana[i] == ',')
//                        {
//                            zmiana[i] = '.';
//                        }
//                    }
//                SetWindowText(hWydatek4, zmiana);
//                SetWindowText(hTytulW4, tytul);
//                break;
//            case 5:
//                GetWindowText(hWartosc, zmiana,10);
//                GetWindowText(hTytul, tytul,20);
//                for(int i = 0; i<10; i++) // ZAMIANA PRZECINKA NA KROPKĘ
//                    {
//                        if(zmiana[i] == ',')
//                        {
//                            zmiana[i] = '.';
//                        }
//                    }
//                SetWindowText(hWydatek5, zmiana);
//                SetWindowText(hTytulW5, tytul);
//                liczba_klikow_W = 0;
//
//                break;
//
//            }
//        }

////////////////////////////////////
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
