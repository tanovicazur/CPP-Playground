#include "Studenti.hpp"

void crtice(){
    std::cout << std::string(93,'-') << std::endl;
}

bool predmetPostoji(const std::unordered_map<std::string, std::string>& predmeti, const std::string& nazivPredmeta){
    if(predmeti.find(nazivPredmeta) == predmeti.end())
        return false;
    else
        return true;
}

bool indexPostoji(const std::unordered_map<std::string, Student>& indexi, const std::string& index){
    if(indexi.find(index) == indexi.end())
        return false;
    else
        return true;
}

int main(int argc, char const *argv[])
{
    std::unordered_map<std::string, std::string> predmeti; //i key i value je naziv predmeta
    std::unordered_map<std::string, std::vector<Ispit>> IspitiDatum; //key je datum
    std::unordered_map<std::string, std::vector<Student>> studentiDatum; //key je datum
    std::unordered_map<std::string, Student> indexStudent; //key je index studenta
    std::cout << "1.\tDodaj novog studenta" << std::endl;
    std::cout << "2.\tDodaj novi ispit" << std::endl;
    std::cout << "3.\tDodaj novi predmet" << std::endl;
    std::cout << "4.\tDodaj novi rezultat ispita" << std::endl;
    std::cout << "5.\tDohvati sve ispite za odredjeni datum" << std::endl;
    std::cout << "6.\tDohvati po datumu i imenu, sve studente koji su polozili odredjeni ispit" << std::endl;
    std::cout << "7.\tDohvati po indeksu sve ispite koje je polozio student hronoloski, te prosjecnu ocjenu" << std::endl;
    crtice();
    int odabir;
    std::cout << "Izbor: ";
    while(std::cin >> odabir){
        switch(odabir){
            case 1 : {
                std::string ime;
                std::string prezime;
                std::string index;
                std::cout << "Ime: ";
                std::cin >> ime;
                std::cout << "Prezime: ";
                std::cin >> prezime;
                std::cout << "Index: ";
                std::cin >> index;
                if(indexPostoji(indexStudent, index)){
                    std::cout << "Student sa istim indexom vec postoji!" << std::endl;
                    crtice();
                    break;
                }
                Student student(index, ime, prezime);
                indexStudent.emplace(index, student);
                crtice();
                break;
            }

            case 2 : {
                std::string datum;
                std::string predmet;
                std::cout << "Datum ispita: ";
                std::cin >> datum;
                std::cout << "Predmet: ";
                std::cin >> predmet;
                if(!predmetPostoji(predmeti, predmet)){
                    std::cout << "Predmet koji ste unijeli ne postoji!" << std::endl;
                    crtice();
                    break;
                }
                Ispit ispit(datum, predmet);
                if(IspitiDatum.find(datum) == IspitiDatum.end()){
                    IspitiDatum.emplace(datum, std::vector<Ispit>{});
                } else {
                    for(int i = 0; i < IspitiDatum[datum].size(); i++){
                        if(IspitiDatum[datum].at(i).getPredmet() == predmet)
                            std::cout << "Iz jednog predmeta je moguce imati samo jedan ispit u jednom danu!" << std::endl;
                            break;
                    };
                }
                IspitiDatum[datum].push_back(ispit);
                crtice();
                break;
            }

            case 3: {
                std::string nazivPredmeta;
                std::cout << "Predmet: ";
                std::cin >> nazivPredmeta;
                if(!predmetPostoji(predmeti, nazivPredmeta))
                    predmeti.emplace(nazivPredmeta, nazivPredmeta);
                else
                    std::cout << "Taj predmet je vec unesen!" << std::endl;
                crtice();
                break;
            }

            case 4: {
                std::string index;
                short int ocjena = 0;
                std::string datum;
                std::string nazivPredmeta;
                std::cout << "Index: ";
                std::cin >> index;
                if(!indexPostoji(indexStudent, index)){
                    std::cout << "Ne postoji student sa ovim indexom!" << std::endl;
                    break;
                }
                while(ocjena < 6 || ocjena > 10){
                    std::cout << "Ocjena: ";
                    std::cin >> ocjena;
                    if(ocjena < 6 || ocjena > 10)
                        std::cout << "Ponovo unesite ocjenu!" << std::endl;
                }         
                std::cout << "Datum: ";
                std::cin >> datum;
                std::cout << "Predmet: ";
                std::cin >> nazivPredmeta;
                if(predmetPostoji(predmeti, nazivPredmeta)){
                    indexStudent[index].dodajIspit(datum, nazivPredmeta);
                    indexStudent[index].dodajOcjenu(ocjena);
                    indexStudent[index].setOcjenaSum(ocjena);
                    Student student = indexStudent[index];
                    Ispit ispit(datum, nazivPredmeta);
                    studentiDatum[datum+nazivPredmeta].push_back(student);
                } else {
                    std::cout << "Predmet koji ste unijeli ne postoji." << std::endl;
                }
                crtice();
                break;
            }

            case 5: {
                std::string datum;
                std::cout << "Datum: ";
                std::cin >> datum;
                for(int i = 0; i < IspitiDatum[datum].size(); i++){
                    std::cout << IspitiDatum[datum].at(i).getPredmet() << std::endl;
                };
                break;
            }

            case 6: {
                std::string datum;
                std::string predmet;
                std::cout << "Datum: ";
                std::cin >> datum;
                std::cout << "Predmet: ";
                std::cin >> predmet;
                crtice();
                if(!predmetPostoji(predmeti, predmet)){
                    std::cout << "Ne postoji uneseni predmet!" << std::endl;
                    break;
                }
                for(int i = 0; i < studentiDatum[datum+predmet].size(); i++){
                    std::cout << studentiDatum[datum+predmet].at(i) << std::endl;
                };
                crtice();
                break;
            }

            case 7: {
                std::string index;
                std::cin >> index;
                for(int i = 0; i < indexStudent[index].getIspiti().size(); i++){
                    std::cout << indexStudent[index].getIspiti().at(i) << std::endl;
                }
                std::cout << std::endl;
                std::cout << indexStudent[index].getOcjenaSum()/indexStudent[index].getOcjene().size() << std::endl;
                crtice();
                break;
            }

            default: {
                std::cout << "Nevalidan unos. Pokusaj ponovo!" << std::endl;
                crtice();
                break;
            }
        }
        std::cout << "1.\tDodaj novog studenta" << std::endl;
        std::cout << "2.\tDodaj novi ispit" << std::endl;
        std::cout << "3.\tDodaj novi predmet" << std::endl;
        std::cout << "4.\tDodaj novi rezultat ispita" << std::endl;
        std::cout << "5.\tDohvati sve ispite za odredjeni datum" << std::endl;
        std::cout << "6.\tDohvati po datumu i imenu, sve studente koji su polozili odredjeni ispit" << std::endl;
        std::cout << "7.\tDohvati po indeksu sve ispite koje je polozio student hronoloski, te prosjecnu ocjenu" << std::endl;
        crtice();
        std::cout << "Izbor: ";

    };
    return 0;
}
