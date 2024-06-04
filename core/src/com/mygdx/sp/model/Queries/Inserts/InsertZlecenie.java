package com.mygdx.sp.model.Queries.Inserts;

import com.mygdx.sp.model.Queries.Query;
import com.mygdx.sp.model.TurboString;

import java.util.List;

public class InsertZlecenie implements Query {
    @Override
    public String getQuery(List<TurboString> args) {
        String id_nadawcy = args.get(0).toString();
        String id_odbiorcy = args.get(1).toString();
        String id_paczkomat_odbiorcy = args.get(2).toString();
        String rozmiar = args.get(3).toString();

        if(!check(args))
            return null;
        return "insert into zlecenia values (default," + id_nadawcy
                + "," + id_odbiorcy + "," + id_paczkomat_odbiorcy + ",now(),"
                + rozmiar + ");";
    }

    @Override
    public Boolean check(List<TurboString> args) {
        String id_nadawcy = args.get(0).toString();
        String id_odbiorcy = args.get(1).toString();
        String id_paczkomat_odbiorcy = args.get(2).toString();
        String rozmiar = args.get(3).toString();
        if(id_nadawcy.isEmpty() || id_odbiorcy.isEmpty() || id_paczkomat_odbiorcy.isEmpty() || rozmiar.isEmpty())
            return false;
        return rozmiar.equals("1") || rozmiar.equals("2") || rozmiar.equals("3");
    }

    @Override
    public List<String> getFields() {
        return List.of("Id nadawcy", "Id odbiorcy", "Id paczkomatu odbiorcy", "Rozmiar");
    }
    @Override
    public String toString() {
        return "Dodaj zlecenie";
    }
}
