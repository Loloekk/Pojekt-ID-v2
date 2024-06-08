package com.mygdx.sp.model.Queries.Inserts;

import com.mygdx.sp.model.Queries.Query;
import com.mygdx.sp.model.TurboString;

import java.util.List;

public class InsertKursPaczkomat implements Query {
    @Override
    public String getQuery(List<TurboString> args) {
        String id_kursu = args.get(0).toString();
        String id_paczkomat = args.get(1).toString();
        if(!check(args))
            return null;
        return "insert into kursy_paczkomaty values(" + id_kursu
                + "," + id_paczkomat + ",now(),NULL);";
    }

    @Override
    public Boolean check(List<TurboString> args) {
        String id_kursu = args.get(0).toString();
        String id_paczkomat = args.get(1).toString();
        return !id_kursu.isEmpty() && !id_paczkomat.isEmpty();
    }

    @Override
    public List<String> getFields() {
        return List.of("Id kursu", "Id paczkomatu");
    }
    @Override
    public String toString() {
        return "Podjedz do paczkomatu w ramach kursu";
    }
}
