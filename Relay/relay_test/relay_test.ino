// Реле модуль подключен к цифровому выводу 4
int Relay = 4;

void setup() 
{                
  pinMode(Relay, OUTPUT);
       
}

void loop() 
{
//  digitalWrite(Relay, LOW);   // реле включено (левая цепь замкнута)
//  delay(2000);               
  digitalWrite(Relay, HIGH);  // реле выключено (правая цепь замкнута)
//  delay(2000);               
}

