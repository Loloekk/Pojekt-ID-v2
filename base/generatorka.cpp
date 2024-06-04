#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double db;
typedef pair<int,int> pii;
typedef vector<int> vi;
#define pb push_back
#define fi first
#define se second
#define rep(i,b,e) for(int i=(b); i<(e); i++)
#define each(a,x)  for(auto &a : (x))
#define all(x) (x).begin(), (x).end()
#define sz(x)  (ll)(x).size()

const int DNI_SYMULACJI = 60;
const int PACZEK_DZIENNIE = 200;
const int ILE_POJAZDOW_NA_MAGAZYN = 20;
const int ILE_KIEROWCOW_NA_MAGAZYN = 10;
const int ILE_KOMISJONEROW_NA_MAGAZYN = 5;
const int ILE_INFORMATYKOW_NA_MAGAZYN = 2;
const int ILE_KLIENTOW = 30000;
const int NIEODEBRANYCH_PACZEK = 40;

const int SEKUNDA = 1;
const int MINUTA = 60;
const int GODZINA = MINUTA*60;
const int DZIEN = GODZINA*24;

auto rd = std::random_device {}; 
auto random_eng = std::default_random_engine { rd() };

template <class T>
void mieszaj(vector<T> &v){
    shuffle(v.begin(),v.end(),random_eng);
}

auto T = time(0);
auto TM = *localtime(&T);

string obecna_data(int add=0){
    ostringstream stream;
    T += add;
    TM = *localtime(&T);
    stream << put_time(&TM, "%Y-%m-%d %H:%M:%S");
    T -= add;
    TM = *localtime(&T);
    auto str = stream.str();
    return str;
}

void dodajSekund(int s){
    T += s;
    TM = *localtime(&T);
}

void ustawCzas(int s){
    T = s;
    TM = *localtime(&T);
}

map<string,int> lokalizacjaMagazyn;
map<int,string> magazynLokalizacja;
map<string,int> miastoMagazyn;
map<int,int> nadmagazyn;
map<int,int> komisjonerMagazyn;
map<int,int> informatykMagazyn;
map<int,int> klientPaczkomat;
map<int,int> pojazdMagazyn; // aktualne polozenie pojazdu
map<int,int> kierowcaMagazyn; // aktualne polozenie kierowcy
map<int,set<int>> pojazdZlecenia; // aktualne zlecenia w pojezdzie 
map<int,set<int>> paczkomatZlecenia; // oczekujace paczki do zabrania przez kierowcow w paczkomacie
map<int,set<int>> magazynZlecenia; // aktualne paczki w magazynie
map<int,int> paczkomatMagazyn;

// Na ten moment zakladamy ze w danym miescie jest maksymalnie jeden magazyn
void dodajMagazyn(const string &miasto, const string &nadmiasto);
void dodajPaczkomat(const string &miasto, const int &ilosc);
void dodajPaczkomat(const string &miasto);
int wolnaSkrytka(const int &paczkomat, const int &rozmiar);
int wolneMiejsce(const int &pojazd);
int paczkaRozmiar(const int &zlecenie);
int potrzebneUprawnienie(const int &pojazd_rodzaj);
int magazyn_startowy(const int &zlecenie);
int magazyn_docelowy(const int &zlecenie);
// Krotki w tabelach;
// Dla int'ów -1 oznacza zazwyczaj wartość NULL 
struct osoba{
    int id;
    string pesel;
    string imie;
    string nazwisko;
    string email;
    string nr_tel;
};

struct stanowisko{
    int id_stanowiska;
    string nazwa;
};

struct stanowisko_osoba{
    int id_osoby;
    int id_stanowiska;
};

struct osoba_uprawnienie{
    int id_osoby;
    int id_uprawnienia;
};

struct uprawnienie{
    int id_uprawnienia;
    string nazwa;
};

struct pojazd{
    int id_pojazdu;
    string nr_rejestracji;
    int id_rodzaju;
};

struct usterka{
    int id_pojazdu;
    string opis;
    string data_wystapienia;
    string data_rozpoczecia_naprawy;
    string data_zakonczenia_naprawy;
};

struct rodzaj_pojazdu{
    int id_rodzaju;
    string nazwa;
    int pojemnosc; // wyrazona w paczkach rozmiaru 1 (1 paczka ~= 20 litrów)
    int id_uprawnienia;
};

struct przeglady_rodzaje_pojazdy{
    int id_rodzaju;
    int id_przegladu;
    int czestotliwosc; // wyrazona w miesiacach
};

struct serwis{
    int id_pojazdu;
    int id_przegladu;
    string data_rozpoczecia;
    string data_zakonczenia;
};

struct rodzaje_przegladow{
    int id_przegladu;
    string nazwa;
};

struct kurs{
    int id_kursu;
    int id_pojazdu;
    int id_kierowcy;
    int magazyn_start;
    int magazyn_docelowy;
    string data_wyjazdu;
    string data_przyjazdu;
};

struct kurs_paczkomat{
    int id_kursu;
    int id_paczkomatu;
    string data_przyjazdu;
    string data_odjazdu;
};

struct zlecenie_kurs{
    int id_zlecenia;
    int id_kursu;
    string data;
};

struct zlecenie{
    int id_zlecenia;
    int id_nadawcy;
    int id_odbiorcy;
    int id_pacz_odb;
    string data_zlozenia;
    int rozmiar; // 1: 20 litrów, 2: 40 litrów, 3: 80 litrów
};

struct nadanie{
    int id_zlecenia;
    int id_skrytki;
    string data;
};

struct odbior{
    int id_zlecenia;
    int id_skrytki;
    string data_dostarczenia;
    string data_odebrania;
};

struct zlecenie_magazyn{
    int id_zlecenia;
    int id_magazynu;
    string data;  
};

struct praca_osoba{
    int id_osoby;
    int id_magazynu;
    int id_stanowiska;
    string data_rozpoczecia;
    string data_zakonczenia;  
};

struct magazyn{
    int id_magazynu;
    string lokalizacja;
};

struct paczkomat{
    int id_paczkomatu;
    string lokalizacja;
    int magazyn;
};

struct skrytka{
    int id_skrytki;
    int id_paczkomatu;
    int rozmiar;
};

struct deklaracja_wypakowania{
    int id_kursu;
    string data;
};

int NEXT_OSOBA_ID=1;
int NEXT_RODZAJ_POJAZDU_ID=1;
int NEXT_POJAZD_ID=1;
int NEXT_KURS_ID=1;
int NEXT_MAGAZYN_ID=1;
int NEXT_PACZKOMAT_ID=1;
int NEXT_SKRYTKA_ID=1;
int NEXT_ZLECENIE_ID=1;

mt19937 mt(124);
int rnd(int a, int b){
    return mt()%(b-a+1)+a;
}

