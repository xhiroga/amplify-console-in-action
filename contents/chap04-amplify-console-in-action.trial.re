= 実践Amplify Console

//abstract{
Amplify Consoleを複数のWebアプリおよび本番を含む複数の環境で運用して得られた知見を共有します。
//}

== ビルド設定のカスタマイズ

=== マネジメントコンソール以外から独自のDockerイメージを使用する

ドキュメントには記述がありませんが、マネジメントコンソール以外からでもビルドに使用するイメージを変更できます。
環境変数に @<code>{_CUSTOM_IMAGE} を設定し、値に @<code>{justincasetech/node:12.14.1-aws-cli-stretch} のようにオリジナルのDockerイメージを指定することで可能です。

=== サービスロールの変更

Amplify ConsoleのCI/CDワークフロー中に、別のAWSリソースにアクセスしたい場合があります。
例えばParameter StoreやSecret ManagerからAPIキーなどを取得するケースでしょうか。
そうした場合、Amplify ConsoleのためのIAM Roleを作成し、Amplifyで使用するように指定するとアクセス可能になります。
//blankline
なお、サービスロール自体はAmplify Consoleの画面ではなくIAMの画面からでも作成可能です。
その際は Trusted entitiesで@<code>{amplify.amazonaws.com}を指定してください。

=== メール以外の通知

@<href>{https://techbookfest.org/product/4838711567056896, 製品版}でご覧ください。

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

@<href>{https://techbookfest.org/product/4838711567056896, 製品版}でご覧ください。

== プライベートなGit Submodule

@<href>{https://techbookfest.org/product/4838711567056896, 製品版}でご覧ください。
