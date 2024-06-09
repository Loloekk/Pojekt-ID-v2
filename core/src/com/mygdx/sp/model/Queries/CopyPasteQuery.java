package com.mygdx.sp.model.Queries;

import com.mygdx.sp.model.TurboString;

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
        return !args.get(0).toString().isEmpty();
    }

    @Override
    public List<String> getFields() {
        return List.of("Komenda");
    }
    @Override
    public String toString()
    {
        return "Komenda SQL";
    }
}
