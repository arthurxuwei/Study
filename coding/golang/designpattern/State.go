package main

import (
	"fmt"
	"strings"
)

type StateContext interface {
	SetClock(hour int)
	ChangeState(state State)
	RecordLog(log string)
}

type State interface {
	DoClock(ctx StateContext, hour int)
	DoUse(ctx StateContext)
}

type DayState struct {}

type NightState struct{}

var DayInstance *DayState

var NightInstance *NightState

func GetDayInstance() *DayState {
	if DayInstance == nil {
		DayInstance = &DayState{}
	}
	return DayInstance
}

func GetNightInstance() *NightState {
	if NightInstance == nil {
		NightInstance = &NightState{}
	}
	return NightInstance
}

func (d *DayState) DoClock(ctx StateContext, hour int)  {
	if hour < 9 || 17 <= hour {
		ctx.ChangeState(GetNightInstance())
	}
}

func (d *DayState) DoUse(ctx StateContext) {
	ctx.RecordLog("day")
}

func (d *NightState) DoClock(ctx StateContext, hour int)  {
	if 9 <= hour && hour < 17 {
		ctx.ChangeState(GetDayInstance())
	}
}

func (d *NightState) DoUse(ctx StateContext) {
	ctx.RecordLog("night")
}

type SafeFrame struct {
	State State
	logs []string
}

func (s *SafeFrame) SetClock(hour int)  {
	s.State.DoClock(s, hour)
}

func (s *SafeFrame) ChangeState(state State) {
	s.State = state
}

func (s *SafeFrame) RecordLog(log string) {
	s.logs = append(s.logs, log)
}

func (s *SafeFrame) Use() {
	s.State.DoUse(s)
}

func (s *SafeFrame) GetLog() string {
	return strings.Join(s.logs, " ")
}

func main() {
	safeFrame := &SafeFrame{State: GetDayInstance()}

	hours := []int{8, 9, 16, 17}

	for _, hour := range hours {
		safeFrame.SetClock(hour)
		safeFrame.Use()
	}

	fmt.Println(safeFrame.GetLog())
}