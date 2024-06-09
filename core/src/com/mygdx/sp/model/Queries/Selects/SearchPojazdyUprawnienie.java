package com.mygdx.sp.model.Queries.Selects;

import com.mygdx.sp.model.Queries.Query;
import com.mygdx.sp.model.TurboString;

import java.util.List;
import java.util.LinkedList;

public class SearchPojazdyUprawnienie implements Query {
    @Override
    public String getQuery(List<TurboString> args) {
        String id_poj = args.get(0).toString();
        return "select nazwa from uprawnienia " +
                "where id_uprawnienia=getWymaganeUprawnieniePojazdu(" + id_poj + ");";
    }

    @Override
    public Boolean check(List<TurboString> args) {
        if(args.isEmpty()) return false;
        return !args.get(0).toString().isEmpty();
    }

    @Override
    public List<String> getFields() {
        List<String> l = new LinkedList<>();
        l.add("Id pojazdu");
        return l;
    }
    @Override
    public String toString()
    {
        return "Podaj wymagane uprawnienie do prowadzenia pojazdu";
    }
}
