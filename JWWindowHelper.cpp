#include "JWWindowHelper.h"

using namespace JWEngine;

static FPOnKeyDown s_FPOnKeyDown{};
static FPOnKeyPressed s_FPOnKeyPressed{};

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CHAR:
		s_FPOnKeyPressed(static_cast<TCHAR>(wParam));
		break;
	case WM_KEYDOWN:
		s_FPOnKeyDown(static_cast<UINT>(wParam));
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		exit(0);
		return 0;
	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

void JWWindowHelper::Create(SPositionInt Position, SSizeInt Size, const STRING& Title) noexcept
{
	m_hInstance = GetModuleHandleA(nullptr);

	m_WindowSize = Size;

	WNDCLASSEXA wc{};
	wc.cbSize = sizeof(WNDCLASSEXA);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = m_hInstance;
	wc.hIcon = LoadIconA(nullptr, IDI_APPLICATION);
	wc.hCursor = nullptr; //LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = nullptr; //(HBRUSH)(COLOR_WINDOW + 2);
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = "JWEngine";
	wc.hIconSm = LoadIconA(nullptr, IDI_APPLICATION);

	assert(RegisterClassExA(&wc));
	
	RECT rect = { Position.X, Position.Y, Position.X + Size.XSize, Position.Y + Size.YSize };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

	m_hWindow = CreateWindowExA(0, wc.lpszClassName, Title.c_str(), WS_OVERLAPPEDWINDOW, rect.left, rect.top,
		rect.right - rect.left, rect.bottom - rect.top, nullptr, nullptr, m_hInstance, nullptr);

	assert(m_hWindow);
	
	ShowWindow(m_hWindow, SW_SHOW);
	UpdateWindow(m_hWindow);
}

void JWWindowHelper::SetFunctionOnKeyDown(FPOnKeyDown pFunction) noexcept
{
	s_FPOnKeyDown = pFunction;
}

void JWWindowHelper::SetFunctionOnKeyPressed(FPOnKeyPressed pFunction) noexcept
{
	s_FPOnKeyPressed = pFunction;
}

void JWWindowHelper::Run() noexcept
{
	m_IsRunning = true;

	MSG message{};

	while (m_IsRunning)
	{
		if (PeekMessage(&message, m_hWindow, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
	}
}

void JWWindowHelper::Halt() noexcept
{
	m_IsRunning = false;
}

auto JWWindowHelper::GetWidth() const noexcept->int
{
	return m_WindowSize.XSize;
}

auto JWWindowHelper::GetHeight() const noexcept->int
{
	return m_WindowSize.YSize;
}

auto JWWindowHelper::GetWindowHandle() const noexcept->HWND
{
	return m_hWindow;
}

auto JWWindowHelper::GetInstanceHandle() const noexcept->HINSTANCE
{
	return m_hInstance;
}