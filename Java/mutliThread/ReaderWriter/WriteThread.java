/**
 * Created by arthur.xw on 2015/5/12.
 */
public class WriteThread implements Runnable{

    ReaderFirst mExample = null;
    String name = null;
    int iFlag = 0;

    public WriteThread(ReaderFirst re, String name) {
        mExample = re;
        this.name = name;
    }
    @Override
    public void run() {
        mExample.mLatchStart.countDown();
        int index = 0;
        while (index < ReaderFirst.BUFFER_LENGTH) {
            mExample.waitReaderEnd();
            int mWriteLength = (int) (Math.random() * 9) + 1;
            if (mWriteLength > (ReaderFirst.BUFFER_LENGTH - index)) {
                mWriteLength = ReaderFirst.BUFFER_LENGTH - index;
            }

            mExample.g_productor.clear();
            int mParam = 0;
            String writeline = "";
            for (int i = 0; i < mWriteLength; i++) {
                mParam = (int) (Math.random() * 14) + 1;
                mExample.g_productor.add(mParam);
                writeline += String.format("%1$x", mParam);
            }
            index = index + mWriteLength;
            System.out.println(name + " write: " + writeline + "\t current index: " + index);
            if (index >= ReaderFirst.BUFFER_LENGTH) {
                mExample.bStopFlag = true;
            }

            mExample.singalWriteEnd();

            iFlag++;
        }

        System.out.println(name + " thread over");
        mExample.mLatchDown.countDown();
    }

}
