#!/usr/bin/bash
echo "Starting mysql ..."
docker stop mysqldb || true
docker rm mysqldb || true
docker run --name mysqldb -e MYSQL_ROOT_PASSWORD=letmein -v $(pwd):/home -p 3306:3306 mysql
