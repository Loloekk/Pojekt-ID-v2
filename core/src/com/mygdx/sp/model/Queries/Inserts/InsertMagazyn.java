package com.mygdx.sp.model.Queries.Inserts;

import com.mygdx.sp.model.Queries.Query;
import com.mygdx.sp.model.TurboString;

import java.util.List;

public class InsertMagazyn implements Query {
    @Override
    public String getQuery(List<TurboString> args) {
        String lok = args.get(0).toString();
        if(!check(args))
            return null;
        return "insert into magazyny values (default,'" + lok + "');";
    }

    @Override
    public Boolean check(List<TurboString> args) {
        return !args.get(0).toString().isEmpty();
    }

    @Override
    public List<String> getFields() {
        return List.of("Lokalizacja");
    }
    @Override
    public String toString() {
        return "Dodaj magazyn";
    }
}