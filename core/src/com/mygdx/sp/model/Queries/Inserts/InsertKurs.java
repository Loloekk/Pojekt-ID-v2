package com.mygdx.sp.model.Queries.Inserts;

import com.mygdx.sp.model.Queries.Query;
import com.mygdx.sp.model.TurboString;

import java.util.LinkedList;
import java.util.List;

public class InsertKurs implements Query {
    @Override
    public String getQuery(List<TurboString> args) {
        String id_pojazdu = args.get(0).toString();
        String id_kierowcy = args.get(1).toString();
        String magazyn_start = args.get(2).toString();
        String magazyn_koniec = args.get(3).toString();
        if(!check(args))
            return null;
        return "insert into kursy values (default," + id_pojazdu
                + "," + id_kierowcy + "," + magazyn_start
                + "," + magazyn_koniec + ");";
    }

    @Override
    public Boolean check(List<TurboString> args) {
        String id_pojazdu = args.get(0).toString();
        String id_kierowcy = args.get(1).toString();
        String magazyn_start = args.get(2).toString();
        String magazyn_koniec = args.get(3).toString();
        return !id_pojazdu.isEmpty() && !id_kierowcy.isEmpty() && !magazyn_start.isEmpty() && !magazyn_koniec.isEmpty();
    }

    @Override
    public List<String> getFields() {
        List<String> l = new LinkedList<>();
        l.add("Id pojazdu");
        l.add("Id kierowcy");
        l.add("Id magazynu startowego");
        l.add("Id magazynu docelowego");
        return l;
    }
    @Override
    public String toString() {
        return "Utworz kurs";
    }
}
