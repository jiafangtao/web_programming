package main

import (
	"fmt"
	"os"
	"log"
	"database/sql"
	
	"github.com/go-sql-driver/mysql"
)

type Album struct {
    ID      int64
    Title   string
    Artist  string
    Price   float32
}

var db *sql.DB

func main() {
	// capture connection props
	cfg := mysql.Config{
		User: os.Getenv("DBUSER"),
		Passwd: os.Getenv("DBPASS"),
		Net: "tcp",
		Addr: "127.0.0.1:3306",
		DBName: "recordings",
	};

	// get a db handle
	var err error
	db, err = sql.Open("mysql", cfg.FormatDSN())
	if err != nil {
		log.Fatal(err)
	}

	pingErr := db.Ping()
	if pingErr != nil {
		log.Fatal(pingErr)
	}

	fmt.Println("Connected!")

    // query by artist name
    albums, err := albumByArtist("John Coltrane")
    if err != nil {
        log.Fatal(err)
    }

    fmt.Printf("Albums found: %v\n", albums)

    // query album with id 2
    alb, err := albumById(2)
    if err != nil {
        log.Fatal(err)
    }

    fmt.Printf("Album found: %v\n", alb)

    log.Print("Adding a new album")
    id, err := addAlbum(Album{
    	Title: "The Modern Sound of Betty Carter",
    	Artist: "Betty Carter",
    	Price: 49.99,
    })

    if err != nil {
    	log.Fatal(err)
    }

    fmt.Printf("ID of newly added album: %d\n", id)
}

// query by id
func albumById(id int64) (Album, error) {
    // an album to hold data from returned row.
    var alb Album

    row := db.QueryRow("SELECT * FROM album WHERE id = ?", id)
    if err := row.Scan(&alb.ID, &alb.Title, &alb.Artist, &alb.Price); err != nil {
        if err == sql.ErrNoRows {
            return alb, fmt.Errorf("albumById %d: no such album", id)
        }

        return alb, fmt.Errorf("albumById %d: %v", id, err)
    }

    return alb, nil
}

// query for all albums with specific artist name
func albumByArtist(name string) ([] Album, error) {
    // An albums slice to hold data from returned rows.
    var albums []Album

    rows, err := db.Query("SELECT * FROM album WHERE artist = ?", name)
    if err != nil {
        return nil, fmt.Errorf("albumByArtist %q: %v", name, err)
    }

    defer rows.Close()

    // loop through rows, using Scan to assign column data to struct fields.
    for rows.Next() {
        var alb Album
        if err := rows.Scan(&alb.ID, &alb.Title, &alb.Artist, &alb.Price); err != nil {
            return nil, fmt.Errorf("albumByArtist %q: %v", name, err)
        }
        
        albums = append(albums, alb)
    }

    if err := rows.Err(); err != nil {
        return nil, fmt.Errorf("albumByArtist %q: %v", name, err)
    }

    return albums, nil
}

func addAlbum(alb Album) (int64, error) {
    result, err := db.Exec("INSERT INTO album (title, artist, price) VALUES (?, ?, ?)", alb.Title, alb.Artist, alb.Price)
    if err != nil {
        return -1, fmt.Errorf("addAlbum: %v", err)
    }

    id, err := result.LastInsertId()
    if err != nil {
        return -1, fmt.Errorf("addAlbum: %v", err)
    }

    return id, nil
}

