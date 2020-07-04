= Amplify Consoleの特徴

//abstract{
//}

 * CloudFront + S3, CloudFront + Amplifyと機能面の比較
 ** amplify.com の適当なドメインで作れること、Previewあること、アクセスコントロール
 ** GitLfsやPrivate SubModuleの非対応
 ** e2eテスト

 * CIとの比較
 ** カバレッジがない
 ** 結果の通知が弱い

 * CloudFront, ALB, CloudFront + Amplifyとの非機能面の比較
 ** セキュリティできること、できないこと
 *** IAM制限
 *** パスワードはできるがIP制限は無理,,,）
 ** 実運用したコスト感とか
