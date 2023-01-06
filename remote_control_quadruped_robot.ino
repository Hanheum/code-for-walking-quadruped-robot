#include <Servo.h>

Servo servo[12];

const int deg0[12] = {50, 60, 35, 60, 60, 30, 35, 100, 85, 65, 125, 40};
const int dir[12] = {-1, -1, -1, 1, 1, 1, 1, 1, 1, -1, -1, -1};

float degs1[12] = {60, 60, 35, 60, 60, 40, 25, 90, 80, 65, 125, 40};
float theta1 = 0;
float theta1_last1;
float theta1_last2;
float theta1_last3;
float theta1_last4;
float theta2 = 0;
float theta2_last1;
float theta2_last2;
float theta2_last3;
float theta2_last4;
float dth1;
float dth2;
float last_x;  //x distance between foot1 and foot3

int legs[4][3] = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}, {9, 10, 11}};

const float h = 5;
const float l = 5;
float H = 8;                //fix constants
const float pi = 3.141592;

const float Ax = 7;
const float Ay = 7;
const float Bx = -7;
const float By = 7;
const float Cx = -7;
const float Cy = -7;
const float Dx = 7;
const float Dy = -7;

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 12; i++) {
    servo[i].attach(i + 2);
  }
  two_degs(0, 0);
  theta1_last1 = theta1;
  theta1_last2 = theta1;
  theta1_last3 = theta1;
  theta1_last4 = theta1;
  theta2_last1 = theta2;
  theta2_last2 = theta2;
  theta2_last3 = theta2;
  theta2_last4 = theta2;
}

void still() {
  for (int i = 0; i < 12; i++) {
    servo[i].write(deg0[i]);
    degs1[i] = deg0[i];
  }
  two_degs(0, 0);
  theta1_last1 = theta1;
  theta1_last2 = theta1;
  theta1_last3 = theta1;
  theta1_last4 = theta1;
  theta2_last1 = theta2;
  theta2_last2 = theta2;
  theta2_last3 = theta2;
  theta2_last4 = theta2;
}

void setDeg1(){
  for (int i=0; i<12; i++){
    servo[i].write(degs1[i]);
  }
}

void two_degs(float x, float y){
  float tsq = sq(x)+sq(H-y);
  float th2 = acos((sq(h)+sq(l)-tsq)/(2*h*l));
  float dia = sqrt(tsq)/sin(th2);
  float th3 = asin(l/dia);
  float th4;
  float th1;
  if(x>=0){
    th4 = acos(abs(x)/sqrt(tsq));
    th1 = pi-(th3+th4);
  }else{
    th4 = asin(abs(x)/sqrt(tsq));
    th1 = (pi/2)-(th3+th4);
  }
  theta1 = degrees(th1);
  theta2 = degrees(th2);
  
}

