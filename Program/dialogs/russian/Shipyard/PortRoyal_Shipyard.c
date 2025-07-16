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
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx"))
            {
				if (pchar.questTemp.Mtraxx == "silk_2" || pchar.questTemp.Mtraxx == "silk_3")
				{
					link.l1 = "Я знаю, что на вашей верфи улучшают ходовые качества кораблей: скорость и ход в бейдевинд. Для этой работы используется редкий товар - корабельный шёлк. Вам... было бы интересно поговорить об этом?";
					link.l1.go = "mtraxx";
				}
			}
			if (CheckAttribute(npchar, "quest.upgradeship")) {
				link.l2 = "Я от мисс МакАртур, по поводу...";
				link.l2.go = "helen_upgradeship";
			}
			
			if (CheckAttribute(npchar, "quest.upgradeship.money") && HelenCanUpgrade()) {
				link.l2 = "Принимайте корабль на доводку!";
				link.l2.go = "helen_upgradeship_money";
			}
		break;
		
		// Addon 2016-1 Jason пиратская линейка
		case "mtraxx":
            dialog.text = "Молодой человек, изъясняйтесь понятнее. Что у вас ко мне за дело? Вам нужно провести работы по улучшению вашего корабля? Давайте обсудим.";
			link.l1 = "Нет, я имею в виду другое. Вы используете в работе товар, который нельзя приобрести в магазинах или где-то заказать. А я хочу вам предложить то, в чём нуждается ваше производство.";
			link.l1.go = "mtraxx_1";
		break;
		
		case "mtraxx_1":
            dialog.text = "Так-так... Кхм... Вы вообще в курсе, что купля-продажа данного товара в нашей колонии находится под контролем властей? Вы можете предоставить мне шёлк для работы, но продавать не имеете права, так же как и я купить его у вас. За это полагается крупный штраф.";
			link.l1 = "Но мы же не в магазине и не на таможне...";
			link.l1.go = "mtraxx_2";
		break;
		
		case "mtraxx_2":
            dialog.text = "Весь шёлк для работы я получаю либо от клиентов, либо приобретаю в ограниченных количествах по специальному разрешению губернатора. Ещё вопросы есть? Если нет - не мешайте работать.";
			link.l1 = "Гм... Ладно. Всего доброго, мастер.";
			link.l1.go = "mtraxx_3";
		break;
		
		case "mtraxx_3":
            DialogExit();
			AddQuestRecord("Roger_2", "5");
			pchar.questTemp.Mtraxx = "silk_4";
		break;
		
		case "helen_upgradeship":
			dialog.text = "Как же, знаю! Счастливчик вы, капитан. Вы по поводу полной доводки корабля? Всё сделаем, наша верфь не уступает верфям Плимута!";
			link.l1 = "Я так понимаю, это всё равно не будет бесплатной услугой?";
			link.l1.go = "helen_upgradeship_1";
		break;
		
		case "helen_upgradeship_1":
			dialog.text = "Конечно, капитан, такие услуги не могут быть бесплатными даже для Кромвеля! Однако, я слово держу и возьму только деньги - таскать контрабанду вам не придётся.";
			link.l1 = "Разумеется. Сколько?";
			link.l1.go = "helen_upgradeship_2";
		break;
		
		case "helen_upgradeship_2":
			dialog.text = "Зависит от размеров вашего флагмана, капитан. Корабль первого ранга пойдёт за пять тысяч дублонов, а пятого - всего за тысячу.";
			link.l1 = "Хорошо, я зайду к вам, как приму решение.";
			link.l1.go = "exit";
			
			npchar.quest.upgradeship.money = true;
		break;
		
		case "helen_upgradeship_money":
			dialog.text = "Замечательно, теперь всё в наличии. Начинаю работу...";
			link.l1 = "Жду.";
			link.l1.go = "helen_upgradeship_money_1";
			
			iTemp = GetCharacterShipType(pchar);
			sld = GetRealShip(iTemp);
			iTemp = (7 - sti(sld.class)) * 1000;
			RemoveDublonsFromPCharTotal(iTemp);
		break;
		
		case "helen_upgradeship_money_1":
			AddTimeToCurrent(6, 30);
			dialog.text = "... Вроде бы всё... Качество работы гарантирую.";
			link.l1 = "Спасибо! Проверю обязательно.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenUpgradeShip2");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

bool HelenCanUpgrade() {
	int shipIndex = GetCharacterShipType(pchar);
	if (shipIndex == SHIP_NOTUSED) {
		return false;
	}
	
	sld = GetRealShip(shipIndex);
	if (sti(sld.class) == 7) {
		return false;
	}
	
	int cost = (7 - sti(sld.class)) * 1000;
	return (PCharDublonsTotal() >= cost);
}
