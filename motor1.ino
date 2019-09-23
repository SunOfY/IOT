#include <ESP8266WiFi.h>

const char* ssid = "danthanh";
const char* password = "06112013";

//const char* ssid = "ngocdaica";
//const char* password = "ngocdeptrai";

int rain = 10;
int gara, phoido, offall;
int ctht3,ctht4,ctht5,ctht6;
WiFiServer server(80);
 void setup() {
  
      Serial.begin(115200);
      
//      ESP.eraseConfig(); 
//      ESP.reset();
      delay(10);
      pinMode(rain,INPUT); 
      
      pinMode(D0, OUTPUT);  //PD
      pinMode(D1, OUTPUT);   // PD
      
      pinMode(D5, INPUT);   // CTHT5
       pinMode(D6, INPUT);   // CTHT6

      pinMode(D3, OUTPUT);  // GR
      pinMode(D2, OUTPUT);   // GR

      pinMode(D7, INPUT);   // CTHT3
      pinMode(D8, INPUT);    // CTHT4
    

      digitalWrite(D0,LOW);
      digitalWrite(D1,LOW);
      
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

 }
void loop() 
{
  int mua = digitalRead(rain);  
  ctht5=digitalRead(D5);
        ctht6=digitalRead(D6);
          ctht3=digitalRead(D7);
             ctht4=digitalRead(D8);
 if (offall == 1) {
          gara = 0;
          phoido = 0;

          offall = 0;
        }
    if (gara == 1) {
                if (ctht3==1 && ctht4==0  || ctht3==1 && ctht4==1)
                {
                    digitalWrite(D3,HIGH);
                    digitalWrite(D2,LOW);
                }
                if( (ctht3==0 && ctht4==1) || (ctht3==0 && ctht4==0) )
                {
                    digitalWrite(D3,LOW);
                    digitalWrite(D2,LOW);
                }
        }
        else {
                if( ctht3==0 && ctht4==1 || ctht3==1 && ctht4==1 )
                 {
                     digitalWrite(D2,HIGH);
                     digitalWrite(D3,LOW);
                      }
                if( (ctht3==1 && ctht4==0) || (ctht3==0 && ctht4==0) )
                 {
                     digitalWrite(D3,LOW);
                     digitalWrite(D2,LOW);
                 }
                       
        }

        if (phoido == 1)
        {
                if (ctht5==0 && ctht6==1 || ctht5==1 && ctht6==1)
                {
                    digitalWrite(D0,HIGH);
                    digitalWrite(D1,LOW);
                }
                if( ctht6==0&&ctht5==1) 
                {
                    digitalWrite(D0,LOW);
                    digitalWrite(D1,LOW);}

        }
        if (phoido==0 || mua == 0 ) 
        {
              if( ctht5==1 && ctht6==0 || ctht5==1 && ctht6==1 )
               {
                    digitalWrite(D1,HIGH);
                    digitalWrite(D0,LOW);
               }     
              if( (ctht5==0 && ctht6==1) || ctht5==0 && ctht6==0) 
               {
                    digitalWrite(D0,LOW);
                    digitalWrite(D1,LOW);
               }
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
     Serial.println("new client");
      
     String req = client.readStringUntil('\r');
      Serial.println(req);
      client.flush();
           
        // ĐC 2
       if (req.indexOf("/cuagara=on") != -1 )       gara = 1;
       else if (req.indexOf("/cuagara=off") != -1)   gara = 0;

       // ĐC 3
       else if (req.indexOf("/phoido") != -1)  phoido = 1;
       else if (req.indexOf("/laydo") != -1)   phoido = 0;

       else if (req.indexOf("/offall") != -1)  offall = 1;

        else 
        {
         client.stop();
         return;
        }

        
         client.println("HTTP/1.1 200 OK");        //Tạo 1 trang mới
         client.println("Content-Type: text/html");
      // client.println("Refresh: 10");   // lệnh để tự động tải lại trang, cứ 20 giây 1 lần tải lại.
         client.println("");
         client.println("<!DOCTYPE HTML>");
         client.println("<HTML>");             // câu lệnh của web để trình duyệt hiểu mà hiển thị các phần đầu, thân, cuối,...mình chưa học lập trình web nên chưa hiểu lắm
            client.println("<HEAD>");
                  client.println("<TITLE>DO AN CO DIEN TU</TITLE>"); // tên tiêu đề ở mác của tab trình duyệt đó, cái này ít quan trọng. có thể thay đổi tùy ý  
            client.println("</HEAD>");
          
            client.println("<CENTER>");
                  client.println("<h1><b>DU AN NHA THONG MINH (SMART HOUSE)</b></h1>");
            client.println("</CENTER>");
            client.println("<br />");

//            client.println("<CENTER>");
//                 if (cong == 1) client.println("CUA CONG :<b>DANG MO</b>");
//                 else client.println("CUA CONG : <b>DANG DONG</b>");
//                 //client.println("<br />");
//                 client.println("<a href=\"/cong=on\"\"><button>ON </button></a>");
//                 client.println("<a href=\"/cong=off\"\"><button>OFF </button></a><br />");
//             client.println("</CENTER>");
//             client.println("<br><br>");
//
//             client.println("<CENTER>");
//                 if (gara == 1) client.println("CUA GARA :<b>DANG MO</b>");
//                 else client.println("CUA GARA : <b>DANG DONG</b>");
//                 //client.println("<br />");
//                 client.println("<a href=\"/gara=on\"\"><button>ON </button></a>");
//                 client.println("<a href=\"/gara=off\"\"><button>OFF </button></a><br />");
//             client.println("</CENTER>");
//             client.println("<br><br>");
//
//             client.println("<CENTER>");
//                 if (phoido == 1) client.println("<b>DANG PHOI DO</b>");
//                 else client.println("<b>DANG LAY DO</b>");
//                 //client.println("<br />");
//                 client.println("<a href=\"/phoido=on\"\"><button>ON </button></a>");
//                 client.println("<a href=\"/phoido=off\"\"><button>OFF </button></a><br />");
//             client.println("</CENTER>");
//             client.println("<br><br>");
             
         client.println("</HTML>");      
       delay(1);
 
}

      