void forward14(float x){
  two_degs(x, 3);
  dth1 = theta1-theta1_last1;
  dth2 = theta2-theta2_last1;
  degs1[legs[0][0]] = degs1[legs[0][0]]+dth2*dir[legs[0][0]];
  degs1[legs[0][1]] = degs1[legs[0][1]]+dth1*dir[legs[0][1]];
  theta1_last1 = theta1;
  theta2_last1 = theta2;
  two_degs(-x, 2);
  dth1 = theta1-theta1_last4;
  dth2 = theta2-theta2_last4;
  degs1[legs[3][0]] = degs1[legs[3][0]]+dth2*dir[legs[3][0]];
  degs1[legs[3][1]] = degs1[legs[3][1]]+dth1*dir[legs[3][1]];
  theta1_last4 = theta1;
  theta2_last4 = theta2;
  setDeg1();
  delay(100);
  two_degs(x, 0);
  dth1 = theta1-theta1_last1;
  dth2 = theta2-theta2_last1;
  degs1[legs[0][0]] = degs1[legs[0][0]]+dth2*dir[legs[0][0]];
  degs1[legs[0][1]] = degs1[legs[0][1]]+dth1*dir[legs[0][1]];
  theta1_last1 = theta1;
  theta2_last1 = theta2;
  two_degs(-x, 0);
  dth1 = theta1-theta1_last4;
  dth2 = theta2-theta2_last4;
  degs1[legs[3][0]] = degs1[legs[3][0]]+dth2*dir[legs[3][0]];
  degs1[legs[3][1]] = degs1[legs[3][1]]+dth1*dir[legs[3][1]];
  theta1_last4 = theta1;
  theta2_last4 = theta2;
  setDeg1();
  delay(100);
  for(int i=5; i>-1; i--){
    two_degs((x/6)*i, 0);
    dth1 = theta1-theta1_last1;
    dth2 = theta2-theta2_last1;
    degs1[legs[0][0]] = degs1[legs[0][0]]+dth2*dir[legs[0][0]];
    degs1[legs[0][1]] = degs1[legs[0][1]]+dth1*dir[legs[0][1]];
    theta1_last1 = theta1;
    theta2_last1 = theta2;

    two_degs((-x/6)*i, 0);
    dth1 = theta1-theta1_last4;
    dth2 = theta2-theta2_last4;
    degs1[legs[3][0]] = degs1[legs[3][0]]+dth2*dir[legs[3][0]];
    degs1[legs[3][1]] = degs1[legs[3][1]]+dth1*dir[legs[3][1]];
    theta1_last4 = theta1;
    theta2_last4 = theta2;

    two_degs((x/6)*(6-i), 0);
    dth1 = theta1-theta1_last2;
    dth2 = theta2-theta2_last2;
    degs1[legs[1][0]] = degs1[legs[1][0]]+dth2*dir[legs[1][0]];
    degs1[legs[1][1]] = degs1[legs[1][1]]+dth1*dir[legs[1][1]];
    theta1_last2 = theta1;
    theta2_last2 = theta2;

    two_degs(-((x+1)/6)*(6-i), 0);
    dth1 = theta1-theta1_last3;
    dth2 = theta2-theta2_last3;
    degs1[legs[2][0]] = degs1[legs[2][0]]+dth2*dir[legs[2][0]];
    degs1[legs[2][1]] = degs1[legs[2][1]]+dth1*dir[legs[2][1]];
    theta1_last3 = theta1;
    theta2_last3 = theta2;
    setDeg1();
    delay(50);
  }
  delay(100);
  two_degs(0, 2);
  dth1 = theta1-theta1_last2;
  dth2 = theta2-theta2_last2;
  degs1[legs[1][0]] = degs1[legs[1][0]]+dth2*dir[legs[1][0]];
  degs1[legs[1][1]] = degs1[legs[1][1]]+dth1*dir[legs[1][1]];
  theta1_last2 = theta1;
  theta2_last2 = theta2;
  two_degs(0, 2);
  dth1 = theta1-theta1_last3;
  dth2 = theta2-theta2_last3;
  degs1[legs[2][0]] = degs1[legs[2][0]]+dth2*dir[legs[2][0]];
  degs1[legs[2][1]] = degs1[legs[2][1]]+dth1*dir[legs[2][1]];
  theta1_last3 = theta1;
  theta2_last3 = theta2;
  setDeg1();
  delay(100);
  two_degs(0, 0);
  dth1 = theta1-theta1_last2;
  dth2 = theta2-theta2_last2;
  degs1[legs[1][0]] = degs1[legs[1][0]]+dth2*dir[legs[1][0]];
  degs1[legs[1][1]] = degs1[legs[1][1]]+dth1*dir[legs[1][1]];
  theta1_last2 = theta1;
  theta2_last2 = theta2;
  two_degs(0, 0);
  dth1 = theta1-theta1_last3;
  dth2 = theta2-theta2_last3;
  degs1[legs[2][0]] = degs1[legs[2][0]]+dth2*dir[legs[2][0]];
  degs1[legs[2][1]] = degs1[legs[2][1]]+dth1*dir[legs[2][1]];
  theta1_last3 = theta1;
  theta2_last3 = theta2;
  setDeg1();
  delay(100);
}

