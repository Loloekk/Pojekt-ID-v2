package com.mygdx.sp.model.Queries.Selects;

import com.mygdx.sp.model.Queries.Query;
import com.mygdx.sp.model.TurboString;

import java.util.List;

public class SearchPojazdyMagazynSprawne implements Query {
    @Override
    public String getQuery(List<TurboString> args) {
        String id_mag = args.get(0).toString();
        return "select * from pojazdy where getMagazynPojazdu(id_pojazdu)=" + id_mag + " " +
                "AND NOT isSerwisedPojazdu(id_pojazdu) " +
                "AND NOT isUsterkiPojazdu(id_pojazdu) " +
                "AND NOT needSerwis(id_pojazdu);";
    }

    @Override
    public Boolean check(List<TurboString> args) {
        if(args.isEmpty()) return false;
        return !args.get(0).toString().isEmpty();
    }

    @Override
    public List<String> getFields() {
        return List.of("Id magazynu");
    }
    @Override
    public String toString()
    {
        return "Podaj sprawne pojazdy w magazynie";
    }
}
