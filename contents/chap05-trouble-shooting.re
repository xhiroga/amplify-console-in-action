= トラブルシューティング

//abstract{
    筆者がAmplify Consoleを利用していて遭遇したトラブルと、その対応をまとめました。お役に立てば幸いです。
//}

== アプリケーションのセットアップに関するトラブル

=== カスタムドメインのセットアップ時、CNAMEがすでに存在するエラー

Amplify ConsoleでホスティングするWebコンテンツは、実際にはAWSが管理するAWSアカウント上のCloudFrontでホスティングされています。
CloudFrontには、複数のディストリビューションに対して同じCNAMEエイリアスを使用できない制約があります。したがって、Amplify Consoleに接続したかったCNAMEエイリアスを持つCloudFrontディストリビューションがすでにある場合、CNAMEが設定できません。@<fn>{86bca824-a2ca-4522-a864-4c6138d15b5d}

==== 対策
ドキュメントにあるようにCloudFront側のエイリアス設定を削除すればOKです。@<fn>{159a775e-ee7e-4068-b87d-0ee34e54b843}
すでにCloudFrontでホスティングしているアプリケーションをAmplify Consoleに移行する時などに引っかかるかもしれません。

//footnote[86bca824-a2ca-4522-a864-4c6138d15b5d][Amazon CloudFront ディストリビューションで CNAME エイリアスを設定する際に、 CNAMEAlreadyExists エラーが表示された場合の解決方法を教えてください。(https://aws.amazon.com/jp/premiumsupport/knowledge-center/resolve-cnamealreadyexists-error/)]
//footnote[159a775e-ee7e-4068-b87d-0ee34e54b843][I get a CNAMEAlreadyExistsException error(https://docs.aws.amazon.com/amplify/latest/userguide/custom-domain-troubleshoot-guide.html#i-get-a-cnamealreadyexistsexception-error)]

=== GitHubリポジトリにWebhookのゴミが残ってしまう

Amplify Consoleでは、AWS側でアプリケーションを削除してもGitHubに登録されたWebhookは削除されません。
お試しでAmplify Consoleの設定と削除を繰り返していると、いつのまにかGitHubリポジトリに大量のWebhookが登録されていることも…
 
==== 対策
地道に消すしかありません。Amplify ConsoleのアプリケーションIDを控えた上で、GitHubリポジトリのWebhookを一つづつ開き、Payload URLのクエリパラメータを確認して利用中でなければ消します。
Amplify Consoleのアプリケーションを削除するときは、忘れずにWebhookも消すようにしたいですね！

== ビルドに関するトラブル

=== GitHubのPull Requestに対するWeb Previewのステータスが更新されない。

Amplify Console側ではビルドが完了しているにも関わらず、GitHubのPull Requestでは `Queued = Waiting to run this check...` のまま更新されないことがあります。
短い間隔でCommitを連続してPushした場合、特に直前のCommitに対するWeb Previewのビルドを実行している間に、新しいCommitをPushした場合に起きることがあるようです。
推測ですが、Amplify ConsoleでGitHubのCheckによるビルドが複数走っている場合、初めのビルドが完了した時点で後続のビルドのステータス更新が実行されなくなるのかもしれません。

==== 対策
新しいコミットをPushしましょう。前のコミットのコミットメッセージを更新してforce pushすれば解決します。
または、単にマネジメントコンソールからAmplify Consoleのビルド結果を確認してもよいと思います。

=== GitHubのPull Requestに対するWeb Previewのチェックが実行されないように見える

Amplify Consoleでは、GitHubのPull Requestに対するWeb Previewの実行中に、新しいWeb Previewが発生するとビルドが保留されます。
保留中のビルドがある場合に更に新しいWeb Previewが発生すると、保留中のビルドが対象とするコミットが書き換わります。その際、GitHub側でコミットに対するチェックが発生していないことになります。
要するに、短い間隔でCommitを3連続以上でPushすると、Pull RequestのCheckからAmplify ConsoleのWeb Previewが消えてしまいます。

==== 対策
ステータスが更新されないケースと同じように、新しいコミットをPushすれば解決します。ただし、保留中のビルドがないことをビルド履歴から確認してください。

=== マネジメントコンソールでBuildタブにビルドのステータスが表示されない

マネジメントコンソールでAmplify Consoleを日本語で表示すると、日本語のビルド・デプロイ・検証に加えて英語のBuild・Deploy・Verifyタブも表示されてしまうバグがあります。
タブが重複して表示されているときは、英語を無視して日本語側を開くと期待している結果が得られます。
