package net.brucejia.learning.maps;

import java.util.Collections;
import java.util.HashMap;
import java.util.Map;

public class Main {


    public static void main(String [] args) {

        HashMap<String, String> jobOwnerCache = new HashMap<String, String>(1000);

        jobOwnerCache.put("job_id_1", "owner_id_1");
        jobOwnerCache.put("job_id_2", "owner_id_2");

        assert jobOwnerCache.containsKey("job_id_1");
        assert jobOwnerCache.containsValue("owner_id_2");

        final int size = jobOwnerCache.size();
        String ownerId = jobOwnerCache.get("job_id_2");

        Map<String, String> syncMap = Collections.synchronizedMap(jobOwnerCache);

        final int size2 = syncMap.size();
    }
}
