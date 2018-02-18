#include "stm32f10x.h"
#include "usr_usart.h"


/**
 * @brief USART_GPIO_Config
 */
void USART_GPIO_Config()
{

    GPIO_InitTypeDef GPIO_Struct;
    RCC_APB1PeriphResetCmd(RCC_APB2Periph_GPIOA,ENABLE);
    /*************Configure USART1 RXD, TXD pin**********************/
    GPIO_Struct.GPIO_Mode=USART_RxD_Mode;
     GPIO_Struct.GPIO_Pin=USART1_NREMAP_RXD_Pin;
     GPIO_Struct.GPIO_Speed=GPIO_Speed_50MHz;

     GPIO_Init(USART1_NREMAP_GPIO,&GPIO_Struct);

     GPIO_Struct.GPIO_Mode=USART_TXD_Mode;
     GPIO_Struct.GPIO_Pin=USART1_NREMAP_TXD_Pin;
     GPIO_Struct.GPIO_Speed=GPIO_Speed_50MHz;

     GPIO_Init(USART1_NREMAP_GPIO,&GPIO_Struct);

}
/**
 * @brief USART_Config
 */

void USART_Config()
{
    USART_InitTypeDef USART1_InitStruct;
//    USART_ClockInitTypeDef USART_Struct;
    /********Clock configuration**********/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    USART1_InitStruct.USART_BaudRate=115200;
    USART1_InitStruct.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
    USART1_InitStruct.USART_Mode=USART_TXD_Mode|USART_RxD_Mode;
    USART1_InitStruct.USART_Parity=USART_Parity_No;
    USART1_InitStruct.USART_StopBits=1;
    USART1_InitStruct.USART_WordLength=8;
    USART_Init(USART1,&USART1_InitStruct);
    /***********Enable USART1***************/
    USART1->CR1|=USART_CR1_UE;

}



/**
 * @brief USART1_SENDBUFFER
 * @param USARTx
 * @param Buffer
 */
void USART1_SENDBUFFER(USART_TypeDef *USARTx, uint8_t *Buffer)
{
    TextBuffer=Buffer;

    /****************check whether transmition is completed*********************/
    while(TextBuffer)
    {
        //waiting for sending completed
        while(USART_GetFlagStatus(USARTx,USART_FLAG_TXE)!=RESET);
        USARTx->DR|=*TextBuffer;
        TextBuffer+=sizeof(uint8_t);

     }

}


/**
 * @brief USART1_RECEIVEBUFFER
 * @param USARTx
 * @return
 */
uint8_t USART1_RECEIVEBUFFER(USART_TypeDef *USARTx)
{
    uint8_t data;
    //waiting or receive completed
    while(USART_GetFlagStatus(USART1,USART_FLAG_RXNE)!=RESET);
    data=USART1->DR;

    return data;
}

