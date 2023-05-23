#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <map>

const int TAILLE_CODE = 4;
const int NB_COULEURS = 6;
std::vector<int> code;
std::vector<int> tentative;
std::string indice;
std::vector<std::vector<int>> solutionsProbables;
std::vector<std::vector<int>> combinaisons;
std::vector<std::vector<int>> tentativeSuivantes;


std::vector<int> saisie_code()
{
    for(int i=0 ; i<TAILLE_CODE ; ++i)
    {
        int chiffre;
        std::cin>>chiffre;
        code.push_back(chiffre);
    }
    return code;
}

void genere_combinaisons(std::vector<std::vector<int>>& combinaisons)
{
    const int MIN = 1;
    const int MAX = 6; 
    
    int totalCombi = pow(MAX, TAILLE_CODE);  // Calcul du nombre total de combinaisons
    std::cout<<totalCombi<<std::endl;
    
    for (int i = 0; i < totalCombi; i++) {
        std::vector<int> combi;
        int num = i;
        
        // Parcours des chiffres de la combinaison
        for (int j = MIN; j <= TAILLE_CODE; j++) {
            int digit = num % MAX  + MIN;
            combi.push_back(digit);
            num /= MAX;
        }
        
        combinaisons.push_back(combi);
    }
}

std::string indication(std::vector<int> tentative, std::vector<int> code)
{
    int bon_ordre = 0 , mauvais_ordre = 0;
    // Tableaux de booléens pour éviter de compter plusieurs fois la même couleur
    bool trouve_code[4] = {false};
    bool trouve_tentative[4] = {false};
    
    // Comptage des couleurs dans le bon ordre
    for (int i = 0; i < 4; ++i) {
        if (tentative[i] == code[i]) {
            bon_ordre++;
            trouve_code[i] = true;
            trouve_tentative[i] = true;
        }
    }
    
    // Comptage des couleurs correctes mais mal placées
    for (int i = 0; i < 4; ++i) {
        if (!trouve_tentative[i]) {
            for (int j = 0; j < 4; ++j) {
                if (!trouve_code[j] and tentative[i] == code[j]) {
                    mauvais_ordre++;
                    trouve_code[j] = true;
                    break;
                }
            }
        }
    }
    std::string indice="";
    for(int i=0 ; i<bon_ordre ; ++i)
    {
        indice+="B";
    }
    for(int i=0 ; i<mauvais_ordre ; ++i)
    {
        indice+="W";
    }
    return indice;
}

void supprime_code(std::vector<std::vector<int>> &combinaisons, std::vector<int> tentative)
{
    int index;
    for (auto it = combinaisons.begin(); it != combinaisons.end(); it++) 
    {
        index = std::distance(combinaisons.begin(), it);

        if (combinaisons[index] == tentative) {
            combinaisons.erase(combinaisons.begin() + index);
            break;
        }
    }
}

void triCodes(std::vector<std::vector<int>> &combinaisons, std::vector<int> tentative, std::string indice) 
{

    int index;
    std::vector<std::vector<int>>::iterator it = combinaisons.begin();

    while (it != combinaisons.end()) 
     {
        index = distance(combinaisons.begin(), it);

        if (indice != indication(tentative, combinaisons[index])) 
        {
            it = combinaisons.erase(combinaisons.begin() + index);
        } else 
        {
            it++;
        }
    }
}

int scoreMAX(std::map<std::string, int> inputMap) 
{

    int max = 0;
    for (auto elem : inputMap) {
        if (elem.second > max) {
            max = elem.second;
        }
    }

    return max;
}

int scoreMIN(std::map<std::vector<int>, int> inputMap)

 {

    int min = 1296;
    for (auto elem : inputMap) 
    {
        if (elem.second < min) 
        {
            min = elem.second;
        }
    }

    return min;
}

std::vector<std::vector<int>> minmax() 
{
    std::map<std::string, int> scoreCount;
    std::map<std::vector<int>, int> score;
    std::vector<std::vector<int>> essaiSuivants;
    int max, min;

    for (int i = 0; i < combinaisons.size(); ++i) 
    {

        for (int j = 0; j < solutionsProbables.size(); ++j) // ici on cherche l'indice avec la plus grande occurrence
        {                  // et donc c'est comme si on cherchait l'indice avec le plus de chance d'etre trouvé pour cette tentative

            std::string pegScore = indication(combinaisons[i], solutionsProbables[j]);
            if (scoreCount.count(pegScore) > 0) {
                scoreCount.at(pegScore)++;
            } else {
                scoreCount.emplace(pegScore, 1);
            }
        }

        max = scoreMAX(scoreCount);
        score.emplace(combinaisons[i], max); // ici on garde le score de la combinaison en question, c'est à dire on garde le max 
        scoreCount.clear();
    }

    min = scoreMIN(score);

    for (auto elem : score) {
        if (elem.second == min) {
            essaiSuivants.push_back(elem.first); // ici on va garder toute les combinaisons dont le score min est MIN
        }
    }

    return essaiSuivants;
}

std::vector<int> tentativeSuivante(std::vector<std::vector<int>> tentativeSuivantes) 
{

    std::vector<int> suivant;

    for (int i = 0; i < tentativeSuivantes.size(); ++i) {
        if (find(solutionsProbables.begin(), solutionsProbables.end(), tentativeSuivantes[i]) != solutionsProbables.end()) {
            return tentativeSuivantes[i];
        }
    }
    for (int j = 0; j < tentativeSuivantes.size(); ++j) {
        if (find(combinaisons.begin(), combinaisons.end(), tentativeSuivantes[j]) != combinaisons.end()) {
            return tentativeSuivantes[j];
        }
    }

    return suivant;
}



int main()
{
    int tour = 1;
    bool gagne = false;

    std::cout<<"Saisissez le code : "<<std::endl;
    code=saisie_code();
    tentative = {1, 1, 2, 2}; //1122

    //Création des 1296 combinaisons possibles
    genere_combinaisons(combinaisons);
    solutionsProbables.insert(solutionsProbables.end(), combinaisons.begin(), combinaisons.end());

    std::cout << "Code : ";
    for (int i = 0; i < code.size(); ++i) 
    {
        std::cout << code[i] << " ";
    }
    std::cout << std::endl;
    std::cout << std::endl;

    while (!gagne) 
    {

        //On supprime la tentative des solutions possibles
        supprime_code(combinaisons, tentative);
        supprime_code(solutionsProbables, tentative);

        //On veut obtenir l'indice de la tentative
        indice = indication(tentative, code);

        std::cout << "Tour : " << tour << std::endl;
        std::cout << "Tentative : ";
        for (int i = 0; i < tentative.size(); ++i) {
           std:: cout << tentative[i] << " ";
        }
        std::cout << "= " << indice << std::endl;

        //Si l'indice c'est 4 pions noirs, alors le jeu est fini
        if (indice == "BBBB") {
            gagne = true;
            std::cout << "Game Won!" << std::endl;
            break;
        }

        //On supprime des solutions probables tout code qui ne donnerait pas la meme réponse s'il était le code
        triCodes(solutionsProbables, tentative, indice);

        //On calcule le score minmax
        tentativeSuivantes = minmax();

        //On choisis la tentative suivante
        tentative = tentativeSuivante(tentativeSuivantes);

        tour++;
    }

    return 0;
}