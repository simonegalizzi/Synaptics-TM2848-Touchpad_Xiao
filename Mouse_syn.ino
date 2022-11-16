#include <ps2.h>
#include <Mouse.h>


PS2 mouse(5, 4);
byte stato;
byte mx;                  
byte my;
byte precx,precy;
bool pre,clik,avvio=false;
int p,c=0;

      
              


unsigned long t1, dt;
bool new_pos = false;




void mouse_init()
{
  Mouse.begin();
  mouse.write(0xff);  // reset
  mouse.read();  // ack byte
  mouse.read();  // blank */
  mouse.read();  // blank */
  mouse.write(0xf0);  // remote mode
  mouse.read();  // ack
  delayMicroseconds(200);
}

void setup()
{
  //Serial.begin(112500);
  delay(15000);
  mouse_init();
}




void ms_read(){
  
  mouse.write(0xeb);  // give me data!
  mouse.read();      // ignore ack
  stato = mouse.read();
  mx = mouse.read();
  my = mouse.read();
  if ((precx==mx)&&(precy==my)){
    new_pos=false;
  }else{
    new_pos=true;
  }
  precx=mx;
  precy=my;

}
void loop()
{
  ms_read();
  
 
   if (int(stato)==9){
        dt=millis();
        if (dt - t1 >= 350L) {
           pre=true;
        }
        else {
          //Serial.println("click");
          clik=true;
        }

  
  }else{ 
    t1=millis();
  } 

 
  if (clik&&pre){
    p++;
    if (p==1){
    //Serial.println("press..");
    Mouse.press(MOUSE_LEFT);
    }
  }
  if ((clik) && (pre==false)){
    c++;
    if (c==1){
      //Serial.println("click...");
      Mouse.press(MOUSE_LEFT);
    }
    
  }
    
   
    
  
  if (stato==10){
    Mouse.click(MOUSE_RIGHT);      
  }
  if (stato==8){
     if (clik==true){
     Mouse.release(MOUSE_LEFT);
     clik=false;
     pre=false;
     p=0;
     c=0;
    } 
  }
 
  
   if (new_pos==true){
   my = map(my, 0, 256, 256, 0);
   Mouse.move(mx,my);
   }
 

 // delay(150);  
 
}
