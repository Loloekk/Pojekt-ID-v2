package com.mygdx.sp.model.Queries.Updates;

import com.mygdx.sp.model.Queries.Query;
import com.mygdx.sp.model.TurboString;

import java.util.LinkedList;
import java.util.List;

public class UpdateOdbior_dostarczenie implements Query {
    @Override
    public String getQuery(List<TurboString> args) {
        String id_zlecenia = args.get(0).toString();
        if(!check(args))
            return null;
        return "update odbiory set data_dostarczenia = now() WHERE id_zlecenia = "
                + id_zlecenia + ";";
    }

    @Override
    public Boolean check(List<TurboString> args) {
        String id_zlecenia = args.get(0).toString();
        return !id_zlecenia.isEmpty();
    }

    @Override
    public List<String> getFields() {
        List<String> l = new LinkedList<>();
        l.add("Id zlecenia");
        return l;
    }
    @Override
    public String toString() {
        return "Dostarcz zlecenie";
    }
}
