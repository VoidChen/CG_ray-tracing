編譯環境
    作業系統: Debian GNU/Linux testing (stretch)
    編譯器: g++ 5.4.0
    編譯參數: g++ -Wall --std=c++11 main.cpp

額外功能
    Multiple sphere
        包含兩個球面, 球心分別位於 (6, 10, -40), (-6, -3, -35), 半徑皆為6
    Ray-plane intersection
        包含一個 y=-25 之平面
    Antialiasing
        利用 Supersampling 之方式, 每個 pixel 皆以數個 primary ray 取樣結果之平均值計算
