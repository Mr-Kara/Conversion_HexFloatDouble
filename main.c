#include "stdio.h"
#include "stdint.h"
#include "string.h"

#define NUMBER_OF_BYTE_FLOAT 4
#define NUMBER_OF_BYTE_DOUBLE 8

void hexToFloat_way1(uint8_t* hData);
void hexToFloat_way2(uint32_t hData);
void hexToFloat_way3(uint8_t* hData);
void hexToFloat_way4(uint32_t hData);
void hexToDouble_way1(uint8_t* hData);
void hexToDouble_way2(uint64_t hData);
void floatToHex(float fData);
void doubleToHex(double dData);


// 32bits test data
uint8_t hData_1[NUMBER_OF_BYTE_FLOAT] = { 0x42,0x1F,0x83,0x7B }; //39.8784
uint32_t hData_2 = 0x421F837B; //39.8784

//***************

float fData_1 = 39.8784;



//64 bits test data
uint8_t hDouble_data1[NUMBER_OF_BYTE_DOUBLE] = { 0x40,0x43,0xF0,0x6D,0xD6,0x9D,0x30,0x27 };

uint64_t hDouble_data2 = 0x4043f06dd69d3027; //39.878352

//*****************

double hDouble_data3 = 39.878352;


typedef union
{
	uint32_t u32_data;
	float float_data;
}convert_float;

typedef union
{
	uint64_t u64_data;
	double double_data;
}convert_double;

void main()
{
	//hex to float
	hexToFloat_way1(hData_1); //memcpy  -- uint8_t* 4. basamakta 2 fazla 
	hexToFloat_way2(hData_2); //memcpy  -- uint32_t daha yakýn sonuc veriyor

	hexToFloat_way3(hData_1); //union   -- uint8_t* 4. basamakta 2 fazla 
	hexToFloat_way4(hData_2); //union	-- uint32_t daha yakýn sonuc veriyor


	//hexx to double
	hexToDouble_way1(hDouble_data1); //union -- uint8_t* kesin sonuç
	hexToDouble_way2(hDouble_data2); //union -- uint64_t kesin sonuç


	//float to hex
	floatToHex(fData_1); // union -- float - kesin sonuç

	//double to hex
	doubleToHex(hDouble_data3); // union - double - kesin sonuç


}


void hexToFloat_way1(uint8_t* hData)
{
	float result;
	uint32_t temp;
	temp = (hData[0] << 24) + (hData[1] << 16) + (hData[2] << 8) + (hData[4]);
	memcpy(&result, &temp, sizeof(result));
	printf("hexToFloat_way1 - %f\n", result);

}

void hexToFloat_way2(uint32_t hData)
{
	float result;
	memcpy(&result, &hData, sizeof(result));
	printf("hexToFloat_way2 - %f\n", result);

}

void hexToFloat_way3(uint8_t* hData)
{
	convert_float convert;
	convert.u32_data = (hData[0] << 24) + (hData[1] << 16) + (hData[2] << 8) + (hData[4]);

	printf("hexToFloat_way3 - %f\n", convert.float_data);
}

void hexToFloat_way4(uint32_t hData)
{
	convert_float convert;
	convert.u32_data = hData;

	printf("hexToFloat_way4 - %f\n", convert.float_data);
}


void hexToDouble_way1(uint8_t* hData)
{
	convert_double convert;

	convert.u64_data = (uint64_t)((uint64_t)hData[0] << 56) + 
		((uint64_t)hData[1] << 48) + ((uint64_t)hData[2] << 40) +  
		((uint64_t)hData[3] << 32) + ((uint64_t)hData[4] << 24) + 
		((uint64_t)hData[5] << 16) + ((uint64_t)hData[6] << 8) + 
		((uint64_t)hData[7]);
	
	printf("hexToDouble_way1 - %lf\n", convert.double_data);

}

void hexToDouble_way2(uint64_t hData)
{
	convert_double convert;
	convert.u64_data = hData;
	printf("hexToDouble_way2 - %lf\n", convert.double_data);
}



void floatToHex(float fData)
{
	convert_float convert;
	convert.float_data = fData;

	printf("floatToHex - %X\n", convert.u32_data);
}




void doubleToHex(double dData)
{
	convert_double convert;
	convert.double_data = dData;
	printf("doubleToHex - %llX\n", convert.u64_data);

}
