/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint8_t counter = 0;   // Biến lưu giá trị đếm từ 0 đến 99
uint8_t running = 0;   // Biến trạng thái đếm (0: Dừng, 1: Đang đếm)
uint32_t lastTick = 0; // Biến lưu mốc thời gian phục vụ bộ đếm 1 giây
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);

/* USER CODE BEGIN PFP */
void DisplayDigit(uint8_t num);
void DisplayDigitUnits(uint8_t num);
void Display2Digit(uint8_t num);
void ScanButton(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

void DisplayDigit(uint8_t num)
{
    // Tắt toàn bộ các đoạn của LED hàng chục (Mức CAO là TẮT đối với cực âm chung)
    HAL_GPIO_WritePin(GPIOA, a_Pin|b_Pin|c_Pin|d_Pin|e_Pin|f_Pin|g_Pin|dp_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOB, d_Pin|e_Pin|f_Pin|g_Pin, GPIO_PIN_SET);

    switch(num)
    {
        case 0:
            HAL_GPIO_WritePin(GPIOA, a_Pin|b_Pin|c_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, d_Pin|e_Pin|f_Pin, GPIO_PIN_RESET);
            break;
        case 1:
            HAL_GPIO_WritePin(GPIOA, b_Pin|c_Pin, GPIO_PIN_RESET);
            break;
        case 2:
            HAL_GPIO_WritePin(GPIOA, a_Pin|b_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, d_Pin|e_Pin|g_Pin, GPIO_PIN_RESET);
            break;
        case 3:
            HAL_GPIO_WritePin(GPIOA, a_Pin|b_Pin|c_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, d_Pin|g_Pin, GPIO_PIN_RESET);
            break;
        case 4:
            HAL_GPIO_WritePin(GPIOA, b_Pin|c_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, f_Pin|g_Pin, GPIO_PIN_RESET);
            break;
        case 5:
            HAL_GPIO_WritePin(GPIOA, a_Pin|c_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, d_Pin|f_Pin|g_Pin, GPIO_PIN_RESET);
            break;
        case 6:
            HAL_GPIO_WritePin(GPIOA, a_Pin|c_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, d_Pin|e_Pin|f_Pin|g_Pin, GPIO_PIN_RESET);
            break;
        case 7:
            HAL_GPIO_WritePin(GPIOA, a_Pin|b_Pin|c_Pin, GPIO_PIN_RESET);
            break;
        case 8:
            HAL_GPIO_WritePin(GPIOA, a_Pin|b_Pin|c_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, d_Pin|e_Pin|f_Pin|g_Pin, GPIO_PIN_RESET);
            break;
        case 9:
            HAL_GPIO_WritePin(GPIOA, a_Pin|b_Pin|c_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, d_Pin|f_Pin|g_Pin, GPIO_PIN_RESET);
            break;
    }

    // Kéo chân dp_Pin xuống mức THẤP để luôn sáng dấu chấm trên LED hàng chục
    HAL_GPIO_WritePin(GPIOA, dp_Pin, GPIO_PIN_RESET);
}

void DisplayDigitUnits(uint8_t num)
{
    // Tắt toàn bộ các đoạn của LED hàng đơn vị trước khi chuyển số
    HAL_GPIO_WritePin(GPIOA, a1_Pin|b1_Pin|c1_Pin|d1_Pin|e1_Pin|f1_Pin|g1_Pin, GPIO_PIN_SET);

    switch(num)
    {
        case 0:
            HAL_GPIO_WritePin(GPIOA, a1_Pin|b1_Pin|c1_Pin|d1_Pin|e1_Pin|f1_Pin, GPIO_PIN_RESET);
            break;
        case 1:
            HAL_GPIO_WritePin(GPIOA, b1_Pin|c1_Pin, GPIO_PIN_RESET);
            break;
        case 2:
            HAL_GPIO_WritePin(GPIOA, a1_Pin|b1_Pin|d1_Pin|e1_Pin|g1_Pin, GPIO_PIN_RESET);
            break;
        case 3:
            HAL_GPIO_WritePin(GPIOA, a1_Pin|b1_Pin|c1_Pin|d1_Pin|g1_Pin, GPIO_PIN_RESET);
            break;
        case 4:
            HAL_GPIO_WritePin(GPIOA, b1_Pin|c1_Pin|f1_Pin|g1_Pin, GPIO_PIN_RESET);
            break;
        case 5:
            HAL_GPIO_WritePin(GPIOA, a1_Pin|c1_Pin|d1_Pin|f1_Pin|g1_Pin, GPIO_PIN_RESET);
            break;
        case 6:
            HAL_GPIO_WritePin(GPIOA, a1_Pin|c1_Pin|d1_Pin|e1_Pin|f1_Pin|g1_Pin, GPIO_PIN_RESET);
            break;
        case 7:
            HAL_GPIO_WritePin(GPIOA, a1_Pin|b1_Pin|c1_Pin, GPIO_PIN_RESET);
            break;
        case 8:
            HAL_GPIO_WritePin(GPIOA, a1_Pin|b1_Pin|c1_Pin|d1_Pin|e1_Pin|f1_Pin|g1_Pin, GPIO_PIN_RESET);
            break;
        case 9:
            HAL_GPIO_WritePin(GPIOA, a1_Pin|b1_Pin|c1_Pin|d1_Pin|f1_Pin|g1_Pin, GPIO_PIN_RESET);
            break;
    }
}

void Display2Digit(uint8_t num)
{
    uint8_t tens = num / 10;
    uint8_t units = num % 10;

    // Quét luân phiên độc lập 2 LED đơn cực nhanh để hiển thị rõ ràng ổn định
    DisplayDigit(tens);
    HAL_Delay(5); // Sáng LED hàng chục trong 5ms

    DisplayDigitUnits(units);
    HAL_Delay(5); // Sáng LED hàng đơn vị trong 5ms
}

void ScanButton(void)
{
    static uint8_t oldSet = 1;
    static uint8_t oldReset = 1;

    uint8_t set = HAL_GPIO_ReadPin(GPIOB, Set_Pin);
    uint8_t reset = HAL_GPIO_ReadPin(GPIOB, Reset_Pin);

    // 1. Nút bấm Pause / Resume / Start (Tích cực mức THẤP)
    if(set == GPIO_PIN_RESET && oldSet == GPIO_PIN_SET)
    {
        HAL_Delay(20); // Chống rung phím
        if(HAL_GPIO_ReadPin(GPIOB, Set_Pin) == GPIO_PIN_RESET)
        {
            // Nếu đồng hồ đang dừng ở mốc giới hạn 99 và còi đang kêu, nhấn nút này sẽ tự động reset về 00
            if (counter == 99)
            {
                counter = 0;
                HAL_GPIO_WritePin(GPIOB, Buzzer_Pin, GPIO_PIN_RESET); // Tắt còi
                running = 0;
            }
            else
            {
                running = !running; // Đảo trạng thái đếm (Start <-> Pause)
            }
        }
    }

    // 2. Nút bấm Reset (Tích cực mức THẤP)
    if(reset == GPIO_PIN_RESET && oldReset == GPIO_PIN_SET)
    {
        HAL_Delay(20); // Chống rung phím
        if(HAL_GPIO_ReadPin(GPIOB, Reset_Pin) == GPIO_PIN_RESET)
        {
            counter = 0;                                          // Đưa bộ đếm về 0
            running = 0;                                          // Ngưng đếm hoàn toàn
            HAL_GPIO_WritePin(GPIOB, Buzzer_Pin, GPIO_PIN_RESET); // Tắt còi Buzzer nếu đang kêu
        }
    }

    oldSet = set;
    oldReset = reset;
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* MCU Configuration--------------------------------------------------------*/
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();

  /* USER CODE BEGIN 2 */
  lastTick = HAL_GetTick(); // Đồng bộ thời điểm khởi động ban đầu
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
      // 1. Liên tục quét trạng thái nút nhấn
      ScanButton();

      // 2. Nếu trạng thái là đang chạy, tiến hành đếm thời gian
      if(running)
      {
          if(HAL_GetTick() - lastTick >= 1000) // Đếm tiến sau mỗi 1 giây (1000ms)
          {
              lastTick = HAL_GetTick();

              if(counter < 99)
              {
                  counter++;
              }

              // MÔ TẢ CHỨC NĂNG: Khi đồng hồ đạt giá trị 99 sẽ kích hoạt buzzer và ngưng đếm
              if(counter == 99)
              {
                  running = 0; // Ngưng đếm
                  HAL_GPIO_WritePin(GPIOB, Buzzer_Pin, GPIO_PIN_SET); // Kích hoạt còi kêu liên tục
              }
          }
      }

      // 3. Quét hiển thị 2 chữ số lên LED 7 đoạn
      Display2Digit(counter);
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();

  /* Configure GPIO pin Output Level cho PORTA */
  // Đồng bộ chân mới PA2 vào trạng thái SET ban đầu chung với hệ chân hiển thị
  HAL_GPIO_WritePin(GPIOA, b1_Pin|c1_Pin|a1_Pin|f1_Pin
                          |g1_Pin|e1_Pin|d1_Pin|dp_Pin
                          |c_Pin|b_Pin|a_Pin|GPIO_PIN_2, GPIO_PIN_SET);

  /* Configure GPIO pin Output Level cho PORTB */
  HAL_GPIO_WritePin(GPIOB, d_Pin|e_Pin|g_Pin|f_Pin, GPIO_PIN_SET);

  // Đảm bảo chân còi Buzzer luôn xuất mức thấp (RESET) để không bị tự kêu khi bật mạch
  HAL_GPIO_WritePin(GPIOB, Buzzer_Pin, GPIO_PIN_RESET);

  /* Khởi tạo hệ thống các chân Output trên PORTA (Đã bổ sung chân mới GPIO_PIN_2 thay PC15) */
  GPIO_InitStruct.Pin = b1_Pin|c1_Pin|a1_Pin|f1_Pin
                          |g1_Pin|e1_Pin|d1_Pin|dp_Pin
                          |c_Pin|b_Pin|a_Pin|GPIO_PIN_2;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* Khởi tạo hệ thống các chân Output trên PORTB */
  GPIO_InitStruct.Pin = d_Pin|e_Pin|g_Pin|f_Pin|Buzzer_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* Khởi tạo hệ thống chân Input có trở kéo lên (PULLUP) cho 2 nút nhấn trên PORTB */
  GPIO_InitStruct.Pin = Set_Pin|Reset_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

void Error_Handler(void)
{
  __disable_irq();
  while (1)
  {
  }
}
