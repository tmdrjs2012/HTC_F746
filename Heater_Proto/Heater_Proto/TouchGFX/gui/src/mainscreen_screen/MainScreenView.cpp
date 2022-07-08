/*
 @file: MainScreenView.cpp
 @brief: MainSceen of Temperature Display
 @date: 2022-05-25
 @ref: Core/stm32f7xx_it.c, generated/MainScreenBase.cpp
 @version: Modified PID and PWM function
 */

#include <gui/mainscreen_screen/MainScreenView.hpp>

#include "stdio.h"

extern double _newtempVal;
extern uint32_t adcVal;
extern int Config_Temp;
extern uint32_t _tim3_cnt;
extern uint32_t checkTimecnt;
extern uint32_t sRelay_Flag;
extern double _pidResult;
extern uint32_t Timer_Flag;
extern uint32_t configcnt;

uint32_t init_temp = 40;
int ConfigMyTemp;
uint32_t Count_Flag;
uint32_t DisplayVal;
extern unsigned char displayContinous;


char buff[20];
long cnt;
uint32_t TenDigit, Digit;


#ifndef SIMULATOR
#include "stm32f7xx_hal.h"
#include "main.h"
#endif

int timeCal(int _TenPoint, int _DigitPoint);


// MainScreen CallbackHandler ScrollWheell items
MainScreenView::MainScreenView():callBack(this, &MainScreenView::callBackHandler)
{
	TenScrollWheel.setAnimateToCallback(callBack);
	TenScrollWheel.animateToItem(TenDigit-1);

	DigitScrollWheel.setAnimateToCallback(callBack);
	DigitScrollWheel.animateToItem(Digit-1);
}

void MainScreenView::setupScreen()
{

    MainScreenViewBase::setupScreen();
}

void MainScreenView::tearDownScreen()
{
    MainScreenViewBase::tearDownScreen();
}

