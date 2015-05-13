package readerwriter;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.*;

/**
 * Created by arthur.xw on 2015/5/12.
 */
public class ReaderFirst {
    public static final int READ_THREAD_SIZE = 4;
    public static final int BUFFER_LENGTH = 100;

    public List<Integer> g_productor = new ArrayList<>();
    public CountDownLatch mReaderLatch = new CountDownLatch(READ_THREAD_SIZE);

    public static Semaphore mWriteSema = new Semaphore(READ_THREAD_SIZE);
    public boolean bStopFlag = false;
    public CountDownLatch mLatchDown = new CountDownLatch(1 + READ_THREAD_SIZE);
    public CountDownLatch mLatchStart = new CountDownLatch(1 + READ_THREAD_SIZE);

    public void startDemo() {
        try {
            initReadNone();
            bStopFlag = false;
            Executor mExecutor = Executors.newFixedThreadPool(1 + READ_THREAD_SIZE);
            mExecutor.execute(new WriterThread(this, "Writer"));

            for (int i = 1; i <= READ_THREAD_SIZE; i++) {
                mExecutor.execute(new ReadThread(this, "Reader" + i));
            }

            mLatchStart.await();
            System.out.println("All Thread is running");
            mLatchDown.await();

            System.out.println("All Thread is down");
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

    }

    public void waitReaderEnd() {
        try {
            mReaderLatch.await();
            mReaderLatch = new CountDownLatch(READ_THREAD_SIZE);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    public void singalWriteEnd() {
        mWriteSema.release(READ_THREAD_SIZE);
    }

    public void waitWriteEnd() {
        try {
            mWriteSema.acquire();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    public void singalReadEnd() {
        mReaderLatch.countDown();
    }

    public void initReadNone() {
        try {
            mWriteSema.acquire(READ_THREAD_SIZE);
            for (int i = 0; i < READ_THREAD_SIZE; i++) {
                mReaderLatch.countDown();
            }
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

}
