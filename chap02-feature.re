= Amplify Consoleの機能

//abstract{
AWS Amplify Consoleの機能は、インテグレーション・ビルド・ホスティングの3種類に分類できます。
3つの分類ごとに機能を紹介し、特に筆者がよく使うものについては詳細に解説します。
//}

=={sec-ext} インテグレーション

GitHubなどのGitプロバイダーと組み合わせて利用するAmplify Consoleですが、手動でビルドを実行することもできます。
そのように、CI/CDパイプラインを任意のタイミングで起動するための機能を紹介します。

 * Gitプロバイダーとの連携機能(GitHub, BitBucket, GitLab, AWS CodeCommit)
 * Pull RequestごとにPreviewの作成
 * ビルド成果物を保存しているストレージの直接指定(Manual Deploy)
 * Incoming WebHookによるビルド実行

=== Pull Request Previewの悩み

Pull Requestを自動で検出してくれるのは良いものの、Previewのビルド・デプロイが成功・失敗したときにbotによるコメントなどはありません。
また、ビルドが失敗した時の原因はAWSのコンソールで確認する必要があります。

=== Incoming WebHookのユースケース

まず挙げられるのは、ヘッドレスCMSなどを用いてコンテンツの更新をトリガーに静的Webサイトをビルドしたいケースです。
ヘッドレスCMSのContentfulではコンソールからリクエストするWebHookを登録できるので、間に連携のためのコードを書かなくてもよいでしょう。

他には、CI自体はCircleCIなどの外部サービスを利用したいケースも考えられます。
例えばテストだけは既存のCIワークフローを利用したい場合や、段階的にAmplifyに移行したい場合に有効ではないでしょうか。

=={sec-ext} ビルド

内部的にはCodeBuildを利用しており、一般的なCIサービスに求められる要件を満たしていると言えそうです。
Cypressと統合されたEnd-to-EndテストでUIの証跡を残せる点はポイントかもしれません。@<fn>{e446e9e4-74ac-4fcb-9e97-f910e45972de}

 * ビルド・テスト・デプロイ・キャッシュ利用・環境変数の仕組み
 * ビルドに用いるコンテナイメージ・IAMロールのカスタマイズ
 * ビルドの通知

//footnote[e446e9e4-74ac-4fcb-9e97-f910e45972de][Cypress Integrated with AWS Amplify Console for End-to-End Testing(https://www.cypress.io/blog/2019/10/02/cypress-integrated-with-aws-amplify-console-for-end-to-end-testing/)]

=== ビルドの通知の悩み

AWSのコンソールからメール通知を設定できます。
また、Amazon EventBridgeを経由することでSNSのトピックで通知を受け取れます。それを利用してSlackへの通知を構築できるので、後ほどご紹介します。

=={sec-ext} ホスティング

内部的にCloudFrontとS3を利用しています。Basic認証やキャッシュ無効化など、CloudFrontとS3の構成ではひと手間必要だった機能がマネージドに提供されているのは嬉しいですね。
ちなみにBasic認証ではブランチごとにパスワードを変更でき、またパスワードそのものの有無も設定できます。

 * Webサイトのホスティング・CDN
 * Basic認証によるアクセス制限
 * カスタムヘッダーの設定
 * リダイレクトの設定
 * アクセスログ
 * Route53の自動設定

なお、Route53の自動設定を行うには、Amplify Console アプリケーションと指定したドメイン名を登録しているHostedZoneが同じAWSアカウントに存在する必要があります。
外部のドメイン管理サービスや別のAWSアカウントのRoute53で管理している場合は、別途手動で設定が必要です。

== Amplify vs CloudFront+S3の機能比較

Amplifyの優位点の一つに、特にドメインの設定をしていなくても amplify.com のドメインでWebサイトの公開ができる点が挙げられます。
一方で、CloudFront+S3の優位点はACLの設定とLambda@Edgeの利用です。これがあることで、CloudFront+S3の構成ではIPアドレスによるアクセス制限や、Lambda@EdgeによるSSRなどが実現できます。
ただし、当然ながらコスト面ではAmplify > CloudFront+S3になっています。

TODO: 手軽さ、キャッシュのInvalidate、デルタデプロイも
