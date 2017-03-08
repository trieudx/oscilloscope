#include <stdio.h>
#include "stm32f4xx_conf.h"

// Private variables
volatile uint32_t time_var1, time_var2;

// Private function prototypes
void Delay(volatile uint32_t nCount);
void timing_handler(void);

int main(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	// Disable STDOUT buffering. Otherwise nothing will be printed
	// before a newline character or when the buffer is flushed.
	// This MUST be done before any writes to STDOUT to have any effect...
	setbuf(stdout, NULL);

	printf("Hello world\r\n");

	// ---------- SysTick timer -------- //
	if (SysTick_Config(SystemCoreClock / 1000))
	{
		// Capture error
		while (1){};
	}

	// GPIOD Periph clock enable
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	// Configure PD12, PD13, PD14 and PD15 in output pushpull mode
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	int iteration = 0;
	time_var2 = 0;

	while (1)
	{
		GPIO_SetBits(GPIOD, GPIO_Pin_12);
		Delay(500);
		GPIO_ResetBits(GPIOD, GPIO_Pin_12);
		Delay(500);

		printf("Time:      %lu\n", time_var2);
		printf("Iteration: %i\n", iteration);

		iteration++;
	}

	return 0;
}

/*
 * Called from systick handler
 */
void timing_handler()
{
	if (time_var1)
		time_var1--;

	time_var2++;
}

/*
 * Delay a number of systick cycles (1ms)
 */
void Delay(volatile uint32_t nCount)
{
	time_var1 = nCount;
	while (time_var1);
}

/**
  * @brief   This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
	timing_handler();
}
