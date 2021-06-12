#pragma once
#include "windows.h"

LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam);

class DisplayWin32 {
public://have to be private
	HINSTANCE hInstance;
	HWND hWnd;
	int module;
	UINT screenWidth;
	UINT screenHeight;
	WNDCLASSEX wc;

	//DisplayWin32();
	DisplayWin32(LPCWSTR applicationName, HINSTANCE hInstance, int width, int height);
};