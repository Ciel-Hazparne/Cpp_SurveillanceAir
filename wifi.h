#ifndef WIFI_H
#define WIFI_H

#include <WiFiNINA.h>

class CWifi : public WiFiClass
{
private :

public:
    CWifi();  // Constructeur de la classe CWifi

    void Connexion(String reseau, String mdpass); // Méthode pour se connecter à un réseau WiFi en utilisant un nom de réseau (reseau) et un mot de passe (mdpass)

    void AfficheStatut(); // Méthode pour afficher le statut de la connexion WiFi
};

#endif
