= Amplify Console in Action

//abstract{
Amplify Console is a static web hosting service for AWS. Just like Netlify, Vercel or Firebase Hosting, Amplify Console comes with CI/CD pipeline integration with GitHub, Hosting and CDN (Content Delivery Network). In this chapter, we shall take a look at how Amplify Console compares to other services, as well as how it is placed among AWS services. 
//}

== Amplify Console

=== Static Web Hosting Service
In this book, we define “Static Web Hosting Service” as a service that has CI/CD pipeline integrated to a Git repository and is capable of deploying SPA or static web sites.
//blankline
A typical static web hosting service, Netlify, was released by MakerLoop Inc. (now Netlify Inc.) in April 2015. @<fn>{de6c201c-3107-451b-9717-6b574ec64a8f}
//blankline
In Japan, Netlify gradually entered usage since 2016.
For example, the oldest Qiita article on Netlify was published on August 18th,2016.@<fn>{93dcd09b-99af-48ab-8a45-49ff46fdfd1b}
As there were no Amplify Console at the time, developers ultilizing CloudFront+S3 on AWS were deeply impressed by the simplicity of Netlify.@<fn>{e7ee5b91-0c84-4e16-bd2f-b82ef813c713}@<fn>{91abfa0f-02ca-4b15-bc37-c1e37059ac28}

//footnote[de6c201c-3107-451b-9717-6b574ec64a8f][https://aws.amazon.com/jp/amplify/console/]
//footnote[93dcd09b-99af-48ab-8a45-49ff46fdfd1b][Trying out Netlify, the powerful hosting service. (https://qiita.com/TakahiRoyte/items/b7c4d1581df1a17a93fb)]
//footnote[e7ee5b91-0c84-4e16-bd2f-b82ef813c713][Netlify, not s3, is exactly what I want for hosting static HTTPS contents. (https://qiita.com/shogomuranushi/items/6ab5bc29923b3f82c9ed)]
//footnote[91abfa0f-02ca-4b15-bc37-c1e37059ac28][FYI: Netlify uses AWS as its infrastructure.]

=== Amplify Console

Amplify Console is a static web hosting service released by AWS in November 2018. @<fn>{f9c89212-b773-4141-8af7-e644d93cca79}Service in Tokyo Region started in April 2019.
//blankline
It can be said to be a service that automates the settings of CloudFront, S3, and CodeBuild. However, CloudFront distributions and S3 packets were made inside the AWS accounts managed by AWS itself, and does not require any input from the users.

#@+++
ここはjustInCaseで許可取ってから載せる
Actually, searching about "services built with Amplify Console" with Wappalyzer@<fn>{00b1467c-cbe4-4e05-8756-7f2570bcdaab} shows that they are built with CloudFront and S3.
//footnote[00b1467c-cbe4-4e05-8756-7f2570bcdaab][Webサイトの技術スタックを解析するアプリケーション(https://www.wappalyzer.com/)]
#@---

=== Other Static Web Hosting services

As of September 2020, there are many static web-hosting services, including those provided by major cloud vendors.

 * AWS Amplify Console
 * Firebase Hosting
 * Azure Static Web Apps
 * Netlify
 * Vercel@<fn>{7c571916-3b38-4e1b-96bd-cf57f51dd4a1}

//footnote[f9c89212-b773-4141-8af7-e644d93cca79][Document History for AWS Amplify(https://docs.aws.amazon.com/amplify/latest/userguide/document-history.html)]
//footnote[7c571916-3b38-4e1b-96bd-cf57f51dd4a1][2020年4月にZEITから改称]

== 1.2	Amplify family and Amplify Console

AWS Amplify is a brand name for a family of frontend services provided by AWS, and Amplify Console is simply a service that provides static hosting among them. Services provided under the AWS Amplify Brand is as follows:

 * Amplify Framework - Amplify Library (SDK)
 * Amplify Framework - Amplify UI Component
 * Amplify Framework - Amplify CLI
 * Amplify Console

Please note that there are TWO static web hosting services by Amplify, Amplify Console and Amplify CLI. Amplify CLI can be said to be the bootstrap that dynamically forms and deploys CloudFormation templates based on user inquiry. Among those Cloud Formations are static web hosting services such as CloudFront+S3 and Amplify Console.
//blankline
Please be careful about the differentiation between Amplify CLI and Amplify Console so that you will not accidentally construct a CloudFront+S3 environment just by googling about Amplify Console!

==[column] About “static web hosting” as a classification
One sore point while writing this book is the name “static web hosting”. In fact, different vendor has completely different names! Let us take a look at how vendors call their own services. (Marketing Buzzwords Alert!)

 * Static Web Hosting (AWS)@<fn>{deeae56f-3189-4dbd-9f4b-6b9ac940520c}
 * “Web content hosting” (Firebase Hosting) @<fn>{d95826c8-df94-444b-b0e8-a6c13af47edd}
 * “A service that automatically builds and deploys full stack web apps to Azure from a GitHub repository.” (Azure Static Web Apps Preview) @<fn>{7ac745d4-683b-400d-a494-8813151f5ce9}
 * “An all-in-one platform for automating modern web projects.” (Netlify) @<fn>{1b61c027-e1ce-497d-b64b-fd1b44d48291}
 * “A cloud platform for static sites and Serverless Functions that fits perfectly with your workflow.” (Vercel) @<fn>{c9ac8488-7450-4a43-b2a2-575ef81d240f}

As you can see, there is no single, standard description.
//blankline
After much consideration, I decided to stop thinking and just use the AWS terms because this book is about Amplify. Guess I’ll make a fixed version when there is a standard in the future. Haha.

//footnote[deeae56f-3189-4dbd-9f4b-6b9ac940520c][https://aws.amazon.com/jp/amplify/console/]
//footnote[d95826c8-df94-444b-b0e8-a6c13af47edd][https://firebase.google.com/docs/hosting/]
//footnote[7ac745d4-683b-400d-a494-8813151f5ce9][https://docs.microsoft.com/ja-jp/azure/static-web-apps/overview]
//footnote[1b61c027-e1ce-497d-b64b-fd1b44d48291][https://docs.netlify.com/]
//footnote[c9ac8488-7450-4a43-b2a2-575ef81d240f][https://vercel.com/docs]
