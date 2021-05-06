#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stack>
using namespace std;;


struct Tranzitie{
    int destinatie;
    char litera;
};

struct Element{
    int start;
    int indice;
};

ifstream f ("date.in");
ofstream g ("date.out");

string NFA(int S, vector<int> stari, vector <vector<Tranzitie>> lista_adiacenta, vector <int> stari_fin,string cuv){
        stack <Element> stiva;
        int stare_cur = S;
        int nr_litera = 0;
        Element e;
        e.start  = stare_cur;
        e.indice = nr_litera;
        stiva.push(e);
        Element x;
        // cat timp stiva nu este goala
        while (stiva.empty() != true){
            // iau elementul din capul stivei
            x = stiva.top();
            // il elimin
            stiva.pop();
            //aflu pozitia starii de start in vectorul stari
            int l;
            for (int j = 0; j < stari.size(); j++){
                if (x.start == stari[j])
                    l = j;
            }
            // parcurg vecinii starii curente
            for (int k = 0; k < lista_adiacenta[l].size(); k++){
                // daca litera curenta se afla in lista de vecini ai starii
                if (lista_adiacenta[l][k].litera == cuv[x.indice]){
                    // daca am ajuns la sfarsitul cuvantului
                    if (x.indice == cuv.size()-1){
                        // daca starea in care am ajuns la sfarsitul cuvantului este finala
                        for (int j = 0; j < stari_fin.size(); j++)
                            if (lista_adiacenta[l][k].destinatie == stari_fin[j])
                                { 
                                    return "DA";
                                    }
                    }
                    else{
                        // daca nu am ajuns la sfarsitul cuvantului adaug in stiva vecinii starii
                        for (int j = 0; j < lista_adiacenta[l].size(); j++){
                            Element e;
                            e.start = lista_adiacenta[l][j].destinatie;
                            e.indice = x.indice + 1;
                            // daca litera vecinului == litera din cuvant care urmeaza
                            if (lista_adiacenta[l][j].litera == cuv[x.indice]){
                                stiva.push(e);
                            }
                        }
                    }
                }
            }
        }
    return "NU";
}


int main(){
    int nr_stari,
        nr_tranzitii;
    vector <int> stari;
    vector <int> tranzitii;
    f>>nr_stari;
    int stare;
    for (int i = 0; i < nr_stari; i++){
        f >> stare;
        stari.push_back(stare);
        }
    f >> nr_tranzitii;
    vector <vector<Tranzitie>> lista_adiacenta(nr_stari,vector<Tranzitie>());
    for (int i = 0; i < nr_tranzitii; i++){
        f >> stare;
        //cout << stare << endl;
        Tranzitie t;
        f >> t.destinatie;
        //cout << t.destinatie << endl;
        f >> t.litera;
        //cout << t.litera << endl;
        for (int j = 0; j < nr_stari; j++){
            if (stari[j] == stare)
                stare = j;
        }
        lista_adiacenta[stare].push_back(t);
    }


    int S; // starea initiala
    f >> S;
    int nrF; // stari finale
    f >> nrF;
    vector <int> stari_fin;
    int sf;
    for (int i = 0; i < nrF; i++){
        f >> sf;
        stari_fin.push_back(sf);
    }
    int nr_cuv;
    f >> nr_cuv;
    string cuv;
    Element x;
    for (int i = 0 ; i < nr_cuv; i++){
        f >> cuv;
        g << NFA(S,stari,lista_adiacenta, stari_fin,cuv) << endl;
    }

    return 0;
}
