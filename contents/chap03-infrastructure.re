= Amplify Consoleを支援するツール

//abstract{
AWSのコンソール以外でAmplify Consoleを構築・運用するためのツールをご紹介します。
具体的には、AWS CLI, Amplify CLI, CFn, CDK, Terraformを取り上げます。
//}


== AWS CLI

Amplify ConsoleにもAWS CLIがあります。念のために付け加えると、Amplify-CLIとは別のCLIです。
他のサービスのAWS CLIにもいえることですが、CloudFormationやCDKの構成のためにコンソールで作成したリソースの情報をJSON化するために役立ちます。

コマンドの例

//terminal[AWS CLI コマンドの例]{

$ aws amplify list-apps
{
  "apps": [
    {
      "appId": "d1234cce567j4q",
      "appArn": "arn:aws:amplify:ap-northeast-1:************:apps/d1234cce567j4q",
      .....
    }
  ]
}
//}


== Amplify CLI
Amplify CLIでもAmplify Consoleのアプリケーションを構築することができます。
AWSに不慣れな方などは、必要なリソースをまとめて構築してくれるのが嬉しいかもしれません。とはいえ、個人的にはAmplify ConsoleのセットアップはAWSのコンソールから行うのが最も簡単だと思います。

//terminal[Amplify CLI コマンドの例]{
# terminal

$ cd my-awesome-amplify-app
$ amplify console

# マネジメントコンソールで my-awesome-amplify-app を参照するURL
https://console.aws.amazon.com/amplify/home#/*************/**********/dev 
//}


== CloudFormation & CDK

Amplify Consoleの設定をAWSのコンソール以外から行う場合に、最もおすすめできる構成管理ツールです。
主な理由は2つあり、
 * バックエンドとの整合性を考慮すると、dev, prodなど環境ごとにAmplify ConsoleのAppを作成するのがベストであるため。
 * Slack通知のために、Amplify Console Appと同時にEventBridgeのRuleを作成したいため。

ただし、GitHubなどGitプロバイダーのトークンをどのように管理するかは悩ましいところです。
筆者のチームでは、SecretManagerにGitHubのPersonal Access Tokenを保存することで対応しています。

またGitHub Preview機能ですが、通常の開発環境・本番環境のためのアプリケーションとは分けて管理することをオススメします。
そうすることで、開発環境と本番環境の設定をドメイン・接続先API以外の点で同じにでき、問題発生時のデバッグが簡単になると考えています。

== Terraform

2020年9月時点で開発中です。@<fn>{e65ebf21-f2ae-4432-82a0-57ea74b669d6}
必要な方はUp Voteすると良いかもしれませんね。
//footnote[e65ebf21-f2ae-4432-82a0-57ea74b669d6][AWS Amplify Console Resources #6917(https://github.com/terraform-providers/terraform-provider-aws/issues/6917)]

