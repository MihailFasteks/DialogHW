#include <windows.h>
#include <tchar.h>
#include "resource.h"
#define MAX_STATICS 10
BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

HWND /*hStatic1,*/ hStatic2;
TCHAR szCoordinates[20];
HINSTANCE hInst;
int x1, y1, x2, y2;
//const int LEFT = 15, TOP = 110, WIDTH = 380, HEIGHT = 50;
HWND statics[MAX_STATICS];
int staticCounter = 0; 

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
	hInst = hInstance;
	// создаём главное окно приложения на основе модального диалога
	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CLOSE:
		EndDialog(hWnd, 0); // закрываем модальный диалог
		return TRUE;
		// WM_INITDIALOG - данное сообщение приходит после создания диалогового окна, но перед его отображением на экран
	/*case WM_INITDIALOG:*/
		/*hStatic1 = GetDlgItem(hWnd, IDC_STATIC1);*/ // получаем дескриптор статика, размещенного на форме диалога
		//создаём статик с помощью CreateWindowEx
		/*hStatic2 = CreateWindowEx(0, TEXT("STATIC"), 0,
			WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER | WS_EX_CLIENTEDGE,
			LEFT, TOP, WIDTH, HEIGHT, hWnd, 0, hInst, 0);
		return TRUE;*/
	//case WM_MOUSEMOVE:
	//	wsprintf(szCoordinates, TEXT("X=%d  Y=%d"), LOWORD(lParam), HIWORD(lParam)); // текущие координаты курсора мыши
	//	SetWindowText(hStatic1, szCoordinates);	// строка выводится на статик
	//	return TRUE;
	
	case WM_LBUTTONDOWN:
		
		 x1 = LOWORD(lParam);
		 y1 = HIWORD(lParam);
		/*SetWindowText(hStatic2, TEXT("Нажата левая кнопка мыши"));*/
		return TRUE;
	case WM_RBUTTONDOWN:
	{
		for (int i = 0; i < staticCounter; ++i) {
			RECT rect;
			GetWindowRect(statics[i], &rect);
			if (LOWORD(lParam) >= rect.left && LOWORD(lParam) <= rect.right &&
				HIWORD(lParam) >= rect.top && HIWORD(lParam) <= rect.bottom) {
				
				TCHAR text[100];
				wsprintf(text, TEXT("Статик %d, ширина: %d, высота: %d, координаты: (%d, %d)"),
					i+1, abs(x2 - x1), abs(y2 - y1), x1, y1);
				SetWindowText(hWnd, text);
				break;
			}
			
		}
		/*TCHAR text[100];
		int length = GetWindowTextLength(hStatic2); 
		wsprintf(text, TEXT("Статик %d, ширина: %d, высота: %d, координаты: (%d, %d)"),
			GetDlgCtrlID(hStatic2), abs(x2 - x1), abs(y2 - y1), x1, y1);
		SetWindowText(hWnd, text);*/
		return TRUE;
	}
	case WM_LBUTTONDBLCLK:
	{
		for (int i = 0; i < staticCounter; ++i) {
			RECT rect;
			GetWindowRect(statics[i], &rect);
			if (LOWORD(lParam) >= rect.left && LOWORD(lParam) <= rect.right &&
				HIWORD(lParam) >= rect.top && HIWORD(lParam) <= rect.bottom) {
				DestroyWindow(statics[i]); 
				
				for (int j = i; j < staticCounter - 1; ++j) {
					statics[j] = statics[j + 1];
				}
				staticCounter--;
				break;
			}
		}
		return TRUE;
	}
	case WM_LBUTTONUP:
		
	        x2 = LOWORD(lParam);
		    y2 = HIWORD(lParam);
			hStatic2 = CreateWindowEx(0, TEXT("STATIC"), 0,
				WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER | WS_EX_CLIENTEDGE,
				x1, y1, abs(x2-x1), abs(y2-y1), hWnd, 0, hInst, 0);
			if (((abs(x2 - x1))<10) || ((abs(y2 - y1))<10)) {
				SetWindowText(hStatic2, TEXT("Этот статик меньше 10х10"));
		}
			statics[staticCounter++] = hStatic2;
		/*SetWindowText(hStatic2, TEXT("Нажата левая кнопка мыши"));*/
		return TRUE;
	/*case WM_RBUTTONDOWN:
		SetWindowText(hStatic2, TEXT("Нажата правая кнопка мыши"));
		return TRUE;*/
	}
	return FALSE;
}