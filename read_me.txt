パーティクル設定の操作方法
1キー押し中:パーティクルの離散度を広げる(最大360°)
2キー押し中:パーティクルの離散度を狭める(最大1°)

3キー単押し:横方向の移動速度を高める
4キー単押し:横方向の移動速度を落とす

5キー単押し:縦方向の移動速度を高める
6キー単押し:縦方向の移動速度を落とす

7キー単押し:パーティクル画像を横長にする
8キー単押し:パーティクル画像を縦長にする

9キー単押し:1フレームで出すパーティクルを増やす(最大10個/1F)
0キー単押し:1フレームで出すパーティクルを減らす(最小1個/1F)

Nキー押し中:パーティクルのフェード時間を長くする(最大120F、約2秒)
Mキー押し中:パーティクルのフェード時間を短くする(最短0F、0.0秒)

Vキー押し中:パーティクルのフェード前の時間を長くする(最大180F、約3秒)
Bキー押し中:パーティクルのフェード前の時間を短くする(最短0F)

Jキー単押し:パーティクル画像の切り替え(〇か□)
Kキー単押し:加算合成描画と通常描画の切り替え


Enterキー
パーティクル情報をparticle_data.txtに出力

※色変えについて
色は手入力でのみ変更可能。
色を指定している場所：
particle.cpp(270行付近)の、SetParticle()関数の引数にXMFLOAT4型のものがある。
このXMFLOAT4型で色を指定している。数値の意味は左から
XMFLOAT4(赤、緑、青、透明度)となっている。
