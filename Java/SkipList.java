package RPC;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.UUID;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.ConcurrentSkipListMap;

/**
 * Created by arthur.xw on 2015/6/24.
 */
public class SkipList {
    public static List<Thread> threads = new ArrayList<>();

    public static void doIt(final Map<String, String> map) {
        threads.clear();
        map.put("xxx", "xxx");
        for (int i = 0; i < 2; i++) {
            threads.add(new Thread(new Runnable() {
                @Override
                public void run() {
                    for (int i = 0; i < 1000000; i++) {
                        String str = UUID.randomUUID().toString();
                        map.put(str, str);
                    }
                }
            }));

            threads.get(i).start();
        }
        for (Thread t : threads) {
            try {
                t.join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }

    public static void main(String args[]) {
        long s1 = System.currentTimeMillis();
        Map<String, String> hmap = new ConcurrentHashMap<>();
        SkipList.doIt(hmap);
        System.out.println(hmap.get("xxx"));
        long e1 = System.currentTimeMillis();
        System.out.println((e1 - s1) / 1000);

        long s2 = System.currentTimeMillis();
        Map<String, String> smap = new ConcurrentSkipListMap<>();
        SkipList.doIt(hmap);
        System.out.println(hmap.get("xxx"));
        long e2 = System.currentTimeMillis();
        System.out.println((e2 - s2) / 1000);
    }
}
