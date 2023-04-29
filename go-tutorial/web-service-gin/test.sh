echo "Testing - GET all albums"
curl -v http://localhost:8080/albums

echo "Testing - POST a new album"
curl  -v http://localhost:8080/albums --data '{"id": "4", "t
itle":"The Modern Sounc of Betty Carter", "artist": "Betty Carter", "price":49.99
}'


echo "Testing - GET album by id"
curl -v http://localhost:8080/albums/3

