package com.mygdx.sp.model.Queries.Inserts;

import com.mygdx.sp.model.Queries.Query;
import com.mygdx.sp.model.TurboString;

import java.util.LinkedList;
import java.util.List;

public class InsertRodzajePrzegladow implements Query {
    @Override
    public String getQuery(List<TurboString> args) {
        String nazwa = args.get(0).toString();
        if(!check(args))
            return null;
        return "insert into rodzaje_przegladow values (default, '" + nazwa + "');";
    }

    @Override
    public Boolean check(List<TurboString> args) {
        return !args.get(0).toString().isEmpty();
    }

    @Override
    public List<String> getFields() {
        List<String> l = new LinkedList<>();
        l.add("Nazwa");
        return l;
    }
    @Override
    public String toString()
    {
        return "Dodaj rodzaj przegladu";
    }
}
