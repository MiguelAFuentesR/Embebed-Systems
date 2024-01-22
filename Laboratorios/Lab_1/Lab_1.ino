
using namespace std;

#define pinC1 6
#define pinC2 5
#define pinC3 4
#define pinC4 3
#define pinC5 15
#define pinC6 14
#define pinC7 13
#define pinC8 12

#define pinSA 11
#define pinSB 10
#define pinSC 9
#define pinSD 8

int x = 0;
int y = 0;

// Orange Ricky
int L[3][3] = {
    {1, 0, 0}, // 1
    {1, 0, 0}, // 2
    {1, 1, 0}, // 3
};

// Blue Ricky
int Linv[3][3] = {
    {0, 1, 0}, // 1
    {0, 1, 0}, // 2
    {1, 1, 0}, // 3
};

// Cleveland Z
int Z[3][3] = {
    {1, 1, 0}, // 1
    {0, 1, 1}, // 2
    {0, 0, 0}, // 2
};

// Rhode Island Z
int Zinv[3][3] = {
    {0, 1, 1}, // 1
    {1, 1, 0}, // 2
    {0, 0, 0}, // 2
};

// Hero
int line[4][4] = {
    {1, 0, 0, 0}, // 1
    {1, 0, 0, 0}, // 2
    {1, 0, 0, 0}, // 3
    {1, 0, 0, 0}, // 4
};

// Teewee
int T[2][3] = {
    {0, 1, 0}, // 1
    {1, 1, 1}, // 2
};

// Smashboy
int sqr[2][2] = {
    {1, 1}, // 1
    {1, 1}, // 2
};

int canvas[16][8] = {
    {0, 0, 0, 0, 0, 0, 0, 0}, // 1
    {0, 0, 0, 0, 0, 0, 0, 0}, // 2
    {0, 0, 0, 0, 0, 0, 0, 0}, // 3
    {0, 0, 0, 0, 0, 0, 0, 0}, // 4
    {0, 0, 0, 0, 0, 0, 0, 0}, // 5
    {0, 0, 0, 0, 0, 0, 0, 0}, // 6
    {0, 0, 0, 0, 0, 0, 0, 0}, // 7
    {0, 0, 0, 0, 0, 0, 0, 0}, // 8
    {0, 0, 0, 0, 0, 0, 0, 0}, // 9
    {0, 0, 0, 0, 0, 0, 0, 0}, // 10
    {0, 0, 0, 0, 0, 0, 0, 0}, // 11
    {0, 0, 0, 0, 0, 0, 0, 0}, // 12
    {0, 0, 0, 0, 0, 0, 0, 0}, // 13
    {0, 0, 0, 0, 0, 0, 0, 0}, // 14
    {0, 0, 0, 0, 0, 0, 0, 0}, // 15
    {0, 0, 0, 0, 0, 0, 0, 0}  // 16
};

void printFig(int x, int y, int **fig, string figName, int t, int rotation)
{
    for (int i = 0; i < t; i++)
    {
        for (int j = 0; j < t; j++)
        {
            if (figName == "L" or figName == "Linv" or figName == "T")
            {
                switch (rotation)
                {
                case 0:
                    canvas[x + i][y + j] = fig[i][j];
                    break;
                case 1:
                    canvas[x + i][y + j] = fig[j][t - 1 - i];
                    break;
                case 2:
                    canvas[x + i][y + j] = fig[t - 1 - i][t - 1 - j];
                    break;
                case 3:
                    canvas[x + i][y + j] = fig[t - 1 - j][i];
                    break;
                }
            }
            else if (figName == "Z" or figName == "Zinv")
            {
                switch (rotation)
                {
                case 0:
                    canvas[x + i][y + j] = fig[i][j];
                    break;
                case 1:
                    canvas[x + i][y + j] = fig[j][t - 1 - i];
                    break;
                }
            }
            else
            {
                canvas[x + i][y + j] = fig[i][j];
            }
        }
    }
}

void setCol(int col)
{
    digitalWrite(pinC1, col & 0x01);
    digitalWrite(pinC2, col & 0x02);
    digitalWrite(pinC3, col & 0x04);
    digitalWrite(pinC4, col & 0x08);
    digitalWrite(pinC5, col & 0x10);
    digitalWrite(pinC6, col & 0x20);
    digitalWrite(pinC7, col & 0x40);
    digitalWrite(pinC8, col & 0x80);
}

void setFil(int fil)
{
    digitalWrite(pinSA, fil & 0x01);
    digitalWrite(pinSB, fil & 0x02);
    digitalWrite(pinSC, fil & 0x04);
    digitalWrite(pinSD, fil & 0x08);
}

void printDisplay()
{
    int f = 1;
    int c = 1;
    for (int fil = 0; fil < 16; fil++)
    {
        for (int col = 0; col < 8; col++)
        {
            if (canvas[fil][col] == 1)
            {
                setCol(c);
                setFil(f);
            }

            c <<= 1;
            /*
                0001
                0010
                0100
                1000
            */
        }
        f += 1;
        /*
            0001
            0010
            0011
            0100
            0101
            0110
            0111
            1000
            1001
            1010
            1011
            1100
            1101
            1110
            1111
            0000
        */
    }
}

void setup()
{
}

void loop()
{
    printDisplay();
    delay(250);
}
