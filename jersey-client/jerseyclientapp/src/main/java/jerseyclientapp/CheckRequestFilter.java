package jerseyclientapp;

import java.io.IOException;
import java.util.List;

import javax.ws.rs.client.ClientRequestContext;
import javax.ws.rs.client.ClientRequestFilter;
import javax.ws.rs.core.MultivaluedMap;


public class CheckRequestFilter implements ClientRequestFilter {
	 
    public void filter(ClientRequestContext requestContext)
                        throws IOException {
    	
    	MultivaluedMap<String, Object> allHeaders = requestContext.getHeaders();
    	List<Object> targetHeaders = allHeaders.get("Content-Length");
    	String header = null;
    	if (targetHeaders != null && targetHeaders.size() != 0) {
    		header = targetHeaders.get(targetHeaders.size() - 1).toString();
    	}
        if (header == null) {            
        	requestContext.getHeaders().add("Content-Length", 0);        	
         }
    }
}
