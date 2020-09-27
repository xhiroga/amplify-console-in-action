= トラブルシューティング

//abstract{
    筆者がAmplify Consoleを利用していて遭遇したトラブルと、その対応をまとめました。お役に立てば幸いです。
//}

== アプリケーションのセットアップに関するトラブル

=== カスタムドメインのセットアップ時、CNAMEが既に存在するエラー

Amplify ConsoleでホスティングするWebコンテンツは、実際にはAWSが管理するAWSアカウント内のCloudFrontでホスティングされています。
ところで、CloudFrontには、複数のディストリビューションに対して同じCNAMEエイリアスを使用できない制約があります。
//blankline
したがって、Amplify Consoleに接続したかったCNAMEエイリアスを持つCloudFrontディストリビューションが既にある場合、CNAMEが設定できません。@<fn>{86bca824-a2ca-4522-a864-4c6138d15b5d}

==== 対策
ドキュメントにあるようにCloudFront側のエイリアス設定を削除すればOKです。@<fn>{159a775e-ee7e-4068-b87d-0ee34e54b843}
既にCloudFrontでホスティングしているアプリケーションをAmplify Consoleに移行する時などに引っかかるかもしれません。

//footnote[86bca824-a2ca-4522-a864-4c6138d15b5d][Amazon CloudFront ディストリビューションで CNAME エイリアスを設定する際に、 CNAMEAlreadyExists エラーが表示された場合の解決方法を教えてください。(https://aws.amazon.com/jp/premiumsupport/knowledge-center/resolve-cnamealreadyexists-error/)]
//footnote[159a775e-ee7e-4068-b87d-0ee34e54b843][I get a CNAMEAlreadyExistsException error(https://docs.aws.amazon.com/amplify/latest/userguide/custom-domain-troubleshoot-guide.html#i-get-a-cnamealreadyexistsexception-error)]

=== GitHubリポジトリにWebhookのゴミが残ってしまう

Amplify Consoleでは、AWS側でアプリケーションを削除してもGitHubに登録されたWebhookは削除されません。
お試しでAmplify Consoleの設定と削除を繰り返していると、いつのまにかGitHubリポジトリに大量のWebhookが登録されていることも…

==== 対策
地道に消すしかありません。Amplify ConsoleのアプリケーションIDを控えた上で、GitHubリポジトリのWebhookを一つづつ開き、Payload URLのクエリパラメータを確認して利用中でなければ消します。
Amplify Consoleのアプリケーションを削除するときは、忘れずにWebhookも消すようにしたいですね！

== ビルドに関するトラブル

=== GitHubでWeb Previewのステータスが更新されない場合

連続でコミットをPushした場合、2つ目のコミットに対するステータスが@<b>{Queued = Waiting to run this check...}のまま更新されません。2020年9月現在、以下の手順で再現します。

 1. GitHubで特定の Pull Request において、コミットを Push する (コミットA)
 2. コミットA のビルドの実行中に、コミットを Push する (コミットB)
 3. コミットA とコミットB 共にビルドは完了する
 4. GitHub の Pull requests -> Commit においてコミットA は "All checks have passed" と表示されるが、コミットB は "Some checks haven’t completed yet" と表示され続ける

==== 対策
新しいコミットをPushしましょう。前のコミットのコミットメッセージを更新してforce pushすれば解決します。
または、単にマネジメントコンソールからAmplify Consoleのビルド結果を確認してもよいと思います。

=== GitHubでWeb Previewが実行されない場合

連続でコミットをPushした場合、中間のコミットに対するビルドが省略されます。（
//blankline
Amplify Consoleでは、GitHubのPull Requestに対するWeb Previewの実行中に、新しいWeb Previewが発生するとビルドが保留されます。
保留中のビルドがある場合に更に新しいWeb Previewが発生すると、保留中のビルドが対象とするコミットが書き換わります。その際、GitHub側でコミットに対するチェックが発生していないことになります。

==== 対策
ステータスが更新されないケースと同じように、新しいコミットをPushすれば解決します。ただし、保留中のビルドがないことをビルド履歴から確認してください。

=== GitHubでPull RequestのTarget Branch変更後、Web Previewが有効にならない場合

GitHubではPull RequestのTarget Branchが別のBranch(例えばmaster)にmergeされた場合、そのPull RequestのTarget Branchが自動的にmergeされたBranch（master）に変更されます。
//blankline
しかし、その場合にAmplify ConsoleのWeb Previewが自動的に有効にならないケースがあります。以下の手順で再現します。

 1. あるGitHubリポジトリで、masterに対するWeb Previewのみを有効化
 2. master をもとに branch_a を作成
 3. master <= branch_a 方向の PR (#1) を作成
 4. branch_a をもとに branch_b を作成
 5. branch_a <= branch_b 方向の PR (#2) を作成
 6. PR #1 をマージし、branch_a を削除
 7. PR #2 が master <= branch_b となるが、Amplify Console 側の Web Preview では PR が作られない

==== 対策

一度Pull Requestをクローズし、新たに作成するしかありません。

=== マネジメントコンソールにビルドのステータスが表示されない

マネジメントコンソールでAmplify Consoleを日本語で表示すると、日本語のビルド・デプロイ・検証に加えて英語のBuild・Deploy・Verifyタブも表示されてしまうバグがあります。
タブが重複して表示されているときは、英語を無視して日本語側を開くと期待している結果が得られます。
