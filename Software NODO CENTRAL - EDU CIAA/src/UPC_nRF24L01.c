/*
 * UPC_nRF24L01.c

 *
 *  Created on: 6 jul. 2018
 *      Author: mateo
 */


#include"UPC_nRF24L01.h"
#include "sapi_spi.h"
#include "chip.h"
#include "sapi_datatypes.h"
#include "sapi_peripheral_map.h"


//#define GPIO0_IRQHandler IRQ_NRF24L01
// incluir todas las librerias

void SPI_Start (void)
{
	SPIbegin(SPI0);
// incluir la biblioteca Sapi
	Chip_SCU_PinMuxSet(0x6, 7, (SCU_MODE_PULLUP | SCU_MODE_FUNC4)); /* CS1 configured as GPIO0 */
	Chip_GPIO_SetPinDIROutput(LPC_GPIO_PORT, 5, 15); //Chip Select en GPIO0
}

void nRF24L01_Ports_Start(void)
{
	//inicializar los pines CSN y CS
		Chip_SCU_PinMux (6,11,MD_PUP,FUNC0);
		Chip_SCU_PinMux (6,1,MD_PUP,FUNC0);
		//GPIO- SALIDAS
		Chip_GPIO_Init(LPC_GPIO_PORT);

		Chip_GPIO_SetPinDIROutput(LPC_GPIO_PORT,3, 7);//ce
		Chip_GPIO_SetPinDIROutput(LPC_GPIO_PORT,3, 0);//csn

	CSN_HIGH(); // At program start CSN must be set High (Inactive) => Signal usedfor Starting a new SPI Communication
	CE_LOW(); // At program start CE must be set Low (Inactive) => Signal used forturning Standby into RX or TX Mode
}

//*************************************************//
// FUNCTION para Enviar o Recivir Datos del SPI //
//*************************************************//
unsigned char SPI_Transfer(unsigned char byte_to_send)
{



	return (   SPITransfer(SPI0 ,&byte_to_send,1) );// llama la funcion que escribe los datos por el puerto



}




//*********************************************************************//
// FUNCION para Leer o Escribir Registros del nRF24L01 (1 Byte Registers) //
//*********************************************************************//
// Introduce nRF24L01 Register_Address to Read

unsigned char Read_nRF24L01_Register (unsigned char Register_Address) // Funcion que lee un Registro Cualquira de 1byte, solo necesita la Direccion y retorna el valor
{
unsigned char Register_Content, nRF24L01_Status;
CSN_LOW(); // ACTIVATE CSN

// Send Instruction Word while Receiving nRF24L01_Status
nRF24L01_Status=SPI_Transfer(R_REGISTER+Register_Address);

// Receive Data Byte while sending dummydata(ignored by the nRF24L01)
Register_Content=SPI_Transfer(0x00);

CSN_HIGH(); // DEACTIVATE CSN

return(Register_Content); // RETURN Register Content
}



// Introduce nRF24L01 Register_Address and Register_Content to be loaded
void Write_nRF24L01_Register ( unsigned char Register_Address,unsigned char Register_Content )//Escribe un registro simple de 1Byte
{
  unsigned char dummydata, nRF24L01_Status;

  CSN_LOW(); // ACTIVATE CSN

  // Send Instruction Word while Receiving nRF24L01_Status
  nRF24L01_Status=SPI_Transfer(W_REGISTER+Register_Address);

  // Send Data Byte while receiving dummydata
  dummydata=SPI_Transfer(Register_Content);

  CSN_HIGH(); // DEACTIVATE CSN

	while(Read_nRF24L01_Register(Register_Address)!=Register_Content)
	// Verifica el Registro
	{
		CSN_LOW();
		nRF24L01_Status=SPI_Transfer(W_REGISTER+Register_Address);

		dummydata=SPI_Transfer(Register_Content);
		CSN_HIGH();
	}

}


// Funcion para Leer el estado del NRF24L01

unsigned char Read_nRF24L01_Status (void)// Lee el registro de estado del dispositivo. El mismo muestra informacion muy importante pero la misma se lee con una mascara
{
	unsigned char nRF24L01_Status;

	CSN_LOW(); // ACTIVATE CSN

	nRF24L01_Status=SPI_Transfer(NOP); // Send Instruction Word while ReceivingnRF24L01_Status

	CSN_HIGH(); // DEACTIVATE CSN

	return(nRF24L01_Status);
}

