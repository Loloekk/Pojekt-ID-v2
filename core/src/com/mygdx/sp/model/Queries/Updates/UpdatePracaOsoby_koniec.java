package com.mygdx.sp.model.Queries.Updates;

import com.mygdx.sp.model.Queries.Query;
import com.mygdx.sp.model.TurboString;

import java.util.List;

public class UpdatePracaOsoby_koniec implements Query {
    @Override
    public String getQuery(List<TurboString> args) {
        String id_osoby = args.get(0).toString();
        if(!check(args))
            return null;
        return "update praca_osoby set data_zakonczenia = now() " +
                "wher id_osoby= " + id_osoby + " and data_zakonczenia = null";
    }

    @Override
    public Boolean check(List<TurboString> args) {
        return !args.get(0).toString().isEmpty();
    }

    @Override
    public List<String> getFields() {
        return List.of("Id osoby");
    }
    @Override
    public String toString() {
        return "Zakoncz prace osoby";
    }
}
