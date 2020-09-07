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

 * Email notificationと言っているがLambdaを起動してくれる
 * 手動でメアドを設定して、自動で作られたトピックをsubscribe…というのは面倒くさいが、いい感じの自動化方法
 * この自動化を荻野さんがどうやったのか確認中...（おそらく捨てメアドをすべてのAmplifyAppに登録する→ルールによって命名されるSNSを自動でSubscribeが一番手っ取り早い?）



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

```
  phases:
    preBuild:
      commands:
        - credentials=$(aws sts assume-role --role-arn ${ASSUME_ROLE_ARN} --role-session-name "RoleSessionFromMyAwesomeAmplify" | jq .Credentials)
        - export AWS_ACCESS_KEY_ID=$(echo ${credentials} | jq -r .AccessKeyId)
        - export AWS_SECRET_ACCESS_KEY=$(echo ${credentials} | jq -r .SecretAccessKey)
        - export AWS_SESSION_TOKEN=$(echo ${credentials} | jq -r .SessionToken)
        # add rsa private key for pulling submodule
        - aws secretsmanager get-secret-value --secret-id "github-deploy-key" --output text --query "SecretString" > ~/.ssh/id_rsa_deploy_key
```



== git submodule vs git subtree vs npm
 * どうしてもサブモジュールでやりたい人向けのdeploy key管理方法
 * subtree基本的に楽だが...
 * （npmモジュール化するのがベストと思われるが実際にやったことがないので説得力がない）
