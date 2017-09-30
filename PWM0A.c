#include "PWM0A.h"
#include "HW_timer.h"
#include "HW_gpio.h"
#include "SysCtrl.h"

void PWM0A_Init(void){

//! GPIO for timer 0A.	
	//Enable clock for GPIO PIN <PB6> <PB7>.	
  clock_Enable_PORT(Clock_PortB);	
	//ckeck lock
	GPIO_PORTB_lock=0x4c4f434b;
	GPIO_PORTB_CR|=0x00000040;
	//Direction output.
	GPIO_PORTB_DIR|=(1<<PB6);
	//Select alternating Function for PORTB pins as digital
	GPIO_PORTB_AFSEL|=0x40;
	// Access port functions from control table to timer0.
	GPIO_PORTB_PCTRL|=(GPIO_PORTB_PCTRL&0xF0FFFFFF)+0x07000000;
	//Enable digital function for porte pins
	GPIO_PORTB_DEN|=(1<<PB6);
	//Turn off Analog function
	GPIO_PORTB_AMSEL=0x00;
	
//! Timer0A setup.
  Clock_Enable_Timer(Timer0);	
	TIMER0_16_32_GPTMCTL&=~(1<<0);
	TIMER0_16_32_GPTMCFG=0x00000004;
	TIMER0_16_32_GPTMTAMR=(1<<3)|(1<<1);
	TIMER0_16_32_GPTMTAMR&=~(1<<2);
	TIMER0_16_32_GPTMCTL&=~(1<<6);
	TIMER0_16_32_GPTMTAILR=65535;
	TIMER0_16_32_GPTMTAMATCHR=60000;
	TIMER0_16_32_GPTMCTL|=(1<<0);
	
	
}


void PWM0A_Duty(U32_t duty){
	
	TIMER0_16_32_GPTMTAMATCHR=duty;
}


void PWM0A_Stop(void){
	TIMER0_16_32_GPTMCTL&=~(1<<0);
}

