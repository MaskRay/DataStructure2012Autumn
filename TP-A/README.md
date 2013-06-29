% 積木
% MaskRay
% 2012年12月16日

## 目錄結構

```
.
|── build
├── data
│   └── generator.rb        數據生成器
├── Makefile
├── README.md               說明
├── src
│   ├── author
│   │   ├── solution.cc     C++ 源文件
│   │   ├── solution.hs     Haskell 源文件
│   │   ├── solution.md     題解 Markdown 源文件
│   │   └── solution.pdf    題解
│   └── reviewer
├── task.md
├── task.pdf
├── TP-A.tar.gz
└── util
    └── pandoc-latex.tex
```

## 數據生成

使用 `data/generator` 需要安裝 ruby-1.8 或 ruby-1.9，它接受兩個參數，第二個參數即爲題目中的 $n$，
第一個參數用於在數據開頭產生一些初始隊列驗證用戶程序的有效性。

使用 `make data` 生成20組測試數據。
