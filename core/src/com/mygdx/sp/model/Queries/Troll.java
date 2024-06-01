package com.mygdx.sp.model.Queries;

import java.util.List;

public class Troll implements Query {
    String name = "Osoby o danym peselu";
    int size = 1;

    @Override
    public String getQuery(List<TurboString> args) {
        if(!check(args))return null;
        return "select * from osoby where pesel "+args.get(0).isEqualsInCiapki()+";";
    }

    @Override
    public Boolean check(List<TurboString> args) {
        if(args.size()!=size) return false;
        return true;
    }

    @Override
    public List<String> getFields() {
        return List.of("Podaj pesel");
    }
    @Override
    public String toString()
    {
        return name;
    }
}
