#include <Keypad.h>
#include <Servo.h>

const byte sor = 4;
const byte oszlop = 3;
char keys[sor][oszlop] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
byte sorPin[sor] = {8, 7, 6, 5};
byte oszlopPin[oszlop] = {4, 3, 2};
Keypad keypad = Keypad( makeKeymap(keys), sorPin, oszlopPin, sor, oszlop );
Servo szervo1, szervo2;

#define pwhossz 6
#define nyitvatartasiido 5000
char bevittjelszo[pwhossz];
char belepekod[pwhossz] = "9753#";
char mesterkod[pwhossz] = "9999#";
char Zaro[pwhossz] = "*****";
byte gombok_megnyomva = 0, master_count = 0;
bool duplazar = false;
char customKey;
int jo = 10;
int rossz = 11;
int on_off = 12;
int helytelenprobalkozasok = 0;
bool helytelen = false;
int i;
int gomb = 13;
bool elso = true;
const int buzzer = 9;



void setup() {
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600);
  szervo1.attach(14);
  szervo2.attach(15);
  pinMode(jo, OUTPUT);
  pinMode(rossz, OUTPUT);
  pinMode(on_off, OUTPUT);
  pinMode(gomb, INPUT);
  szervo1.write(5);        
  szervo2.write(180);
}

void loop() {

 /* if (digitalRead(gomb) == HIGH)
  {
    digitalWrite(jo, HIGH);
    delay(1000);
    szervo1.write(175);
    digitalWrite(jo, LOW);
    delay(nyitvatartasiido); //15mp
    szervo1.write(5);
  }*/


  char keypressed = keypad.getKey();
  digitalWrite(jo, LOW);
  digitalWrite(rossz, LOW);
  digitalWrite(on_off, HIGH);


  if (keypressed)
  {
    bevittjelszo[gombok_megnyomva] = keypressed;
    digitalWrite(jo, HIGH);
    tone(buzzer, 1000);
    delay(100);
    noTone(buzzer);
    digitalWrite(jo, LOW);
    gombok_megnyomva++;
  }

  if (gombok_megnyomva == pwhossz - 1)
  {

    if (helytelen == false)
    {
      if (strcmp(bevittjelszo, belepekod) == 0)
      {
        Serial.println("Elfogadva!");
        delay(500);
        digitalWrite(jo, HIGH);
        tone(buzzer, 1000);
        delay(1000);
        noTone(buzzer);
        digitalWrite(jo, LOW);
        szervo1.write(180);
        //delay(nyitvatartasiido);
        //szervo1.write(5);
      }
      else if (strcmp(bevittjelszo, Zaro) == 0)
      {
        Serial.println("Zárolás");
        delay(500);
        for (i = 0; i < 2; i++)
        {
          digitalWrite(jo, HIGH);
          tone(buzzer, 1000);
          delay(200);
          noTone(buzzer);
          digitalWrite(jo, LOW);
          delay(200);
        }
        szervo1.write(5);
      }
      else
      {
        Serial.println("Hibás!");
        delay(500);
        for (i = 0; i < 3; i++)
        {
          digitalWrite(rossz, HIGH);
          tone(buzzer, 1000);
          delay(100);
          noTone(buzzer);
          digitalWrite(rossz, LOW);
          delay(100);
        }
        Serial.print("Hibás próbálkozások száma: ");
        Serial.print(helytelenprobalkozasok + 1);
        Serial.println();
        helytelenprobalkozasok++;

      }
      if (helytelenprobalkozasok == 3)
      {
        helytelen = true;
      }

    }
    if (helytelen == true)
    {

      if (strcmp(bevittjelszo, mesterkod) == 0)
      {
        Serial.println("Mesterkód elfogadva!");
        delay(500);
        for (i = 0; i < 1; i++)
        {
          digitalWrite(rossz, HIGH);
          digitalWrite(jo, HIGH);
          tone(buzzer, 1000);
          delay(1000);
          noTone(buzzer);
          digitalWrite(rossz, LOW);
          digitalWrite(jo, LOW);
          //delay(400);
        }
        szervo2.write(180);
        szervo1.write(180);
        //delay(nyitvatartasiido);
        //szervo1.write(5);
        helytelen = false;
        helytelenprobalkozasok = 0;
      }
      else
      {
        Serial.println("Túl sok hibás próbálkozás, kérem adja meg a mesterkódot!!!");
        delay(500);
        szervo2.write(5);
        for (i = 0; i < 2; i++)
        {
          digitalWrite(rossz, HIGH);
          delay(200);
          digitalWrite(rossz, LOW);
          delay(200);
          digitalWrite(jo, HIGH);
          delay(200);
          digitalWrite(jo, LOW);
          delay(200);
        }
      }
    }

    delay(400);
    Serial.flush();
    jelszoreset();
  }
}


void jelszoreset()
{
  while (gombok_megnyomva != 0)
  {
    bevittjelszo[gombok_megnyomva--] = 0;
  }
  return;
}