vector<string> ulice = {
    "Bajeczna","Piastowska","Kamienna","Cicha","Krajowa","Dolna","Czerwona","Mickiewicza","Brodzikowa","Praska",
    "Warna","Wokulskiego","Kmicica","Sienkiewicza","Kiemlicza","Ketlinga","Trawiasta","Mokra","Sucha","Szeroka",
    "Wiejska","Chwalebna","Jerozolimska","Krakowska","Narutowicza","Lwowska","Walna","Bema","Matejki","Mostowa",
    "Jeziorna","Walentego","Konopnickiej","Bernardyna","Elektryczna","Azotowa","Sowia",
};
vector<string> imiona = {
"Jan","Marian","Kazimierz","Barnaba","Piotr","Maciej","Kacper","Krystian","Cezary","Krystian","Tomasz","Marek",
"Kamil","Bogdan","Teofil","Grzegorz","Romuald","Filip","Krzysztof","Gabriel","Wincenty","Wojciech","Arkadiusz",
"Maria","Anna","Kamila","Hiacynt","Agata","Zofia","Zuzanna","Laura","Hanna","Oliwa","Julia","Balbina",
"Jadwiga","Izabela","Aleksandra","Wiktoria","Wanda","Alicja","Zuzanna","Ewa","Magdalena","Natalia","Dorota",
};
vector<string> nazwiska = {
  "Nowak","Kowal","Steiner","Poziomka","Wojtar","Kowalczyk","Boryna","Zimno","Buk","Szulc",
  "Mazurek","Lis","Kot","Mak","Odra","Duda","Niemen","Mickiewicz","Miazga","Wilk","Pawlak",
  "Szewczyk","Kaczmarek","Kareta","Krawczyk","Sikora","Rudzik","Dudek","Kos","Koza","Czech",
  "Potok","Mazur","Wieczorek","Czwartek","Maj","Stelarz","Wiorsta",
};
vector<string> przymiotnik = {
    "ekstra","mega","czerwony","zielony","czarny","ultra","super","niebieski","limonkowy","dzielny","dumny",
    "nieustraszliwy","waleczny","wielki","fioletowy","kwadratowy","nieprzeliczalny","the","trafny","smaczny",
    "radosny","cichy","luzacki","maly","smieszny","pomocny","pomocna","wielka","cicha","radosna","nieustraszliwa",
    "smaczna","dumna","dzielna","limonkowa","zielona","czarna","srebrny","srebrna","trafna","kwadratowa","czerwona",
    "wilczy","przestraszony","boczny","dolny","dolna","metalowy","liniowy","liniowa","misiowy","obszerny","wysoki",
    "wysoka","niski","niska","plaski","bezprzewodowy","bezprzewodowa","kablowy","kablowa","jasna","jasny","ciemny",
    "ciemna"
};
vector<string> rzecz = {
    "heban","rock","trawa","herb","tarcza","kura","osa","kula","kwadrat","mysz","lis","klej","kostka","chleb",
    "owoc","warzywo","bohater","batman","kosz","smok","pluszak","mur","poeta","giermek","rycerz","hrabia","stefan",
    "smerf","banan","toster","parasol","drewno","drzewo","spray","talerz","widelec","linijka","drut","matryca",
    "kartka","karton","astronauta","problem","moneta","muzyka","papier","puszka","drzwi","sikorka","kos","orzel",
    "reszka","okno","skarpeta","lampka","kawa","herbata","yeti","stopa","metal","plastik","lustro","srebro","byk",
    "cielak","wilk","bok","linia","trawa","mak","mech","rak","dudek","liliput","oryks","antylopa","papuga","klops",
    "wiewiorka","jajko","dolar","rubel","funt","kilogram","waga","masa","kula","sfera","koszyk","stal","misiek"
};
vector<string> domena = {
    "gmail.com","onet.pl","o2.pl","interia.pl","wp.pl",
};
vector<string> prefiksyRejestracje = {
"BI", "BS", "BL", "BAU", "BIA", "BBI", "BGR", "BHA", "BKL", "BMN", "BSE", "BSI", "BSK", "BSU", "BWM", "BZA", "BLM", "CB", "CG", "CT", "CW", "CAL", "CBR", "CBY", "CCH", "CGD", "CGR", "CIN", "CLI", "CMG", "CNA", "CRA", "CRY", "CSE", "CSW", "CTR", "CTU", "CWA", "CWL", "CZN", "DJ", 
"DL", "DB", "DW", "DBL", "DDZ", "DGR", "DGL", "DJA", "DJE", "DKA", "DKL", "DLE", "DLB", "DLU", "DLW", "DMI", "DOL", "DOA", "DPL", "DSR", "DST", "DSW", "DTR", "DBA", "DWL", "DWR", "DZA", "DZG", "DZL", "EP", "ES", "EL", "EBE", "EBR", "EKU", "EOP", "EPA", "EPJ", "EPI", "EPD", 
"ERA", "ERW", "ESI", "ESK", "ETM", "EWI", "EWE", "EZD", "EZG", "ELA", "ELE", "ELW", "ELC", "FG", "FZ", "FGW", "FKR", "FMI", "FNW", "FSD", "FSU", "FSW", "FSL", "FWS", "FZG", "FZA", "FZI", "GD", "GA", "GSP", "GS", "GBY", "GCH", "GCZ", "GDA", "GKA", "GKS", "GKW", "GLE", "GMB", 
"GND", "GPU", "GST", "GSZ", "GSL", "GTC", "GWE", "GWO", "KR", "KK", "KN", "KT", "KBC", "KBA", "KBR", "KCH", "KDA", "KGR", "KRA", "KLI", "KMI", "KMY", "KNS", "KNT", "KOL", "KOS", "KPR", "KSU", "KTA", "KTT", "KWA", "KWI", "LB", "LC", "LU", "LZ", "LBI", "LBL", "LCH", "LHR", 
"LJA", "LKR", "LKS", "LLB", "LUB", "LOP", "LPA", "LPU", "LRA", "LRY", "LSW", "LTM", "LWL", "LZA", "LLE", "LLU", "NE", "NO", "NBA", "NBR", "NDZ", "NEB", "NEL", "NGI", "NGO", "NIL", "NKE", "NLI", "NMR", "NNI", "NNM", "NOE", "NOL", "NOS", "NPI", "NSZ", "NWE", "OP", "OB", "OGL", 
"OK", "OKL", "OKR", "ONA", "ONY", "OOL", "OPO", "OPR", "OST", "PK", "PN", "PL", "PO", "PY", "PCH", "PCT", "PGN", "PGS", "PGO", "PJA", "PKA", "PKE", "PKL", "PKN", "PKS", "PKR", "PLE", "PMI", "PNT", "POB", "POS", "POT", "PP", "PPL", "PZ", "PRA", "PSR", "PSE", "PSZ", "PSL", 
"PTU", "PWA", "PWL", "PWR", "PZL", "RK", "RP", "RZ", "RT", "RBI", "RBR", "RDE", "RJA", "RJS", "RKL", "RKR", "RLS", "RLE", "RLU", "RMI", "RNI", "RPR", "RPZ", "RRS", "RZE", "RSA", "RST", "RSR", "RTA", "RLA", "SB", "SY", "SH", "SC", "SD", "SG", "SJZ", "SJ", "SK", "SM", 
"SPI", "SL", "SR", "SI", "SO", "SW", "ST", "SZ", "SZO", "SBE", "SBI", "SBL", "SCI", "SCZ", "SGL", "SKL", "SLU", "SMI", "SMY", "SPS", "SRC", "SRB", "STA", "SWD", "SWZ", "SZA", "SZY", "TK", "TBU", "TJE", "TKA", "TKI", "TKN", "TOP", "TOS", "TPI", "TSA", "TSK", "TST", "TSZ", 
"TLW", "WO", "WP", "WR", "WS", "WB", "WA", "WD", "WE", "WU", "WH", "WF", "WW", "WI", "WJ", "WK", "WN", "WT", "WX", "WY", "WBR", "WCI", "WG", "WGS", "WGM", "WGR", "WKZ", "WL", "WLI", "WMA", "WM", "WML", "WND", "WOR", "WOS", "WOT", "WPI", "WPR", "WPP", "WPS", 
"WPZ", "WPY", "WPU", "WPL", "WPN", "WRA", "WSI", "WSE", "WSC", "WSK", "WSZ", "WZ", "WWE", "WWL", "WV", "WWY", "WZU", "WZW", "WZY", "WLS", "ZK", "ZSW", "ZS", "ZZ", "ZBI", "ZCH", "ZDR", "ZGL", "ZGY", "ZGR", "ZKA", "ZKO", "ZKL", "ZMY", "ZPL", "ZPY", "ZST", "ZSD", "ZSZ", "ZSL", 
"ZWA", "ZLO", 
};

string to_string(const osoba&);
string to_string(const pojazd&);
string to_string(const rodzaj_pojazdu&);
string to_string(const magazyn&);
string to_string(const paczkomat&);
string to_string(const uprawnienie&);
string to_string(const stanowisko&);
string to_string(const osoba_uprawnienie&);
string to_string(const stanowisko_osoba&);
string to_string(const usterka&);
string to_string(const serwis&);
string to_string(const przeglady_rodzaje_pojazdy&);
string to_string(const rodzaje_przegladow&);
string to_string(const kurs&);
string to_string(const kurs_paczkomat&);
string to_string(const zlecenie_kurs&);
string to_string(const zlecenie_magazyn&);
string to_string(const zlecenie&);
string to_string(const odbior&);
string to_string(const nadanie&);
string to_string(const praca_osoba&);
string to_string(const skrytka&);

osoba genOsoba();
pojazd genPojazd();
string genLokalizacja(const string &miasto);
bool czyKobieta(const osoba &os);
vector<string> tokenize(string, char);
void printEverything();
void odbierzPaczke(const int &zlecenie, const string &data_dostarczenia, const string &data_odbioru);
pair<pojazd,osoba> dajPojazdKierowca(const int &magazynId, const vector<bool>&, const vector<bool>&);
bool mozeProwadzic(const int &osobaId, const int &pojazdId);
int rodzajPojazdu(const int &pojazdId);
osoba idToOsoba(const int &osobaId);
pojazd idToPojazd(const int &pojazdId);
vector<pair<int,int>> wyznaczTrasy(); // Zwraca zbiór par {A,B} takich, że pasuje wykonać kurs z magazynu A do magazynu B
string dataNadania(const int &zlecenie);
bool czySkrytkaWolna(const int &skrytka);


