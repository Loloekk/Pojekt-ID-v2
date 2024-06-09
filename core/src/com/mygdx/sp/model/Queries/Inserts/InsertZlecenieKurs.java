package com.mygdx.sp.model.Queries.Inserts;

import com.mygdx.sp.model.Queries.Query;
import com.mygdx.sp.model.TurboString;

import java.util.LinkedList;
import java.util.List;

public class InsertZlecenieKurs implements Query {
    @Override
    public String getQuery(List<TurboString> args) {
        String id_zlecenia = args.get(0).toString();
        String id_kursu = args.get(1).toString();

        if(!check(args))
            return null;
        return "insert into kursy_zlecenia values (" + id_zlecenia
                + "," + id_kursu + ",now());";
    }

    @Override
    public Boolean check(List<TurboString> args) {
        String id_zlecenia = args.get(0).toString();
        String id_kursu = args.get(1).toString();
        return !id_zlecenia.isEmpty() && !id_kursu.isEmpty();
    }

    @Override
    public List<String> getFields() {
        List<String> l = new LinkedList<>();
        l.add("Id zlecenia");
        l.add("Id kursu");
        return l;
    }
    @Override
    public String toString() {
        return "Dodaj zlecenie do kursu";
    }
}
