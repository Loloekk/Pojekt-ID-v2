package com.mygdx.sp.model.Queries.Selects;

import com.mygdx.sp.model.Queries.Query;
import com.mygdx.sp.model.TurboString;

import java.util.LinkedList;
import java.util.List;

public class SearchUprawnieniaOsoby implements Query {
    @Override
    public String getQuery(List<TurboString> args) {
        String id = args.get(0).toString();
        return "select u.nazwa from osoby o join osoby_uprawnienia ou on o.id_osoby=ou.id_osoby\n" +
                "join uprawnienia u on u.id_uprawnienia=ou.id_uprawnienia\n" +
                "where o.id_osoby=" + id + ";";
    }

    @Override
    public Boolean check(List<TurboString> args) {
        if(args.isEmpty()) return false;
        return !args.get(0).toString().isEmpty();
    }

    @Override
    public List<String> getFields() {
        List<String> l = new LinkedList<>();
        l.add("Id osoby");
        return l;
    }
    @Override
    public String toString()
    {
        return "Podaj uprawnienia osoby";
    }
}