vector<osoba> OSOBY;
vector<stanowisko_osoba> STANOWISKA_OSOBY;
vector<osoba_uprawnienie> OSOBY_UPRAWNIENIA;
vector<usterka> USTERKI;
vector<pojazd> POJAZDY;
vector<serwis> SERWIS;
vector<przeglady_rodzaje_pojazdy> PRZEGLADY_ROD_POJAZDY;
vector<kurs> KURSY;
vector<kurs_paczkomat> KURSY_PACZKOMATY;
vector<zlecenie_kurs> ZLECENIA_KURSY;
vector<zlecenie> ZLECENIA;
vector<zlecenie_magazyn> ZLECENIA_MAGAZYNY;
vector<odbior> ODBIORY;
vector<nadanie> NADANIA;
vector<praca_osoba> PRACA_OSOBY;
vector<skrytka> SKRYTKI;
vector<deklaracja_wypakowania> DEKLARACJA_WYPAKOWAN;
vector<rodzaj_pojazdu> RODZAJE_POJAZDOW = {
    {1,"Ford Transit", 750, 1},
    {2,"Mercedes Sprinter", 775, 1},
    {3,"Volkswagen Crafter", 900, 1},
    {4,"Tir XXL", 4500, 4},
    {5,"Tir XL", 3000, 4},
};
vector<stanowisko> STANOWISKA = {
    {1,"dyrektor"},{2,"kierowca"},{3,"komisjoner"},{4,"informatyk"},
};
vector<uprawnienie> UPRAWNIENIA = {
    {1,"C"},{2,"C1"},{3,"C1E"},{4,"CE"},
};
vector<rodzaje_przegladow> RODZAJE_PRZEGLADOW = {
    {1,"Wymiana oleju"},
    {2,"Wymiana plynu hamulcowego"},
    {3,"Wymiana plynu do spryskiwaczy"},
    {4,"Wymiana plynu chlodniczego"},
    {5,"Wymiana tarczy hamulcowych"},
    {6,"Wymiana opon"},
};
vector<magazyn> MAGAZYNY;
vector<paczkomat> PACZKOMATY;

