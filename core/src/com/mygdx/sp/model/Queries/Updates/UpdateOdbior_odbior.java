package com.mygdx.sp.model.Queries.Updates;

import com.mygdx.sp.model.Queries.Query;
import com.mygdx.sp.model.TurboString;

import java.util.List;

public class UpdateOdbior_odbior implements Query {
    @Override
    public String getQuery(List<TurboString> args) {
        String id_zlecenia = args.get(0).toString();
        if(!check(args))
            return null;
        return "update odbiory set data_odebrania = now() WHERE id_zlecenia = "
                + id_zlecenia + ";";
    }

    @Override
    public Boolean check(List<TurboString> args) {
        String id_zlecenia = args.get(0).toString();
        return !id_zlecenia.isEmpty();
    }

    @Override
    public List<String> getFields() {
        return List.of("Id zlecenia");
    }
    @Override
    public String toString() {
        return "Odbior zlecenia przez klienta";
    }
}
