#include "jeton.h"
std::string Jeton_Progres::getCheminImage() const {
    return R"(../../ressources/)" + nom + ".png";
}
