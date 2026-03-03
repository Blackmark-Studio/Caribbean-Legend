// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("我々の砦をどう思う？なかなか立派だろう、そうじゃねえか？それに守備隊も負けず劣らずだぜ、はは…","砦の兵士の生活なんて、正直退屈なもんだ……見張りと巡回、寝て休んで、また同じことの繰り返しさ。だが町の中は違う……で、何の用だ、 "+GetAddress_Form(NPChar)+"?"),"「兵士にくだらない質問をして迷惑をかけるのは感心せんぞ。」 "+GetAddress_Form(NPChar)+"...","今日はもう三度目だぞ、俺に聞こうとしたのは……","兵士でいるのは楽じゃねえが、それでもまたここに来たんだな"+GetSexPhrase("、この野郎、  "," ")+" 俺を怒らせようってのか。気をつけろよ、さもないと砦の地下牢行きだぞ…","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("気が変わった、邪魔して悪かったな。","申し訳ないが、話すことは何もない。"),"おっしゃる通りだ、謝罪する。","おっしゃる通りだ、もう三度目だな。失礼した。","すまん、なんでもねえよ。",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