void forward23(float x){
  two_degs(x, 3);
  dth1 = theta1-theta1_last3;
  dth2 = theta2-theta2_last3;
  degs1[legs[2][0]] = degs1[legs[2][0]]+dth2*dir[legs[2][0]];
  degs1[legs[2][1]] = degs1[legs[2][1]]+dth1*dir[legs[2][1]];
  theta1_last3 = theta1;
  theta2_last3 = theta2;
  two_degs(-x, 2);
  dth1 = theta1-theta1_last2;
  dth2 = theta2-theta2_last2;
  degs1[legs[1][0]] = degs1[legs[1][0]]+dth2*dir[legs[1][0]];
  degs1[legs[1][1]] = degs1[legs[1][1]]+dth1*dir[legs[1][1]];
  theta1_last2 = theta1;
  theta2_last2 = theta2;
  setDeg1();
  delay(100);
  two_degs(x, 0);
  dth1 = theta1-theta1_last3;
  dth2 = theta2-theta2_last3;
  degs1[legs[2][0]] = degs1[legs[2][0]]+dth2*dir[legs[2][0]];
  degs1[legs[2][1]] = degs1[legs[2][1]]+dth1*dir[legs[2][1]];
  theta1_last3 = theta1;
  theta2_last3 = theta2;
  two_degs(-x, 0);
  dth1 = theta1-theta1_last2;
  dth2 = theta2-theta2_last2;
  degs1[legs[1][0]] = degs1[legs[1][0]]+dth2*dir[legs[1][0]];
  degs1[legs[1][1]] = degs1[legs[1][1]]+dth1*dir[legs[1][1]];
  theta1_last2 = theta1;
  theta2_last2 = theta2;
  setDeg1();
  delay(100);
  for(int i=5; i>-1; i--){
    two_degs((x/6)*i, 0);
    dth1 = theta1-theta1_last3;
    dth2 = theta2-theta2_last3;
    degs1[legs[2][0]] = degs1[legs[2][0]]+dth2*dir[legs[2][0]];
    degs1[legs[2][1]] = degs1[legs[2][1]]+dth1*dir[legs[2][1]];
    theta1_last3 = theta1;
    theta2_last3 = theta2;

    two_degs((-x/6)*i, 0);
    dth1 = theta1-theta1_last2;
    dth2 = theta2-theta2_last2;
    degs1[legs[1][0]] = degs1[legs[1][0]]+dth2*dir[legs[1][0]];
    degs1[legs[1][1]] = degs1[legs[1][1]]+dth1*dir[legs[1][1]];
    theta1_last2 = theta1;
    theta2_last2 = theta2;

    two_degs((x/6)*(6-i), 0);
    dth1 = theta1-theta1_last4;
    dth2 = theta2-theta2_last4;
    degs1[legs[3][0]] = degs1[legs[3][0]]+dth2*dir[legs[3][0]];
    degs1[legs[3][1]] = degs1[legs[3][1]]+dth1*dir[legs[3][1]];
    theta1_last4 = theta1;
    theta2_last4 = theta2;

    two_degs(-((x+1)/6)*(6-i), 0);
    dth1 = theta1-theta1_last1;
    dth2 = theta2-theta2_last1;
    degs1[legs[0][0]] = degs1[legs[0][0]]+dth2*dir[legs[0][0]];
    degs1[legs[0][1]] = degs1[legs[0][1]]+dth1*dir[legs[0][1]];
    theta1_last1 = theta1;
    theta2_last1 = theta2;
    setDeg1();
    delay(50);
  }
  delay(100);
  two_degs(0, 2);
  dth1 = theta1-theta1_last4;
  dth2 = theta2-theta2_last4;
  degs1[legs[3][0]] = degs1[legs[3][0]]+dth2*dir[legs[3][0]];
  degs1[legs[3][1]] = degs1[legs[3][1]]+dth1*dir[legs[3][1]];
  theta1_last4 = theta1;
  theta2_last4 = theta2;
  two_degs(0, 2);
  dth1 = theta1-theta1_last1;
  dth2 = theta2-theta2_last1;
  degs1[legs[0][0]] = degs1[legs[0][0]]+dth2*dir[legs[0][0]];
  degs1[legs[0][1]] = degs1[legs[0][1]]+dth1*dir[legs[0][1]];
  theta1_last1 = theta1;
  theta2_last1 = theta2;
  setDeg1();
  delay(100);
  two_degs(0, 0);
  dth1 = theta1-theta1_last4;
  dth2 = theta2-theta2_last4;
  degs1[legs[3][0]] = degs1[legs[3][0]]+dth2*dir[legs[3][0]];
  degs1[legs[3][1]] = degs1[legs[3][1]]+dth1*dir[legs[3][1]];
  theta1_last4 = theta1;
  theta2_last4 = theta2;
  two_degs(0, 0);
  dth1 = theta1-theta1_last1;
  dth2 = theta2-theta2_last1;
  degs1[legs[0][0]] = degs1[legs[0][0]]+dth2*dir[legs[0][0]];
  degs1[legs[0][1]] = degs1[legs[0][1]]+dth1*dir[legs[0][1]];
  theta1_last1 = theta1;
  theta2_last1 = theta2;
  setDeg1();
  delay(100);
}

