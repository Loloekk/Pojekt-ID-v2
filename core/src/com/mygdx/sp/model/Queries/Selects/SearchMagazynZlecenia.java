package com.mygdx.sp.model.Queries.Selects;

import com.mygdx.sp.model.Queries.Query;
import com.mygdx.sp.model.TurboString;

import java.util.List;

public class SearchMagazynZlecenia implements Query {
    @Override
    public String getQuery(List<TurboString> args) {
        String id_mag = args.get(0).toString();
        return "select * from zlecenia where getMagazynZlecenia(id_zlecenia)=" + id_mag + ";";
    }

    @Override
    public Boolean check(List<TurboString> args) {
        if(args.isEmpty()) return false;
        return !args.get(0).toString().isEmpty();
    }

    @Override
    public List<String> getFields() {
        return List.of("Id magazynu");
    }
    @Override
    public String toString()
    {
        return "Podaj paczki w magazynie";
    }
}
