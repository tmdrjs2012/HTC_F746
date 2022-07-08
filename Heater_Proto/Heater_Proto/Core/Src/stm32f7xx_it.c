/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f7xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */


/*
 @file: stm32f7xx_it.c
 @brief: Interrupt Service Routines of Temperature Display
 @date: 2022-05-25
 @ref: MainScreenViewBase.cpp, MainScreenView
 @version: CalCulate Temperature and PID
 */

/*********************************************************************************/
/********************* YOU SHOULD WIRTE IN USER OCDE ZONE  ***********************/
/*********************************************************************************/

/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f7xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "math.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
uint32_t _tim3_cnt;
uint32_t _pid3_cnt;
uint32_t configcnt;
uint32_t checkTimecnt;
int Flag_Cnt;
double _tempVal;
double _newtempVal;
uint32_t adcVal;
double temp;
double _pidResult;

double moduleParam_A = 0.054346079;
double moduleParam_B = 0.040493721;
double moduleParam_C = 0.0030094258;

#define betaRK 3435
#define RT0 10000
#define VCC 3.3
#define R 10000

double VRT, VR, ln, RT;
double T0 = 25 + 273.15;

#define B_CONST 3635 //3435

double Themi1;
double Themi2;
double logThemi1;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */
double tempGetValue(void);
double log_ln(double x);

double caliVal(double input_data, uint32_t count);
double PID_Contorller(double kp, double ki, double kd, uint32_t ConfigTemp, double ReadTemp);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern DMA2D_HandleTypeDef hdma2d;
extern LTDC_HandleTypeDef hltdc;
extern DMA_HandleTypeDef hdma_tim2_up_ch3;
extern DMA_HandleTypeDef hdma_tim3_ch4_up;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim6;

/* USER CODE BEGIN EV */
extern ADC_HandleTypeDef hadc3;
extern int ConfigMyTemp;
extern uint32_t Count_Flag;
/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M7 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */

  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Pre-fetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/******************************************************************************/
/* STM32F7xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f7xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles DMA1 stream1 global interrupt.
  */
void DMA1_Stream1_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Stream1_IRQn 0 */

  /* USER CODE END DMA1_Stream1_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_tim2_up_ch3);
  /* USER CODE BEGIN DMA1_Stream1_IRQn 1 */

  /* USER CODE END DMA1_Stream1_IRQn 1 */
}

/**
  * @brief This function handles DMA1 stream2 global interrupt.
  */
void DMA1_Stream2_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Stream2_IRQn 0 */

  /* USER CODE END DMA1_Stream2_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_tim3_ch4_up);
  /* USER CODE BEGIN DMA1_Stream2_IRQn 1 */

  /* USER CODE END DMA1_Stream2_IRQn 1 */
}

/**
  * @brief This function handles TIM2 global interrupt.
  */
void TIM2_IRQHandler(void)
{
  /* USER CODE BEGIN TIM2_IRQn 0 */

  /* USER CODE END TIM2_IRQn 0 */
  HAL_TIM_IRQHandler(&htim2);
  /* USER CODE BEGIN TIM2_IRQn 1 */
  if(Count_Flag){
	  ++configcnt;
  }
  /* USER CODE END TIM2_IRQn 1 */
}

/**
  * @brief This function handles TIM3 global interrupt.
  */
void TIM3_IRQHandler(void)
{
  /* USER CODE BEGIN TIM3_IRQn 0 */

  /* USER CODE END TIM3_IRQn 0 */
  HAL_TIM_IRQHandler(&htim3);
  /* USER CODE BEGIN TIM3_IRQn 1 */


  static _pid_count;		 // pid timer count
  ++_tim3_cnt;

  // get temperature
  _tempVal = tempGetValue();
  _pid3_cnt += 1;

  // Calculate temperature sampling value
  _newtempVal = caliVal(_tempVal, _tim3_cnt);

   if(_pid3_cnt == 25)
   {
	   // 0.1s = count 100
	   // 0.05s = count 50

	   _pidResult = PID_Contorller(1, 0.05, 0.2, ConfigMyTemp, _newtempVal);   // 9A		//  40 / 39.3

	   _pid3_cnt = 0;
   }
  /* USER CODE END TIM3_IRQn 1 */
}

/**
  * @brief This function handles TIM6 global interrupt, DAC1 and DAC2 underrun error interrupts.
  */
void TIM6_DAC_IRQHandler(void)
{
  /* USER CODE BEGIN TIM6_DAC_IRQn 0 */

  /* USER CODE END TIM6_DAC_IRQn 0 */
  HAL_TIM_IRQHandler(&htim6);
  /* USER CODE BEGIN TIM6_DAC_IRQn 1 */

  /* USER CODE END TIM6_DAC_IRQn 1 */
}

