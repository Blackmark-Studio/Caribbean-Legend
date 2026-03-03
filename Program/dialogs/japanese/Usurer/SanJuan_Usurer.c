// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("どのようなご質問がありますか？","ご用件をお伺いできますか？"),"少し前にもその質問を私にしようとしましたね……","ああ、当ててみようか……また同じところをぐるぐる回ってるんじゃねえか？","聞きなさい、ここで財務を担当しているのは私です、質問にはお答えしません…","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("考えが変わった……","今は話すことは何もありません。"),"うーん、俺の記憶はどこへ行っちまったんだ…","その通りです、申し訳ありません……","承知しました…",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
