package main

import (
	"context"
	"fmt"
	"github.com/influxdata/influxdb-client-go/v2"
	"time"
)

func connInflux() influxdb2.Client {
	client := influxdb2.NewClient(
		"http://100.81.152.16:8086",
		"xrZrQV3igI9_XjYBi5WFfiqxtwYgq_mRfRVoM4dFS9PXSqF85nQVWgN0u3HoW05fC3VnlUKX-3jXfewoopP9cA==",
		)
	return client
}

func main() {
	client := connInflux()
	writeAPI := client.WriteAPIBlocking("test", "test")
	p := influxdb2.NewPoint("stat",
		map[string]string{"unit": "temperature"},
		map[string]interface{}{"avg":24.5, "max":45.0},
		time.Now())
	writeAPI.WritePoint(context.Background(), p)

	p = influxdb2.NewPointWithMeasurement("stat").AddTag("unit", "temperature").AddField("avg", 23.2).AddField("max",45.0).SetTime(time.Now())
	writeAPI.WritePoint(context.Background(), p)

	line := fmt.Sprintf("stat,unit=temperature avg=%f,max=%f", 23.5, 45.0)
	writeAPI.WriteRecord(context.Background(), line)

	queryAPI := client.QueryAPI("test")
	result, err := queryAPI.Query(context.Background(), `from(bucket:"test")|> range(start: -1h) |> filter(fn: (r) => r._measurement == "stat")`)
	if err == nil {
		// Use Next() to iterate over query result lines
		for result.Next() {
			// Observe when there is new grouping key producing new table
			if result.TableChanged() {
				fmt.Printf("table: %s\n", result.TableMetadata().String())
			}
			// read result
			fmt.Printf("row: %s\n", result.Record().String())
		}
		if result.Err() != nil {
			fmt.Printf("Query error: %s\n", result.Err().Error())
		}
	}



}

