#include "io430g2553.h"
int count = 0;
void GPIO_Init(){
	P1DIR |= BIT2; // P1.2���������
	P1OUT |= BIT2;
	//P1SEL |= BIT2;
}
void TimerA_Init(){
	// ʱ��Դѡ��SMCLK��������ģʽ
	TA0CTL |= MC_1 + TASSEL_1;  

	// ����DCOʱ��Ƶ�ʣ�Ĭ����1MHz,����ѡ��12MHz
	BCSCTL1 = CALBC1_12MHZ;
	DCOCTL = CALDCO_12MHZ;

        TA0CCTL1 = OUTMOD_7;  // ģʽ7  �ߵ�ƽPWM���,������CCR1����0����CCR0����1
	TA0CCR0 = 1000-1;  //����Ƶ����10HZ
	TA0CCR1 = 750;  //  ����ռ�ձ�Ϊ75%���ߵ�ƽռ75%���͵�ƽռ25%��

}
int main(void){
	// Stop watchdog timer to prevent time out reset
	WDTCTL = WDTPW + WDTHOLD;
	GPIO_Init();
	TimerA_Init();
	while(1){
          LPM0;// �����͹���ģʽ0������͹���ģʽ���ȴ��ж�
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