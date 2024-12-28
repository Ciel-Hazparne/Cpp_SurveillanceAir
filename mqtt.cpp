#include "appli.h"

// Définition du constructeur de la classe CMqtt
CMqtt::CMqtt() : PubSubClient{m_client_wifi} {}

// Méthode pour établir une connexion MQTT
void CMqtt::Connexion(String broker, int port, String id_client) {
    setServer(broker.c_str(), port);

    Serial.print("Attente connexion MQTT broker : ");
    Serial.println(broker);

    // Boucle tant que la connexion n'est pas établie
    while (!connect(id_client.c_str()))//("broker.c_str()", port))
    {
        Serial.print(".");
        delay(5000);
    }

    Serial.println("Connecté");
}

// Méthode pour publier un message MQTT
void CMqtt::Publie(String topic, String valeur) {
    publish(topic.c_str(), valeur.c_str());
    Serial.print("Envoi MQTT :");
    Serial.print(topic);
    Serial.print(" valeur :");
    Serial.println(valeur);
}
