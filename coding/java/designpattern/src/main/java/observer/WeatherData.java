package observer;

import java.util.ArrayList;

public class WeatherData implements ISubject {
	private ArrayList<IObserver> observers;
	private float temperature;
	private float humidity;
	private float pressure;
	
	public WeatherData() {
		observers = new ArrayList<IObserver>();
	}

	@Override
	public void RegisterObserver(IObserver o) {
		// TODO Auto-generated method stub
		observers.add(o);
	}

	@Override
	public void RemoveOvserver(IObserver o) {
		// TODO Auto-generated method stub
		int i = observers.indexOf(o);
		if (i >= 0) {
			observers.remove(o);
		}
	}

	@Override
	public void NotifyObserver() {
		// TODO Auto-generated method stub
		for (IObserver observer : observers) {
			observer.Update(temperature, humidity, pressure);
		}
	}
	
	public void MeasurementsChanged() {
		NotifyObserver();
	}

	public void SetMeasurements(float temperature, float humidity, float pressure) {
		this.temperature = temperature;
		this.humidity = humidity;
		this.pressure = pressure;
		MeasurementsChanged();
	}
}
