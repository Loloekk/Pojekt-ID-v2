package com.mygdx.sp.model.Queries.Selects;

import com.mygdx.sp.model.Queries.Query;
import com.mygdx.sp.model.TurboString;

import java.util.List;
import java.util.LinkedList;

public class SearchOsoba implements Query {
    @Override
    public String getQuery(List<TurboString> args) {
        StringBuilder str = new StringBuilder("select * from osoby");
        String id = args.get(0).toString();
        String pesel = args.get(1).toString();
        String imie = args.get(2).toString();
        String nazw = args.get(3).toString();
        String mail = args.get(4).toString();
        String tel = args.get(5).toString();
        if(!id.isEmpty() || !pesel.isEmpty() || !imie.isEmpty() || !nazw.isEmpty() || !mail.isEmpty() || !tel.isEmpty())
            str.append(" where");
        boolean isFirst = true;
        if(!id.isEmpty()){
            if(isFirst) isFirst = false;
            else  str.append(" and");
            str.append(" id_osoby="+id);
        }
        if(!pesel.isEmpty()){
            if(isFirst) isFirst = false;
            else  str.append(" and");
            str.append(" pesel='"+pesel+"'");
        }
        if(!imie.isEmpty()){
            if(isFirst) isFirst = false;
            else  str.append(" and");
            str.append(" imie='"+imie+"'");
        }
        if(!nazw.isEmpty()){
            if(isFirst) isFirst = false;
            else  str.append(" and");
            str.append(" nazwisko='"+nazw+"'");
        }
        if(!mail.isEmpty()){
            if(isFirst) isFirst = false;
            else  str.append(" and");
            str.append(" email='"+mail+"'");
        }
        if(!tel.isEmpty()){
            if(isFirst) isFirst = false;
            else  str.append(" and");
            str.append(" nr_tel='"+tel+"'");
        }
        str.append(";");
        return str.toString();
    }

    @Override
    public Boolean check(List<TurboString> args) {
        return true;
    }

    @Override
    public List<String> getFields() {
        List<String> l = new LinkedList<>();
        l.add("Id osoby");
        l.add("PESEL");
        l.add("Imie");
        l.add("Nazwisko");
        l.add("E-mail");
        l.add("Telefon");
        return l;
    }
    @Override
    public String toString()
    {
        return "Wyszukaj osoby spelniajace kryteria";
    }
}