void MainScreenView::handleTickEvent()
{

	// upload Temperature configuration
	ConfigMyTemp = init_temp + Config_Temp;

	if(ConfigMyTemp >= 65)
	{
		Config_Temp = 25;
	}
	else if(ConfigMyTemp <= 35)
	{
		Config_Temp = -5;
	}

	// Display Temperature
	Unicode::snprintf(ConfigTempTextBuffer, 10, "%d" , ConfigMyTemp);
	ConfigTempText.setWildcard(ConfigTempTextBuffer);
	ConfigTempText.invalidate();

	if(checkTimecnt == 2){


		if(sRelay_Flag == 1)
		{
			if(_newtempVal >= (ConfigMyTemp-0.1) && _newtempVal <= ConfigMyTemp+1.2)
			{
				displayContinous = 1;
			}
			else if(_newtempVal >= (ConfigMyTemp+1.5) && _newtempVal < (ConfigMyTemp-2.1))
			{
				displayContinous = 0;
			}
			if(displayContinous == 0)
			{
				DisplayVal = (int)_newtempVal;
			}
			if(displayContinous == 1)
			{
				DisplayVal = ConfigMyTemp;
			}
		}
		else
		{
			displayContinous = 0;
			DisplayVal = (int)_newtempVal;
		}

		Unicode::snprintf(ReadTempTextBuffer, 10, " %d", DisplayVal);
		ReadTempText.setWildcard(ReadTempTextBuffer);
		ReadTempText.invalidate();


		checkTimecnt = 0;
	}

#ifndef SIMULATOR
	if(sRelay_Flag == 1)
	{
		// Heater ON as PWM
		TIM12->ARR = 1000-1;
		TIM12->CCR1 = ( (1000-1)*(1-_pidResult));	// -> Frequency  500Hz
	}
	else
	{
		// Heater Off
		TIM12->ARR = 1000-1;
		TIM12->CCR1 = ( (1000-1)*1);			// HIGH
	}

#endif
	// Timer ON
	if(Timer_Flag && !((TenDigit == 0) && (Digit == -1)))
	{
		Count_Flag = 1;		// count on

		timer_img.setAlpha(255);
		timer_img.invalidate();

		int resTime = timeCal(TenDigit, Digit);
		resTime -= configcnt;


		if((resTime/60)>=0 && (resTime%60)>=0){
			Unicode::snprintf(MinTextBuffer, 10, "%d", resTime/60);
			Unicode::snprintf(SecTextBuffer, 10, "%d", resTime%60);
			Unicode::snprintf(textArea10Buffer, 10, "%d", resTime/60);	// min
			Unicode::snprintf(textArea11Buffer, 10, "%d", resTime%60);	// sec

			MinText.setWildcard(MinTextBuffer);
			SecText.setWildcard(SecTextBuffer);
			textArea10.setWildcard(textArea10Buffer);
			textArea10.setAlpha(255);
			textArea10.invalidate();
			textArea11.setWildcard(textArea11Buffer);
			textArea11.setAlpha(255);
			textArea11.invalidate();
			textArea8.setAlpha(255);
			textArea8.invalidate();
			textArea9.setAlpha(255);
			textArea9.invalidate();
			MinText.invalidate();
			SecText.invalidate();

		}
		if(resTime == 0 ){
			configcnt = 0;
			Count_Flag = 0;			// count off
			Timer_Flag = 0;			// timer off
			sRelay_Flag = 0;
			timer_img.setAlpha(60);
			timer_img.invalidate();

			// if timer turn off, Button forcibly change off state
			RelayBtn.forceState(0);
			RelayBtn.invalidate();

			TimerBtn.forceState(0);
			TimerBtn.invalidate();
		}
		if(Count_Flag == 0){
			// cannot count
				resTime = 0; //
				configcnt = 0;
				Count_Flag = 0;			// count off
				Timer_Flag = 0;			// timer off
				timer_img.setAlpha(60);

				Unicode::snprintf(MinTextBuffer, 10, "%d", 0);
				MinText.setWildcard(MinTextBuffer);
				MinText.invalidate();
				Unicode::snprintf(SecTextBuffer, 10, "%d", 0);
				SecText.setWildcard(SecTextBuffer);
				SecText.invalidate();

				Unicode::snprintf(textArea10Buffer, 10, "%d", 0);	// 분
				textArea10.setWildcard(textArea10Buffer);
				textArea10.setAlpha(60);
				textArea10.invalidate();
				Unicode::snprintf(textArea11Buffer, 10, "%d", 0);	// 초
				textArea11.setWildcard(textArea11Buffer);
				textArea11.setAlpha(60);
				textArea11.invalidate();

				textArea8.setAlpha(60);
				textArea8.invalidate();
				textArea9.setAlpha(60);
				textArea9.invalidate();
		}
	}
	else if(Timer_Flag == 0 && !((TenDigit == 0) && (Digit == -1))){
		Timer_Flag = 0;
		configcnt = 0;
		Count_Flag = 0;
		timer_img.setAlpha(60);
		timer_img.invalidate();

		Unicode::snprintf(MinTextBuffer, 10, "%d", 0);
		MinText.setWildcard(MinTextBuffer);
		MinText.invalidate();
		Unicode::snprintf(SecTextBuffer, 10, "%d", 0);
		SecText.setWildcard(SecTextBuffer);
		SecText.invalidate();
		Unicode::snprintf(textArea10Buffer, 10, "%d", 0);	// 분
		textArea10.setWildcard(textArea10Buffer);
		textArea10.setAlpha(60);
		textArea10.invalidate();
		Unicode::snprintf(textArea11Buffer, 10, "%d", 0);	// 초
		textArea11.setWildcard(textArea11Buffer);
		textArea11.setAlpha(60);
		textArea11.invalidate();

		textArea8.setAlpha(60);
		textArea8.invalidate();
		textArea9.setAlpha(60);
		textArea9.invalidate();
	}

}

void MainScreenView::TenScrollWheelUpdateItem(CustomContainer1& item, int16_t itemIndex)
{
    // Override and implement this function in MainScreen
	item.setText(itemIndex);
}

void MainScreenView::TenScrollWheelUpdateCenterItem(CustomContainer2& item, int16_t itemIndex)
{
    // Override and implement this function in MainScreen
	TenDigit = item.setText(itemIndex);
}

void MainScreenView::DigitScrollWheelUpdateItem(CustomContainer1& item, int16_t itemIndex)
{
    // Override and implement this function in MainScreen
	item.setText(itemIndex);
}

void MainScreenView::DigitScrollWheelUpdateCenterItem(CustomContainer2& item, int16_t itemIndex)
{
    // Override and implement this function in MainScreen
	Digit = item.setText(itemIndex);
}

void MainScreenView::callBackHandler(int16_t index)
{

}

/*
 @function: timcCal
 @param: (_TenPoint) Calculate Ten digit of the timer
 	 	 (_DigitPoint) Calculate digit of the timer
 	 	 (totalSec)	total second
 @brief: the function which Calculate digit point of the timer
 */
int timeCal(int _TenPoint, int _DigitPoint)
{
	int totalSec;
	int totalMin;

	if(_TenPoint == 0){
		totalMin = _DigitPoint-1;
		totalSec = totalMin*60;
	}
	else if(_DigitPoint == 0 && _TenPoint > 0){
		totalMin = ((_TenPoint-1)*10)+(_DigitPoint);
		totalSec = totalMin*60;
	}
	else{
		totalMin = ((_TenPoint-1)*10)+(_DigitPoint-1);
		totalSec = totalMin*60;
	}

	return totalSec;
}
