package com.mygdx.sp.model.Queries.Inserts;

import com.mygdx.sp.model.Queries.Query;
import com.mygdx.sp.model.TurboString;

import java.util.LinkedList;
import java.util.List;

public class InsertPojazd implements Query {
    @Override
    public String getQuery(List<TurboString> args) {
        String nr_rej = args.get(0).toString();
        String id_rodz = args.get(1).toString();
        if(!check(args))
            return null;
        return "insert into pojazdy values (default,'" + nr_rej + "'," + id_rodz + ");";
    }

    @Override
    public Boolean check(List<TurboString> args) {
        return !args.get(0).toString().isEmpty()
            && !args.get(1).toString().isEmpty();
    }

    @Override
    public List<String> getFields() {
        List<String> l = new LinkedList<>();
        l.add("Nr rejestracyjny");
        l.add("Id rodzaju");
        return l;
    }
    @Override
    public String toString() {
        return "Dodaj nowy pojazd";
    }
}
