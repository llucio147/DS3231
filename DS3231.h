/*
  DS3231.cpp - Arduino/chipKit library support for the DS3231 I2C Real-Time Clock
  Copyright (C)2015 Rinky-Dink Electronics, Henning Karlsen. All right reserved
  
  This library has been made to easily interface and use the DS3231 RTC with
  an Arduino or chipKit.


  This library was originally developed by the Dev described above, 
  and changed by me (llucio147), 
  the changes in the original library are changing the date and time format to the 
  standard adopted in Brazil, changing the days of the week to Brazilian Portuguese,
  Brazilian months, year also changed to Brazilian Portuguese.
*/
#ifndef DS3231_h
#define DS3231_h

#if defined(__AVR__)
	#include "Arduino.h"
	#include "hardware/avr/HW_AVR_defines.h"
#elif defined(__PIC32MX__)
	#include "WProgram.h"
	#include "hardware/pic32/HW_PIC32_defines.h"
#elif defined(__arm__)
	#include "Arduino.h"
	#include "hardware/arm/HW_ARM_defines.h"
#endif

#define DS3231_ADDR_R	0xD1
#define DS3231_ADDR_W	0xD0
#define DS3231_ADDR		0x68

#define FORMAT_SHORT	1
#define FORMAT_LONG		2

#define FORMAT_LITTLEENDIAN	1
#define FORMAT_BIGENDIAN	2
#define FORMAT_MIDDLEENDIAN	3

#define SEGUNDA		1
#define TERCA		2
#define QUARTA	    3
#define QUINTA	    4
#define SEXTA		5
#define SABADO	    6
#define DOMINGO		7

#define SQW_RATE_1		0
#define SQW_RATE_1K		1
#define SQW_RATE_4K		2
#define SQW_RATE_8K		3

#define OUTPUT_SQW		0
#define OUTPUT_INT		1

class Time
{
public:
	uint8_t		hour;
	uint8_t		min;
	uint8_t		sec;
	uint8_t		date;
	uint8_t		mon;
	uint16_t	year;
	uint8_t		dow;

	Time();
};

class DS3231
{
	public:
		DS3231(uint8_t data_pin, uint8_t sclk_pin);
		void	begin();
		Time	getTime();
		void	setTime(uint8_t hour, uint8_t min, uint8_t sec);
		void	setDate(uint8_t date, uint8_t mon, uint16_t year);
		void	setDOW();
		void	setDOW(uint8_t dow);

		char	*getTimeStr(uint8_t format=FORMAT_LONG);
		char	*getDateStr(uint8_t slformat=FORMAT_LONG, uint8_t eformat=FORMAT_LITTLEENDIAN, char divider='.');
		char	*getDOWStr(uint8_t format=FORMAT_LONG);
		char	*getMonthStr(uint8_t format=FORMAT_LONG);
		long	getUnixTime(Time t);

		void	enable32KHz(bool enable);
		void	setOutput(byte enable);
		void	setSQWRate(int rate);
		float	getTemp();

	private:
		uint8_t _scl_pin;
		uint8_t _sda_pin;
		uint8_t _burstArray[7];
		boolean	_use_hw;

		void	_sendStart(byte addr);
		void	_sendStop();
		void	_sendAck();
		void	_sendNack();
		void	_waitForAck();
		uint8_t	_readByte();
		void	_writeByte(uint8_t value);
		void	_burstRead();
		uint8_t	_readRegister(uint8_t reg);
		void 	_writeRegister(uint8_t reg, uint8_t value);
		uint8_t	_decode(uint8_t value);
		uint8_t	_decodeH(uint8_t value);
		uint8_t	_decodeY(uint8_t value);
		uint8_t	_encode(uint8_t vaule);
#if defined(__arm__)
		Twi		*twi;
#endif
};
#endif
