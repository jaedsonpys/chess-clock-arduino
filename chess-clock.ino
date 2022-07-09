#include <LiquidCrystal_I2C.h>

const int ledOnePin = 7;
const int ledTwoPin = 8;
const int buzzerPin = 5;

const int buttonOnePin = 2;
const int buttonTwoPin = 12;

unsigned long int playerOneMillis = 0;
unsigned long int playerTwoMillis = 0;
long int gameTime = 180000;

int currentPlayer = 0;
int previousTime = 0;

void startGame();
void changePlayer();
void finishGame();
void printTime();

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  // put your setup code here, to run once:]
  Serial.begin(9600);
  
  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Chess clock");
  lcd.setCursor(0, 1);
  lcd.print("Start.");
  
  pinMode(ledOnePin, OUTPUT);
  pinMode(ledTwoPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(buttonOnePin, INPUT_PULLUP);
  pinMode(buttonTwoPin, INPUT_PULLUP);

  startGame();
}

void loop() {
  // wait start player
  startGame();
  
  while(true) {
    if(digitalRead(buttonOnePin) == LOW) {
      currentPlayer = 1;
      break;
    } else if(digitalRead(buttonTwoPin) == LOW) {
      currentPlayer = 2;
      break;
    }
  }

  playerOneMillis = gameTime;
  playerTwoMillis = gameTime;
  
  changePlayer();
  
  while(true) {
    int currentMillis = millis();
    if(currentMillis - previousTime >= 1000) {
      if(currentPlayer == 1) {
        playerOneMillis = playerOneMillis - 1000;
        Serial.print("Player 1: "); Serial.println(playerOneMillis);
      } else if(currentPlayer == 2){
        playerTwoMillis = playerTwoMillis - 1000;
        Serial.print("Player 2: "); Serial.println(playerTwoMillis);
      }

      printTime();
      previousTime = currentMillis;
    }

    if(playerOneMillis == 0 || playerTwoMillis == 0){
      finishGame();
      break;
    }
    
    if(!digitalRead(buttonOnePin) && currentPlayer == 1) {
      changePlayer();
    } else if(!digitalRead(buttonTwoPin) && currentPlayer == 2) {
      changePlayer();
    }
  }
}

void changePlayer() {
  if(currentPlayer == 1){
    digitalWrite(ledTwoPin, HIGH);
    digitalWrite(ledOnePin, LOW);
    currentPlayer = 2;
  } else if(currentPlayer == 2){
    digitalWrite(ledOnePin, HIGH);
    digitalWrite(ledTwoPin, LOW);
    currentPlayer = 1;
  }

  tone(buzzerPin, 1200, 150);
}

void finishGame() {
  if(currentPlayer == 1){
    digitalWrite(ledOnePin, HIGH);
    tone(buzzerPin, 1200);
    delay(300);
    digitalWrite(ledOnePin, LOW);
    noTone(buzzerPin);
    delay(300);
    digitalWrite(ledOnePin, HIGH);
    tone(buzzerPin, 1200);
    delay(300);
    digitalWrite(ledOnePin, LOW);
    noTone(buzzerPin);
  } else if(currentPlayer == 2){
    digitalWrite(ledTwoPin, HIGH);
    tone(buzzerPin, 1200);
    delay(300);
    digitalWrite(ledTwoPin, LOW);
    noTone(buzzerPin);
    delay(300);
    digitalWrite(ledTwoPin, HIGH);
    tone(buzzerPin, 1200);
    delay(300);
    digitalWrite(ledTwoPin, LOW);
    noTone(buzzerPin);
  }
}

void printTime() {
  lcd.clear();
  
  if(currentPlayer == 1) {
    lcd.setCursor(0, 0);
    lcd.print("Player 1");
    lcd.setCursor(0, 1);
    lcd.print(playerOneMillis / 1000);
  } else if(currentPlayer == 2) {
    lcd.setCursor(0, 0);
    lcd.print("Player 2");
    lcd.setCursor(0, 1);
    lcd.print(playerTwoMillis / 1000);
  }
}

void startGame() {
  digitalWrite(ledOnePin, HIGH);
  digitalWrite(ledTwoPin, HIGH);
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Chess clock");
  lcd.setCursor(0, 1);
  lcd.print("Start.");
}
