# 🚀 M5Stack CoreS3 Build & Upload

このプロジェクトは、**Arduino CLI** と **Makefile** を使用して  
M5Stack CoreS3向けのプログラムを簡単に **ビルド**・**アップロード** できるようにするための設定です。

# 📁 プロジェクト構成
````
project_root/
├── Makefile
├── arduino-cli.yaml
├── external/
│ ├── boards/ ← 外部ボード定義
│ └── libraries/ ← 外部ライブラリ
├── source/
│ ├── main/
│ │ └── main.ino
│ └── libraries/
├── build/ ← ビルド成果物（.binファイルなど）が出力される
└── tmp/
├── build/ ← 一時ビルドキャッシュ
├── cache/ ← Arduino CLI のキャッシュ
└── downloads/ ← ボードやライブラリの一時ダウンロード
````

## ⚙️ 事前準備

### 1. Arduino CLI のインストール
[Arduino CLI公式ページ](https://arduino.github.io/arduino-cli/latest/installation/) に従ってインストールします。

### 2. Make のインストール
[Make for Windowsインストール](https://gnuwin32.sourceforge.net/downlinks/make.php)　これを実行してexeファイルをダウンロード&実行

### 3. 初期セットアップ
```
make first-setup
```
このコマンドで以下が自動的に行われます：

- ボードマネージャの更新  
- `m5stack:esp32` のインストール  
- `M5CoreS3` ライブラリのインストール  

## 🛠️ ビルド

スケッチ（`source/main/main.ino`）をビルドするには以下を実行します：
```
make
```
ビルド成果物（例：`main.ino.bin`）は `build/` に出力されます。

## 🔌 アップロード

M5Stack CoreS3 をPCに接続し、シリアルポート（例：`COM3`）を確認します。  
必要に応じて `Makefile` 内の以下の行を変更してください：
```
SERIAL_DEV ?= COM3
```
その後、以下を実行：
```
make upload
```
これにより、ビルド済みのバイナリがデバイスに書き込まれます。

---

## 📄 主なMakeターゲット

| コマンド | 説明 |
|-----------|------|
| `make first-setup` | Arduino CLIの初期設定とライブラリ導入 |
| `make` | ソースコードのビルド |
| `make upload` | コンパイル済みバイナリをM5Stack CoreS3へアップロード |