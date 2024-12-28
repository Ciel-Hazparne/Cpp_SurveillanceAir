#ifndef APPLI_H
#define APPLI_H

/*
#define  VERSION "MKRWIFI_2023.03.07.16h35.V000"
#define VERSION "MKRWIFI_2023.03.08.17h35.wifi_ok.V001"
#define VERSION "MKRWIFI_2023.03.11.17h07.publi_ok.V002"
#define VERSION "MKRWIFI_2023.03.15.17h00.V003"
#define VERSION "MKRWIFI_2023.03.20.09h45.TEST"
#define VERSION "MKRWIFI_2023.03.22.ok"
#define VERSION "MKRWIFI_2023.05.23.15h00.ok.mqtt.http"
#define VERSION "AIR_2023.05.23.15h10.ok.mqtt.http"
#define  VERSION "AIR_2023.05.25.15h45.ok.mqtt.http.relay.ok"
#define VERSION "AIR_2023.05.23.17h30.ok1x.mqtt.ko.http"
*/
#define    VERSION    "AIR_2023.05.30.15h30.testCTemps.ok.http"  // Version actuelle du code


//Librairies configurées pour les classes du projet

//Pour CMqtt :
#include "mqtt.h"

//Pour CHttp :
#include "http.h"

//Pour Temps :

#include <NTPClient.h>
#include <TimeLib.h>

//Pour CWifi :
#include "wifi.h"

//Pour la classe SCD30 Capteur atmosphère ambiante :
//https://github.com/sparkfun/SparkFun_SCD30_Arduino_Library
#include <SparkFun_SCD30_Arduino_Library.h>

//WIFI

#define RESEAU_WIFI "SNIR"  // Nom du réseau WiFi
#define CLEF_WIFI   "bts-snir"  // Clé de sécurité du réseau WiFi


//MQTT
#define BROKER  "broker.mqttdashboard.com"  // Adresse du broker MQTT
#define PORT_MQTT   1883    // Port utilisé pour MQTT

//HTTP

#define SERVER_ADDRESS    "10.0.5.154"  // Adresse du serveur HTTP
#define PATH  "/ HTTP/1.1"  // Chemin de la requête HTTP
#define PORT  80    // Port utilisé pour HTTP

//Relais
#define PORT_RELAIS 4

class CAppli {
private:
    float m_seuilCO2;  // Seuil de CO2
    CWifi m_wifi;  // Objet pour la gestion du WiFi
    CMqtt m_clientMqtt;  // Objet pour la communication MQTT
    CHttp m_clientHttp{SERVER_ADDRESS, PATH, PORT};  // Objet pour la communication HTTP
    SCD30 m_capteur;  // Objet pour le capteur d'atmosphère ambiante SCD30
    unsigned long m_top_run = 0;  // Temps de début de l'exécution
    unsigned long m_last_api_send;  //Variable pour enregistrer le temps du dernier envoi API.
    const unsigned long API_SEND_INTERVAL = 5 * 60 * 1000; // Interval de 5 minutes en millisecondes
    
public:
    CAppli() {};    // Constructeur par défaut

    ~CAppli() {};   // Destructeur

    void Init(float seuilCO2);  // Initialise l'application avec un seuil de CO2 spécifié

    void Init();    // Initialise l'application

    void Run(long intervalle);  // Exécute l'application avec un intervalle de temps spécifié
};

#endif
