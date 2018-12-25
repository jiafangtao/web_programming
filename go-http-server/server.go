// An HTTP server supports listing and downloading files
package main

import (
	"net/http"
	"io"
	"log"
)

func viewHandler (w http.ResponseWriter, r *http.Request) {
	// TODO: 1. get relative dir from request
	// 2. security check for dir to see if it has injections, e.g. containing ../ or ;
	// 3. calculate the target directory
	// 4. get list of folders and files
	// 5. format them in HTML format
	// 6. respond to client
	io.WriteString(w, "Listing a dir or file: " + r.URL.String())
}

func main() {
	http.HandleFunc("/", viewHandler)
	err := http.ListenAndServe(":8080", nil)
	if err != nil {
		log.Fatal("ListenAndServe: ", err.Error())
	}
}
