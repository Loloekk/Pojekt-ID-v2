package com.mygdx.sp.model;

import com.mygdx.sp.model.Queries.GetWholeTable;
import com.mygdx.sp.model.Queries.Query;

import java.util.ArrayList;
import java.util.List;

public class JacekDodajeQuery {
    public static List<Query> getQuieres()
    {
        List<Query> list = new ArrayList<>();
        list.add(new GetWholeTable());
        /////TODO Tu dodajemy kolejne zapytania dla przykładu są trzy identyczne
        return list;
    }
}
