#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include "Device.h"

static TCHAR AppName[] = _T("DesktopApp");
static TCHAR AppTitle[] = _T("TransferApp");
int windowWidth = 1000,
windowHeight = 700;

HINSTANCE hInst;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(_In_  HINSTANCE hInstance,
				   _In_opt_ HINSTANCE hPrevInstance,
				   _In_ LPSTR lpCmdLine,
				   _In_ int nCmdShow) {

	WNDCLASSEX janela;

	janela.cbSize = sizeof(WNDCLASSEX);
	janela.style = CS_HREDRAW | CS_VREDRAW;
	janela.lpfnWndProc = WndProc;
	janela.cbClsExtra = 0;
	janela.cbWndExtra = 0;
	janela.hInstance = hInstance;
	janela.hIcon = LoadIcon(janela.hInstance, IDI_APPLICATION);
	janela.hCursor = LoadCursor(NULL, IDC_ARROW);
	janela.hbrBackground = CreateSolidBrush(RGB(255,255,255));
	janela.lpszMenuName = NULL;
	janela.lpszClassName = AppName;
	janela.hIconSm = LoadIcon(janela.hInstance, IDI_APPLICATION);

	if (!RegisterClassEx(&janela)) {
		MessageBox(NULL,
				   _T("A chamada do RegisterClassEx falhou!"),
				   _T("TransferApp"),NULL);
		return 1;
	}

	hInst = hInstance;

	HWND hWnd = CreateWindowEx(
		WS_EX_OVERLAPPEDWINDOW,
		AppName, AppTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		windowWidth, windowHeight, NULL, NULL, hInstance, NULL);
	if (!hWnd) {
		MessageBox(NULL, _T("O programa falhou em criar uma janela!"),
			_T("TransferApp"), NULL);
		return 1;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}

//Lida com mensagens
LRESULT CALLBACK WndProc(_In_ HWND hWnd,
						 _In_ UINT message,
					 	 _In_ WPARAM wParam,
					 	 _In_ LPARAM lParam) {

	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR testMessage[] = _T("Hello World");

	switch (message) {
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		TextOut(hdc, 5, 5, testMessage, _tcslen(testMessage));

		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}

	return 0;
}