package com.mygdx.sp.model.Queries.Inserts;

import com.mygdx.sp.model.Queries.Query;
import com.mygdx.sp.model.TurboString;

import java.util.List;

public class InsertZlecenieMagazyn implements Query {
    @Override
    public String getQuery(List<TurboString> args) {
        String id_zlecenia = args.get(0).toString();
        String id_magazynu = args.get(1).toString();

        if(!check(args))
            return null;
        return "insert into zlecenia_magazyny values (" + id_zlecenia
                + "," + id_magazynu + ",now());";
    }

    @Override
    public Boolean check(List<TurboString> args) {
        String id_zlecenia = args.get(0).toString();
        String id_magazynu = args.get(1).toString();
        return !id_zlecenia.isEmpty() && !id_magazynu.isEmpty();
    }

    @Override
    public List<String> getFields() {
        return List.of("Id zlecenia", "Id magazynu");
    }
    @Override
    public String toString() {
        return "Zaladuj zlecenie do magazynu";
    }
}
