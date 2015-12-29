#include <18F4550.h>
#device ADC=8


#FUSES NOWDT                    //No Watch Dog Timer
#FUSES WDT128                   //Watch Dog Timer uses 1:128 Postscale
#FUSES NOBROWNOUT               //No brownout reset
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NOXINST                  //Extended set extension and Indexed Addressing mode disabled (Legacy mode)

#use delay(clock=4MHz,crystal=4MHz)

//bibliotecas
#include <GLCD.c>

#define direita   0
#define dir       pin_c1
#define cima      1
#define cim       pin_c2
#define esquerda  2
#define esq       pin_c4
#define baixo     3
#define bai       pin_c5
char yl[10] = "You Lose!";
struct Dot{
   unsigned int x;
   unsigned int y;
};
struct Dot snake[128];
struct Dot point;
int8   sentido;
int8   size=10;

void mov(){
   int8 i;
   struct Dot aux;
   aux.x = snake[0].x;
   aux.y = snake[0].y;
   switch (sentido){
      case direita:
         if(aux.x==127)
            aux.x=0;
         else
            aux.x++;
      break;
      case cima:
         if(aux.y==0)
            aux.y=63;
         else
            aux.y--;
      break;
      case esquerda:
         if(aux.x==0)
            aux.x=127;
         else
            aux.x--;
      break;
      case baixo:
         if(aux.y==63)
            aux.y=0;
         else
            aux.y++;
      break;
   }
   for(i=1;i<size;i++){
      if(aux.x==snake[i].x && aux.y==snake[i].y){
         glcd_text57(0,0,yl,2,1);
         delay_ms(1000);
         return;
      }
   }
   if(aux.x==point.x && aux.y==point.y){
      size++;
   }
   for(i=size;i>0;i--){
      snake[i].x=snake[i-1].x;
      snake[i].y=snake[i-1].y;
   }
   snake[0].x=aux.x;
   snake[0].y=aux.y;
}

void draw(){
   int8 i;
   glcd_fillScreen(0);
   for(i=1;i<size;i++){
      glcd_pixel(snake[i].x,snake[i].y,1);
   }
   glcd_pixel(point.x,point.y,1);
}

void main(){
   setup_adc_ports(AN0);
   setup_adc(ADC_CLOCK_INTERNAL|ADC_TAD_MUL_0);
   setup_psp(PSP_DISABLED);
   setup_spi(SPI_SS_DISABLED);
   setup_wdt(WDT_OFF);
   setup_timer_0(RTCC_INTERNAL);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DISABLED,0,1);
   setup_timer_3(T3_DISABLED|T3_DIV_BY_1);

   glcd_init(ON);   //inicializa o display
   glcd_fillScreen(0); //limpa display inteiro

   snake[0].x = 64;
   snake[0].y = 32;
   snake[1].x = 63;
   snake[1].y = 32;
   snake[2].x = 62;
   snake[2].y = 32;
   snake[3].x = 61;
   snake[3].y = 32;
   
   point.x = 50;
   point.y = 32;
   while(TRUE){
      if(input(dir)){
         if(sentido!=esquerda)
            sentido = direita;
      }
      else if(input(cim)){
         if(sentido!=baixo)
            sentido = cima;
      }
      else if(input(esq)){
         if(sentido!=direita)
            sentido = esquerda;
      }
      else if(input(bai)){
         if(sentido!=cima)
            sentido = baixo;
      }
      mov();
      draw();
      delay_ms(10);
   }
}
/*    int n;               //circle test
      for(n=0;n<32;n+=3){
         glcd_circle(64, 32, n, NO, 1);
         delay_ms(100);
      }
      glcd_fillScreen(1);
      for(n=0;n<32;n+=3){
         glcd_circle(64, 32, n, NO, 0);
         delay_ms(100);
      }
      glcd_fillScreen(0);*/
      
/*    char Str1[20];       //text test
      Str1 = "Loren Ipsun";
      int n;
      for(n=0;n<4;n++){
         glcd_fillScreen(0);
         glcd_text57(0,0,Str1,n,1);
         delay_ms(500);
      }*/
      
/*    int x,y;       //lazy clock
      float a;
      for(a=0;a<6.2831;a+=0.0523598){
         y=(float)-30*cos(a);
         x=(float)30*sin(a);
         y+=32;
         x+=64;
         glcd_fillScreen(0);
         glcd_circle(64, 32, 32, NO, 1);
         glcd_line(64,32,x,y,1);
         delay_ms(500);
      }*/
      
/* set_adc_channel(0);     //osciloscope
   int8 xa,x,n=0;
   char pt[10],pv[10];
   pt = "100ms";
   pv = "78.25v";
   glcd_text57(0,57,pv,1,1);
   glcd_text57(90,57,pt,1,1);
   while(TRUE){
      n++;
      if(n>127){
         n=1;
         glcd_fillScreen(0);
         glcd_text57(0,57,pv,1,1);
         glcd_text57(90,57,pt,1,1);
      }
      xa=x;
      x=read_adc()/4;
      glcd_line(n-1,xa,n,x,1);
      delay_ms(100);
   }*/
