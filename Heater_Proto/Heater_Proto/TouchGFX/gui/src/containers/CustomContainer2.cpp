#include <gui/containers/CustomContainer2.hpp>

CustomContainer2::CustomContainer2()
{

}

void CustomContainer2::initialize()
{
    CustomContainer2Base::initialize();
}

int CustomContainer2::setText(int n)
{
	Unicode::snprintf(textArea1Buffer, 10, "%d", n);
	textArea1.resizeToCurrentText();
	textArea1.invalidate();
	return n;
}
