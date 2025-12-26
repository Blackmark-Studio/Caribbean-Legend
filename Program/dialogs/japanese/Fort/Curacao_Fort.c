// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("我々の砦、どう思う？なかなか立派だろう？それに守備隊もまだまだ悪くねえぜ、はは…","砦の兵士の生活は、かなり退屈だ……見張りと巡回、寝て休んで、また同じことの繰り返しさ。だが、町の中は違う……それで、何の用だ、 "+GetAddress_Form(NPChar)+"?"),"「くだらん質問で兵士を煩わせるのは感心せんぞ。」 "+GetAddress_Form(NPChar)+"...","今日はもう三度目だぞ、お前が俺に聞こうとしたのは……","兵士でいるのは楽じゃねえが、それでもまたここに来たんだな"+GetSexPhrase("、この野郎、  "," ")+" 俺を怒らせようってのか。気をつけろよ、さもないと砦の地下牢行きだぜ……","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("気が変わった、邪魔して悪かったな。","申し訳ないが、何も言うことはない。"),"おっしゃる通りだ、失礼した。","おっしゃる通り、もう三度目ですね。失礼しました。","すまん、なんでもねえよ。",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
