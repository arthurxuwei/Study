package observer;

public class CurrentConditionsDisplay implements IObserver, IDisplayElement {
	private float temperature;
	private float humidity;
	private float pressure;
	private ISubject weatherData;
	
	public CurrentConditionsDisplay(ISubject weatherData){
		this.weatherData = weatherData;
		weatherData.RegisterObserver(this);
	}

	@Override
	public Object Display() {
		// TODO Auto-generated method stub
		return "Current conditions: " + temperature + "F degrees and " + humidity + "% humidity";
	}

	@Override
	public void Update(float temperature, float humidity, float pressure) {
		// TODO Auto-generated method stub
		this.temperature = temperature;
		this.humidity = humidity;
		this.pressure = pressure;
	}

}
