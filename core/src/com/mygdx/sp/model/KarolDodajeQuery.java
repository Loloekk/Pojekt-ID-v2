package com.mygdx.sp.model;

import com.mygdx.sp.model.Queries.CopyPasteQuery;
import com.mygdx.sp.model.Queries.GetWholeTable;
import com.mygdx.sp.model.Queries.Query;

import java.util.ArrayList;
import java.util.List;

public class KarolDodajeQuery {
    public static List<Query> getQuieres()
    {
        List<Query> list = new ArrayList<>();
        list.add(new GetWholeTable());
        list.add(new CopyPasteQuery());
        /////TODO Tu dodajemy kolejne zapytania dla przykładu są trzy identyczne
        return list;
    }
}