// ESCRIBE EL rEGISTRO STATUS
void Write_nRF24L01_Status (unsigned char Register_Content)// escribe sobre el registro de estado, para limpiar flag
{
	unsigned char dummydata, nRF24L01_Status;

	CSN_LOW(); // ACTIVATE CSN

	nRF24L01_Status=SPI_Transfer(W_REGISTER+STATUS_RF);
	// Send Instruction Word (Write STATUS Register) whileReceiving nRF24L01_Status
	dummydata=SPI_Transfer(Register_Content);
	// Send Data Byte while receiving dummydata (discardedby the PIC18)
	CSN_HIGH(); // DEACTIVATE CSN
}

//************************************************************************************//
// FUNCTIONS PARA LEER O ESCRIBIR DIRECCIONES DE REGISTROS (3, 4 or 5 Byte Registers) //
//************************************************************************************//

void Read_nRF24L01_Address_Register ( unsigned char TX_RX_Address_Width,unsigned char Register_Address, unsigned char *Register_Content )// lee un registro de mas de 1 byte, necesita la longitud del dato , y su direccion, el valor lo retorna con un puntero
{
	unsigned char i, nRF24L01_Status;
	CSN_LOW(); // ACTIVATE CSN

	nRF24L01_Status=SPI_Transfer(R_REGISTER+Register_Address);

	for(i=0; i<(TX_RX_Address_Width+2); i++)
	{
	Register_Content[i]=SPI_Transfer(0x00);

	// Receive Data Bytes while sending dummydata (ignored by thenRF24L01)
	}
	CSN_HIGH(); // DEACTIVATE CSN
}


void Write_nRF24L01_Address_Register ( unsigned char TX_RX_Address_Width,unsigned char Register_Address, unsigned char *Register_Content )//Escribe un registro con mas de 1Byte
{
	unsigned char dummydata, i, nRF24L01_Status;
	unsigned char Process_Finished;
	unsigned char Address_Verification[5];
	Process_Finished=0;
	while(!Process_Finished) // The process of writing the Address is repeated until it is confirmed
	{
	CSN_LOW(); // ACTIVATE CSN

	nRF24L01_Status=SPI_Transfer(W_REGISTER+Register_Address);
	// Send Instruction Word while Receiving nRF24L01_Status

		for(i=0; i<(TX_RX_Address_Width+2); i++)
		{
			dummydata=SPI_Transfer(Register_Content[i]);

			// Send Data Byte while receiving dummydata
		}
	CSN_HIGH(); // DEACTIVATE CSN

	Read_nRF24L01_Address_Register(TX_RX_Address_Width, Register_Address,Address_Verification); // The address is read to be sure it was well writen
	Process_Finished=1;

		for(i=0; i<(TX_RX_Address_Width+2); i++)
			// Every address byte that was read is compared with the one defined by the user
		{
			if(Register_Content[i]!=Address_Verification[i])
			{
				Process_Finished=0;
				// When there is a mismatch between them, the variable is set low in order to repeat process
			}
		}
		//Process_Finished=1;
	}
}







unsigned char Read_nRF24L01_RX_Payload ( unsigned char Enable_Checksum,unsigned char TX_RX_Payload_Width, unsigned char *RX_Payload )// Lee el buffer donde se encuentra la informacion recivida del otro dispositivo
{
	unsigned char nRF24L01_Status, TX_Checksum;
	// Two Checksums are defined: TX_Checksum is the one received from TX Device
	unsigned char RX_Checksum, Checksum_Conclusion;
	// RX_Checksum is the one calculated by the RX Device. Both are compared to verify transmission.
	unsigned char i;

	CSN_LOW(); // ACTIVATE CSN

	nRF24L01_Status=SPI_Transfer(R_RX_PAYLOAD); // Send Instruction Word while Receiving nRF24L01_Status

	if(!Enable_Checksum) // Operation in case that Chechsum Byte is NOT used
	{
		for(i=0; i<TX_RX_Payload_Width; i++) // For the whole Payload Width
		{
			RX_Payload[i]=SPI_Transfer(0x00);// Receive Data Bytes while sending dummydata(ignored by the nRF24L01)
		}
	  Checksum_Conclusion=1; // RX_Payload is assumed to be correct
	}
	else if(Enable_Checksum) // Operation in case that Chechsum Byte is used
	{
			RX_Checksum=0b00000000;

			for(i=0; i<TX_RX_Payload_Width; i++) // For the whole Payload Width
			{
				RX_Payload[i]=SPI_Transfer(0x00);
					// Receive Data Bytes while sending dummydata(ignored by the nRF24L01)
				RX_Checksum=RX_Checksum+RX_Payload[i];
					// Update RX Checksum byte with every Data Byte received
			}
			TX_Checksum=SPI_Transfer(0x00); // Receive Checksum Byte from TX Device(an extra bit for Receiveing Payload)
			if(RX_Checksum==TX_Checksum)
			{
			Checksum_Conclusion=1; // RX_Payload is assumed to be correct
			}
			else if(RX_Checksum!=TX_Checksum)
			{
			Checksum_Conclusion=0; // RX_Payload is assumed NOT tobe correct
			}

	}
	CSN_HIGH(); // DEACTIVATE CSN

	return (Checksum_Conclusion);
}




