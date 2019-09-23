                                                                              /* ĐỒ ÁN CƠ ĐIỆN TỬ */
                                                                              
  #include <Servo.h>
  #include <ESP8266WiFi.h>

  #define SERVO1 D1 // Cửa sổ khách
  #define SERVO2 D2 // Cửa sổ khách
  #define SERVO3 D3 // Cửa sổ ngủ
  #define SERVO4 D4 // Cửa sổ ngủ
  #define SERVO5 D5 // Cửa sổ bếp
  #define SERVO6 D6 // Cửa bếp
  #define SERVO7 D7 // Cửa chính
  #define SERVO8 D8 // Cửa chính
  
  Servo gServo1;
  Servo gServo2;
  Servo gServo3;
  Servo gServo4;
  Servo gServo5;
  Servo gServo6;
  Servo gServo7;
  Servo gServo8;

const char* ssid = "danthanh";
const char* password = "06112013";

//const char* ssid = "NgocDaiCa";
//const char* password = "ngocdeptrai";

int rainSensor = 10;
int gas = A0;
WiFiServer server(80);

int cuasokhach, cuasongu, cuasobep, cuabep, cuachinh, quatngu, offall;

 void setup() 
 {
      //ESP.eraseConfig(); 
      //ESP.reset();
      Serial.begin(115200);
      delay(10);
            
       pinMode(A0, INPUT); // A0
       pinMode(10,INPUT); // CB mưa
       pinMode(D0, OUTPUT); // Báo động
       digitalWrite(D0,LOW); 
       pinMode(3, OUTPUT);  // Quạt Ngủ
       digitalWrite(3,HIGH);
       
       gServo1.attach(SERVO1);
       gServo2.attach(SERVO2); 
       gServo3.attach(SERVO3); 
       gServo4.attach(SERVO4);
       gServo5.attach(SERVO5); 
       gServo6.attach(SERVO6); 
       gServo7.attach(SERVO7);
       gServo8.attach(SERVO8);

    Serial.print("Connecting to: ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    
     while (WiFi.status() != WL_CONNECTED) {
        delay(500);
       Serial.print(".");
      }
     Serial.println("");
     Serial.println("WiFi connected");
      
      // Start the server
      server.begin();
      Serial.println("Server started");
    
      // Print the IP address
      Serial.println(WiFi.localIP());

          gServo1.write(150);
          gServo2.write(5);
          gServo3.write(0);
          gServo4.write(180);
          gServo5.write(0);
          gServo6.write(2);
          gServo7.write(142);
          gServo8.write(8);
          
 }
 
void loop() 
{
      int analogSensor = analogRead(gas); //A0
      int mua = digitalRead(rainSensor);  //10
      //Serial.println(analogSensor);
      delay(10);
      
      if (analogSensor > 160)
      {
            digitalWrite(D0,HIGH); // Còi
              gServo1.write(5);
              gServo2.write(170);
              gServo3.write(170);
              gServo4.write(0);
              gServo5.write(130);

//                cuasokhach = 1;
//                cuasongu = 1;
//                cuasobep = 1;
//                cuabep = 1;
//                cuachinh = 1;
      }
      else digitalWrite(D0,LOW);

      if (mua == LOW) 
        {
              gServo1.write(150);
              gServo2.write(5);
              gServo3.write(0);
              gServo4.write(180);
              gServo5.write(0);
              gServo6.write(2);

//                cuasokhach = 0;
//                cuasongu = 0;
//                cuasobep = 0;
//                cuabep = 0;
//                cuachinh = 0;
        }

      
   // Check if a client has connected
      WiFiClient client = server.available();
      if (!client) {
        return;
      }
      while(!client.available()){
        delay(1);
      }
      
    // Wait until the client sends some data
    //  Serial.println("new client");
      while(!client.available()){
        delay(1);
      }


     String req = client.readStringUntil('\r');
      Serial.println(req);
      client.flush();
      
        // Cửa sổ khách
        if (req.indexOf("/cuasokhach=on") != -1) cuasokhach = 1;
        else if (req.indexOf("/cuasokhach=off") != -1) cuasokhach = 0;

        // Cửa Sổ Ngủ
        else if (req.indexOf("/cuasongu=on") != -1) cuasongu = 1;
        else if (req.indexOf("/cuasongu=off") != -1) cuasongu = 0;

        // Cửa Sổ Bếp
        else if (req.indexOf("/cuasobep=on") != -1) cuasobep = 1;
        else if (req.indexOf("/cuasobep=off") != -1) cuasobep = 0;

        // Cửa Bếp
        else if (req.indexOf("/cuabep=on") != -1) cuabep = 1;
        else if (req.indexOf("/cuabep=off") != -1) cuabep = 0;

        // Cửa Chính
        else if (req.indexOf("/cuachinh=on") != -1) cuachinh = 1;
        else if (req.indexOf("/cuachinh=off") != -1) cuachinh = 0;

        // QUẠT PHÒNG NGỦ
        else if (req.indexOf("/quatngu=on") != -1)        quatngu = 1;
        else if (req.indexOf("/quatngu=off") != -1)       quatngu = 0;

        else if (req.indexOf("/offall") != -1) offall = 1;

        else 
        {
         client.stop();
         return;
        }
        
        if (offall == 1) {
          cuasokhach = 0;
          cuasongu = 0;
          cuasobep = 0;
          cuabep = 0;
          quatngu = 0;
          offall = 0;
        }
        
        if (cuasokhach == 1) {
          gServo1.write(5);
          gServo2.write(170);
        }
        else             {
          gServo1.write(150);
          gServo2.write(5);
        }

        if (cuasongu == 1) {
          gServo3.write(170);
          gServo4.write(0);
        }
        else             {
          gServo3.write(0);
          gServo4.write(180);
        }
        
        if (cuasobep == 1)  gServo5.write(130);
        else                  gServo5.write(0);

        if (cuabep == 1) gServo6.write(92);
        else                gServo6.write(2);

        if(cuachinh == 1) {
          gServo7.write(30);
          gServo8.write(160);
        }
        else {
          gServo7.write(142);
          gServo8.write(0);
        }

        if (quatngu == 1) digitalWrite(3,LOW); 
        else              digitalWrite(3,HIGH);
        
                                                                    /*    ĐƯA LÊN INTERNET    */
                                              
         client.println("HTTP/1.1 200 OK");        //Tạo 1 trang mới
         client.println("Content-Type: text/html");
     //  client.println("Refresh: 10");   // lệnh để tự động tải lại trang, cứ 20 giây 1 lần tải lại.
         client.println("");
         client.println("<!DOCTYPE HTML>");
         client.println("<HTML>");             // câu lệnh của web để trình duyệt hiểu mà hiển thị các phần đầu, thân, cuối,...mình chưa học lập trình web nên chưa hiểu lắm
            client.println("<HEAD>");
                  client.println("<TITLE>DO AN CO DIEN TU</TITLE>"); // tên tiêu đề ở mác của tab trình duyệt đó, cái này ít quan trọng. có thể thay đổi tùy ý  
            client.println("</HEAD>");
          
            client.println("<CENTER>");
                  client.println("<h1><b>DU AN NHA THONG MINH (SMART HOME)</b></h1>");
            client.println("</CENTER>");
            client.println("<br />");
            
            client.println("<CENTER>");
                 if (cuasokhach == 1) client.println("CUA SO KHACH :<b>DANG MO</b>");
                 else client.println("CUA SO KHACH : <b>DANG DONG</b>");
                 //client.println("<br />");
                 client.println("<a href=\"/cuasokhach=on\"\"><button>ON </button></a>");
                 client.println("<a href=\"/cuasokhach=off\"\"><button>OFF </button></a><br />");
             client.println("</CENTER>");
             client.println("<br><br>");
             
             client.println("<CENTER>");
                 if (cuasongu == 1) client.println("CUA SO NGU :<b>DANG MO</b>");
                 else client.println("CUA SO NGU : <b>DANG DONG</b>");
                 //client.println("<br />");
                 client.println("<a href=\"/cuasongu=on\"\"><button>ON </button></a>");
                 client.println("<a href=\"/cuasongu=off\"\"><button>OFF </button></a><br />");
             client.println("</CENTER>");
             client.println("<br><br>");

             client.println("<CENTER>");
                 if (cuasobep == 1) client.println("CUA SO BEP :<b>DANG MO</b>");
                 else client.println("CUA SO BEP : <b>DANG DONG</b>");
                 //client.println("<br />");
                 client.println("<a href=\"/cuasobep=on\"\"><button>ON </button></a>");
                 client.println("<a href=\"/cuasobep=off\"\"><button>OFF </button></a><br />");
             client.println("</CENTER>");
             client.println("<br><br>");

             client.println("<CENTER>");
                 if (cuabep == 1) client.println("CUA BEP :<b>DANG MO</b>");
                 else client.println("CUA BEP : <b>DANG DONG</b>");
                 //client.println("<br />");
                 client.println("<a href=\"/cuabep=on\"\"><button>ON </button></a>");
                 client.println("<a href=\"/cuabep=off\"\"><button>OFF </button></a><br />");
             client.println("</CENTER>");
             client.println("<br><br>");

             client.println("<CENTER>");
                 if (cuachinh == 1) client.println("CUA CHINH :<b>DANG MO</b>");
                 else client.println("CUA CHINH : <b>DANG DONG</b>");
                 //client.println("<br />");
                 client.println("<a href=\"/cuachinh=on\"\"><button>ON </button></a>");
                 client.println("<a href=\"/cuachinh=off\"\"><button>OFF </button></a><br />");
             client.println("</CENTER>");
             client.println("<br><br>");

              client.println("<CENTER>");
                 client.println("<b>DONG HET CUA : </b>");
                 //client.println("<br />");
                 client.println("<a href=\"/offall\"\"><button>Turn Off </button></a><br />");
             client.println("</CENTER>");
             client.println("<br><br>");
             
             client.println("<CENTER>");
                 client.print("NONG DO GAS: ");
                 client.print("<b>"); 
                 client.print(analogSensor);
                 client.print(" PPM ");
                 client.print("</b>"); 
                 client.println("<br><br>");
             client.println("</CENTER>");
         client.println("</HTML>");               
       delay(10);
}
      
