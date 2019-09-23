                                                                   /* ĐỒ ÁN CƠ ĐIỆN TỬ */
#include <ESP8266WiFi.h>
#include "DHT.h" 

const char* ssid = "danthanh";
const char* password = "06112013";

//const char* ssid = "NgocDaiCa";
//const char* password = "ngocdeptrai";

WiFiServer server(80);

int dencong, dengara ,denvuon ,denkhach ,denngu1 , denngu2, denbep, quatkhach, quatbep, offall ;
// int quatngu;
  void setup() 
  {
      Serial.begin(115200);
      delay(10); 
      
      //ESP.eraseConfig(); 
      //ESP.reset();
        
        pinMode(D0, OUTPUT);  // Đèn cổng
        pinMode(D1, OUTPUT);  // Đèn gara
        pinMode(D2, OUTPUT);  // Đèn vườn
        pinMode(D3, OUTPUT);  // Đèn khách
        pinMode(D4, OUTPUT);  // Đèn bếp
        pinMode(D5, OUTPUT);  // Đèn ngủ 1
        pinMode(D8, OUTPUT);  // Đèn ngủ 2 
        pinMode(D7, OUTPUT);  // Quạt Khách
       //  pinMode(D8, OUTPUT);  // Quạt Ngủ
        pinMode(3, OUTPUT);  // Quạt Bếp 
        
        digitalWrite(D0,HIGH);
        digitalWrite(D1,HIGH);
        digitalWrite(D2,HIGH);
        digitalWrite(D3,HIGH);
        digitalWrite(D4,HIGH);
        digitalWrite(D5,HIGH);
        digitalWrite(D8,HIGH);
        digitalWrite(D7,HIGH);
        // digitalWrite(D8,HIGH);
        digitalWrite(3,HIGH);
        
        
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

void loop() {

       // Check if a client has connected
      WiFiClient client = server.available();
      if (!client) {
        return;
      }
      
      // Wait until the client sends some data
    //  Serial.println("new client");
      while(!client.available()){
        delay(1);
      }

      // Read the first line of the request
      String req = client.readStringUntil('\r');
      Serial.println(req);
      client.flush();
            
        // ĐÈN CỔNG
        if (req.indexOf("/dencong=off") != -1)         dencong = 0;
        else if (req.indexOf("/dencong=on") != -1)      dencong = 1;

        //ĐÈN GARA   
        else if (req.indexOf("/dengara=off") != -1)     dengara = 0;
        else if (req.indexOf("/dengara=on") != -1)      dengara = 1;
           
        //ĐÈN VƯỜN   
        else if (req.indexOf("/denvuon=off") != -1)     denvuon = 0;
        else if (req.indexOf("/denvuon=on") != -1)      denvuon = 1;

        //ĐÈN KHÁCH   
        else if (req.indexOf("/denkhach=off") != -1)    denkhach = 0;
        else if (req.indexOf("/denkhach=on") != -1)     denkhach = 1;

        //ĐÈN BẾP   
        else if (req.indexOf("/denbep=off") != -1)      denbep = 0;
        else if (req.indexOf("/denbep=on") != -1)       denbep = 1;

        //ĐÈN NGỦ 1   
        else if (req.indexOf("/denngu1=off") != -1)      denngu1 = 0;
        else if (req.indexOf("/denngu1=on") != -1)       denngu1 = 1;

        // ĐÈN NGỦ 2
        else if (req.indexOf("/denngu2=off") != -1)      denngu2 = 0;
        else if (req.indexOf("/denngu2=on") != -1)       denngu2 = 1;
        
        // QUẠT PHÒNG KHÁCH
        else if (req.indexOf("/quatkhach=on") != -1)      quatkhach = 1;
        else if (req.indexOf("/quatkhach=off") != -1)     quatkhach = 0;
        
//        // QUẠT PHÒNG NGỦ
//        else if (req.indexOf("/quatngu=on") != -1)        quatngu = 1;
//        else if (req.indexOf("/quatngu=off") != -1)       quatngu = 0;
        
        // QUẠT PHÒNG BẾP
        else if (req.indexOf("/quatbep=on") != -1)        quatbep = 1;
        else if (req.indexOf("/quatbep=off") != -1)       quatbep = 0;

        // TĂT HẾT THIẾT BỊ
        else if (req.indexOf("/offall") != -1)            offall = 1;
           
        else 
        {
           client.stop();
           return;
        }

        if (offall == 1) 
        {
            dencong = 0;
            dengara = 0;
            denvuon = 0;
            denbep = 0;
            denkhach = 0;
            denngu1 = 0;
            denngu2 = 0;
            quatkhach = 0;
            //quatngu = 0;
            quatbep = 0;
   
            offall = 0;
        }
        
        if (dencong == 1) digitalWrite(D0,LOW); 
        else              digitalWrite(D0,HIGH);
        
        if (dengara == 1) digitalWrite(D1,LOW); 
        else              digitalWrite(D1,HIGH);
        
        if (denvuon == 1) digitalWrite(D2,LOW); 
        else              digitalWrite(D2,HIGH);
        
        if (denkhach == 1) digitalWrite(D3,LOW); 
        else               digitalWrite(D3,HIGH);

        if (denbep == 1) digitalWrite(D4,LOW); 
        else               digitalWrite(D4,HIGH);
        
        if (denngu1 == 1) digitalWrite(D5,LOW); 
        else              digitalWrite(D5,HIGH);
        
        if (denngu2 == 1) digitalWrite(D8,LOW); 
        else              digitalWrite(D8,HIGH);
        
        if (quatkhach == 1) digitalWrite(D7,LOW); 
        else                digitalWrite(D7,HIGH);
        
//        if (quatngu == 1) digitalWrite(D8,LOW); 
//        else              digitalWrite(D8,HIGH);
        
        if (quatbep == 1) digitalWrite(3,LOW); 
        else              digitalWrite(3,HIGH);
        

                                                                    /*    ĐƯA LÊN INTERNET    */
                                                                    
        // Prepare the response
         client.println("HTTP/1.1 200 OK");        //Tạo 1 trang mới
         client.println("Content-Type: text/html");
    //   client.println("Refresh: 10");   // lệnh để tự động tải lại trang, cứ 20 giây 1 lần tải lại.
         client.println("");
         client.println("<!DOCTYPE HTML>");
         client.println("<HTML>");             // câu lệnh của web để trình duyệt hiểu mà hiển thị các phần đầu, thân, cuối,...mình chưa học lập trình web nên chưa hiểu lắm
            client.println("<HEAD>");
                  client.println("<TITLE>DO AN CO DIEN TU</TITLE>"); // tên tiêu đề ở mác của tab trình duyệt đó, cái này ít quan trọng. có thể thay đổi tùy ý  
            client.println("</HEAD>");
          
            client.println("<CENTER>");
                  client.println("<h1>DU AN NHA THONG MINH (SMART HOUSE)</h1>");
            client.println("</CENTER>");
            client.println("<br />");
            client.println("<CENTER>");
                 if (dencong == 1) client.println("DEN CONG:<b>ON</b>");
                 else client.println("DEN CONG: <b>OFF</b>");
                 //client.println("<br />");
                 client.println("<a href=\"/dencong=on\"\"><button>Turn On </button></a>");
                 client.println("<a href=\"/dencong=off\"\"><button>Turn Off </button></a><br />");
             client.println("</CENTER>");
             client.println("<br><br>");
             client.println("<CENTER>");
                   if (dengara == 1) client.println("DEN GARA:<b>ON</b>");
                   else client.println("DEN GARA: <b>OFF</b>");
                   //client.println("<br />");
                   client.println("<a href=\"/dengara=on\"\"><button>Turn On </button></a>");
                   client.println("<a href=\"/dengara=off\"\"><button>Turn Off </button></a><br />");
             client.println("</CENTER>");
             client.println("<br><br>");
             client.println("<CENTER>");
                   if (denvuon == 1) client.println("DEN VUON:<b>ON</b>");
                   else client.println("DEN VUON: <b>OFF</b>");
                   //client.println("<br />");
                   client.println("<a href=\"/denvuon=on\"\"><button>Turn On </button></a>");
                   client.println("<a href=\"/denvuon=off\"\"><button>Turn Off </button></a><br />");
             client.println("</CENTER>");
             client.println("<br><br>");
             client.println("<CENTER>");
                   if (denkhach == 1) client.println("DEN KHACH:<b>ON</b>");
                   else client.println("DEN KHACH: <b>OFF</b>");
                   //client.println("<br />");
                   client.println("<a href=\"/denkhach=on\"\"><button>Turn On </button></a>");
                   client.println("<a href=\"/denkhach=off\"\"><button>Turn Off </button></a><br />");
             client.println("</CENTER>");
             client.println("<br><br>");
            client.println("<CENTER>");
                   if (denbep == 1) client.println("DEN BEP:<b>ON</b>");
                   else client.println("DEN BEP: <b>OFF</b>");
                   //client.println("<br />");
                   client.println("<a href=\"/denbep=on\"\"><button>Turn On </button></a>");
                   client.println("<a href=\"/denbep=off\"\"><button>Turn Off </button></a><br />");
             client.println("</CENTER>");
             client.println("<br><br>");
             client.println("<CENTER>");
                   if (denngu1 == 1) client.println("DEN NGU 1:<b>ON</b>");
                   else client.println("DEN NGU 1: <b>OFF</b>");
                   //client.println("<br />");
                   client.println("<a href=\"/denngu1=on\"\"><button>Turn On </button></a>");
                   client.println("<a href=\"/denngu1=off\"\"><button>Turn Off </button></a><br />");
             client.println("</CENTER>");
             client.println("<br><br>");
              client.println("<CENTER>");
                   if (denngu2 == 1) client.println("DEN NGU 2:<b>ON</b>");
                   else client.println("DEN NGU 2: <b>OFF</b>");
                   //client.println("<br />");
                   client.println("<a href=\"/denngu2=on\"\"><button>Turn On </button></a>");
                   client.println("<a href=\"/denngu2=off\"\"><button>Turn Off </button></a><br />");
             client.println("</CENTER>");
             client.println("<br><br>");
              client.println("<CENTER>");
                 if (quatkhach == 1) client.println("QUAT KHACH:<b>ON</b>");
                 else client.println("QUAT KHACH: <b>OFF</b>");
                 //client.println("<br />");
                 client.println("<a href=\"/quatkhach=on\"\"><button>Turn On </button></a>");
                 client.println("<a href=\"/quatkhach=off\"\"><button>Turn Off </button></a><br />");
             client.println("</CENTER>");
             client.println("<br><br>");
//              client.println("<CENTER>");
//                 if (quatngu == 1) client.println("QUAT NGU:<b>ON</b>");
//                 else client.println("QUAT NGU: <b>OFF</b>");
//                 //client.println("<br />");
//                 client.println("<a href=\"/quatngu=on\"\"><button>Turn On </button></a>");
//                 client.println("<a href=\"/quatngu=off\"\"><button>Turn Off </button></a><br />");
//             client.println("</CENTER>");
             client.println("<br><br>");
              client.println("<CENTER>");
                 if (quatbep == 1) client.println("QUAT BEP:<b>ON</b>");
                 else client.println("QUAT BEP: <b>OFF</b>");
                 //client.println("<br />");
                 client.println("<a href=\"/quatbep=on\"\"><button>Turn On </button></a>");
                 client.println("<a href=\"/quatbep=off\"\"><button>Turn Off </button></a><br />");
             client.println("</CENTER>");
             client.println("<br><br>");
             client.println("<CENTER>");
                 client.println("<b>TAT HET THIET BI DIEN: </b>");
                 //client.println("<br />");
                 client.println("<a href=\"/offall\"\"><button>Turn Off </button></a><br />");
             client.println("</CENTER>");
  //         client.println("<br><br>");
  //             client.println("<CENTER>");
  //             client.print("NHIET DO:");
  //             client.print("<b>");              
  //             client.print(t);
  //             client.print(" *C");
  //             client.print("</b>");
  //             client.println("<br><br>");

  //             client.print("TINH TRANG MUA:");
  //             client.print("<b>"); 
  //             if (mua == HIGH) client.print(" KHONG MUA");
  //             else client.print(" DANG MUA");
  //             client.print("</b>"); 
//             client.println("<br><br>");
//             client.println("</CENTER>");
             client.println("</HTML>");
  
          delay(10);
}
