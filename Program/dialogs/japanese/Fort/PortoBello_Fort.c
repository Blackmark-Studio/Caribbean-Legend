// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("我々の砦、どう思う？なかなか立派だろう？それに守備隊もまだまだ健在だ、はは…","砦の兵士の生活は、かなり退屈だ……警備や巡回、寝て休んで、また同じことの繰り返しさ。\nだが町の中は違う……で、何の用だ。 "+GetAddress_Form(NPChar)+"?"),"「兵士にくだらん質問をするのは歓迎されんぞ」 "+GetAddress_Form(NPChar)+"...","今日はもう三度目だぞ、お前が俺に聞こうとしたのは……","兵士でいるのは楽じゃねえが、それでもまたここに来たんだな"+GetSexPhrase("、この野郎、  "," ")+" 俺を怒らせようってのか。気をつけろよ、そうしないと砦の地下にぶち込まれるぞ…","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("気が変わった、邪魔して悪かったな。","申し訳ないが、何も言うことはない。"),"おっしゃる通りです、失礼しました。","おっしゃる通りだ、もう三度目だな。すまない。","すまん、なんでもねえ。",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
