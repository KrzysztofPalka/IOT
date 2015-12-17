
#include <SPI.h>

#include <Ethernet.h>

#include<OneWire.h>

// Enter a MAC address and IP address for your controller below.

// The IP address will be dependent on your local network:

byte mac[] = {

  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED

};

IPAddress ip(192, 168, 0, 66);


// Initialize the Ethernet server library

// with the IP address and port you want to use

// (port 80 is default for HTTP):

EthernetServer server(80);


void setup() {

  pinMode(2, INPUT); 

   pinMode(8, OUTPUT); 

   pinMode(12, OUTPUT); 

   pinMode(1, OUTPUT); 

   pinMode(4, OUTPUT); 

   digitalWrite(1, HIGH);


  // Open serial communications and wait for port to open:

  Serial.begin(9600);

  while (!Serial) {

    ; // wait for serial port to connect. Needed for Leonardo only

  }



  // start the Ethernet connection and the server:

  Ethernet.begin(mac, ip);

  server.begin();

  Serial.print("server is at ");

  Serial.println(Ethernet.localIP());

}



void loop() {


  int i=0;

  // listen for incoming clients

  EthernetClient client = server.available();

  if (client) {

    Serial.println("new client");

    // an http request ends with a blank line

    boolean currentLineIsBlank = true;

    while (client.connected()) {

      i++;

      if (client.available()) {

        char c = client.read();

        Serial.write(c);

           if(i==6){

            int przycisk = digitalRead(8);

            if(c=='0'){

              digitalWrite(8, LOW);

              }

             if(c=='1'){

              digitalWrite(8, HIGH);

              }

              if(c=='4'){

             digitalWrite(12, LOW);

              }

             if(c=='5'){

              digitalWrite(12, HIGH);

              }

              if(c=='2'){

              digitalWrite(1, LOW);

              }

             if(c=='3'){

              digitalWrite(1, HIGH);

              }


          if(digitalRead(2)==HIGH){

            Serial.print("Light ON");}else{Serial.print("Light OFF");}

              

         Serial.print("\n");

        Serial.write(c);

        Serial.print("\n");

           }

  String buffer;  

          

if (c == '\n') {


currentLineIsBlank = true;

buffer="";

} else if (c == '\r') {

  

if(buffer.indexOf("GET /?value=99999")>=0)

Serial.print("ccccccc");


}







        

        // if you've gotten to the end of the line (received a newline

        // character) and the line is blank, the http request has ended,

        // so you can send a reply

        if (c == '\n' && currentLineIsBlank) {

          // send a standard http response header

          client.println("HTTP/1.1 200 OK");

          client.println("Content-Type: text/html");

          client.println("Connection: close");  // the connection will be closed after completion of the response

          client.println("Refresh: 5");  // refresh the page automatically every 5 sec

          client.println();

          client.println("<!DOCTYPE HTML>");

          client.println("<html>");

          // output the value of each analog input pin

          for (int analogChannel = 0; analogChannel < 6; analogChannel++) {

            int sensorReading = analogRead(analogChannel);

            client.print("analog input ");

            client.print(analogChannel);

            client.print(" is ");

            client.print(sensorReading);

            client.println("<br />");

            client.println("<input type=\"text\" name='value'/>");

          }

          client.println("</html>");

          break;

        }

        if (c == '\n') {

          // you're starting a new line

          currentLineIsBlank = true;

        }

        else if (c != '\r') {

          // you've gotten a character on the current line

          currentLineIsBlank = false;

        }

      }

    }

    // give the web browser time to receive the data

    delay(1);

    // close the connection:

    client.stop();

    Serial.println("client disconnected");

  }

}



