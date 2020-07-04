= Amplify Consoleを支援するツール

//abstract{
AWS CLI, Amplify-CLI, CFn, CDKについて
//}


== AWS CLI
 * まずAmplify CLIと違うことに釘を差す
 * AppやらBranchやらリソースが細かいので作成には向いてない。参照系とか、ログ取りとか...（実際のところAmplifyのログが必要になった試しがないので説得力がない）
 * ちなみにログの取得は現時点でAWS SDKにはなくCLIにしかない。

== Amplify-CLI
 * ぶっちゃけ初心者向けのテンプレ作成機能以上の意味はないと思っているが...

== CFn
 * GithubのPATをいい感じに用いる（Parameter StoreかSecretにつっこもう）
 * たいていAmplify App自体を更新することはないのでCLIで十分だ。
 * カスタムDockerイメージの設定の仕方に癖がある（これドキュメントに書いてるのか？）
 * Amplify Console App以外に、Amplicyの通知の設定を手でやるのがしんどいのでCFnおすすめ

== CDK
 * だいたいCFnと同じだが、現在アルファリリース
