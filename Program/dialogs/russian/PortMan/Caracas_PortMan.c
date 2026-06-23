// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Какие вопросы?", "Что вам угодно, " + GetAddress_Form(NPChar) + "?"), "Совсем недавно вы пытались задать мне вопрос " + GetAddress_Form(NPChar) + "...", "В течение этого дня вы уже третий раз говорите о каком-то вопросе...",
                          "Послушайте, если вы не по делам порта, то не стоит меня вопросами донимать.", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Я передумал"+ GetSexPhrase("","а") +"...", "Сейчас мне не о чем говорить."), "Хм, что-то с памятью моей стало...",
                      "Да уж, действительно в третий раз...", "Извините, но портовые дела меня сейчас не интересуют.", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			
			// belamour legengary edition на пару с Акулой -->
			if(CheckAttribute(pchar,"questTemp.SharkGoldFleet"))
			{
				if(pchar.questTemp.SharkGoldFleet == "toCarPortOffice" || pchar.questTemp.SharkGoldFleet == "start" || pchar.questTemp.SharkGoldFleet == "afterGvik" || pchar.questTemp.SharkGoldFleet == "buyincar")
				{
					link.l1 = "Дело в том, что я со дня на день собираюсь идти в Порто-Белло с грузом товара, приобретённого у вас в колонии. Подумал: вдруг у вас есть какой-нибудь фрахт или дело, которое я могу выполнить по пути... За определённую плату, разумеется.";
					link.l1.go = "SharkGoldFleet";
				}
				if(pchar.questTemp.SharkGoldFleet == "LightVar")
				{
					if(!bImCasual) pchar.quest.SharkGoldFleetToCPO10.over = "yes";
					link.l1 = "И снова здравствуйте. Я передал ваше письмо в Порто-Белло. Там меня попросили передать вам ответ.";
					link.l1.go = "SharkGoldFleet_09";
				}
				if(pchar.questTemp.SharkGoldFleet == "DifficultVar")
				{
					if(!bImCasual) pchar.quest.SharkGoldFleetToCPO10.over = "yes";
					link.l1 = "Здравствуйте. Я пришёл к вам из Порто-Белло. Ваш коллега из местного портового управления попросил меня передать вам вот это письмо.";
					link.l1.go = "SharkGoldFleet_13";
				}
			}
			//<-- на пару с Акулой
		break;
		
		// belamour на пару с Акулой -->
		case "SharkGoldFleet":
			if(CheckAttribute(pchar,"questTemp.SharkGoldFleet.Fail21"))
			{
				pchar.questTemp.SharkGoldFleet = "toCurierDie";
				AddQuestRecord("SharkGoldFleet", "5");
				SGF_CreateCurierInWorld("");
				dialog.text = "Благодарю за беспокойство, но никаких таких дел у меня нет. На самом деле было одно поручение, но вы опоздали буквально на пару дней: я отправил скоростной курьерский люггер для этой цели.";
				link.l1 = "Понимаю... Что ж, и на том спасибо.";
				link.l1.go = "exit";
			}
			else
			{
				if(!bImCasual) pchar.quest.SharkGoldFleet21.over = "yes"; 
				if(!bImCasual) pchar.quest.SharkGoldFleet30.over = "yes"; 
				if(GetCompanionQuantity(pchar) > 1)
				{
					pchar.questTemp.SharkGoldFleet = "toCurierWait";
					AddQuestRecord("SharkGoldFleet", "10");
					SetFunctionTimerCondition("SGF_CreateCurierInWorld", 0, 0, 1+rand(2), false);
					dialog.text = "Я смотрю, у вас даже не один корабль. Вы, должно быть, богатый торговец. Хм... Но я всех местных торговцев с эскадрами знаю в лицо, а вот вас - нет. Так что не обессудьте, но не могу вам ничего серьёзного доверить.";
					link.l1 = "Понимаю... Что ж, и на том спасибо.";
					link.l1.go = "exit";
				}
				else
				{
					if(int(RealShips[int(pchar.ship.type)].basetype) != SHIP_FRIGATE_L)
					{
						pchar.questTemp.SharkGoldFleet = "toCurierWait";
						AddQuestRecord("SharkGoldFleet", "11");
						SetFunctionTimerCondition("SGF_CreateCurierInWorld", 0, 0, 1+rand(2), false);
						dialog.text = "Хм... Задание-то у меня есть. Только вот судно ваше не подходит. Мне нужен одновременно быстрый и мощный корабль, а ваш не до конца отвечает этим требованиям. По крайней мере, одновременно. Так что прошу простить.";
						link.l1 = "Понимаю... Что ж, и на том спасибо.";
						link.l1.go = "exit";
					}
					else
					{
						if(!CheckAttribute(pchar,"questTemp.SharkGoldFleet.LicenceOk"))
						{
							pchar.questTemp.SharkGoldFleet = "toCurierWait";
							AddQuestRecord("SharkGoldFleet", "12");
							SetFunctionTimerCondition("SGF_CreateCurierInWorld", 0, 0, 1+rand(2), false);
							dialog.text = "Дело-то у меня есть... И корабль у вас хороший. Только вот на торговый не похож. Да и долгосрочной лицензии Голландской Вест-Индской Компании у вас, как я погляжу, нет. Не обижайтесь, но вы не производите впечатление торговца. Я не могу так рисковать.";
							link.l1 = "Понимаю... Что ж, и на том спасибо.";
							link.l1.go = "exit";
						}
						else
						{
							if(pchar.questTemp.SharkGoldFleet != "toCarPortOffice" || GetSquadronGoods(pchar, GOOD_COFFEE) < 300 || GetSquadronGoods(pchar, GOOD_CHOCOLATE) < 300)
							{
								pchar.questTemp.SharkGoldFleet = "toCurierWait";
								AddQuestRecord("SharkGoldFleet", "13");
								SetFunctionTimerCondition("SGF_CreateCurierInWorld", 0, 0, 1+rand(2), false);
								dialog.text = "Дело-то у меня есть... И корабль у вас хороший. Только вот не понимаю, чем вы торговать собрались... Вы сказали, что собираетесь в Порто-Белло, чтобы товар продать, но, насколько я знаю, вы его у нас в колонии особо и не приобрели. Не обижайтесь, но вы не производите впечатление торговца. Я не могу так рисковать.";
								link.l1 = "Понимаю... Что ж, и на том спасибо.";
								link.l1.go = "exit";
							}
							else
							{
								dialog.text = "Дело-то у меня есть. Я вас, конечно, не знаю... Но, сказать по правде, я только торговцев с эскадрами в лицо помню. Остальных - нет. Да и лицензия у вас долгосрочная, сразу видно опытного купца. Корабль у вас, однако, интересный. Зачем вам торговать на фрегате?";
								link.l1 = "Хах, это не простой фрегат. Он может развивать очень высокую скорость даже с набитым битком трюмом. Всегда проще уйти от пиратов, чем сражаться с ними, разве нет? Пусть вместительность у моего судна и поменьше, чем у обычных торговых кораблей, зато и риск гораздо ниже.";
								link.l1.go = "SharkGoldFleet_01";
							}
						}
						
					}
					
				}
			}
		break;
		
		case "SharkGoldFleet_01":
			dialog.text = "Хм, а ведь ваша правда! Испанцы умеют строить корабли, не так ли? Да-да, я сразу увидел, что этот красавец сошёл со стапелей наших верфей. И да, мне действительно уже рассказали сегодня, что вы купили у нашего торговца партию кофе и какао для последующей перепродажи в Порто-Белло. Выгодная сделка, я вам скажу. Люди, незнакомые с торговлей, не знают, что здесь эти товары, благодаря плантациям, дешёвые, а в Порто-Белло на них большой спрос, поскольку оттуда они уходят в метрополию.";
			link.l1 = "Ну так на то и расчёт, сеньор. Ради нескольких песо я бы не стал так далеко гонять своё судно.";
			link.l1.go = "SharkGoldFleet_02";
		break;
		
		case "SharkGoldFleet_02":
			dialog.text = "Ну что ж, сказать по правде, у меня действительно есть для вас дело. И очень хорошо, что у вас такой быстрый корабль, который ещё и отпор может дать в случае чего.";
			link.l1 = "Подождите, сеньор... Ваше дело предполагает, что мне придётся сражаться?..";
			link.l1.go = "SharkGoldFleet_03";
		break;
		
		case "SharkGoldFleet_03":
			dialog.text = "Нет-нет, что вы! На самом деле задание у меня максимально простое. Мне нужно, чтобы вы передали одно письмо начальнику портового управления в Порто-Белло. Письмо запечатанное, вскрывать нельзя. Рассказывать о нём тоже никому не надо, корреспонденция... личная. Передать лично в руки. Срок - десять суток. Потом уже будет неактуально.";
			link.l1 = "Так просто? И сколько я за это получу?";
			link.l1.go = "SharkGoldFleet_04";
		break;
		
		case "SharkGoldFleet_04":
			dialog.text = "Пять тысяч песо. Считайте, это за то, что мне не придётся посылать в Порто-Белло курьерский люггер.";
			link.l1 = "А к чему были ваши расспросы обо мне и моём корабле?";
			link.l1.go = "SharkGoldFleet_05";
		break;
		
		case "SharkGoldFleet_05":
			dialog.text = "Да не берите в голову. Просто корреспонденция достаточно важная, и я должен быть уверен, что она достигнет адресата. А так ничего особенного. Бюрократия... Для обычного человека эти документы интереса не представляют.";
			link.l1 = "Ну что ж, я согласен. Давайте сюда ваши документы. Как только прибуду в Порто-Белло, занесу их вашему коллеге. За десять дней управлюсь, не переживайте.";
			link.l1.go = "SharkGoldFleet_06";
		break;
		
		case "SharkGoldFleet_06":
			dialog.text = "Одну секундочку. Прошу прощения, я совсем забыл ваше имя. Можете его сказать, пожалуйста? Мне нужно записать это в документах.";
			link.l1 = "Меня зовут Андреас Гарсия.";
			link.l1.go = "SharkGoldFleet_07";
		break;
		
		case "SharkGoldFleet_07":
			dialog.text = "Спасибо. Так... Отлично. Помните, что доставить этот документ должны именно вы и непосредственно в руки адресату. Вот, держите. Награду вам выдаст начальник портового управления в Порто-Белло. Удачного пути!";
			link.l1 = "Благодарю вас! А теперь разрешите откланяться.";
			link.l1.go = "SharkGoldFleet_08";
		break;
		
		case "SharkGoldFleet_08":
			DialogExit();
			if(!bImCasual) SetFunctionTimerCondition("SharkGoldFleetToPB10", 0, 0, 10, false);
			else NewGameTip("Режим исследования: таймер отключён.");
			AddCharacterSkillDontClearExp(pchar, SKILL_LEADERSHIP, 1);
			AddCharacterSkillDontClearExp(pchar, SKILL_SNEAK, 1);
			TakeNItems(pchar, "letter_1", 1);
			ChangeItemDescribe("letter_1", "itmdescr_letter_SharkGoldFleet_1");
			AddQuestRecord("SharkGoldFleet", "14");
			pchar.questTemp.SharkGoldFleet = "toPBPortOffice";
		break;
		
		case "SharkGoldFleet_09":
			RemoveItems(PChar, "letter_2", 1);
			ChangeItemDescribe("letter_2", "itmdescr_letter_2");
			dialog.text = "Отлично! Вы мне очень помогли. Никаких сложностей не возникло?";
			link.l1 = "Нет, сложностей не было. Правда ваш коллега ругался на вас: сказал, что вы тут все скряги, потому что посылаете не курьерское судно, а попутных торговцев, да ещё оплату вешаете на получателя. Грозился, что напишет жалобу в Гавану...";
			link.l1.go = "SharkGoldFleet_10";
		break;
		
		case "SharkGoldFleet_10":
			dialog.text = "Что?! Это я-то скряга?! Да что он там о себе возомнил? Во-первых, держите ваши пять... нет, шесть тысяч песо! Я плачу честно!";
			link.l1 = "Благодарю вас. Приятно видеть, что ваш коллега ошибался в своём мнении о вас.";
			link.l1.go = "SharkGoldFleet_11";
		break;
		
		case "SharkGoldFleet_11":
			AddMoneyToCharacter(pchar, 6000);
			dialog.text = "А во-вторых, этот негодяй, похоже, забыл, как два месяца тому назад повесил на меня все расходы на содержание торгового судна, которое шло из Каракаса в Порто-Белло, а оттуда - в Гавану! А мы договаривались, что вторую часть пути оплатит он! И долг он так и не вернул, а обещал, что ещё в прошлом месяце всё погасит! И это я ещё скряга... Да я сам напишу на него жалобу в Гавану!";
			link.l1 = "Ну у вас и страсти Мадридского двора, конечно...";
			link.l1.go = "SharkGoldFleet_12";
		break;
		
		case "SharkGoldFleet_12":
			AddQuestRecord("SharkGoldFleet", "20");
			AddQuestUserData("SharkGoldFleet", "date", pchar.questTemp.SharkGoldFleet.Date)
			pchar.questTemp.SharkGoldFleet = "LightVarToShark";
			SetFunctionLocationCondition("SharkGoldFleetToShark", "Curacao", false);
			dialog.text = "Нет, вы только подумайте... Каков нахал! Ладно, я с ним ещё разберусь... А сейчас попрошу извинить: меня ждут неотложные дела. Приятно было иметь с вами дело!";
			link.l1 = "И вам всего хорошего!";
			link.l1.go = "exit";
		break;
		
		case "SharkGoldFleet_13":
			RemoveItems(PChar, "letter_2", 1);
			ChangeItemDescribe("letter_2", "itmdescr_letter_2");
			dialog.text = "Отлично! Вы мне очень помогли. Хотя, я к ним посылал курьерский люггер, а они мне ответ вернули с попутным кораблём. Да уж... И после этого они ещё жалуются, что это у нас тут скряги сидят.";
			link.l1 = "Ну, может быть денег на курьера пожалели...";
			link.l1.go = "SharkGoldFleet_14";
		break;
		
		case "SharkGoldFleet_14":
			AddMoneyToCharacter(pchar, 5000);
			AddQuestRecord("SharkGoldFleet", "20");
			AddQuestUserData("SharkGoldFleet", "date", pchar.questTemp.SharkGoldFleet.Date)
			pchar.questTemp.SharkGoldFleet = "DifficultVarToShark";
			SetFunctionLocationCondition("SharkGoldFleetToShark", "Curacao", false);
			dialog.text = "Не 'может быть', а точно, говорю вам! Ладно, это не важно. Вот, возьмите за ваши труды. А сейчас у меня много работы, прошу извинить.";
			link.l1 = "Ну, может быть денег на курьера пожалели...";
			link.l1.go = "exit";
		break;
		// <-- на пару с Акулой
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}


