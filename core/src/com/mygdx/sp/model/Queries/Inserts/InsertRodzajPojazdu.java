package com.mygdx.sp.model.Queries.Inserts;

import com.mygdx.sp.model.Queries.Query;
import com.mygdx.sp.model.TurboString;

import java.util.List;

public class InsertRodzajPojazdu implements Query {
    @Override
    public String getQuery(List<TurboString> args) {
        String nazwa = args.get(0).toString();
        String pojemnosc = args.get(1).toString();
        String uprawnienie = args.get(2).toString();
        if(!check(args))
            return null;
        return "insert into rodzaje_pojazdow values (default, '" + nazwa + "'," + pojemnosc + ","
                + "(SELECT id_uprawnienia FROM uprawnienia WHERE nazwa='" + uprawnienie + "'));";
    }

    @Override
    public Boolean check(List<TurboString> args) {
        return !args.get(0).toString().isEmpty()
            && !args.get(1).toString().isEmpty()
            && !args.get(2).toString().isEmpty();
    }

    @Override
    public List<String> getFields() {
        return List.of("Nazwa", "Pojemnosc", "Uprawnienie");
    }
    @Override
    public String toString()
    {
        return "Dodaj rodzaj pojazdu";
    }
}
