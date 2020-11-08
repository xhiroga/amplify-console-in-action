= Amplify Consoleを支援するツール

//abstract{
マネジメントコンソール以外でAmplify Consoleを構築・運用するためのツールをご紹介します。
具体的には、AWS CLI・Amplify CLI・CloudFormation・AWS CDK・Terraformを取り上げます。
//}


== AWS CLI

AWS CLIからAmplify Consoleを操作できます。念のために付け加えると、AWS CLIとAmplify CLIは全く別のツールです。
AWS CLIでAmplify Consoleアプリケーションを作成するケースは少ないと思います。
現場で利用するケースとしては、マネジメントコンソールで作成したAmplify Consoleアプリケーションの参照や、アクセスログの取得などが考えられます。

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

Amplify CLIでもAmplify Consoleのアプリケーションを構築・管理することができます。
本書では詳しく取り上げませんが、Amplify Console以外のAWSサービスをまとめて構築したい場合に便利かもしれません。

//terminal[Amplify CLI コマンドの例]{
$ cd my-awesome-amplify-app
$ amplify console # Amplify CLIで管理しているリポジトリで、マネジメントコンソールの対応するURLを生成する。

https://console.aws.amazon.com/amplify/home#/*************/**********/dev 
//}


== CloudFormation & AWS CDK

マネジメントコンソール以外からAmplify Consoleアプリケーションを管理する場合に、以下の理由から最もおすすめできるツールです。

 * バックエンドとの整合性を考慮すると、dev, prodなど環境ごとに同じ構成のAmplify Consoleアプリケーションを作成するのがベストであるため。
 * Slack通知のために、Amplify Console Appと同時にEventBridgeのRuleを作成したいため。

ただし、マネジメントコンソール以外からAmplify Consoleアプリケーションを作る場合は、Gitプロバイダーのトークンを明示的に渡す必要があります。
筆者のチームでは、Secret ManagerにGitHubのPersonal Access Tokenを保存し、それをAWS CDKから参照することで解決しています。

なお、 @<code>{AWS::Amplify::Domain} の @<code>{DependsOn} 属性に対応するブランチの @<code>{AWS::Amplify::Branch} を設定することをおすすめします。
@<code>{AWS::Amplify::Domain} が先に作成されようとした場合、 @<code>{SubDomainSetting} に指定されているドメインが未接続のため CloudFormation/CDK のデプロイが失敗します。

== Terraform

2020年9月時点で開発中です。@<fn>{e65ebf21-f2ae-4432-82a0-57ea74b669d6}
必要な方はTerraformのIssueにUp Voteすると良いかもしれませんね。
//footnote[e65ebf21-f2ae-4432-82a0-57ea74b669d6][AWS Amplify Console Resources #6917(https://github.com/terraform-providers/terraform-provider-aws/issues/6917)]
