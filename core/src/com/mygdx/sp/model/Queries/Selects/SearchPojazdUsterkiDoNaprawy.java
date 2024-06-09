package com.mygdx.sp.model.Queries.Selects;

import com.mygdx.sp.model.Queries.Query;
import com.mygdx.sp.model.TurboString;

import java.util.List;
import java.util.LinkedList;

public class SearchPojazdUsterkiDoNaprawy implements Query {
    @Override
    public String getQuery(List<TurboString> args) {
        String id_poj = args.get(0).toString();
        return "select opis,data_wystapienia,data_rozpoczecia_naprawy from usterki\n" +
                "where id_pojazdu=" + id_poj + "\n" +
                "and data_zakonczenia_naprawy is null;";
    }

    @Override
    public Boolean check(List<TurboString> args) {
        if(args.isEmpty()) return false;
        return !args.get(0).toString().isEmpty();
    }

    @Override
    public List<String> getFields() {
        List<String> l = new LinkedList<>();
        l.add("Id pojazdu");
        return l;
    }
    @Override
    public String toString()
    {
        return "Podaj nienaprawione usterki pojazdu";
    }
}
