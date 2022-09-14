#include <bits/stdc++.h>

class Regat {
protected:
    std::string nume;
    std::string cultura;
    unsigned long long nr_trupe;
    unsigned long long nr_trupe_initiale;
public:
    explicit Regat(std::string &nume, std::string &cultura, unsigned long long nr_trupe) : nume(nume), cultura(cultura), nr_trupe(nr_trupe) {
        this->nr_trupe_initiale = nr_trupe;
    };

    std::string get_nume() {
        return this->nume;
    }

    std::string get_cultura() {
        return this->cultura;
    }

    unsigned long long get_nr_trupe() {
        return this->nr_trupe;
    }

    unsigned long long get_nr_trupe_initiale() {
        return this->nr_trupe_initiale;
    }

    void add_nr_trupe(unsigned long long new_trupe) {
        this->nr_trupe += new_trupe;
    }

    void sub_nr_trupe(unsigned long long new_trupe) {
        this->nr_trupe -= new_trupe;
        this->nr_trupe = std::max(this->nr_trupe, this->nr_trupe_initiale/2);
    }

    virtual unsigned long long get_nr_trupe_dat()=0;
    virtual unsigned long long get_procent()=0;
    virtual unsigned long long get_nr_min_trupe_dat()=0;
};

class Bizantin : public Regat {
private:
    unsigned long long nr_trupe_dat;
public:
    Bizantin(unsigned long long nr_trupe, std::string &nume, std::string &cultura, unsigned long long nr_trupe_dat) : Regat(nume, cultura, nr_trupe) {
        this->nr_trupe = nr_trupe;
        this->nr_trupe_initiale = nr_trupe;
        this->nume = nume;
        this->cultura = cultura;
        this->nr_trupe_dat = nr_trupe_dat;
    };

    unsigned long long get_nr_trupe_dat() override{
        return this->nr_trupe_dat;
    }

    unsigned long long get_procent() override {
        return 0;
    }

    unsigned long long get_nr_min_trupe_dat() override {
        return 0;
    }
};

class Franc : public Regat {
private:
    unsigned long long procent;
public:
    Franc(unsigned long long nr_trupe, std::string &nume, std::string &cultura, unsigned long long procent) : Regat(nume, cultura, nr_trupe) {
        this->nr_trupe = nr_trupe;
        this->nr_trupe_initiale = nr_trupe;
        this->nume = nume;
        this->cultura = cultura;
        this->procent = procent;
    };

    unsigned long long get_nr_trupe_dat() override {
        return 0;
    }

    unsigned long long get_nr_min_trupe_dat() override {
        return 0;
    }

    unsigned long long get_procent() override {
        return this->procent;
    }
};

class Anglo : public Regat {
private:
    unsigned long long procent;
    unsigned long long nr_min_trupe_dat;
public:
    Anglo(unsigned long long nr_trupe, std::string &nume, std::string &cultura, unsigned long long procent, unsigned long long nr_min_trupe_dat) : Regat(nume, cultura, nr_trupe) {
        this->nr_trupe = nr_trupe;
        this->nr_trupe_initiale = nr_trupe;
        this->nume = nume;
        this->cultura = cultura;
        this->procent = procent;
        this->nr_min_trupe_dat = nr_min_trupe_dat;
    };

    unsigned long long get_nr_trupe_dat() override {
        return 0;
    }

    unsigned long long get_procent() override {
        return this->procent;
    }

    unsigned long long get_nr_min_trupe_dat() override {
        return this->nr_min_trupe_dat;
    }
};

int main() {
    std::vector<Regat*> regate;
    unsigned long long N, M;
    std::cin >> N >> M;
    for(unsigned long long i=0; i<N; i++) {
        std::string nume, cultura;
        unsigned long long nr_trupe;
        std::cin >> nume >> nr_trupe >> cultura;

        if(cultura == "BYZANTINE") {
            unsigned long long nr_trupe_dat;
            std::cin >> nr_trupe_dat;
            Bizantin *biz;
            biz = new Bizantin(nr_trupe, nume, cultura, nr_trupe_dat);
            regate.push_back(biz);
        } else if(cultura == "FRANK") {
            unsigned long long procent;
            std::cin >> procent;
            Franc *fr;
            fr = new Franc(nr_trupe, nume, cultura, procent);
            regate.push_back(fr);
        } else {
            unsigned long long procent, nr_min_trupe_dat;
            std::cin >> procent >> nr_min_trupe_dat;
            Anglo *an;
            an = new Anglo(nr_trupe, nume, cultura, procent, nr_min_trupe_dat);
            regate.push_back(an);
        }
    }

    for(unsigned long long i=0; i<M; i++) {
        std::string vasal, suzeran;
        std::cin >> vasal >> suzeran;
        unsigned long long trupe_dat = 0;
        for(auto &regat : regate) {
            if(regat->get_nume() == vasal) {
                if(regat->get_cultura() == "BYZANTINE") {
                    trupe_dat = regat->get_nr_trupe_dat();
                    if(regat->get_nr_trupe() - trupe_dat < regat->get_nr_trupe_initiale()/2) {
                        trupe_dat = regat->get_nr_trupe()-regat->get_nr_trupe_initiale()/2;
                    }
                    regat->sub_nr_trupe(trupe_dat);
                } else if(regat->get_cultura() == "FRANK") {
                    trupe_dat = regat->get_nr_trupe()*regat->get_procent()/100;
                    if(regat->get_nr_trupe() - trupe_dat < regat->get_nr_trupe_initiale()/2) {
                        trupe_dat = regat->get_nr_trupe()-regat->get_nr_trupe_initiale()/2;
                    }
                    regat->sub_nr_trupe(trupe_dat);
                } else {
                    trupe_dat = std::max(regat->get_nr_min_trupe_dat(), (regat->get_nr_trupe()*regat->get_procent()/100));
                    if(regat->get_nr_trupe() - trupe_dat < regat->get_nr_trupe_initiale()/2) {
                        trupe_dat = regat->get_nr_trupe()-regat->get_nr_trupe_initiale()/2;
                    }
                    regat->sub_nr_trupe(trupe_dat);
                }
            }
        }

        for(auto &regat : regate) {
            if(regat->get_nume() == suzeran) {
                regat->add_nr_trupe(trupe_dat);
            }
        }
    }

    for(auto &regat : regate) {
        std::cout << regat->get_nume() << " " << regat->get_nr_trupe() << "\n";
    }
    return 0;
}
