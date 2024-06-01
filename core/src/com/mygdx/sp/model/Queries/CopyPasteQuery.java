package com.mygdx.sp.model.Queries;

import java.util.List;

public class CopyPasteQuery implements Query {
    @Override
    public String getQuery(List<TurboString> args) {
        if(!check(args))return null;
        return args.get(0)+";";
    }

    @Override
    public Boolean check(List<TurboString> args) {
        if(args.size()!=1) return false;
        if(args.get(0).equals("")) return false;
        return true;
    }

    @Override
    public List<String> getFields() {
        return List.of("Podaj zapytanie");
    }
    @Override
    public String toString()
    {
        return "Zapytanie";
    }
}
