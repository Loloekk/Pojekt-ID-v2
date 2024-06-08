package com.mygdx.sp.model.Queries.Selects;

import com.mygdx.sp.model.Queries.Query;
import com.mygdx.sp.model.TurboString;

import java.util.List;

public class SearchPaczkiOczekujaceOdbiorcy implements Query {
    @Override
    public String getQuery(List<TurboString> args) {
        return "select id_zlecenia,id_nadawcy,id_odbiorcy,data_zlozenia,data_dostarczenia,id_skrytki " +
                "from odbiory o join zlecenia z using(id_zlecenia) where data_dostarczenia is not null " +
                "and data_odebrania is null;";
    }

    @Override
    public Boolean check(List<TurboString> args) {
        return true;
    }

    @Override
    public List<String> getFields() {
        return List.of();
    }
    @Override
    public String toString()
    {
        return "Podaj nieodebrane przez odbiorcow paczki";
    }
}
