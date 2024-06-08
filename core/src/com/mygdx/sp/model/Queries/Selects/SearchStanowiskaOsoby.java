package com.mygdx.sp.model.Queries.Selects;

import com.mygdx.sp.model.Queries.Query;
import com.mygdx.sp.model.TurboString;

import java.util.List;

public class SearchStanowiskaOsoby implements Query {
    @Override
    public String getQuery(List<TurboString> args) {
        String id = args.get(0).toString();
        return "select s.nazwa from osoby o join stanowiska_osoby so on o.id_osoby=so.id_osoby\n" +
                "join stanowiska s on s.id_stanowiska=so.id_stanowiska\n" +
                "where o.id_osoby=" + id + ";";
    }

    @Override
    public Boolean check(List<TurboString> args) {
        if(args.isEmpty()) return false;
        return !args.get(0).toString().isEmpty();
    }

    @Override
    public List<String> getFields() {
        return List.of("Id osoby");
    }
    @Override
    public String toString()
    {
        return "Podaj stanowiska osoby";
    }
}
