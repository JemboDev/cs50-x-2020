-- write a SQL query to list the titles of all movies in which both Johnny Depp and Helena Bonham Carter starred

SELECT title
FROM movies
WHERE id IN (
    SELECT movie_id
    FROM stars
    WHERE person_id IN (
        SELECT id
        FROM people
        WHERE name = "Johnny Depp"
           OR name = "Helena Bonham Carter")
GROUP BY movie_id
HAVING COUNT(movie_id) > 1);