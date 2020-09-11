= Amplify Consoleの機能

//abstract{
AWS Amplify Consoleの機能は、インテグレーション・ビルド・ホスティングの3種類に分類できます。
3つの分類ごとに機能を紹介し、特に筆者がよく使うものについては詳細に解説します。
//}

== インテグレーション

GitHubなどのGitプロバイダーと組み合わせて利用するAmplify Consoleですが、手動でビルドを実行することもできます。
そのように、CI/CDパイプラインを任意のタイミングで起動するための機能を紹介します。

 * Gitプロバイダーとの連携機能(GitHub, BitBucket, GitLab, AWS CodeCommit)
 * Pull RequestごとにWeb Previewのデプロイ
 * ビルド成果物を保存しているストレージの直接指定(Manual Deploy)
 * Incoming WebHookによるビルド実行

=== Pull Request の Web Previewについて

GitHub 等の Pull Request ごとにビルドを行い、一時的なURLに成果物をデプロイしてWebで確認できる機能です。

GitHubでPull Requestに対するWeb Previewを有効にするには、対象のリポジトリに対してアクセス権のあるGitHubユーザーがAmplify Consoleに対して権限を付与する必要があります。
チームで運用する場合は、GitHub側にシステムユーザーを作成して権限を付与するのがよいでしょう。

Web Previewには悩みもあります。
例えばビルドに失敗した場合、GitHubのコンソールで理由を知ることはできません。毎回Amplify Consoleにアクセスする必要があります。
また、短い間隔でコミットを連投した場合の挙動が不安定です。詳細は第5章のトラブルシューティングをご覧ください。

=== Incoming WebHookのユースケース

そもそも、GitHubなどのGitリポジトリ連携も内部的にはWebHookを用いています。単にAmplify側でWebHookの登録をしてくれるかどうか、という違いです。

まず挙げられるのは、ヘッドレスCMSなどを用いてコンテンツの更新をトリガーに静的Webサイトをビルドしたいケースです。
ヘッドレスCMSのContentfulではコンソールからリクエストするWebHookを登録できるので、間に連携のためのコードを書かなくてもよいでしょう。

他には、CI自体はCircleCIなどの外部サービスを利用したいケースも考えられます。
例えばテストだけは既存のCIワークフローを利用したい場合や、段階的にAmplifyに移行したい場合に有効ではないでしょうか。

== ビルド

内部的にはCodeBuildを利用しており、一般的なCIサービスに求められる要件を満たしていると言えそうです。
Cypressと統合されたEnd-to-EndテストでUIの証跡を残せる点はポイントかもしれません。@<fn>{e446e9e4-74ac-4fcb-9e97-f910e45972de}

 * ビルド・テスト・デプロイ・キャッシュ利用・環境変数の仕組み
 * ビルドに用いるコンテナイメージ・IAMロールのカスタマイズ
 * ビルドの通知

//footnote[e446e9e4-74ac-4fcb-9e97-f910e45972de][Cypress Integrated with AWS Amplify Console for End-to-End Testing(https://www.cypress.io/blog/2019/10/02/cypress-integrated-with-aws-amplify-console-for-end-to-end-testing/)]

=== ビルドの通知の悩み

AWSのコンソールからメール通知を設定できます。
また、Amazon EventBridgeを経由することでSNSのトピックで通知を受け取れます。それを利用してSlackへの通知を構築できるので、後ほどご紹介します。

== ホスティング

内部的にCloudFrontとS3を利用しています。Basic認証やキャッシュ無効化など、CloudFrontとS3の構成ではひと手間必要だった機能がマネージドに提供されているのは嬉しいですね。
ちなみにBasic認証ではブランチごとにパスワードを変更でき、またパスワードそのものの有無も設定できます。

 * Webコンテンツのホスティング・CDN
 * Basic認証によるアクセス制限
 * カスタムヘッダーの設定
 * リダイレクトの設定
 * アクセスログ
 * Route53の自動設定

なお、Route53の自動設定を行うには、Amplify Console アプリケーションと指定したドメイン名を登録しているHostedZoneが同じAWSアカウントに存在する必要があります。
外部のドメイン管理サービスや別のAWSアカウントのRoute53で管理している場合は、別途手動で設定が必要です。

== Amplify Console vs CloudFront+S3の機能比較

Amplify Console のパフォーマンスは、CloudFront + S3 と同レベルです。しかし、機能の違いがあります。
Amplify Consoleの優位点は、コミットごとの即時キャッシュ無効化・ブランチごとの自動デプロイ・Pull Request のWeb Preview 作成、パスワード保護などがマネージドサービスとして提供されていることです。
一方で、CloudFrontでは可能だったLambda@Edgeの利用は現在サポートされていません。したがって、IPアドレスによるアクセス制限・サーバーサイドレンダリングなどを実装することができません。
また、コスト面

Amplifyの優位点の一つに、特にドメインの設定をしていなくても amplify.com のドメインでWebサイトの公開ができる点が挙げられます。
一方で、CloudFront+S3の優位点はACLの設定とLambda@Edgeの利用です。これがあることで、CloudFront+S3の構成ではIPアドレスによるアクセス制限や、Lambda@EdgeによるSSRなどが実現できます。
