-- return longest string row in column.
select * from table_name order by LENGTH(column_name) DESC limit 1;

-- group by time slot 
SELECT   b.mindate +          
	INTERVAL FLOOR(TIMESTAMPDIFF(SECOND, b.mindate, gather_time) / (3600*4)) * (3600*4) SECOND AS end_time,           
    CONCAT_WS(",",
    IFNULL(SUM(CASE WHEN sum_power BETWEEN 0 AND 1 THEN 1 else 0 END), 0),      
    IFNULL(SUM(CASE WHEN sum_power BETWEEN 1 AND 2 THEN 1 else 0 END), 0),      
    IFNULL(SUM(CASE WHEN sum_power BETWEEN 2 AND 3 THEN 1 else 0 END), 0),      
    IFNULL(SUM(CASE WHEN sum_power BETWEEN 3 AND 5 THEN 1 else 0 END), 0),      
    IFNULL(SUM(CASE WHEN sum_power BETWEEN 5 AND 7 THEN 1 else 0 END), 0),      
    IFNULL(SUM(CASE WHEN sum_power BETWEEN 7 AND 65536 THEN 1 else 0 END), 0) ) as result   
FROM dcos_power_data   JOIN     (SELECT '2015-04-22 00:00:00' AS mindate) b ON gather_time  <=  b.mindate 
WHERE is_deleted='n'   
GROUP BY end_time;