#include "appli.h"

CAppli appli; // Instance de la classe CAppli

void setup() {
    float seuilCO2 = 1000.0; // Définition d'une variable seuilCO2 avec la valeur 1000.0
    appli.Init(seuilCO2); // Appel de la fonction Init de l'objet appli pour initialiser avec le seuilCO2
}

void loop() {
    appli.Run(10000); // Appel de la fonction Run de l'objet appli avec l'argument 10000 pour exécuter la boucle principale
}
