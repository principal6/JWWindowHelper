#include "JWWindowHelper.h"

using namespace JWEngine;

FOnKeyDown(OnKeyDown);
FOnKeyPressed(OnKeyPressed);

JWWindowHelper myWindow;

int main()
{
	myWindow.Create(SPositionInt(0, 50), SSizeInt(600, 400), "MY");
	myWindow.SetFunctionOnKeyDown(OnKeyDown);
	myWindow.SetFunctionOnKeyPressed(OnKeyPressed);
	myWindow.Run();

	return 0;
}

FOnKeyDown(OnKeyDown)
{
	if (VKCode == VK_ESCAPE)
	{
		myWindow.Halt();
	}
}

FOnKeyPressed(OnKeyPressed)
{
	if (Character == 'a')
	{
		std::cout << "a Pressed." << std::endl;
	}
	else if (Character == 'A')
	{
		std::cout << "A Pressed." << std::endl;
	}
}