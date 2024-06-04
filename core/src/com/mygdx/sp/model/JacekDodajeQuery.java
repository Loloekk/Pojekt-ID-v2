package com.mygdx.sp.model;

import com.mygdx.sp.model.Queries.Inserts.*;
import com.mygdx.sp.model.Queries.Query;
import com.mygdx.sp.model.Queries.Updates.*;

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
        return list;
    }
}
