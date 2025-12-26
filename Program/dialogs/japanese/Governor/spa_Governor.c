// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    ref sld;
    int i, iTemp, iMoney, ShipType, Rank;
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = RandPhraseSimple("「どんな質問ですか？」","ご用件は何でしょうか？");
			link.l1 = RandPhraseSimple("「特に重要なことはありません、旦那。」","申し訳ありませんが、私から申し上げることはございません。");
		    link.l1.go = "exit";
		break;
		
		case "work_1":  // работа на благо короны - линейка нации
			if (CheckAttribute(npchar, "notQuestLine"))
			{
                dialog.text = "残念ですが、あなたに仕事を任せるわけにはいきません。今は一緒に働きたい相手ではありませんので。では、 失礼します。";
                link.l1 = "本気じゃないだろう……まあ、仕方ない。";
                link.l1.go = "exit";
				break;
			}                   
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
