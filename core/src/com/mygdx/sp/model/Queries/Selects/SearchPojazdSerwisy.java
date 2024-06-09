package com.mygdx.sp.model.Queries.Selects;

import com.mygdx.sp.model.Queries.Query;
import com.mygdx.sp.model.TurboString;

import java.util.LinkedList;
import java.util.List;

public class SearchPojazdSerwisy implements Query {
    @Override
    public String getQuery(List<TurboString> args) {
        String id_poj = args.get(0).toString();
        return "select czestotliwosc||' miesiecy' as \"czestotliwosc\",nazwa," +
                "GREATEST(0,EXTRACT(DAY FROM lastSerwis(" + id_poj + ",id_przegladu)+(czestotliwosc * interval'1 month') - now())) " +
                "as \"Dni do wymaganego serwisu\" from (select * from pojazdy where id_pojazdu=" + id_poj + ") po\n" +
                "join przeglady_rod_pojazdy prp using(id_rodzaju)\n" +
                "join rodzaje_przegladow using (id_przegladu);";
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
        return "Podaj stan serwisow danego pojazdu";
    }
}
