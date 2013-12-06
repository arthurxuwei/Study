package designPattern.Observer;

public class StatisticDisplay implements IObserver, IDisplayElement {
	private float maxTemp = 0.0f;
	private float minTemp = 200;                                    
	private float temperatureSum = 0.0f;
	private int numReadings = 0;
	private ISubject weatherData;
	
	public StatisticDisplay(ISubject weatherData){
		this.weatherData = weatherData;
		weatherData.RegisterObserver(this);
	}
	
	public int getNumberOfReadings(){
		return numReadings;
	} 
	
	@Override
	public Object Display() {
		// TODO Auto-generated method stub
		return "Avg/Max/Min temperature = " + RoundFloatToString(temperatureSum / numReadings) + "F/" + maxTemp + "F/" + minTemp + "F";
	}
	

	@Override
	public void Update(float temperature, float humidity, float pressure) {
		// TODO Auto-generated method stub
		temperatureSum += temperature;
		numReadings++;
		
		if (temperature > maxTemp) {
			maxTemp = temperature;
		}
		
		if (temperature < minTemp) {
			minTemp = temperature;
		}
	}
	
	public static String RoundFloatToString(Float floatToRound) {
		return floatToRound.toString();
	}

}
