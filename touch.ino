#define touch1 30 // đèn ngủ 1 1
#define touch2 32 // quạt ngủ  2
#define touch3 34 // đèn vườn  3
#define touch4 36 // đèn khách 4
#define touch5 38 // quạt khách 5
#define touch6 40 // đèn cổng 6
#define touch7 42 // đèn gara  7
#define touch8 44 // đèn bếp   8
#define touch9 46 // quạt bếp  9
#define touch10 48 // đèn tắm  10
#define touch11 26 // đèn ngủ 2 11


#define denngu1 31
#define quatngu 33
#define denvuon 35
#define denkhach 37
#define quatkhach 39
#define dencong 41
#define dengara 43
#define denbep 45
#define quatbep 47
#define dentam 49
#define denngu2 28




int val1, val2, val3, val4, val5, val6, val7, val8, val9, val10, val11;

int dem1, dem2, dem3, dem4, dem5, dem6, dem7, dem8, dem9, dem10, dem11 ;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(dencong,OUTPUT);
  pinMode(dengara,OUTPUT);
  pinMode(denvuon,OUTPUT);
  pinMode(denkhach,OUTPUT);
  pinMode(denngu1,OUTPUT);
  pinMode(denngu2,OUTPUT);
  pinMode(denbep,OUTPUT);
  pinMode(dentam,OUTPUT);
  pinMode(quatngu,OUTPUT);
  pinMode(quatkhach,OUTPUT);
  pinMode(quatbep,OUTPUT);

  digitalWrite(dencong, HIGH);
  digitalWrite(dengara, HIGH);
  digitalWrite(denvuon, HIGH);
  digitalWrite(denkhach, HIGH);
  digitalWrite(denngu1, HIGH);
  digitalWrite(denngu2, HIGH);
  digitalWrite(denbep, HIGH);
  digitalWrite(dentam, HIGH);
  digitalWrite(quatkhach, HIGH);
  digitalWrite(quatngu, HIGH);
  digitalWrite(quatbep, HIGH);
  
  
  pinMode(touch1, INPUT);
  pinMode(touch2, INPUT);
  pinMode(touch3, INPUT);
  pinMode(touch4, INPUT);
  pinMode(touch5, INPUT);
  pinMode(touch6, INPUT);
  pinMode(touch7, INPUT);
  pinMode(touch8, INPUT);
  pinMode(touch9, INPUT);
  pinMode(touch10, INPUT);
  pinMode(touch11, INPUT);
  
  
}

void loop() {
  
  val1 = digitalRead(touch1);
  val2 = digitalRead(touch2);
  val3 = digitalRead(touch3);
  val4 = digitalRead(touch4);
  val5 = digitalRead(touch5);
  val6 = digitalRead(touch6);
  val7 = digitalRead(touch7);
  val8 = digitalRead(touch8);
  val9 = digitalRead(touch9);
  val10 = digitalRead(touch10);
  val11 = digitalRead(touch11);
  

  if (val1 == 1)  
  {  
    dem1 ++;
  }
  if (dem1 == 2 ) dem1 = 0;
  if (dem1 == 1) digitalWrite(denngu1, LOW);
  else            digitalWrite(denngu1, HIGH);

   if (val2 == 1)  
  {
    dem2 ++;
  }
  if (dem2 == 2 ) dem2 = 0;
  if (dem2 == 1) digitalWrite(quatngu, LOW);
  else            digitalWrite(quatngu, HIGH);

   if (val3 == 1)  
  {
    dem3 ++;
  }
  if (dem3 == 2 ) dem3 = 0;
  if (dem3 == 1) digitalWrite(denvuon, LOW);
  else            digitalWrite(denvuon, HIGH);

  if (val4 == 1)  
  {
    dem4 ++;
  }
  if (dem4 == 2 ) dem4 = 0;
  if (dem4 == 1) digitalWrite(denkhach, LOW);
  else           digitalWrite(denkhach, HIGH);

  if (val5 == 1)  
  {
    dem5 ++;
  }
  if (dem5 == 2 ) dem5 = 0;
  if (dem5 == 1) digitalWrite(quatkhach, LOW);
  else digitalWrite(quatkhach, HIGH);

  if (val6 == 1)  
  {
    dem6 ++;
  }
  if (dem6 == 2 ) dem6 = 0;
  if (dem6 == 1) digitalWrite(dencong, LOW);
  else digitalWrite(dencong, HIGH);

  if (val7 == 1)  
  {
    dem7 ++; 
  }
  if (dem7 == 2 ) dem7 = 0;
  if (dem7 == 1) digitalWrite(dengara, LOW);
  else digitalWrite(dengara, HIGH);

  if (val8 == 1)  
  {
    dem8 ++; 
  }
  if (dem8 == 2 ) dem8 = 0;
  if (dem8 == 1) digitalWrite(denbep, LOW);
  else digitalWrite(denbep, HIGH);

  if (val9 == 1)  
  {
    dem9 ++;
  }
  if (dem9 == 2 ) dem9 = 0;
  if (dem9 == 1) digitalWrite(quatbep, LOW);
  else digitalWrite(quatbep, HIGH);

  if (val10 == 1)  
  {
    dem10 ++;
  }
  if (dem10 == 2 ) dem10 = 0;
  if (dem10 == 1) digitalWrite(dentam, LOW);
  else digitalWrite(dentam, HIGH);

  if (val11 == 1)  
  {
    dem11 ++;
  }
  if (dem11 == 2 ) dem11 = 0;
  if (dem11 == 1) digitalWrite(denngu2, LOW);
  else digitalWrite(denngu2, HIGH);

  
}
