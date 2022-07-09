const int ledOnePin = 7;
const int ledTwoPin = 8;
const int buzzerPin = 6;

const int buttonOnePin = 2;
const int buttonTwoPin = 13;

int playerOneMillis = 0;
int playerTwoMillis = 0;

const int gameTimeMillis = 180000;  // 3 minutes

int getTime(int player);

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

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
