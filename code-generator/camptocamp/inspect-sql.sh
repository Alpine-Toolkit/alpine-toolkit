grep 'CREATE TABLE' c2corg.sql | sed 's/CREATE TABLE //;s/ (//' | sort > _tables.txt
