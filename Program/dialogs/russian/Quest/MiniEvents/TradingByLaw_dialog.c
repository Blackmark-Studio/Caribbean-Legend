void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "Что вам надо?";
			link.l1 = "Ничего.";
			link.l1.go = "exit";
		break;
		
		case "Kristian":
			dialog.text = "Приветствую вас в моём доме! Меня зовут Кристиан. Кристиан Делюш. Чем могу помочь?";
			link.l1 = "Я - капитан "+GetFullName(pchar)+". Мне нужно прикупить партию спиртного. Вы понимаете, о чём я?";
			link.l1.go = "Kristian_2";
			DelLandQuestMark(npchar);
		break;
		
		case "Kristian_2":
			dialog.text = "Что??? Кто вам такое сказал? Это всё какая-то ошибка, уверяю вас, я не торгую никаким спиртным!";
			link.l1 = "Так-так. Вижу, я по адресу.";
			link.l1.go = "Kristian_3";
		break;
		
		case "Kristian_3":
			dialog.text = "О-о-о, нет-нет, что вы! Никакой торговли спиртным, вы что, я... я просто, э-э, ну... Да, у меня есть товары, но это... это всё по закону! Я просто покупаю для частных лиц, э-э... ну, для праздников, для небольших встреч!";
			link.l1 = "Что же вы так разволновались? Я вас не арестовывать приш"+GetSexPhrase("ёл","ла")+", а процветанию дела поспособствовать. И мои карманы, надеюсь, пополнятся парой золотых.";
			link.l1.go = "Kristian_4";
		break;
		
		case "Kristian_4":
			dialog.text = "Я... я вовсе не волнуюсь! С чего бы мне волноваться? Я честный горожанин, мой дом прямо возле резиденции губернатора. Я ничего не нарушаю, уверяю вас!";
			link.l1 = "Значит, вы не торгуете спиртным? Жаль, очень жаль. Видите ли, у меня есть очень выгодное предложение. Уверен, столько дублонов мелкому подпольному торговцу и не снилось. Ну, раз вы не тот, кто мне нужен, то я, пожалуй, пойду. Да?";
			link.l1.go = "Kristian_5";
		break;
		
		case "Kristian_5":
			dialog.text = "Э-э... постойте... "+GetAddress_Form(NPChar)+"... простите, я просто совсем растерялся от волнения, забыл, как вас зовут.";
			link.l1 = "Капитан "+GetFullName(pchar)+".";
			link.l1.go = "Kristian_6";
		break;
		
		case "Kristian_6":
			dialog.text = ""+GetSexPhrase("Месье","Мадмуазэль")+" "+pchar.lastname+", дело в том, э-э... ну... я знаю, где найти того, кто вам нужен. Могу передать ему... ваше предложение.";
			link.l1 = "Передать? Вы действительно думаете, что в таком деле стоит что-то передавать через посторонних людей?";
			link.l1.go = "Kristian_7";
		break;
		
		case "Kristian_7":
			dialog.text = "Вы правы. Но... эх... была не была... да, это я тот, кто вам нужен.";
			link.l1 = "Ну вот, так-то лучше, Кристиан. Видите ли, в таверне сейчас большие проблемы с поставками спиртного, и я надеюсь, что мы с вами сможем извлечь из этого выгоду.";
			link.l1.go = "Kristian_8";
		break;
		
		case "Kristian_8":
			dialog.text = "Капитан, мне известно о затруднениях трактирщика, ибо народ повалил ко мне, и мне уже стало страшно торговать - это привлекает слишком много внимания. Вот я и подумал, что вы... ну, вы понимаете...";
			link.l1 = "Почему же вы не предложили ему свои услуги?";
			link.l1.go = "Kristian_9";
		break;
		
		case "Kristian_9":
			dialog.text = "Он... он ни за что не станет со мной сотрудничать. Этот человек терпеть не может мелких дельцов вроде меня.";
			link.l1 = "Да, об этом я слышал. С вами - может и не станет. А вот со мной - станет.";
			link.l1.go = "Kristian_10";
		break;
		
		case "Kristian_10":
			dialog.text = "Вы хотите стать посредником? Что ж, я не против... мы тут на днях партию завезли - это настоящий рекорд! Мне её должно было хватить, пожалуй, на полгода. Но, Бог свидетель, только чудо спасло нас от раскрытия\nЯ до сих пор не понимаю, как нам удалось ускользнуть. Повторять такое во второй раз было бы самоубийством.";
			link.l1 = "Тогда вам стоит выйти из тени. Хотя бы частично.";
			link.l1.go = "Kristian_11";
		break;
		
		case "Kristian_11":
			dialog.text = "В-выйти из тени? Но... это же... для этого нужны связи! И деньги! Да и зачем? Разве вы, капитан судна, осядете в городе и займётесь поставками для местной таверны?";
			link.l1 = "Со связями, полагаю, я смогу вам помочь. Насчёт денег... Не думаю, что потребуется слишком много. А что до последнего - то это и не понадобится. Вы будете действовать от моего имени. Я помогу вам, а вы будете помогать мне. Причём на регулярной основе. Вы получаете стабильный сбыт, а я - надёжного поставщика. Как вам такая сделка?";
			link.l1.go = "Kristian_12";
		break;
		
		case "Kristian_12":
			dialog.text = "Я уж думал, что всё это ловушка. Но, если честно, ваше предложение звучит... весьма заманчиво. Стабильность, надёжность... Кто бы мог подумать, что мне выпадет такой шанс. "+GetSexPhrase("Месье","Мадмуазэль")+", я согласен! Сколько вы хотите покупать?";
			link.l1 = "Для начала займёмся легализацией вашего дела, а уж потом перейдём к обсуждению деталей. Сколько рома и вина у вас есть прямо сейчас?";
			link.l1.go = "Kristian_13";
		break;
		
		case "Kristian_13":
			dialog.text = "Прямо сейчас? Э-э... давайте пройдём в погреб, там я смогу назвать вам точное количество.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TPZ_GoToPogreb");	// спускаемся в погреб
		break;
		
		// погреб
		case "Kristian_15":
			dialog.text = "Так-так... Что тут у нас? Ага\nСейчас у меня в наличии ровно сто бутылок рома и сто бутылок вина.";
			link.l1 = "Что ж, думаю, для начала этого будет достаточно. Если проблему с ввозом удастся уладить, вы сможете привозить такие партии ежемесячно, без сбоев?";
			link.l1.go = "Kristian_16";
		break;
		
		case "Kristian_16":
			dialog.text = "Разумеется, капитан! И даже в три, нет-нет... в четыре раза больше смогу! Сбоев не будет, я всегда буду держать на складе нужное количество, чтобы, случись что, перекрыть любую накладку.";
			link.l1 = "Сколько вы хотите получить за эту партию?";
			link.l1.go = "Kristian_17";
		break;
		
		case "Kristian_17":
			dialog.text = "Меня устроит: десять дублонов за каждые десять бутылок вина и три дублона за десять бутылок рома. То есть всего сто тридцать дублонов за всю партию.";
			link.l1 = "Хорошо. Я поговорю с трактирщиком и скоро вернусь.";
			link.l1.go = "Kristian_18";
		break;
		
		case "Kristian_18":
			DialogExit();
			
			NextDiag.CurrentNode = "Kristian_18_1";
			pchar.questTemp.TPZ_Tavern_2 = true;
			AddLandQuestMark(characterFromId("BasTer_tavernkeeper"), "questmarkmain");
			AddQuestRecord("TPZ", "4");
		break;
		
		case "Kristian_18_1":
			dialog.text = "Капитан, есть новости? Что сказал трактирщик?";
			link.l1 = "Как раз к нему направляюсь.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Kristian_18_1";
		break;
		
		case "Kristian_21":
			dialog.text = "Как всё прошло, капитан? Вам удалось договориться с трактирщиком?";
			if (CheckAttribute(pchar, "questTemp.TPZ_Vino240"))
			{
				link.l1 = "Я потрудился на славу, Кристиан. Он купит эту и все последующие партии по двести сорок дублонов. За первую я заплачу вам сто тридцать дублонов, как вы и просили. Остаток оставлю себе в качестве награды за мои труды. А вся дальнейшая прибыль - целиком и полностью ваша.";
			}
			if (CheckAttribute(pchar, "questTemp.TPZ_Vino200"))
			{
				link.l1 = "Я хорошо потрудился, Кристиан. Он купит эту партию и все последующие по двести дублонов. За первую я заплачу вам сто тридцать дублонов, как вы и просили. Остаток оставлю себе в качестве награды за мои труды. А вся дальнейшая прибыль - целиком и полностью ваша.";
			}
			link.l1.go = "Kristian_22";
			DelLandQuestMark(npchar);
		break;
		
		case "Kristian_22":
			dialog.text = "Вот это новость, капитан! Я и мечтать не мог о такой сделке, спасибо вам! Но... не поторопились ли вы? Губернатор... я... то есть...";
			link.l1 = "С губернатором всё улажено. Теперь каждый месяц вы будете платить налог - сто дублонов и предоставлять отчётность о своей торговле.";
			link.l1.go = "Kristian_23";
		break;
		
		case "Kristian_23":
			dialog.text = "Невероятно! Как вам это удалось, капитан? Губернатор ведь человек строгий, да ещё и ярый противник теневой торговли...";
			link.l1 = "В том-то и дело, Кристиан, что он противник теневой торговли, но не честной. Он охотно выслушал меня и озвучил условия торговли спиртным на острове. Вы будете работать от моего имени, и за все ваши проступки я буду отвечать наравне с вами. Так что не подведите, иначе я найду вас даже на том свете.";
			link.l1.go = "Kristian_24";
		break;
		
		case "Kristian_24":
			dialog.text = "Клянусь, капитан, вы не пожалеете!";
			link.l1 = "Теперь нам нужно завершить сделку с трактирщиком, после чего мы обсудим детали нашего с вами сотрудничества.";
			link.l1.go = "Kristian_25";
		break;
		
		case "Kristian_25":
			dialog.text = "Конечно, капитан. Вы готовы забрать партию прямо сейчас? Это будет стоить сто тридцать дублонов.";
			if (PCharDublonsTotal() >= 130)
			{
				link.l1 = "Да, вот ваши дублоны.";
				link.l1.go = "Kristian_26";
			}
			else
			{
				link.l1 = "Прямо сейчас у меня нет нужной суммы. Ждите меня здесь, я найду деньги и вернусь.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Kristian_25_1";
			}
		break;
		
		case "Kristian_25_1":
			dialog.text = "Капитан! Вы вернулись, чтобы забрать товар? Это будет стоить сто тридцать дублонов.";
			if (PCharDublonsTotal() >= 130)
			{
				link.l1 = "Именно так! Вот ваши дублоны.";
				link.l1.go = "Kristian_26";
			}
			else
			{
				link.l1 = "К сожалению, я пока не обладаю нужной суммой. Загляну позже.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Kristian_25_1";
			}
		break;
		
		case "Kristian_26":
			dialog.text = "Благодарю! Забирайте! Сто бутылок вина и сто бутылок рома, как и договаривались.";
			link.l1 = "Товар заберут мои матросы. А я пока поговорю с трактирщиком.";
			link.l1.go = "Kristian_27";
			RemoveDublonsFromPCharTotal(130);
		break;
		
		case "Kristian_27":
			DialogExit();
			
			LAi_CharacterDisableDialog(npchar);
			pchar.questTemp.TPZ_Tavern_4 = true;
			AddLandQuestMark(characterFromId("BasTer_tavernkeeper"), "questmarkmain");
		break;
		
		case "Kristian_31":
			dialog.text = ""+pchar.name+"! Вы уже здесь! Ну как, всё прошло успешно?";
			link.l1 = "Всё в порядке, Кристиан. Трактирщик будет забирать такие же партии дважды в месяц. Обеспечьте ему стабильные поставки - и вы забудете, что такое бедность.";
			link.l1.go = "Kristian_32";
			DelLandQuestMark(npchar);
		break;
		
		case "Kristian_32":
			dialog.text = "Капитан... вы... вас словно сама судьба ко мне привела! Это просто чудо какое-то, я всё ещё не верю! Чем я заслужил такую доброту? Я не знаю, как вас благодарить!";
			link.l1 = "Зато я знаю, Кристиан. Каждый месяц у вас должна быть отложена часть товара специально для меня - и никого другого. Покупать я её буду по той цене, которую вы озвучили: десять дублонов за десяток бутылок вина и три дублона за десяток бутылок рома.";
			link.l1.go = "Kristian_33";
		break;
		
		case "Kristian_33":
			dialog.text = "Буду счастлив, "+pchar.name+", придерживать для вас товар! Будьте уверены, я не подведу! Сколько всего вы будете забирать? По пятьдесят? По сто бутылок? Любое количество - только скажите!";
			link.l1 = "Так много мне пока не нужно. По двадцать бутылок будет вполне достаточно. Если потребуется больше - я дам вам знать.";
			link.l1.go = "Kristian_34";
		break;
		
		case "Kristian_34":
			dialog.text = "Конечно-конечно! Итак, двадцать бутылок вина и двадцать рома за 26 дублонов. Каждый месяц 15-го числа, товар будет вас ждать. Буду рад видеть вас в любое время, даже если зайдёте просто поздороваться!";
			link.l1 = "Отлично! И ещё, Кристиан. Я поручился за вас своим именем. Так что не подведите.";
			link.l1.go = "Kristian_35";
		break;
		
		case "Kristian_35":
			dialog.text = "Я... что вы, капитан... вы... нет-нет, я не подведу! Всё будет на высшем уровне, клянусь!";
			link.l1 = "Тогда до встречи!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TPZ_SpawnShip");
		break;
		
		case "Pirate_1":
			dialog.text = "Мерзав"+GetSexPhrase("ец","ка")+"! Разве тебя не учили, что совать нос в чужие дела - это всегда к неприятностям?";
			link.l1 = "Ты сам на меня напал, а теперь ещё и говоришь, что я в чужие дела лезу? Ты, похоже, умом тронулся?";
			link.l1.go = "Pirate_2";
		break;
		
		case "Pirate_2":
			dialog.text = "Молния мне в бушприт! Так ты, "+GetSexPhrase("ублюдок","дрянь")+", даже не понимаешь, во что влез"+GetSexPhrase("","ла")+"? Думаешь, поставки в таверну просто так прекратились?";
			link.l1 = "Хочешь сказать, что та фактория твоими стараниями сгорела?";
			link.l1.go = "Pirate_3";
		break;
		
		case "Pirate_3":
			dialog.text = "Ха-ха, ну наконец-то до тебя дошло, ядро мне в печень. Именно моими! Слишком уж крепко он в этом деле сидел. Но, как видишь, я всегда нахожу способ победить противника. И тебе тоже не уйти, книппель мне в грот!";
			link.l1 = "Забавно. Ну, проверим, насколько ты хорош, акулу тебе в глотку! Ха-ха!";
			link.l1.go = "Pirate_4";
		break;
		
		case "Pirate_4":
			DialogExit();
			
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree();
			LAi_SetFightMode(pchar, true);
		break;
		
		case "Kristian_41":
			dialog.text = "Здравствуйте, "+pchar.name+"! По какому делу зашли?";
			if(CheckAttribute(pchar, "questTemp.TPZ_TradeVinoAndRom")) // торговля вином и ромом
			{
				if (GetDataDay() == 15)
				{
					link.l1 = "Здравствуйте, Кристиан. Товар для меня готов?";
					link.l1.go = "Kristian_42";
				}
			}
			link.l2 = "Здравствуйте, Кристиан. Просто хотел"+GetSexPhrase("","а")+" посмотреть, как вы. Уже ухожу.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Kristian_41";
		break;
		
		case "Kristian_42":
			if (CheckAttribute(pchar, "questTemp.TPZ_UpgradeVino"))
			{
				dialog.text = "Разумеется, капитан! Неужели вы могли усомниться в моей надёжности?";
				if (PCharDublonsTotal() >= 130)
				{
					link.l1 = "Конечно, нет, Кристиан. Вот ваши дублоны, выпивку я забираю.";
					link.l1.go = "Kristian_43";
				}
				else
				{
					link.l2 = "Нисколько. Однако, я забыл"+GetSexPhrase("","а")+" прихватить дублоны. Возможно, я загляну чуть позже.";
					link.l2.go = "exit";
					NextDiag.TempNode = "Kristian_41";
				}
			}
			else
			{
				dialog.text = "Разумеется, капитан! Неужели вы могли усомниться в моей надёжности?";
				if (PCharDublonsTotal() >= 26)
				{
					link.l1 = "Конечно, нет, Кристиан. Вот ваши дублоны, выпивку я забираю.";
					link.l1.go = "Kristian_43";
				}
				else
				{
					link.l2 = "Нисколько. Однако, я забыл"+GetSexPhrase("","а")+" прихватить дублоны. Возможно, я загляну чуть позже.";
					link.l2.go = "exit";
					NextDiag.TempNode = "Kristian_41";
				}
			}
			if(sti(pchar.questTemp.TPZ_KritstianVinoAndRom) >= 1 && !CheckAttribute(pchar, "questTemp.TPZ_KritstianVinoBlock")) // увеличить объём поставок вина и рома
			{
				link.l4 = "Кристиан, я хочу покупать больше. Скажем, по сто бутылок рома и вина ежемесячно.";
				link.l4.go = "UpgradeVino";
			}
			if(sti(pchar.questTemp.TPZ_KritstianVinoAndRom) >= 1 && CheckAttribute(pchar, "questTemp.TPZ_KritstianVinoPotom") && sti(pchar.Money) >= 50000) // увеличить объём поставок вина и рома, если в первый раз не принесли
			{
				link.l4 = "Кристиан, я хочу обсудить увеличение поставок.";
				link.l4.go = "UpgradeVino_Agreed";
			}
		break;
		
		case "Kristian_43":
			dialog.text = "Превосходно. Пятнадцатого числа новая партия будет ждать вас, как всегда. Заходите.";
			link.l1 = "Обязательно зайду. До встречи.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Kristian_41";
			
			if (CheckAttribute(pchar, "questTemp.TPZ_UpgradeVino"))
			{
				RemoveDublonsFromPCharTotal(130);
				AddItems(pchar, "potionrum", 100);
				AddItems(pchar, "potionwine", 100);
			}
			else
			{
				RemoveDublonsFromPCharTotal(26);
				AddItems(pchar, "potionrum", 20);
				AddItems(pchar, "potionwine", 20);
			}
			
			DeleteAttribute(pchar, "questTemp.TPZ_TradeVinoAndRom");
			SetFunctionTimerCondition("TPZ_KristianReturn", 0, 0, 1, false); // таймер
			AddCharacterExpToSkill(pchar, "Commerce", 100);
			pchar.questTemp.TPZ_KritstianVinoAndRom = sti(pchar.questTemp.TPZ_KritstianVinoAndRom) + 1; // счётчик покупок
		break;
		
		case "UpgradeVino":
			dialog.text = "Капитан, увеличение объёма - дело разумеется приятное, но и затратное! Больше товара - значит больше рабочих рук, нужно расширить складские помещения, нанять судно повместительней... Без вложений я просто не смогу обеспечить нужное количество товара вовремя.";
			link.l1 = "И о какой сумме идёт речь? Сколько потребуется, чтобы всё это заработало как следует?";
			link.l1.go = "UpgradeVino_2";
		break;
		
		case "UpgradeVino_2":
			dialog.text = "Пятьдесят тысяч песо. Остальные расходы я возьму на себя.";
			link.l1 = "Пятьдесят тысяч? Хм... сумма значительная. Неужели нельзя сократить затраты?";
			link.l1.go = "UpgradeVino_3";
		break;
		
		case "UpgradeVino_3":
			dialog.text = "Увы, капитан, но тут не выйдет сэкономить. Если не сделать всё как требуется, всё может пойти... ну, скажем так, совсем не по плану. А мне, да и вам, полагаю, проблемы ни к чему.";
			if (sti(pchar.Money) >= 50000)
			{
				link.l1 = "Вот ваши деньги. Не разочаруйте меня, Кристиан.";
				link.l1.go = "UpgradeVino_5";
			}
			link.l2 = "Знаете, Кристиан, возможно, это не такая уж и хорошая затея. Мы вернёмся к этому разговору позже.";
			link.l2.go = "UpgradeVino_4";
		break;
		
		case "UpgradeVino_4":
			dialog.text = "Как скажете, капитан. Если передумаете - дайте мне знать.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Kristian_41";
			pchar.questTemp.TPZ_KritstianVinoBlock = true;
			pchar.questTemp.TPZ_KritstianVinoPotom = true;
		break;
		
		case "UpgradeVino_Agreed":
			dialog.text = "Капитан, это отличные новости! Вы готовы внести пятьдесят тысяч серебром прямо сейчас?";
			if (sti(pchar.Money) >= 50000)
			{
				link.l1 = "Вот ваши деньги. Не разочаруйте меня, Кристиан.";
				link.l1.go = "UpgradeVino_5";
			}
			link.l2 = "Прямо сейчас у меня нет нужной суммы. Я вернусь, когда у меня будет достаточно денег.";
			link.l2.go = "UpgradeVino_4";
		break;
		
		case "UpgradeVino_5":
			dialog.text = "Обещаю, "+pchar.name+" вы не пожалеете! Я немедленно займусь подготовкой. Уже со следующего завоза сможете получать по сто бутылок рома и столько же отличного вина - по сто тридцать дублонов за всю партию.";
			link.l1 = "Отлично. И не забывайте об осторожности. Ваша работа - это и моя репутация.";
			link.l1.go = "UpgradeVino_6";
			AddMoneyToCharacter(pchar, -50000);
		break;
		
		case "UpgradeVino_6":
			DialogExit();
			
			NextDiag.CurrentNode = "Kristian_41";
			pchar.questTemp.TPZ_UpgradeVino = true;
			pchar.questTemp.TPZ_KritstianVinoBlock = true;
			DeleteAttribute(pchar, "questTemp.TPZ_KritstianVinoPotom");
			AddQuestRecordInfo("Useful_Acquaintances", "4_1");
		break;
		
		
	}
}