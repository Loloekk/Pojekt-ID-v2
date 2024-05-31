package com.mygdx.sp.model;

import java.util.ArrayList;
import java.util.List;

public class getQuieres {
    public static Query[] getQuieres()
    {
        List<Query> list = new ArrayList<>();
        list.add(new getWholeTable());
        list.add(new getWholeTable());
        list.add(new getWholeTable());
        /////TODO Tu dodajemy kolejne zapytania dla przykładu są trzy identyczne
        return list.toArray(new Query[0]);
    }
}
