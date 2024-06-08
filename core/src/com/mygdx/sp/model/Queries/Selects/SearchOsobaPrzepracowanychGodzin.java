package com.mygdx.sp.model.Queries.Selects;

import com.mygdx.sp.model.Queries.Query;
import com.mygdx.sp.model.TurboString;

import java.util.List;

public class SearchOsobaPrzepracowanychGodzin implements Query {
    @Override
    public String getQuery(List<TurboString> args) {
        String id = args.get(0).toString();
        return "select EXTRACT(HOUR FROM SUM(data_zakonczenia-data_rozpoczecia))" +
                " from praca_osoby where id_osoby=" + id +
                " group by id_osoby;";
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
        return "Ilosc przepracowanych godzin";
    }
}
