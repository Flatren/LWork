#pragma once
#include <windows.h>
#include <ctime>
void Check_Game(char* dataptr,int x,int y,int n)
{
	bool r = true,c=true;
	for (int i = 1;(r||c) && i < n; i++)
	{
		if (r) r= *(dataptr + x*n + i) == *(dataptr + x*n + i - 1 );
		if (c) c = *(dataptr + i*n + y) == *(dataptr + (i-1)*n +y );
	}
	if(r||c)
		MessageBox(NULL, L"Win", L"Game End", 0);
}
bool Check_Player_Try(char* dataPtr,int id_g)
{

	return id_g != dataPtr[1];


	//	MessageBox(NULL, L"Win", L"Check_Player_Try", 0);
}
void Paint(void *hWnd)
{
	//Sleep(1000);
	int ti=0,o=10;
	while (1) {
		//
		Sleep(66);
		Size size;
		GetSizeWin((HWND)hWnd, size);
		
		int cx, cy;
		cx = size.height - 40;
		cy = size.wight - 17;
	
		int* mas = new int[cy*cx];
		ti+= o;
				for (int i = 0; i < cx; i++)
				{
					for (int j = 0; j < cy; j++)
						*(mas + i*cy + j) = ((double)INT32_MAX/(cx*cy))*(i+j-abs(ti));
				}
				o = (abs(ti) > 500) ? -o : o;
		HBITMAP hBitmap = CreateBitmap(cx, cy, 1, 32, mas);
		delete mas;
		HBRUSH hbr = CreatePatternBrush(hBitmap);
		DeleteObject((HBRUSH)GetClassLong((HWND)hWnd, GCLP_HBRBACKGROUND));
		SetClassLongPtr((HWND)hWnd, GCLP_HBRBACKGROUND, (LONG)hbr);
		InvalidateRect((HWND)hWnd, NULL, 1);	
		//Sleep(1000);
	
		DeleteObject(hBitmap);
		//DeleteObject(hbr);
		/*
		

		
		HBITMAP hBitmap = CreateBitmap(cx, cy, 1, 32, mas);
		
		SelectObject(memBit, hBitmap);
		
		DeleteObject(memBit);
		DeleteObject(hBitmap);
		
		ReleaseDC((HWND)hWnd, hdc);
		EndPaint((HWND)hWnd, &ps);
		DeleteObject(hdc);
		InvalidateRect((HWND)hWnd, NULL, FALSE);*/
		
		
	}

}
