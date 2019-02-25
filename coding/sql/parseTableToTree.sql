--stackoverflow.com questions 19220 
--what is the most efficient elegant way to parse a flat table into a tree

--Closure Table
CREATE TABLE ClosureTable (
	ancestor_id INT NOT NULL REFERENCES FlatTable(id),
	descendant_id INT NOT NULL REFERENCES FlatTable(id),
	PRIMARY KEY (ancestor_id, descendant_id)
);

INSERT INTO ClosureTable (ancestor_id, descendant_id) VALUES
  (1,1), (1,2), (1,4), (1,6),
  (2,2), (2,4),
  (3,3), (3,5),
  (4,4),
  (5,5),
  (6,6);
--descending from noe 1
SELECT f.*
FROM FlatTable f
  JOIN ClosureTable a ON (f.id = a.descendant_id)
WHERE a.ancestor_id = 1;

--into a nested structure
SELECT f.name, GROUP_CONCAT(b.ancestor_id order by b.path_length desc) AS breadcrumbs
FROM FlatTable f
JOIN ClosureTable a ON (f.id = a.descendant_id)
JOIN ClosureTable b ON (b.descendant_id = a.descendant_id)
WHERE a.ancestor_id = 1
GROUP BY a.descendant_id
ORDER BY f.name
