#include "io430g2553.h"
int count = 0;
void GPIO_Init(){
	P1DIR |= BIT2; // P1.2输出并复用
	P1OUT |= BIT2;
	//P1SEL |= BIT2;
}
void TimerA_Init(){
	// 时钟源选择SMCLK，增计数模式
	TA0CTL |= MC_1 + TASSEL_1;  

	// 设置DCO时钟频率，默认是1MHz,这里选择12MHz
	BCSCTL1 = CALBC1_12MHZ;
	DCOCTL = CALDCO_12MHZ;

        TA0CCTL1 = OUTMOD_7;  // 模式7  高电平PWM输出,计数到CCR1就置0，到CCR0就置1
	TA0CCR0 = 1000-1;  //设置频率是10HZ
	TA0CCR1 = 750;  //  设置占空比为75%（高电平占75%，低电平占25%）

}
int main(void){
	// Stop watchdog timer to prevent time out reset
	WDTCTL = WDTPW + WDTHOLD;
	GPIO_Init();
	TimerA_Init();
	while(1){
          LPM0;// 开启低功耗模式0，进入低功耗模式，等待中断
	}
	return 0;
}
#pragma vector = TIMER0_A0_VECTOR
__interrupt void time(){
	if(++count == 10){
		P1OUT |= BIT2;
		count = 0;
	}
}
#pragma vector = TIMER0_A1_VECTOR
__interrupt void timeA(){
	switch(TAIV)
        {
        case 2:P1OUT &=~ BIT2;break;
        }
}