void backward14(float x){
  two_degs(x, 3);
  dth1 = theta1-theta1_last4;
  dth2 = theta2-theta2_last4;
  degs1[legs[3][0]] = degs1[legs[3][0]]+dth2*dir[legs[3][0]];
  degs1[legs[3][1]] = degs1[legs[3][1]]+dth1*dir[legs[3][1]];
  theta1_last4 = theta1;
  theta2_last4 = theta2;
  two_degs(-x, 2);
  dth1 = theta1-theta1_last1;
  dth2 = theta2-theta2_last1;
  degs1[legs[0][0]] = degs1[legs[0][0]]+dth2*dir[legs[0][0]];
  degs1[legs[0][1]] = degs1[legs[0][1]]+dth1*dir[legs[0][1]];
  theta1_last1 = theta1;
  theta2_last1 = theta2;
  setDeg1();
  delay(100);
  two_degs(x, 0);
  dth1 = theta1-theta1_last4;
  dth2 = theta2-theta2_last4;
  degs1[legs[3][0]] = degs1[legs[3][0]]+dth2*dir[legs[3][0]];
  degs1[legs[3][1]] = degs1[legs[3][1]]+dth1*dir[legs[3][1]];
  theta1_last4 = theta1;
  theta2_last4 = theta2;
  two_degs(-x, 0);
  dth1 = theta1-theta1_last1;
  dth2 = theta2-theta2_last1;
  degs1[legs[0][0]] = degs1[legs[0][0]]+dth2*dir[legs[0][0]];
  degs1[legs[0][1]] = degs1[legs[0][1]]+dth1*dir[legs[0][1]];
  theta1_last1 = theta1;
  theta2_last1 = theta2;
  setDeg1();
  delay(100);
  for(int i=5; i>-1; i--){
    two_degs((x/6)*i, 0);
    dth1 = theta1-theta1_last4;
    dth2 = theta2-theta2_last4;
    degs1[legs[3][0]] = degs1[legs[3][0]]+dth2*dir[legs[3][0]];
    degs1[legs[3][1]] = degs1[legs[3][1]]+dth1*dir[legs[3][1]];
    theta1_last4 = theta1;
    theta2_last4 = theta2;

    two_degs((-x/6)*i, 0);
    dth1 = theta1-theta1_last1;
    dth2 = theta2-theta2_last1;
    degs1[legs[0][0]] = degs1[legs[0][0]]+dth2*dir[legs[0][0]];
    degs1[legs[0][1]] = degs1[legs[0][1]]+dth1*dir[legs[0][1]];
    theta1_last1 = theta1;
    theta2_last1 = theta2;

    two_degs((x/6)*(6-i), 0);
    dth1 = theta1-theta1_last3;
    dth2 = theta2-theta2_last3;
    degs1[legs[2][0]] = degs1[legs[2][0]]+dth2*dir[legs[2][0]];
    degs1[legs[2][1]] = degs1[legs[2][1]]+dth1*dir[legs[2][1]];
    theta1_last3 = theta1;
    theta2_last3 = theta2;

    two_degs(-((x+1)/6)*(6-i), 0);
    dth1 = theta1-theta1_last2;
    dth2 = theta2-theta2_last2;
    degs1[legs[1][0]] = degs1[legs[1][0]]+dth2*dir[legs[1][0]];
    degs1[legs[1][1]] = degs1[legs[1][1]]+dth1*dir[legs[1][1]];
    theta1_last2 = theta1;
    theta2_last2 = theta2;
    setDeg1();
    delay(50);
  }
  delay(100);
  two_degs(0, 2);
  dth1 = theta1-theta1_last3;
  dth2 = theta2-theta2_last3;
  degs1[legs[2][0]] = degs1[legs[2][0]]+dth2*dir[legs[2][0]];
  degs1[legs[2][1]] = degs1[legs[2][1]]+dth1*dir[legs[2][1]];
  theta1_last3 = theta1;
  theta2_last3 = theta2;
  two_degs(0, 2);
  dth1 = theta1-theta1_last2;
  dth2 = theta2-theta2_last2;
  degs1[legs[1][0]] = degs1[legs[1][0]]+dth2*dir[legs[1][0]];
  degs1[legs[1][1]] = degs1[legs[1][1]]+dth1*dir[legs[1][1]];
  theta1_last2 = theta1;
  theta2_last2 = theta2;
  setDeg1();
  delay(100);
  two_degs(0, 0);
  dth1 = theta1-theta1_last3;
  dth2 = theta2-theta2_last3;
  degs1[legs[2][0]] = degs1[legs[2][0]]+dth2*dir[legs[2][0]];
  degs1[legs[2][1]] = degs1[legs[2][1]]+dth1*dir[legs[2][1]];
  theta1_last3 = theta1;
  theta2_last3 = theta2;
  two_degs(0, 0);
  dth1 = theta1-theta1_last2;
  dth2 = theta2-theta2_last2;
  degs1[legs[1][0]] = degs1[legs[1][0]]+dth2*dir[legs[1][0]];
  degs1[legs[1][1]] = degs1[legs[1][1]]+dth1*dir[legs[1][1]];
  theta1_last2 = theta1;
  theta2_last2 = theta2;
  setDeg1();
  delay(100);
}