vector<int> komisjonerzy; // {osobaId,magazynId}; pracuja kazdy w swoim magazynie od rana do wieczora 
vector<int> informatycy; // {osobaId}; pracuja losowym magazynie od rana do wieczora 
vector<int> klienci; // {osobaId,paczkomatId}; nadaje paczki ze swojego paczkomatu 
vector<int> dyrektorzy; // {osobaId}; "pracuje" w losowym magazynie
vector<int> kierowcy; // {osobaId}; jezdza w losowe miejsca

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ustawCzas((-1)*3600 + 24*3600*54*365 + 24*3600*107 - 3600); // 2024-01-01 00:00:00
    OSOBY.pb({NEXT_OSOBA_ID++,"0","N","N","-","-"});
    const osoba NN = OSOBY.back();

    // Magazyny
    dodajMagazyn("Warszawa","-");
    dodajMagazyn("Krakow","-");
    dodajMagazyn("Poznan","-");
    dodajMagazyn("Piaseczno","Warszawa");
    dodajMagazyn("Radom","Warszawa");
    dodajMagazyn("Siedlce","Warszawa");
    dodajMagazyn("Tarnow","Krakow");
    dodajMagazyn("Katowice","Krakow");
    dodajMagazyn("Gniezno","Poznan");
    dodajMagazyn("Pila","Poznań");
    dodajMagazyn("Leszno","Poznan");
    dodajMagazyn("Nowy Sacz","Krakow");
    // Paczkomaty
    dodajPaczkomat("Warszawa",20);
    dodajPaczkomat("Krakow",20);
    dodajPaczkomat("Poznan",15);
    dodajPaczkomat("Radom",9);
    dodajPaczkomat("Siedlce",10);
    dodajPaczkomat("Piaseczno",10);
    dodajPaczkomat("Tarnow",10);
    dodajPaczkomat("Katowice",10);
    dodajPaczkomat("Nowy Sacz",10);
    dodajPaczkomat("Gniezno",10);
    dodajPaczkomat("Pila",10);
    dodajPaczkomat("Leszno",5);
    assert(MAGAZYNY.size()%2==0 && "Ilosc paczkomatow ma byc parzysta (na potrzeby generowania danych)");

    // Rodzaje przegladow
    
    // PrzegladyRodzajePojazdow
    for(int i=0; i<int(RODZAJE_PRZEGLADOW.size()); ++i){
        for(int j=0; j<int(RODZAJE_POJAZDOW.size()); ++j){
            int czestotliwosc = rnd(2,24);
            PRZEGLADY_ROD_POJAZDY.pb({j+1,i+1,czestotliwosc});
        }
    }
    // Rodzaje pojazdow

    // Stanowiska
    // Uprawnienia
    /// Klienci zwykli (bez stanowisk)
    rep(i,0,ILE_KLIENTOW){
        osoba klient = genOsoba();
        int paczkomatId = rnd(1,PACZKOMATY.size());
        OSOBY.pb(klient);
        klienci.pb(klient.id);
        klientPaczkomat[klient.id] = paczkomatId;
    }
    /// Dyrektor
    {
        osoba dyr = genOsoba();
        OSOBY.pb(dyr);
        STANOWISKA_OSOBY.pb({dyr.id,1});
        dyrektorzy.pb(dyr.id);
    }

    // Kierowcy
    each(m,MAGAZYNY){
        int magId = m.id_magazynu;
        int ile = ILE_KIEROWCOW_NA_MAGAZYN + rnd(0,1);
        rep(k,0,ile){
            osoba kier = genOsoba();
            OSOBY.pb(kier);
            STANOWISKA_OSOBY.pb({kier.id,2});
            kierowcaMagazyn[kier.id] = magId;
            kierowcy.pb(kier.id);
            int ile_prob = rnd(2,4);
            vector<bool> upr(sz(UPRAWNIENIA)+1);
            rep(i,0,ile_prob){
                upr[rnd(1,sz(UPRAWNIENIA))] = 1;
            }
            for(int u=1; u<=sz(UPRAWNIENIA); ++u){
                if(upr[u]){
                    OSOBY_UPRAWNIENIA.pb({kier.id,u});
                }
            }            
        }
    }

    /// Pojazdy
    each(m,MAGAZYNY){
        int magId = m.id_magazynu;
        int ile = ILE_POJAZDOW_NA_MAGAZYN + rnd(0,2);
        rep(p,0,ile){
            pojazd poj = genPojazd();
            POJAZDY.pb(poj);
            /// kurs pojazdu "p" z "magId" do "magId", aby zaznaczyc mu pozycje startowa
            KURSY.pb({NEXT_KURS_ID++, poj.id_pojazdu, NN.id, magId, magId, obecna_data(), obecna_data()});            
            pojazdMagazyn[poj.id_pojazdu] = magId;
            // Wirtualnie serwisujemy nowo otrzymany pojazd (świeżo z fabryki)
            for(auto &[id_rodzaju,id_przegladu,czestotliwosc] : PRZEGLADY_ROD_POJAZDY){
                if(id_rodzaju == poj.id_rodzaju){
                    SERWIS.pb({poj.id_pojazdu, id_przegladu, obecna_data(-24*GODZINA), obecna_data(-24*GODZINA+MINUTA)});
                }
            }
        }
    }
    /// Komisjonerzy
    each(m,MAGAZYNY){
        int magId = m.id_magazynu;
        int ile = ILE_KOMISJONEROW_NA_MAGAZYN + rnd(0,2);
        rep(k,0,ile){
            osoba kom = genOsoba();
            OSOBY.pb(kom);
            STANOWISKA_OSOBY.pb({kom.id,3});
            komisjonerzy.pb(kom.id);
            komisjonerMagazyn[kom.id] = magId;
        }
    }
    // Informatyków
    each(m,MAGAZYNY){
        int magId = m.id_magazynu;
        int ile = ILE_INFORMATYKOW_NA_MAGAZYN + rnd(0,1);
        rep(k,0,ile){
            osoba inf = genOsoba();
            OSOBY.pb(inf);
            STANOWISKA_OSOBY.pb({inf.id,4});
            informatycy.pb(inf.id);
            informatykMagazyn[inf.id] = magId;
        }
    }
    for(int d=0; d<DNI_SYMULACJI; ++d){
        cerr << '.' << flush;
        // cerr << "GENEROWANIE DNIA " << d << "." << endl;
        ll czasDzien = 0;
        // godzina 0:00:00
        czasDzien = 7*GODZINA;
        // godzina 7:00:00
        // Komisjonerzy i dyrektor zaczynaja prace i pracuja 12 godzin
        for(auto komId : komisjonerzy){
            int magId = komisjonerMagazyn[komId];
            if(rnd(1,20) == 1) continue; // 5% szans, że nie przyjdzie do pracy
            string dataRozpoczecia = obecna_data(czasDzien + rnd(-10*MINUTA,10*MINUTA));
            string dataZakonczenia = obecna_data(czasDzien + 12*GODZINA + rnd(-5*MINUTA,10*MINUTA));
            PRACA_OSOBY.pb({komId, magId, 3, dataRozpoczecia, dataZakonczenia });
        }
        for(auto dyrId : dyrektorzy){
            int magId = rnd(1,MAGAZYNY.size());
            if(rnd(1,50) == 1) continue; // 2% szans, że nie przyjdzie do pracy
            string dataRozpoczecia = obecna_data(czasDzien + rnd(-10*MINUTA,10*MINUTA));
            string dataZakonczenia = obecna_data(czasDzien + 12*GODZINA + rnd(2*MINUTA,10*MINUTA));
            PRACA_OSOBY.pb({dyrId, magId, 1, dataRozpoczecia, dataZakonczenia});
        }
        // Informatycy zaczynaja prace od 10 (+/- 2h) do 18 (+/- 2h)
        for(auto infId : informatycy){
            int magId = informatykMagazyn[infId];
            if(rnd(1,20) == 1) continue; // 5% szans, że nie przyjdzie do pracy 
            string dataRozpoczecia = obecna_data(10*GODZINA + rnd(-2*GODZINA,2*GODZINA));
            string dataZakonczenia = obecna_data(18*GODZINA + rnd(-2*GODZINA,2*GODZINA));
            PRACA_OSOBY.pb({infId, magId, 4, dataRozpoczecia, dataZakonczenia});
        }

        czasDzien = 8*GODZINA;
        // godzina 8:00:00 - 9:00:00
        
        // Ludzie nadaja paczki
        for(int i=0; i<PACZEK_DZIENNIE; ++i){
            ll czasNadania = czasDzien + (i*1*GODZINA)/(PACZEK_DZIENNIE) + rnd(0,3*SEKUNDA);
            string dataNadania = obecna_data(czasNadania);
            int nadawcaId = klienci[rnd(0,klienci.size()-1)];
            int adresatId = klienci[rnd(0,klienci.size()-1)];
            if(nadawcaId==adresatId) continue;
            int paczkomatNadawcy = klientPaczkomat[nadawcaId];
            int paczkomatOdbiorcy = klientPaczkomat[adresatId];
            
            int rozmiar = rnd(1,3);
            int skrytkaNadawcyId,skrytkaOdbiorcyId;
            if(paczkomatNadawcy == paczkomatOdbiorcy){
                // Paczka lokalna, generatorka się nią nie zajmuje - od razu wpisujemy że ktoś ją odebrał
                skrytkaNadawcyId = skrytkaOdbiorcyId = wolnaSkrytka(paczkomatNadawcy,rozmiar);
                if(skrytkaNadawcyId == -1) continue; // Brak miejsca w paczkomacie
                int zlecenieId = NEXT_ZLECENIE_ID++;
                ZLECENIA.pb({zlecenieId, nadawcaId, adresatId, paczkomatOdbiorcy, dataNadania, rozmiar});

                ll czasOdbioru = czasNadania + rnd(5*MINUTA,3*GODZINA);
                string dataOdbioru = obecna_data(czasOdbioru);
                ODBIORY.pb({zlecenieId, skrytkaOdbiorcyId, dataNadania, dataOdbioru});
                // rejestrujemy nadanie
                NADANIA.pb({zlecenieId,skrytkaNadawcyId,dataNadania});
                continue;
            }
            skrytkaNadawcyId = wolnaSkrytka(paczkomatNadawcy,rozmiar);
            skrytkaOdbiorcyId = wolnaSkrytka(paczkomatOdbiorcy,rozmiar);
            
            if(skrytkaNadawcyId == -1 || skrytkaOdbiorcyId == -1) continue;  

            // tworzymy zlecenie
            int zlecenieId = NEXT_ZLECENIE_ID++;
            ZLECENIA.pb({zlecenieId, nadawcaId, adresatId, paczkomatOdbiorcy, dataNadania, rozmiar});

            // zajmujemy dana skrytke poprzez dodanie pustej krotki odbioru
            ODBIORY.pb({zlecenieId, skrytkaOdbiorcyId, "NULL", "NULL"});
            // rejestrujemy nadanie
            NADANIA.pb({zlecenieId,skrytkaNadawcyId,dataNadania});
            paczkomatZlecenia[paczkomatNadawcy].insert(zlecenieId);
        }

        czasDzien = 10*GODZINA;
        // Kierowcy zaczynaja prace o 10 i pracuja do 18
        for(auto kierId: kierowcy){
            int magId = kierowcaMagazyn[kierId];
            string dataRozpoczecia = obecna_data(czasDzien + rnd(0,3*MINUTA));
            string dataZakonczenia = obecna_data(czasDzien + 8*GODZINA - rnd(0,3*MINUTA));
            PRACA_OSOBY.pb({kierId, magId, 2, dataRozpoczecia, dataZakonczenia});
        }
        
        // godzina 10:00:00 - 11:00:00
        // Kierowcy zbieraja paczki z paczkomatow nalezacych do okolicznego magazynu
        {
            vector<bool> visKierowca(sz(OSOBY)+1),visPojazd(sz(POJAZDY)+1);
            each(m,MAGAZYNY){
                int magId = m.id_magazynu;
                osoba kier;
                pojazd poj;
                try{
                    tie(poj,kier) = dajPojazdKierowca(magId,visKierowca,visPojazd);
                }catch(...){
                    continue; // Nie skompletujemy kierowcy i pojazdu :(
                }

                int kierowcaId = kier.id;
                int pojazdId = poj.id_pojazdu;

                vector<int> paczkomatyDoWyzbierania;
                for(auto &[id_p2,lok2,magId2] : PACZKOMATY){
                    if(magId2 == magId && !paczkomatZlecenia[id_p2].empty()){
                        paczkomatyDoWyzbierania.pb(id_p2);
                    }
                }
                if(paczkomatyDoWyzbierania.empty()) continue; // Nic nie ma w paczkomatach ;(
                visKierowca[kier.id] = 1;
                visPojazd[poj.id_pojazdu] = 1;
                int idKursu = NEXT_KURS_ID++; // Kurs od magazynu do siebie samego - wyzbieranie paczek
                ll czasStart = czasDzien+rnd(1*MINUTA,5*MINUTA);
                ll czasKoniec = czasDzien+rnd(40*MINUTA,45*MINUTA);
                
                string dataStart = obecna_data(czasStart);
                string dataKoniec = obecna_data(czasKoniec);
                for(int i=0; i<sz(paczkomatyDoWyzbierania); ++i){
                    const auto &id_p = paczkomatyDoWyzbierania[i];
                    ll czasP = (czasKoniec*(i)+czasStart*(sz(paczkomatyDoWyzbierania)-i)) / (sz(paczkomatyDoWyzbierania));
                    ll czasP2 = (czasKoniec*(i+1)+czasStart*(sz(paczkomatyDoWyzbierania)-i-1)) / (sz(paczkomatyDoWyzbierania));
                    string dataP = obecna_data(czasP);
                    string dataO = obecna_data(czasP2);
                    // Ładujemy paczki z paczkomatu do pojazdu
                    for(auto it=paczkomatZlecenia[id_p].begin(); it!=paczkomatZlecenia[id_p].end();){
                        int zlecenie = *it;
                        int rozmiar = paczkaRozmiar(zlecenie);
                        if(wolneMiejsce(pojazdId) >= (1<<rozmiar)){
                            pojazdZlecenia[pojazdId].insert(zlecenie);
                            ZLECENIA_KURSY.pb({zlecenie, idKursu, dataP});
                            it = paczkomatZlecenia[id_p].erase(it);
                            // cerr << "Bierzemy paczuche:" << zlecenie << endl;
                        }else{
                            ++it;
                        }
                    }
                    KURSY_PACZKOMATY.pb({idKursu,id_p,dataP,dataO});
                }
                KURSY.pb({idKursu, pojazdId, kierowcaId, magId, magId, dataStart, dataKoniec});
                // Wyładowujemy paczki do magazynu
                ll czasStartWyladowania = czasKoniec + rnd(1*MINUTA, 3*MINUTA);
                ll czasKoniecWyladowania = czasStartWyladowania + rnd(10*MINUTA,15*MINUTA);
                for(auto it=pojazdZlecenia[pojazdId].begin(); it!=pojazdZlecenia[pojazdId].end();){
                    int zlecenie = *it;
                    ll czasWyladowania = rnd(czasStartWyladowania+0.5*MINUTA, czasKoniecWyladowania-0.5*MINUTA);
                    string dataWyladowania = obecna_data(czasWyladowania);
                    magazynZlecenia[magId].insert(zlecenie);
                    ZLECENIA_MAGAZYNY.pb({zlecenie,magId,dataWyladowania});
                    it = pojazdZlecenia[pojazdId].erase(it);
                }
                string dataKoniecWyladowania = obecna_data(czasKoniecWyladowania);
                DEKLARACJA_WYPAKOWAN.pb({idKursu,dataKoniecWyladowania});
            }
        }
        czasDzien = 11.5*GODZINA;
        // Godzina 11:30:00 - 16:30:00
        // Rozwożenie paczek między magazynami
        {  
            vector<bool> visKierowca(sz(OSOBY)+1),visPojazd(sz(POJAZDY)+1);
            const auto trasy = wyznaczTrasy();
            int cnt = 0;
            for(const auto &[magazynStart, magazynKoniec] : trasy){
                pojazd poj;
                osoba kier;
                try{
                    tie(poj,kier) = dajPojazdKierowca(magazynStart,visKierowca,visPojazd);
                }catch(...){
                    continue; // Nie skompletujemy kierowcy i pojazdu :(
                }

                ll czasStartZaladunek = czasDzien + rnd(5*MINUTA,10*MINUTA);
                ll czasKoniecZaladunek = czasStartZaladunek + rnd(5*MINUTA,15*MINUTA);
                int kursId = NEXT_KURS_ID++;
                int kierId = kier.id;
                int pojazdId = poj.id_pojazdu;
                // Ładujemy pojazd paczkami
                for(auto it=magazynZlecenia[magazynStart].begin(); it!=magazynZlecenia[magazynStart].end();){
                    int zlecenie = *it;
                    if(magazyn_docelowy(zlecenie)==magazynKoniec && wolneMiejsce(pojazdId)>=(1<<paczkaRozmiar(zlecenie))){
                        pojazdZlecenia[pojazdId].insert(zlecenie);
                        ll czasZaladunek = rnd(czasStartZaladunek,czasKoniecZaladunek);
                        string dataZaladunek = obecna_data(czasZaladunek);
                        ZLECENIA_KURSY.pb({zlecenie,kursId,dataZaladunek});
                        it = magazynZlecenia[magazynStart].erase(it);
                        // cerr << "Przewozimy paczuche:" << zlecenie << endl;
                    }else{
                        ++it;
                    }
                }
                if(pojazdZlecenia[pojazdId].empty()){
                    --NEXT_KURS_ID;
                    continue;
                }
                ++cnt;
                visKierowca[kier.id] = 1;
                visPojazd[poj.id_pojazdu] = 1;
                // Wysyłamy pojazd w podróż do magazynKoniec
                ll czasStart = czasKoniecZaladunek + rnd(3*MINUTA,5*MINUTA);
                ll czasKoniec = czasStart + rnd(3.5*GODZINA,4*GODZINA);
                string dataStart = obecna_data(czasStart);
                string dataKoniec = obecna_data(czasKoniec);
                KURSY.pb({kursId,pojazdId,kierId,magazynStart,magazynKoniec,dataStart,dataKoniec});
                kierowcaMagazyn[kierId] = magazynKoniec;
                pojazdMagazyn[pojazdId] = magazynKoniec;
                // Rozładowujemy pojazd w magazynKoniec
                ll czasStartRozladunek = czasKoniec + rnd(3*MINUTA,7*MINUTA);
                ll czasKoniecRozladunek = czasStartRozladunek + rnd(10*MINUTA,15*MINUTA);
                for(auto it=pojazdZlecenia[pojazdId].begin(); it!=pojazdZlecenia[pojazdId].end();){
                    int zlecenie = *it;
                    ll czasRozladunek = rnd(czasStartRozladunek, czasKoniecRozladunek);
                    string dataRozladunek = obecna_data(czasRozladunek);
                    ZLECENIA_MAGAZYNY.pb({zlecenie,magazynKoniec,dataRozladunek});
                    magazynZlecenia[magazynKoniec].insert(zlecenie);
                    it = pojazdZlecenia[pojazdId].erase(it);
                }
                string dataKoniecRozladunek = obecna_data(czasKoniecRozladunek);
                DEKLARACJA_WYPAKOWAN.pb({kursId,dataKoniecRozladunek});
            }
            // cerr << cnt;
        }
        czasDzien = 17*GODZINA;
        // godzina: 17:00:00 - 18:00:00 
        // Rozwozenie paczek z magazynow do lokalnych paczkomatow
        
        {
            vector<bool> visKierowca(sz(OSOBY)+1),visPojazd(sz(POJAZDY)+1);
            each(m,MAGAZYNY){
                int magId = m.id_magazynu;
                pojazd poj;
                osoba kier;
                try{
                    tie(poj,kier) = dajPojazdKierowca(magId,visKierowca,visPojazd);
                }catch(...){
                    continue; // Nie skompletujemy kierowcy i pojazdu :(
                }
                visKierowca[kier.id] = 1;
                visPojazd[poj.id_pojazdu] = 1;
                // Ladowanie paczek z magazynu do pojazdu
                int kursId = NEXT_KURS_ID++;
                int pojazdId = poj.id_pojazdu;
                int kierId = kier.id;
                ll czasStartZaladunek = czasDzien + rnd(0*MINUTA,5*MINUTA);
                ll czasKoniecZaladunek = czasStartZaladunek + rnd(6*MINUTA,10*MINUTA);
                for(auto it=magazynZlecenia[magId].begin(); it!=magazynZlecenia[magId].end();){
                    int zlecenie = *it;
                    if(magazyn_docelowy(zlecenie)==magId && wolneMiejsce(pojazdId)>=(1<<paczkaRozmiar(zlecenie))){
                        pojazdZlecenia[pojazdId].insert(zlecenie);
                        ll czasZaladunek = rnd(czasStartZaladunek,czasKoniecZaladunek);
                        string dataZaladunek = obecna_data(czasZaladunek);
                        ZLECENIA_KURSY.pb({zlecenie,kursId,dataZaladunek});
                        it = magazynZlecenia[magId].erase(it);
                    }else{
                        ++it;
                    }
                }
                if(pojazdZlecenia[pojazdId].empty()){
                    --NEXT_KURS_ID;
                    continue;
                }
                // Rozwozenie paczek po paczkomatach wokolo
                ll czasStart = czasKoniecZaladunek + rnd(3*MINUTA,5*MINUTA);
                ll czasKoniec = czasStart + rnd(30*MINUTA, 40*MINUTA);
                string dataStart = obecna_data(czasStart);
                string dataKoniec = obecna_data(czasKoniec);
                vector<int> paczkomatyDoOdwiedzenia;
                for(auto &[id_p2,lok2,magId2] : PACZKOMATY){
                    if(magId2 == magId){
                        paczkomatyDoOdwiedzenia.pb(id_p2);
                    }
                }
                KURSY.pb({kursId,pojazdId,kierId,magId,magId,dataStart,dataKoniec});
                for(int i=0; i<sz(paczkomatyDoOdwiedzenia); ++i){
                    const auto &id_p = paczkomatyDoOdwiedzenia[i];
                    ll czasP = (czasKoniec*(i)+czasStart*(int(paczkomatyDoOdwiedzenia.size())-i)) / (sz(paczkomatyDoOdwiedzenia));
                    ll czasP2 = (czasKoniec*(i+1)+czasStart*(int(paczkomatyDoOdwiedzenia.size())-i-1)) / (sz(paczkomatyDoOdwiedzenia));
                    string dataP = obecna_data(czasP);
                    string dataO = obecna_data(czasP2);
                    // Rozładowujemy paczki z pojazdu do paczkomatu
                    for(auto it=pojazdZlecenia[pojazdId].begin(); it!=pojazdZlecenia[pojazdId].end();){
                        int zlecenie = *it;
                        // Wsadzamy paczke do paczkomatu/skrytki - zaznaczamy to w ODBIORY
                        {
                            string data_dost = dataP;
                            string data_odeb = obecna_data(czasP + rnd(5*MINUTA,2*GODZINA));
                            odbierzPaczke(zlecenie,data_dost,data_odeb);
                            // cerr << "Dowozimy paczuche:" << zlecenie << endl;
                        }
                        it = pojazdZlecenia[pojazdId].erase(it);
                    }
                    KURSY_PACZKOMATY.pb({kursId,id_p,dataP,dataO});
                }
                DEKLARACJA_WYPAKOWAN.pb({kursId,dataKoniec});
            }
        }
        dodajSekund(1*DZIEN);
    }
    // Usun odbiory z kilku paczek ostatnich 
    assert((NIEODEBRANYCH_PACZEK <= ODBIORY.size()) && "Za mało odbiorów");
    rep(p,0,NIEODEBRANYCH_PACZEK){
        for(int i=sz(ODBIORY)-1; i>=0; --i){
            if(rnd(1,10)==1){
                if(czySkrytkaWolna(ODBIORY[i].id_skrytki) && ODBIORY[i].data_odebrania!="NULL")
                    ODBIORY[i].data_odebrania = "NULL";
                break;
            }
        }
    }

    cerr << endl;
    int cntAll=0,cntDone=0;
    each(o,ODBIORY){
        ++cntAll;
        cntDone += o.data_dostarczenia!="NULL";
    }
    cerr << " Dostarczono: " << cntDone << "/" << cntAll << " (" <<  (100*cntDone/cntAll) << "%)" << endl;
    printEverything();
    return 0;
}