/**
  * @brief This function handles LTDC global interrupt.
  */
void LTDC_IRQHandler(void)
{
  /* USER CODE BEGIN LTDC_IRQn 0 */

  /* USER CODE END LTDC_IRQn 0 */
  HAL_LTDC_IRQHandler(&hltdc);
  /* USER CODE BEGIN LTDC_IRQn 1 */

  /* USER CODE END LTDC_IRQn 1 */
}

/**
  * @brief This function handles DMA2D global interrupt.
  */
void DMA2D_IRQHandler(void)
{
  /* USER CODE BEGIN DMA2D_IRQn 0 */

  /* USER CODE END DMA2D_IRQn 0 */
  HAL_DMA2D_IRQHandler(&hdma2d);
  /* USER CODE BEGIN DMA2D_IRQn 1 */

  /* USER CODE END DMA2D_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/*
 @function: TempGetValuje
 @param (Themi_temp) get temperature result of the thermistor
 @brief: the function which Calculate temperature using ADC Value
 */
double tempGetValue(void)
{
	HAL_ADC_Start(&hadc3);
	if(HAL_ADC_PollForConversion(&hadc3, 100) == HAL_OK){
		adcVal = HAL_ADC_GetValue(&hadc3);
	}
	HAL_ADC_Stop(&hadc3);

	double Themi_mV = adcVal*0.79;
	double Themi_V = Themi_mV/1000;
	double Themi_R = 120000*(Themi_V/((5)-Themi_V));

	double Themi_temp = 1/((log_ln(Themi_R/10000)/B_CONST)+(1/(25+273.15)))-273.15;

	return Themi_temp;
}

/*
 @function: log_ln
 @brief: the function which get Natural logarithm
 */
double log_ln(double x)
{
	return log(x)/log(exp(1));
}

/*
 @function: PID_Contorller
 @param: (kp) P GAIN
 	 	 (ki) I GAIN
 	 	 (kd) D GAIN
 	 	 (ConfigTemp) get Configuration Temperature
 	 	 (ReadTemp) Read Current Temperature
 	 	 (pidValue) PID controlled variable
 @brief: the function which Calculate PID GAIN and PID controlled variable
 */
double caliVal(double input_data, uint32_t count)
{
	static double temp[500];
	static double totalVal;
	static int sFlag = 1;

	if(sFlag){
		temp[count-1] = input_data;
		totalVal = totalVal + input_data;

		if(count == 500){
			sFlag = 0;
			_tim3_cnt = 0;
		}
	}
	else if(!sFlag){
		totalVal = totalVal - temp[count-1];
		temp[count-1] = input_data;
		totalVal = totalVal + temp[count-1];

		if(count >= 500){
			_tim3_cnt = 0;
			++checkTimecnt;
		}

		double cal_out = totalVal/500;
		return cal_out;
	}
}

/*
 @function: PID_Contorller
 @param: (kp) P GAIN
 	 	 (ki) I GAIN
 	 	 (kd) D GAIN
 	 	 (ConfigTemp) get Configuration Temperature
 	 	 (ReadTemp) Read Current Temperature
 	 	 (pidValue) PID controlled variable
 @brief: the function which Calculate PID GAIN and PID controlled variable
 */
double PID_Contorller(double kp, double ki, double kd, uint32_t ConfigTemp, double ReadTemp)
{

	static double pidValue, _pidError, prevError, _pidP, _pidI, _pidD;

	const double margin = -0.2;

	_pidError = ConfigTemp - (ReadTemp + margin);

	_pidP = kp * _pidError;
	_pidI = ki * (_pidI + _pidError);
	_pidD = kd * (_pidError - prevError);

	pidValue = _pidP+_pidI+_pidD;

	pidValue = _pidP+_pidI+_pidD;

	if(pidValue <= 0)
	{
		pidValue = 0; // transfer on signal
	}
	if(pidValue >= 1)
	{
		pidValue = 1;	// transfer off signal
	}

	prevError = _pidError;

	return pidValue;
}

/*
void TIM2Classic_Init(void)
{
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	NVIC->IP[28] = 0xF0;

	TIM2->CR1 |= TIM_CR1_CEN | TIM_CR1_URS;
	TIM2->PSC = 20000-1;

	//TIM2->ARR = ; // ...... 200MHz/20000 = 10000Cnt is 1sec
	NVIC->ISER[0] = 0x10000000;
	TIM2->EGR = TIM_EGR_UG;
	TIM2->DIER = TIM_DIER_UIE;

	SCB->AIRCR = 0x00000300;
}
*/
/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
