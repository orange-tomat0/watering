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

### ディレクトリの役割

- `source/main/`  
  プロジェクトの **メインスケッチ** を置く場所です。  
  例: `main.ino`  `main.h` 
  → 基本的にはここにプログラムのエントリーポイントを置きます。

- `source/libraries/`  
  プロジェクト専用の **拡張ライブラリ** を追加する場所です。  
  → 自作関数やクラス、ヘッダーファイルなどをここに追加します。  
  → 例: `MySensor/MySensor.h` と `MySensor/MySensor.cpp`

- `external/libraries/`  
  外部から導入したライブラリ（M5Stack公式やArduino公式など）を置く場所です。

## ⚙️ 事前準備

### 1. Arduino CLI のインストール
[Arduino CLI公式ページ](https://arduino.github.io/arduino-cli/latest/installation/) に従ってインストールします。

### 2. Make のインストール
[Make for Windowsインストール](https://gnuwin32.sourceforge.net/downlinks/make.php)　これを実行してexeファイルをダウンロード&実行

### 3. Windowsでパスを通す

#### Arduino CLI のパスを通す

1. Arduino CLI を解凍またはインストールしたフォルダ（例：`C:\Users\ユーザー名\arduino-cli`）を確認。
2. 環境変数 `PATH` に追加：
   - Windows の「環境変数」設定を開く
   - 「ユーザー環境変数」または「システム環境変数」の `Path` を編集
   - Arduino CLI のパス（例：`C:\Users\ユーザー名\arduino-cli`）を追加

#### Make のパスを通す

1. Make の `bin` フォルダ（例：`C:\Program Files (x86)\GnuWin32\bin`）を確認。
2. 同様に `PATH` に追加。

#### 確認

コマンドプロンプトで以下を実行：

```cmd
arduino-cli version
make --version
```
それぞれのバージョンが出力されたらOK

### 4. 初期セットアップ
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

##　著者
watanabe 
