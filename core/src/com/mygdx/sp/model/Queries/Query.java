package com.mygdx.sp.model.Queries;


import java.util.List;

public interface Query {
    String getQuery(List<String> args);
    Boolean check(List<String> args);
    List<String> getFields();
    String toString();
}
