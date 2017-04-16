#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include<Wire.h>

ESP8266WebServer server(80);
const char* ssid="jargon";
const char* password="radhekrishna";
String webSite,javaScript,XML;
int str;
String res;
const int MPU=0x68;  // I2C address of the MPU-6050
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
void buildWebsite(){
  buildJavascript();
  webSite="<!DOCTYPE HTML>\n";
  webSite+=javaScript;
  webSite+="<BODY onload='process()'>\n";
  //webSite+="<div title='mainbody'>\n";
  //webSite+="<BR>This is the ESP website ...<BR>\n";
  webSite+="<A id='runtime'></A>\n";
  //webSite+="</div>\n";
  webSite+="</BODY>\n";
  webSite+="</HTML>\n";
}

void buildJavascript(){
  javaScript="<SCRIPT>\n";
  javaScript+="var xmlHttp=createXmlHttpObject();\n";

  javaScript+="function createXmlHttpObject(){\n";
  javaScript+=" if(window.XMLHttpRequest){\n";
  javaScript+="    xmlHttp=new XMLHttpRequest();\n";
  javaScript+=" }else{\n";
  javaScript+="    xmlHttp=new ActiveXObject('Microsoft.XMLHTTP');\n";
  javaScript+=" }\n";
  javaScript+=" return xmlHttp;\n";
  javaScript+="}\n";

  javaScript+="function process(){\n";
  javaScript+=" if(xmlHttp.readyState==0 || xmlHttp.readyState==4){\n";
  javaScript+="   xmlHttp.open('PUT','xml',true);\n";
  javaScript+="   xmlHttp.onreadystatechange=handleServerResponse;\n"; // no brackets?????
  javaScript+="   xmlHttp.send(null);\n";
  javaScript+=" }\n";
  javaScript+=" setTimeout('process()',1000);\n";
  javaScript+="}\n";

  javaScript+="function handleServerResponse(){\n";
  javaScript+=" if(xmlHttp.readyState==4 && xmlHttp.status==200){\n";
  javaScript+="   xmlResponse=xmlHttp.responseXML;\n";
  javaScript+="   xmldoc = xmlResponse.getElementsByTagName('response');\n";
  javaScript+="   message = xmldoc[0].firstChild.nodeValue;\n";
  javaScript+="   document.getElementById('runtime').innerHTML=message;\n";
  javaScript+="   console.log('Hello Reading is '+message);\n";
  javaScript+="   sendData(message);\n";
  javaScript+=" }\n";
  javaScript+="}\n";

  javaScript+="function sendData(data){\n";
  javaScript+=" var url='http://192.168.43.214:5000/getData';\n";
  javaScript+=" console.log(url);\n";
  javaScript+=" var payload=data;\n";
  javaScript+=" sendRequest(url,payload);\n";
  javaScript+=" }\n";

  javaScript+="function sendRequest(url,payload){\n";
  javaScript+="  var xhr=new XMLHttpRequest();\n";
  javaScript+="  if(xhr){\n";
  javaScript+="    xhr.open('POST',url,true);\n";
  javaScript+="    xhr.setRequestHeader('Content-Type','text/plain');\n";
  javaScript+="    xhr.onreadystatechange=function(){\n";
  javaScript+="      // handleResponse(xhr);\n";
  javaScript+="    };\n";
  javaScript+="    xhr.send(payload);\n";
  javaScript+="  }\n";
  javaScript+="}\n";

  
  
  javaScript+="</SCRIPT>\n";
}

void buildXML(){
  XML="<?xml version='1.0'?>";
  XML+="<response>";
  XML+=millis2time();
  XML+="</response>";
}
String millis2time(){
  /*String Time="";
  unsigned long ss;
  byte mm,hh;
  ss=millis()/1000;
  hh=ss/3600;
  mm=(ss-hh*3600)/60;
  ss=(ss-hh*3600)-mm*60;
  if(hh<10)Time+="0";
  Time+=(String)hh+":";
  if(mm<10)Time+="0";
  Time+=(String)mm+":";
  if(ss<10)Time+="0";
  Time+=(String)ss;
  return Time;*/
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,14,true);  // request a total of 14 registers
  AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp=Wire.read()<<8|Wire.read();  //
  char t_buffer[10];
  float t=AcX/1000;
  String temp=dtostrf(t,0,5,t_buffer);
  res=temp;
   /* server.handleClient();
  if(Serial.available()>0)
  { int tr=Serial.read();
    if(tr==1){
      Serial.println("bulb1");
      //digitalWrite(LED_BUILTIN, LOW);
      res="1 "+temp;
    }
     if(tr==2){
      Serial.println("bulb2");
      //digitalWrite(LED_BUILTIN, LOW);
      res="2 "+temp;
    } if(tr==3){
      Serial.println("bulb3");
      //digitalWrite(LED_BUILTIN, LOW);
      res="3 "+temp;
    } if(tr==4){
      Serial.println("bulb4");
      //digitalWrite(LED_BUILTIN, LOW);
      res="4 "+temp;
    }
  }
  Serial.println('value');
  Serial.println(res);*/
  return res;
  //return res;
}

void handleWebsite(){
  buildWebsite();
  server.send(200,"text/html",webSite);
}

void handleXML(){
  buildXML();
  server.send(200,"text/xml",XML);
}

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid,password);
  while(WiFi.status()!=WL_CONNECTED)delay(500);
  WiFi.mode(WIFI_STA);
  Serial.println("\n\nBOOTING ESP8266 ...");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("Station IP address: ");
  Serial.println(WiFi.localIP());
  server.on("/",handleWebsite);
  server.on("/xml",handleXML);
   Wire.begin(4, 5); // sda, scl
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  //pinMode(LED_BUILTIN, OUTPUT);
  Serial.println("Setup completato...");
  server.begin();
}

void loop() {
  server.handleClient();
  /*if(Serial.available()>0)
  { str=Serial.read();
    if(str=='1'){
      Serial.println("bulb1");
      //digitalWrite(LED_BUILTIN, LOW);
    }
  }*/
}

