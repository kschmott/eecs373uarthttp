/*
    Function uses the ping stream message to find out how many 
    lockers there are.

    If there are no lockers, it will take the full 8 seconds to timeout.

    Requires the huart variable address. "&huart_"
    Returns the number of lockers as an int.
*/ 
int init_stream(UART_HandleTypeDef *huart) {
    uint8_t buffer[1] = {0xFF};
    HAL_StatusTypeDef receiveStatus = HAL_UART_Transmit(huart, buffer, 1, 1000);
    if (receiveStatus != HAL_OK) {
    	printf("Transmit to init box returned error %d", receiveStatus);
    	return 0;
    }
    receiveStatus = HAL_UART_Receive(huart, buffer, 1, 7000);
    if(receiveStatus == HAL_OK) {
        return (buffer[0] >> 2) + 1;
    }
    return 0;
}

/* 
    Sends the close signal to the designated locker number.
    Index must be less than or equal to 64
    One based indexing
*/ 
void close_locker(UART_HandleTypeDef *huart, uint32_t index) {
    uint8_t buffer[1] = {0x00};
    buffer[0] = 4 * (index - 1); // remove the ' - 1' for zero based indexing
    HAL_StatusTypeDef status = HAL_UART_Transmit(huart, buffer, 1, 1000);
    if (HAL_OK != status) {
    	printf("Failed to close locker with %d", status);
    }
} 

/* 
    Sends the open signal to the designated locker number.
    Index must be less than or equal to 64
    One based indexing
*/ 
void open_locker(UART_HandleTypeDef *huart, uint32_t index) {
    uint8_t buffer[1] = {0x00};
    buffer[0] = (4 * (index - 1) ) + 1; // remove the ' - 1' for zero based indexing
    HAL_UART_Transmit(huart, buffer, 1, 1000);
}
