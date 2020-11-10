class Funds
{
    private:
        float funds;

    public:
        Funds(float funds);

        float getFunds() { return funds; }
}

class Own: Funds { Own(float own): Float(own) {} };

class Borrowed: Funds { Borrowed(float borrowed): Float(borrowed) {} };

class Margin: Funds { Margin(float margin): Float(margin) {} };


class Position:

    private:

        float p0;
        float r;

        float purchase;
        float own;
        float borrowed;
        float init_margin;

        int n_shares;

    public:

        Position(float p0, int n_shares, float r=0, Funds funds);
        ~Position();

        float getP0();
        float getR();

        float getPurchase;
        float getOwn();
        float getBorrowed();
        float getInitMargin();

        float netWorth(float p, int t=0);
        float netWorthGain(float p, t=0);
        float netWorthRets(float p, t=0);
        float marginAt(float p, t=0);
        float priceForMargin(float margin);

};


class Long: Position
{
    public:
        float netWorth(float p, int t=0);
        float priceForMargin(float margin);
};


class Short: Position
{
    public:
        float netWorth(float p, int t=0);
        float priceForMargin(float margin);
}:
