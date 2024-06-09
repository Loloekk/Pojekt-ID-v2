package com.mygdx.sp.model.Queries.Inserts;

import com.mygdx.sp.model.Queries.Query;
import com.mygdx.sp.model.TurboString;

import java.util.LinkedList;
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
        List<String> l = new LinkedList<>();
        l.add("Nazwa");
        l.add("Pojemnosc");
        l.add("Uprawnienie");
        return l;
    }
    @Override
    public String toString()
    {
        return "Dodaj rodzaj pojazdu";
    }
}
