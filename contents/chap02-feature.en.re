= Features of Amplify Console
//abstract{
AWS Amplify Console’s functions can be classified into Integration, Build, and Hosting. This chapter will introduce these functions to readers and provides details for the ones commonly used by the author.
//}

== Integration

Amplify Console can easily construct a workflow using the management console with repositories such as GitHub. These repository connections are implemented by assigning webhook as the Git provider, which also acts as the build trigger for Amplify Console.
//blankline
Therefore, you can use webhook to make a build anytime, with the following features already included:

 * Build with Incoming Webhook
 * Integration with Git providers (GitHub, Bitbucket, GitLab, AWS CodeCommit)
 * Deploy Web Preview with every Pull Request
 * Manually Deploy into storage medias meant for the final build

=== Use-case for Incoming Webhook

The first that comes to mind would be updating web contents with triggers other than repository source code updates. For example, when there is an update on headless CMS or modules such as Git Submodule, Git Subtree, or npm.
//blankline
For some headless CMS services such as Contentful, you can assign webhook from console request.
//blankline
Other than that, there are also cases where you want execute CI/CD with external services such as CircleCI, or if you want a gradual transfer to Amplify Console.

=== About Web Previews for Pull Requests

This feature allows for deploying the product to a temporary URL with every Pull Request made with GitHub.
//blankline
To enable Web Preview in GitHub, a GitHub user with access rights to the target repository must authenticate Amplify Console. When working with a team, it is helpful to create a system user on the GitHub side.
//blankline
While convenient, Web Preview has its problems. As GitHub console does not show causes of error, one must access the Amplify Console to resolve possible errors occurred during a failed build. Furthermore, commits made in short intervals lead to instabilities as well. 
Refer to @<secref>{chap05-trouble-shooting.en|Troubles during the build} for more details.

== Builds

Most requirements for general CI services are met. It also has the merit of leaving UI traces for End-to-End tests integrated to Cypress.@<fn>{e446e9e4-74ac-4fcb-9e97-f910e45972de}

 * Build and Deploy. Caching. Mechanisms for Environmental Variables.
 * Container Images for the build. Customization of IAM roles.
 * Build Notifications.

//footnote[e446e9e4-74ac-4fcb-9e97-f910e45972de][Cypress Integrated with AWS Amplify Console for End-to-End Testing(https://www.cypress.io/blog/2019/10/02/cypress-integrated-with-aws-amplify-console-for-end-to-end-testing/)]

=== Woes of the Build Notification

You can set mail notifications from the management console. By hooking Amplify Console’s build events with EventBridge, any services other than Lambda can be executed as well. 
Further explanation can be found in @<secref>{chap04-amplify-console-in-action.en}

== Hosting

Basic authentication and immediate cache invalidation are offered by using CloudFront and S3 as the base. You can change the password for Basic authentication for each branch and set whether passwords are required.

 * Web contents hosting, CDN
 * Access limitations using Basic authentication
 * Setting Custom Headers
 * Setting Redirects
 * Access Logs
 * Automatic setting of Route53

Note that Route53’s automatic setting requires an AWS Account with the same Hosted Zone between the Amplify Console Application and the target domain. Route 53 for management services from external domains or other AWS accounts requires manual setup.

== Amplify Console vs CloudFront+S3

While Amplify Console delivers the same performance as CloudFront+S3, the difference lies in the features offered.
//blankline
Amplify Console scores advantage in providing the immediate cache invalidation with each commit, automatic deployment for each branch, generating Web Previews for each Pull Request, and password protection in a management service bundle.
//blankline
On the other hand, Lambda@Edge, which was possible on CloudFront, is no longer supported. Therefore, one cannot implement IP address-based access restrictions and server-side rendering.@<fn>{c52cda50-2930-4c8c-a0c4-78b9632e9fbf}

//footnote[c52cda50-2930-4c8c-a0c4-78b9632e9fbf][Placing CloudFront and Lambda@Edge in front of Amplify Console is still an viable option.]


