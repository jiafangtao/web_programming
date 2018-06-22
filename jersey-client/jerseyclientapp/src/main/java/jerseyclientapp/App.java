package jerseyclientapp;

import javax.ws.rs.client.Client;
import javax.ws.rs.client.ClientBuilder;
import javax.ws.rs.client.Entity;
import javax.ws.rs.client.Invocation;
import javax.ws.rs.client.WebTarget;
import javax.ws.rs.core.MediaType;
import javax.ws.rs.core.Response;

public class App {

	public static void main(String[] args) {
		
		log ("Posting with Header: Content-Length: 0 ......");
		doPost("http://localhost:3000", null);
		
		log ("===============================");
		
		doPost("http://localhost:3000", "hello, world");
		
		log ("Done.");
	}
	
	public static void doPost (String url, String data) {
		
		Response response = null;
    	
		//Client client = ClientBuilder.newBuilder().build();
		Client client = ClientBuilder.newClient();
		
        WebTarget webTarget = client.target(url).queryParam("responseFormat", "json");
        
        Invocation.Builder invocBuilder = webTarget.request(MediaType.APPLICATION_JSON_TYPE);
        
        if (data == null) {
        	response = invocBuilder.header("Content-Length", 0).post(null);
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
