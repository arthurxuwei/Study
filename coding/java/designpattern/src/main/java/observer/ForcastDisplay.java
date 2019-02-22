package observer;

public class ForcastDisplay implements IObserver, IDisplayElement {
	private float currentPressure = 29.92f;
	private float lastPressure;
	private ISubject weatherData;

	public ForcastDisplay(ISubject weatherData) {
		this.weatherData = weatherData;
		weatherData.RegisterObserver(this);
	}
	@Override
	public Object Display() {
		// TODO Auto-generated method stub
		StringBuilder sBuilder = new StringBuilder();
		sBuilder.append("Forecast: ");
		
		if (currentPressure > lastPressure) {
			sBuilder.append("Improving weather on the way!");
		} else if (currentPressure == lastPressure) {
			sBuilder.append("More of the same");
		} else if (currentPressure < lastPressure) {
			sBuilder.append("Watch out for cooler, rainy weather");
		}
		return sBuilder.toString();
	}

	@Override
	public void Update(float temperature, float humidity, float pressure) {
		// TODO Auto-generated method stub
		lastPressure = currentPressure;
		currentPressure = pressure;
	}

}
