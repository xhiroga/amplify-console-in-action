= Amplify Consoleの機能

//abstract{
AWS Amplify Consoleの機能は、インテグレーション・ビルド・ホスティングの3種類に分類できます。
3つの分類ごとに機能を紹介し、特に筆者がよく使うものについては詳細に解説します。
//}

== インテグレーション

Amplify Consoleは、マネジメントコンソールから手軽にGitHubなどのリポジトリと接続したワークフローを構築できます。
それらの接続は、Amplify ConsoleのビルドのトリガーとなるWebhookをGitプロバイダーに登録する形で実装されています。
//blankline
したがって、Webhookを利用して任意のタイミングでビルドを実行することもできます。機能は以下の通りです。

 * Incoming Webhookによるビルド実行
 * Gitプロバイダーとの連携機能(GitHub, BitBucket, GitLab, AWS CodeCommit)
 * Pull RequestごとにWeb Previewをデプロイ
 * ビルド成果物を保存しているストレージを直接指定(Manual Deploy)したデプロイ

=== Incoming Webhookのユースケース

まず考えられるのは、リポジトリのソースコード以外の更新をトリガーにWebコンテンツを最新化したいケースではないでしょうか。
例えば、ヘッドレスCMSでコンテンツに更新があった場合や、Git SubmoduleやGit Subtree、npmモジュールが更新された場合などが考えられます。
//blankline
ヘッドレスCMSサービスによっては、こうしたユースケースが想定されています。例えばContentfulでは、コンソールからリクエストするWebhookを登録することができます。
//blankline
他には、CircleCIなどの外部サービスでCI/CDを実行したいケースが考えられます。
段階的にAmplify Consoleに移行したい場合などが当てはまるでしょうか。

=== Pull Requestの Web Previewについて

GitHubなどで作成されたPull Requestごとに、成果物を一時的なURLにデプロイしてWebでPreviewできる機能です。
//blankline
GitHubでWeb Previewを有効にするには、対象のリポジトリに対してアクセス権のあるGitHubユーザーがAmplify Consoleに対して権限を付与する必要があります。
チームで運用する場合は、GitHub側にシステムユーザーを作成して作業するのがよいでしょう。
//blankline
便利な一方で、Web Previewには悩みもあります。
例えばビルドに失敗した場合、原因を知るためにAmplify Consoleにアクセスしなければいけません。GitHubのコンソールには原因が表示されないためです。
また、短い間隔でコミットを連投した場合の挙動が不安定です。詳細は@<secref>{chap05-trouble-shooting|ビルドに関するトラブル}をご覧ください。

== ビルド

一般的なCIサービスに求められる要件を満たしていると言えそうです。
Cypressと統合されたEnd-to-EndテストでUIの証跡を残せる点はポイントかもしれません。@<fn>{e446e9e4-74ac-4fcb-9e97-f910e45972de}

 * ビルド・テスト・デプロイ・キャッシュ利用・環境変数の仕組み
 * ビルドに用いるコンテナイメージ・IAMロールのカスタマイズ
 * ビルドの通知

//footnote[e446e9e4-74ac-4fcb-9e97-f910e45972de][Cypress Integrated with AWS Amplify Console for End-to-End Testing(https://www.cypress.io/blog/2019/10/02/cypress-integrated-with-aws-amplify-console-for-end-to-end-testing/)]

=== ビルドの通知の悩み

マネジメントコンソールからメール通知を設定できます。
また、EventBridgeでAmplify Consoleのビルドイベントをフックすることで、Lambdaなどの任意のサービスを動かすことができます。@<secref>{chap04-amplify-console-in-action|メール以外の通知}で解説します。

== ホスティング

CloudFrontとS3をベースに、Basic認証やキャッシュの即時無効化などの機能が提供されています。
ちなみにBasic認証ではブランチごとにパスワードを変更でき、またパスワードそのものの有無も設定できます。

 * Webコンテンツのホスティング・CDN
 * Basic認証によるアクセス制限
 * カスタムヘッダーの設定
 * リダイレクトの設定
 * アクセスログ
 * Route53の自動設定

なお、Route53の自動設定を行うには、Amplify Console アプリケーションと指定したドメイン名を登録しているHostedZoneが同じAWSアカウントに存在する必要があります。
外部のドメイン管理サービスや別のAWSアカウントのRoute53で管理している場合は、別途手動で設定が必要です。
