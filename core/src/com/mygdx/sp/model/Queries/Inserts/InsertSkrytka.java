package com.mygdx.sp.model.Queries.Inserts;

import com.mygdx.sp.model.Queries.Query;
import com.mygdx.sp.model.TurboString;

import java.util.List;

public class InsertSkrytka implements Query {
    @Override
    public String getQuery(List<TurboString> args) {
        String id_pacz = args.get(0).toString();
        String roz = args.get(1).toString();
        if(!check(args))
            return null;
        return "insert into skrytki values (default," + id_pacz + "," + roz + ");";
    }

    @Override
    public Boolean check(List<TurboString> args) {
        String id_pacz = args.get(0).toString();
        String roz = args.get(1).toString();
        if(id_pacz.isEmpty() || roz.isEmpty())
            return false;
        return roz.equals("1") || roz.equals("2") || roz.equals("3");
    }

    @Override
    public List<String> getFields() {
        return List.of("Id paczkomatu", "Rozmiar");
    }
    @Override
    public String toString() {
        return "Dodaj skrytke";
    }
}
