package com.mygdx.sp.model.Queries.Selects;

import com.mygdx.sp.model.Queries.Query;
import com.mygdx.sp.model.TurboString;

import java.util.List;

public class SearchKursyAktywne implements Query {
    @Override
    public String getQuery(List<TurboString> args) {
        return "select id_kursu,id_pojazdu,id_kierowcy,magazyn_start,magazyn_docelowy,data_wyjazdu " +
                "from kursy where data_przyjazdu is not null;";
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
        return "Podaj aktywne kursy";
    }
}
