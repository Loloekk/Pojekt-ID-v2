package com.mygdx.sp.model;

import com.mygdx.sp.model.Queries.CopyPasteQuery;
import com.mygdx.sp.model.Queries.GetWholeTable;
import com.mygdx.sp.model.Queries.Query;
import com.mygdx.sp.model.Queries.Troll;

import java.util.ArrayList;
import java.util.List;

public class KarolDodajeQuery {
    public static List<Query> getQuieres()
    {
        List<Query> list = new ArrayList<>();
        list.add(new GetWholeTable());
        list.add(new CopyPasteQuery());
        list.add(new Troll());
        /////TODO Tu dodajemy kolejne zapytania
        return list;
    }
}
