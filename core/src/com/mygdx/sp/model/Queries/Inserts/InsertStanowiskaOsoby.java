package com.mygdx.sp.model.Queries.Inserts;

import com.mygdx.sp.model.Queries.Query;
import com.mygdx.sp.model.TurboString;

import java.util.LinkedList;
import java.util.List;

public class InsertStanowiskaOsoby implements Query {
    @Override
    public String getQuery(List<TurboString> args) {
        String id_osoby = args.get(0).toString();
        String id_stanowiska = args.get(1).toString();
        if(!check(args))
            return null;
        return "insert into stanowiska_osoby values (" + id_osoby + "," + id_stanowiska + ");";
    }

    @Override
    public Boolean check(List<TurboString> args) {
        return !args.get(0).toString().isEmpty()
                && !args.get(1).toString().isEmpty();
    }

    @Override
    public List<String> getFields() {
        List<String> l = new LinkedList<>();
        l.add("Id osoby");
        l.add("Id stanowiska");
        return l;
    }
    @Override
    public String toString()
    {
        return "Przydziel osobie stanowisko";
    }
}
