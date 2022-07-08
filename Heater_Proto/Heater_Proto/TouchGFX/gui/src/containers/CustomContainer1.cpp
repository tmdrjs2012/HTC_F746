#include <gui/containers/CustomContainer1.hpp>

CustomContainer1::CustomContainer1()
{

}

void CustomContainer1::initialize()
{
    CustomContainer1Base::initialize();
}

int CustomContainer1::setText(int n)
{
	Unicode::snprintf(textArea1Buffer, 10, "%d", n);
	textArea1.resizeToCurrentText();
	textArea1.invalidate();
	return n;
}
