package com.mygdx.sp.model;

import com.mygdx.sp.model.Queries.Inserts.*;
import com.mygdx.sp.model.Queries.Query;
import com.mygdx.sp.model.Queries.Updates.*;
import com.mygdx.sp.model.Queries.Selects.*;

import java.util.ArrayList;
import java.util.List;

public class JacekDodajeQuery {
    public static List<Query> getQuieres()
    {
        List<Query> list = new ArrayList<>();
        list.add(new InsertOsoba());
        list.add(new InsertStanowisko());
        list.add(new InsertStanowiskaOsoby());
        list.add(new InsertPracaOsoby_start());
        list.add(new UpdatePracaOsoby_koniec());
        list.add(new InsertOsobyUprawnienia());
        list.add(new InsertUprawnienia());
        list.add(new InsertRodzajPojazdu());
        list.add(new InsertRodzajePrzegladow());
        list.add(new InsertPrzegladyRodzajePojazdy());
        list.add(new InsertPojazd());
        list.add(new InsertSerwis_start());
        list.add(new UpdateSerwis_koniec());
        list.add(new InsertUsterka_start());
        list.add(new UpdateUsterka_startNaprawa());
        list.add(new UpdateUsterka_koniec());
        list.add(new InsertMagazyn());
        list.add(new InsertPaczuchomat());
        list.add(new InsertSkrytka());
        list.add(new InsertZlecenie());
        list.add(new InsertNadanie());
        list.add(new InsertKurs());
        list.add(new UpdateKurs_start());
        list.add(new UpdateKurs_koniec());
        list.add(new InsertZlecenieKurs());
        list.add(new InsertKursPaczuchomat());
        list.add(new UpdateKursPaczuchomat_koniec());
        list.add(new InsertZlecenieMagazyn());
        list.add(new InsertDeklaracjaWypakowania());
        list.add(new InsertOdbior());
        list.add(new UpdateOdbior_dostarczenie());
        list.add(new UpdateOdbior_odbior());
        // Select'y
        list.add(new SearchOsoba());
        list.add(new SearchUprawnieniaOsoby());
        list.add(new SearchStanowiskaOsoby());
        list.add(new SearchOsobaPrzepracowanychGodzin());
        list.add(new SearchOsobaCzyPracuje());
        list.add(new SearchOsobyNaStanowisku());
        list.add(new SearchOsobyWMagazynie());
        list.add(new SearchPojazdyMagazynSprawne());
        list.add(new SearchPojazdyMagazyn());
        list.add(new SearchPojazdyUprawnienie());
        return list;
    }
}
