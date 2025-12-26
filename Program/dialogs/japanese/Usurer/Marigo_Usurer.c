// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("ご質問は何でしょうか？","どのようなご用件でしょうか？"),"つい最近もその質問を私にしようとしましたね……","ああ、さては……また堂々巡りってわけか？","聞きなさい、ここでは私が財務を担当していますので、質問にはお答えしません…","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("考えが変わった……","今は話すことは何もありません。"),"うーん、俺の記憶はどこへ行っちまったんだ…","お察しの通りです、申し訳ありません……","承知しました……",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