void backward23(float x){
  two_degs(x, 3);
  dth1 = theta1-theta1_last2;
  dth2 = theta2-theta2_last2;
  degs1[legs[1][0]] = degs1[legs[1][0]]+dth2*dir[legs[1][0]];
  degs1[legs[1][1]] = degs1[legs[1][1]]+dth1*dir[legs[1][1]];
  theta1_last2 = theta1;
  theta2_last2 = theta2;
  two_degs(-x, 2);
  dth1 = theta1-theta1_last3;
  dth2 = theta2-theta2_last3;
  degs1[legs[2][0]] = degs1[legs[2][0]]+dth2*dir[legs[2][0]];
  degs1[legs[2][1]] = degs1[legs[2][1]]+dth1*dir[legs[2][1]];
  theta1_last3 = theta1;
  theta2_last3 = theta2;
  setDeg1();
  delay(100);
  two_degs(x, 0);
  dth1 = theta1-theta1_last2;
  dth2 = theta2-theta2_last2;
  degs1[legs[1][0]] = degs1[legs[1][0]]+dth2*dir[legs[1][0]];
  degs1[legs[1][1]] = degs1[legs[1][1]]+dth1*dir[legs[1][1]];
  theta1_last2 = theta1;
  theta2_last2 = theta2;
  two_degs(-x, 0);
  dth1 = theta1-theta1_last3;
  dth2 = theta2-theta2_last3;
  degs1[legs[2][0]] = degs1[legs[2][0]]+dth2*dir[legs[2][0]];
  degs1[legs[2][1]] = degs1[legs[2][1]]+dth1*dir[legs[2][1]];
  theta1_last3 = theta1;
  theta2_last3 = theta2;
  setDeg1();
  delay(100);
  for(int i=5; i>-1; i--){
    two_degs((x/6)*i, 0);
    dth1 = theta1-theta1_last2;
    dth2 = theta2-theta2_last2;
    degs1[legs[1][0]] = degs1[legs[1][0]]+dth2*dir[legs[1][0]];
    degs1[legs[1][1]] = degs1[legs[1][1]]+dth1*dir[legs[1][1]];
    theta1_last2 = theta1;
    theta2_last2 = theta2;

    two_degs((-x/6)*i, 0);
    dth1 = theta1-theta1_last3;
    dth2 = theta2-theta2_last3;
    degs1[legs[2][0]] = degs1[legs[2][0]]+dth2*dir[legs[2][0]];
    degs1[legs[2][1]] = degs1[legs[2][1]]+dth1*dir[legs[2][1]];
    theta1_last3 = theta1;
    theta2_last3 = theta2;

    two_degs((x/6)*(6-i), 0);
    dth1 = theta1-theta1_last1;
    dth2 = theta2-theta2_last1;
    degs1[legs[0][0]] = degs1[legs[0][0]]+dth2*dir[legs[0][0]];
    degs1[legs[0][1]] = degs1[legs[0][1]]+dth1*dir[legs[0][1]];
    theta1_last1 = theta1;
    theta2_last1 = theta2;

    two_degs(-((x+1)/6)*(6-i), 0);
    dth1 = theta1-theta1_last4;
    dth2 = theta2-theta2_last4;
    degs1[legs[3][0]] = degs1[legs[3][0]]+dth2*dir[legs[3][0]];
    degs1[legs[3][1]] = degs1[legs[3][1]]+dth1*dir[legs[3][1]];
    theta1_last4 = theta1;
    theta2_last4 = theta2;
    setDeg1();
    delay(50);
  }
  delay(100);
  two_degs(0, 2);
  dth1 = theta1-theta1_last1;
  dth2 = theta2-theta2_last1;
  degs1[legs[0][0]] = degs1[legs[0][0]]+dth2*dir[legs[0][0]];
  degs1[legs[0][1]] = degs1[legs[0][1]]+dth1*dir[legs[0][1]];
  theta1_last1 = theta1;
  theta2_last1 = theta2;
  two_degs(0, 2);
  dth1 = theta1-theta1_last4;
  dth2 = theta2-theta2_last4;
  degs1[legs[3][0]] = degs1[legs[3][0]]+dth2*dir[legs[3][0]];
  degs1[legs[3][1]] = degs1[legs[3][1]]+dth1*dir[legs[3][1]];
  theta1_last4 = theta1;
  theta2_last4 = theta2;
  setDeg1();
  delay(100);
  two_degs(0, 0);
  dth1 = theta1-theta1_last1;
  dth2 = theta2-theta2_last1;
  degs1[legs[0][0]] = degs1[legs[0][0]]+dth2*dir[legs[0][0]];
  degs1[legs[0][1]] = degs1[legs[0][1]]+dth1*dir[legs[0][1]];
  theta1_last1 = theta1;
  theta2_last1 = theta2;
  two_degs(0, 0);
  dth1 = theta1-theta1_last4;
  dth2 = theta2-theta2_last4;
  degs1[legs[3][0]] = degs1[legs[3][0]]+dth2*dir[legs[3][0]];
  degs1[legs[3][1]] = degs1[legs[3][1]]+dth1*dir[legs[3][1]];
  theta1_last4 = theta1;
  theta2_last4 = theta2;
  setDeg1();
  delay(100);
}

