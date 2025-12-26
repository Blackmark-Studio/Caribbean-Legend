// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("どんな質問だ？","何の用だ、 "+GetAddress_Form(NPChar)+"?"),"もうすでに俺に質問しようとしたじゃねえか "+GetAddress_Form(NPChar)+"...","今日はこれで三度目の質問だな……","港の用件について何も話すことがないなら、くだらない質問で俺を煩わせるな。","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("考えを変えた。","話すことは何もねえ。"),"気にするな。","確かに、もう三度目だな……","悪いが、今は港のことには興味がないんだ。",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "maarten1")
			{
				link.l1 = "フランスの旗の下にある『アドミラブル』というガレオン船を探しているんだ。 その船長はガイウス・マルシェという名だった。彼が次にどこへ航海したか教えてもらえないか？ もしかしてここで登録していったのか？";
                link.l1.go = "guardoftruth";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "ふむ、「アドミラブル」号か？ガレオン船だな。覚えているぞ。ええと……バルバドスのブリッジタウンまでパプリカを運ぶために貸し出したんだ。何かあったのか？";
			link.l1 = "いいや、でもガイウスは俺の友人だし、会うのを楽しみにしているんだ。";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "それならバルバドスへ航海しろ。ただし、そこに奴がいるとは思えねえ、もうずいぶん前のことだからな。 少なくとも現地の港長に協力を頼んでみるといい。";
			link.l1 = "また出発だな、俺は。";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			DialogExit();
			AddQuestRecord("Guardoftruth", "12");
			pchar.questTemp.Guardoftruth = "barbados";
		break;

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
