const int ledOnePin = 7;
const int ledTwoPin = 8;
const int buzzerPin = 5;

const int buttonOnePin = 2;
const int buttonTwoPin = 12;

unsigned long int playerOneMillis = 180000;
unsigned long int playerTwoMillis = 180000;

int currentPlayer = 0;
int previousTime = 0;

int getTime(int player);
void changePlayer();
void finishGame();

void setup() {
  // put your setup code here, to run once:]
  Serial.begin(9600);
  
  pinMode(ledOnePin, OUTPUT);
  pinMode(ledTwoPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(buttonOnePin, INPUT_PULLUP);
  pinMode(buttonTwoPin, INPUT_PULLUP);

  digitalWrite(ledOnePin, HIGH);
  digitalWrite(ledTwoPin, HIGH);
}

void loop() {
  // wait start player
  while(true) {
    if(digitalRead(buttonOnePin) == LOW) {
      currentPlayer = 1;
      break;
    } else if(digitalRead(buttonTwoPin) == LOW) {
      currentPlayer = 2;
      break;
    }
  }
  
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

      previousTime = currentMillis;
    }

    if(playerOneTime == 0 || playerTwoTime == 0){
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

int getTime(int player) {
  int finalTime;
  
  if(player == 1){
    finalTime = (gameTimeMillis - playerOneMillis) / 1000;
  } else if(player == 2) {
    finalTime = (gameTimeMillis - playerTwoMillis) / 1000;
  }

  return finalTime;
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
