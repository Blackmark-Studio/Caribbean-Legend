// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple("どんな質問だ？","何の用だ？");
			link.l1 = RandPhraseSimple("気が変わったんだ。","今は何も言うことはねえ。");
		    link.l1.go = "exit";
			//Jason, суп из черепахи
			if (CheckAttribute(PChar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "baster" && !CheckAttribute(npchar, "quest.terrapin") && CheckAttribute(PChar, "questTemp.Terrapin.SJ_count"))
			{
				link.l1 = "俺はジョーンズさんを探してるんだ。あんた、知ってるか？";
				link.l1.go = "terrapin";
			}
		break;
		
		case "terrapin":
			if (sti(pchar.questTemp.Terrapin.SJ_count) == 5 || rand(9) == 1) // 10% или числом
			{
				dialog.text = "ここにはジョーンズという名の者がたくさんいるぜ。俺が知ってる中で一番有名なのはフォックス大佐の副官、 ベンジャミン・ジョーンズだ。たいてい連隊本部で来客の応対をしてるぜ。";
				link.l1 = "奴にはモリーって名前の妹がいるのか？";
				link.l1.go = "terrapin_yes";
			}
			else
			{
				dialog.text = LinkRandPhrase("どのジョーンズが必要なんだ？俺が知ってるだけでも二十人以上はいるぜ……","ここにはジョーンズが多すぎるんだ。もっと詳しく言ってくれ。","ここにはジョーンズがたくさんいるし、ジョンソンやジャクソンもいるんだぜ。もっと詳しく言ってくれよ、あんた？");
				link.l1 = "彼にはモリーという名の大人の姉がいるんだ。彼女は滅多にいない美人だって聞いたぜ。";
				link.l1.go = "terrapin_no";
			}
			npchar.quest.terrapin = "true";
		break;
		
		case "terrapin_no":
			dialog.text = RandPhraseSimple(LinkRandPhrase("うーん、それについては力になれそうにないな。","いや、俺はそいつを知らねえ。","ふん！俺の知ってるモリー・ジョーンズが絶世の美女なら、フォックス大佐は教区の神父だぜ。"),LinkRandPhrase("モリー・ジョーンズなら何人か知ってるぜ。そのうちの一人には兄貴がいるが……あんたが探してる女じゃねえな。あいつを「稀な美人」なんて呼ぶのは、猿と一緒に暮らしてた野郎くらいだろうよ。","悪いが、俺の知ってるジョーンズたちには姉妹はいねえんだ。","悪いが、俺には手伝えねえ。他の奴に聞いてくれ。"));
			link.l1 = "なるほど。迷惑をかけてすまねえな。";
			link.l1.go = "exit";
			pchar.questTemp.Terrapin.SJ_count = sti(pchar.questTemp.Terrapin.SJ_count)+1;
		break;
		
		case "terrapin_yes":
			dialog.text = "ああ、でも彼女はあいつの兄貴だった方がよかったかもな。このガタイのいい娘は、 その醜いツラのせいで婿なんて見つからねえだろうよ。";
			link.l1 = "感謝する。";
			link.l1.go = "terrapin_yes_1";
		break;
		
		case "terrapin_yes_1":
			DialogExit();
			AddQuestRecord("Terrapin", "2");
			pchar.questTemp.Terrapin.Benjamin = true;
			DeleteAttribute(pchar, "questTemp.Terrapin.SJ_count");
		break;
		
		case "info":
        // заменить на описание неких НПС, по квестам
			dialog.text = "俺があの秘密情報部のために働いてると思うのか "+NationNameGenitive(sti(NPChar.nation))+"?";
			link.l1 = "うーん……いや。じゃあ、さらばだ。";
			link.l1.go = "exit";
			link.l2 = "他に質問はあるか？";
			link.l2.go = "new question";
		break;
		
		case "town":
        // заменить на описание как пройти, по квестам
			dialog.text = "俺が調査局に見えるか？知らねえよ、何も知らねえ。";

            link.l1 = "お前は本当にドジだな！消え失せろ。";
			link.l1.go = "exit";
			link.l2 = "他に質問はあるか？";
			link.l2.go = "new question";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
