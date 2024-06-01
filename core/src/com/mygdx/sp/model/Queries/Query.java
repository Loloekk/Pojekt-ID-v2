package com.mygdx.sp.model.Queries;


import java.util.List;

public interface Query {
    String getQuery(List<TurboString> args);
    Boolean check(List<TurboString> args);
    List<String> getFields();
    String toString();
}
