package com.mygdx.sp.model.Queries;

import com.mygdx.sp.model.TurboString;

import java.util.LinkedList;
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
        List<String> l = new LinkedList<>();
        l.add("Podaj pesel");
        return l;
    }
    @Override
    public String toString()
    {
        return name;
    }
}
