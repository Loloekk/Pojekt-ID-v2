package com.mygdx.sp.model.Queries.Inserts;

import com.mygdx.sp.model.Queries.Query;
import com.mygdx.sp.model.TurboString;

import java.util.List;

public class InsertPrzegladyRodzajePojazdy implements Query {
    @Override
    public String getQuery(List<TurboString> args) {
        String id_rodzaj_poj = args.get(0).toString();
        String id_przegladu = args.get(1).toString();
        String czestotliwosc = args.get(2).toString();
        if(!check(args))
            return null;
        return "insert into przeglady_rod_pojazdy values (" + id_rodzaj_poj + "," + id_przegladu + "," + czestotliwosc + ")";
    }

    @Override
    public Boolean check(List<TurboString> args) {
        return !args.get(0).toString().isEmpty()
            && !args.get(1).toString().isEmpty()
            && !args.get(2).toString().isEmpty();
    }

    @Override
    public List<String> getFields() {
        return List.of("Id rodzaju pojazdu", "Id przegladu", "Czestotliwosc");
    }
    @Override
    public String toString()
    {
        return "Przypisz rodzaj przegladu do pojazdu";
    }
}
