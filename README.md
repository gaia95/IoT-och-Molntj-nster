# IoT-och-Molntjänster-Temperatur sensor

Projektbeskrivning
Detta projekt fokuserar på att samla in data från en sensor. Syftet med arbetet är att övervaka temperaturen med hjälp av en sensor som samlar in data och lagrar det i en molntjänst. Genom att använda en enkel temperatursensor och överföring av data till Azure IoT-plattformen, möjliggörs långsiktig datalagring och fjärrövervakning.
Komponenter för projektet:

  - TMP36GZ-sensor: Analog sensor för övervakning av temperatur.


  - Azure IoT Molntjänst: Molnbaserad plattform som kan hantera och          ansluta till IoT-enheter och dess data. Azure erbjuder även inbyggda     säkerhetsfunktioner. 


  - Azure IoT Hubb: En tjänst som möjliggör kommunikation och hantering      av ett flertal IoT-enheter.


  - Esp32: Mikrokontroller med inbyggd Wifi. Den möjliggör trådlös           kommunikation och samlar in data från temperatursensorn som sedan        skickas vidare till Azure IoT Hubb.


  - Breadboard: Arbetsyta för projektets komponenter.


Översikt:

ProjektDiagram.drawio.png

Huvudsyftet är att sammanställa data från TMP36-sensorn med hjälp av ESP 32-mikrokontroller och överföra denna information till Azure IoT Hub. Därefter är tanken att dess data lagras i en Cosmos DB-databas samt realtidsanalys och bearbetning genom användning av Stream Analytics-tjänsten i Azure. 


Slutligen är avsikten att överföra det bearbetade data till Power BI för att skapa visuella representationer. ESP32 kommer att ansvara för överföringen av data till Azure IoT Hub, där integration med Azure Functions ska implementeras för att skapa en trigger. Denna funktions-trigger ska sedan användas för att starta sändning av meddelanden till användaren via Telegram om sensorn känner av en viss temperatur. Integration av telegram är möjligt med Azure-funktioner och Telegrams API. Man behöver dock om man har rätt autentiserings nycklar.

Koppling: 

kopplingsch.png


Anslutning av TMP36GZ-temperatursensorn till ESP 32 för mätning av omgivningstemperaturen. Kopplar ihop ESP’s hårdvaru pinnar till brädan för att förse den med ström.

Information om användning

1. Installation av Azure SDK C-bibliotek och den senaste versionen av Arduino IDE. Man behöver även välja en bräda som representerar den fysiska mikrokontrollern som man utvecklar sitt projekt på. I mitt fall är det ESP32 Dev Module.

2. För att generera data kan man röra på sensorn för olika temperaturer.

3. Datat samlas med hjälp av enheten (ESP 32) och skickar det till Azure IoT Hub.

   IoT Hubb msg.png

5. För att överföra data till IoT-hubben, krävs det viktig information om Azure IoT-Hubb, enhetens ID och nyckel samt WiFi-anslutningen:

// Wifi
#define IOT_CONFIG_WIFI_SSID "SSID"
#define IOT_CONFIG_WIFI_PASSWORD "PWD"

// Azure IoT
#define IOT_CONFIG_IOTHUB_FQDN "Your Azure IoT host name.azure-devices.net"
#define IOT_CONFIG_DEVICE_ID "DEVICE ID"
#define IOT_CONFIG_DEVICE_KEY "DEVICE KEY"





