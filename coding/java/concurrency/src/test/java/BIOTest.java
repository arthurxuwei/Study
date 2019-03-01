import java.io.IOException;
import java.io.InputStream;
import java.net.ServerSocket;
import java.net.Socket;

public class BIOTest {
    public static void main(String[] args) throws IOException {
        ServerSocket serverSocket = new ServerSocket(8888);
        while(true){
            Socket socket = serverSocket.accept();
            new Thread(() -> {
                try {
                    // 获取客户端输入流
                    InputStream is = socket.getInputStream();
                    byte[] b = new byte[1024];
                    while(true){
                        // 循环读取数据, read() 阻塞点
                        int data = is.read(b);
                        if(data != -1){
                            String info = new String(b,0,data,"GBK");
                            System.out.println(info);
                        }else{
                            break;
                        }
                    }
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }).start();
        }
    }
}