// ESTA FUNCIOIN ESCROBE UN DATO EN TX FIFO PARA SE ENVIADA. If Enable_Checksum is Enabled, a Checksumbyte is also sent (Used in TX Mode only)

void Write_nRF24L01_TX_Payload ( unsigned char Enable_Checksum,unsigned char TX_RX_Payload_Width, unsigned char *TX_Payload )//Escribe sobre el Registro la informacion a ser enviada por el trasmisor
{
	unsigned char nRF24L01_Status, TX_Checksum;
	unsigned char i, dummydata;

	CSN_LOW(); // ACTIVATE CSN
	nRF24L01_Status = SPI_Transfer(W_TX_PAYLOAD);

	if(!Enable_Checksum) // Operation in case that Chechsum
	{
		for(i=0; i<TX_RX_Payload_Width; i++) // For the whole Payload Width
		{
		dummydata=SPI_Transfer(TX_Payload[i]);
		// Send Data Byte while receiving dummydata (discarded by the PIC18)
		}

	}
	else if(Enable_Checksum) // Operation in case that Chechsum Byte is used
	{
		TX_Checksum=0;
		for(i=0; i<TX_RX_Payload_Width; i++) // For the whole Payload Width
		{
			dummydata=SPI_Transfer(TX_Payload[i]);// Send Data Byte while receiving dummydata


			TX_Checksum=TX_Checksum+TX_Payload[i];// Update Checksum byte with every Data Byte form TX_Payload is sent


		}
		dummydata=SPI_Transfer(TX_Checksum);// ENVIA CHECKSUM AL ULTIMO BYTE DEL TX FIFO


	}
	CSN_HIGH(); // DEACTIVATE CSN
}


//**************************************************************************************//
// FUNCTION hace un reset de registro STATUS y limpia la memoria TX y RX //
//**************************************************************************************//
void Reset_nRF24L01_Status_and_nRF24L01_Payloads (void)//Limpia e Inicializa los Registros del Dispositivo
{

	unsigned char nRF24L01_Status;
	CSN_LOW(); // ACTIVATE CSN

	nRF24L01_Status=SPI_Transfer(FLUSH_TX); // Send Instruction to Flush TX while receiving nRF24L01 Status
	CSN_HIGH(); // DEACTIVATE CSN

	delay(); // Minimum CSN=0 delay

	CSN_LOW(); // ACTIVATE CSN
	nRF24L01_Status=SPI_Transfer(FLUSH_RX); // Send Instruction to Flush RX while receiving nRF24L01 Status

	CSN_HIGH(); // DEACTIVATE CSN

	Write_nRF24L01_Status(RX_DR); // Limpia RX_DR flag if it is High
	Write_nRF24L01_Status(TX_DS); // Limpia TX_DS flag if it is High
	Write_nRF24L01_Status(MAX_RT); // Limpia MAX_RT flag if it is High
}