osoba genOsoba(){
    osoba os;
    os.id = NEXT_OSOBA_ID++; 
    os.imie = imiona[rnd(0,imiona.size()-1)];
    os.nazwisko = nazwiska[rnd(0,nazwiska.size()-1)];
    os.email = przymiotnik[rnd(0,przymiotnik.size()-1)] + "." + rzecz[rnd(0,rzecz.size()-1)] + to_string(rnd(0,100000)) + "@" + domena[rnd(0,domena.size()-1)];
    os.nr_tel = "+48 ";
    rep(i,0,9) os.nr_tel += char(rnd('0','9'));
    
    string pesel = "";
    int miesiac = rnd(1,12);
    int dzien = rnd(1,28);
    int rok = rnd(1944,2004);
    if(rok >= 2000) miesiac += 20;
    rok %= 100;
    pesel = (rok<10?"0":"") + to_string(rok) + (miesiac<10?"0":"") + to_string(miesiac) + (dzien<10?"0":"") + to_string(dzien);
    rep(i,0,4) pesel += char(rnd('0','9'));
    if(czyKobieta(os) && pesel.back()%2==1){
        ++pesel.back();
        if(pesel.back() > '9')
            pesel.back() -= 10;
    }
    int cyfraKontrolna = 0;
    cyfraKontrolna += (pesel[0]+pesel[4]+pesel[8]-3*'0') * 1;
    cyfraKontrolna += (pesel[1]+pesel[5]+pesel[9]-3*'0') * 3;
    cyfraKontrolna += (pesel[2]+pesel[6]-2*'0') * 7;
    cyfraKontrolna += (pesel[3]+pesel[7]-2*'0') * 9;
    cyfraKontrolna %= 10;
    cyfraKontrolna = 10 - cyfraKontrolna;
    cyfraKontrolna %= 10;
    pesel += char('0'+cyfraKontrolna);
    os.pesel = rnd(1,100) == 1 ? "NULL" : pesel;
    return os;
}

