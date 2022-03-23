#include <iostream>
#include <vector>
#include <Windows.h>

using namespace std;

const int N = 2048;
const int S = 64;

float A[N][N];
float B[N][N];
float C[N][N];
float(&p1)[N][N] = A;
float(&p2)[N][N] = B;
float(&p3)[N][N] = C;

void Fill(float M[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            M[i][j] = rand() % 100;
        }
    }
}

void CommonMulti(float M1[N][N], float M2[N][N], float M3[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            float s = 0.0f;

            for (int k = 0; k < N; k++)
                s += M1[i][k] * M2[k][j];
            M3[i][j] = s;
        }
    }
}

void BuffCol(float M1[N][N], float M2[N][N], float M3[N][N])
{
    float buff[N];
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            buff[j] = M2[j][i];
        }

        for (int k = 0; k < N; k++)
        {
            float s = 0.0f;
            /*float s1 = 0.0f;
            float s2 = 0.0f;
            float s3 = 0.0f;
            float s4 = 0.0f;
            float s5 = 0.0f;
            float s6 = 0.0f;
            float s7 = 0.0f;
            float s8 = 0.0f;
            float s9 = 0.0f;
            float s10 = 0.0f;
            float s11 = 0.0f;
            float s12 = 0.0f;
            float s13 = 0.0f;
            float s14 = 0.0f;
            float s15 = 0.0f;
            float s16 = 0.0f;*/
            for (int l = 0; l < N; l++)
            {
                s += M1[k][l] * buff[l];
                /*s1 += M1[k][l] * buff[l];
                s2 += M1[k][l + 1] * buff[l + 1];
                s3 += M1[k][l + 2] * buff[l + 2];
                s4 += M1[k][l + 3] * buff[l + 3];
                s5 += M1[k][l + 4] * buff[l + 4];
                s6 += M1[k][l + 5] * buff[l + 5];
                s7 += M1[k][l + 6] * buff[l + 6];
                s8 += M1[k][l + 7] * buff[l + 7];
                s9 += M1[k][l + 8] * buff[l + 8];
                s10 += M1[k][l + 9] * buff[l + 9];
                s11 += M1[k][l + 10] * buff[l + 10];
                s12 += M1[k][l + 11] * buff[l + 11];
                s13 += M1[k][l + 12] * buff[l + 12];
                s14 += M1[k][l + 13] * buff[l + 13];
                s15 += M1[k][l + 14] * buff[l + 14];
                s16 += M1[k][l + 15] * buff[l + 15];*/
            }
            //s = s1 + s2 +s3 + s4 + s5 + s6 + s7 + s8 + s9 + s10 + s11 + s12 + s13 + s14 + s15 + s16;
            M3[k][i] = s;
        }
    }

}

void BlockMulti(float M1[N][N], float M2[N][N], float M3[N][N])
{
    float buffA[S][S];
    float buffB[S][S];

    for (int i = 0; i < N; i += S) 
    {
        for (int j = 0; j < N; j += S) 
        {
            float summ[S][S];
            for (int di = 0; di < S; di++) 
            {
                for (int dj = 0; dj < S; dj++) 
                {
                    summ[di][dj] = 0.0f;
                }
            }

            for (int di = 0; di < N / S; di++)
            {
                int b = di * S;
                for (int dj = 0; dj < S; dj++)
                {
                    for (int dk = 0; dk < S; dk++)
                    {
                        buffA[dj][dk] = M1[i + dj][b + dk];
                        buffB[dj][dk] = M2[b + dj][j + dk];
                    }
                }

                for (int dj = 0; dj < S; dj++)
                {
                    for (int dk = 0; dk < S; dk++)
                    {
                        float t = 0.0f;
                        float t1 = 0.0f;
                        float t2 = 0.0f;
                        float t3 = 0.0f;
                        float t4 = 0.0f;
                        /*float t5 = 0.0f;
                        float t6 = 0.0f;
                        float t7 = 0.0f;
                        float t8 = 0.0f;*/
                        for (int k = 0; k < S; k+=8) {
                            //t += buffA[dj][k] * buffB[k][dk];
                            t1 += buffA[dj][k] * buffB[k][dk];
                            t2 += buffA[dj][k + 1] * buffB[k + 1][dk];
                            t3 += buffA[dj][k + 2] * buffB[k + 2][dk];
                            t4 += buffA[dj][k + 3] * buffB[k + 3][dk];
                            /*t5 += buffA[dj][k + 4] * buffB[k + 4][dk];
                            t6 += buffA[dj][k + 5] * buffB[k + 5][dk];
                            t7 += buffA[dj][k + 6] * buffB[k + 6][dk];
                            t8 += buffA[dj][k + 7] * buffB[k + 7][dk];*/
                        }
                        t = t1 + t2 + t3 + t4;// +t5 + t6 + t7 + t8;
                        summ[dj][dk] += t;
                    }
                }

                for (int dj = 0; dj < S; dj++) 
                {
                    for (int dk = 0; dk < S; dk++) 
                    {
                        M3[i + dj][j + dk] = summ[dj][dk];
                    }
                }
            }
        }
    }
}

int main()
{
    setlocale(LC_ALL, "ru");
    cout.setf(ios_base::fixed);
    cout.precision(3);
    Fill(p1);
    Fill(p2);
    std::cout << "Choose method:\n";
    std::cout << "1 - Common multiplication\n";
    std::cout << "2 - Buffering multiplication\n";
    std::cout << "3 - Block multiplication\n";
    int num;
    __int64 start;
    __int64 end;
    cin >> num;
    switch (num)
    {
        case 1:
            start = _Query_perf_counter();
            CommonMulti(p1, p2, p3);
            end = _Query_perf_counter();
            break;
        case 2:
            start = _Query_perf_counter();
            BuffCol(p1, p2, p3);
            end = _Query_perf_counter();
            break;
        case 3:
            start = _Query_perf_counter();
            BlockMulti(p1, p2, p3);
            end = _Query_perf_counter();
            break;
    default:
        cout << "Incorrect value";
    }
    

    long long freq = _Query_perf_frequency();
    double b = (end - start) / (double)freq;
    std::cout << "QueryPerformanceCounter method\n" << "Ellapsed time: \n" << end - start << " ticks\n" << b << "s\n";
    /*for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cout << C[i][j] << " ";
        }
    }*/
    system("pause");
}
