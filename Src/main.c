/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2018 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f0xx_hal.h"

/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <string.h>
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc;

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ADC_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_USART2_UART_Init(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/
void udelay(void){
	int tempo=10;
	while (tempo)tempo--;

}
void delayus(int tempo){
	while (tempo){udelay();tempo--;}
}
int fputc(int ch, FILE *f){
		HAL_UART_Transmit(&huart1,(uint8_t*)&ch,1,10);
		return ch;
}

void base(ADC_ChannelConfTypeDef adc_s_config){ //Fun��o do Joystick que tem botao ligaod
		int estado;
		uint32_t X, Y, c;
		char valor[6];
		char str[12];
		unsigned char ack;
		// Canal 0
		strcpy(valor,"B"); //B base 
		adc_s_config.Rank = ADC_RANK_CHANNEL_NUMBER;
		adc_s_config.Channel = ADC_CHANNEL_0;
		while(HAL_ADC_Init(&hadc) != HAL_OK) HAL_Delay(1);
		while(HAL_ADC_ConfigChannel(&hadc, &adc_s_config) != HAL_OK) HAL_Delay(1);
		HAL_ADC_Start(&hadc);
		HAL_ADC_PollForConversion(&hadc, 10);
		Y = HAL_ADC_GetValue(&hadc);
		HAL_ADC_Stop(&hadc);
		HAL_ADC_DeInit(&hadc);
		
		sprintf(str,"%d",Y);
		printf("%s",valor); //Manda quem �
		HAL_UART_Receive(&huart1, (uint8_t*)&ack, 1, 10);
		if(ack == '1'){
				printf("%s",str);
		}
}
void garra(ADC_ChannelConfTypeDef adc_s_config){
		uint32_t X, Y;
		char valor[6];
		char str[12];
		unsigned char ack;
		// Canal 1
		strcpy(valor,"G"); //G1 garra 1
		adc_s_config.Rank = ADC_RANK_CHANNEL_NUMBER;
		adc_s_config.Channel = ADC_CHANNEL_1;
		while(HAL_ADC_Init(&hadc) != HAL_OK) HAL_Delay(1);
		while(HAL_ADC_ConfigChannel(&hadc, &adc_s_config) != HAL_OK) HAL_Delay(1);
		HAL_ADC_Start(&hadc);
		HAL_ADC_PollForConversion(&hadc, 10);
		X = HAL_ADC_GetValue(&hadc);
		HAL_ADC_Stop(&hadc);
		HAL_ADC_DeInit(&hadc);
		
		sprintf(str,"%d",Y);
		printf("%s",valor); //Manda quem �
		HAL_UART_Receive(&huart1, (uint8_t*)&ack, 1, 10);
		if(ack == '1'){
				printf("%s",str);
		}
}
void distancia(ADC_ChannelConfTypeDef adc_s_config){
		uint32_t X, Y;
		char valor[6];
		char str[12];
		char unsigned ack;
		// Canal 2
		strcpy(valor,"L"); //L distancia 
		adc_s_config.Rank = ADC_RANK_CHANNEL_NUMBER;
		adc_s_config.Channel = ADC_CHANNEL_2;
		while(HAL_ADC_Init(&hadc) != HAL_OK) HAL_Delay(1);
		while(HAL_ADC_ConfigChannel(&hadc, &adc_s_config) != HAL_OK) HAL_Delay(1);
		HAL_ADC_Start(&hadc);
		HAL_ADC_PollForConversion(&hadc, 10);
		Y = HAL_ADC_GetValue(&hadc);
		HAL_ADC_Stop(&hadc);
		HAL_ADC_DeInit(&hadc);
		
		sprintf(str,"%d",Y);
		printf("%s",valor); //Manda quem �
		HAL_UART_Receive(&huart1, (uint8_t*)&ack, 1, 10);
		if(ack == '2'){
				printf("%s",str);
		}
		
}
void altura(ADC_ChannelConfTypeDef adc_s_config){
		uint32_t X, Y;
		char valor[6];
		char str[12];
	  unsigned char ack;
		// Canal 3
		strcpy(valor,"A"); //A altura 	
		adc_s_config.Rank = ADC_RANK_CHANNEL_NUMBER;
		adc_s_config.Channel = ADC_CHANNEL_3;
		while(HAL_ADC_Init(&hadc) != HAL_OK) HAL_Delay(1);
		while(HAL_ADC_ConfigChannel(&hadc, &adc_s_config) != HAL_OK) HAL_Delay(1);
		HAL_ADC_Start(&hadc);
		HAL_ADC_PollForConversion(&hadc, 10);
		X = HAL_ADC_GetValue(&hadc);
		HAL_ADC_Stop(&hadc);
		HAL_ADC_DeInit(&hadc);
			
		sprintf(str,"%d",Y);
		printf("%s",valor); //Manda quem �
		HAL_UART_Receive(&huart1, (uint8_t*)&ack, 1, 10);
		if(ack == '3'){
				printf("%s",str);
		}
}
void roda_esquerda(ADC_ChannelConfTypeDef adc_s_config){
		uint32_t X, Y;
		char valor[6];
		char str[12];
		unsigned char ack;
		// Canal 0
		strcpy(valor,"E"); // Rodas da esquerda 
		adc_s_config.Rank = ADC_RANK_CHANNEL_NUMBER;
		adc_s_config.Channel = ADC_CHANNEL_0;
		while(HAL_ADC_Init(&hadc) != HAL_OK) HAL_Delay(1);
		while(HAL_ADC_ConfigChannel(&hadc, &adc_s_config) != HAL_OK) HAL_Delay(1);
		HAL_ADC_Start(&hadc);
		HAL_ADC_PollForConversion(&hadc, 10);
		Y = HAL_ADC_GetValue(&hadc);
		HAL_ADC_Stop(&hadc);
		HAL_ADC_DeInit(&hadc);
		
		sprintf(str,"%d",Y); //Converte int para string
		printf("%s",valor); //Manda quem �
		
		do 
		{
				HAL_UART_Receive(&huart1,(uint8_t*)&ack, 1, 10);
		}while (ack != '5'); //aguarda o ack
	
		printf("%s",str); // Manda a string de numeros

}
void roda_direita(ADC_ChannelConfTypeDef adc_s_config){
		uint32_t X, Y;
		char valor[6];
		char str[12];
		unsigned char ack;
		// Canal 2
		strcpy(valor,"D"); //D Rodas direita
		adc_s_config.Rank = ADC_RANK_CHANNEL_NUMBER;
		adc_s_config.Channel = ADC_CHANNEL_2;
		while(HAL_ADC_Init(&hadc) != HAL_OK) HAL_Delay(1);
		while(HAL_ADC_ConfigChannel(&hadc, &adc_s_config) != HAL_OK) HAL_Delay(1);
		HAL_ADC_Start(&hadc);
		HAL_ADC_PollForConversion(&hadc, 10);
		Y = HAL_ADC_GetValue(&hadc);
		HAL_ADC_Stop(&hadc);
		HAL_ADC_DeInit(&hadc);
		
		sprintf(str,"%d",Y); //Converte int para string
		printf("%s",valor); //Manda quem �
		
		do 
		{
				HAL_UART_Receive(&huart1,(uint8_t*)&ack, 1, 10);
		}while (ack != '5'); //aguarda o ack
	
		printf("%s",str); // Manda a string de numeros

}
int le_botao() {
		int botao = 0;
		if(GPIOB->IDR&(1 << 5)) botao = 1;
		return botao;
}
int aguarda_botao(){
		int botao = 0; //NADA
		while(botao == 0)botao = le_botao();
		while(le_botao() != 0) HAL_Delay(1);
		return botao;
}

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  *
  * @retval None
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	int estado;
	
  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_ADC_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
	int botao = 0,i;
	char buf = 'E';
	ADC_ChannelConfTypeDef adc_s_config;;
  HAL_ADC_Init(&hadc);
	
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		botao = aguarda_botao();
  /* USER CODE END WHILE */
    switch (estado) {
      case 0:
        base(adc_s_config);
        break;
      case 1:
        garra(adc_s_config);
        break;
      case 2:
        distancia(adc_s_config);
        break;
      case 3:
        altura(adc_s_config);
        break;
      case 4:
        roda_esquerda(adc_s_config);
        break;
      case 5:
        roda_direita(adc_s_config);
        break;
      default:
        estado = 0;
        break;
    }
  /* USER CODE BEGIN 3 */
    estado = (estado + 1) % 6;
    HAL_Delay(500);
  }
  /* USER CODE END 3 */

}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInit;

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_HSI14;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSI14State = RCC_HSI14_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.HSI14CalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL12;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* ADC init function */
static void MX_ADC_Init(void)
{

  ADC_ChannelConfTypeDef sConfig;

    /**Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion) 
    */
  hadc.Instance = ADC1;
  hadc.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1;
  hadc.Init.Resolution = ADC_RESOLUTION_12B;
  hadc.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc.Init.ScanConvMode = ADC_SCAN_DIRECTION_FORWARD;
  hadc.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc.Init.LowPowerAutoWait = DISABLE;
  hadc.Init.LowPowerAutoPowerOff = DISABLE;
  hadc.Init.ContinuousConvMode = DISABLE;
  hadc.Init.DiscontinuousConvMode = DISABLE;
  hadc.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc.Init.DMAContinuousRequests = DISABLE;
  hadc.Init.Overrun = ADC_OVR_DATA_PRESERVED;
  if (HAL_ADC_Init(&hadc) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure for the selected ADC regular channel to be converted. 
    */
  sConfig.Channel = ADC_CHANNEL_0;
  sConfig.Rank = ADC_RANK_CHANNEL_NUMBER;
  sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure for the selected ADC regular channel to be converted. 
    */
  sConfig.Channel = ADC_CHANNEL_1;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure for the selected ADC regular channel to be converted. 
    */
  sConfig.Channel = ADC_CHANNEL_4;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure for the selected ADC regular channel to be converted. 
    */
  sConfig.Channel = ADC_CHANNEL_8;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* USART1 init function */
static void MX_USART1_UART_Init(void)
{

  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_RS485Ex_Init(&huart1, UART_DE_POLARITY_HIGH, 0, 0) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* USART2 init function */
static void MX_USART2_UART_Init(void)
{

  huart2.Instance = USART2;
  huart2.Init.BaudRate = 38400;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
*/
static void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);

  /*Configure GPIO pin : PC13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : PA5 */
  GPIO_InitStruct.Pin = GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
void _Error_Handler(char *file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