bool czyKobieta(const osoba &os){
    return os.imie.back()=='a';
}

pojazd genPojazd(){
    pojazd p;
    p.id_pojazdu = NEXT_POJAZD_ID++;
    p.id_rodzaju = rnd(1,RODZAJE_POJAZDOW.size());
    string rejestracja = ""; // Tylko I i II zasób
    rep(i,0,3) rejestracja += char(rnd('0','9'));
    if(rnd(0,1) == 0) rejestracja += char(rnd('0','1')); // zasób I
    else rejestracja += char(rnd('A','Z')); // zasób II
    rejestracja = prefiksyRejestracje[rnd(0,prefiksyRejestracje.size()-1)] + rejestracja;    
    p.nr_rejestracji = rejestracja;
    return p;
}

string genLokalizacja(const string &miasto){
    string lok = "";
    lok += miasto;
    lok += ", ";
    lok += ulice[rnd(0,ulice.size()-1)];
    lok += " ";
    lok += to_string(rnd(1,60));
    if(rnd(1,4)==1){
        lok+=char(rnd('a','g'));
    }
    return lok;
}

vector<string> tokenize(string s, char sep){
    vector<string> res;
    string txt="";
    s+=sep;
    for(auto &c : s){
        if(c==sep){
            if(!txt.empty()) res.pb(txt);
            txt = "";
        }else txt+=c;
    }
    return res;
}

string to_string(const osoba &os){
    return "(" + (os.id==-1 ? "default" : to_string(os.id)) + (os.pesel=="NULL" ? ",NULL,\'" : ",\'" + os.pesel + "\',\'") + os.imie + "\',\'" + os.nazwisko + "\',\'" + os.email + "\',\'" + os.nr_tel + "\')";
}
string to_string(const pojazd &p){
    return "(" + (p.id_pojazdu==-1 ? "default" : to_string(p.id_pojazdu)) + ",\'" + p.nr_rejestracji + "\'," + to_string(p.id_rodzaju) + ")";
}
string to_string(const rodzaj_pojazdu &p){
    return "(" + (p.id_rodzaju==-1 ? "default" : to_string(p.id_rodzaju)) + ",\'" + p.nazwa + "\'," + to_string(p.pojemnosc) + "," + to_string(p.id_uprawnienia) + ")";
}
string to_string(const magazyn &m){
    return "(" + (m.id_magazynu==-1 ? "default" : to_string(m.id_magazynu)) + ",\'" + m.lokalizacja + "\')";
}
string to_string(const paczkomat &p){
    return "(" + (p.id_paczkomatu==-1 ? "default" : to_string(p.id_paczkomatu)) + ",\'" + p.lokalizacja + "\'," + to_string(p.magazyn) + ")";
}
string to_string(const uprawnienie &u){
    return "(" + (u.id_uprawnienia==-1 ? "default" : to_string(u.id_uprawnienia)) + ",\'" + u.nazwa + "\')";
}
string to_string(const stanowisko &s){
    return "(" + (s.id_stanowiska==-1 ? "default" : to_string(s.id_stanowiska)) + ",\'" + s.nazwa + "\')";
}
string to_string(const osoba_uprawnienie &u){
    return "(" + to_string(u.id_osoby) + "," + to_string(u.id_uprawnienia) + ")";
}
string to_string(const stanowisko_osoba &s){
    return "(" + to_string(s.id_osoby) + "," + to_string(s.id_stanowiska) + ")";
}
string to_string(const usterka &u){
    return "(" + to_string(u.id_pojazdu) + ",\'" + u.opis + "\',\'" + u.data_wystapienia + "\',\'" + u.data_rozpoczecia_naprawy + "\',\'" + u.data_zakonczenia_naprawy + "\')";
}
string to_string(const serwis &s){
    return "(" + to_string(s.id_pojazdu) + "," + to_string(s.id_przegladu) + ",\'" + s.data_rozpoczecia + "\',\'" + s.data_zakonczenia + "\')";
}
string to_string(const przeglady_rodzaje_pojazdy &p){
    return "(" + to_string(p.id_rodzaju) + "," + to_string(p.id_przegladu) + "," + to_string(p.czestotliwosc) + ")";
}
string to_string(const rodzaje_przegladow &r){
    return "(" + (r.id_przegladu==-1 ? "default" : to_string(r.id_przegladu)) + ",\'" + r.nazwa + "\')";
}
string to_string(const kurs &k){
    return "(" + (k.id_kursu==-1 ? "default" : to_string(k.id_kursu)) + "," + to_string(k.id_pojazdu) + "," + to_string(k.id_kierowcy) + "," + to_string(k.magazyn_start) + "," + to_string(k.magazyn_docelowy) + ",\'" + k.data_wyjazdu + "\',\'" + k.data_przyjazdu + "\')";
}
string to_string(const kurs_paczkomat &k){
    return "(" + to_string(k.id_kursu) + "," + to_string(k.id_paczkomatu) + ",\'" + k.data_przyjazdu + "\',\'" + k.data_odjazdu + "\')"; 
}
string to_string(const zlecenie_kurs &z){
    return "(" + to_string(z.id_zlecenia) + "," + to_string(z.id_kursu) + ",\'" + z.data + "\')";
}
string to_string(const zlecenie_magazyn &z){
    return "(" + to_string(z.id_zlecenia) + "," + to_string(z.id_magazynu) + ",\'" + z.data + "\')";
}
string to_string(const zlecenie &z){
    return "(" + (z.id_zlecenia==-1 ? "default" : to_string(z.id_zlecenia)) + "," + to_string(z.id_nadawcy) + "," + to_string(z.id_odbiorcy) + "," + to_string(z.id_pacz_odb) + ",\'" + z.data_zlozenia + "\'," + to_string(z.rozmiar) + ")";
}
string to_string(const odbior &o){
    return "(" + to_string(o.id_zlecenia) + "," + to_string(o.id_skrytki) + (o.data_dostarczenia=="NULL" ? ",NULL," : ",\'" + o.data_dostarczenia + "\',") + (o.data_odebrania=="NULL" ? "NULL)" : "\'" + o.data_odebrania + "\')");
}
string to_string(const nadanie &n){
    return "(" + to_string(n.id_zlecenia) + "," + to_string(n.id_skrytki) + ",\'" + n.data + "\')";
}
string to_string(const praca_osoba &po){
    return "(" + to_string(po.id_osoby) + "," + to_string(po.id_magazynu) + "," + to_string(po.id_stanowiska) + ",\'" + po.data_rozpoczecia + "\',\'" + po.data_zakonczenia + "\')";
}
string to_string(const skrytka &s){
    return "(" + (s.id_skrytki==-1 ? "default" : to_string(s.id_skrytki)) + "," + to_string(s.id_paczkomatu) + "," + to_string(s.rozmiar) + ")";
}
string to_string(const deklaracja_wypakowania &d){
    return "(" + to_string(d.id_kursu) + ",\'" + d.data + "\')";
}

string Insert(const string &s){
    return "INSERT INTO " + s + " VALUES\n";
}

