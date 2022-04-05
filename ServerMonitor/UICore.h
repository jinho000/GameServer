#pragma once


class UICore
{
public:
	static bool Init(HWND _wndHandle);
	static void Update();
	static void Destroy();

	// win message proc
	static void WinMessageProc(WPARAM, LPARAM);
};

