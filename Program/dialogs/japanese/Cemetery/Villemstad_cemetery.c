// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("どうお手伝いしましょうか？","俺に何か用か？"),"「どうした、何か悩みでもあるのか、」 "+GetAddress_Form(NPChar)+"?","「三度目だが、」 "+GetAddress_Form(NPChar)+"、何の用だ？","もううんざりだ。出て行け！","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("気が変わった、すまねえ。","たいしたことじゃねえ、すまねえな。"),"許してくれ、なんでもねえよ。","おっしゃる通りだ、もう三度目だな。すまねえ……","申し訳ない。",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2); 
}
