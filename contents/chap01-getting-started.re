= 入門Amplify Console

//abstract{
Amplify Consoleは、AWSの静的Webホスティングサービスです。
NetlifyやVercel、Firebase Hostingらと同様に、GitHubなどと連携したCI/CDパイプライン・ホスティング・CDNを備えています。
それらのサービスとの対比に加え、AWSのサービスの中でどう位置づけられるかも合わせて見ていきましょう。
//}

== Amplify Console

=== 静的Webホスティングサービス
本書における静的Webホスティングサービスとは、Gitリポジトリと連携したCI/CDパイプラインを備え、SPAや静的サイトをデプロイできるサービスをいいます。
//blankline
代表的な静的WebホスティングサービスであるNetlifyは、2015年4月に、MakerLoop, Inc.（現: Netlify, Inc.）からリリースされました。@<fn>{de6c201c-3107-451b-9717-6b574ec64a8f}
//blankline
Netlifyは日本では2016年頃から徐々に利用されているようです。
例えば、Netlifyに関する一番古いQiitaの記事は2016年8月18日に投稿されています。@<fn>{93dcd09b-99af-48ab-8a45-49ff46fdfd1b}
当時はAmplify Consoleがなかったので、AWSでCloudFront+S3を運用している方がNetlifyのシンプルさに惹かれるということもあったようです。@<fn>{e7ee5b91-0c84-4e16-bd2f-b82ef813c713}@<fn>{91abfa0f-02ca-4b15-bc37-c1e37059ac28}

//footnote[de6c201c-3107-451b-9717-6b574ec64a8f][https://aws.amazon.com/jp/amplify/console/]
//footnote[93dcd09b-99af-48ab-8a45-49ff46fdfd1b][高機能ホスティングサービスNetlifyについて調べて使ってみた(https://qiita.com/TakahiRoyte/items/b7c4d1581df1a17a93fb)]
//footnote[e7ee5b91-0c84-4e16-bd2f-b82ef813c713][HTTPSの静的コンテンツをホストするならs3よりNetlifyが俺の求めていたものだった(https://qiita.com/shogomuranushi/items/6ab5bc29923b3f82c9ed)]
//footnote[91abfa0f-02ca-4b15-bc37-c1e37059ac28][ちなみにNetlifyのインフラはAWSです。]

=== Amplify Console

Amplify Consoleは、2018年11月にAWSからリリースされた静的Webホスティングサービスです。@<fn>{f9c89212-b773-4141-8af7-e644d93cca79}2019年4月に東京リージョンでも使えるようになりました。
//blankline
CloudFrontとS3とCodeBuildの設定を自動化したサービスと言えるかもしれません。
ただし、CloudFrontのディストリビューションやS3のバケットはAWSが管理するAWSアカウント内に作成されるので、私達が気にする必要はありません。

#@+++
ここはjustInCaseで許可取ってから載せる
実際にAmplify Console で構築したサービスをWappalyzer@<fn>{00b1467c-cbe4-4e05-8756-7f2570bcdaab}で検索すると、CloudFrontとS3で構築されています。
//footnote[00b1467c-cbe4-4e05-8756-7f2570bcdaab][Webサイトの技術スタックを解析するアプリケーション(https://www.wappalyzer.com/)]
#@---

=== Amplify Console以外の静的Webホスティングサービス

2020年9月現在、大手クラウドベンダーのサービスを含めた複数の静的Webホスティングサービスがあります。

 * AWS Amplify Console
 * Firebase Hosting
 * Azure Static Web Apps
 * Netlify
 * Vercel@<fn>{7c571916-3b38-4e1b-96bd-cf57f51dd4a1}

//footnote[f9c89212-b773-4141-8af7-e644d93cca79][Document History for AWS Amplify(https://docs.aws.amazon.com/amplify/latest/userguide/document-history.html)]
//footnote[7c571916-3b38-4e1b-96bd-cf57f51dd4a1][2020年4月にZEITから改称]

== AmplifyファミリーとAmplify Console

AWS Amplifyは、AWSがフロントエンド向けに提供するサービスを総称するブランド名です。Amplify Consoleは、そのうち静的サイトホスティングを担うサービスに過ぎません。
AWS Amplifyブランドで提供されるサービスは以下の通りです。

 * Amplifyフレームワーク - Amplifyライブラリー（SDK）
 * Amplifyフレームワーク - AmplifyUIコンポーネント
 * Amplifyフレームワーク - Amplify CLI
 * Amplify Console

特に注意したいのは、Amplifyによる静的WebホスティングサービスはAmplify ConsoleとAmplify CLIの2つがあることです。
Amplify CLIはいわばブートストラップで、ユーザーの質問に対して動的にCloudFormationのテンプレートを生成・デプロイします。その中には、CloudFront+S3やAmplify Consoleによる静的Webホスティングも含まれます。
Amplify Consoleについて検索していたら、いつの間にかCloudFront+S3を構築していた...とならないよう、Amplifyに関する記事を読むときはAmplify CLIとAmplify Consoleのどちらを指しているのか注意してください。

//note[コラム: 静的ウェブホスティングという分類について]{
本書を書くにあたって悩んだことのひとつが、静的ウェブホスティングという呼び方です。実は、ベンダーごとに呼び方が異なります。
各ベンダーが自社サービスをどのように呼んでいるか見てみましょう（一部筆者訳）

 * 静的ウェブホスティングサービス（AWS）@<fn>{deeae56f-3189-4dbd-9f4b-6b9ac940520c}
 * ウェブ コンテンツ ホスティング（Firebase）@<fn>{d95826c8-df94-444b-b0e8-a6c13af47edd}
 * GitHub リポジトリから Azure にフルスタック Web アプリを自動的に構築してデプロイするサービス（Azure）@<fn>{7ac745d4-683b-400d-a494-8813151f5ce9}
 * モダンなWebプロジェクトのAll-in-Oneプラットフォーム（Netlify）@<fn>{1b61c027-e1ce-497d-b64b-fd1b44d48291}
 * ワークフローと完璧に合致する静的サイトとサーバレスファンクションのクラウドプラットフォーム（Vercel）@<fn>{c9ac8488-7450-4a43-b2a2-575ef81d240f}

//footnote[deeae56f-3189-4dbd-9f4b-6b9ac940520c][https://aws.amazon.com/jp/amplify/console/]
//footnote[d95826c8-df94-444b-b0e8-a6c13af47edd][https://firebase.google.com/docs/hosting/]
//footnote[7ac745d4-683b-400d-a494-8813151f5ce9][https://docs.microsoft.com/ja-jp/azure/static-web-apps/overview]
//footnote[1b61c027-e1ce-497d-b64b-fd1b44d48291][https://docs.netlify.com/]
//footnote[c9ac8488-7450-4a43-b2a2-575ef81d240f][https://vercel.com/docs]

ご覧の通り、標準的な呼び名が定まっていません。
//blankline
悩んだ挙げ句、「この本はAmplify本なんだから、AWSでの呼び名を採用すればいいや」という半ば思考停止的な理由で本書では "静的ウェブホスティング" を用いることにしました。
もし将来標準的な呼び名が決まったら、改訂版を出そうと思います。笑

//}
