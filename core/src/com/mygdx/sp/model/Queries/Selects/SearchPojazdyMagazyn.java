package com.mygdx.sp.model.Queries.Selects;

import com.mygdx.sp.model.Queries.Query;
import com.mygdx.sp.model.TurboString;

import java.util.LinkedList;
import java.util.List;

public class SearchPojazdyMagazyn implements Query {
    @Override
    public String getQuery(List<TurboString> args) {
        String id_mag = args.get(0).toString();
        return "select * from pojazdy where getMagazynPojazdu(id_pojazdu)=" + id_mag + ";";
    }

    @Override
    public Boolean check(List<TurboString> args) {
        if(args.isEmpty()) return false;
        return !args.get(0).toString().isEmpty();
    }

    @Override
    public List<String> getFields() {
        List<String> l = new LinkedList<>();
        l.add("Id magazynu");
        return l;
    }
    @Override
    public String toString()
    {
        return "Podaj pojazdy w magazynie";
    }
}
