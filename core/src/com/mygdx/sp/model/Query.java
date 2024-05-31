package com.mygdx.sp.model;


import java.util.List;

public interface Query {
    String getQuery(List<String> args);
    Boolean check(List<String> args);
    List<String> getFields();
    String toString();
}
