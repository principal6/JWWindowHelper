#pragma once

#include <iostream>
#include <string>
#include <cstdint>
#include <cassert>
#include <Windows.h>

namespace JWEngine
{
#define FOnKeyDown(Name) void Name(UINT VKCode)
	using FPOnKeyDown = void(*)(UINT);

#define FOnKeyPressed(Name) void Name(TCHAR Character)
	using FPOnKeyPressed = void(*)(TCHAR);

	using STRING = std::string;

	struct SPositionInt
	{
		int16_t X{};
		int16_t Y{};

		SPositionInt() = default;
		SPositionInt(int16_t _X, int16_t _Y) : X{ _X }, Y{ _Y } {};
	};

	struct SSizeInt
	{
		int16_t XSize{};
		int16_t YSize{};

		SSizeInt() = default;
		SSizeInt(int16_t _XSize, int16_t _YSize) : XSize{ _XSize }, YSize{ _YSize } {};
	};

	class JWWindowHelper
	{
	public:
		JWWindowHelper() = default;
		~JWWindowHelper() = default;

		void Create(SPositionInt Position, SSizeInt Size, const STRING& Title) noexcept;

		void SetFunctionOnKeyDown(FPOnKeyDown pFunction) noexcept;
		void SetFunctionOnKeyPressed(FPOnKeyPressed pFunction) noexcept;

		void Run() noexcept;
		void Halt() noexcept;

		auto GetWidth() const noexcept->int;
		auto GetHeight() const noexcept->int;
		auto GetWindowHandle() const noexcept->HWND;
		auto GetInstanceHandle() const noexcept->HINSTANCE;

	private:
		bool m_IsRunning{ false };
		HINSTANCE m_hInstance{};
		HWND m_hWindow{};
		SSizeInt m_WindowSize{};
	};
};