void rotation_left(float theta){
  float first_shaft = degrees(asin(0.3));
  float r = sqrt(98);
  float t0 = asin(Ax/r);
  float t = radians(-theta);
  float A2x = r*sin(t0+t);
  float A2y = r*cos(t0+t);
  float B2x = -r*sin(t0-t);
  float B2y = r*cos(t0-t);
  float C2x = -r*sin(t0+t);
  float C2y = -r*cos(t0+t);
  float D2x = r*sin(t0-t);
  float D2y = -r*cos(t0-t);
  float shaftX = 4;
  float shaftY = 7;
  float shaftZ = 9;
  float A2_shaft = sqrt(sq(shaftX-A2x)+sq(shaftY-A2y)+sq(shaftZ));
  float footX = A2y-7;
  float footY = H-A2_shaft;
  float line_shaft_Ax = sqrt(sq(A2_shaft)-sq(Ay-A2y));
  float shaft_deg = degrees(asin((A2x-shaftX)/line_shaft_Ax));
  float dshaft = shaft_deg-first_shaft;

  two_degs(0, 3);
  dth1 = theta1-theta1_last3;
  dth2 = theta2-theta2_last3;
  degs1[legs[2][0]] = degs1[legs[2][0]]+dth2*dir[legs[2][0]];
  degs1[legs[2][1]] = degs1[legs[2][1]]+dth1*dir[legs[2][1]];
  degs1[legs[1][0]] = degs1[legs[1][0]]+dth2*dir[legs[1][0]];
  degs1[legs[1][1]] = degs1[legs[1][1]]+dth1*dir[legs[1][1]];
  theta1_last3 = theta1;
  theta2_last3 = theta2;
  theta1_last2 = theta1;
  theta2_last2 = theta2;
  setDeg1();
  delay(50);
  two_degs(footX, footY);
  dth1 = theta1-theta1_last3;
  dth2 = theta2-theta2_last3;
  degs1[legs[2][0]] = degs1[legs[2][0]]+dth2*dir[legs[2][0]];
  degs1[legs[2][1]] = degs1[legs[2][1]]+dth1*dir[legs[2][1]];
  degs1[legs[1][0]] = degs1[legs[1][0]]+dth2*dir[legs[1][0]];
  degs1[legs[1][1]] = degs1[legs[1][1]]+dth1*dir[legs[1][1]];
  theta1_last3 = theta1;
  theta2_last3 = theta2;
  theta1_last2 = theta1;
  theta2_last2 = theta2;
  degs1[legs[2][2]] = degs1[legs[2][2]]+dshaft*dir[legs[2][2]];
  degs1[legs[1][2]] = degs1[legs[1][2]]+dshaft*dir[legs[1][2]];
  setDeg1();
  delay(300);
  float m3 = -degs1[legs[1][0]]+deg0[legs[1][0]];
  float m4 = -degs1[legs[1][1]]+deg0[legs[1][1]];
  float m5 = -degs1[legs[1][2]]+deg0[legs[1][2]];
  float m6 = -degs1[legs[2][0]]+deg0[legs[2][0]];
  float m7 = -degs1[legs[2][1]]+deg0[legs[2][1]];
  float m8 = -degs1[legs[2][2]]+deg0[legs[2][2]];
  for(int i=1; i<6; i++){
    degs1[legs[1][0]] = degs1[legs[1][0]]+m3/5;
    degs1[legs[1][1]] = degs1[legs[1][1]]+m4/5;
    degs1[legs[1][2]] = degs1[legs[1][2]]+m5/5;
    degs1[legs[2][0]] = degs1[legs[2][0]]+m6/5;
    degs1[legs[2][1]] = degs1[legs[2][1]]+m7/5;
    degs1[legs[2][2]] = degs1[legs[2][2]]+m8/5;
    degs1[legs[3][0]] = degs1[legs[3][0]]+m3/6;
    degs1[legs[3][1]] = degs1[legs[3][1]]+m4/5;
    degs1[legs[3][2]] = degs1[legs[3][2]]+m5/3;
    degs1[legs[0][0]] = degs1[legs[0][0]]+m6/6;
    degs1[legs[0][1]] = degs1[legs[0][1]]+m7/5;
    degs1[legs[0][2]] = degs1[legs[0][2]]+m8/3;
    setDeg1();
    delay(50);
  }
  delay(100);
  two_degs(0, 0);
  float first1 = theta1;
  float first2 = theta2;
  two_degs(0, 4);
  dth1 = theta1-first1;
  dth2 = theta2-first2;
  degs1[legs[0][0]] = deg0[legs[0][0]]+dth2*dir[legs[0][0]];
  degs1[legs[0][1]] = deg0[legs[0][1]]+dth1*dir[legs[0][1]];
  degs1[legs[0][2]] = deg0[legs[0][2]];
  degs1[legs[3][0]] = deg0[legs[3][0]]+dth2*dir[legs[3][0]];
  degs1[legs[3][1]] = deg0[legs[3][1]]+dth1*dir[legs[3][1]];
  degs1[legs[3][2]] = deg0[legs[3][2]];
  theta1_last1 = theta1;
  theta2_last1 = theta2;
  theta1_last4 = theta1;
  theta2_last4 = theta2;
  setDeg1();
  delay(100);
  still();
}