void printEverything(){
    cout << Insert("uprawnienia");
    for(int i=0; i<sz(UPRAWNIENIA); ++i){
        UPRAWNIENIA[i].id_uprawnienia=-1;
        cout << to_string(UPRAWNIENIA[i]);
        if(i!=sz(UPRAWNIENIA)-1) cout << ",\n";
    }
    cout << ";\n\n";
    cout << Insert("rodzaje_pojazdow");
    for(int i=0; i<sz(RODZAJE_POJAZDOW); ++i){
        RODZAJE_POJAZDOW[i].id_rodzaju = -1;
        cout << to_string(RODZAJE_POJAZDOW[i]);
        if(i!=sz(RODZAJE_POJAZDOW)-1) cout << ",\n";
    }
    cout << ";\n\n";
    cout << Insert("stanowiska");
    for(int i=0; i<sz(STANOWISKA); ++i){
        STANOWISKA[i].id_stanowiska = -1;
        cout << to_string(STANOWISKA[i]);
        if(i!=sz(STANOWISKA)-1) cout << ",\n";
    }
    cout << ";\n\n";
    cout << Insert("rodzaje_przegladow");
    for(int i=0; i<sz(RODZAJE_PRZEGLADOW); ++i){
        RODZAJE_PRZEGLADOW[i].id_przegladu = -1;
        cout << to_string(RODZAJE_PRZEGLADOW[i]);
        if(i!=sz(RODZAJE_PRZEGLADOW)-1) cout << ",\n";
    }
    cout << ";\n\n";
    cout << Insert("magazyny");
    for(int i=0; i<sz(MAGAZYNY); ++i){
        MAGAZYNY[i].id_magazynu = -1;
        cout << to_string(MAGAZYNY[i]);
        if(i!=sz(MAGAZYNY)-1) cout << ",\n";
    }
    cout << ";\n\n";
    cout << Insert("paczkomaty");
    for(int i=0; i<sz(PACZKOMATY); ++i){
        PACZKOMATY[i].id_paczkomatu = -1;
        cout << to_string(PACZKOMATY[i]);
        if(i!=sz(PACZKOMATY)-1) cout << ",\n";
    }
    cout << ";\n\n";
    cout << Insert("osoby");
    for(int i=0; i<sz(OSOBY); ++i){
        OSOBY[i].id = -1;
        cout << to_string(OSOBY[i]);
        if(i!=sz(OSOBY)-1) cout << ",\n";
    }
    cout << ";\n\n";
    cout << Insert("stanowiska_osoby");
    for(int i=0; i<sz(STANOWISKA_OSOBY); ++i){
        cout << to_string(STANOWISKA_OSOBY[i]);
        if(i!=sz(STANOWISKA_OSOBY)-1) cout << ",\n";
    }
    cout << ";\n\n";
    cout << Insert("osoby_uprawnienia");
    for(int i=0; i<sz(OSOBY_UPRAWNIENIA); ++i){
        cout << to_string(OSOBY_UPRAWNIENIA[i]);
        if(i!=sz(OSOBY_UPRAWNIENIA)-1) cout << ",\n";
    }
    cout << ";\n\n";
    // cout << Insert("usterki");
    // for(int i=0; i<sz(USTERKI); ++i){
    //     cout << to_string(USTERKI[i]);
    //     if(i!=sz(USTERKI)-1) cout << ",\n";
    // }
    // cout << ";\n\n";
    cout << Insert("pojazdy");
    for(int i=0; i<sz(POJAZDY); ++i){
        POJAZDY[i].id_pojazdu = -1;
        cout << to_string(POJAZDY[i]);
        if(i!=sz(POJAZDY)-1) cout << ",\n";
    }
    cout << ";\n\n";
    cout << Insert("serwis");
    for(int i=0; i<sz(SERWIS); ++i){
        cout << to_string(SERWIS[i]);
        if(i!=sz(SERWIS)-1) cout << ",\n";
    }
    cout << ";\n\n";
    cout << Insert("przeglady_rod_pojazdy");
    for(int i=0; i<sz(PRZEGLADY_ROD_POJAZDY); ++i){
        cout << to_string(PRZEGLADY_ROD_POJAZDY[i]);
        if(i!=sz(PRZEGLADY_ROD_POJAZDY)-1) cout << ",\n";
    }
    cout << ";\n\n";
    cout << Insert("kursy");
    for(int i=0; i<sz(KURSY); ++i){
        KURSY[i].id_kursu = -1;
        cout << to_string(KURSY[i]);
        if(i!=sz(KURSY)-1) cout << ",\n";
    }
    cout << ";\n\n";
    cout << Insert("kursy_paczkomaty");
    for(int i=0; i<sz(KURSY_PACZKOMATY); ++i){
        cout << to_string(KURSY_PACZKOMATY[i]);
        if(i!=sz(KURSY_PACZKOMATY)-1) cout << ",\n";
    }
    cout << ";\n\n";
    
    cout << Insert("zlecenia");
    for(int i=0; i<sz(ZLECENIA); ++i){
        ZLECENIA[i].id_zlecenia = -1;
        cout << to_string(ZLECENIA[i]);
        if(i!=sz(ZLECENIA)-1) cout << ",\n";
    }
    cout << ";\n\n";
    cout << Insert("zlecenia_kursy");
    for(int i=0; i<sz(ZLECENIA_KURSY); ++i){
        cout << to_string(ZLECENIA_KURSY[i]);
        if(i!=sz(ZLECENIA_KURSY)-1) cout << ",\n";
    }
    cout << ";\n\n";
    cout << Insert("zlecenia_magazyny");
    for(int i=0; i<sz(ZLECENIA_MAGAZYNY); ++i){
        cout << to_string(ZLECENIA_MAGAZYNY[i]);
        if(i!=sz(ZLECENIA_MAGAZYNY)-1) cout << ",\n";
    }
    cout << ";\n\n";
    cout << Insert("skrytki");
    for(int i=0; i<sz(SKRYTKI); ++i){
        SKRYTKI[i].id_skrytki = -1;
        cout << to_string(SKRYTKI[i]);
        if(i!=sz(SKRYTKI)-1) cout << ",\n";
    }
    cout << ";\n\n";
    cout << Insert("odbiory");
    for(int i=0; i<sz(ODBIORY); ++i){
        cout << to_string(ODBIORY[i]);
        if(i!=sz(ODBIORY)-1) cout << ",\n";
    }
    cout << ";\n\n";
    cout << Insert("praca_osoby");
    for(int i=0; i<sz(PRACA_OSOBY); ++i){
        cout << to_string(PRACA_OSOBY[i]);
        if(i!=sz(PRACA_OSOBY)-1) cout << ",\n";
    }
    cout << ";\n\n";
    
    cout << Insert("nadania");
    for(int i=0; i<sz(NADANIA); ++i){
        cout << to_string(NADANIA[i]);
        if(i!=sz(NADANIA)-1) cout << ",\n";
    }
    cout << ";\n\n";
    
    cout << Insert("deklaracja_wypakowan");
    for(int i=0; i<sz(DEKLARACJA_WYPAKOWAN); ++i){
        cout << to_string(DEKLARACJA_WYPAKOWAN[i]);
        if(i!=sz(DEKLARACJA_WYPAKOWAN)-1) cout << ",\n";
    }
    cout << ";\n\n";

}

void dodajMagazyn(const string &miasto, const string &nadmiasto){ // Obecnie rownowazne z dodaniem miasta
    int id = NEXT_MAGAZYN_ID++;
    int idNad = nadmiasto == "-" ? -1 : miastoMagazyn[nadmiasto];
    string lokacja = genLokalizacja(miasto);
    lokalizacjaMagazyn[lokacja] = id;
    magazynLokalizacja[id] = lokacja;
    miastoMagazyn[miasto] = id;
    nadmagazyn[id] = idNad;
    MAGAZYNY.pb({id, lokacja});
}

void dodajPaczkomat(const string &miasto){
    int id_paczkomatu = NEXT_PACZKOMAT_ID++;
    string lokacja = genLokalizacja(miasto);
    PACZKOMATY.pb({id_paczkomatu,lokacja,miastoMagazyn[miasto]});
    paczkomatMagazyn[id_paczkomatu] = miastoMagazyn[miasto];
    int ileSkrytek = rnd(50,300) / 5 * 5;
    rep(i,0,ileSkrytek){
        int id_skrytki = NEXT_SKRYTKA_ID++;
        int rozmiar = rnd(1,3);
        SKRYTKI.pb({id_skrytki, id_paczkomatu, rozmiar});
    }
}

void dodajPaczkomat(const string &miasto, const int &cnt){
    rep(i,0,cnt)
        dodajPaczkomat(miasto);
}

int wolnaSkrytka(const int &paczkomat, const int &rozmiar){
    map<int,bool> zajetaSkrytka;
    // eliminujemy id skrytek, ktore czekaja na dostarczenie paczki/odebranie jej przez odbiorce
    for(auto &[id_zle, id_skr, data_dost, data_odeb] : ODBIORY){
        if(data_odeb == "NULL"){
            zajetaSkrytka[id_skr] = 1;
        }
    }
    for(auto &[id_s, id_p, roz] : SKRYTKI){
        if(id_p==paczkomat && roz==rozmiar && !zajetaSkrytka[id_s]){
            // eliminujemy id skrytek, ktore trzymaja paczke, ktora dopiero ma zaczac podroz
            // znajdujemy ostatnie zlecenie dla danej skrytki
            string ostatniaData = "0000-0-0";
            int ostatnieZlecenie=-1;
            for(auto &[id_z2,id_s2,data2] : NADANIA){
                if(id_s2==id_s && data2>ostatniaData){
                    ostatniaData = data2;
                    ostatnieZlecenie = id_z2;
                }
            }
            if(ostatnieZlecenie==-1){
                return id_s; // Nigdy nie nadano stad jeszcze paczki
            }
            bool rozpoczetoKurs=false;
            for(auto &[id_z2,id_k2,data2] : ZLECENIA_KURSY){
                if(id_z2 == ostatnieZlecenie){
                    rozpoczetoKurs = true;
                    break;
                }
            }
            if(!rozpoczetoKurs){
                return id_s;
            }
        }
    }
    return -1;
}

