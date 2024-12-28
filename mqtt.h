#ifndef MQTT_H
#define MQTT_H

#include <PubSubClient.h>
#include <WiFiNINA.h>

class CMqtt : public PubSubClient {
private:
    WiFiClient m_client_wifi;   // Client WiFi pour la connexion MQTT

public:
    CMqtt();    // Constructeur de la classe CMqtt

    ~CMqtt() {};    // Destructeur de la classe CMqtt

    void Connexion(String broker, int port, String id_client);   // Méthode pour établir la connexion MQTT

    void Publie(String topic, String valeur);   // Méthode pour publier un message MQTT


    void reconnect();   // Méthode pour reconnecter MQTT en cas de perte de connexion

    void deconnecte();  // Méthode pour déconnecter MQTT

};

#endif
