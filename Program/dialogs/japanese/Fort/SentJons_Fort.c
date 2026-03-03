// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("我々の砦、どう思う？立派だろう、そうじゃねえか？それに駐屯兵も負けてねえぜ、はは…","砦の兵士の生活なんて、退屈なもんさ……見張りや巡回、寝て休んで、また同じことの繰り返しだ。\nだが、町じゃ話が違う……で、何の用だ、 "+GetAddress_Form(NPChar)+"?"),"「兵士にくだらん質問をするのは歓迎されんぞ」 "+GetAddress_Form(NPChar)+"...","今日はもう三度目だぞ、俺に聞こうとしたのは……","兵士でいるのは楽じゃねえが、それでもまたここにいるんだな"+GetSexPhrase("、この野郎、  "," ")+" 俺を怒らせようってのか。気をつけろよ、さもないと砦の地下室送りにしてやるぞ……","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("気が変わった、邪魔して悪かったな。","申し訳ないが、俺から言うことは何もねえ。"),"おっしゃる通りだ、すまない。","おっしゃる通り、もう三度目ですね。失礼しました。","すまん、なんでもねえよ。",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
