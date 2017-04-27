#include <Arduino.h>
#include <Thread.h>
#include <ThreadController.h>
int i = 0;
int j = 0;
//https://github.com/ivanseidel/ArduinoThread/blob/master/examples/SimpleThread/SimpleThread.ino
Thread myThread1 = Thread();
Thread myThread2 = Thread();
ThreadController controll = ThreadController();
// callback for myThread
void niceCallback1(){
  Serial.println("Callback (1):" + String(i));  
  i = i + 1;
  if (i = 10){
    i = 0;
  }
}

void niceCallback2(){
  Serial.println("Callback (2):" + String(i));  
  i = i + 1;
}

void setup(){
  Serial.begin(9600);
  myThread1.onRun(niceCallback1);   
  myThread1.setInterval(5000);
  myThread2.onRun(niceCallback2);   
  myThread2.setInterval(1000);

  controll.add(&myThread1); // & to pass the pointer to it
  controll.add(&myThread2);
}

void loop(){
  controll.run();
  j++;
  delay(500);
  Serial.println("loop " + String(j));
  if(j == 10){
	  controll.remove(myThread2.ThreadID);
  }
  if(j == 20){
    controll.add(&myThread2);
  }
  if(j == 30){
    Serial.println("reset loop ");
    j = 0;
  }
}
