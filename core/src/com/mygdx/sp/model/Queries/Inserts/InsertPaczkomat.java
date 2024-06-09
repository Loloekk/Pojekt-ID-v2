package com.mygdx.sp.model.Queries.Inserts;

import com.mygdx.sp.model.Queries.Query;
import com.mygdx.sp.model.TurboString;

import java.util.LinkedList;
import java.util.List;

public class InsertPaczkomat implements Query {
    @Override
    public String getQuery(List<TurboString> args) {
        String lok = args.get(0).toString();
        String id_mag = args.get(1).toString();
        if(!check(args))
            return null;
        return "insert into paczkomaty values (default,'" + lok + "'," + id_mag + ");";
    }

    @Override
    public Boolean check(List<TurboString> args) {
        return !args.get(0).toString().isEmpty()
            && !args.get(1).toString().isEmpty();
    }

    @Override
    public List<String> getFields() {
        List<String> l = new LinkedList<>();
        l.add("Lokalizacja");
        l.add("Id magazynu");
        return l;
    }
    @Override
    public String toString() {
        return "Dodaj paczkomat";
    }
}
