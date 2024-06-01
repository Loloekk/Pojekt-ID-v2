package com.mygdx.sp.model.Queries;


import com.mygdx.sp.model.TurboString;

import java.util.List;

public interface Query {
    String getQuery(List<TurboString> args);
    Boolean check(List<TurboString> args);
    List<String> getFields();
    String toString();
}
