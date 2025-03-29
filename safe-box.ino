#include <Servo.h> // подключаем библиотеку для работы с сервоприводом
#include <Keypad.h>

#define pik 12 // Пин пищалки
#define servoPin 11 // Пин серво привода

// Подключите к пинам Arduino эти пины KeyPad-а
#define R1 2
#define R2 3
#define R3 4
#define R4 5
#define C1 6
#define C2 7
#define C3 8
#define C4 9

const byte lenthPassword = 4;
const char password[lenthPassword] = {'1','2','3','4'};


Servo servo1; // объявляем переменную servo типа "servo1"


// Picalka //
void Pikalka()
{
  digitalWrite(pik, HIGH);
  delay(50);
  digitalWrite(pik, LOW);
}
// End Pikalka //

// Servo //

void ServoOpen() {
  servo1.write(90); // Ставим серво в позицию 90 градусов

  Pikalka();
  delay(200);
  Pikalka();
}

void ServoClose()
{
  servo1.write(0); // Ставим серво в позицию 0 градусов

  Pikalka();
  delay(50);
  Pikalka();
  delay(50);
  Pikalka();
}

// End Servo //

void setup() {
    pinMode(pik, OUTPUT);
    servo1.attach(servoPin); 
    
    ServoClose();
    
}

// размер KeyPad-a
const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'A','7','4','1'},
  {'0','8','5','2'},
  {'D','9','6','3'},
  {'*','*','*','*'}
};

byte rowPins[ROWS] = {R1, R2, R3, R4};
byte colPins[COLS] = {C1, C2, C3, C4};

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

char result[lenthPassword] = {'0', '0', '0', '0'};
int i = 0;

void loop() {
  char key = keypad.getKey();  
  if (key){
    result[i] = key;
    Pikalka(); // Пикаем
    i++;

    // Если пользователь ввёл последний символ
    if (result[lenthPassword - 1] != '0') 
    {
        // Если пароль правильный
        if (result[0] == password[0] && result[1] == password[1] && result[2] == password[2] && result[3] == password[3])
        {
          // Сбравсываем массив для ввода пароля
          for (int ii = 0; ii != (lenthPassword); ii++)
          {
            result[ii] = '0';
          }
          i = 0; // Сбрасываем счётчик количества символов, который ввёл пользователь
          ServoOpen(); // Открываем доступ для выхода ящику
        } 
        // Если пароль неправильный
        else {
          // Сбравсываем массив для вв// Подключите к пинам Arduino эти пины KeyPad-аода пароля
          for (int ii = 0; ii != (lenthPassword); ii++)
          {
            result[ii] = '0';
          }
          i = 0; // Сбрасываем счётчик количества символов, который ввёл пользователь
          ServoClose(); // Закрываем доступ к выходу ящику
        }
      }
  }
}