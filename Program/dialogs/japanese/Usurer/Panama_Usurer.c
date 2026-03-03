// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("どのようなご質問がありますか？","ご用件をお伺いしましょうか？"),"つい最近もその質問を私にしようとしましたね……","ああ、どうせまた同じところをぐるぐる回ってるんだろう？","聞きなさい、ここで財務を担当しているのは私です、質問にはお答えしません…","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("考えが変わった……","今は話すことは何もありません。"),"うーん、俺の記憶はどこへ行っちまったんだ……","ご明察ですね、申し訳ありません……","承知しました……",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
		
		// Реакция ростовщика Панамы на репутацию ГГ или на разграбление Картахены по сюжету
		case "Panama_Deposit_NoReputation":
			dialog.text = "その通りです……国王の臣民に愛される名誉ある方なら、どの国籍であろうと私の銀行は決してお断りいたしません。";
			link.l1 = "承知しました。さようなら。";
			link.l1.go = "exit";
		break;
		
		case "Panama_Deposit_Cartahena":
			dialog.text = "しかし、残念ながら私の娘と義父がそれにかかってしまった。彼らはカルタヘナに住んでいたんだ。行ってくれ、 "+GetAddress_Form(NPChar)+"。ここはあなたを歓迎しません。";
			if (pchar.questTemp.Mtraxx.Retribution.Choice == "good")
			{
				link.l1 = "お許しください。では、失礼いたします。";
				link.l1.go = "exit";
			}
			else
			{
				link.l1 = "あなたの損失ですね。さようなら。";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "NeHochuRazgovarivat";
		break;
		
		case "Panama_Deposit_SgorelVklad":
			dialog.text = "資金はカルタヘナ市襲撃の被害者を救済するため、王室によって押収されました。お力にはなれません。 警備兵を呼ぶ前に、直ちに私の銀行からお引き取りいただきますようお願いいたします！";
			link.l1 = "「これを後悔することになるぞ……」";
			link.l1.go = "exit";
			NextDiag.TempNode = "NeHochuRazgovarivat";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
