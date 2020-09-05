= はじめに

Webアプリケーションのフロントエンドの継続的な開発にはベストプラクティスがあります。GitをトリガーにCI/CDが動作すること。PullRequestに対して、プレビュー用のURLを発行すること。その過程をチャットで通知すること。

一昔前ならS3 + CloudFront + CIなどを組み合わせて独自のパイプライン構築が必要でした。しかしいまや、CI/CD同梱のサーバレスなWebアプリケーションホスティングサービスには多数の選択肢があります。
それらの選択肢のうち、AWSが提供するのがAWS Amplify Consoleです。AWSの様々なサービスとの一元的な管理や、Route53とのシームレスな連携が強みと言えるでしょう。
その一方で初心者には分かりづらい点も多く、特にその他のAmplifyファミリーと混同することは容易に想像できます（なお予めお断りしておきますが、この本はAmplify Consoleだけを対象にしています）

筆者は2019年にAmplify Consoleに初めて触り、それから約半年のうちに3つ以上のAWSアカウントで合計20以上のWebアプリケーションをセットアップしてきました。少人数のチームで大量のアプリケーションを管理するために、様々な工夫をしています。
そのためにAmplify Consoleの機能を活用し、またAWSならではの強力な構成管理ツール（CloudFormationとCDK）を活用して社内の複数のWebアプリケーションのデプロイを一元管理しています。

本書では、そうした経験から得られたAmplify Consoleを扱う上でのテクニックを公開します。これからAmplify Consoleに触る方が、本書を参考に1日でも早く理想のCI/CDパイプラインを構築できれば幸いです。

=={sec-ext} 本書で扱うこと

* Amplify Consoleの基本的な機能
* Amplify Consoleとそれ以外のAWSサービスとの関係
* Amplify Consoleを現場で活用するためのテクニック
* Amplify Consoleに関するトラブルシューティング

=={sec-ext} 本書で扱わないこと

 * Amplify Consoleの基本的な仕様@<fn>{a72f2df2-5366-4ca7-9826-1cfda7a69c25}
 * サンプルアプリケーションやチュートリアル
 * Amplify CLI
 * Amplify Framework
 * カスタムバックエンド

//footnote[a72f2df2-5366-4ca7-9826-1cfda7a69c25][AWSの公式ドキュメントをご覧ください。]

=={sec-ext} 本書の構成

初めに第一章で、Amplify Consoleについての基本的な紹介を行います。NetlifyなどAmplify Console以外の選択肢の紹介や、Amplify CLIなどのAmplifyファミリーの紹介もここでします。
次に第二章では、それまでのAWSのサービスにおけるフロントエンドCI／CDパイプライン構築とAmplify Consoleを比較します。
続く第三章でAmplify Consoleの構成管理について、第4章ではカスタムビルドやSlack通知の構築などの発展的なトピックを扱います。
最後の第五章では、筆者のチームが実際に遭遇したトラブルと、その対応をまとめました。読者の方のご参考になれば幸いです。

=={sec-ext} 意見と質問

本書はAWSドキュメントやサポートに確認した内容をもとに執筆していますが、誤りや不正確な表現に気づかれることもあるかと思います。また、本書で紹介するやり方よりもよいやり方をご存知の方もいるかもしれません。
そうした点については、今後の版で随時更新させていただきたいのでお知らせいただけると幸いです。ご意見だけでなく質問も大歓迎です。連絡先を以下に記します。

 * Mail: hiroga1030@gmail.com
 * Twitter: @hiroga_cc
