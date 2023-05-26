#include "mastermindV1.h"
#include "mastermindV2.h"
#include "mastermindV3.h"
#include <string>
#include <iostream>

int main()
{
    int choix;
    std::cout<<"Bienvenue dans le menu du jeu MasterMind !"<<std::endl;
    std::cout<<"Il y a trois versions : "<<std::endl<<std::endl;
    std::cout<<"Une version a deux joueurs, avec un score et un gagnant a la fin "<<std::endl;
    std::cout<<"Une deuxieme ou le joueur doit deviner le code genere par l'ordinateur ."<<std::endl;
    std::cout<<"Et en dernier c'est la version INTELLIGENCE ARTIFICIELLE, ou l'ordinateur devra deviner votre code."<<std::endl;
    std::cout<<"A quelle version voulez-vous jouer ? (1-2-3)"<<std::endl;
    std::cin>>choix;
    while(choix!=1 and choix!=2  and choix !=3)
    {
        std::cout<<"Erreur veuillez choisir 1 ou 2 ou 3 ."<<std::endl;
        std::cin>>choix;
    }
    if(choix==1)
    {
        int nb_tentatives, nb_couleurs, nb_manches, score_j1=0 , score_j2=0;
        init_jeu(nb_tentatives,nb_couleurs,nb_manches);
        std::string j1, j2;
        saisie_joueurs(j1,j2);
        std::string code; int tour=0;
        int manche=0;
        while(manche < nb_manches)
        {
            std::string gagnant ; 
            manche++;
            std::cout<<"Manche numero "<<manche<<std::endl;
            jeu(code,j2,j1,nb_tentatives,gagnant);
            if(gagnant == j1) score_j1++;
            else score_j2++;
            if(manche==nb_manches)              // Si jamais le nb_manches est impaire, on sort de la boucle while
                break;
            manche++;
            std::cout<<"Manche numero "<<manche<<std::endl;
            jeu(code,j1,j2,nb_tentatives,gagnant);
            if(gagnant == j1) score_j1++;
            else score_j2++;
        }
        if(score_j1 > score_j2)
            std::cout<<j1<<" remporte la partie !! Le score final est :"<<score_j1<<"-"<<score_j2<<std::endl;
        else if(score_j1 < score_j2)
            std::cout<<j2<<" remporte la partie !! Le score final est :"<<score_j2<<"-"<<score_j1<<std::endl;
        else
            std::cout<<"Les deux joueurs sont a egalite !!"<<std::endl;
    }
    else if(choix==2)
    {
        std::string j1, code; int nb_couleurs, nb_manches, nb_tentatives, manche_gagnee=0, manche=0;
        init_jeu(j1,nb_manches,nb_couleurs,nb_tentatives);
        while(manche < nb_manches)
        {
            manche++;
            std::cout<<"Manche numero "<<manche<<std::endl;
            jeu(code,j1,nb_tentatives,nb_couleurs,manche_gagnee);
        }
        std::cout<<"Vous avez gagne "<<manche_gagnee<<" manches !"<<std::endl;
        if(manche_gagnee>=(nb_manches-manche_gagnee))
            std::cout<<"Felicitations, vous avez gagne la partie avec "<<manche_gagnee<<" manches gagnees ! "<<std::endl;
        else 
            std::cout<<"Dommage ! Vous avez perdu la partie avec "<<nb_manches-manche_gagnee<<"manches perdues ! "<<std::endl;
    }
    else if(choix==3)
    {
        int tour = 1;
        bool gagne = false;

        std::cout<<"Saisissez le code : "<<std::endl;
        code=saisie_code();
        tentative = {1, 1, 2, 2}; 

        //Création des 1296 combinaisons possibles
        genere_combinaisons(combinaisons);
        solutionsProbables.insert(solutionsProbables.end(), combinaisons.begin(), combinaisons.end());

        std::cout << "Code : ";
        intTostring(code);
        std::cout <<" "<< std::endl;
        std::cout << std::endl;

        while (!gagne) 
        {

            //On supprime la tentative des solutions possibles
            supprime_code(combinaisons, tentative);
            supprime_code(solutionsProbables, tentative);

            //On veut obtenir l'indice de la tentative
            indice3 = indication(tentative, code);

            std::cout << "Tour : " << tour << std::endl;
            std::cout << "Tentative : ";
            intTostring(tentative);
            std::cout << " = " << indice << std::endl;

            //Si l'indice c'est 4 pions noirs, alors le jeu est fini
            if (indice3 == "BBBB") {
                gagne = true;
                std::cout << "L'ordinateur a trouve la combinaison !" << std::endl;
                break;
            }

            //On supprime des solutions probables tout code qui ne donnerait pas la meme réponse s'il était le code
            triCodes(solutionsProbables, tentative, indice3);

            //On calcule le score minmax
            tentativeSuivantes = minmax();

            //On choisis la tentative suivante
            tentative = tentativeSuivante(tentativeSuivantes);

            tour++;
        }
    }
    return 0;
}