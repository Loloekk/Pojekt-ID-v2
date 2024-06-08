package com.mygdx.sp.model.Queries.Inserts;

import com.mygdx.sp.model.Queries.Query;
import com.mygdx.sp.model.TurboString;

import java.util.List;

public class InsertOdbior implements Query {
    @Override
    public String getQuery(List<TurboString> args) {
        String id_zlecenia = args.get(0).toString();
        String id_skrytki = args.get(1).toString();

        if(!check(args))
            return null;
        return "insert into odbiory values (" + id_zlecenia
                + "," + id_skrytki + ",NULL,NULL);";
    }

    @Override
    public Boolean check(List<TurboString> args) {
        String id_zlecenia = args.get(0).toString();
        String id_skrytki = args.get(1).toString();

        return !id_zlecenia.isEmpty() && !id_skrytki.isEmpty();
    }

    @Override
    public List<String> getFields() {
        return List.of("Id zlecenia", "Id kursu");
    }
    @Override
    public String toString() {
        return "Zarezerwuj skrytke";
    }
}