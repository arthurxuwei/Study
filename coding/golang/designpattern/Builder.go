package main

import (
	"encoding/json"
	"encoding/xml"
	"fmt"
)

type Message struct {
	Body []byte
	Format string
}

type MessageBuilder interface {
	SetRecipient(recipient string)
	SetText(text string)
	Message() (*Message, error)
}

type JSONMessageBuilder struct {
	messageRecipient string
	messageText string
}

func (b *JSONMessageBuilder) SetRecipient(recipient string)  {
	b.messageRecipient = recipient
}

func (b *JSONMessageBuilder) SetText(text string)  {
	b.messageText = text
}

func (b *JSONMessageBuilder) Message() (*Message, error)  {
	m := make(map[string]string)
	m["recipient"] = b.messageRecipient
	m["text"] = b.messageText

	data, err := json.Marshal(m)
	if err != nil {
		return nil, err
	}
	return &Message{Body:data, Format:"JSON"}, nil
}


type XMLMessageBuilder struct {
	messageRecipient string
	messageText string
}

func (b *XMLMessageBuilder) SetRecipient(recipient string)  {
	b.messageRecipient = recipient
}

func (b *XMLMessageBuilder) SetText(text string)  {
	b.messageText = text
}

func (b *XMLMessageBuilder) Message() (*Message, error)  {
	type XMLMessage struct {
		Recipient string `xml:"recipient"`
		Text string `xml:"text"`
	}
	m := XMLMessage{
		Recipient:b.messageRecipient,
		Text:b.messageText,
	}

	data, err := xml.Marshal(m)
	if err != nil {
		return nil, err
	}
	return &Message{Body:data, Format:"XML"}, nil
}

type Sender struct {}

func (s *Sender) BuildMessage(builder MessageBuilder) (*Message, error) {
	builder.SetRecipient("XXX")
	builder.SetText("Hahahaha")
	return builder.Message()
}

func main() {
	sender := &Sender{}
	jsonMsg, err := sender.BuildMessage(&JSONMessageBuilder{})
	if err != nil {
		panic(err)
	}

	xmlMsg, err := sender.BuildMessage(&XMLMessageBuilder{})
	if err != nil {
		panic(err)
	}

	fmt.Printf("jsonMsg: %s, xmlMsg: %s", jsonMsg, xmlMsg)
}