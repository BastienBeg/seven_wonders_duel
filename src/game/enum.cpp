#include "enum.h"
// Surcharge des operateur << pour les enums


// -- Chainage -- : 

std::ostream& operator<<(std::ostream& flux, const Chainage& chainage) {
    switch (chainage) {
    case Chainage::AUCUN:
        flux << "Aucun";
        break;
    case Chainage::AMPHORE:
        flux << "Amphore";
        break;
    case Chainage::TAMBOUR:
        flux << "Tambour";
        break;
    case Chainage::MASQUE:
        flux << "Masque";
        break;
    case Chainage::TEMPLE:
        flux << "Temple";
        break;
    case Chainage::SOLEIL:
        flux << "Soleil";
        break;
    case Chainage::GOUTTE:
        flux << "Goutte";
        break;
    case Chainage::PILLIER:
        flux << "Pillier";
        break;
    case Chainage::LUNE:
        flux << "Lune";
        break;
    case Chainage::CIBLE:
        flux << "Cible";
        break;
    case Chainage::CASQUE:
        flux << "Casque";
        break;
    case Chainage::FER:
        flux << "Fer";
        break;
    case Chainage::EPEE:
        flux << "Ep�e";
        break;
    case Chainage::TOUR:
        flux << "Tour";
        break;
    case Chainage::HARPE:
        flux << "Harpe";
        break;
    case Chainage::ENGRENAGE:
        flux << "Engrenage";
        break;
    case Chainage::LIVRE:
        flux << "Livre";
        break;
    case Chainage::LAMPE:
        flux << "Lampe";
        break;

    }
    return flux;
}

bool operator==(Chainage c1, Chainage c2) {
    return static_cast<int>(c1) == static_cast<int>(c2);
}

bool operator!=(Chainage c1, Chainage c2) {
    return !(c1 == c2);
}


// -- symbole scientifique--
std::ostream& operator<<(std::ostream& os, Symbol_Scientifique symbol) {
    switch (symbol) {
        case Symbol_Scientifique::GLOBE:
            os << "Globe";
            break;
        case Symbol_Scientifique::BALANCE:
            os << "Balance";
            break;
        case Symbol_Scientifique::CADRAN:
            os << "Cadran";
            break;
        case Symbol_Scientifique::BOL:
            os << "Bol";
            break;
        case Symbol_Scientifique::COMPAS:
            os << "Compas";
            break;
        case Symbol_Scientifique::PLUME:
            os << "Plume";
            break;
        case Symbol_Scientifique::ROUE:
            os << "Roue";
            break;
        default:
            os << "Symbole inconnu";
            break;
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const AGE& age) {
    switch (age) {
        case AGE::AGE1: os << "AGE1"; break;
        case AGE::AGE2: os << "AGE2"; break;
        case AGE::AGE3: os << "AGE3"; break;
        case AGE::FIN: os << "FIN"; break;
            // Add more cases if there are more AGE values
        default: os << "Unknown AGE"; break;
    }
    return os;
}
