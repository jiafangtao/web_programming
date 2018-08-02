package jerseyclientapp;

import javax.ws.rs.client.Client;
import javax.ws.rs.client.ClientBuilder;
import javax.ws.rs.client.Entity;
import javax.ws.rs.client.Invocation;
import javax.ws.rs.client.WebTarget;
import javax.ws.rs.core.MediaType;
import javax.ws.rs.core.Response;

import org.glassfish.jersey.client.ClientConfig;
import org.glassfish.jersey.client.ClientProperties;
import org.glassfish.jersey.client.RequestEntityProcessing;

public class App {

	public static void main(String[] args) {
		
		System.setProperty("sun.net.http.allowRestrictedHeaders", "true");
		
		log ("Posting with Header: Content-Length: 0 ......");
		doPost("http://localhost:3000", null);
		
		log ("===============================");
		
		doPost("http://localhost:3000", "hello, world");
		
		log ("Done.");
	}
	
	public static void doPost (String url, String data) {
		
		Response response = null;
    	
		
		ClientConfig config = new ClientConfig();
		config.register(CheckRequestFilter.class);
		
		config.property(ClientProperties.REQUEST_ENTITY_PROCESSING, RequestEntityProcessing.BUFFERED);
		
		Client client = ClientBuilder.newBuilder().build();
		//Client client = ClientBuilder.newClient(config);
		
		//Client client = ClientBuilder.newClient().register(CheckRequestFilter.class);
		
		
        WebTarget webTarget = client.target(url).queryParam("responseFormat", "json");
        
        Invocation.Builder invocBuilder = webTarget.request(MediaType.APPLICATION_JSON_TYPE);
        
        if (data == null) {
        	response = invocBuilder.header("content-length", 0).post(null);
        	//response = invocBuilder.post(null);
        }
        else
        {
        	Entity<String> entity = Entity.entity(data, MediaType.TEXT_PLAIN_TYPE);
        	response = invocBuilder.post(entity);
        }
                
        int code = response.getStatus();
        
        if (code >= 200 && code < 300) {
        	
        	String result = response.readEntity(String.class);
        	log(String.format("Response: %s", result));
        }
        else {
        	log(String.format("Something went wrong with status %s", code));
        }
	}
	
	public static void log (String message) {
		System.out.println(message);
	}
}
