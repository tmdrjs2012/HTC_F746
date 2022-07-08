#ifndef MAINSCREENVIEW_HPP
#define MAINSCREENVIEW_HPP

#include <gui_generated/mainscreen_screen/MainScreenViewBase.hpp>
#include <gui/mainscreen_screen/MainScreenPresenter.hpp>

class MainScreenView : public MainScreenViewBase
{
public:
    MainScreenView();
    virtual ~MainScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void handleTickEvent();
protected:
    virtual void TenScrollWheelUpdateItem(CustomContainer1& item, int16_t itemIndex);
    virtual void TenScrollWheelUpdateCenterItem(CustomContainer2& item, int16_t itemIndex);
    virtual void DigitScrollWheelUpdateItem(CustomContainer1& item, int16_t itemIndex);
    virtual void DigitScrollWheelUpdateCenterItem(CustomContainer2& item, int16_t itemIndex);

    touchgfx::Callback<MainScreenView, int16_t> callBack;
    void callBackHandler(int16_t index);
};

#endif // MAINSCREENVIEW_HPP
