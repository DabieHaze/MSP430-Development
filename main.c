#include "io430.h"
//static unsigned char temp = 0XAA;
// 1Hz����
int count = 0;
int flag = 0;
void init(){
  P2DIR = 0xff;             //�趨P2Ϊ���
  P1DIR &=~ BIT3;           //�趨P1.3Ϊ����
  P2OUT &=~ (BIT0+BIT2+BIT4+BIT6)
    ;   
  P2OUT |= (BIT1+BIT3+BIT5+BIT7);
  TA0CCTL0 = CCIE;     //���ж� (Timer0_A3 Capture/Compare Control 0 )
  TA0CCR0 = 1000 ;      //�趨��������
  TA0CTL = TASSEL_2 + MC_1; //��ʱ��ѡ��ʱ��SMCLK��ʹ��ģʽ1����������ʽ,Ĭ��ID_0��1��Ƶ��
  P1IE |= BIT3;
  P1IES |= BIT3;
  //  _EINT();       //�����ж�
  __enable_interrupt();

}
int main( void )
{
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;    // �رտ��Ź�
  
  init();
  while(1)
  {     LPM0;      }    //�����͹���ģʽ0������͹���ģʽ���ȴ��жϻ��� 

}
#pragma vector = TIMER0_A0_VECTOR
__interrupt void time()
{
  //if(flag == 0){
    //if(count == 1000){
      //P2OUT ^= (BIT0+BIT2+BIT4+BIT6);         //ȡ��
      //P2OUT ^= (BIT1+BIT3+BIT5+BIT7);
      
      //P2OUT ^= BIT0;
      //count = 0;}      
   /* else{
     count++;
    }
  }
  else{
     */if(count == 500){
      // P2OUT ^= (BIT0+BIT2+BIT4+BIT6);         //ȡ��
      // P2OUT ^= (BIT1+BIT3+BIT5+BIT7);
       P2OUT ^= BIT0;
      count = 0; }      
     else{
      count++;
    }
  //}
 
}

#pragma vector = PORT1_VECTOR
__interrupt void P1_ISR(void)
{
  if(P1IFG&BIT3){
    if(flag == 0){
      flag = 1;
    }
    else{
      flag = 0;
    }
  }
  P1IFG = 0;
}



