// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("我々の砦はどう思う？なかなか立派だろう、そうだよな？それに守備隊もまだまだ悪くねえぜ、はは…","砦の兵士の生活はかなり退屈だ……見張りや巡回、寝て休んで、また同じことの繰り返しさ。だが町の中は違う……で、何の用だ、 "+GetAddress_Form(NPChar)+"?"),"「くだらない質問で兵士を煩わせるのは感心せんぞ。」 "+GetAddress_Form(NPChar)+"...","今日はもう三度目だぞ、お前が俺に聞こうとしたのは……","兵士でいるのは楽じゃねえが、それでもまたここにいるんだな"+GetSexPhrase("、この野郎、  "," ")+" 俺を怒らせようってのか。気をつけろよ、さもないと砦の地下室行きだぞ……","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("気が変わった、邪魔して悪かったな。","申し訳ないが、話すことは何もない。"),"おっしゃる通りだ、謝る。","おっしゃる通り、もう三度目ですね。失礼しました。","すまん、なんでもねえ。",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