//************************************************************************************* //
// FUNCTION to Start RX Mode and Turn ON the nRF24L01							//
// 																				//
// TX_RX_Address_Width: 0b01 => 3 bytes, 0b10 => 4 bytes, 0b11 => 5 bytes 		//
// Frequency_Channel: from 0b0000000 to 0b1111111 								//
// RF_Data_Rate: 0 => 1Mbps, 1 => 2Mbps 										//
// RF_Output_Power: 0b00 => -18dBm, 0b01 => -12dBm, 0b10 => -6dBm, 0b11 => 0dBm //
// LNA_Gain: 0 => Disabled, 1 => Enabled 										//
// CRC_Setup: 0 => 1byte, 1 => 2byte 											//
// 																				//
// RX_Pipe0_Address: from 3 to 5 bytes 											//
// RX_Pipe1_Address: from 3 to 5 bytes 											//
// RX_Pipe2_Address: 1 byte 													//
// RX_Pipe3_Address: 1 byte 													//
// RX_Pipe4_Address: 1 byte														//
// RX_Pipe5_Address: 1 byte 													//
// 																				//
// Enable_Checksum: 0=> Disable Checksum byte, 									//
// 1 => Enable 1 byte Checksum for RX Payload 									//
// 																				//
// If Enable_Checksum = 0 														//
// RX_Pipe0_Payload_Width: from 1 to 32 										//
// RX_Pipe1_Payload_Width: from 0 to 32 (0 if Disabled) 						//
// RX_Pipe2_Payload_Width: from 0 to 32 (0 if Disabled) 						//
// RX_Pipe3_Payload_Width: from 0 to 32 (0 if Disabled) 						//
// RX_Pipe4_Payload_Width: from 0 to 32 (0 if Disabled)							//
// RX_Pipe5_Payload_Width: from 0 to 32 (0 if Disabled) 						//
// (Summatory of RX_Pipe(i)_Payload_Width <= 32) 								//
// 																				//
// If Enable_Checksum = 1 														//
// RX_Pipe0_Payload_Width: from 1 to 31 										//
// RX_Pipe1_Payload_Width: from 0 to 31 (0 if Disabled) 						//
// RX_Pipe2_Payload_Width: from 0 to 31 (0 if Disabled) 						//
// RX_Pipe3_Payload_Width: from 0 to 31 (0 if Disabled)							//
// RX_Pipe4_Payload_Width: from 0 to 31 (0 if Disabled) 						//
// RX_Pipe5_Payload_Width: from 0 to 31 (0 if Disabled) 						//
// (Summatory of RX_Pipe(i)_Payload_Width <= 26) 								//
// 																				//
//************************************************************************************* //


