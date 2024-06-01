package com.mygdx.sp.model.Queries;

import com.mygdx.sp.model.TurboString;

import java.util.List;

public class GetWholeTable implements Query {
    String name = "Podaj tabele";
    int size = 1;

    @Override
    public String getQuery(List<TurboString> args) {
        if(!check(args))return null;
        return "select * from "+args.get(0)+";";
    }

    @Override
    public Boolean check(List<TurboString> args) {
        if(args.size()!=size) return false;
        if(args.get(0).equals("")) return false;
        return true;
    }

    @Override
    public List<String> getFields() {
        return List.of("Podaj nazwe tabeli");
    }
    @Override
    public String toString()
    {
        return name;
    }
}
