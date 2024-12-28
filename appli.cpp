#include "appli.h"

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

void CAppli::Init(float seuilCO2) {
    timeClient.begin(); // Initialisation du client NTP (Network Time Protocol) pour l'horodatage des mesures.
    timeClient.setTimeOffset(
            7200); // Ajustement du décalage horaire par rapport à l'UTC en secondes (ici, 7200 secondes pour UTC+2).
    timeClient.update();

    //Commande Relais
    m_seuilCO2 = seuilCO2;

    //Initialisation Relais
    pinMode(PORT_RELAIS, OUTPUT);

    //Initialisation du port serie
    Serial.begin(115200);
    while (!Serial);

    //Affichage Initialisation de la classe
    Serial.println(VERSION);

    // Connexion au réseau WiFi
    m_wifi.Connexion(RESEAU_WIFI, CLEF_WIFI);

    // Connexion au broker MQTT
    m_clientMqtt.Connexion(BROKER, PORT_MQTT, "id_client");

    //Initialisation du capteur SCD30
    Wire.begin();
    Serial.print("Attente connexion capteur SCD30.");
    while (!m_capteur.begin()) Serial.print(".");
    Serial.println("Connecté.");

     m_last_api_send = millis(); // Enregistrement de l'heure actuelle en millisecondes


}

String printIso8601(time_t t) {
    tmElements_t tm; // Déclaration d'une variable tm de type tmElements_t pour stocker les éléments
    breakTime(t, tm); // Conversion du temps Unix (time_t) en éléments de l'heure (tmElements_t)
    char isoTime[20]; // Déclaration d'un tableau de caractères pour stocker la chaîne de caractères
    sprintf(isoTime,
            "%04d-%02d-%02dT%02d:%02d:%02dZ", // Utilisation de la fonction sprintf pour formater la chaîne de caractères
            tm.Year + 1970, tm.Month, tm.Day,
            tm.Hour, tm.Minute, tm.Second);

    return (String(isoTime)); // Retour de la chaîne de caractères formatée en tant qu'objet String.
}

void CAppli::Run(long intervalle) {
    timeClient.update();  // Mise à jour de l'heure avec le client NTP

    // Vérification du délai écoulé depuis la dernière exécution de Run()
    if (millis() - m_top_run > intervalle)
        m_top_run += intervalle;
    else return;

    // Lecture des mesures de température, CO2 et humidité
    float temperature = m_capteur.getTemperature();
    delay(5);
    float co2 = m_capteur.getCO2();
    delay(5);
    float hygro = m_capteur.getHumidity();
    delay(5);

    // Récupération du temps au format Unix (epoch time) depuis le client NTP
    unsigned long epochTime = timeClient.getEpochTime();

    // Conversion des mesures en chaînes de caractères
    String co2Data = String(co2);
    String tempData = String(temperature);
    String humData = String(hygro);

    // Comparaison de la valeur du CO2 avec le seuil et activation du relais
    digitalWrite(PORT_RELAIS, (co2 >= m_seuilCO2));

    // Publication des mesures sur le broker MQTT
    m_clientMqtt.Publie("AIR/TEMP", String(temperature));
    m_clientMqtt.Publie("AIR/CO2", String(co2));
    m_clientMqtt.Publie("AIR/HUMID", String(hygro));

 // Vérification du délai écoulé depuis le dernier envoi sur l'API
    if (millis() - m_last_api_send > (5 * 60 * 1000)) {  // 5 minutes en millisecondes
        // Envoi des mesures au serveur HTTP
        m_clientHttp.postData(co2Data, "c_o2s", printIso8601(epochTime));
        m_clientHttp.postData(humData, "hygrometries", printIso8601(epochTime));
        m_clientHttp.postData(tempData, "temperatures", printIso8601(epochTime));

        m_last_api_send = millis();  // Met à jour le dernier envoi sur l'API avec l'instant actuel
    }

    

    // Délai de 30 secondes avant la prochaine exécution de Run()
    delay(30000);
}
