package com.mygdx.sp.model;

public class TurboString {
    private String value;
    public TurboString(String value){
        this.value = value;
    }
    @Override
    public boolean equals(Object o) {
        return value.equals(o);
    }
    @Override
    public String toString() {
        return value;
    }
    public String isEquals()
    {
        if(value.equals("") || value == null || value.equals(null)|| value.equals("null") || value.equals("NULL")){
            return "is null";
        }
        return "= "+ value;
    }
    public String isEqualsInCiapki() //'
    {
        if(value.equals("") || value == null || value.equals(null)|| value.equals("null") || value.equals("NULL")){
            return "is null";
        }
        return "= '"+ value+"'";
    }
    public String isEqualsInCudzyslow() //"
    {
        if(value.equals("") || value == null || value.equals(null)|| value.equals("null") || value.equals("NULL")){
            return "is null";
        }
        return "= \""+ value+"\"";
    }
    public String isNotEquals()
    {
        if(value.equals("") || value == null || value.equals(null)|| value.equals("null") || value.equals("NULL")){
            return "is not null";
        }
        return "!= "+ value;
    }
    public String isNotEqualsInCiapki() //'
    {
        if(value.equals("") || value == null || value.equals(null)|| value.equals("null") || value.equals("NULL")){
            return "is not null";
        }
        return "!= '"+ value+"'";
    }
    public String isNotEqualsInCudzyslow() //"
    {
        if(value.equals("") || value == null || value.equals(null)|| value.equals("null") || value.equals("NULL")){
            return "is not null";
        }
        return "!= \""+ value+"\"";
    }

}
