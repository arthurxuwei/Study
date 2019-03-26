import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

/**
 * this code demo will lead to OOM Exception,
 * Attributed to newCachedThreadPool Default params:maximumPoolSize
 */
public class NewCachedThreadPoolTest {
    public static void main(String[] args) {
        ExecutorService executorService = Executors.newCachedThreadPool();
        for (int i = 1; i < 100; i++)

            executorService.submit(new task());
    }
}

class task implements Runnable {

    @Override
    public void run() {
        try {
            System.out.println("sleep start");
            Thread.sleep(5000);
            System.out.println("sleep over");
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

    }
}