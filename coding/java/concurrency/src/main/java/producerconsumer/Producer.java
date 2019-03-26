package producerconsumer;

import java.util.Random;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicInteger;

/**
 *
 * @author weixu
 * @date 5/6/2014
 */
public class Producer implements Runnable {

    public Producer(BlockingQueue queue) {
        this.queue = queue;
    }

    @Override
    public void run() {
        String data;
        Random r = new Random();

        System.out.println("Start Producer Thread.");
        try {
            while (isRunning) {
                System.out.println("Producing Data...");
                Thread.sleep(r.nextInt(DEFAULT_RANGE_FOR_SLEEP));

                data = "data: " + count.incrementAndGet();
                System.out.println("Push "+ data + " into queue");
                if (!queue.offer(data, 2, TimeUnit.SECONDS)) {
                    System.out.println("Failure with: "+ data);
                }
            }
        } catch (InterruptedException e) {
            e.printStackTrace();
            Thread.currentThread().interrupt();
        } finally {
            System.out.println("Exit producer thread.");
        }
    }

    public void stop() {
        isRunning = false;
    }


    private volatile boolean isRunning = true;
    private BlockingQueue queue;
    private static AtomicInteger count = new AtomicInteger();
    private static final int DEFAULT_RANGE_FOR_SLEEP = 1000;
}
