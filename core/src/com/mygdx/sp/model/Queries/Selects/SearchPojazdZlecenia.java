package com.mygdx.sp.model.Queries.Selects;

import com.mygdx.sp.model.Queries.Query;
import com.mygdx.sp.model.TurboString;

import java.util.LinkedList;
import java.util.List;

public class SearchPojazdZlecenia implements Query {
    @Override
    public String getQuery(List<TurboString> args) {
        String id_poj = args.get(0).toString();
        return "select id_zlecenia,id_kursu,id_kierowcy,id_nadawcy,id_odbiorcy,rozmiar,data_zapakowania " +
                "from kursy k join zlecenia_kursy zk using(id_kursu) " +
                "join zlecenia using(id_zlecenia) " +
                "where data_przyjazdu is null and id_pojazdu=" + id_poj + ";";
    }

    @Override
    public Boolean check(List<TurboString> args) {
        if(args.isEmpty()) return false;
        return !args.get(0).toString().isEmpty();
    }

    @Override
    public List<String> getFields() {
        List<String> l = new LinkedList<>();
        l.add("Id pojazdu");
        return l;
    }
    @Override
    public String toString()
    {
        return "Podaj paczki w pojezdzie";
    }
}
