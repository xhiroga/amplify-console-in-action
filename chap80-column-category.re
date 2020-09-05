= コラム: 静的ウェブホスティングという分類について

本書を書くにあたって悩んだことのひとつが、静的ウェブホスティングという分類についてです。それぞれのサービスごとに呼び名が違っているため、何を採用するか悩みました。

まずは各ベンダーが自社サービスをどのように呼んでいるか見てみましょう（一部筆者訳）

 * 静的ウェブホスティングサービス（AWS）@<fn>{deeae56f-3189-4dbd-9f4b-6b9ac940520c}
 * ウェブ コンテンツ ホスティング（Firebase）@<fn>{d95826c8-df94-444b-b0e8-a6c13af47edd}
 * GitHub リポジトリから Azure にフルスタック Web アプリを自動的に構築してデプロイするサービス（Azure）@<fn>{7ac745d4-683b-400d-a494-8813151f5ce9}
 * モダンなWebプロジェクトのAll-in-Oneプラットフォーム（Netlify）@<fn>{1b61c027-e1ce-497d-b64b-fd1b44d48291}
 * ワークフローと完璧に合致する静的サイトとサーバレスファンクションのクラウドプラットフォーム（Vercel）@<fn>{c9ac8488-7450-4a43-b2a2-575ef81d240f}

//footnote[deeae56f-3189-4dbd-9f4b-6b9ac940520c][https://aws.amazon.com/jp/amplify/console/]
//footnote[d95826c8-df94-444b-b0e8-a6c13af47edd][https://firebase.google.com/docs/hosting/]
//footnote[7ac745d4-683b-400d-a494-8813151f5ce9][https://docs.microsoft.com/ja-jp/azure/static-web-apps/overview]
//footnote[1b61c027-e1ce-497d-b64b-fd1b44d48291][https://docs.netlify.com/]
//footnote[c9ac8488-7450-4a43-b2a2-575ef81d240f][https://vercel.com/docs]

ご覧の通り、標準的な名前が定まっていないことが分かります。
また、技術スタックの比較サービスである "StackShare" では、静的ウェブホスティング（static web hosting）という分類が設けられています。@<fn>{6e13296f-92e4-4553-806e-67024802a065}
ただし、この分類にはJavaScriptアプリケーションに最適化されたサービスではない GitHub Pagesや GitLab Pagesも含まれており、本書で示したい分類よりも多少広いといえるでしょう。

//footnote[6e13296f-92e4-4553-806e-67024802a065][https://stackshare.io/static-web-hosting]

結局悩んだ挙げ句、「この本はAmplify本なんだから、AWSでの呼び名を採用すればいいや」という半ば思考停止的な理由で本書では "静的ウェブホスティング" を用いることにしました。
もし将来標準的な呼び名が決まったら、第2版で直そうと思います。笑
