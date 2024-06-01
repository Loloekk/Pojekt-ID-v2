package com.mygdx.sp.model;

import java.util.ArrayList;
import java.util.List;

public class GetQueries {
    public static Query[] getQuieres()
    {
        List<Query> list = new ArrayList<>();
        list.addAll(KarolDodajeQuery.getQuieres());
        list.addAll(JacekDodajeQuery.getQuieres());
        /////TODO Tu dodajemy kolejne zapytania dla przykładu są trzy identyczne
        return list.toArray(new Query[0]);
    }
}
