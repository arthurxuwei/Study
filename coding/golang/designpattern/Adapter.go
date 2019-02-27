package main

import (
	"fmt"
	"time"
)

type Money struct {
	Amount float64
	Currency string
}

type PalPayMent struct {
	APIKey string
}

func (*PalPayMent) Send(sender, recipient string , money *Money) {
	fmt.Printf("Send %f %s from %s to %s", money.Amount, money.Currency, sender, recipient)
}

type Account struct {
	Owner string
	Email string
	Balance float64
	Currency string
}

type Transaction struct {
	FromAccount *Account
	ToAccount *Account
	Amount float64
	Date time.Time
	Reason string
}

type Gateway struct {
	Token string
	Accounts []*Account
}

func (g *Gateway) FindAccountByEmail(email string) *Account {
	for _, account := range g.Accounts {
		if account.Email == email {
			return account
		}
	}
	return nil
}

func (g *Gateway) ProcessTransaction(t *Transaction) {
	fmt.Printf("Transfered %f %s from %s to %s at %v", t.Amount,
		t.FromAccount.Currency, t.FromAccount.Owner, t.ToAccount.Owner, t.Date)
	t.FromAccount.Balance -= t.Amount
}


type Item struct {
	Name string
	Price float64
}

type Payment interface {
	// Pay from email to email this amount
	Pay(fromEmail, toEmail string, amount float64)
}

type ShoppingCard struct {
	Items []*Item
	PaymentMethod Payment
	ShopEmailAddress string
}

func (c *ShoppingCard) Checkout(payee string)  {
	var total float64
	for _, item := range c.Items {
		total += item.Price
	}
	c.PaymentMethod.Pay(payee, c.ShopEmailAddress, total)
}

type BankAdapter struct {
	Gateway *Gateway
}

func (b *BankAdapter) Pay(from string, to string, amount float64)  {
	fromAccount := b.Gateway.FindAccountByEmail(from)
	toAccount := b.Gateway.FindAccountByEmail(to)
	t := &Transaction{FromAccount:fromAccount, ToAccount:toAccount, Amount:amount, Date:time.Now(), Reason:"Payment to Online Store"}
	b.Gateway.ProcessTransaction(t)
}

type PayPalAdapter struct {
	Payment *PalPayMent
}

func (p *PayPalAdapter) Pay(from string, to string, amount float64)  {
	p.Payment.Send(from, to, &Money{Amount:amount, Currency:"RMB"})
}

func main()  {
	payPalAdapter := &PayPalAdapter{
		Payment: &PalPayMent{
			APIKey: "pay-pal-api-key",
		},
	}

	bankAdapter := &BankAdapter{
		Gateway: &Gateway{
			Token: "bank-token",
			Accounts:[]*Account{
				{
					Owner:    "iShop",
					Email:    "shop@example.com",
					Balance:  1000000,
					Currency: "RMB",
				},
				{
					Owner:    "Mike Meadows",
					Email:    "mike@example.com",
					Balance:  890300,
					Currency: "RMB",
				},
			},
		},
	}

	card := &ShoppingCard{
		Items: []*Item{
			{
				Name:  "Tablet",
				Price: 1000,
			},
			{
				Name:  "Headphones",
				Price: 50,
			},
			{
				Name:  "Smart Watch",
				Price: 550,
			},
		},
		ShopEmailAddress: "shop@example.com",
	}

	fmt.Println("PayPal transaction")
	card.PaymentMethod = payPalAdapter
	card.Checkout("ben.johnson@example.com")

	fmt.Println("bank transaction")
	card.PaymentMethod = bankAdapter
	card.Checkout("mike@example.com")


}