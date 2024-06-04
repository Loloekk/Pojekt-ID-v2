package com.mygdx.sp.model.Queries.Inserts;

import com.mygdx.sp.model.Queries.Query;
import com.mygdx.sp.model.TurboString;

import java.util.List;

public class InsertPracaOsoby_start implements Query {
    @Override
    public String getQuery(List<TurboString> args) {
        String id_osoby = args.get(0).toString();
        String id_magazynu = args.get(1).toString();
        String id_stanowiska = args.get(2).toString();
        if(!check(args))
            return null;
        return "insert into praca_osoby values (" + id_osoby + "," + id_magazynu + "," + id_stanowiska + ",now(),NULL)";
    }

    @Override
    public Boolean check(List<TurboString> args) {
        return !args.get(0).toString().isEmpty()
                && !args.get(1).toString().isEmpty()
                && !args.get(2).toString().isEmpty();
    }

    @Override
    public List<String> getFields() {
        return List.of("Id osoby","Id magazynu","Id stanowiska");
    }
    @Override
    public String toString() {
        return "Rozpocznij prace osoby";
    }
}
