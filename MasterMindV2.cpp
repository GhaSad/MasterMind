#include <iostream>
#include <string>
#include <array>
#include <cstdlib>
#include <ctime>


void init_jeu(std::string &j1, int &nb_manches, int &nb_couleurs,int &nb_tentatives)
{
    char rep;
    std::cout<<"Bienvenue dans le menu du jeu MasterMind. Voulez-vous une explication du deroulement du jeu ? (o/n)"; std::cin>>rep;std::cout<<std::endl;
    if(rep=='o')
    {
        std::cout<<"Le jeu se deroule entre deux joueurs : "<<std::endl;
        std::cout<<"Le premier decide du code couleur secret "<<std::endl;
        std::cout<<"Et le deuxieme possede un nombre de tentatives choisis pour deviner l'ordre des couleurs "<<std::endl;
        std::cout<<"Apres la saisie de la reponse, le premier joueur donne un indice qui indique le nombre de couleurs correctes ainsi que leurs ordres "<<std::endl;
        std::cout<<"Vous pouvez choisir le nombre de manches a jouer, ainsi que la difficulte "<<std::endl;
        std::cout<<"Facile -> 2 couleurs "<<std::endl;
        std::cout<<"Moyen -> 3 couleurs "<<std::endl;
        std::cout<<"Difficle -> 4 couleurs "<<std::endl;
        std::cout<<"Les couleurs disponibles sont : "<<std::endl;
        std::cout<<"Rouge(R) , Bleu(B), Jaune(J), Violet(V) "<<std::endl;
        std::cout<<"Si la manche se termine avant que le code ne soit devine, le premier joueur gagne, dans le cas contraire, le deuxieme joueur emporte la manche "<<std::endl<<std::endl;
    }
    std::cout<<"Nom du joueur ? " ; std::cin>>j1;
    std::cout<<"Nombre de manches ? " ; std::cin>>nb_manches;
    std::cout<<"Nombre de tentatives ? "; std::cin>>nb_tentatives;
    char difficulte; 
    std::cout<<"Quelle difficulte ? (facile(f),moyen(m),difficile(d)) "; std::cin>>difficulte;
    if(difficulte=='f')
        nb_couleurs=2;
    else if(difficulte=='m')
        nb_couleurs=3;
    else if(difficulte=='d')
        nb_couleurs=4;
    else std::cout<<"Difficulte parametree a moyen par defaut !"<<std::endl;
    using couleur = std::array<std::string,4>;
    couleur c = {"Rouge","Bleu","Jaune","Violet"};
    std::cout<<"Les couleurs disponibles sont donc : ";
    int compteur_couleur = 0;
    while(compteur_couleur < nb_couleurs)
    {
        std::cout<<c[compteur_couleur]<<" ";
        compteur_couleur++;
    }
    std::cout<<std::endl;
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

}

bool verif(std::string reponse, std::string code)
{
    if(reponse.length()!=code.length())
        return false;
    else if(reponse==code)
        return true;
    else return false;
}

int compt_couleur(char couleur, std::string suite_couleurs)
{
    int compteur=0;
    for(int i=0 ; i<suite_couleurs.length(); ++i)
    {
        if(suite_couleurs[i]==couleur)
            compteur++;
    }
    return compteur;
}

void genere_indice(std::string reponse, std::string code)
{
    int mauvaise_couleur=0;
    for(int i=0 ; i<4 ; ++i)
    {
        int occ_rep = compt_couleur(reponse[i],reponse), occ_code = compt_couleur(reponse[i],code);
        if (occ_rep != occ_code)
            if(occ_code < occ_rep)
                mauvaise_couleur = occ_rep - occ_code;
            else 
                mauvaise_couleur = occ_code - occ_rep;
    }
    int mauvais_ordre=0;
    for(int i=0 ; i<4 ; i++)
    {
        if(reponse[i]!=code[i])
            mauvais_ordre++;
    }
    std::cout<<"Vous avez "<<mauvaise_couleur<<" mauvaises couleurs "<<std::endl;
    std::cout<<"Vous avez "<<mauvais_ordre<<" couleur dans le mauvais emplacement "<<std::endl;
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
        if(verif(code,reponse))
        {
            std::cout<<j1<<" a gagne en "<<tour<<" tours !"<<std::endl;
            manche_gagnee +=1 ;
            return;
        }
        else
            genere_indice(reponse,code);
    }
    std::cout<<"Vous avez perdu cette manche !"<<std::endl;
}

int main()
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
    return 0;
}