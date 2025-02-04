cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(SevenWondersDuel VERSION 1.0 DESCRIPTION "7 Wonders Duel Game Simulation" LANGUAGES CXX)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

# Add directories to the list of paths to search for include files
include_directories(${PROJECT_SOURCE_DIR}/game)
include_directories(${PROJECT_SOURCE_DIR}/gui)
include_directories(${PROJECT_SOURCE_DIR}/ressources)

# Collect all the sources
file(GLOB SOURCES "game/*.cpp" "gui/*.cpp")
file(GLOB HEADERS "game/*.h" "gui/*.h")



# Define the executable with all sources files and the main test file
add_executable(SevenWondersDuel ${SOURCES}
        main.cpp
        game/carte.h game/cartes_data.h game/enum.h game/exception.h game/jeton.h game/joueur.h game/merveille.h game/partie.h game/plateau.h game/ressources.h
        gui/vuecarte.cpp gui/vuecarte.h gui/vuejoueur.cpp gui/vuejoueur.h gui/vuemerveille.cpp gui/vuemerveille.h gui/vuepartie.cpp gui/vuepartie.h gui/vueplateau.cpp gui/vueplateau.h gui/vueressource.cpp gui/vueressource.h
        gui/vuemescartes.h
        gui/vuemescartes.cpp
        gui/vuedefausse.h
        gui/vuedefausse.cpp
        gui/choixdialogue.h
        gui/choixdialogue.cpp
        gui/merveillesdialogue.h
        gui/merveillesdialogue.cpp
        ressources/academie.png
        ressources/apothicaire.png
        ressources/aqueduc.png
        ressources/arene.png
        ressources/armurerie.png
        ressources/arsenal.png
        ressources/atelier.png
        ressources/atelier_de_siege.png
        ressources/autel.png
        ressources/bains.png
        ressources/baraquements.png
        ressources/bassin_argileux.png
        ressources/bibliotheque.png
        ressources/brasserie.png
        ressources/briqueterie.png
        ressources/caravanserail.png
        ressources/carriere.png
        ressources/caserne.png
        ressources/cavite.png
        ressources/chambre_de_commerce.png
        ressources/champs_de_tir.png
        ressources/chantier.png
        ressources/circus_maximus.png
        ressources/cirque.png
        ressources/colosse.png
        ressources/depot_argile.png
        ressources/depot_de_bois.png
        ressources/depot_de_pierre.png
        ressources/dispensaire.png
        ressources/dos_age_deux.png
        ressources/dos_age_trois.png
        ressources/dos_age_un.png
        ressources/dos_guilde.png
        ressources/douane.png
        ressources/ecole.png
        ressources/ecurie.png
        ressources/etude.png
        ressources/exploitation.png
        ressources/fortifications.png
        ressources/forum.png
        ressources/gisement.png
        ressources/grand_phare.png
        ressources/grande_bibliotheque.png
        ressources/guilde_des_armateurs.png
        ressources/guilde_des_batisseurs.png
        ressources/guilde_des_commerçants.png
        ressources/guilde_des_magistrats.png
        ressources/guilde_des_scientifiques.png
        ressources/guilde_des_tacticiens.png
        ressources/guilde_des_usuries.png
        ressources/haras.png
        ressources/hotel_de_ville.png
        ressources/jardins.png
        ressources/jardins_suspendus.png
        ressources/laboratoire.png
        ressources/mausolee.png
        ressources/mine.png
        ressources/murail.png
        ressources/obelisque.png
        ressources/observatoire.png
        ressources/officine.png
        ressources/palace.png
        ressources/palissade.png
        ressources/pantheon.png
        ressources/phare.png
        ressources/piree.png
        ressources/place_armes.png
        ressources/port.png
        ressources/presse.png
        ressources/pretoire.png
        ressources/pyramides.png
        ressources/rostres.png
        ressources/scierie.png
        ressources/scriptorium.png
        ressources/sechoir.png
        ressources/senat.png
        ressources/soufflerie.png
        ressources/sphinx.png
        ressources/statue.png
        ressources/statue_zeus.png
        ressources/taverne.png
        ressources/temple.png
        ressources/temple_artemis.png
        ressources/theatre.png
        ressources/tour_de_garde.png
        ressources/tribunal.png
        ressources/universite.png
        ressources/verrerie.png
        ressources/via_appia.png

        gui/ConstructionMerveilleDialogue.cpp
        gui/ConstructionMerveilleDialogue.h
        gui/ConstructionMerveilleDialogue.cpp
        gui/ConstructionMerveilleDialogue.h
        gui/clickablelabel.h
        gui/clickablelabel.cpp

        ressources/demarrage.png
        gui/choixjetondialogue.h
        gui/choixjetondialogue.cpp
        gui/vuevictoire.h
    )
# If you have any other directories with header files, include them as well
# target_include_directories(SevenWondersDuel PRIVATE some/other/directory)

# Link libraries (if you have any)
target_link_libraries(SevenWondersDuel Qt6::Widgets)

# Ensure the MOC files are generated
qt6_wrap_cpp(MOC_SOURCES ${HEADERS})
target_sources(SevenWondersDuel PRIVATE ${MOC_SOURCES})
