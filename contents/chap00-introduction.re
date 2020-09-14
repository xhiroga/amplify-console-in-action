= はじめに

本書を手にとっていただきありがとうございます。
Amplify Consoleを利用してWebサイト・Webアプリケーションのホスティングを検討している方や、既に活用されている方に対して、Amplify Consoleを現場で運用して得られた知見を共有したいと考えて本書を執筆しました。
//blankline

Amplify Consoleを使えば、フロントエンド開発のベストプラクティスを手軽に導入できます。
Amplify Consoleの登場以前は、AWSであればS3、CloudFront、CodeBuildなどを組み合わせたCI/CDパイプラインを自前で構築する必要がありました。
Amplify Consoleの登場によって、それらの構築は不要になりました。それだけでなく、Pull Requestの作成に応じたWeb Previewやコミットごとのキャッシュの自動的な即時無効化などの機能も提供されています。
//blankline

しかし、Amplify Consoleは登場してから日の浅いサービスでもあります。便利な一方で、通知やビルドの設定で悩まされることは誰もが通る道です。
また、Amplifyファミリー、特にAmplify CLIと混同することで、検索がしづらくなっている面も否めません。
そうした状況で、本書が少しでもAmplify Consoleを実践するための助けになれば幸いです。
//blankline

筆者は2019年に業務でAmplify Consoleを導入して以来、半年のうちに3つ以上のAWSアカウントで合計20以上のWebアプリケーションをセットアップしてきました。
少人数のチームで多くのアプリケーションを管理するために、Amplify Consoleの機能の活用、CloudFormationおよびAWS CDKを使った一括管理、様々なトラブルシューティングを行ってきました。
//blankline

本書では、そうした経験から得られたAmplify Consoleを扱う上での知見を共有します。
これからAmplify Consoleに触る方も、既にAmplify Consoleを導入されている方も、Amplify Consoleを実践する上で何らかの発見があれば幸いです。

== 本書で扱うこと

 * Amplify Consoleの基本的な機能
 * Amplify Consoleを実践するための知見
 * Amplify Consoleに関するトラブルシューティング

== 本書で扱わないこと

 * Amplify Consoleのチュートリアル
 * Amplify Framework（Amplify CLIなど）を利用した開発

== 本書の構成

基本的な機能を紹介する前半と、実践した上での知見をご紹介する後半に分かれています。
//blankline

前半の第1章では静的WebホスティングとAmplify Consoleについて、第2章ではAmplify Consoleの基本的な機能についてご紹介します。
後半の第3章ではAmplify ConsoleとCloudFormation・AWS CDKについて、第4章では実践する上でのテクニックをご紹介します。また、第5章では筆者が対応したトラブルシューティングを簡単にご紹介します。

== 意見と質問

本書はAWSドキュメントやサポートに確認した内容をもとに執筆していますが、誤りや不正確な表現に気づかれることもあるかと思います。また、本書で紹介するやり方よりもよいやり方をご存知の方もいるかもしれません。
そうした点については、今後の版で随時更新させていただきたいのでお知らせいただけると幸いです。ご意見だけでなく質問も大歓迎です。連絡先を以下に記します。

 * Mail: @<href>{mailto://hiroga1030@gmail.com, hiroga1030@gmail.com}
 * Twitter: @<href>{https://twitter.com/hiroga_cc, @hiroga_cc}
