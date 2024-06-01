package com.mygdx.sp.model;

import com.mygdx.sp.model.Queries.Query;

import java.util.ArrayList;
import java.util.List;

public class GetQueries {
    public static Query[] getQuieres()
    {
        List<Query> list = new ArrayList<>();
        list.addAll(KarolDodajeQuery.getQuieres());
        list.addAll(JacekDodajeQuery.getQuieres());
        return list.toArray(new Query[0]);
    }
}
