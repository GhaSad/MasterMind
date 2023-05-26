#include <iostream>
#include <string>
#include <array>
#include <cstdlib>
#include <ctime>


void init_jeu(std::string &j1, int &nb_manches, int &nb_couleurs,int &nb_tentatives)
{
    nb_couleurs=4;
    char rep;
    std::cout<<" Voulez-vous une explication du deroulement du jeu ? (o/n)"; std::cin>>rep;std::cout<<std::endl;
    if(rep=='o')
    {
        std::cout<<"Le jeu se deroule le joueur et l'ordinateur : "<<std::endl;
        std::cout<<"L'ordinateur genere le code couleur secret "<<std::endl;
        std::cout<<"Et le joueur a un nombre de tentatives choisis pour deviner l'ordre des couleurs "<<std::endl;
        std::cout<<"Apres la saisie de la reponse, un indice donne indique le nombre de couleurs correctes ainsi que leurs ordres "<<std::endl;
        std::cout<<"Vous pouvez choisir le nombre de manches a jouer, ainsi que la difficulte "<<std::endl;
        std::cout<<"Facile -> 2 couleurs "<<std::endl;
        std::cout<<"Moyen -> 3 couleurs "<<std::endl;
        std::cout<<"Difficle -> 4 couleurs "<<std::endl;
        std::cout<<"Les couleurs disponibles sont : "<<std::endl;
        std::cout<<"Rouge(R) , Bleu(B), Jaune(J), Violet(V), Marron(M), Orange(O) "<<std::endl;
        std::cout<<"Si la manche se termine avant que le code ne soit devine, le joueur perd la manche "<<std::endl<<std::endl;
    }
    std::cout<<"Nom du joueur ? " ; std::cin>>j1;
    std::cout<<"Nombre de manches ? " ; std::cin>>nb_manches;
    char difficulte;
    std::cout<<"Quelle difficulte ? (facile(f),moyen(m),difficile(d)) "; std::cin>>difficulte;
    while(difficulte!='f' and difficulte!='m' and difficulte!='d')
    {
        std::cout<<"Saisie incorrecte ! Quelle difficulte ? (facile(f),moyen(m),difficile(d)) " ; std::cin>>difficulte;
    }
    if(difficulte=='f')
        nb_tentatives=10;
    else if(difficulte=='m')
        nb_tentatives=8;
    else if(difficulte=='d')
        nb_tentatives=6;
    std::cout<<"Vous avez "<<nb_tentatives<<" tentatives pour trouver la reponse ! "<<std::endl;
    std::cout<<"Vous allez jouer avec les 4 couleurs suivante : Rouge(R) , Bleu(B) , Jaune(J) , Violet(V) "<<std::endl;
    std::cout<<"Que le jeu commence ! " ; std::cout<<std::endl<<std::endl;
}

void genere_code(std::string &code, int nb_couleurs)
{
    char couleurs[4] = {'B', 'R', 'J', 'V'};
    code = "";
    std::srand(std::time(nullptr));
    for(int i = 0; i < 4; ++i)
    {
        int index = std::rand() % nb_couleurs;
        code += couleurs[index];
    }
    std::cout<<"Le code est : "<<code<<std::endl;
}

bool verif1(std::string reponse, std::string code)
{
    if(reponse.length()!=code.length())
        return false;
    else if(reponse==code)
        return true;
    else return false;
}

int occurence_couleur(char couleur, std::string suite_couleurs)
{
    int compteur=0;
    for(int i=0 ; i<suite_couleurs.length(); ++i)
    {
        if(suite_couleurs[i]==couleur)
            compteur++;
    }
    return compteur;
}

void indice(const std::string& tentative, const std::string& secret)
{
    int bon_ordre = 0;
    int mauvais_ordre = 0;
    
    // Tableaux de booléens pour éviter de compter plusieurs fois la même couleur
    bool trouve_secret[4] = {false};
    bool trouve_tentative[4] = {false};
    
    // Comptage des couleurs dans le bon ordre
    for (int i = 0; i < 4; ++i) {
        if (tentative[i] == secret[i]) {
            bon_ordre++;
            trouve_secret[i] = true;
            trouve_tentative[i] = true;
        }
    }
    // Comptage des couleurs correctes mais mal placées
    for (int i = 0; i < 4; ++i) {
        if (!trouve_tentative[i]) {
            for (int j = 0; j < 4; ++j) {
                if (!trouve_secret[j] and tentative[i] == secret[j]) {
                    mauvais_ordre++;
                    trouve_secret[j] = true;
                    break;
                }
            }
        }
    }
    std::cout<<"Vous avez "<<bon_ordre<<" couleurs dans le bon emplacement "<<std::endl;
    std::cout<<"Vous avez "<<mauvais_ordre<<" couleurs correctes mais mal placees "<<std::endl;
}


void jeu(std::string &code, std::string j1, int nb_tentatives, int nb_couleurs, int &manche_gagnee)
{
    int tour=0;
    std::string reponse;
    genere_code(code,nb_couleurs);
    while(tour<=nb_tentatives)
    {
        tour++;
        std::cout<<j1<<" a vous de jouer : "; std::cin>>reponse;
        if(verif1(code,reponse))
        {
            std::cout<<j1<<" a gagne en "<<tour<<" tours !"<<std::endl;
            manche_gagnee +=1 ;
            return;
        }
        else
           indice(reponse,code);
    }
    std::cout<<"Vous avez perdu cette manche ! La reponse etait : "<<code<<std::endl;
}