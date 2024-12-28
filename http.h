#ifndef HTTP_H
#define HTTP_H

#include <WiFiNINA.h>

// Classe CHttp pour les requêtes HTTP
class CHttp : public WiFiClient {
private:
    String m_path;  // Chemin de l'URL pour la requête
    String m_adresse = "";  // Adresse de l'hôte
    String m_hote = ""; // Nom de l'hôte
    int m_port; // Numéro de port pour la connexion
    IPAddress m_ip; // Adresse IP de l'hôte (si utilisée)
    unsigned long m_top_envoi = 0;  // Temps écoulé depuis le dernier envoi de données

public:
    // Constructeur prenant l'adresse de l'hôte, le chemin de l'URL et le port
    CHttp(String adresse, String path, int port);

    // Méthode pour envoyer des données en utilisant une requête POST
    void postData(String valeur, String type, String temp);
};

#endif
