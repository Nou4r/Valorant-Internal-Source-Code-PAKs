#include <fstream>
#include <string>
#include "offsets.hpp"

void SaveConfig(const std::string& name) {
    std::ofstream file("./" + name + ".cfg");
    if (!file.is_open()) {
        // Ajouter un message d'erreur pour débugger
        MessageBox(NULL, L"Impossible de créer le fichier", L"Erreur", MB_OK);
        return;
    }
    file << globals::buddy::enabled << "\n";
    file << globals::buddy::index << "\n";
    file.close();
}

void LoadConfig(const std::string& name) {
    std::ifstream file("C:\\" + name + ".cfg");
    if (!file.is_open()) return;



    file >> globals::buddy::enabled;
    file >> globals::buddy::index;

    file.close();
}