void Start_RX_Mode_nRF24L01 ( 		unsigned char TX_RX_Address_Width,
unsigned char Frequency_Channel, 	unsigned char RF_Data_Rate,
unsigned char RF_Output_Power, 		unsigned char LNA_Gain,
unsigned char CRC_Setup, 			unsigned char *RX_Pipe0_Address,
unsigned char *RX_Pipe1_Address, 	unsigned char RX_Pipe2_Address,
unsigned char RX_Pipe3_Address, 	unsigned char RX_Pipe4_Address,
unsigned char RX_Pipe5_Address, 	unsigned char Enable_Checksum,
unsigned char RX_P0_Payload_Width, 	unsigned char RX_P1_Payload_Width,
unsigned char RX_P2_Payload_Width, 	unsigned char RX_P3_Payload_Width,
unsigned char RX_P4_Payload_Width, 	unsigned char RX_P5_Payload_Width )
{
	//Write_nRF24L01_Register(RX_PW_P0, RX_P0_Payload_Width);
	//Write_nRF24L01_Register(RX_PW_P1, RX_P0_Payload_Width);
	CE_LOW(); // We rest in Standby I Mode (Low Consumption) until

	Reset_nRF24L01_Status_and_nRF24L01_Payloads();
	// Reset the nRF24L01 Status Register and Flush TX and RX Payload Memories
	Write_nRF24L01_Register (EN_AA, 0b00111111);
	// Enable Auto Acknowledgement for all RX Pipes
	Write_nRF24L01_Register (EN_RXADDR, 0b00111111);
	// Enable all RX Pipes
	Write_nRF24L01_Register (SETUP_AW, TX_RX_Address_Width);
	// Set Width for all Addresses: 0b01 => 3 bytes, 0b10 => 4 bytes, 0b11 => 5 bytes
	Write_nRF24L01_Register (RF_CH, Frequency_Channel);
	// Set the frequency channel nRF24L01 operates on
	Write_nRF24L01_Register (RF_SETUP, RF_Data_Rate*0b1000 + RF_Output_Power*0b10 +LNA_Gain); // Set nRF24L01 RF Data Rate, Power and LNA Gain
	//Write_nRF24L01_Register (RF_SETUP,0X06);
	Write_nRF24L01_Register(CONFIG_RF, EN_CRC + CRCO + PWR_UP + PRIM_RX);
	CE_HIGH();
	Write_nRF24L01_Address_Register (TX_RX_Address_Width, RX_ADDR_P0, RX_Pipe0_Address);
	// Define RX Address for Pipe0 (3, 4 or 5 bytes)

	Write_nRF24L01_Register (RX_ADDR_P2, RX_Pipe2_Address);
	// Define RX Address for Pipe2 (1 byte => MSBytes will be equal to RX_ADDR_P1)
	Write_nRF24L01_Address_Register (TX_RX_Address_Width, RX_ADDR_P1, RX_Pipe1_Address);
		// Define RX Address for Pipe1 (3, 4 or 5 bytes)
	Write_nRF24L01_Register (RX_ADDR_P3, RX_Pipe3_Address);
	// Define RX Address for Pipe3 (1 byte => MSBytes will be equal to RX_ADDR_P1)
	Write_nRF24L01_Register (RX_ADDR_P4, RX_Pipe4_Address);
	// Define RX Address for Pipe4 (1 byte => MSBytes will be equal to RX_ADDR_P1)
	Write_nRF24L01_Register (RX_ADDR_P5, RX_Pipe5_Address);
	// Define RX Address for Pipe5 (1 byte => MSBytes will be equal to RX_ADDR_P1)
	Write_nRF24L01_Register (RX_PW_P0, RX_P0_Payload_Width+Enable_Checksum);
	// Define Payload Width for Pipe0 in RX Mode (extra byte if Checksum is Enabled)
	Write_nRF24L01_Register (RX_PW_P1, RX_P1_Payload_Width+Enable_Checksum);
	// Define Payload Width for Pipe1 in RX Mode (extra byte if Checksum is Enabled)
	Write_nRF24L01_Register (RX_PW_P2, RX_P2_Payload_Width+Enable_Checksum);
	// Define Payload Width for Pipe2 in RX Mode (extra byte if Checksum is Enabled)
	Write_nRF24L01_Register (RX_PW_P3, RX_P3_Payload_Width+Enable_Checksum);
	// Define Payload Width for Pipe3 in RX Mode (extra byte if Checksum is Enabled)
	Write_nRF24L01_Register (RX_PW_P4, RX_P4_Payload_Width+Enable_Checksum);
	// Define Payload Width for Pipe4 in RX Mode (extra byte if Checksum is Enabled)
	Write_nRF24L01_Register (RX_PW_P5, RX_P5_Payload_Width+Enable_Checksum);
	// Define Payload Width for Pipe5 in RX Mode (extra byte if Checksum is Enabled)
	Write_nRF24L01_Register (CONFIG_RF, EN_CRC + CRC_Setup*0b100 + PWR_UP + PRIM_RX);

	delay(); delay();delay(); delay(); delay();
	delay(); delay();delay(); delay(); delay();
	delay(); delay();delay(); delay(); delay();// TIMING CONDITION #1: Delay required between Power Down and Stanby Mode I => 1.5 ms


	}



//************************************************************************************* //
// FUNCTION to Start TX Mode and Turn ON the nRF24L01 //
// //
// TX_RX_Address_Width: 0b01 => 3 bytes, 0b10 => 4 bytes, 0b11 => 5 bytes //
// Frequency_Channel: from 0b0000000 to 0b1111111 //
// RF_Data_Rate: 0 => 1Mbps, 1 => 2Mbps //
// RF_Output_Power: 0b00 => -18dBm, 0b01 => -12dBm, 0b10 => -6dBm, 0b11 => 0dBm //
// LNA_Gain: 0 => Disabled, 1 => Enabled //
// CRC_Setup: 0 => 1byte, 1 => 2byte //
// //
// Auto_Retransmit_Delay: from 0b0000 to 0b1111 //
// Max_Auto_Retransmit: 0 => Disable Auto_Retransmit, //
// from 1 to 15 => Number of Auto_Retransmit Allowed //
// //
// Enable_Checksum: 0=> Disable Checksum byte, //
// 1 => Enable 1 byte Checksum for RX Payload //
// //
// TX_RX_Payload_Width: If Enable_Checksum = 0, from 1 to 32 //
// If Enable_Checksum = 1, from 1 to 31 //
// //
//************************************************************************************* //

