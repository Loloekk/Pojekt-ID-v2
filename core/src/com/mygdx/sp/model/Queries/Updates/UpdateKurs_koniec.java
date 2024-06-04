package com.mygdx.sp.model.Queries.Updates;

import com.mygdx.sp.model.Queries.Query;
import com.mygdx.sp.model.TurboString;

import java.util.List;

public class UpdateKurs_koniec implements Query {
    @Override
    public String getQuery(List<TurboString> args) {
        String id_kursu = args.get(0).toString();
        if(!check(args))
            return null;
        return "update kursy set data_przyjazdu = now() WHERE id_kursu = " + id_kursu + ";";
    }

    @Override
    public Boolean check(List<TurboString> args) {
        String id_kursu = args.get(0).toString();
        return !id_kursu.isEmpty();
    }

    @Override
    public List<String> getFields() {
        return List.of("Id kursu");
    }
    @Override
    public String toString() {
        return "Zakoncz kurs";
    }
}
