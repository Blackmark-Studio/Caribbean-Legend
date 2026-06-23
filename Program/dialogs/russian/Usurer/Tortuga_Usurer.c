// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Какие вопросы?", "Что вам угодно?"), "Совсем недавно вы пытались задать мне вопрос...", "М-да, позвольте угадаю... Опять ничего существенного?",
                          "Послушайте, я финансами оперирую, а не на вопросы отвечаю...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Я "+ GetSexPhrase("передумал","передумала") +"...", "Сейчас мне не о чем говорить."), "Хм, что-то с памятью моей стало...",
                      "Вы угадали, простите...", "Я понимаю...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
		
		case "tonzag_bail":
			dialog.text = "Здравствуйте, капитан. Чем я и моя фирма могут быть вам полезны?";
			link.l1 = "Хочу сделать пожертвование в пенсионный фонд славного гарнизона Тортуги.";
			link.l1.go = "tonzag_bail_1";
		break;
		
		case "tonzag_bail_1":
			dialog.text = "Понимаю. Что-то зачастили! Сколько вы должны... то есть, хотите пожертвовать?";
			link.l1 = pchar.questTemp.TonzagQuest.Bail + " дублонов. Скажите, вы принимаете в песо?";
			link.l1.go = "tonzag_bail_2";
		break;
		
		case "tonzag_bail_2":
			dialog.text = "Разумеется, однако это выйдет для вас немного дороже. Сейчас скажу точнее... " + pchar.questTemp.TonzagQuest.Bail + " дублонов это будет " + int(pchar.questTemp.TonzagQuest.Bail) * 150 + " песо.";
			if (PCharDublonsTotal() >= int(pchar.questTemp.TonzagQuest.Bail) || int(pchar.money) >= int(pchar.questTemp.TonzagQuest.Bail) * 150) {
				link.l1 = "Немного дороже, говорите? Прошу, вот нужная сумма.";
				link.l1.go = "tonzag_bail_give";
			} else {
				link.l1 = "Немного дороже, говорите? К сожалению, такой суммой пока не располагаю. Скажите, а есть возможность взять кредит под это дело?";
				link.l1.go = "tonzag_bail_loan";
			}
		break;
		
		case "tonzag_bail_give":
			dialog.text = "Замечательно. Мы немедленно сообщим вашему контрагенту! До свидания, капитан. И... удачи, мы давно ждём вашего выступления.";
			link.l1 = "До свидания.";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "First time";
			
			if (PCharDublonsTotal() >= int(pchar.questTemp.TonzagQuest.Bail)) {
				RemoveDublonsFromPCharTotal(int(pchar.questTemp.TonzagQuest.Bail));
			} else {
				AddMoneyToCharacter(pchar, -(int(pchar.questTemp.TonzagQuest.Bail) * 150));
			}
			sld = CharacterFromID("TortugaJailOff");
			LAi_CharacterEnableDialog(sld);
			sld.dialog.currentnode = "tonzag_bailed";
		break;
		
		case "tonzag_bail_loan":
			dialog.text = "Для вас такая возможность всегда имеется, капитан! Скажем, с возвращением двухсот тысяч песо через полгода?";
			link.l1 = "Выбора у меня нет. Куда ставить подпись?";
			link.l1.go = "tonzag_bail_give";
			
			pchar.quest.loans.tortuga.sum = 200000;
			pchar.quest.loans.tortuga.interest = 0;
			pchar.quest.loans.tortuga.period = 6;
			pchar.quest.loans.tortuga.StartDay = GetDataDay();
			pchar.quest.loans.tortuga.StartMonth = GetDataMonth();
			pchar.quest.loans.tortuga.StartYear = GetDataYear();
			pchar.quest.loans.tortuga.StartTime = GetTime();
			SetTimerCondition("Loans_Tortuga", 0, int(pchar.quest.loans.tortuga.period), 0, false);
			pchar.quest.Loans_Tortuga.CityId = "Tortuga";
			pchar.quest.Loans_Tortuga.win_condition = "LoansForAll";
			
			AddMoneyToCharacter(pchar, int(pchar.questTemp.TonzagQuest.Bail) * 150);
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

