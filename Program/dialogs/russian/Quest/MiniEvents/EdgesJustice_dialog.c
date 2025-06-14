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
		
		case "Naemnik":
			dialog.text = "Ты хорош"+GetSexPhrase("","а")+"... чертовски хорош"+GetSexPhrase("","а")+". Но прежде чем ты закончишь дело, выслушай меня. Уверен, то, что я скажу, тебя заинтересует.";
			link.l1 = "Пожалуй, ты можешь высказаться перед смертью. Но не обольщайся. Из этой пещеры тебе уже не выйти.";
			link.l1.go = "Naemnik_2";
		break;
		
		case "Naemnik_2":
			dialog.text = "Начальник порта, да? Это он отправил тебя за моей головой?";
			link.l1 = "Ты сама проницательность.";
			link.l1.go = "Naemnik_3";
		break;
		
		case "Naemnik_3":
			dialog.text = "Он ведь отправил тебя убить меня, верно? Не найти, не поймать, а именно убить?";
			link.l1 = "Верно. И что с того?";
			link.l1.go = "Naemnik_4";
		break;
		
		case "Naemnik_4":
			dialog.text = "Ох... ну ты и "+GetSexPhrase("болван","глупышка")+". Ты хоть раз задума"+GetSexPhrase("лся","лась")+", почему ему так важно, чтобы меня прикончили, а не просто кинули за решётку, а? Нет? Ты даже и близко не представляешь, кого ты сейчас пытаешься спасти. Этот портовый паук всё здесь окутал паутиной лжи, и ты, "+GetSexPhrase("парень","малышка")+", в ней крепко застрял"+GetSexPhrase("","а")+"\nДумаешь, он честный управитель? Ха, да честность ему разве что во сне снится! Он продаёт наводки пиратам и голландцам. Сдаёт тех, кто ему доверяет. Такой мрази, как он, место только в земле!";
			link.l1 = "Чей бы сапог грязи не месил! Ты ведь тоже на монаха не похож.";
			link.l1.go = "Naemnik_5";
		break;
		
		case "Naemnik_5":
			dialog.text = "Не похож, и не притворяюсь. Мой клинок - никогда не врёт. Достаточно одного взгляда - и человек понимает: смерть пришла за ним. Я не улыбаюсь жертве, не жму ей руку, зная, что она уже обречена. Нет. Мои намерения прозрачны. А этот чинуша\nОн предаёт всех, кто ему доверился, и делает это с таким видом, будто помогает им. Он хуже любого ублюдка, которого я когда-либо отправлял в могилу.";
			link.l1 = "Предположим, ты говоришь правду. Кто тебя нанял?";
			link.l1.go = "Naemnik_6";
		break;
		
		case "Naemnik_6":
			dialog.text = "Имя я тебе не назову - я его и сам не знаю. Но это тот, кто хлебнул горя из-за мерзавца. Человек, которому нужна справедливость... или месть. Называй, как хочешь, суть от этого не меняется. Пять сотен дублонов за голову гнилого чинуши! Помоги мне, и мы поделим эти деньги пополам.";
			link.l1 = "Хватит с меня твоей болтовни! Ты всё, что угодно скажешь, чтобы спасти свою жалкую шкуру. Высказаться я тебе дал"+GetSexPhrase("","а")+" - теперь пришло время умирать.";
			link.l1.go = "Naemnik_7";
			link.l2 = "Прекрасная история. Но тебе, приятель, я на слово верить не стану. У тебя есть, что-то, кроме твоих слов? Доказательства, свидетели? Или это просто очередная уловка, чтобы избежать смерти?";
			link.l2.go = "Naemnik_8";
		break;
		
		case "Naemnik_7":
			DialogExit();
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("GS_Naemnik");
			LAi_SetImmortal(sld, false);
			LAi_SetCurHPMax(sld);
			LAi_GetCharacterMaxEnergy(sld);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheckFunction("EnemyFight", "GS_UbivaemNaemnika");
		break;
		
		case "Naemnik_8":
			dialog.text = "Эти бумаги нашли в каюте пирата, которого мой заказчик одолел в бою. Он получал наводки от начальника порта. В записках чётко указаны маршруты судов, время их выхода в море и грузы, которые они перевозили. Маршруты совпадают с маршрутами тех, кто был ограблен, убит или исчез без следа\nА главное, почерк в записках точно такой же, как в документах на груз. Эти записки - ключ к его разоблачению. Мой заказчик хочет, чтобы они оказались на трупе. Ему мало обычного суда\nЭтот мерзавец слишком влиятелен и имеет много продажных дружков. Если бы дело дошло до суда, он бы выкрутился. Таким, как он, нет места среди живых. Смерть с позором - это всё, чего он заслуживает.";
			link.l1 = "Подлый ублюдок! Люди доверяют ему свои судьбы, а он продаёт их жизни пиратам! Я в деле. Для такого человека нет места на этой земле.";
			link.l1.go = "Naemnik_9";
			GiveItem2Character(PChar, "GS_letters");
			AddQuestRecordInfo("GS_Letters", "1");
		break;
		
		case "Naemnik_9":
			dialog.text = "У меня есть ключ от его дома - раздобыл через плотника, который чинил мебель в его особняке. Всё шло гладко, пока не оказалось, что он живёт там не один. Когда я пришёл, чтобы завершить дело, его жена была внутри\nЕё присутствие застало меня врасплох. За её шкуру мне никто доплачивать не стал бы, а власти уж точно проявили бы больший энтузиазм в поисках убийцы. Поэтому я изменил план и подстерёг его у управления.";
			link.l1 = "Дьявол. Весь город на ушах, просто пойти и убить его внаглую уже не получится. И что же делать?";
			link.l1.go = "Naemnik_10";
		break;
		
		case "Naemnik_10":
			dialog.text = "Я наблюдал за городом, ожидая, пока шум утихнет. После моего визита этот трусливый крысёныш решил спрятать свою благоверную. Я своими глазами видел, как она поднялась на борт корабля и покинула гавань\nТеперь он остался один - самое время закончить начатое. Ночью можно пробраться в его логово и прикрыть эту лавочку. А потом оставить записки на виду, чтобы каждый знал, какого сорта гнилью он является\nНо мне в город сейчас дорога заказана. А вот ты... тебе это под силу. Тебя не ждут, ты можешь без труда проскользнуть. Его дом возле городской тюрьмы. Пять сотен дублонов! Половина твоя, если доведёшь дело до конца.";
			link.l1 = "Хорошо. Я лично отправлю этого подонка на тот свет. Эти бумаги останутся в его доме - все должны узнать правду. Жди меня здесь. Я вернусь, как только дело будет сделано.";
			link.l1.go = "Naemnik_11";
		break;
		
		case "Naemnik_11":
			DialogExit();
			chrDisableReloadToLocation = false;
			locations[FindLocation("Beliz_Cave")].DisableEncounters = false;
			AddQuestRecord("GS", "5");
			AddQuestUserData("GS", "sSex", GetSexPhrase("","а"));
			
			sld = CharacterFromID("GS_Naemnik");
			LAi_SetWarriorType(sld);
			LAi_SetCurHPMax(sld);
			LAi_GetCharacterMaxEnergy(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PEACE);
			NextDiag.CurrentNode = "Naemnik_12";
			
			sld = &Locations[FindLocation("Beliz_town")];
			sld.reload.l11.open_for_night = 1;
			sld = &Locations[FindLocation("Beliz_houseS5_room2")];
			sld.locators_radius.item.button01 = 1.0;
			
			//pchar.quest.GS_SoldatyDoma.win_condition.l1 = "Hour";
			//pchar.quest.GS_SoldatyDoma.win_condition.l1.start.hour = 0.00;
			//pchar.quest.GS_SoldatyDoma.win_condition.l1.finish.hour = 5.00;
			PChar.quest.GS_SoldatyDoma.win_condition.l1 = "location";
			PChar.quest.GS_SoldatyDoma.win_condition.l1.location = "Beliz_houseS5";
			PChar.quest.GS_SoldatyDoma.function = "GS_SoldatyDoma";
		break;
		
		case "Naemnik_12":
			dialog.text = "Чего встал"+GetSexPhrase("","а")+", как вкопанн"+GetSexPhrase("ый","ая")+"?";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Naemnik_12";
		break;
		
		case "Portman_1":
			dialog.text = "Вы? Какого чёрта? Как вы сюда попали?";
			link.l1 = "Как я сюда попал"+GetSexPhrase("","а")+" - не имеет никакого значения. И я думаю, что в глубине души вы понимаете, зачем я приш"+GetSexPhrase("ёл","ла")+".";
			link.l1.go = "Portman_2";
			DelLandQuestMark(npchar);
		break;
		
		case "Portman_2":
			dialog.text = "Нет, не понимаю! Если вы за наградой, то приходите завтра в управление, я всё отдам.";
			link.l1 = "Хватит прикидываться невинным! Мне всё известно. Вы продавали пиратам наводки на суда ваших клиентов. Столь гнусный человек не заслуживает права занимать такие должности. Более того, вы не заслуживаете жить среди честных людей. Сэр, ваше место среди себе подобных - в аду.";
			link.l1.go = "Portman_3";
		break;
		
		case "Portman_3":
			dialog.text = "О, нет-нет-нет! Нет! Вы всё не так поняли! О-они заставили меня... Они пришли ко мне и угрожали расправиться с моей семьёй, если я не стану им помогать... вы не понимаете...";
			link.l1 = "Хватит с меня ваших жалких оправданий! У меня на руках ваши записки, где вы требуете свой процент за наводки! Ваше лицемерие отвратительно, и я больше не намерен"+GetSexPhrase("","а")+" это терпеть. Доставайте оружие и защищайтесь, если у вас хватит на это смелости!";
			link.l1.go = "Portman_4";
		break;
		
		case "Portman_4":
			DialogExit();
			LAi_LocationFightDisable(loadedLocation, false);
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("Beliz_portman_clone");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheckFunction("EnemyFight", "GS_PortmanDead");
		break;
		
		case "Naemnik_21":
			dialog.text = "Ну, какие новости? Дело сделано?";
			link.l1 = "А ты сомневался? Он изо всех сил пытался выдавить из себя хоть какое-то оправдание, но это ему не помогло. Записки я оставил"+GetSexPhrase("","а")+" на видном месте, как и договаривались.";
			link.l1.go = "Naemnik_22";
		break;
		
		case "Naemnik_22":
			dialog.text = "Жалкие слизняки вроде него всегда думают, что смогут откупиться от правосудия дешёвым враньём и деньгами.";
			link.l1 = "Ну, теперь он уже ни о чём не думает. Давай сюда мои деньги, и я пойду.";
			link.l1.go = "Naemnik_23";
		break;
		
		case "Naemnik_23":
			dialog.text = "Вот твои дублоны. Отличная работа, должен признать. Но знаешь, будь у меня тогда в руках что-то более серьёзное, всё могло бы пойти по-другому... для тебя. В тесных стенах дома особо не размахнёшься, так что я взял эту жалкую зубочистку, рассчитывая быстро провернуть дело\nЗнай я, как всё развернётся, взял бы инструмент посолиднее.";
			link.l1 = "Ха-ха. А наш бедолага говорил, что ты вооружён как сам Роланд перед Ронсевальским ущельем!";
			link.l1.go = "Naemnik_24";
			AddItems(pchar, "gold_dublon", 250);
		break;
		
		case "Naemnik_24":
			dialog.text = "Хех. Ну, у страха глаза велики. Сам"+GetSexPhrase("","а")+" видишь, с какой вилкой я едва твоё сердце не пощупал.";
			link.l1 = "Хочешь сказать, что будь у тебя железка потяжелее, ты бы смог составить мне конкуренцию?";
			link.l1.go = "Naemnik_25";
		break;
		
		case "Naemnik_25":
			dialog.text = "Во владении оружием среднего веса я мастер - это уж факт. Не веришь? Так уж и быть, поделюсь с тобой парой хитростей, которые не раз выручали меня. Слушай внимательно - это не просто слова, а то, что однажды может спасти твою шкуру. Такие секреты кому попало не рассказывают.";
			link.l1 = "...";
			link.l1.go = "Naemnik_26";
		break;
		
		case "Naemnik_26":
			DialogExit();
			
			SetLaunchFrameFormParam("Прошёл час...", "Run_Function", 0, 4.0);
			SetLaunchFrameRunFunctionParam("GS_Spravedlivost_2", 0.0);
			LaunchFrameForm();
		break;
		
		case "Naemnik_27":
			dialog.text = "...";
			link.l1 = "Вижу, ты и впрямь разбираешься в своём ремесле. Спасибо за науку. Но если это всё, то мне пора.";
			link.l1.go = "Naemnik_28";
			AddComplexSelfExpToScill(0, 750, 0, 0);
		break;
		
		case "Naemnik_28":
			dialog.text = "Бывай, "+GetSexPhrase("кэп","милашка")+". Надеюсь, мы больше не встретимся в бою. Жаль будет тебя убивать. Ха-ха.";
			link.l1 = "У тебя не будет ни единого шанса, даже если я буду пьян"+GetSexPhrase("ый","ая")+" и на одной ноге, хех! Ну, прощай, наёмник.";
			link.l1.go = "Naemnik_29";
		break;
		
		case "Naemnik_29":
			DialogExit();
			chrDisableReloadToLocation = false;
			locations[FindLocation("Beliz_Cave")].DisableEncounters = false;
			LAi_SetPlayerType(pchar);
			
			LAi_SetWarriorType(npchar);
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PEACE);
			
			AddQuestRecord("GS", "7");
			CloseQuestHeader("GS");
			
			AddSimpleRumourCity("Говорят, начальника порта нашли мёртвым прямо у себя в доме. При нём обнаружены записки, доказывающие его причастность к исчезновению кораблей. Подумать только, какой позор для нашего города...", "Beliz", 30, 1, "");
			AddSimpleRumourCity("Вы уже слышали? Кто-то пробрался в дом начальника порта, перебил охрану и прикончил его. На трупе нашли записки с маршрутами пропавших кораблей - написанные им самим! Слуга короны, а на деле - предатель! Получил по заслугам! И куда только смотрел губернатор все эти годы?", "Beliz", 30, 1, "");
			AddSimpleRumourCity("Начальник порта убит! Прямо в своём доме! Охрана перебита, а среди его вещей - записки с маршрутами пропавших кораблей. Тут и думать нечего, исчезновения - его рук дело! Что ж, негодяя настигла справедливая судьба.", "Beliz", 30, 1, "");
		break;
		
		
		
		
		
		
	}
}