import java.lang.ref.*;
import java.util.HashMap;
import java.util.Objects;

/**
 * Difference between four reference (http://weixublog.appspot.com/?p=5738914362949632)
 */
public class ReferenceType {
    private static void testPhantomReference () {
        ReferenceQueue referenceQueue = new ReferenceQueue();
        Object object = new Object() {
            public String toString() {
                return "Referenced Object";
            }
        };
        Object data = new Object() {
            public String toString() {
                return "Data";
            }
        };

        HashMap map = new HashMap();
        Reference reference = null;
        System.out.println("-----Testing PhantomReference-----");
        reference = new PhantomReference(object, referenceQueue);

        map.put(reference, data);

        System.out.println(reference.get());
        System.out.println(map.get(reference));
        System.out.println(reference.isEnqueued());

        System.gc();

        System.out.println(reference.get());
        System.out.println(map.get(reference));
        System.out.println(reference.isEnqueued());

        object = null;
        data = null;

        System.gc();

        System.out.println(reference.get());
        System.out.println(map.get(reference));
        System.out.println(reference.isEnqueued());

        System.out.println("-----Test Over-----");
    }

    private static void testWeakReference () {
        ReferenceQueue referenceQueue = new ReferenceQueue();
        Object object = new Object() {
            public String toString() {
                return "Referenced Object";
            }
        };
        Object data = new Object() {
            public String toString() {
                return "Data";
            }
        };

        HashMap map = new HashMap();
        Reference reference = null;
        System.out.println("-----Testing WeakReference-----");
        reference = new WeakReference(object, referenceQueue);

        map.put(reference, data);

        System.out.println(reference.get());
        System.out.println(map.get(reference));
        System.out.println(reference.isEnqueued());

        System.gc();

        System.out.println(reference.get());
        System.out.println(map.get(reference));
        System.out.println(reference.isEnqueued());

        object = null;
        data = null;

        System.gc();

        System.out.println(reference.get());
        System.out.println(map.get(reference));
        System.out.println(reference.isEnqueued());

        System.out.println("-----Test Over-----");
    }

    private static void testSoftReference () {
        ReferenceQueue referenceQueue = new ReferenceQueue();
        Object object = new Object() {
            public String toString() {
                return "Referenced Object";
            }
        };
        Object data = new Object() {
            public String toString() {
                return "Data";
            }
        };

        HashMap map = new HashMap();
        Reference reference = null;
        System.out.println("-----Testing SoftReference-----");
        reference = new SoftReference(object, referenceQueue);

        map.put(reference, data);

        System.out.println(reference.get());
        System.out.println(map.get(reference));
        System.out.println(reference.isEnqueued());

        System.gc();

        System.out.println(reference.get());
        System.out.println(map.get(reference));
        System.out.println(reference.isEnqueued());

        object = null;
        data = null;

        System.gc();

        System.out.println(reference.get());
        System.out.println(map.get(reference));
        System.out.println(reference.isEnqueued());

        System.out.println("-----Test Over-----");
    }

    public static void main(String[] argv) throws InterruptedException {
        //phantom reference
        testPhantomReference();

        //weak reference
        testWeakReference();

        //soft reference
        testSoftReference();
    }
}
