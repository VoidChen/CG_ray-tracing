編譯環境
    作業系統: Debian GNU/Linux testing (stretch)
    編譯器: GCC 6.2.0
    編譯參數: g++ -Wall main.cpp

基本功能
    Multiple sphere
        7個小球面
            6個不透明球面
            1個透明球面
        3個大球面
            1個透明球面
            1個鏡面球面
            1個不透明並有反射之球面

    Recursive intersection with refraction and transmission
        trace function 以遞迴方式計算

    Material attribute
        反射係數
        折射率
        合成直射、反射及折射之係數
        Attenuation coefficient

額外功能
    Ray-plane intersection
        1個 y=-25 之平面

    Antialiasing
        利用 Supersampling 之方式, 每個 pixel 皆以數個 primary ray 取樣結果之平均值計算

    BMP format output
        以 BMP 格式輸出

    Attenuation
        以各材質之attenuation coefficient及光穿越該物體之距離計算光透過該物體後之強度
