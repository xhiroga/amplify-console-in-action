# AWS Amplify Console 実践入門

## 更新終了のお知らせ

本書の執筆時、筆者はAmplify Console（現在はAmplify Hosting）を業務で利用し、そこで知り得た知見を共有できることに喜びを感じておりました。
しかし、ここ3年ほどは別の技術を利用する機会が増え、Amplify Consoleの最新の知見や変更を追うことが困難となってしまいました。

さらに、現在の私の関心は新しい技術に移りつつあり、公私共にそちらに力を注ぎたいと考えております。
その一方で、本書の誤りや古くなった情報を放置することは、読者の皆様にとって不利益となると考えております。

そこで、一つの決断を下しました。本書を非公開にする代わりに、本文をそのGitHubのリポジトリごと無償公開することにします。
これにより、誤りや古くなった情報について、読者の皆様で更新いただくことが可能です。

これまで有償で本書をご購入いただいた皆様には、深くお礼を申し上げます。
有償で購入いただいた書籍が無償公開されることについて、不利益を被ったと感じられる方もいらっしゃると思います。
購入者の方に公平な埋め合わせを、とも考えたのですが、販売形態や同人誌であることから現実的ではありませんでした。
代わりに、技術イベントやSNSでやり取りさせていただく際には、改めて深くお礼をさせてくださいませ。

以下、主に本書刊行時点（2020年9月）時点の情報を元に執筆しております。多少なりとも読者の方のお役に立てば幸いです。

どうぞよろしくお願いいたします。

## 商品紹介用

### 商品紹介文

Amplify Console を導入された方・検討している方に向けて、@xhiroga が現場で得た知見を共有するために書きました。

筆者は 2019 年に Amplify Console をプロダクションに導入して以来、3 つ以上の AWS アカウントで合計 20 以上の Web アプリケーションをセットアップしました。

そうした経験から得た、Amplify Console の機能の概観・業務に取り入れるためのテクニック・トラブルシューティングなどにを紹介いたします。
これから Amplify Console に触る方も、既に Amplify Console を導入されている方も、Amplify Console を実践する上での何らかの発見があれば幸いです。

### 対象となる読者

以下に当てはまる方は、本書を読むと AWS のドキュメントの理解・処理の実装が効率化できるかもしれません。
・Amplify Console の導入を検討されている方
・Amplify Console で手が届かない機能、困っていることの解決方法を探している方

以下に当てはまる方には、Amplify Console の役割を見直す効果があるかもしれません。
・現場で Amplify Console を利用されている方

## ビルド

```shell
# TODO: use vars instead of secrets.
act -j deploy-prod -s AWS_ACCESS_KEY_ID=${AWS_ACCESS_KEY_ID} -s AWS_SECRET_ACCESS_KEY=${AWS_SECRET_ACCESS_KEY} -s AWS_SESSION_TOKEN=${AWS_SESSION_TOKEN} --artifact-server-path .artifacts
```

## 商品リンク

- [\[更新終了につき無償公開\] Amplify Console 実践入門 - hiroga - BOOTH](https://hiroga.booth.pm/items/2376840)
- [\[体験版\] Amplify Console 実践入門 - hiroga - BOOTH](https://hiroga.booth.pm/items/2372813)
- [Amplify Console 実践入門 - さわら - 技術書点マーケット](https://techbookfest.org/product/4838711567056896)（販売終了）
- [Kindle](https://kdp.amazon.com/en_US/bookshelf)
