= 実践Amplify Console

//abstract{
Amplify Consoleを複数のWebアプリおよび本番を含む複数の環境で運用して得られた知見を共有します。
//}

== ビルド設定のカスタマイズ

=== マネジメントコンソール以外から独自のDockerイメージを使用する

ドキュメントには記述がありませんが、マネジメントコンソール以外からでもビルドに使用するイメージを変更できます。
環境変数に @<b>{_CUSTOM_IMAGE} を設定し、値に @<b>{justincasetech/node:12.14.1-aws-cli-stretch} のようにオリジナルのDockerイメージを指定することで可能です。

=== サービスロールの変更

Amplify ConsoleのCI/CDワークフロー中に、別のAWSリソースにアクセスしたい場合があります。
例えばParameter StoreやSecret ManagerからAPIキーなどを取得するケースでしょうか。
そうした場合、Amplify ConsoleのためのIAM Roleを作成し、Amplifyで使用するように指定するとアクセス可能になります。
//blankline
なお、サービスロール自体はAmplify Consoleの画面ではなくIAMの画面からでも作成可能です。
その際は Trusted entitiesで@<b>{amplify.amazonaws.com}を指定してください。

=== メール以外の通知

そもそも、マネジメントコンソールから設定するメール通知は、以下サービスの組み合わせで成り立っています。
//blankline
@<b>{Amplify Console → EventBridge → SNS}
//blankline
ここでEventBridgeについて簡単にご説明します。AWSのサービス内で発生した事象を通知してくれるサービスで、例えばECSのタスクの状態変化に応じてLambdaを起動するようなことが可能です。
したがって、Amplify ConsoleのビルドイベントをEventBridgeでフックし、そこからLambdaなどを起動すれば、Slackなど任意の通知が可能になります。
//blankline
さて、EventBridgeがAmplify Consoleのビルドイベントをフックする仕組みですが、Amplify Consoleアプリケーションと対象のブランチによって一意になる名前のEventBridge Ruleに対して自動でイベントが通知されています。
例えば、アプリケーションのIDが@<b>{abcde12345678}、対象のブランチが@<b>{master}なら、@<b>{amplify-abcde12345678-master-branch-notification}という名前のRuleに対して自動でイベントが通知されます。
//blankline
ちなみに、全てのブランチが対象の場合は@<b>{amplify-abcde12345678-AMPLIBRANCHSENTINEL-branch-notification}のような名前になります。

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

== アイデア集

現場で使えるちょっとしたアイデアです。みなさんのお役に立てば幸いです。

=== メンテナンス画面の表示

Amplify Consoleでは、カスタムドメインに紐づくブランチを任意のタイミングで切り替えることができます。これを利用して、Webサイトを数秒程度でメンテナンス画面に切り替えられます。
手順は以下の通りです。

 1. masterブランチとは別に、maintenanceなどのブランチを作成する。
 2. maintenanceブランチでは、Webサイトがメンテナンス中の旨だけを表示するようにする。
 3. maintenanceブランチをAmplify Consoleに接続する。
 4. メンテナンス中にしたいタイミングで、ドメイン管理から接続先ブランチをmaintenanceにする。
 5. メンテナンスが終わったら、ドメイン管理から接続先をmasterに戻す。

=== ビルド中にスイッチロール

別のAWSアカウントのリソースにアクセスしたい場合などで、ビルド中にスイッチロールを試みたいケースがあると思います。
サービスロールを指定した上で、アクセスしたいAWSアカウントにサービスロールからスイッチできるロールを設定することでスイッチロールができます。

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

== PrivateなGit Submodule

チームによっては、Webアプリケーションで利用しているモジュールをGit Submoduleで管理していると思います。
しかし、2020年9がつ日現在、残念なことにAmplify ConsoleはプライベートなGit Submoduleに対応していません。
//blankline
したがってGit Subtreeやnpmモジュールを利用したほうが楽なのですが、どうしてもGit Submoduleを利用したい場合にはDeploy KeyをSecret Managerで管理するのがおすすめです。
なお、Amplify Consoleがデフォルトで用意するIAMロールはSecret Managerへのアクセス権限がないので、自前で用意したサービスロールを設定するようにしてください。
