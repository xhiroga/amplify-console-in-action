= 入門Amplify Console

//abstract{
Amplify Consoleは、AWSが提供する静的Webホスティングサービスです。
NetlifyやVercel、Firebase Hostingらと同様に、GitHubリポジトリとの連携・統合されたCI/CDパイプライン・統合されたホスティングとCDNを備えるサービスです。
それらのサービスとの対比に加え、AWSのサービスの中でどう位置づけられるかも合わせて見ていきましょう。
//}

=={sec-ext} Amplify Consoleとは
AWSの静的Webホスティングサービスです。AWSコンソール上でWebアプリケーションのGitHubリポジトリとブランチを指定することで、コミットごとにWebアプリケーションを最新化してくれます。
また、PullRequestに対応して一時的なURLにWebアプリをデプロイしたり、E2Eテストを実行することもできます。

=== 静的Webホスティングサービス
2015年4月に、MakerLoop, Inc.（現: Netlify, Inc.）からNetlifyがリリースされました。@<fn>{de6c201c-3107-451b-9717-6b574ec64a8f}
日本では2016年から徐々に利用されているようです。例えば、QiitaのNetlifyに関する一番古い記事は2016年8月18日に投稿されています。@<fn>{93dcd09b-99af-48ab-8a45-49ff46fdfd1b}
S3+CloudFrontによる静的WebホスティングはAWSに慣れている人でも面倒なことから、AWSメインの開発者でもNetlifyのシンプルさを好む方もいたようです。@<fn>{91abfa0f-02ca-4b15-bc37-c1e37059ac28}

そうした状況を受けてか、2018年11月にAWSからAmplify Consoleがリリースされ、@<fn>{f9c89212-b773-4141-8af7-e644d93cca79}2019年4月に東京リージョンでも使えるようになりました。
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

=== 従来の S3+CloudFront 構成との違い

Amplify Consoleは、AWS自身がマネージするアカウント上で動作するS3+CloudFront+CodeBuild等で構成されたCI/CDパイプラインおよび、開発者のアカウントのRoute53とACMを合わせて設定してくれるサービスです。
最大のメリットは、AWSに不慣れな方でもGitリポジトリさえ指定すればWebアプリケーションのデプロイ環境が構築できることでしょう。
また、ある程度AWSに慣れている方であっても、CloudFrontの構築待ちをせずに済んだり、キャッシュの無効化のための仕組みを自作せずに済むメリットがあります。

TODO: 掘り下げる。

=={sec-ext} AmplifyファミリーとAmplify Console

AWS Amplifyは、AWSがフロントエンド向けに提供するサービスを総称するブランド名です。Amplify Consoleは、そのうち静的サイトホスティングを担うサービスに過ぎません。
まずは、AWS Amplifyブランドで提供されるサービスを概観します。

 * Amplifyフレームワーク - Amplifyライブラリー（SDK）
 * Amplifyフレームワーク - AmplifyUIコンポーネント
 * Amplifyフレームワーク - Amplify CLI
 * Amplify Console

Amplifyというブランド名でまとめられているものの、AmplifyフレームワークとAmplify Consoleには直接的な関係はありません。
ここで注意いただきたいのは、Amplify CLIで静的サイトの構築のためのCloudFormationのスタックを生成するようなチュートリアルが存在し、その中ではS3+CloudFrontによるデプロイメントパイプラインが構築される、ということです。
Web上でAmplifyの静的Webホスティングについて検索しても、よくAmplify CLIに関する記事がヒットします。したがって、Amplifyの記事を見かけたら、それがCLIなのかConsoleなのか注意して読むようにしてください。
