= 実践Amplify Console

//abstract{
Amplify Consoleを複数のWebアプリおよび本番を含む複数の環境で運用して得られた知見を共有します。
//}

== ビルド設定のカスタマイズ

=== AWSのコンソール以外から独自のDockerイメージを使用する

ドキュメントには記述がありませんが、AWSのコンソール以外からでもビルドに使用するイメージを変更できます。
環境変数に `_CUSTOM_IMAGE` を設定し、値に `justincasetech/node:12.14.1-aws-cli-stretch` のようにオリジナルのDockerイメージを指定することで可能です。

最新バージョンのNode.jsを利用したいケースなどで有益ではないでしょうか。

=== サービスロールの変更

AmplifyのCI/CDワークフロー中に、別のAWSリソースにアクセスしたい場合があります。
例えばParameter StoreやSecret ManagerからAPIキーなどを取得するケースでしょうか。
そうした場合、AmplifyのためのIAM Roleを作成し、Amplifyで使用するように指定するとアクセス可能になります。

なお、サービスロール自体はAmplifyのコンソールではなくIAMのコンソールからでも作成可能です。
その際は Trusted entitiesで`amplify.amazonaws.com` を指定してください。

=== メール以外の通知設定

公式ドキュメントには説明がありませんが、EventBridgeとLambdaを組み合わせることでSlack等に通知が送れるようになります。

そもそもAWSのコンソールから設定できるメール通知ですが、以下のようなサービスの組み合わせで成り立っています。

Amplify Console -> EventBridge -> SNS

ここでAmazon EventBridgeについて簡単にご説明します。AWSのサービス内で発生した事象を通知してくれるサービスで、例えばECSのタスクの状態変化に応じてLambdaを起動するようなことが可能です。
したがってAmplify ConsoleからEventBridgeにメッセージを送信する設定ができれば、ビルド通知のカスタマイズも可能ということがわかると思います。

さて、Amplify ConsoleからEventBridgeにイベントが通知される仕組みですが、Amplify Consoleアプリケーションと対象のブランチによって一意になる名前のEventBridge Ruleに対して自動でイベントが通知されています。
例えば、アプリケーションのIDが `abcde12345678`、対象のブランチが `master` なら、 `amplify-abcde12345678-master-branch-notification` という名前のRuleに対して自動でイベントが通知されます。
ちなみに、全てのブランチが対象の場合は `amplify-abcde12345678-AMPLIBRANCHSENTINEL-branch-notification` のような名前になります。

EventBridgeのRuleが定まれば、後はLambdaを定義するだけです。
参考までに、以下のようなイベントが流れてきます。


//terminal[Lambdaが受け取るEvent(ビルド成功時)]{
{
  "version": "0",
  "id": "3b0a98b1-2e98-5af5-f0c6-1510101e8362",
  "detail-type": "Amplify Deployment Status Change",
  "source": "aws.amplify",
  "account": "************",
  "time": "2020-09-07T23:51:03Z",
  "region": "ap-northeast-1",
  "resources": [
    "arn:aws:amplify:ap-northeast-1:************:apps/abcde12345678/branches/master/jobs/0000000004"
  ],
  "detail": {
    "appId": "abcde12345678",
    "branchName": "master",
    "jobId": "4",
    "jobStatus": "SUCCEED"
  }
}
//}

//terminal[Lambdaが受け取るEvent(ビルド失敗時)]{
{
  "version": "0",
  "id": "e335584f-e9d8-ff33-e100-19cbb1c4c569",
  "detail-type": "Amplify Deployment Status Change",
  "source": "aws.amplify",
  "account": "************",
  "time": "2020-09-07T23:44:38Z",
  "region": "ap-northeast-1",
  "resources": [
    "arn:aws:amplify:ap-northeast-1:************:apps/abcde12345678/branches/master/jobs/0000000003"
  ],
  "detail": {
    "appId": "abcde12345678",
    "branchName": "master",
    "jobId": "3",
    "jobStatus": "FAILED"
  }
}
//}


TODO: 画像を追加

== アイデア集

現場で使えるちょっとしたアイデアです。みなさんのお役に立てば幸いです。

== メンテナンス表示をカスタムドメインとブランチの切り替えで実現する

Amplify Consoleでは、カスタムドメインに紐づくブランチを任意のタイミングで切り替えることができます。
これを利用して、メンテナンス画面に数秒程度で切り替えることができます。


=== 複数のAWSアカウントをまたいで利用するAPIキーを、サービスロール＋スイッチロールで取得する。

Amplify Consoleを複数のAWSアカウントで利用していると、共通のパラメータの管理に悩むことがあります。
例えばGitHubのサブモジュールをPullするためのDeploy Keyの管理などが該当すると思います。

それぞれのAWSアカウントにパラメータを保存してもいいですが、より発展的なやり方としてスイッチロールをご紹介します。

コード例

//terminal[amplify.yml の例]{
  phases:
  preBuild:
    commands:
    - credentials=$(aws sts assume-role --role-arn ${ASSUME_ROLE_ARN} --role-session-name "RoleSessionFromMyAwesomeAmplify" | jq .Credentials)
    - export AWS_ACCESS_KEY_ID=$(echo ${credentials} | jq -r .AccessKeyId)
    - export AWS_SECRET_ACCESS_KEY=$(echo ${credentials} | jq -r .SecretAccessKey)
    - export AWS_SESSION_TOKEN=$(echo ${credentials} | jq -r .SessionToken)
    # add rsa private key for pulling submodule
    - aws secretsmanager get-secret-value --secret-id "github-deploy-key" --output text --query "SecretString" > ~/.ssh/id_rsa_deploy_key
//}



== git submodule vs git subtree vs npm
 * どうしてもサブモジュールでやりたい人向けのdeploy key管理方法
 * subtree基本的に楽だが...
 * （npmモジュール化するのがベストと思われるが実際にやったことがないので説得力がない）
