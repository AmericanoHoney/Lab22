#include <windows.h>
#include <stdio.h>

char t1[20],t2[20],sum[100];
double num1 = 0 ,num2=0;
HBRUSH hBrushCustomBg;
HWND textfield,plus,TextBox1,minus,TextBox2,mul,divi;

/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {
		/* Upon destruction, tell the main thread to stop */
		case WM_CREATE:
			textfield = CreateWindow("STATIC",
									"Please input two numbers :D",
									WS_VISIBLE|WS_CHILD,
									20,20,200,25,
									hwnd,NULL,NULL,NULL);
			TextBox1 = CreateWindow	("EDIT",
									"",
									WS_VISIBLE|WS_CHILD|WS_BORDER,
									20,50,200,25,
									hwnd,NULL,NULL,NULL);
			TextBox2 = CreateWindow	("EDIT",
									"",
									WS_VISIBLE|WS_CHILD|WS_BORDER,
									20,80,200,25,
									hwnd,NULL,NULL,NULL);	
			plus = CreateWindow	("BUTTON",
									"+",
									WS_VISIBLE|WS_CHILD|WS_BORDER,
									50,130,20,20,
									hwnd,(HMENU) 1,NULL,NULL);											
			minus = CreateWindow	("BUTTON",
									"-",
									WS_VISIBLE|WS_CHILD|WS_BORDER,
									90,130,20,20,
									hwnd,(HMENU) 2,NULL,NULL);
			mul = CreateWindow	("BUTTON",
									"*",
									WS_VISIBLE|WS_CHILD|WS_BORDER,
									130,130,20,20,
									hwnd,(HMENU) 3,NULL,NULL);
			divi = CreateWindow	("BUTTON",
									"-",
									WS_VISIBLE|WS_CHILD|WS_BORDER,
									170,130,20,20,
									hwnd,(HMENU) 4,NULL,NULL);	
			hBrushCustomBg = CreateSolidBrush(RGB(158, 118, 180));										
			break;
		
		case WM_COMMAND :
			switch (LOWORD(wParam))
			{
				case 1:
					GetWindowText(TextBox1,&t1[0],20);
					GetWindowText(TextBox2,&t2[0],20);
					num1 = atof (t1);
					num2 = atof (t2);
					sprintf(sum,"%f",num1+num2);
					::MessageBox(hwnd,sum,"Result",MB_OK);
					break;
				case 2:
					GetWindowText(TextBox1,&t1[0],20);
					GetWindowText(TextBox2,&t2[0],20);
					num1 = atof (t1);
					num2 = atof (t2);
					sprintf(sum,"%f",num1-num2);
					::MessageBox(hwnd,sum,"Result",MB_OK);
					break;
				case 3:
					GetWindowText(TextBox1,&t1[0],20);
					GetWindowText(TextBox2,&t2[0],20);
					num1 = atof (t1);
					num2 = atof (t2);
					sprintf(sum,"%f",num1*num2);
					::MessageBox(hwnd,sum,"Result",MB_OK);
					break;
				case 4:
					GetWindowText(TextBox1,&t1[0],20);
					GetWindowText(TextBox2,&t2[0],20);
					num1 = atof (t1);
					num2 = atof (t2);
					sprintf(sum,"%f",num1/num2);
					::MessageBox(hwnd,sum,"Result",MB_OK);
					break;
			}
			break;
		case WM_ERASEBKGND:
        {
            HDC hdc = (HDC)wParam;
            RECT rect;
            GetClientRect(hwnd, &rect);
            FillRect(hdc, &rect, hBrushCustomBg); // Fill the client area with the custom color
            return 1; // Return non-zero to indicate that the message has been handled
        }
		case WM_CTLCOLORSTATIC:
            // Make static text background transparent
        {
            HDC hdcStatic = (HDC)wParam;
            SetBkMode(hdcStatic, TRANSPARENT);
            return (LRESULT)GetStockObject(NULL_BRUSH);
        }
		// case WM_CTLCOLORSTATIC:
		// case WM_CTLCOLOREDIT:
        // {
        //     HDC hdcStatic = (HDC)wParam;
        //     //SetBkColor(hdcStatic, RGB(2, 220, 240)); // Match the brush color
        //     //SetTextColor(hdcStatic, RGB(200, 220, 240)); // Black text color
        //     return (INT_PTR)hBrushCustomBg;
        // }
		case WM_DESTROY: {
			DeleteObject(hBrushCustomBg);
			PostQuitMessage(0);
			break;
		}
		
		/* All other messages (a lot of them) are processed using default procedures */
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc; /* A properties struct of our window */
	HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
	MSG msg; /* A temporary location for all messages */

	/* zero out the struct and set the stuff we want to modify */
	memset(&wc,0,sizeof(wc));
	wc.cbSize	 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
	wc.hInstance	 = hInstance;
	wc.hCursor	 = LoadCursor(NULL, IDC_ARROW);
	
	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszClassName = "WindowClass";
	wc.hIcon	 = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
	wc.hIconSm	 = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","My Calculator",WS_VISIBLE|WS_SYSMENU,
		CW_USEDEFAULT, /* x */
		CW_USEDEFAULT, /* y */
		250, /* width */
		200, /* height */
		NULL,NULL,hInstance,NULL);

	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	/*
		This is the heart of our program where all input is processed and 
		sent to WndProc. Note that GetMessage blocks code flow until it receives something, so
		this loop will not produce unreasonably high CPU usage
	*/
	while(GetMessage(&msg, NULL, 0, 0) > 0) { /* If no error is received... */
		TranslateMessage(&msg); /* Translate key codes to chars if present */
		DispatchMessage(&msg); /* Send it to WndProc */
	}
	return msg.wParam;
}
