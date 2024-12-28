#include "appli.h"

CWifi::CWifi() { ; }    // Constructeur de la classe CWifi.

void CWifi::Connexion(String reseau, String mdpass) {
    Serial.print("Attente connexion wifi au réseau : ");    // Affiche le message d'attente de connexion.
    Serial.println(reseau); // Affiche le nom du réseau auquel se connecter.
    while (begin(reseau.c_str(), mdpass.c_str()) != WL_CONNECTED) { // Boucle tant que la connexion n'est pas établie.
        Serial.print(".");  // Affiche un point pour indiquer l'attente.
        delay(3000);    // Attend 3 secondes avant de réessayer.
    }
    Serial.println("=>Connecté!");  // Affiche un message de confirmation de connexion.

    AfficheStatut();    // Appelle la fonction AfficheStatut pour afficher les informations de connexion.
}

void CWifi::AfficheStatut() {
    String version_wifi = firmwareVersion();     // Récupère la version du firmware wifi.
    if (version_wifi < WIFI_FIRMWARE_LATEST_VERSION) {
        Serial.print("Obsolescence firmware wifi : ");  // Affiche un avertissement sur l'obsolescence du firmware wifi.
        Serial.println(version_wifi);   // Affiche la version actuelle du firmware wifi.
        Serial.print("Dernière version : ");    // Affiche la dernière version du firmware wifi.
        Serial.println(WIFI_FIRMWARE_LATEST_VERSION);
    }
    Serial.print("Réseau: ");   // Affiche le nom du réseau auquel on est connecté.
    Serial.println(SSID()); // Affiche le nom du réseau WiFi actuel.
    Serial.print("Adresse IP: ");   // Affiche l'adresse IP attribuée.
    Serial.println(localIP());  // Affiche l'adresse IP locale attribuée à l'appareil.
    Serial.print("Niveau du signal: "); // Affiche le niveau du signal wifi.
    Serial.print(RSSI());   // Récupère et affiche le niveau du signal RSSI.
    Serial.println(" dBm"); // Unité de mesure du niveau du signal (dBm : décibels milliwatts).

}
