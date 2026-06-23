// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Спрашивай, чего ты хочешь?",
                          "Мы только что поднимали эту тему. Вы, вероятно, запамятовали...", "Сегодня вы уже третий раз говорите о каком-то вопросе...",
                          "Послушай, это магазин, здесь люди покупают что-то. Не отвлекай меня!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Знаешь, " + NPChar.name + ", как-нибудь в следующий раз.", "Точно, "+ GetSexPhrase("забыл","забыла") +" что-то...",
                      "Да уж, действительно в третий раз...", "Гм, не буду...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			
			//Jason --> ----------------------------------мини-квест Бесчестный конкурент------------------------------------
			if (CheckAttribute(pchar, "questTemp.Shadowtrader"))
			{
				if(pchar.questTemp.Shadowtrader == "begin" && GetNpcQuestPastDayParam(npchar, "Shadowtrader_date") < 5 && NPChar.location == pchar.questTemp.Shadowtrader.City + "_store")
				{
					dialog.text = "Спасибо, капитан, что выполнили мою просьбу. Теперь, когда "+pchar.questTemp.Shadowtrader.Guardername+" здесь, я могу чувствовать себя хоть немного спокойнее.";
					link.l1 = "Хм... Не сочтите за навязчивость, но мне кажется, что у вас какие-то проблемы. Может, расскажете - а вдруг я смогу вам помочь?"; 
					link.l1.go = "Shadowtrader_fort";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Shadowtrader.Trouble") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_store")
				{
					dialog.text = "Ну как? Вы передали моё письмо?";
					link.l1 = "Да, передал"+GetSexPhrase("","а")+". Комендант попросил передать ответ на словах - того, что написано в вашем письме недостаточно, чтобы городская стража предприняла какие-либо действия."; 
					link.l1.go = "Shadowtrader_trouble";
					pchar.quest.ShadowtraderTimeFort_Over.over = "yes";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Shadowtrader.End.Fort") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_store" && CheckAttribute(pchar, "questTemp.Shadowtrader.EndFort"))
				{
					dialog.text = "Я уже слышал новость - сегодня ночью стража нашла подпольную торговую точку контрабандистов и всех арестовала. Заправлял всем этим один редкостный мерзавец. Ничего, теперь он долго никому не сможет пакостить\nКомендант рассказал мне о вашей роли в этом предприятии - спасибо вам огромное! Вы выполнили своё обещание! Вот, возьмите награду - 15 000 песо. Вы просто спасли меня! Теперь я займусь торговлей по-настоящему!";
					link.l1 = "Да не за что. Это было нетрудно."; 
					link.l1.go = "Shadowtrader_complete";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Shadowtrader.End.Escape") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_store")
				{
					dialog.text = "Ну, что расскажете хорошего, " + pchar.name + "?";
					link.l1 = "Я разыскал"+GetSexPhrase("","а")+" вашего конкурента. Больше он не будет вам докучать - мне удалось... убедить его покинуть этот остров. Его 'магазин' находился в доме у городских ворот - что делать с брошенным товаром, решайте сами. Хотите - сдайте властям, хотите - попробуйте забрать себе."; 
					link.l1.go = "Shadowtrader_Escape_complete";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Shadowtrader.End.Free") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_store")
				{
					dialog.text = "Я уже слышал новость - сегодня ночью стража обнаружила в одном из домов подпольную торговую точку контрабандистов. Два негодяя найдены мертвыми. Великолепная работа, " + pchar.name + ", я восхищаюсь вами! Вот, возьмите награду - 15 000 песо. Вы просто спасли меня! Теперь я займусь торговлей по-настоящему!\nУдовлетворите моё любопытство - их главный... тоже, среди этих двух мертвецов?";
					link.l1 = "Нет. Но он уже никогда не посмеет даже появиться в вашем городе. Думаю, сейчас он уже на расстоянии нескольких десятков миль от этого острова."; 
					link.l1.go = "Shadowtrader_complete";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Shadowtrader.End.Kill") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_store")
				{
					dialog.text = "Я уже слышал новость - сегодня ночью стража обнаружила в одном из домов подпольную торговую точку контрабандистов. Три негодяя найдены мертвыми. Великолепная работа, " + pchar.name + ", я восхищаюсь вами! Вот, возьмите награду - 15 000 песо. Вы просто спасли меня! Теперь я займусь торговлей по-настоящему!\nУдовлетворите моё любопытство - их главный... тоже, среди этих трёх мертвецов?";
					link.l1 = "Да. Вы навсегда избавлены от вашего конкурента. Более он вас не побеспокоит."; 
					link.l1.go = "Shadowtrader_complete";
					break;
				}
			}
			//<-- мини-квест Бесчестный конкурент
		break;
		
		// --> мини-квест Бесчестный конкурент
		case "Shadowtrader_begin":
			pchar.questTemp.Shadowtrader = "true";
			pchar.questTemp.Shadowtrader_Block = true;
			pchar.questTemp.Shadowtrader.Guardername = GenerateRandomName_Generator(int(npchar.nation), "man");
			dialog.text = "Не могли бы вы сходить в таверну, найти там человека по имени "+pchar.questTemp.Shadowtrader.Guardername+" и сказать, чтобы он побыстрее явился ко мне? Я ни на минуту не могу отлучиться из магазина, а этот болван сидит в таверне, хлещет ром и, конечно, не догадается прийти сюда сам, хотя уже находится у меня на службе.";
			link.l1 = "Всегда рад"+GetSexPhrase("","а")+" помочь, дружище. Тем более, что я и сам"+GetSexPhrase("","а")+" собирал"+GetSexPhrase("ся","ась")+" в таверну заглянуть.";
			link.l1.go = "Shadowtrader_begin_1";
			link.l2 = "Ты что, смеёшься? Я похож"+GetSexPhrase("","а")+" на "+GetSexPhrase("мальчика","девочку")+" на побегушках? Тут до таверны два шага, сам дойдёшь, не рассыпешься.";
			link.l2.go = "exit";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("BasTer");
		break;
		
		case "Shadowtrader_begin_1":
			dialog.text = "Спасибо! Скажите ему, чтобы шёл сюда немедленно. Ох, да за что же мне такое наказание...";
			link.l1 = "Не переживайте. Сейчас я его к вам отправлю.";
			link.l1.go = "exit";
			pchar.questTemp.Shadowtrader.City = npchar.City;
			pchar.questTemp.Shadowtrader.nation = int(npchar.nation);
			//создаем охранника
			sld = GetCharacter(NPC_GenerateCharacter("ShadowGuarder" , "officer_7", "man", "man", 10, int(npchar.nation), 5, true, "quest"));
			FantomMakeCoolFighter(sld, 20, 50, 50, "topor_2", "pistol3", "bullet", 50);
			sld.name = pchar.questTemp.Shadowtrader.Guardername;
			sld.lastname = "";
			sld.dialog.FileName = "Quest\LineMiniQuests\ShadowTrader.c";
			sld.dialog.currentnode = "ShadowGuarder";
			sld.greeting = "pirat_common";
			LAi_SetSitType(sld);
			LAi_SetImmortal(sld, true);
			FreeSitLocator(pchar.questTemp.Shadowtrader.City + "_tavern", "sit_front1");
			ChangeCharacterAddressGroup(sld, pchar.questTemp.Shadowtrader.City + "_tavern", "sit", "sit_front1");
			SaveCurrentNpcQuestDateParam(npchar, "Shadowtrader_date");
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "Shadowtrader_fort":
			dialog.text = "Помочь? Ах, капитан, мне действительно нужна ваша помощь. Не могли бы ли вы отнести вот это письмо коменданту как можно быстрее? Я заплачу вам за это пустяковое дело 300 монет - как я уже говорил, я не могу отлучится из магазина.";
			link.l1 = "Да без проблем. Давайте сюда ваше письмо.";
			link.l1.go = "Shadowtrader_fort_1";
			link.l2 = "Нет, уважаемый, у меня больше нет времени на подобную ерунду.";
			link.l2.go = "Shadowtrader_fort_end";
			DelLandQuestMark(npchar);
		break;
		
		case "Shadowtrader_fort_1":
			dialog.text = "Вот, держите. Постарайтесь передать его до конца сегодняшнего дня и доставить мне ответ!";
			link.l1 = "Не переживайте, всё сделаю в лучшем виде.";
			link.l1.go = "exit";
			GiveItem2Character(pchar, "letter_1");
			ChangeItemDescribe("letter_1", "itmdescr_letter_1"); // 240912
			pchar.questTemp.Shadowtrader.Tradername = GetFullName(npchar);
			SetFunctionTimerCondition("ShadowtraderTimeFort_Over", 0, 0, 1, false);
			pchar.questTemp.Shadowtrader = "current"
			pchar.questTemp.Shadowtrader.Fort = "true";
			AddQuestRecord("Shadowtrader", "1");
			AddQuestUserData("Shadowtrader", "sCity", XI_ConvertString("Colony"+pchar.questTemp.Shadowtrader.City+"Gen"));
			AddLandQuestMarkToPhantom("baster_prison", "basterJailOff");
		break;
		
		case "Shadowtrader_fort_end":
			dialog.text = "Что же, придётся попросить кого-то другого. Извините, что отвлек вас от дел, капитан.";
			link.l1 = "Да ничего. До свидания!";
			link.l1.go = "exit";
			pchar.questTemp.Shadowtrader = "true";
			DeleteAttribute(pchar, "questTemp.Shadowtrader_Block");
		break;
		
		case "Shadowtrader_trouble":
			dialog.text = "Он так и сказал? Да какие же ещё ему нужны доказательства?! Мой труп? Ну так скоро он их точно получит, если все продолжится и дальше!..";
			link.l1 = "Тише, тише, " + npchar.name + ", успокойтесь, а то так и впрямь до апоплексического удара недалеко. Выпейте воды... Расскажите мне наконец, что у вас за неприятности - может, я смогу вам помочь?";
			link.l1.go = "Shadowtrader_trouble_1";
			DeleteAttribute(pchar, "questTemp.Shadowtrader.Trouble");
			DelLandQuestMark(npchar);
		break;
		
		case "Shadowtrader_trouble_1":
			dialog.text = "Ах, капитан! Да, возьмите ваши 300 песо, я чуть не забыл от расстройства... Я расскажу вам, конечно, правда, не понимаю, чем вы сможете мне помочь. Мой бизнес на грани краха, и всё из-за проклятых контрабандистов и неведомого мерзавца, который ими руководит.";
			link.l1 = "Контрабандисты?";
			link.l1.go = "Shadowtrader_trouble_2";
			AddMoneyToCharacter(pchar, 300);
		break;
		
		case "Shadowtrader_trouble_2":
			dialog.text = "Именно! Эти негодяи явно решили выжить меня из города! До поры все было как обычно - они перепродавали запрещенный товар, патруль их отлавливал, если удавалось, они прятались и откупались. Но с недавнего времени они открыли где-то в городе подпольную лавочку, и стали торговать самым ходовым товаром по невероятно низким ценам!\nЯ не могу позволить себе такой роскоши - мне ведь нужно платить подати - и постепенно разоряюсь: моряки ко мне уже практически не заходят за товарами - все покупают у этих проходимцев.";
			link.l1 = "Но вы должны были в таком случае обратиться к властям! Это их обязанность - пресекать подобные беззакония.";
			link.l1.go = "Shadowtrader_trouble_3";
		break;
		
		case "Shadowtrader_trouble_3":
			dialog.text = "Результат последнего обращения вы видели сами. Губернатор слишком занят, а комендант не верит, что контрабандисты организовали подпольный магазин, или делает вид, что не верит - я уже допускаю и такое\nКонечно, зачем им этим заниматься? А я скажу: я уверен, что всё это придумал какой-то проходимец, желающий разорить меня и вытеснить из города, а потом он спокойно приберет мой бизнес к своим грязным ручонкам.";
			link.l1 = "Хм... ваше предположение небезосновательно. Это очень похоже на торгашей - таскать каштаны из огня чужими руками... ой, простите, вас я, конечно, не имел"+GetSexPhrase("","а")+" в виду.";
			link.l1.go = "Shadowtrader_trouble_4";
		break;
		
		case "Shadowtrader_trouble_4":
			dialog.text = "Да ничего... А недавно ко мне пришёл какой-то оборванец, который нагло заявил, что если я буду и дальше поднимать шум, то они сожгут мой магазин\nВот я и нанял охранника. "+pchar.questTemp.Shadowtrader.Guardername+" обошёлся мне недёшево, но он профессионал, и я могу под его защитой чувствовать себя хоть немного спокойнее.";
			link.l1 = "Да уж... Неприятная история. Похоже, вы были правы - я ничем не могу вам помочь. Но я уверен"+GetSexPhrase("","а")+", что всё образуется - подобные чёрные лавочки обычно долго не существуют. До свидания.";
			link.l1.go = "Shadowtrader_end";
			link.l2 = "Понятно. Послушайте, я могу попробовать вам помочь...";
			link.l2.go = "Shadowtrader_trouble_5";
		break;
		
		case "Shadowtrader_trouble_5":
			dialog.text = "Вы всё-таки хотите предложить мне помощь? Но что вы предпримете?";
			link.l1 = "Я попытаюсь найти этого вашего 'коллегу' и... попробую убедить его не мешать вам жить. У меня иногда это неплохо получается - убеждать людей.";
			link.l1.go = "Shadowtrader_trouble_6";
		break;
		
		case "Shadowtrader_trouble_6":
			dialog.text = "Вы серьёзно? Да благословит вас Господь на правое дело! Если вы избавите меня от этой пакости - обещаю, в долгу не останусь и щедро отплачу.";
			link.l1 = "Ну что же, считайте, что мы договорились. Я приступаю к поискам.";
			link.l1.go = "exit";
			pchar.questTemp.Shadowtrader.seeksmugglers = "true";
			AddLandQuestMark(characterFromId("BasTer_Smuggler"), "questmarkmain");
			AddQuestRecord("Shadowtrader", "2");
			AddQuestUserData("Shadowtrader", "sCity", XI_ConvertString("Colony"+pchar.questTemp.Shadowtrader.City+"Gen"));
			AddQuestUserData("Shadowtrader", "sSex1", GetSexPhrase("ся","ась"));
		break;
		
		case "Shadowtrader_end":
			pchar.questTemp.Shadowtrader = "true";
			CloseQuestHeader("Shadowtrader");
			DeleteAttribute(pchar, "questTemp.Shadowtrader_Block");
			DialogExit();
		break;
		
		case "Shadowtrader_Escape_complete":
			dialog.text = "Это правда? Неужели я теперь смогу торговать спокойно? Спасибо вам огромное! Вот ваше вознаграждение - 15 000 песо. А товар в их доме лучше всего будет сдать коменданту. Ещё раз спасибо!";
			link.l1 = "Да не за что. Это было нетрудно. Я же говорил"+GetSexPhrase("","а")+" вам - у меня есть дар убеждения.";
			link.l1.go = "Shadowtrader_complete";
		break;
		
		case "Shadowtrader_complete":
			dialog.text = "Заходите ко мне почаще, капитан - я всегда буду рад вас видеть.";
			link.l1 = "Всенепременно! А теперь позвольте откланяться - дела! Всего доброго и успехов в торговле, " + npchar.name + "!";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Shadowtrader.End");
			AddMoneyToCharacter(pchar, 15000);
			pchar.questTemp.Shadowtrader = "complete";
			AddQuestRecord("Shadowtrader", "11");
			AddQuestUserData("Shadowtrader", "sSex", GetSexPhrase("","а"));
			CloseQuestHeader("Shadowtrader");
			DeleteAttribute(pchar, "questTemp.Shadowtrader_Block");
			DeleteAttribute(pchar, "questTemp.Shadowtrader.EndFort");
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("BasTer");
		break;
		//<-- мини-квест Бесчестный конкурент
	}
	UnloadSegment(NPChar.FileDialog2);
}

