package com.mygdx.sp.model.Queries;

import com.mygdx.sp.model.TurboString;

import java.util.List;

public class GetWholeTable implements Query {
    String name = "Wypisz zawartosc tabeli";
    int size = 1;

    @Override
    public String getQuery(List<TurboString> args) {
        if(!check(args))return null;
        return "select * from "+args.get(0)+";";
    }

    @Override
    public Boolean check(List<TurboString> args) {
        if(args.size()!=size) return false;
        return !args.get(0).toString().isEmpty();
    }

    @Override
    public List<String> getFields() {
        return List.of("Nazwa tabeli");
    }
    @Override
    public String toString()
    {
        return name;
    }
}
