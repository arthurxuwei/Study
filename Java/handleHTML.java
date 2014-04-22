package test;

import java.awt.Image;
import java.awt.image.BufferedImage;
import java.io.BufferedReader;
import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.InetSocketAddress;
import java.net.Proxy;
import java.net.MalformedURLException;
import java.net.URL;
import java.net.URLConnection;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

import javax.imageio.ImageIO;

import org.cyberneko.html.parsers.DOMParser;
import org.dom4j.Attribute;
import org.dom4j.Document;
import org.dom4j.Node;
import org.dom4j.XPath;
import org.dom4j.io.DOMReader;
import org.dom4j.xpath.DefaultXPath;
import org.jaxen.SimpleNamespaceContext;
import org.xml.sax.InputSource;
import org.xml.sax.SAXException;


public class handleHTML {

	public List getAttr(Document doc, String gz){
		List nodes = doc.getRootElement().selectNodes(gz);
		System.out.println(nodes.size());
		return nodes;
	}
	
	public Document getDoc(InputStream inputStream){
		DOMParser parser = new DOMParser();
		
		try {
//			parser.setFeature("http://xml.org/sax/features/namespaces", false);  
			BufferedReader bin = new BufferedReader(new InputStreamReader(inputStream));
			parser.parse(new InputSource(bin));
		} catch (SAXException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
		
		org.w3c.dom.Document doc = parser.getDocument();
		DOMReader domReader = new DOMReader();
		
		Document document = domReader.read(doc);
		return document;
	}
	
	public String[] getUrl(List nodes) {
		if (nodes == null) {
			return null;
		}
		Iterator iter = nodes.iterator();
		String[] url = new String[nodes.size()];
		for(int i=0; iter.hasNext(); i++){
			Attribute attribute = (Attribute)iter.next();
			url[i] = attribute.getValue();
		} 
		return url;
	}
	
	public InputStream getInput(String path, Proxy proxy){
		URL url = null;
		try {
			url = new URL(path);
		} catch (MalformedURLException e) {
			e.printStackTrace();
		}
		URLConnection conn = null;
		
		try {
			if (proxy != null) {
				conn = url.openConnection(proxy);
			} else {
				conn = url.openConnection();
			}
			
		} catch (IOException e) {
			e.printStackTrace();
		}
		conn.setDoOutput(true);
		
		InputStream inputStream = null;
		
		try {
			inputStream = conn.getInputStream();
		} catch (IOException e) {
			e.printStackTrace();
		}
		
		return inputStream;
	}

	public void outputPhoto(String[] photoUrl, Proxy proxy) {

		for(int i=0;i<photoUrl.length;i++){   
			
            if("".equals(photoUrl[i]))continue;   
            System.out.println(photoUrl[i]);
            InputStream inputStream = this.getInput(photoUrl[i], proxy); 
            try {
            	BufferedImage image = ImageIO.read(inputStream);
            	if (image == null) continue;
                File outputfile = new File("D:/img/" + i);
                ImageIO.write(image, "jpg", outputfile);
                	
            } catch (IOException e) {
            	e.printStackTrace();
            }
            
         }	 
			
	}
	
	public static void main(String[] args) {
		System.out.println("Starting...");
		System.out.println("Set Proxy...");
		System.setProperty("http.proxyHost", "http://web-proxy.usa.hp.com");
		System.setProperty("http.proxyPort", "8080");
		
		
		handleHTML test = new handleHTML();
		String url = "http://www.douban.com/"; 
		
		InetSocketAddress addr = new InetSocketAddress("web-proxy.usa.hp.com", 8080); 
		Proxy proxy = new Proxy(Proxy.Type.HTTP, addr);
		
		System.out.println("Get Stream...");
		InputStream stream = test.getInput(url, proxy);
		
		System.out.println("Get Doc...");
		Document document = test.getDoc(stream); 
		
//		System.out.println(document.asXML());
		
		String gz = "//IMG/@src";//xpath匹配   
		
		System.out.println("Get Attr...");
		List nodes = test.getAttr(document, gz);
				
		System.out.println("Get Url...");
		String[] photoUrl = test.getUrl(nodes); 
		
		System.out.println(photoUrl.length);
		
		System.out.println("Save Photo...");
		test.outputPhoto(photoUrl, proxy); 
		
		System.out.println("Done");
    }
}
