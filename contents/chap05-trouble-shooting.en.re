= Troubleshooting

//abstract{
    This chapter is a compilation of troubleshooting the author experienced in Amplify Console. I hope they will be useful to you in the future!
//}

== Application Setup Troubleshooting

=== Error caused by the presence of prior CNAME during custom domain setup

Web contents hosted in Amplify Console is in fact hosted by CloudFront in AWS-managed AWS accounts. This leads to the CloudFront restriction where the same CNAME alias cannot be use for multiple distributions.
//blankline
As a result, any CNAME with prior CloudFront distribution cannot be used for Amplify Console@<fn>{86bca824-a2ca-4522-a864-4c6138d15b5d}

==== Solution:
According to the documentation, you need to delete the CloudFront’s alias setting. @<fn>{159a775e-ee7e-4068-b87d-0ee34e54b843}
This error is commonly encountered when transferring from a CloudFront hosted application to Amplify Console.

//footnote[86bca824-a2ca-4522-a864-4c6138d15b5d][How do I resolve the error CNAMEAlreadyExists when setting up a CNAME alias for my Amazon CloudFront distribution? (https://aws.amazon.com/jp/premiumsupport/knowledge-center/resolve-cnamealreadyexists-error/)]
//footnote[159a775e-ee7e-4068-b87d-0ee34e54b843][I get a CNAMEAlreadyExistsException error(https://docs.aws.amazon.com/amplify/latest/userguide/custom-domain-troubleshoot-guide.html#i-get-a-cnamealreadyexistsexception-error)]

=== Webhook residuals left in GitHub repository

Webhook registered in GitHub is persistent even if the application is deleted from AWS in Amplify Console. Repeating attempts to setup and delete Amplify Console will cause an obscene amount of Webhooks attached to the GitHub repository.
 
==== Solution:
You will have to remove them by hand. Take a note of the Amplify Console’s application ID and open up each and every Webhook entry in the repository, deleting any unused entries after confirming the Payload URL. This process needs to be repeated for every deletion of Amplify Console application.

== Troubles during the build

//warning[CAUTION!]{
The following behavior is confirmed by the author on September 12nd, 2020. This is NOT an officially declared feature of Amplify Console.
//}

=== Web Preview status is not updating

Despite of the finished build on Amplify Console, the Pull Request status check sometimes remains to be @<b>{Queued = Waiting to run this check...}
This occurs often after Pushing Commits made in short intervals, especially when the previous Web Preview build is still in progress.
//blankline
The author’s theory is that parallel GitHub Check builds running on Amplify Console leads to the build status stops being reported after the first build is finished.

==== Solution:
Push a new Commit. Updating the previous commit message and force pushing it will do the trick. Alternatively, you may simply confirm the build result from Amplify Console’s management console.

=== Web Preview appears to be not running

During an ongoing Web Preview for GitHub Pull Request, new builds with Web Preview will be put in reserve. This reserve, however, will be overwritten by newer commits, of which none is checked from GitHub’s side.
//blankline
In summary, pushing more than 3 commits in short intervals will lead to Web Preview disappearing from Pull Request’s Check.

==== Solution:
Similar to the status check not being updated issue, pushing a new commit will solve the problem. Make sure there are no builds in reserve in the build history just in case.

=== Build status not showing up on management console

Using Japanese localization on Amplify Console through the management console causes a bug where both the localized and English tabs for build, deploy and verify showing up. In this case, opening the Japanese tabs will display the correct build messages.
