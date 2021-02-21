#include "io430.h"
//static unsigned char temp = 0XAA;
// 1Hz方波
int count = 0;
int flag = 0;
void init(){
  P2DIR = 0xff;             //设定P2为输出
  P1DIR &=~ BIT3;           //设定P1.3为输入
  P2OUT &=~ (BIT0+BIT2+BIT4+BIT6)
    ;   
  P2OUT |= (BIT1+BIT3+BIT5+BIT7);
  TA0CCTL0 = CCIE;     //打开中断 (Timer0_A3 Capture/Compare Control 0 )
  TA0CCR0 = 1000 ;      //设定计数变量
  TA0CTL = TASSEL_2 + MC_1; //定时器选择时钟SMCLK，使用模式1连续计数方式,默认ID_0（1分频）
  P1IE |= BIT3;
  P1IES |= BIT3;
  //  _EINT();       //开总中断
  __enable_interrupt();

}
int main( void )
{
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;    // 关闭看门狗
  
  init();
  while(1)
  {     LPM0;      }    //开启低功耗模式0，进入低功耗模式，等待中断唤醒 

}
#pragma vector = TIMER0_A0_VECTOR
__interrupt void time()
{
  //if(flag == 0){
    //if(count == 1000){
      //P2OUT ^= (BIT0+BIT2+BIT4+BIT6);         //取反
      //P2OUT ^= (BIT1+BIT3+BIT5+BIT7);
      
      //P2OUT ^= BIT0;
      //count = 0;}      
   /* else{
     count++;
    }
  }
  else{
     */if(count == 500){
      // P2OUT ^= (BIT0+BIT2+BIT4+BIT6);         //取反
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