void Start_TX_Mode_nRF24L01 ( 		unsigned char TX_RX_Address_Width,
unsigned char Frequency_Channel, 	unsigned char RF_Data_Rate,
unsigned char RF_Output_Power, 		unsigned char LNA_Gain,
unsigned char CRC_Setup, 			unsigned char Auto_Retransmit_Delay,
unsigned char Max_Auto_Retransmit, 	unsigned char Enable_Checksum,
unsigned char TX_RX_Payload_Width )
{

	CE_LOW();
	Reset_nRF24L01_Status_and_nRF24L01_Payloads();
	// Reset the nRF24L01 Status Register and Flush TX and RX Payload Memories
	Write_nRF24L01_Register (EN_AA, 0b00111111);
	// Enable Auto Acknowledgement for all RX Pipes
	Write_nRF24L01_Register (EN_RXADDR, 0b00111111);
	// Enable all RX Pipes
	Write_nRF24L01_Register (SETUP_AW, TX_RX_Address_Width);
	// Set Width for all Addresses: 0b01 => 3 bytes, 0b10 => 4 bytes, 0b11 => 5 bytes
	Write_nRF24L01_Register (SETUP_RETR, Auto_Retransmit_Delay*0b10000 +Max_Auto_Retransmit); // Automatic Retransmission Setup: Delay between and Maximum number
	Write_nRF24L01_Register (RF_CH, Frequency_Channel);
	// Set the frequency channel nRF24L01 operates on
	Write_nRF24L01_Register (RF_SETUP, RF_Data_Rate*0b1000 + RF_Output_Power*0b10 + LNA_Gain);
	// Set nRF24L01 RF Data Rate, Power and LNA Gain
	Write_nRF24L01_Register (RX_PW_P0, TX_RX_Payload_Width+Enable_Checksum);
	// Define Payload Width for Pipe0 (extra byte if Checksum is Enabled)
	Write_nRF24L01_Register (CONFIG_RF,EN_CRC + CRC_Setup*0b100 + PWR_UP + 0*PRIM_RX);
	// nRF24L01 Configuration: TX Mode, Power Up and 2_byte CRC Encoding
	delay(); delay(); delay(); delay();// TIMING CONDITION #1: Delay required between Power Down and Stanby Modes => 1.5 ms

}


//**************************************************************************************//
// FUNCTION to Define TX Address, Load Data to transmit into nRF24L01 and Enable 		//
// TX Mode starting transmission (Used only in TX Mode) 								//
//																						//
// Enable_Checksum: 0=> Disable Checksum byte, 											//
// 1 => Enable 1 byte Checksum for TX Payload 											//
// 																						//
// TX_RX_Address_Width: 0b01 => 3 bytes, 0b10 => 4 bytes, 0b11 => 5 bytes 				//
// TX_Address: from 3 to 5 bytes 														//
// TX_RX_Payload_Width: from 1 to 32 													//
// TX_Payload: from 1 to 32 bytes 														//
// 																						//
//**************************************************************************************//

void Send_Data_TX_Mode_nRF24L01( 			unsigned char Enable_Checksum,
unsigned char TX_RX_Address_Width, 			unsigned char *TX_Address,
unsigned char TX_RX_Payload_Width, 			unsigned char *TX_Payload )
{
	Write_nRF24L01_Address_Register (TX_RX_Address_Width, TX_ADDR, TX_Address);
	// Define TX Address (3, 4 or 5 bytes)
	Write_nRF24L01_Address_Register (TX_RX_Address_Width, RX_ADDR_P0, TX_Address);
	// Define RX Address for Pipe0: equal to TX Address to receive Auto Acknowledgement (3, 4 or 5 bytes)
	Write_nRF24L01_TX_Payload (Enable_Checksum, TX_RX_Payload_Width, TX_Payload);
	// Load Data into nRF24L01 TX FIFO, it will be sent after CE is set High
	CE_HIGH(); // Activate CE to leave Standby I mode and enter RX Mode (nRF24L01 searchs incoming signal)

	delay();delay();delay(); // TIMING CONDITION #2: Delay required between Stanby Modes and RX or TX Mode => 130 us

	delay();delay();// TIMING CONDITION #3: Minimum CE High => 10 us

	CE_LOW(); // Deactivate CE to leave RX Mode (Low Current Consumtion)

	delay();delay(); // TIMING CONDITION #4: Delay required between CE edge and CSN low => 4 us
}

