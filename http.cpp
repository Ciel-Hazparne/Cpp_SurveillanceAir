#include "appli.h"

// Constructeur de la classe CHttp
CHttp::CHttp(String adresse, String path, int port) {
    m_port = port;
    m_path = path;
    m_adresse = adresse;
    m_hote = m_adresse.substring(8);  // Extraction du nom de l'hôte de l'adresse et attribution à l'attribut m_hote de l'objet
}

// Méthode pour envoyer des données via une requête POST
void CHttp::postData(String valeur, String type, String temp) {
    // Création d'une chaîne de caractères au format JSON pour les données à envoyer.
    String data = "{";
    data += "\"data\": " + valeur + ",";
    data += "\"date\": " + String("\"" + temp + "\"");
    data += "}";

    // Envoi d'une requête POST à l'API pour les données du capteur (type : CO2, température, etc.).
    if (connected()) stop();
    Serial.println("Connexion HTTP");

    //Connexion par nom de domaine
    bool result = connect(m_adresse.c_str(), m_port);
    // Connexion par IP si la connexion par nom de domaine a échoué
    if (!result) result = connect(m_ip, m_port);
    if (result) {
        Serial.println(m_adresse.c_str());
        Serial.println(type);
        // Envoi de l'en-tête de la requête POST avec les informations nécessaires.
        println("POST /api/" + type + " HTTP/1.1");
        println("Host: " + String(m_adresse.c_str()));
        println("Accept: */*");
        println("Content-Type: application/json");
        println("Content-Length: " + String(data.length()));
        println();
        // Envoi du corps de la requête POST contenant les données au format JSON.
        print(data);
        // Affichage des données envoyées dans le moniteur série.
        Serial.println(data);
    } else Serial.println("Échec connexion HTTP");
}
