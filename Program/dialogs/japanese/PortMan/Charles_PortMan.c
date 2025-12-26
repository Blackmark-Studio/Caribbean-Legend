// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("どんな質問だ？","何の用だ、 "+GetAddress_Form(NPChar)+"?"),"もうすでに俺に質問しようとしただろ "+GetAddress_Form(NPChar)+"...","今日はこれで三度目のご質問ですね……","港の用事について何も話すことがないなら、俺に質問して邪魔するんじゃねえぞ。","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("考えを変えた。","話すことは何もねえ。"),"気にするな。","確かに、もう三度目だな……","悪いが、今は港のことには興味がないんだ。",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
		
		// НСО пошив мундира Xenon-->
		case "Tailor":
			dialog.text = "はい、よく分かっていますよ、そんなに大声を出さなくてもいいでしょう。ですが、すでに説明した通り、 今回は普段よりもずっと多くの書簡や郵便物があったのです。\nご心配なく、あなたの書類が紛失することはありませんし、次の連絡船で必ず届けられます。";
			link.l1 = "...";
			link.l1.go = "Tailor_01";
		break;
		
		case "Tailor_01":
			DialogExit();
			sld = characterFromId("Patria_Tailor");
			sld.dialog.currentnode = "Tailor_02";
			Lai_SetPlayerType(pchar);
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;
		
		case "Tailor_02":
			dialog.text = "まあ、明らかにもっと重要な荷物があったのです。船も積みすぎるわけにはいきませんからね。しかし、 郵便の配達方法については私には詳しい説明がありません。どうか落ち着いて、興奮なさらないでください。 繰り返しますが、あなたの荷物はすべて無事に届きます。ただ、少し遅れるだけです。";
			link.l1 = "...";
			link.l1.go = "Tailor_03";
		break;
		
		case "Tailor_03":
			npchar.dialog.currentnode = "First time";
			DialogExit();
			Lai_SetPlayerType(pchar);
			sld = characterFromId("Patria_Tailor");
			sld.dialog.currentnode = "Tailor_04";
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;
		// <-- пошив мундира
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