void rotation_right(float theta){
  float first_shaft = degrees(asin(0.3));
  float r = sqrt(98);
  float t0 = asin(Ax/r);
  float t = radians(-theta);
  float A2x = r*sin(t0+t);
  float A2y = r*cos(t0+t);
  float B2x = -r*sin(t0-t);
  float B2y = r*cos(t0-t);
  float C2x = -r*sin(t0+t);
  float C2y = -r*cos(t0+t);
  float D2x = r*sin(t0-t);
  float D2y = -r*cos(t0-t);
  float shaftX = 4;
  float shaftY = 7;
  float shaftZ = 9;
  float A2_shaft = sqrt(sq(shaftX-A2x)+sq(shaftY-A2y)+sq(shaftZ));
  float footX = A2y-7;
  float footY = H-A2_shaft;
  float line_shaft_Ax = sqrt(sq(A2_shaft)-sq(Ay-A2y));
  float shaft_deg = degrees(asin((A2x-shaftX)/line_shaft_Ax));
  float dshaft = shaft_deg-first_shaft;

  two_degs(0, 3);
  dth1 = theta1-theta1_last1;
  dth2 = theta2-theta2_last1;
  degs1[legs[0][0]] = degs1[legs[0][0]]+dth2*dir[legs[0][0]];
  degs1[legs[0][1]] = degs1[legs[0][1]]+dth1*dir[legs[0][1]];
  degs1[legs[3][0]] = degs1[legs[3][0]]+dth2*dir[legs[3][0]];
  degs1[legs[3][1]] = degs1[legs[3][1]]+dth1*dir[legs[3][1]];
  theta1_last1 = theta1;
  theta2_last1 = theta2;
  theta1_last4 = theta1;
  theta2_last4 = theta2;
  setDeg1();
  delay(100);
  two_degs(footX, footY);
  dth1 = theta1-theta1_last1;
  dth2 = theta2-theta2_last1;
  degs1[legs[0][0]] = degs1[legs[0][0]]+dth2*dir[legs[0][0]];
  degs1[legs[0][1]] = degs1[legs[0][1]]+dth1*dir[legs[0][1]];
  degs1[legs[3][0]] = degs1[legs[3][0]]+dth2*dir[legs[3][0]];
  degs1[legs[3][1]] = degs1[legs[3][1]]+dth1*dir[legs[3][1]];
  theta1_last1 = theta1;
  theta2_last1 = theta2;
  theta1_last4 = theta1;
  theta2_last4 = theta2;
  degs1[legs[0][2]] = degs1[legs[0][2]]+dshaft*dir[legs[0][2]];
  degs1[legs[3][2]] = degs1[legs[3][2]]+dshaft*dir[legs[3][2]];
  setDeg1();
  delay(300);
  float m3 = -degs1[legs[3][0]]+deg0[legs[3][0]];
  float m4 = -degs1[legs[3][1]]+deg0[legs[3][1]];
  float m5 = -degs1[legs[3][2]]+deg0[legs[3][2]];
  float m6 = -degs1[legs[0][0]]+deg0[legs[0][0]];
  float m7 = -degs1[legs[0][1]]+deg0[legs[0][1]];
  float m8 = -degs1[legs[0][2]]+deg0[legs[0][2]];
  for(int i=1; i<6; i++){
    degs1[legs[1][0]] = degs1[legs[1][0]]+m3/5;
    degs1[legs[1][1]] = degs1[legs[1][1]]+m4/5;
    degs1[legs[1][2]] = degs1[legs[1][2]]+m5/5;
    degs1[legs[2][0]] = degs1[legs[2][0]]+m6/5;
    degs1[legs[2][1]] = degs1[legs[2][1]]+m7/5;
    degs1[legs[2][2]] = degs1[legs[2][2]]+m8/5;
    degs1[legs[3][0]] = degs1[legs[3][0]]+m3/5;
    degs1[legs[3][1]] = degs1[legs[3][1]]+m4/5;
    degs1[legs[3][2]] = degs1[legs[3][2]]+m5/5;
    degs1[legs[0][0]] = degs1[legs[0][0]]+m6/5;
    degs1[legs[0][1]] = degs1[legs[0][1]]+m7/5;
    degs1[legs[0][2]] = degs1[legs[0][2]]+m8/5;
    setDeg1();
    delay(50);
  }
  delay(100);
  two_degs(0, 0);
  float first1 = theta1;
  float first2 = theta2;
  two_degs(0, 4);
  dth1 = theta1-first1;
  dth2 = theta2-first2;
  degs1[legs[2][0]] = deg0[legs[2][0]]+dth2*dir[legs[2][0]];
  degs1[legs[2][1]] = deg0[legs[2][1]]+dth1*dir[legs[2][1]];
  degs1[legs[2][2]] = deg0[legs[2][2]];
  degs1[legs[1][0]] = deg0[legs[1][0]]+dth2*dir[legs[1][0]];
  degs1[legs[1][1]] = deg0[legs[1][1]]+dth1*dir[legs[1][1]];
  degs1[legs[1][2]] = deg0[legs[1][2]];
  theta1_last3 = theta1;
  theta2_last3 = theta2;
  theta1_last2 = theta1;
  theta2_last2 = theta2;
  setDeg1();
  delay(100);
  still();
}

void forward(float x){
  forward14(x);
  delay(100);
  forward23(x);
}

void backward(float x){
  backward14(x);
  delay(100);
  backward23(x);
}

void loop(){
  still();
  char data = Serial.read();
  if(data == 'a'){
    forward(4);
  }else if(data == 'b'){
    rotation_right(15);
  }else if(data == 'c'){
    rotation_left(15);
  }else if(data == 'd'){
    backward(4);
  }
}
