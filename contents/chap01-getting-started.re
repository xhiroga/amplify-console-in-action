= 入門Amplify Console

//abstract{
Amplify Consoleは、AWSの静的Webホスティングサービスです。
NetlifyやVercel、Firebase Hostingらと同様に、GitHub等と連携したCI/CDパイプライン・ホスティング・CDNを備えるサービスです。
//blankline
それらのサービスとの対比に加え、AWSのサービスの中でどう位置づけられるかも合わせて見ていきましょう。
//}

=={sec-ext} Amplify Console

=== 静的Webホスティングサービス
本書における静的Webホスティングサービスとは、Gitリポジトリと連携したCI/CDパイプラインを備え、SPAや静的サイトをデプロイできるサービスをいいます。
//blankline
2015年4月に、MakerLoop, Inc.（現: Netlify, Inc.）からNetlifyがリリースされました。@<fn>{de6c201c-3107-451b-9717-6b574ec64a8f}
//blankline
日本では2016年から徐々に利用されているようです。例えば、QiitaのNetlifyに関する一番古い記事は2016年8月18日に投稿されています。@<fn>{93dcd09b-99af-48ab-8a45-49ff46fdfd1b}
S3+CloudFrontによる静的WebホスティングはAWSに慣れている人でも面倒なことから、AWSメインの開発者でもNetlifyのシンプルさを好む方もいたようです。@<fn>{91abfa0f-02ca-4b15-bc37-c1e37059ac28}

=== Amplify Console

そうした状況を受けてか、2018年11月にAWSからAmplify Consoleがリリースされ、@<fn>{f9c89212-b773-4141-8af7-e644d93cca79}2019年4月に東京リージョンでも使えるようになりました。

TODO: 内部的にS3+CloudFront＋CodeBuild、スクショ

=== Amplify Console以外の静的Webホスティングサービス

2020年9月現在は大手クラウドベンダー含め複数のサービスがあるので、以下にまとめます。

 * AWS Amplify Console
 * Firebase Hosting
 * Azure Static Web Apps
 * Netlify
 * Vercel@<fn>{7c571916-3b38-4e1b-96bd-cf57f51dd4a1}

//footnote[de6c201c-3107-451b-9717-6b574ec64a8f][https://aws.amazon.com/jp/amplify/console/]
//footnote[93dcd09b-99af-48ab-8a45-49ff46fdfd1b][高機能ホスティングサービスNetlifyについて調べて使ってみた(https://qiita.com/TakahiRoyte/items/b7c4d1581df1a17a93fb)]
//footnote[91abfa0f-02ca-4b15-bc37-c1e37059ac28][ちなみにNetlifyのインフラはAWSです。]
//footnote[f9c89212-b773-4141-8af7-e644d93cca79][Document History for AWS Amplify(https://docs.aws.amazon.com/amplify/latest/userguide/document-history.html)]
//footnote[7c571916-3b38-4e1b-96bd-cf57f51dd4a1][2020年4月にZEITから改称]

=={sec-ext} AmplifyファミリーとAmplify Console

AWS Amplifyは、AWSがフロントエンド向けに提供するサービスを総称するブランド名です。Amplify Consoleは、そのうち静的サイトホスティングを担うサービスに過ぎません。
まずは、AWS Amplifyブランドで提供されるサービスを概観します。

 * Amplifyフレームワーク - Amplifyライブラリー（SDK）
 * Amplifyフレームワーク - AmplifyUIコンポーネント
 * Amplifyフレームワーク - Amplify CLI
 * Amplify Console

ここで注意いただきたいのは、Amplify CLIで静的サイトの構築のためのCloudFormationのスタックを生成するようなチュートリアルが存在し、その中ではS3+CloudFrontによるデプロイメントパイプラインが構築される、ということです。
Web上でAmplifyの静的Webホスティングについて検索しても、よくAmplify CLIに関する記事がヒットします。したがって、Amplifyの記事を見かけたら、それがCLIなのかConsoleなのか注意して読むようにしてください。

//note[静的ウェブホスティングという分類について]{
本書を書くにあたって悩んだことのひとつが、静的ウェブホスティングという分類についてです。それぞれのサービスごとに呼び名が違っているため、何を採用するか悩みました。

まずは各ベンダーが自社サービスをどのように呼んでいるか見てみましょう（一部筆者訳）

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

ご覧の通り、標準的な名前が定まっていないことが分かります。
また、技術スタックの比較サービスである "StackShare" では、静的ウェブホスティング（static web hosting）という分類が設けられています。@<fn>{6e13296f-92e4-4553-806e-67024802a065}
ただし、この分類にはJavaScriptアプリケーションに最適化されたサービスではない GitHub Pagesや GitLab Pagesも含まれており、本書で示したい分類よりも多少広いといえるでしょう。

//footnote[6e13296f-92e4-4553-806e-67024802a065][https://stackshare.io/static-web-hosting]

悩んだ挙げ句、「この本はAmplify本なんだから、AWSでの呼び名を採用すればいいや」という半ば思考停止的な理由で本書では "静的ウェブホスティング" を用いることにしました。
もし将来標準的な呼び名が決まったら、改訂版を出そうと思います。笑

//}
