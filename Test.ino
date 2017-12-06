
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>
#include <Wire.h>
//wifi i mysql zmienne
IPAddress ip(12, 12, 12, 125);
IPAddress gat(12, 12, 12, 55);
IPAddress subnet(255, 255, 255, 0);

WiFiClient client;
MySQL_Connection conn((Client *)&client);
//"pid"
float Setpoint, Input, Out;
float Kp = 2, Ki = 0, Kd = 0;
//zapytania do SQL
char INSERT_SQL[] = "UPDATE pkss.system SET value = '%d.%d' WHERE name = 'Tr1'";
char SELECT_SQL_B[] = "SELECT value FROM pkss.system WHERE name = 'Tr1' ";
char SELECT_SQL_Z[] = "SELECT value FROM pkss.system WHERE name = 'Tr1zad' ";
char query[128];
float zmienna1=-200.6;
float zadana=23;
void setup()
{
  /* wifi */
	Serial.begin(115200);
  /*
	WiFi.config(ip, gat, subnet);
	bool isConnected = false;
	
	WiFi.begin("PKSS", "qwe147rty258");
	//WiFi.begin("gx0", "zxcvb123");
	//WiFi.begin("AndroidAP", "sddj1894");
	while (!(isConnected = WiFi.isConnected()))
	{
		Serial.println(isConnected);
		delay(500);
	}
	Serial.println(WiFi.gatewayIP());
	Serial.println("Connecting tosql ");
	if (conn.connect(gat, 3306, "pkss", "pkss125")) {
		delay(1000);
	}
	else {
		Serial.println("Connection failed.");
		conn.close();
	}

	Serial.println("'PID' controller set");
	*/
}
	/*
	HTTPClient client;

	client.begin("http://psychiatryk.ml");
	client.GET();
	WiFiClient stream = client.getStream();
	String s = stream.readString();

	Serial.println(s);*/
	//pinMode(8, OUTPUT);
	


void loop()
{
	/*
	row_values *row = NULL;
	MySQL_Cursor cur_in = MySQL_Cursor(&conn);
	MySQL_Cursor cur_out = MySQL_Cursor(&conn);
	
	cur_out.execute(SELECT_SQL_B);
	cur_out.get_columns();
	do {
		row = cur_out.get_next_row();
		if (row != NULL) {
			zmienna1 = atol(row->values[0]);
		}
	} while (row != NULL);
	cur_out.execute(SELECT_SQL_Z);
	cur_out.get_columns();
	do {
		row = cur_out.get_next_row();
		if (row != NULL) {
			zadana = atol(row->values[0]);
		}
	} while (row != NULL);
	*/

	//tutaj regulacja
	if (zmienna1<zadana) {
		zmienna1 = zmienna1 + Kp;
	}
	else if (zmienna1 > zadana) {
		zmienna1 = zmienna1 - 0.1;
	}

	//UWAGA - CZARY MARY
	int tmpInt1 = zmienna1;
	float tmpFrac = zmienna1 - tmpInt1;
	int tmpInt2 = abs(trunc(tmpFrac * 100));
	sprintf(query, INSERT_SQL, tmpInt1, tmpInt2);
	// CZARY MARY END;
	delay(1000);
	//cur_in.execute(query);
	Serial.println(query);
	Serial.println(zadana);
	Serial.println(zmienna1);
	//cur_in.close();
	//cur_out.close();
	
}
