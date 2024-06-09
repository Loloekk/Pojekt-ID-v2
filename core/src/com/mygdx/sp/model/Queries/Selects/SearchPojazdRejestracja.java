package com.mygdx.sp.model.Queries.Selects;

import com.mygdx.sp.model.Queries.Query;
import com.mygdx.sp.model.TurboString;

import java.util.List;
import java.util.LinkedList;

public class SearchPojazdRejestracja implements Query {
    @Override
    public String getQuery(List<TurboString> args) {
        String nr_rej = args.get(0).toString();
        return "select id_pojazdu as \"Id\",rp.nazwa as \"Model\",pojemnosc as \"Pojemnosc\",u.nazwa as \"Wymagane uprawnienie\" "
           + "from pojazdy p join rodzaje_pojazdow rp using(id_rodzaju) "
           + "join uprawnienia u using(id_uprawnienia) where nr_rejestracyjny='" + nr_rej + "';";
    }

    @Override
    public Boolean check(List<TurboString> args) {
        if(args.isEmpty()) return false;
        return !args.get(0).toString().isEmpty();
    }

    @Override
    public List<String> getFields() {
        List<String> l = new LinkedList<>();
        l.add("Numer rejestracyjny");
        return l;
    }
    @Override
    public String toString()
    {
        return "Wyszukaj pojazd";
    }
}
