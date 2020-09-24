= Tools supporting Amplify Console

//abstract{
This chapter introduces tools outside of the management console that help with the build and executions process of Amplify Console. This includes the AWS CLI, Amplify CLI, CloudFormation, AWS CDK, and Terraform.
//}


== AWS CLI

You can control Amplify Console from the AWS CLI. Despite the similarities in naming, these are entirely different tools, and there are many cases where Amplify Console apps is made through AWS CLI. In the business cases, AWS CLI is often used for referencing Amplify Console apps made with management console and acquiring access logs.

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

You can also build and manage Amplify Console apps with Amplify CLI. While not covered in this book, it may be useful in building a bundle of other AWS applications.

//terminal[Amplify CLI コマンドの例]{
$ cd my-awesome-amplify-app
$ amplify console # Generate an URL for management console from repositories managed by Amplify CLI

https://console.aws.amazon.com/amplify/home#/*************/**********/dev 
//}


== CloudFormation & AWS CDK

If you have to manage Amplify Console without the management console, then CloudFormation and AWS CDK is your best alternative for the following reasons:

 * Ensures consistency with the backend by having the same Amplify Console setup through the dev and prod environment.
 * Enables Slack notifications by creating EventBridge Rules and Amplify Console App at the same time.

However, you must explicitly pass the Git provider’s token while making Amplify Console Applications without management console. The author’s team solves this issue by saving GitHub’s Personal Access Token to the Secret Manager and refer to them from AWS CDK.

== Terraform

Still in development as of September 2020. @<fn>{e65ebf21-f2ae-4432-82a0-57ea74b669d6}
You might want to Upvote Terraform’s Issue page if you need it sooner.
//footnote[e65ebf21-f2ae-4432-82a0-57ea74b669d6][AWS Amplify Console Resources #6917(https://github.com/terraform-providers/terraform-provider-aws/issues/6917)]
