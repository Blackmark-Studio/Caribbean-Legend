// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("我々の砦、どう思う？なかなか立派だろう？それに守備隊も負けてねえぜ、はは…","砦の兵士の生活は、かなり退屈だ……警備や巡回、寝て休んで、また同じことの繰り返しさ。\nだが町では違う……何の用だ、 "+GetAddress_Form(NPChar)+"?"),"「くだらん質問で兵士を煩わせるのは感心せんぞ。」 "+GetAddress_Form(NPChar)+"...","今日はもう三度目だぞ、お前が俺に聞こうとしたのは……","兵士でいるのは楽じゃねえが、それでもまたここに来たんだな"+GetSexPhrase("、この野郎、  "," ")+" 俺を怒らせようってのか。気をつけろよ、さもないと砦の地下にぶち込まれるぞ…","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("気が変わったんだ、邪魔して悪かったな。","話すことは何もない、すまない。"),"おっしゃる通りだ、謝るよ。","おっしゃる通り、もう三度目ですね。失礼しました。","すまん、なんでもねえ。",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
