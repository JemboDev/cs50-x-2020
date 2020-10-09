-- https://cs50.harvard.edu/x/2020/psets/7/movies/
-- SQL queries to answer questions about a database of movies. (12.06.20)
-------------------------------------------------------------------------
-- write a SQL query to list the titles of all movies released in 2008.

SELECT title FROM movies WHERE year = 2008;