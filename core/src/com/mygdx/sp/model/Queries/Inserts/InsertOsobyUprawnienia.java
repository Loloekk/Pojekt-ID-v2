package com.mygdx.sp.model.Queries.Inserts;

import com.mygdx.sp.model.Queries.Query;
import com.mygdx.sp.model.TurboString;

import java.util.List;

public class InsertOsobyUprawnienia implements Query {
    @Override
    public String getQuery(List<TurboString> args){
        String id_osoby = args.get(0).toString();
        String id_uprawnienia = args.get(1).toString();
        if(!check(args))
            return null;
        return "insert into osoby_uprawnienia values (" + id_osoby + "," + id_uprawnienia + ");";
    }

    @Override
    public Boolean check(List<TurboString> args){
        return !args.get(0).toString().isEmpty()
                && !args.get(1).toString().isEmpty();
    }

    @Override
    public List<String> getFields(){
        return List.of("Id osoby","Id uprawnienia");
    }

    @Override
    public String toString(){
        return "Dodaj osobie uprawnienia";
    }
}
