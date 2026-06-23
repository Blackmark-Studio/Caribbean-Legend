// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Какие вопросы?", "Что вам угодно?"), "Совсем недавно вы пытались задать мне вопрос...", "У себя на верфи, да и вообще в городе, я таких однообразно любознательных не видал.",
                          "Ну что за вопросы? Моё дело - корабли строить, давайте этим и займёмся.", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Я "+ GetSexPhrase("передумал","передумала") +"...", "Сейчас мне не о чем говорить."), "Хм, что-то с памятью моей стало...",
                      "Хм, однако...", "Давайте...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
		
		case "helendrinking_buy_rainbow":
			dialog.text = "... достойный выбор, сэр. Значит, по рукам?";
			link.l1 = "Д-да! и-ик! Давай, заворачивай и гони к пирсу. И поживее, меня д-дама ждёт на улице!";
			link.l1.go = "helendrinking_buy_rainbow_1";
			locCameraFromToPos(0.36, 1.86, 1.15, true, 2.06, -0.20, -4.38);
		break;
		
		case "helendrinking_buy_rainbow_1":
			dialog.text = "За всё про всё пятьдесят тысяч серебром, сэр.";
			if (int(pchar.money) >= 55000) {
				link.l1 = "С-сколько ты сказал? П-пять тыщ? Н-на, сам считай! И ещё п-пять сверху бери себе. Гуляем!";
				link.l1.go = "helendrinking_buy_rainbow_yes";
			}
			
			link.l2 = "Не-а, я конечно парень, и-ик! ... богатый, но за столько не возьму. Нет, сэр! Бывай, л-лодочник.";
			link.l2.go = "helendrinking_buy_rainbow_no";
		break;
		
		case "helendrinking_buy_rainbow_yes":
			dialog.text = "Благодарю вас, сэр. Пусть она хорошо вам послужит!";
			link.l1 = "";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "First time";
			
			AddMoneyToCharacter(pchar, -55000);
			pchar.questTemp.HelenDrinking.BoughtRainbow = true;
			
			AddDialogExitQuestFunction("HelenDrinking_GoToPerlas");
		break;
		
		case "helendrinking_buy_rainbow_no":
			dialog.text = "Ага, проваливай, богатый парень. Мы уже три часа как закрыты.";
			link.l1 = "";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "First time";
			
			AddDialogExitQuestFunction("HelenDrinking_GoToPerlas");
		break;
		
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

