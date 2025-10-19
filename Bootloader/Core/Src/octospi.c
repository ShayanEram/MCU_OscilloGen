/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    octospi.c
  * @brief   This file provides code for the configuration
  *          of the OCTOSPI instances.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include "octospi.h"

/* USER CODE BEGIN 0 */
#include <string.h>

static uint8_t QSPI_WriteEnable(void);
uint8_t QSPI_AutoPollingMemReady(void);
static uint8_t QSPI_Configuration(void);
static uint8_t QSPI_ResetChip(void);
/* USER CODE END 0 */

OSPI_HandleTypeDef hospi1;

/* OCTOSPI1 init function */
void MX_OCTOSPI1_Init(void)
{

  /* USER CODE BEGIN OCTOSPI1_Init 0 */

  /* USER CODE END OCTOSPI1_Init 0 */

  OSPIM_CfgTypeDef sOspiManagerCfg = {0};

  /* USER CODE BEGIN OCTOSPI1_Init 1 */

  /* USER CODE END OCTOSPI1_Init 1 */
  hospi1.Instance = OCTOSPI1;
  hospi1.Init.FifoThreshold = 4;
  hospi1.Init.DualQuad = HAL_OSPI_DUALQUAD_DISABLE;
  hospi1.Init.MemoryType = HAL_OSPI_MEMTYPE_MICRON;
  hospi1.Init.DeviceSize = 21;
  hospi1.Init.ChipSelectHighTime = 1;
  hospi1.Init.FreeRunningClock = HAL_OSPI_FREERUNCLK_DISABLE;
  hospi1.Init.ClockMode = HAL_OSPI_CLOCK_MODE_0;
  hospi1.Init.WrapSize = HAL_OSPI_WRAP_NOT_SUPPORTED;
  hospi1.Init.ClockPrescaler = 4;
  hospi1.Init.SampleShifting = HAL_OSPI_SAMPLE_SHIFTING_HALFCYCLE;
  hospi1.Init.DelayHoldQuarterCycle = HAL_OSPI_DHQC_DISABLE;
  hospi1.Init.ChipSelectBoundary = 0;
  hospi1.Init.DelayBlockBypass = HAL_OSPI_DELAY_BLOCK_BYPASSED;
  hospi1.Init.MaxTran = 0;
  hospi1.Init.Refresh = 0;
  if (HAL_OSPI_Init(&hospi1) != HAL_OK)
  {
    Error_Handler();
  }
  sOspiManagerCfg.ClkPort = 1;
  sOspiManagerCfg.NCSPort = 1;
  sOspiManagerCfg.IOLowPort = HAL_OSPIM_IOPORT_1_LOW;
  if (HAL_OSPIM_Config(&hospi1, &sOspiManagerCfg, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN OCTOSPI1_Init 2 */

  /* USER CODE END OCTOSPI1_Init 2 */

}

void HAL_OSPI_MspInit(OSPI_HandleTypeDef* ospiHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
  if(ospiHandle->Instance==OCTOSPI1)
  {
  /* USER CODE BEGIN OCTOSPI1_MspInit 0 */

  /* USER CODE END OCTOSPI1_MspInit 0 */

  /** Initializes the peripherals clock
  */
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_OSPI;
    PeriphClkInitStruct.OspiClockSelection = RCC_OSPICLKSOURCE_D1HCLK;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
      Error_Handler();
    }

    /* OCTOSPI1 clock enable */
    __HAL_RCC_OCTOSPIM_CLK_ENABLE();
    __HAL_RCC_OSPI1_CLK_ENABLE();

    __HAL_RCC_GPIOF_CLK_ENABLE();
    __HAL_RCC_GPIOE_CLK_ENABLE();
    /**OCTOSPI1 GPIO Configuration
    PF6     ------> OCTOSPIM_P1_IO3
    PF7     ------> OCTOSPIM_P1_IO2
    PF8     ------> OCTOSPIM_P1_IO0
    PF9     ------> OCTOSPIM_P1_IO1
    PF10     ------> OCTOSPIM_P1_CLK
    PE11     ------> OCTOSPIM_P1_NCS
    */
    GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF10_OCTOSPIM_P1;
    HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_OCTOSPIM_P1;
    HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_11;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF11_OCTOSPIM_P1;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /* USER CODE BEGIN OCTOSPI1_MspInit 1 */

  /* USER CODE END OCTOSPI1_MspInit 1 */
  }
}

void HAL_OSPI_MspDeInit(OSPI_HandleTypeDef* ospiHandle)
{

  if(ospiHandle->Instance==OCTOSPI1)
  {
  /* USER CODE BEGIN OCTOSPI1_MspDeInit 0 */

  /* USER CODE END OCTOSPI1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_OCTOSPIM_CLK_DISABLE();
    __HAL_RCC_OSPI1_CLK_DISABLE();

    /**OCTOSPI1 GPIO Configuration
    PF6     ------> OCTOSPIM_P1_IO3
    PF7     ------> OCTOSPIM_P1_IO2
    PF8     ------> OCTOSPIM_P1_IO0
    PF9     ------> OCTOSPIM_P1_IO1
    PF10     ------> OCTOSPIM_P1_CLK
    PE11     ------> OCTOSPIM_P1_NCS
    */
    HAL_GPIO_DeInit(GPIOF, GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9
                          |GPIO_PIN_10);

    HAL_GPIO_DeInit(GPIOE, GPIO_PIN_11);

  /* USER CODE BEGIN OCTOSPI1_MspDeInit 1 */

  /* USER CODE END OCTOSPI1_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */

/* ---------------- Low-level helpers ---------------- */

static uint8_t QSPI_WriteEnable(void) {
    OSPI_RegularCmdTypeDef sCommand = {0};
    sCommand.InstructionMode = HAL_OSPI_INSTRUCTION_1_LINE;
    sCommand.Instruction     = WRITE_ENABLE_CMD;
    sCommand.AddressMode     = HAL_OSPI_ADDRESS_NONE;
    sCommand.DataMode        = HAL_OSPI_DATA_NONE;
    return HAL_OSPI_Command(&hospi1, &sCommand, HAL_OSPI_TIMEOUT_DEFAULT_VALUE);
}

uint8_t QSPI_AutoPollingMemReady(void) {
    OSPI_RegularCmdTypeDef sCommand = {0};
    OSPI_AutoPollingTypeDef sConfig = {0};

    sCommand.InstructionMode = HAL_OSPI_INSTRUCTION_1_LINE;
    sCommand.Instruction     = READ_STATUS_REG_CMD;
    sCommand.AddressMode     = HAL_OSPI_ADDRESS_NONE;
    sCommand.DataMode        = HAL_OSPI_DATA_1_LINE;
    sCommand.NbData          = 1;

    sConfig.Match           = 0x00;
    sConfig.Mask            = 0x01; // WIP bit
    sConfig.MatchMode       = HAL_OSPI_MATCH_MODE_AND;
    sConfig.Interval        = 0x10;
    sConfig.AutomaticStop   = HAL_OSPI_AUTOMATIC_STOP_ENABLE;

    if (HAL_OSPI_Command(&hospi1, &sCommand, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
        return HAL_ERROR;

    if (HAL_OSPI_AutoPolling(&hospi1, &sConfig, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
        return HAL_ERROR;

    return HAL_OK;
}

/* ---------------- Public API ---------------- */

uint8_t CSP_QUADSPI_Init(void) {
    // Here can add JEDEC ID check if needed
    return HAL_OK;
}

uint8_t CSP_QSPI_EraseSector(uint32_t EraseStartAddress ,uint32_t EraseEndAddress) {
    OSPI_RegularCmdTypeDef sCommand = {0};

    while (EraseStartAddress <= EraseEndAddress) {
        if (QSPI_WriteEnable() != HAL_OK) return HAL_ERROR;

        sCommand.InstructionMode = HAL_OSPI_INSTRUCTION_1_LINE;
        sCommand.Instruction     = SECTOR_ERASE_CMD;
        sCommand.AddressMode     = HAL_OSPI_ADDRESS_1_LINE;
        sCommand.AddressSize     = HAL_OSPI_ADDRESS_24_BITS;
        sCommand.Address         = EraseStartAddress;
        sCommand.DataMode        = HAL_OSPI_DATA_NONE;

        if (HAL_OSPI_Command(&hospi1, &sCommand, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
            return HAL_ERROR;

        if (QSPI_AutoPollingMemReady() != HAL_OK) return HAL_ERROR;

        EraseStartAddress += MEMORY_SECTOR_SIZE;
    }
    return HAL_OK;
}

uint8_t CSP_QSPI_EraseBlock(uint32_t flash_address) {
    OSPI_RegularCmdTypeDef sCommand = {0};

    if (QSPI_WriteEnable() != HAL_OK) return HAL_ERROR;

    sCommand.InstructionMode = HAL_OSPI_INSTRUCTION_1_LINE;
    sCommand.Instruction     = BLOCK_ERASE_CMD;
    sCommand.AddressMode     = HAL_OSPI_ADDRESS_1_LINE;
    sCommand.AddressSize     = HAL_OSPI_ADDRESS_24_BITS;
    sCommand.Address         = flash_address;
    sCommand.DataMode        = HAL_OSPI_DATA_NONE;

    if (HAL_OSPI_Command(&hospi1, &sCommand, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
        return HAL_ERROR;

    return QSPI_AutoPollingMemReady();
}

uint8_t CSP_QSPI_WriteMemory(uint8_t* buffer, uint32_t address, uint32_t buffer_size) {
    OSPI_RegularCmdTypeDef sCommand = {0};
    uint32_t current_addr = address;
    uint32_t end_addr = address + buffer_size;
    uint32_t current_size;

    while (current_addr < end_addr) {
        current_size = MEMORY_PAGE_SIZE - (current_addr % MEMORY_PAGE_SIZE);
        if (current_size > (end_addr - current_addr)) current_size = end_addr - current_addr;

        if (QSPI_WriteEnable() != HAL_OK) return HAL_ERROR;

        sCommand.InstructionMode = HAL_OSPI_INSTRUCTION_1_LINE;
        sCommand.Instruction     = FAST_PROG_CMD; // or QUAD_IN_FAST_PROG_CMD if QE bit set
        sCommand.AddressMode     = HAL_OSPI_ADDRESS_1_LINE;
        sCommand.AddressSize     = HAL_OSPI_ADDRESS_24_BITS;
        sCommand.Address         = current_addr;
        sCommand.DataMode        = HAL_OSPI_DATA_1_LINE;
        sCommand.NbData          = current_size;

        if (HAL_OSPI_Command(&hospi1, &sCommand, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
            return HAL_ERROR;

        if (HAL_OSPI_Transmit(&hospi1, buffer, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
            return HAL_ERROR;

        if (QSPI_AutoPollingMemReady() != HAL_OK) return HAL_ERROR;

        current_addr += current_size;
        buffer += current_size;
    }
    return HAL_OK;
}

uint8_t CSP_QSPI_Read(uint8_t* pData, uint32_t ReadAddr, uint32_t Size) {
    OSPI_RegularCmdTypeDef sCommand = {0};

    sCommand.InstructionMode = HAL_OSPI_INSTRUCTION_1_LINE;
    sCommand.Instruction     = QUAD_OUT_FAST_READ_CMD; // or QUAD_IN_OUT_FAST_READ_CMD
    sCommand.AddressMode     = HAL_OSPI_ADDRESS_1_LINE;
    sCommand.AddressSize     = HAL_OSPI_ADDRESS_24_BITS;
    sCommand.Address         = ReadAddr;
    sCommand.DataMode        = HAL_OSPI_DATA_4_LINES;
    sCommand.NbData          = Size;
    sCommand.DummyCycles     = DUMMY_CLOCK_CYCLES_READ_QUAD;

    if (HAL_OSPI_Command(&hospi1, &sCommand, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
        return HAL_ERROR;

    return HAL_OSPI_Receive(&hospi1, pData, HAL_OSPI_TIMEOUT_DEFAULT_VALUE);
}

uint8_t CSP_QSPI_Erase_Chip(void) {
    OSPI_RegularCmdTypeDef sCommand = {0};

    if (QSPI_WriteEnable() != HAL_OK) return HAL_ERROR;

    sCommand.InstructionMode = HAL_OSPI_INSTRUCTION_1_LINE;
    sCommand.Instruction     = CHIP_ERASE_CMD;
    sCommand.AddressMode     = HAL_OSPI_ADDRESS_NONE;
    sCommand.DataMode        = HAL_OSPI_DATA_NONE;

    if (HAL_OSPI_Command(&hospi1, &sCommand, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
        return HAL_ERROR;

    return QSPI_AutoPollingMemReady();
}

uint8_t CSP_QSPI_EnableMemoryMappedMode(void) {
    OSPI_RegularCmdTypeDef sCommand = {0};
    OSPI_MemoryMappedTypeDef sMemMappedCfg = {0};

    // Configure the read command (Quad I/O Fast Read)
    sCommand.OperationType      = HAL_OSPI_OPTYPE_READ_CFG;
    sCommand.FlashId            = HAL_OSPI_FLASH_ID_1;
    sCommand.InstructionMode    = HAL_OSPI_INSTRUCTION_1_LINE;
    sCommand.Instruction        = QUAD_IN_OUT_FAST_READ_CMD; // 0xEB
    sCommand.AddressMode        = HAL_OSPI_ADDRESS_4_LINES;
    sCommand.AddressSize        = HAL_OSPI_ADDRESS_24_BITS;
    sCommand.AlternateBytesMode = HAL_OSPI_ALTERNATE_BYTES_4_LINES;
    sCommand.AlternateBytesSize = HAL_OSPI_ALTERNATE_BYTES_8_BITS;
    sCommand.AlternateBytes     = 0x00;
    sCommand.DataMode           = HAL_OSPI_DATA_4_LINES;
    sCommand.DummyCycles        = DUMMY_CLOCK_CYCLES_READ_QUAD;

    if (HAL_OSPI_Command(&hospi1, &sCommand, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
        return HAL_ERROR;

    // Configure memory-mapped mode
    sMemMappedCfg.TimeOutActivation = HAL_OSPI_TIMEOUT_COUNTER_DISABLE;

    if (HAL_OSPI_MemoryMapped(&hospi1, &sMemMappedCfg) != HAL_OK)
        return HAL_ERROR;

    return HAL_OK;
}

/* USER CODE END 1 */