unsigned char Receive_Data_RX_Mode_nRF24L01( unsigned char Enable_Checksum,unsigned char Max_Waiting_ds, unsigned char TX_RX_Payload_Width,unsigned char *RX_Payload,int *datos_SD ){
	unsigned char nRF24L01_Status;
	unsigned char Origin_Pipe;

	CE_LOW(); // Deactivate CE to leave RX Mode (Low Current Consumtion)
	delay(); delay();

	nRF24L01_Status=Read_nRF24L01_Status();
	// Update the nRF24L01 Status to get the Origin_Pipe
	Origin_Pipe=(nRF24L01_Status & RX_P_NO);
	// Data Pipe Number is obtained from the STATUS Register
	Read_nRF24L01_RX_Payload(Enable_Checksum,TX_RX_Payload_Width,RX_Payload); // After Reading the RX FIFO, all data is deleted from FIFO.
	Write_nRF24L01_Status(RX_DR);

		datos_SD[0]= (RX_Payload[4]*10)+RX_Payload[5];

		if(RX_Payload[2] > 128){
		datos_SD[1]= ((-256 + RX_Payload[2])*10 )- RX_Payload[3];
		}else datos_SD[1]= ( RX_Payload[2]*10 )+ RX_Payload[3];

		datos_SD[2]= (RX_Payload[6]*10)+RX_Payload[7];

		if(RX_Payload[0] > 128){
		datos_SD[3]= ((-256 + RX_Payload[0])*10 )- RX_Payload[1];
		}else datos_SD[3]= ( RX_Payload[0]*10 )+ RX_Payload[1];
}
uint8_t dataReady(void){
	uint8_t status;


    status=Read_nRF24L01_Status();

	if ( status & RX_DR ) { return 1;
	status=Read_nRF24L01_Status();}
	else {

	return (0);
	}

}

void Finish_nRF24L01_Operation (void)
{
	unsigned char previous_config_register;

	previous_config_register=Read_nRF24L01_Register(CONFIG_RF);
	// Read the previous CONFIG Register to change just the PWR_UP bit
	Write_nRF24L01_Register(CONFIG_RF, previous_config_register & 0b11111101);

	// Set Power Up bit Low
}

void Finish_SPI_Operation (void)
{
delay();
}

void delay(void){
	unsigned int i=0;
	for(i=0; i< 60000; i++);

}

void CE_HIGH(void){
	//se configura el pin cePin=8 y se coloca alto

	Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,3,7);
}

void CE_LOW(void){
	//se configura el pin cePin=8 y se coloca bajo

	Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,3,7);

}

void CSN_HIGH(void){
//se configura el Pin 	csnPin = 7; se coloca en alto
	//SCU
        delay();	delay();
		Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,3,0);//GPIO 01
		delay();
}

void CSN_LOW(){
//se configura el Pin 	csnPin = 7; se coloca en bajo
	//SCU

	Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,3,0);//GPIO 01
	delay();
}

void MIRF_IRQinit(void){
	//CONFIGURACION DE SCU Y GPIO
	Chip_SCU_PinMux(6,8,MD_PUP|MD_EZI|MD_ZI,FUNC0);
	Chip_GPIO_SetPinDIRInput(LPC_GPIO_PORT, 5, 16);

	//CONFIGURACION DE PINES GPIO COMO PINES DE INTERRUPCION.
	Chip_SCU_GPIOIntPinSel(0, 5, 16); // Configura un pin GPIO como un pin de interrupciÃ³

	//CONFIGURACION DE MODO DE INTERRUPCION
	Chip_PININT_SetPinModeEdge(LPC_GPIO_PIN_INT,PININTCH0);
	Chip_PININT_EnableIntLow(LPC_GPIO_PIN_INT,PININTCH0);

	//CONFIGURA EL NVIC limpieza flag de interrupcion NVIC
	Chip_PININT_ClearRiseStates(LPC_GPIO_PIN_INT,0);

	//LIMPIEZA Y HABILITACION DE FLAG IRQ
	NVIC_ClearPendingIRQ(PIN_INT0_IRQn);
	NVIC_EnableIRQ(PIN_INT0_IRQn);


}

void GPIO0_IRQHandler(void){
    //LIMPIA BANDERA DE INTERRUPCION


	Chip_PININT_ClearIntStatus(LPC_GPIO_PIN_INT,PININTCH0);
	NVIC_ClearPendingIRQ(PIN_INT0_IRQn);

	//Receive_Data_RX_Mode_nRF24L01( 0,0, 8,RX_Payload,datos_SD );
	//Reset_nRF24L01_Status_and_nRF24L01_Payloads ();

}





