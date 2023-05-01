# Tip: with mysql cli, you can use source create-tables.sql to load all this info a database
DROP TABLE IF EXISTS album;
CREATE TABLE album (
	id		INT AUTO_INCREMENT NOT NULL,
	title	VARCHAR(128) NOT NULL,
	artist	VARCHAR(255) NOT NULL,
	price	DECIMAL(5,2) NOT NULL,
	PRIMARY KEY (`id`)
);

# fill in data to the table
INSERT INTO album (title, artist, price)
VALUES
  ('Blue Train', 'John Coltrane', 56.99),
  ('Giant Steps', 'John Coltrane', 63.99),
  ('Jeru', 'Gerry Mulligan', 17.99);
  
