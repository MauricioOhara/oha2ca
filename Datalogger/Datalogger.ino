#include <RTClib.h>
#include <SPI.h>
#include <SD.h>
int Pino_CS = 10;
RTC_DS1307 rtc;
File file;

void setup () {
  Serial.begin(9600);


  Serial.println("Iniciando cartão SD");
  if(!SD.begin(Pino_CS))
  {
    Serial.println("Falha na inicialização do SD!");
    return;
  }
  Serial.println("Cartão SD iniciado. OK");

  // SETUP RTC MODULE
  if (! rtc.begin()) {
    Serial.println("RTC não encontrado");
    Serial.flush();
    while (1);
  }
 //A linha abaixo ajusta o RTC com a data e hora do momento da compilacao
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  //A linha abaixo permite ajustar manualmente a data e hora do RTC
  //Formato: DateTime(ano, mes, dia, hora, minuto, segundo)
  // rtc.adjust(DateTime(2021, 1, 21, 3, 0, 0));



}

void loop () {

grava_cartao_SD("teste");


  delay(1000); // delay 1 seconds
}

void grava_cartao_SD(String uid_card)
{
  //Abre arquivo no SD para gravação
  file = SD.open("log.txt", FILE_WRITE);
  //le as informações de data e hora
  DateTime now = rtc.now();
    //Grava os dados no cartao SD
  file.print("Data/hora: ");
  file.print(now.day() < 10 ? "0" : "");
  file.print(now.day(), DEC);
  file.print('/');
  file.print(now.month() < 10 ? "0" : "");
  file.print(now.month(), DEC);
  file.print('/');
  file.print(now.year(), DEC);
  file.print(' ');
  file.print(now.hour() < 10 ? "0" : "");
  file.print(now.hour(), DEC);
  file.print(':');
  file.print(now.minute() < 10 ? "0" : "");
  file.print(now.minute(), DEC);
  file.print(':');
  file.print(now.second() < 10 ? "0" : "");
  file.print(now.second(), DEC);
  file.print(' ');
  file.print("- UID Cartao: ");
  file.println(uid_card);
  //Fecha arquivo
  file.close();
}