int wolneMiejsce(const int &pojazd){
    int rodzaj=-1,pojemnosc=-1;
    for(auto &[id_p,nr_rej,id_r] : POJAZDY){
        if(id_p==pojazd){
            rodzaj = id_r;
            break;
        }
    }
    assert(rodzaj>=0);
    for(auto &[id_r,nazwa,poj,id_upr] : RODZAJE_POJAZDOW){
        if(id_r==rodzaj){
            pojemnosc = poj;
            break;
        }
    }
    assert(pojemnosc>=0);
    for(auto &id_z : pojazdZlecenia[pojazd]){
        pojemnosc -= 1<<paczkaRozmiar(id_z);
    }
    assert(pojemnosc>=0);
    return pojemnosc;
}

int paczkaRozmiar(const int &zlecenie){
    for(auto &[id_z,id_n,id_o,id_p_o,data,roz] : ZLECENIA){
        if(zlecenie == id_z)
            return roz;
    }
    assert(false);
    return -1;
}

int potrzebneUprawnienie(const int &pojazd_rodzaj){
    for(auto &[id_r,nazwa,poj,id_upr] : RODZAJE_POJAZDOW){
        if(id_r==pojazd_rodzaj){
            return id_upr;
        }
    }
    assert(false);
    return -1;
}

void odbierzPaczke(const int &zlecenie, const string &data_dostarczenia, const string &data_odbioru){
    for(auto &[id_z,id_s,data_dost,data_odeb] : ODBIORY){
        if(id_z == zlecenie){
            data_dost = data_dostarczenia;
            data_odeb = data_odbioru;
            return;
        }
    }
    assert(false && "Nie znaleziono paczki");
}

int rodzajPojazdu(const int &pojazdId){
    for(auto &[id_poj, rej, id_rodz] : POJAZDY)
        if(id_poj == pojazdId)
            return id_rodz;
    assert(false && "Nie znaleziono pojazdu");
}

bool mozeProwadzic(const int &osobaId, const int &pojazdId){
    int pojazdRodzajId = rodzajPojazdu(pojazdId);
    int upr = potrzebneUprawnienie(pojazdRodzajId);
    for(auto &[id_os, id_upr] : OSOBY_UPRAWNIENIA)
        if(id_os==osobaId && id_upr==upr)
            return true;
    return false;
}

osoba idToOsoba(const int &osobaId){
    each(os,OSOBY)
        if(os.id == osobaId)
            return os;
    assert(false && "Nie znaleziono osoby o danym id");
}

pojazd idToPojazd(const int &pojazdId){
    each(poj,POJAZDY)
        if(poj.id_pojazdu == pojazdId)
            return poj;
    assert(false && "Nie znaleziono pojazdu o danym id");
}

pair<pojazd,osoba> dajPojazdKierowca(const int &magazynId, const vector<bool> &visKierowca, const vector<bool> &visPojazd){
    vi dostepniKierowcy,dostepnePojazdy;
    each(k,kierowcy)
        if(kierowcaMagazyn[k] == magazynId)
            dostepniKierowcy.pb(k);
    each(poj,POJAZDY)
        if(pojazdMagazyn[poj.id_pojazdu] == magazynId)
            dostepnePojazdy.pb(poj.id_pojazdu);
    mieszaj(dostepniKierowcy);
    mieszaj(dostepnePojazdy);
    each(kier,dostepniKierowcy)
        each(poj,dostepnePojazdy)
            if(mozeProwadzic(kier,poj) && !visKierowca[kier] && !visPojazd[poj])
                return {idToPojazd(poj),idToOsoba(kier)};
    throw "Nie skompletowano pary (pojazd,kierowca)";
}

string dataNadania(const int &zlecenie){
    each(n,NADANIA)
        if(n.id_zlecenia==zlecenie)
            return n.data;
    assert(false && "Nie znaleziono zlecenia");
}

bool czyZakonczone(const int &zlecenie){
    each(o,ODBIORY)
        if(o.id_zlecenia==zlecenie)
            return o.data_dostarczenia!="NULL";
    return false;
}

int magazyn_startowy(const int &zlecenie){
    each(z,ZLECENIA)
        if(z.id_zlecenia == zlecenie)
            return paczkomatMagazyn[klientPaczkomat[z.id_nadawcy]]; 
    assert(false && "Nie znaleziono zlecenia");
}

int magazyn_docelowy(const int &zlecenie){
    each(z,ZLECENIA)
        if(z.id_zlecenia == zlecenie)
            return paczkomatMagazyn[klientPaczkomat[z.id_odbiorcy]];
    assert(false && "Nie znaleziono zlecenia");
}

vector<pair<int,int>> wyznaczTrasy(){
    vector<pair<int,int>> trasy;
    vector<tuple<int,int,int>> paczkiDoDostarczenia;// {id_zlecenia, id_nadawcy, id_odbiorcy, data_zlozenia}
    each(z,ZLECENIA){
        if(!czyZakonczone(z.id_zlecenia))
            paczkiDoDostarczenia.pb({z.id_zlecenia,z.id_nadawcy,z.id_odbiorcy});
    }
    //Pierwszenstwo maja paczki czekajace najdluzej (czy na pewno dobrze sortujemy ?)
    sort(all(paczkiDoDostarczenia), [](const tuple<int,int,int> &a, const tuple<int,int,int> &b){
        return get<0>(a) > get<0>(b);
    });
    
    vector<bool> visStart(sz(MAGAZYNY) + 1),visKoniec(sz(MAGAZYNY) + 1);
    set<pair<int,int>> vis;
    for(auto &[zlecenie, id_nadawca, id_odbiorca] : paczkiDoDostarczenia){
        int magazynStart = paczkomatMagazyn[klientPaczkomat[id_nadawca]];
        int magazynKoniec = paczkomatMagazyn[klientPaczkomat[id_odbiorca]];
        if(magazynStart!=magazynKoniec && !visStart[magazynStart] && !visKoniec[magazynKoniec]){
            vis.insert({magazynStart,magazynKoniec});
            visStart[magazynStart] = 1;
            visKoniec[magazynKoniec] = 1;
            trasy.pb({magazynStart,magazynKoniec});   
        }
    }
    fill(all(visStart),0);
    fill(all(visKoniec),0);
    for(auto &[zlecenie, id_nadawca, id_odbiorca] : paczkiDoDostarczenia){
        int magazynStart = paczkomatMagazyn[klientPaczkomat[id_nadawca]];
        int magazynKoniec = paczkomatMagazyn[klientPaczkomat[id_odbiorca]];
        if(magazynStart!=magazynKoniec && vis.find({magazynStart,magazynKoniec})==vis.end()){
            vis.insert({magazynStart,magazynKoniec});
            trasy.pb({magazynStart,magazynKoniec});   
        }
    }

    rep(proba,0,100){        
        int magazynStart = MAGAZYNY[rnd(0,sz(MAGAZYNY)-1)].id_magazynu;
        int magazynKoniec = MAGAZYNY[rnd(0,sz(MAGAZYNY)-1)].id_magazynu;
        if(magazynStart == magazynKoniec) continue;
        trasy.pb({magazynStart,magazynKoniec});   
        if(!visStart[magazynStart] && !visKoniec[magazynKoniec] && vis.find({magazynStart,magazynKoniec})==vis.end()){
            vis.insert({magazynStart,magazynKoniec});
            visStart[magazynStart] = 1;
            visKoniec[magazynKoniec] = 1;
            trasy.pb({magazynStart,magazynKoniec});   
        }
    }

    fill(all(visStart),0);
    fill(all(visKoniec),0);
    
    rep(proba,0,100){        
        int magazynStart = MAGAZYNY[rnd(0,sz(MAGAZYNY)-1)].id_magazynu;
        int magazynKoniec = MAGAZYNY[rnd(0,sz(MAGAZYNY)-1)].id_magazynu;
        if(magazynStart == magazynKoniec) continue;
        trasy.pb({magazynStart,magazynKoniec});   
        if(!visKoniec[magazynKoniec] && vis.find({magazynStart,magazynKoniec})==vis.end()){
            vis.insert({magazynStart,magazynKoniec});
            visKoniec[magazynKoniec] = 1;
            trasy.pb({magazynStart,magazynKoniec});   
        }
    }
    
    
    rep(proba,0,100){        
        int magazynStart = MAGAZYNY[rnd(0,sz(MAGAZYNY)-1)].id_magazynu;
        int magazynKoniec = MAGAZYNY[rnd(0,sz(MAGAZYNY)-1)].id_magazynu;
        if(magazynStart == magazynKoniec) continue;
        if(vis.find({magazynStart,magazynKoniec})!=vis.end()) continue;
        vis.insert({magazynStart,magazynKoniec});
        trasy.pb({magazynStart,magazynKoniec});   
    }
    return trasy;
}

bool czySkrytkaWolna(const int &id_skrytki){
    for(int i=ODBIORY.size()-1; i>=0; --i){
        const auto &[id_zle, id_skr, data_dost, data_odeb] = ODBIORY[i];
        if(id_skr == id_skrytki)
            return data_odeb!="NULL";
    }
    return true;
}
