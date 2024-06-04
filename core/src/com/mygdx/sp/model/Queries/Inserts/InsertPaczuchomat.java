package com.mygdx.sp.model.Queries.Inserts;

import com.mygdx.sp.model.Queries.Query;
import com.mygdx.sp.model.TurboString;

import java.util.List;

public class InsertPaczuchomat implements Query {
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
        return List.of("Lokalizacja", "Id magazynu");
    }
    @Override
    public String toString() {
        return "Dodaj paczkomat";
    }
}
