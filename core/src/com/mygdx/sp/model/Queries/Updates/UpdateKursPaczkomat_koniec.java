package com.mygdx.sp.model.Queries.Updates;

import com.mygdx.sp.model.Queries.Query;
import com.mygdx.sp.model.TurboString;

import java.util.List;

public class UpdateKursPaczkomat_koniec implements Query {
    @Override
    public String getQuery(List<TurboString> args) {
        String id_kursu = args.get(0).toString();
        String id_paczkomat = args.get(1).toString();
        if(!check(args))
            return null;
        return "update kursy_paczkomaty set data_odjazdu = now() WHERE id_kursu = "
                + id_kursu + " AND id_paczkomatu = " + id_paczkomat + ";";
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
        return "Odjedz od paczkomatu w ramach kursu";
    }
}
