// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("我々の砦、どう思う？なかなか立派だろう？それに駐屯兵も負けてねえぜ、はは…","砦の兵士の生活はかなり退屈だ……見張りや巡回、寝て休んで、また同じことの繰り返しさ。\nだが町の中は違う……で、何の用だ、 "+GetAddress_Form(NPChar)+"?"),"「兵士にくだらない質問をして迷惑をかけるのは感心しないぞ」 "+GetAddress_Form(NPChar)+"...","今日はもう三度目だぞ、俺に聞こうとしたのは……","兵士でいるのは楽じゃねえが、それでもまたここに来たんだな"+GetSexPhrase("、この野郎、  "," ")+" 俺を怒らせようってのか。気をつけろよ、さもないと砦の地下にぶち込むぞ……","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("気が変わった、邪魔して悪かったな。","申し訳ないが、話すことは何もない。"),"おっしゃる通りだ、すまない。","おっしゃる通り、もう三度目ですね。失礼しました。","すまん、なんでもねえ。",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
