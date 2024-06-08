package com.mygdx.sp.model.Queries.Selects;

import com.mygdx.sp.model.Queries.Query;
import com.mygdx.sp.model.TurboString;

import java.util.List;

public class SearchOsobaCzyPracuje implements Query {
    @Override
    public String getQuery(List<TurboString> args) {
        String id = args.get(0).toString();
        return "SELECT (CASE WHEN t.data_zakonczenia IS NULL THEN 'Jest w pracy' " +
                "ELSE 'Nie jest w pracy' END) as \"Stan\" " +
                "FROM (select * from praca_osoby where id_osoby=" + id + " " +
                "order by data_rozpoczecia desc limit 1) t;";
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
        return "Czy osoba jest w pracy";
    }
}
