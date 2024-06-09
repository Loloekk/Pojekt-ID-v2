package com.mygdx.sp.model.Queries.Selects;

import com.mygdx.sp.model.Queries.Query;
import com.mygdx.sp.model.TurboString;

import java.util.LinkedList;
import java.util.List;

public class SearchOsobyNaStanowisku implements Query {
    @Override
    public String getQuery(List<TurboString> args) {
        String stanowisko = args.get(0).toString();
        return "select o.id_osoby,o.pesel,o.imie,o.nazwisko,o.email,o.nr_tel from stanowiska_osoby so\n" +
                "JOIN osoby o on o.id_osoby=so.id_osoby\n" +
                "JOIN stanowiska s ON s.id_stanowiska=so.id_stanowiska\n" +
                "WHERE s.nazwa='" + stanowisko + "';";
    }

    @Override
    public Boolean check(List<TurboString> args) {
        if(args.isEmpty()) return false;
        return !args.get(0).toString().isEmpty();
    }

    @Override
    public List<String> getFields() {
        List<String> l = new LinkedList<>();
        l.add("Nazwa stanowiska");
        return l;
    }
    @Override
    public String toString()
    {
        return "Podaj osoby na stanowisku";
    }
}
