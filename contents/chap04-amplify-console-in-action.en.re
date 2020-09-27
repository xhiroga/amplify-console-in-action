= Amplify Console in Action

//abstract{
This chapter focuses on the expertise gained from utilizing Amplify Console for multiple Web apps under production environment.
//}

== Customize Build Settings

=== Using custom Docker Image without management console

While not detailed in the documentation, it is possible to change the image used for the build without management console by setting the 
 @<code>{_CUSTOM_IMAGE} environment variable to your custom Docker image, such as @<code>{justincasetech/node:12.14.1-aws-cli-stretch} 

=== Changing the Service Role

There are cases where you want to access other AWS resources during Amplify Console’s CI/CD workflow. For example, when you need access to the API key from Parameter Store or Secret Manager, you can create IAM Role for Amplify Console and enable access.
//blankline

You also can craete IAM Service Role from IAM, not only Amplify Console. If do so, you should specify @<code>{amplify.amazonaws.com} as trusted entities.s

=== Notifications Other than Emails

First of all, mail notifications set from the management console is a combination of the following services:
//blankline
@<b>{Amplify Console → EventBridge → SNS}
//blankline
EventBridge sends notifications on events occurred in AWS services, which are useful in cases such as starting up Lambda based on the task status of ECS. Therefore, by hooking EventBridge to Amplify Console’s build events and start Lambda from there, you can send any notifications like Slack.
//blankline
As the mechanism that hooks EventBridge to Amplify Console, it sends notifications to a unique EventBridge Rule named after the combination of Amplify Console applications’ ID and the target branch. For example, if the application ID is 
@<code>{abcde12345678}, and the target branch is the @<code>{master}branch, then EventBridge will automatically send notifications to a Rule named@<code>{amplify-abcde12345678-master-branch-notification}
//blankline
Additionally, when targeting all branches, the name will be @<code>{amplify-abcde12345678-AMPLIBRANCHSENTINEL-branch-notification}

After the EventBridge Rule is set, the only work left is to define Lambda. For your reference, here are some sample events that will arrive.
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

== Ideas

These are just some ideas to be used for work, I hope they will be useful.

=== Showing the Maintenance Screen

Amplify Console change branches attached to custom domains at any timing. Using this feature, we can transform the Web site into a maintenance screen in a matter of seconds. The steps are as following:

 1. Make a maintenance branch separated from master.
 2. Ensure that the web site will show “in maintenance” message on maintenance branch.
 3. Connect the maintenance branch to Amplify Console.
 4. Switch the branch from maintenance to master at the start of maintenance.
 5. Switch back to master when the maintenance is finished.

=== Switch roles during build

There are cases where you may want to switch roles to access other AWS account resources. Once the service role is set, you may switch roles by setting the roles from the AWS account you wish to access.

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

== Private Git Submodule

Some teams use Git Submodule to manage modules used for Web applications. However as of September 2020, there are unfortunately no private Git Submodule support in Amplify Console.
//blankline
While it may be easier to use Git Subtree or npm modules, I do recommend managing the Deploy Key through Secret Manager if Git Module is absolutely required. However, as default IAM Role provided by Amplify Console does not have access to the Secret Manager, you need to setup your own service role.