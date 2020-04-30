import java.text.SimpleDateFormat;
import java.util.*;
import java.util.List;
import java.util.concurrent.TimeUnit;

/**
 * Created by arthur.xw on 2015/5/20.
 */
public class NavigableMapTest {
    public static void main(String[] args) {
        long millisPerHour = TimeUnit.HOURS.toMillis(1);
        Calendar cal = Calendar.getInstance();
        cal.set(Calendar.HOUR_OF_DAY, 0);
        cal.set(Calendar.MINUTE, 0);
        cal.set(Calendar.SECOND, 0);
        long millisToday = cal.getTimeInMillis();
        NavigableMap<Long, List<Double>> l = new TreeMap<>();
        for (int i = 0; i < 7; i++) {
            List<Double> arr = new ArrayList<>();
            arr.add((double)i);
            l.put(millisToday + i * 4 * millisPerHour, arr);
        }

        for (Long key : l.keySet()) {
            System.out.println(new SimpleDateFormat("yyyy-MM-dd HH:mm:ss").format(new Date(key)));
        }

        System.out.println(l.get(l.floorKey(Calendar.getInstance().getTimeInMillis())));
    }
}
