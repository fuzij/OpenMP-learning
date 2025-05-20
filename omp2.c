/*積分による円周率の近似*/
#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

#define F(X) 4.0L/(1.0L + (X) * (X)) //[0~1]定積分したい関数 F(x) = 4/(1+x^2)

int main(int argc, char *argv[]){
    int i, num_intervals; //num_intervalsは分割数
    long double x, step, sum = 0.0l; //step = (1.0 / num_intervals)
    double st_time, en_time; //st_time:計算開始時間 en_time:計算終了時間

    if(argc!=3){
        exit(1); //スレッド数, 分割数の引数が過不足なく設定されていない時は自動修了
    }

    omp_set_num_threads(atoi(argv[1])); //第1引数をスレッド数として設定
    num_intervals=atoi(argv[2]); //積分の分割数

    st_time = omp_get_wtime(); //現在の時間を記録
    step = 1.0L / num_intervals; //1stepの幅を計算

    #pragma omp parallel for reduction(+:sum) private(x) //以下のforループを並列化 各スレッドでsumを個別計算し合計する
    for(i = 0; i < num_intervals; i++){ //積分区間[0, 1]をnum_intervals個に分割し積分計算
        x = (i + 0.5L) * step; //各区間の中央のxの値をとる
        sum += F(x); //F(x) = 4/(1+x^2) の値を合計を保存していく
    }
    sum *= step; //和にステップ幅をかけて面積にする
    en_time = omp_get_wtime(); //終了時間を記録

    printf("threads=%2d Etime=%.6f sum=%.30Lf\n", omp_get_max_threads(), en_time-st_time, sum); //スレッド数・時間・積分結果を出力

    return 0;
}