const int ledOnePin = 7;
const int ledTwoPin = 8;
const int buzzerPin = 5;

const int buttonOnePin = 2;
const int buttonTwoPin = 13;

int playerOneMillis = 0;
int playerTwoMillis = 0;
int currentPlayer = 0;

const int gameTimeMillis = 180000;  // 3 minutes

int getTime(int player);
void changePlayer();

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
}

void loop() {
  // put your main code here, to run repeatedly:
  changePlayer();
  
  while(true) {
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
