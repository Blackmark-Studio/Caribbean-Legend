void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag, arTmp;
	int i, n;
	string sTemp, sStr;
	
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
		
		// Квест "Путеводная звезда"
		// Этап 0, ПРОЛОГ
		case "PZ_Alonso_1":
			dialog.text = "Прошу прощения, что навязался к вам в каюту, сеньор капитан, но это очень важно.";
			link.l1 = "Ох, надеюсь, Алонсо. Потому что если каждый из ребят будет заходить ко мне в каюту, как к себе домой, то... ну, сам понимаешь. Что произошло?";
			link.l1.go = "PZ_Alonso_2";
		break;
		
		case "PZ_Alonso_2":
			dialog.text = "Мы с парнями обнаружили, что кто-то рылся в вашем рундуке.";
			link.l1 = "ЧТО?! Хотя погоди... А как вы это поняли, и что вы все делали у меня в каюте?";
			link.l1.go = "PZ_Alonso_3";
		break;
		
		case "PZ_Alonso_3":
			dialog.text = "Мы время от времени убираемся у вас в каюте, когда вы на шканцах, в городе или ещё где-нибудь. Никогда не обращали внимание? Или запамятовали?";
			link.l1 = "О, и правда. Что ж, ты можешь идти.";
			link.l1.go = "PZ_OsmatrivaemKautu";
		break;
		
		case "PZ_Tichingitu_1":
			dialog.text = "Капитан Шарль, смотреть! Кто-то рыться ваш большой ящик.";
			link.l1 = "Что? Когда ты это узнал? Ты знаешь, кто это сделал?";
			link.l1.go = "PZ_Tichingitu_2";
		break;
		
		case "PZ_Tichingitu_2":
			dialog.text = "Только что. Захотеть заглянуть к вам. И нет - духи молчать, кто это мочь быть.";
			link.l1 = "Это ты удачно зашёл, Тичингиту. А теперь извини - мне нужно проверить, не пропало ли что из моих вещей.";
			link.l1.go = "PZ_OsmatrivaemKautu";
		break;
		
		case "PZ_Duran_1":
			dialog.text = "Эй, капитан, куда смотришь? Гляди, кто-то рылся в твоих пожитках. Даже я это заметил.";
			link.l1 = "Уж не ты ли это был? В конце концов, я плачу тебе не так щедро, как Франсуа.";
			link.l1.go = "PZ_Duran_2";
		break;
		
		case "PZ_Duran_2":
			dialog.text = "Хе, на воре шапка горит, в моём случае это будет шляпа. Стал бы я тогда тебе это говорить? Скажу так - будь это я, я бы забрал ценности, а потом навёл после себя порядок. А тут бардак - не мой почерк.";
			link.l1 = "Неприятно, конечно, такое слышать, но ты прав, чёрт побери. Ладно, Клод, оставь меня со своими колкостями - сейчас не до них. Мне ещё проверять, что забрал с собой вор...";
			link.l1.go = "PZ_OsmatrivaemKautu";
		break;
		
		case "PZ_Folke_1":
			dialog.text = "Капитан, я сегодня заметил, что кто-то рылся в ваших вещах в рундуке. Как вы сами до сих пор не обратили на это внимание?..";
			link.l1 = "Что?.. И правда... Я же не всё время стою и трясусь над рундуком. Я даже не всё время в каюте. Скажи мне честно, Фульк - это был ты? Ты набрал ещё займов у какого-нибудь ростовщика, когда мы были на суше?";
			link.l1.go = "PZ_Folke_2";
		break;
		
		case "PZ_Folke_2":
			dialog.text = "Что вы, капитан - нет, конечно. Ни в карманах, ни в моём кубрике в кают-компании ничего вашего у меня нет. И никогда не будет.";
			link.l1 = "Очень на это надеюсь. Можешь идти - сейчас буду смотреть, что пропало...";
			link.l1.go = "PZ_OsmatrivaemKautu";
		break;
		
		case "PZ_OsmatrivaemKautu":
			DialogExit();
			
			if (npchar.id == "Tichingitu")
			{
				LAi_SetOfficerType(npchar);
				npchar.Dialog.Filename = "Quest\Sharlie\Tichingitu.c";
				npchar.Dialog.CurrentNode = "Tichingitu_officer";
			}
			if (npchar.id == "FMQT_mercen" || npchar.id == "Folke")
			{
				LAi_SetOfficerType(npchar);
				npchar.Dialog.Filename = "Enc_Officer_dialog.c";
				npchar.Dialog.CurrentNode = "hired";
			}
			ChangeCharacterAddressGroup(npchar, "none", "", "");
			
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "rld", "loc2", "PZ_OsmatrivaemSunduk", -1);
		break;
		
		case "PZ_LigaInJungle_1":
			dialog.text = "Шарль де Мор, верно?";
			link.l1 = "Судя по вашему виду, вы и так уже это знаете. Что вам нужно?";
			link.l1.go = "PZ_LigaInJungle_2";
		break;
		
		case "PZ_LigaInJungle_2":
			dialog.text = "Ваша голова.";
			link.l1 = "Занимательно! Мне нравится начало нашего общения. Могу я теперь узнать, кому я насолил? Я мог бы попробовать договориться с этим человеком.";
			link.l1.go = "PZ_LigaInJungle_3";
		break;
		
		case "PZ_LigaInJungle_3":
			dialog.text = "Мы не дилетанты, чтобы раскрывать подобную информацию, капитан де Мор. Однако даже если бы мы сказали, это всё равно бы вам ничем не помогло - тот, кто нанял нас, уже покинул Архипелаг. И ни навредить, ни попросить прощения вы уже не сможете. Мы уже получили свою оплату, осталось только отработать её.";
			link.l1 = "Так ведь если вы уже получили деньги, зачем лить кровь друг друга, не правда ли?";
			link.l1.go = "PZ_LigaInJungle_4";
		break;
		
		case "PZ_LigaInJungle_4":
			dialog.text = "Отнюдь. Повторюсь, мы не дилетанты. А ещё мы дорожим своей репутацией.";
			link.l1 = "Боюсь, в этот раз вам всё равно не удастся её оправдать.";
			link.l1.go = "PZ_LigaInJungle_5";
		break;
		
		case "PZ_LigaInJungle_5":
			dialog.text = "Это мы ещё посмотрим. Обыскать его труп, как закончим! Всё, что найдём - сжечь!";
			link.l1 = "";
			link.l1.go = "PZ_LigaInJungle_6";
		break;
		
		case "PZ_LigaInJungle_6":
			DialogExit();
			
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			LAi_SetFightMode(pchar, true);
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("LigaInJungle_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_LigaInJunglePosleBitvy");
			
			if (CharacterIsHere("Longway"))
			{
				sld = characterFromId("Longway");
				LAi_SetCheckMinHP(sld, 1, true, "");
			}
		break;
		
		case "PZ_Longway_1":
			dialog.text = "Давно покинуть Архипелаг, хм... Мочь ли это быть?..";
			link.l1 = "Что такое, Лонгвэй? Не первый раз в моей жизни, когда за мной приходят охотники за головами.";
			link.l1.go = "PZ_Longway_2";
		break;
		
		case "PZ_Longway_2":
			dialog.text = "Лонгвэй догадываться, кто послать эти люди за господин капитан.";
			link.l1 = "Мне что-то следует знать?";
			link.l1.go = "PZ_Longway_3";
		break;
		
		case "PZ_Longway_3":
			dialog.text = "Это способ господин Роденбург вести работа - убить тех, кто ему помочь, но очень много знать.";
			link.l1 = "И правда... этот тип в маске успел проговориться, что его наниматель недавно покинул Архипелаг. Лукас ведь именно это и собирался сделать! Думаешь, нам стоит опасаться новых нападений?";
			link.l1.go = "PZ_Longway_4";
		break;
		
		case "PZ_Longway_4":
			dialog.text = "Стоит быть готов ко всему, капитан.";
			link.l1 = "Мудрые слова. Значит, будем. Но что же искал Лукас, что, по его мнению, может быть у меня при себе? У тебя есть мысли и на этот счёт, Лонгвэй?";
			link.l1.go = "PZ_Longway_5";
		break;
		
		case "PZ_Longway_5":
			dialog.text = "М-м-м, нет, у Лонгвэй нет ни один мысль, что это мочь быть.";
			link.l1 = "Жаль, конечно. Но ладно, пойдём отсюда.";
			link.l1.go = "PZ_Longway_6";
		break;
		
		case "PZ_Longway_6":
			DialogExit();
			
			Return_LongwayOfficer();
			
			chrDisableReloadToLocation = false;
			pchar.questTemp.PZ_RazgovorGerrits = true;
			pchar.questTemp.PZ_PodozrenieLucas = true;
		break;
		
		// Этап 1, ВЕРНЫЙ КЛЯТВЕ
		case "PZ_Longway_11":
			dialog.text = "Лонгвэй хотеть поговорить с вами, господин капитан. Это быть очень важно.";
			if (CheckAttribute(pchar, "questTemp.PZ_PodozrenieLucas"))
			{
				link.l1 = "Что такое, Лонгвэй? Беспокоишься о новых наймитах Лукаса? Или как раз что-то выяснил об этом?";
				link.l1.go = "PZ_Longway_12";
				AddCharacterExpToSkill(pchar, "Sneak", 100);
			}
			else
			{
				link.l1 = "Конечно, Лонгвэй, что случилось?";
				link.l1.go = "PZ_Longway_13";
			}
		break;
		
		case "PZ_Longway_12":
			dialog.text = "К сожалению, нет, не выяснить.";
			link.l1 = "Так что произошло, Лонгвэй?";
			link.l1.go = "PZ_Longway_13";
		break;
		
		case "PZ_Longway_13":
			dialog.text = "Лонгвэй не мочь сказать. И... он хотеть попросить дать ему уйти.";
			link.l1 = "Уйти? Навсегда? Но почему? Как твой капитан, я имею право знать причину.";
			link.l1.go = "PZ_Longway_14";
		break;
		
		case "PZ_Longway_14":
			dialog.text = "Верно, капитан. Но Лонгвэй - не батрак, не раб, не слуга. Он прийти помогать вам по свой воля. И мочь уйти по свой воля. Это не быть навсегда - есть один важный дело, и Лонгвэй надеяться, что ещё смочь вернуться, как только закончить всё.";
			link.l1 = "Что же это за дело такое? Расскажи хоть что-нибудь - не как капитану, а как человеку, вместе с которым ты уже через столько прошёл.";
			link.l1.go = "PZ_Longway_15";
		break;
		
		case "PZ_Longway_15":
			dialog.text = "Лонгвэй мочь сказать лишь то, что когда-то он дать один очень важный обещание. Клятва. И теперь, спустя много год, прийти время исполнить его. Иначе... иначе в жизни Лонгвэй нет никакой смысл.";
			link.l1 = "Ты прав, Лонгвэй - ты не пленник, а я не тюремщик. Ты можешь идти. Удачи тебе.";
			link.l1.go = "PZ_Longway_Otpustit_1";
			link.l2 = "Конечно, ты можешь идти. Ты не обязан говорить всего, но, скажи хотя бы, куда? Я мог бы пойти с тобой и помочь, не задавая лишних вопросов.";
			link.l2.go = "PZ_Longway_Pomoch_1";
			link.l3 = "У меня тоже важное дело - спасти брата. А для этого мне нужен каждый мой человек. Мы без тебя не справимся, Лонгвэй.";
			link.l3.go = "PZ_Longway_NeOtpuskaem_1";
		break;
		
		case "PZ_Longway_NeOtpuskaem_1":
			dialog.text = "Нет нужда играть на мои жалость и чувство долг. Я прекрасно это понимать. Вы когда-нибудь давать клятва, господин капитан?";
			link.l1 = "Давал, конечно. Так что расскажи мне всё, как есть, а мы с ребятами обязательно тебе поможем.";
			link.l1.go = "PZ_Longway_NeOtpuskaem_2";
		break;
		
		case "PZ_Longway_NeOtpuskaem_2":
			dialog.text = "Лонгвэй не мочь. Просто... не мочь. Это быть великий тайна. И даже не мой.";
			link.l1 = "Жаль. А я-то думал, что между нами есть доверие. Корабль ты не покинешь - сейчас у меня все офицеры на счету.";
			link.l1.go = "PZ_Longway_NeOtpuskaem_3";
			link.l2 = "Ты прав, Лонгвэй - ты не пленник, а я не тюремщик. Ты можешь идти. Удачи тебе.";
			link.l2.go = "PZ_Longway_Otpustit_1";
		break;
		
		case "PZ_Longway_NeOtpuskaem_3":
			dialog.text = "Вы не мочь так поступить!..";
			link.l1 = "К сожалению, мочь, Лонгвэй. А теперь возвращайся к своим обязанностям.";
			link.l1.go = "PZ_Longway_NeOtpuskaem_4";
		break;
		
		case "PZ_Longway_NeOtpuskaem_4":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Longway.c";
			npchar.Dialog.CurrentNode = "Longway_officer";
			
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			
			PChar.quest.PZ_LongwayUhoditOtNasNavsegda.win_condition.l1 = "MapEnter";
			PChar.quest.PZ_LongwayUhoditOtNasNavsegda.win_condition = "PZ_LongwayUhoditOtNasNavsegda";
		break;
		
		case "PZ_Longway_Otpustit_1":
			dialog.text = "Признаться, я думать, что вы не позволить мне так легко взять и уйти. Спасибо, господин капитан.";
			link.l1 = "А, пустое. Хорошего же ты обо мне мнения, раз так подумал! Но скажи - где мне тебя искать, когда ты закончишь свои дела, Лонгвэй?";
			link.l1.go = "PZ_Longway_GdeIskat_1";
		break;
		
		case "PZ_Longway_Pomoch_1":
			dialog.text = "Лонгвэй правда не мочь рассказать ничего из этого, как бы сильно это не желать. Но он ценит готовность господина капитана прийти на помощь.";
			link.l1 = "Значит, быть по сему. Где мне тебя потом искать, когда ты выполнишь своё обещание, Лонгвэй?";
			link.l1.go = "PZ_Longway_GdeIskat_1";
			pchar.questTemp.PZ_LongwayGood = true;
		break;
		
		case "PZ_Longway_GdeIskat_1":
			dialog.text = "Я думать, что успеть закончить свой дело через один месяц. Затем Лонгвэй будет ждать вас ещё неделя в таверна город Бас-Тер.";
			link.l1 = "Что ж, как скажешь, друг мой. Не прощаемся. Увидимся в Бас-Тере.";
			link.l1.go = "PZ_Longway_GdeIskat_2";
		break;
		
		case "PZ_Longway_GdeIskat_2":
			DialogExit();
			
			RemovePassenger(pchar, npchar);
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
			LAi_SetImmortal(npchar, true);
			npchar.location = "None";
			
			SetQuestHeader("PZ");
			AddQuestRecord("PZ", "1");
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			
			SetTimerCondition("PZ_IshemLongway", 0, 0, 30, false);	// ВЕРНУТЬ 30 дней
		break;
		
		case "PZ_SharliePlennik_BadFinal_1":
			dialog.text = "Ну здравствуйте, месье капитан.";
			link.l1 = "Не нравится мне ваша ухмылка, сударь.";
			link.l1.go = "PZ_SharliePlennik_BadFinal_2";
		break;
		
		case "PZ_SharliePlennik_BadFinal_2":
			dialog.text = "Вот как? А ведь я пришёл вам сообщить, что вы, наконец, свободны. Но если вы хотите ещё задержаться в сей роскошной каюте, то на здоровье.";
			link.l1 = "Ну уж нет. Значит, Лонгвэя нашли? Где он? В одной из камер?";
			link.l1.go = "PZ_SharliePlennik_BadFinal_3";
		break;
		
		case "PZ_SharliePlennik_BadFinal_3":
			dialog.text = "На том свете - он решительно не хотел ни с кем из нас разговаривать и сразу кидался в бой.";
			link.l1 = "Чёрт побери!.. Вы ведь могли просто пленить его, навалившись толпой.";
			link.l1.go = "PZ_SharliePlennik_BadFinal_4";
		break;
		
		case "PZ_SharliePlennik_BadFinal_4":
			dialog.text = "Некоторых убить гораздо легче, чем скрутить, неужто не знаете? Радуйтесь, что мы вовсе не предъявили к вам никаких претензий - ваш китаец в очередной раз учинил бойню, и нам понадобилась ещё пара отрядов, со стрелками.";
			link.l1 = "Да уж, действительно, спасибо и на этом.";
			link.l1.go = "PZ_SharliePlennik_BadFinal_5";
		break;
		
		case "PZ_SharliePlennik_BadFinal_5":
			dialog.text = "Кстати говоря, возьмите, раз уж он был вашим другом - мы при себе у него нашли какие-то бумажки. Что это, мы так и не поняли, вам наверняка виднее - на тех участках, что не залиты кровью, была написана какая-то тарабарщина.";
			link.l1 = "Вот оно что... Спасибо, что вернули. До свидания, офицер.";
			link.l1.go = "PZ_SharliePlennik_BadFinal_6";
		break;
		
		case "PZ_SharliePlennik_BadFinal_6":
			DialogExit();
			
			LAi_ActorGoToLocator(npchar, "goto", "goto22", "", -1);
			DoQuestCheckDelay("PZ_SharliePlennik_BadFinal_2", 3.0);
		break;
		
		case "PZ_BasTerStop":
			dialog.text = "Пройдите с нами, с вами желает побеседовать господин комендант.";
			link.l1 = "Я так понимаю, это связано с моими поисками китайца?";
			link.l1.go = "PZ_BasTerStop_2";
		break;
		
		case "PZ_BasTerStop_2":
			dialog.text = "Сами всё поймёте, месье.";
			link.l1 = "Меня в чём-то обвиняют?";
			link.l1.go = "PZ_BasTerStop_3";
		break;
		
		case "PZ_BasTerStop_3":
			dialog.text = "Никак нет. Никто не пытается вас арестовать или задержать. Пока что. Когда я сказал, что комендант желает поговорить с вами, то имел в виду именно это.";
			link.l1 = "Ох, ну хорошо...";
			link.l1.go = "PZ_BasTerStop_4";
		break;
		
		case "PZ_BasTerStop_4":
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation("BasTer_town")], false);
			DoQuestReloadToLocation("BasTer_prison", "goto", "goto17", "PZ_BasTer_TurmaPriveli");
		break;
		
		case "PZ_BasTer_OtryadPeshera_1":
			dialog.text = "У вас есть какие-нибудь идеи? Этот желтокожий крайне опасен, мы уже не первый отряд, посланный сюда. Приказ - приказом, но не хотелось бы вот так глупо умереть, идя туда без какого-либо плана.";
			if (CheckAttribute(pchar, "questTemp.PZ_OhotnikOtryad"))
			{
				link.l1 = "Он всего один, а с вами я. Займусь им, а вы навалитесь. Справимся.";
				link.l1.go = "PZ_BasTer_OtryadPeshera_2";
				if (pchar.location.from_sea != "BasTer_Town")
				{
					link.l2 = "План у меня есть. И, согласно ему, вы как раз все глупо умрёте. Прямо здесь.";
					link.l2.go = "PZ_BasTer_OtryadPeshera_Kill_1";
				}
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DrugOtryad"))
			{
				link.l1 = "Не волнуйся, мы просто поговорим с ним.";
				link.l1.go = "PZ_BasTer_OtryadPeshera_2";
				if (pchar.location.from_sea != "BasTer_Town")
				{
					link.l2 = "Мне очень жаль, но вы все умрёте сегодня. И не от рук китайца.";
					link.l2.go = "PZ_BasTer_OtryadPeshera_Kill_1";
				}
			}
		break;
		
		case "PZ_BasTer_OtryadPeshera_Kill_1":
			pchar.questTemp.PZ_Podelnik = true;
			if (CheckAttribute(pchar, "questTemp.PZ_OhotnikOtryad"))
			{
				dialog.text = "Так вы не охотник за головами... Но даже если и охотник, то вы друг этого трижды проклятого китайца!..";
				link.l1 = "Верно. Мне и так пришлось бы от вас избавиться - не вижу смысла это откладывать.";
				link.l1.go = "PZ_BasTer_OtryadPeshera_Kill_2";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DrugOtryad"))
			{
				dialog.text = "Что это значит?! Вы же сказали, что поможете нам его утихомирить.";
				link.l1 = "Мне кажется, что вы бы всё равно нам потом не дали жилья. Ничего личного.";
				link.l1.go = "PZ_BasTer_OtryadPeshera_Kill_2";
			}
		break;
		
		case "PZ_BasTer_OtryadPeshera_Kill_2":
			DialogExit();
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			chrDisableReloadToLocation = true;
			
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("PZ_BasTer_OtryadPeshera"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			sld = CharacterFromID("PZ_BasTer_OtryadPesheraOff");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_BasTer_OtryadPeshera_Kill_3");
		break;
		
		case "PZ_BasTer_OtryadPeshera_2":
			if (CheckAttribute(pchar, "questTemp.PZ_OhotnikOtryad"))
			{
				dialog.text = "Хотелось бы в это верить.";
				link.l1 = "Я и не в таких передрягах побывал, один китаец нам ничего не сделает. Вперёд, парни!";
				link.l1.go = "PZ_BasTer_OtryadPeshera_3";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DrugOtryad"))
			{
				dialog.text = "А если разговор пойдёт не по плану?";
				link.l1 = "Мне бы этого очень не хотелось, но тогда мне придётся защищаться вместе со всеми вами. Идём.";
				link.l1.go = "PZ_BasTer_OtryadPeshera_3";
			}
		break;
		
		case "PZ_BasTer_OtryadPeshera_3":
			DialogExit();
			
			DoQuestReloadToLocation("Guadeloupe_CaveEntrance", "reload", "reload2", "PZ_IshemLongway_OtryadUPeshery");
		break;
		
		case "PZ_BasTer_SOtryadom_DialogLongway":
			dialog.text = "Господин капитан?! Лонгвэй не мочь поверить, что вы с эти солдаты!..";
			link.l1 = "Нет, Лонгвэй, я здесь, чтобы просто поговорить! Всё не так, как ты подумал!";
			link.l1.go = "PZ_BasTer_SOtryadom_DialogLongway_2";
		break;
		
		case "PZ_BasTer_SOtryadom_DialogLongway_2":
			dialog.text = "Тогда бы вы прийти сюда один. Вы пытаться усыпить мой бдительность, чтобы напасть вместе с эти солдаты!";
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayGood"))
			{
				link.l1 = "Мог бы - пришёл бы один. Я - единственная причина, по которой на тебя до сих пор никто не напал. Успокойся, и давай поговорим, хорошо?";
				link.l1.go = "PZ_BasTer_SOtryadom_DialogLongway_3";
			}
			else
			{
				link.l1 = "Хватит! Хотел бы - напал бы уже. Но я этого не хочу. Сложи оружие, и мы поговорим обо всём, Лонгвэй. Это приказ твоего капитана.";
				link.l1.go = "PZ_BasTer_SOtryadom_DialogLongway_Bad_1";
			}
		break;
		
		case "PZ_BasTer_SOtryadom_DialogLongway_3":
			dialog.text = "Хмм, хорошо. Лонгвэй вам верить, господин капитан.";
			link.l1 = "Вот, другое дело. Расскажи мне...";
			link.l1.go = "PZ_BasTer_SOtryadom_DialogLongway_4";
		break;
		
		case "PZ_BasTer_SOtryadom_DialogLongway_4":
			StartInstantDialog("PZ_BasTer_OtryadPesheraOff", "PZ_BasTer_SOtryadom_DialogLongway_5", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_BasTer_SOtryadom_DialogLongway_5":
			if (CheckAttribute(pchar, "questTemp.PZ_OhotnikOtryad"))
			{
				dialog.text = "Месье, что происходит? Что за... трогательное воссоединение? Вы ведь должны были помочь нам устранить этого китайца.";
				link.l1 = "Так и есть. Я забираю его с собой, и все эти убийства на этом прекратятся. А вы скажете коменданту, что мы вместе его убили. Идёт?";
				link.l1.go = "PZ_BasTer_SOtryadomOhotnik_1";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DrugOtryad"))
			{
				dialog.text = "Отличная работа, капитан! Он сложил оружие. Хорошо, что вы с нами. Теперь давайте отведём его к коменданту.";
				link.l1 = "С чего бы это? Я заплатил компенсацию за поступки Лонгвэя. Щедрую. Ваши сослуживцы были свидетелями, подтвердят. Комендант подтвердит. Он разрешил мне забрать моего человека с собой на корабль.";
				link.l1.go = "PZ_BasTer_SOtryadomDrug_1";
			}
		break;
		
		case "PZ_BasTer_SOtryadomDrug_1":
			dialog.text = "Если коменданту достаточно этого кровавого золота, то мне - нет. Среди убитых им у этой чёртовой пещеры были мои друзья. Месье коменданту будет плевать, если мы всё равно убьём китайца.";
			link.l1 = "Вы не знаете этого наверняка. Но знаете о той наглой ораве разбойников. Это наверняка были они.";
			link.l1.go = "PZ_BasTer_SOtryadomDrug_2";
		break;
		
		case "PZ_BasTer_SOtryadomDrug_2":
			StartInstantDialog("Longway", "PZ_BasTer_SOtryadomDrug_3", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_BasTer_SOtryadomDrug_3":
			dialog.text = "";
			link.l1 = "Лонгвэй! Ты ведь убил далеко не так много солдат, как тебе приписывают, не правда ли?";
			link.l1.go = "PZ_BasTer_SOtryadomDrug_4";
		break;
		
		case "PZ_BasTer_SOtryadomDrug_4":
			dialog.text = "Верно, господин капитан. Лонгвэй видеть тот разбойники. Он спрятаться поглубже в пещера, чтобы они его не заметить. И он слышать звуки разговор, ругань и бой между разбойники и солдаты.";
			link.l1 = "";
			link.l1.go = "PZ_BasTer_SOtryadomDrug_5";
		break;
		
		case "PZ_BasTer_SOtryadomDrug_5":
			StartInstantDialog("PZ_BasTer_OtryadPesheraOff", "PZ_BasTer_SOtryadomDrug_6", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_BasTer_SOtryadomDrug_6":
			dialog.text = "";
			link.l1 = "Видите? Всё сошлось. Лонгвэй бывает вспыльчив, но он честный человек. Мы уходим. Если вы нас тронете, то опозорите честь мундира. Прощайте, господа.";
			link.l1.go = "PZ_BasTer_SOtryadomDrug_7";
		break;
		
		case "PZ_BasTer_SOtryadomDrug_7":
			DialogExit();
			
			AddQuestRecord("PZ", "13");
			LAi_LocationFightDisable(&Locations[FindLocation("Guadeloupe_CaveEntrance")], false);
			chrDisableReloadToLocation = false;
			bDisableLandEncounters = false;
			LAi_LocationDisableOfficersGen("Guadeloupe_jungle_02", false);
			LAi_LocationDisableOfficersGen("Guadeloupe_CaveEntrance", false);
			//LAi_LocationDisableOfficersGen("Guadeloupe_Cave", false);
			
			for (i=1; i<=5; i++)
			{
				sld = CharacterFromID("PZ_BasTer_OtryadPeshera"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "PZ_BasTer_OtryadRazveli", -1);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				LAi_CharacterDisableDialog(sld);
			}
			sld = CharacterFromID("PZ_BasTer_OtryadPesheraOff");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "PZ_BasTer_OtryadRazveli", -1);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			LAi_CharacterDisableDialog(sld);
			
			sld = CharacterFromID("Longway");
			AddPassenger(pchar, sld, false);
			LAi_SetImmortal(sld, false);
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			sld.Dialog.Filename = "Quest\HollandGambit\Longway.c";
			sld.Dialog.CurrentNode = "Longway_officer";
			
			DeleteQuestCondition("PZ_LongwayNelzyaUmeret");
			
			//Продолжение второго этапа
			PChar.quest.PZ_LongwayRazgovorVKaute.win_condition.l1 = "EnterToSea"
			PChar.quest.PZ_LongwayRazgovorVKaute.win_condition = "PZ_LongwayRazgovorVKaute";
		break;
		
		case "PZ_BasTer_SOtryadomOhotnik_1":
			dialog.text = "Нет, месье, не идёт! Он перебил целую кучу наших сослуживцев, и вы говорите, что он уйдёт безнаказанным?! Либо вы помогаете нам расправиться с ним, либо хотя бы не мешайте!";
			link.l1 = "Боюсь, что вынужден помешать. Мне жаль, правда.";
			link.l1.go = "PZ_BasTer_SOtryadomOhotnik_2";
		break;
		
		case "PZ_BasTer_SOtryadomOhotnik_2":
			DialogExit();
			
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("Longway");
			LAi_SetImmortal(sld, false);
			DeleteAttribute(sld, "OfficerImmortal");
			if(CheckAttribute(sld, "Health.HP")) DeleteAttribute(sld, "Health.HP");
			if(CheckAttribute(sld, "Health.maxHP")) DeleteAttribute(sld, "Health.maxHP");
			sTemp = "RestoreHealth_" + sld.index;
			if(CheckAttribute(PChar, "quest.RestoreHealth_" + sld.index)) PChar.quest.(sTemp).over = "Yes";
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			for (i=1; i<=5; i++)
			{
				sld = CharacterFromID("PZ_BasTer_OtryadPeshera"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				LAi_CharacterDisableDialog(sld);
			}
			sld = CharacterFromID("PZ_BasTer_OtryadPesheraOff");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_CharacterDisableDialog(sld);
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_IshemLongway_Zastupaemsya");
			
			PChar.quest.PZ_LongwayNelzyaUmeret.win_condition.l1 = "NPC_Death";
			PChar.quest.PZ_LongwayNelzyaUmeret.win_condition.l1.character = "Longway";
			PChar.quest.PZ_LongwayNelzyaUmeret.win_condition = "PZ_LongwayNelzyaUmeret";
		break;
		
		case "PZ_BasTer_SOtryadom_DialogLongway_Bad_1":
			dialog.text = "Желать вы просто поговорить, вы бы не просить убрать оружие. Но тигр есть тигр даже с убранный когти\nВы наверняка уже решить предать Лонгвэй, нет нужда врать. Защищаться, господин капитан!";
			link.l1 = "Чёрт возьми, нет...";
			link.l1.go = "PZ_BasTer_SOtryadom_DialogLongway_Bad_2";
		break;
		
		case "PZ_BasTer_SOtryadom_DialogLongway_Bad_2":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation("Guadeloupe_CaveEntrance")], false);
			LAi_SetFightMode(pchar, true);
			
			for (i=1; i<=5; i++)
			{
				sld = CharacterFromID("PZ_BasTer_OtryadPeshera"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				LAi_CharacterDisableDialog(sld);
			}
			
			sld = CharacterFromID("Longway");
			LAi_SetImmortal(sld, false);
			DeleteAttribute(sld, "OfficerImmortal");
			if(CheckAttribute(sld, "Health.HP")) DeleteAttribute(sld, "Health.HP");
			if(CheckAttribute(sld, "Health.maxHP")) DeleteAttribute(sld, "Health.maxHP");
			sTemp = "RestoreHealth_" + sld.index;
			if(CheckAttribute(PChar, "quest.RestoreHealth_" + sld.index)) PChar.quest.(sTemp).over = "Yes";
			sld.SaveItemsForDead = true;
			sld.DontClearDead = true;
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_BasTer_MyUbilLongway_BadFinal");
		break;
		
		case "PZ_BasTer_SOtryadom_UbiliLongway":
			if (CheckAttribute(pchar, "questTemp.PZ_OhotnikOtryad"))
			{
				dialog.text = "Не могу поверить, что мы с ним справились! Но скажите, почему он называл вас капитан? Разве вы не охотились за ним?";
				link.l1 = "Всё это гораздо сложнее и запутаннее, чем кажется на первый взгляд, дружище. Мне нужно было успокоить вашего коменданта. Самое главное - результат, разве нет? А результат - Лонгвэй мёртв, и я вам в этом помог.";
				link.l1.go = "PZ_BasTer_SOtryadom_UbiliLongway_2";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DrugOtryad"))
			{
				dialog.text = "Даже ваше присутствие не помогло, он всё равно на нас набросился. Проклятый желтокожий дикарь...";
				link.l1 = "Не нужно так о нём говорить. Он набросился, потому что расстроился и решил, что я заодно с вами.";
				link.l1.go = "PZ_BasTer_SOtryadom_UbiliLongway_2";
			}
		break;
		
		case "PZ_BasTer_SOtryadom_UbiliLongway_2":
			if (CheckAttribute(pchar, "questTemp.PZ_OhotnikOtryad"))
			{
				dialog.text = "Может быть. В таком случае, до свидания, месье. Мы сами передадим, что китаец наконец-то мёртв.";
				link.l1 = "Отлично, спасибо. До свидания, парни.";
				link.l1.go = "PZ_BasTer_SOtryadom_UbiliLongway_3";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DrugOtryad"))
			{
				dialog.text = "Ну, расстроился он или нет, дикарь или нет, это ничего не меняет, месье - он убил очень многих из нас, напал первым. И пытался убить нас всех сейчас, вместе с вами.";
				link.l1 = "Наверняка что-то довело его до этого состояния. Впрочем, не будем об этом. Я пойду, а вы возвращайтесь к коменданту, когда сочтёте нужным. Бывайте.";
				link.l1.go = "PZ_BasTer_SOtryadom_UbiliLongway_3";
			}
		break;
		
		case "PZ_BasTer_SOtryadom_UbiliLongway_3":
			DialogExit();
			
			LAi_SetWarriorType(npchar);
			LAi_CharacterDisableDialog(npchar);
			ChangeCharacterNationReputation(pchar, FRANCE, 12);
			AddQuestRecord("PZ", "11");
			CloseQuestHeader("PZ");
			
			LAi_LocationDisableOfficersGen("Guadeloupe_jungle_02", false);
			LAi_LocationDisableOfficersGen("Guadeloupe_CaveEntrance", false);
			//LAi_LocationDisableOfficersGen("Guadeloupe_Cave", false);
			chrDisableReloadToLocation = false;
			bDisableLandEncounters = false;
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog":
			dialog.text = "Господин капитан?..";
			link.l1 = "Верно! Ох и поискать мне тебя пришлось, Лонгвэй. Ну и шороху же ты навёл в городе! Нам нужно о многом поговорить, бежим на корабль.";
			link.l1.go = "PZ_IshemLongway_SorraKomendant_Dialog_2";
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog_2":
			dialog.text = "Смотреть!..";
			link.l1 = "Вижу. Придётся слегка задержаться.";
			link.l1.go = "PZ_IshemLongway_SorraKomendant_Dialog_3";
			locCameraFromToPos(-12.27, 1.29, -8.89, true, -3.23, -1.20, -4.77);
			DoQuestCheckDelay("PZ_IshemLongway_SorraKomendant_Dialog_Povernutsya", 1.3);
			
			for (i=1; i<=5; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("PZ_BasTer_OtryadPeshera"+i, "sold_fra_"+(rand(7)+1), "man", "man", sti(pchar.rank), FRANCE, 0, true, "soldier"));
				ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload2");
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, pchar, "", -1);
				LAi_SetHP(sld, 60.0, 60.0);
			}
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog_3":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation("Guadeloupe_CaveEntrance")], false);
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("Longway");
			LAi_SetImmortal(sld, false);
			DeleteAttribute(sld, "OfficerImmortal");
			if(CheckAttribute(sld, "Health.HP")) DeleteAttribute(sld, "Health.HP");
			if(CheckAttribute(sld, "Health.maxHP")) DeleteAttribute(sld, "Health.maxHP");
			sTemp = "RestoreHealth_" + sld.index;
			if(CheckAttribute(PChar, "quest.RestoreHealth_" + sld.index)) PChar.quest.(sTemp).over = "Yes";
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			for (i=1; i<=5; i++)
			{
				sld = CharacterFromID("PZ_BasTer_OtryadPeshera"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_IshemLongway_SorraKomendant_Pobeda1");
			
			PChar.quest.PZ_LongwayNelzyaUmeret.win_condition.l1 = "NPC_Death";
			PChar.quest.PZ_LongwayNelzyaUmeret.win_condition.l1.character = "Longway";
			PChar.quest.PZ_LongwayNelzyaUmeret.win_condition = "PZ_LongwayNelzyaUmeret";
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog_4":
			dialog.text = "Ещё идти!";
			link.l1 = "Да, похоже, нас в покое не оставят. Мы здесь, как на ладони. Идём в пещеру, так будет проще отбиться.";
			link.l1.go = "PZ_IshemLongway_SorraKomendant_Dialog_5";
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog_5":
			DialogExit();
			pchar.questTemp.PZ_IshemLongway_SorraKomendant = true;
			PlaySound("Interface\MusketFire1.wav");
			PlaySound("Interface\MusketFire1.wav");
			PlaySound("Interface\MusketFire1.wav");
			
			sld = CharacterFromID("Longway");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "Guadeloupe_Cave", "goto", "locator1", "PZ_IshemLongway_VPesheru", -1);
			
			LAi_SetActorType(pchar);
			LAi_ActorRunToLocation(pchar, "reload", "reload1", "Guadeloupe_Cave", "goto", "locator1", "PZ_IshemLongway_VPesheru", -1);
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog_6":
			dialog.text = "Нам нужно попробовать выйти. Мы не мочь находиться здесь вечность.";
			link.l1 = "И это первое, что ты хочешь мне сказать, учитывая всё произошедшее, Лонгвэй? Не хочешь, например, объяснить мне, что происходит?";
			link.l1.go = "PZ_IshemLongway_SorraKomendant_Dialog_7";
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog_7":
			dialog.text = "Господин капитан, Лонгвэй...";
			link.l1 = "Но ты прав, на самом деле. Пойдём, пока сюда не прибежал ещё один отряд. Поговорим на корабле, сразу же, как отчалим.";
			link.l1.go = "PZ_IshemLongway_SorraKomendant_Dialog_8";
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog_8":
			DoQuestReloadToLocation("Guadeloupe_CaveEntrance", "reload", "reload1", "PZ_IshemLongway_VyhodIsPeshery");
		break;
		
		case "PZ_IshemLongway_Zastupaemsya_1":
			dialog.text = "Коварство и злоба белый люди не знать границ.";
			link.l1 = "Ну, не говори так. Я ведь тоже белый человек. К тому же, ты убил их друзей и сослуживцев. Их можно понять.";
			link.l1.go = "PZ_IshemLongway_Zastupaemsya_2";
		break;
		
		case "PZ_IshemLongway_Zastupaemsya_2":
			dialog.text = "Вы оправдывать их, господин капитан?";
			link.l1 = "Я оправдываю тебя, Лонгвэй. Но призываю не судить людей по цвету кожи. Нас прервали. На чём мы остановились?..";
			link.l1.go = "PZ_IshemLongway_Zastupaemsya_3";
		break;
		
		case "PZ_IshemLongway_Zastupaemsya_3":
			dialog.text = "Капитан! Позади!";
			link.l1 = "Ох, не дадут нам сегодня нормально поговорить...";
			link.l1.go = "PZ_IshemLongway_Zastupaemsya_4";
		break;
		
		case "PZ_IshemLongway_Zastupaemsya_4":
			DialogExit();
			LAi_SetCurHPMax(pchar);
			LAi_GetCharacterMaxEnergy(pchar);
			LAi_SetCurHPMax(sld);
			LAi_GetCharacterMaxEnergy(sld);
			
			sld = CharacterFromID("Longway");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			for (i=6; i<=10; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("PZ_BasTer_OtryadPeshera"+i, "sold_fra_"+(rand(7)+1), "man", "man", sti(pchar.rank), FRANCE, 0, true, "soldier"));
				ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload2");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				LAi_SetHP(sld, 60.0, 60.0);
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_IshemLongway_Zastupaemsya_5");
			
			AddDialogExitQuest("MainHeroFightModeOn"); // Rebbebion, fix
		break;
		
		case "PZ_IshemLongway_Zastupaemsya_6":
			dialog.text = "На горизонт никто, господин капитан.";
			link.l1 = "Это, конечно, хорошо, но не будем здесь задерживаться. Нам с тобой нужно о многом поговорить. Следуй за мной, мы возвращаемся на корабль.";
			link.l1.go = "PZ_IshemLongway_Zastupaemsya_7";
		break;
		
		case "PZ_IshemLongway_Zastupaemsya_7":
			DialogExit();
			
			sld = CharacterFromID("Longway");
			AddPassenger(pchar, sld, false);
			sld.OfficerImmortal = true;
			sld.Health.HP       = 60.0;
			sld.Health.maxHP    = 60.0;
			SetCharacterPerk(sld, "ShipEscape");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			sld.Dialog.Filename = "Quest\HollandGambit\Longway.c";
			sld.Dialog.CurrentNode = "Longway_officer";
			
			LAi_LocationDisableOfficersGen("Guadeloupe_jungle_02", false);
			LAi_LocationDisableOfficersGen("Guadeloupe_CaveEntrance", false);
			//LAi_LocationDisableOfficersGen("Guadeloupe_Cave", false);
			chrDisableReloadToLocation = false;
			bDisableLandEncounters = false;
			AddQuestRecord("PZ", "14");
			DeleteQuestCondition("PZ_LongwayNelzyaUmeret");
			DeleteQuestCondition("PZ_KorablBuhta_BadFinal");
			
			//Продолжение второго этапа
			PChar.quest.PZ_LongwayRazgovorVKaute.win_condition.l1 = "EnterToSea"
			PChar.quest.PZ_LongwayRazgovorVKaute.win_condition = "PZ_LongwayRazgovorVKaute";
		break;
		
		case "PZ_IshemLongway_SrazuNashli_1":
			dialog.text = "Господин капитан, это правда вы?..";
			link.l1 = "Да, Лонгвэй. Ты цел, кстати?";
			link.l1.go = "PZ_IshemLongway_SrazuNashli_2";
		break;
		
		case "PZ_IshemLongway_SrazuNashli_2":
			dialog.text = "Лонгвэй быть порядок. Благодарить\nГосподин капитан!.. Обернуться!";
			link.l1 = "Бежим в пещеру, скорее! Там будет легче обороняться.";
			link.l1.go = "PZ_IshemLongway_SrazuNashli_3";
		break;
		
		case "PZ_IshemLongway_SrazuNashli_3":
			DialogExit();
			PlaySound("Interface\MusketFire1.wav");
			PlaySound("Interface\MusketFire1.wav");
			PlaySound("Interface\MusketFire1.wav");
			
			sld = CharacterFromID("Longway");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "Guadeloupe_Cave", "goto", "locator1", "PZ_IshemLongway_VPesheru", -1);
			
			LAi_SetActorType(pchar);
			LAi_ActorRunToLocation(pchar, "reload", "reload1", "Guadeloupe_Cave", "goto", "locator1", "PZ_IshemLongway_VPesheru", -1);
		break;
		
		case "PZ_IshemLongway_SrazuNashli_4":
			dialog.text = "Лонгвэй выйти проверить, не идти ли ещё солдаты.";
			link.l1 = "Выйдем вместе - мы не будем держать оборону против всего гарнизона. И Лонгвэй.";
			link.l1.go = "PZ_IshemLongway_SrazuNashli_5";
		break;
		
		case "PZ_IshemLongway_SrazuNashli_5":
			dialog.text = "Да, господин капитан?";
			link.l1 = "Нам нужно будет очень о многом поговорить. А сейчас беги за мной - нам нужно немедленно поднять якорь.";
			link.l1.go = "PZ_IshemLongway_SrazuNashli_6";
		break;
		
		case "PZ_IshemLongway_SrazuNashli_6":
			DoQuestReloadToLocation("Guadeloupe_CaveEntrance", "reload", "reload1", "PZ_IshemLongway_VyhodIsPeshery");
		break;
		
		// Этап 2, СТРАНИЦЫ ИСТОРИИ
		case "PZ_LongwayRazgovorOProshlom":
			dialog.text = "Лонгвэй ещё раз благодарить за спасение. У господина капитана наверняка множество вопросов.";
			link.l1 = "Это мягко сказано. Зачем ты убил столько солдат? Это совершенно на тебя не похоже, ты не убиваешь ради удовольствия.";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_LongwayRazgovorOProshlom_2":
			dialog.text = "Причина быть, конечно. Солдаты остановить Лонгвэй. А он никак не мочь попасть в тюрьму. Именно она ему и грозить, пойти он с ними, надолго - никто не будет слушать китаец, в отличие от белый человек.";
			link.l1 = "Да они и других белых не всегда слушают, скажу я тебе. Ты, конечно, правильно поступил, что не дал себя арестовать, хотя не стоило устраивать резню прямо в городе! Бежал бы лучше сразу в джунгли. А что за дело у тебя было в Бас-Тере?";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_3";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_3":
			dialog.text = "Белый люди... не слушать меня, иногда даже не хотеть разговаривать. Или вовсе сразу вызывать стража. Мы не выбирать наш кожа, наш разрез глаз. Лонгвэй не выбирать, кем он быть!\nИ всё же, он гордиться тем, кто он есть. Когда солдаты снова насмехаться и угрожать, Лонгвэй... устать. И злиться.";
			link.l1 = "Отныне я предлагаю нам действовать сообща. Мне белые люди всё скажут. Ну или, по крайней мере, не сразу вызовут стражу, ха-ха-ха! Но серьёзно. Расскажи мне о своём великом деле. И позволь тебе помочь.";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_4";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_4":
			dialog.text = "Прошу, господин капитан, понять Лонгвэй. Он дать клятва, что должен это сделать один. Не давить на него. Вы... должен Лонгвэй. Он когда-то очень помочь вам.";
			link.l1 = "Кто знает, может, я бы и сам тогда справился с ван Мерденом? Но не подумай, я и правда благодарен. Однако мы были квиты с самого начала - ты сказал, что я сохранил тебе лицо, а ты сохранил мне жизнь. А теперь тебя спас я.";
			if (CheckAttribute(pchar, "questTemp.PZ_NashliArhiv")) link.l1.go = "PZ_LongwayRazgovorOProshlom_5";
			else link.l1.go = "PZ_LongwayRazgovorOProshlom_Grubim_1";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_5":
			dialog.text = "Хмм... вы быть правы, господин капитан. Лонгвэй верить, что вы - его настоящий друг среди белый люди. Он так уже думать раньше. И горько ошибиться. Вы помнить Джон Мердок? Йохан ван Мерден.";
			link.l1 = "Как странно, что ты упомянул ван Мердена. Ведь какое-то время назад кто-то вырвал несколько страниц из его архива прямо у меня под носом. Видимо, это оказалось как-то связано с твоим делом, и ты нашёл вора?";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_6";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_6":
			dialog.text = "Правда. Быть связанным. Но... этот вор быть Лонгвэй. Ему очень жаль, господин капитан. Он тогда ещё не знать, мочь ли он доверять вам полный мера.";
			if (sti(pchar.reputation.nobility) <= 60)
			{
				link.l1 = "Говоришь о дружбе, а сам обворовываешь меня за моей спиной?! Чтобы это было в первый и последний раз. Ты меня понял, Лонгвэй?";
				link.l1.go = "PZ_LongwayRazgovorOProshlom_Grubim_1";
				notification("Слишком низкий уровень чести! ("+XI_ConvertString(GetReputationName(61))+")", "None");
			}
			else
			{
				link.l1 = "А как тебе это удалось провернуть, Лонгвэй?";
				link.l1.go = "PZ_LongwayRazgovorOProshlom_Proshaem_1";
				notification("Проверка чести пройдена", "None");
			}
		break;
		
		case "PZ_LongwayRazgovorOProshlom_Grubim_1":
			dialog.text = "Лонгвэй всё понять. Он непременно иметь это ввиду.";
			link.l1 = "Уж надеюсь на это. А теперь рассказывай, как ты докатился до такой жизни, что за обещание ты дал, когда, кому.";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_Grubim_2";
			if (CheckAttribute(pchar, "questTemp.PZ_NashliArhiv")) AddComplexSelfExpToScill(100, 100, 100, 100);
			notification("Лонгвэй не одобряет", "Longway");
		break;
		
		case "PZ_LongwayRazgovorOProshlom_Grubim_2":
			dialog.text = "Да, господин капитан\nЛонгвэй искать самый важный из оставшийся в живой человек для него - Чанг Шин. Он даже не знать, жить ли всё ещё Чанг Шин.";
			link.l1 = "Чанг Шин - твой лучший друг?";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_7";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_Proshaem_1":
			dialog.text = "Благодаря ваш доброта весь остальной команда тоже быстро привыкнуть и начать верить мне, а не следить за Лонгвэй.";
			link.l1 = "Ну что же, я понял. Не тот случай, когда нужно похвалить, но хорошая работа, Лонгвэй. Правда, беспорядок за собой стоило прибрать.";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_Proshaem_2";
			AddComplexLandExpToScill(200, 200, 0);
			pchar.questTemp.PZ_FlagArhiv = true;
			notification("Лонгвэй одобряет", "Longway");
		break;
		
		case "PZ_LongwayRazgovorOProshlom_Proshaem_2":
			dialog.text = "Верно. Но на это не быть время.";
			link.l1 = "Пожалуй. Но постарайся так больше не делать, хорошо? Если что-то нужно - спроси меня сам. Понял? Ты можешь мне доверять. Расскажи мне о своей клятве.";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_Proshaem_3";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_Proshaem_3":
			dialog.text = "Конечно, Лонгвэй с радостью поделить этим с вами, господин капитан\nЛонгвэй искать самый важный из оставшийся в живой человек для него - Чанг Шин.";
			link.l1 = "Чанг Шин - твой лучший друг?";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_7";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_7":
			dialog.text = "Чанг Шин - мой семья. Сестра. Она пропасть много лет назад. Чтобы отыскать её, Лонгвэй искать тех, кто мочь знать, где она быть.";
			link.l1 = "А причём же здесь архив ван Мердена? Он как-то относится к пропаже твоей сестры?";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_8";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_8":
			dialog.text = "Верно. Относиться. Лонгвэй и Йохан знать друг друга очень много лет, когда они познакомиться в земли, что белый люди звать Формоза, ещё до мой прибытие на Архипелаг.";
			link.l1 = "Вы знакомы столько лет? И ван Мерден был там? Поразительно. И, всё же, как он был связан с пропажей твоей сестры?";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_9";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_9":
			dialog.text = "Он помочь мне в поисках другие, очень плохие люди. Даже для белый люди. Они быть зло. Их быть ещё трое - Оливерио Ферментелуш, Антони ван Димен и Сепп ван дер Винк.";
			link.l1 = "Судя по их именам, один из них португалец, остальные - голландцы.";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_10";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_10":
			dialog.text = "Да, быть так. Но тогда поиски не увенчаться успех. Лонгвэй терпеливо ждать подсказка Небес. Поэтому, когда к господин капитан попасть архив ван Мерден, я решить его изучить. И когда найти первые же страницы с упоминание Оливерио, вырвать их и покинуть каюта.";
			link.l1 = "Вот, значит, как всё произошло. Наконец-то всё сложилось в этой истории.";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_11";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_11":
			dialog.text = "Но сама история только начинаться. Господин капитан хотеть узнать о поисках Лонгвэй. С самый начало. Вы готовы сесть и послушать?";
			link.l1 = "Я как бы для этого тебя и вызвал в каюту. Конечно, продолжай.";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_12";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_12":
			DialogExit();
			
			SetCurrentTime(12, 00);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			SetMainCharacterIndex(GetCharacterIndex("Longway"));
			PChar = GetMainCharacter();
			LAi_SetPlayerType(PChar);
			DoQuestReloadToLocation("Formosa", "patrol", "patrol1", "PZ_Formosa_Start");
		break;
		
		case "PZ_Formosa_Tavern_1":
			dialog.text = "Желтокожим сюда нельзя, у меня здесь вообще-то уважаемое заведение. Для уважаемых людей, а не таких, как ты.";
			link.l1 = "У мой только один вопрос. Позвольте задать, и я уйти.";
			link.l1.go = "PZ_Formosa_Tavern_2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_Formosa_Tavern_2":
			dialog.text = "Говорить сначала нормально научись! Сказано тебе - вашим сюда нельзя.";
			link.l1 = "Где мой мочь найти Оливерио Ферментелуш? Вы сказать - я сразу выйти.";
			link.l1.go = "PZ_Formosa_Tavern_3";
		break;
		
		case "PZ_Formosa_Tavern_3":
			dialog.text = "А ты, я посмотрю, ещё и глухой, да? Не испытывай моё терпение, а то вся зала скоро провоняет жёлтым дерьмом.";
			link.l1 = "Наши люди жить тут тысячи лет, это наш остров, и мы не мочь зайти в простой трактир?!";
			link.l1.go = "PZ_Formosa_Tavern_4";
		break;
		
		case "PZ_Formosa_Tavern_4":
			dialog.text = "У-у-у, как ты заговорил. Тебя за такое и повесить могут. Пошёл прочь.";
			link.l1 = "...";
			link.l1.go = "PZ_Formosa_Tavern_5";
		break;
		
		case "PZ_Formosa_Tavern_5":
			DialogExit();
			locCameraSleep(true);
			LAi_CharacterDisableDialog(npchar);
			
			sld = CharacterFromID("PZ_Formosa_smuggler");
			LAi_CharacterEnableDialog(sld);
			//AddLandQuestMark(sld, "questmarkmain");
			LAi_Fade("PZ_Formosa1_9", "");
		break;
		
		case "PZ_Formosa_smuggler_1":
			dialog.text = "Я слышал о твоей большой проблеме, мой маленький друг. Не стоило, конечно, говорить так громко - как и об этом имени, так и о том, куда таким, как ты, ходить можно, а куда - нет.";
			link.l1 = "Вы что-то знать об этот человек? Что именно?";
			link.l1.go = "PZ_Formosa_smuggler_2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_Formosa_smuggler_2":
			dialog.text = "Угомонись, приятель.";
			link.l1 = "Мой приносить вам извинения.";
			link.l1.go = "PZ_Formosa_smuggler_3";
		break;
		
		case "PZ_Formosa_smuggler_3":
			dialog.text = "Извинения мне твои не нужны. А вот денежки - вполне. Глядишь, тогда и помогу тебе. Давай познакомимся, как следует. Марселу Шулте. Ну а ты? Деньги у тебя есть, самое главное?";
			link.l1 = "Мой... Чанг Ту. Деньги есть. Это достаточно?";
			link.l1.go = "PZ_Formosa_smuggler_4";
		break;
		
		case "PZ_Formosa_smuggler_4":
			dialog.text = "(присвистывает) Эскудо, песо, гульдены, дублоны, какие-то ваши странные монетки. Допустим. Ну хорошо, Чанг-Чанг. Постараюсь что-нибудь о нём выяснить. Не боись, я тут бываю почти каждый день, так что никуда не денусь с твоими деньгами. Заглядывай украдкой ежедневно, и обязательно пересечёмся.";
			link.l1 = "Мой надеяться на это - больше деньги нет...";
			link.l1.go = "PZ_Formosa_smuggler_5";
		break;
		
		case "PZ_Formosa_smuggler_5":
			DialogExit();
			LAi_SetStayType(pchar);
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("Прошло несколько дней"+ NewStr() +"4 апреля 1645 года", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("Formosa_tavern", "goto", "goto1", "PZ_Formosa_Spustya4Dnya");
			LaunchFrameForm();
		break;
		
		case "PZ_Formosa_smuggler_11":
			dialog.text = "А, Чанг-Чанг! Ты уже тут как тут.";
			link.l1 = "Чанг Ту.";
			link.l1.go = "PZ_Formosa_smuggler_12";
		break;
		
		case "PZ_Formosa_smuggler_12":
			dialog.text = "Да мне как-то плевать, приятель.";
			link.l1 = "Вы смочь узнать, где сейчас Оливерио?";
			link.l1.go = "PZ_Formosa_smuggler_13";
		break;
		
		case "PZ_Formosa_smuggler_13":
			dialog.text = "Нет, понятия не имею, где он сейчас.";
			link.l1 = "Мой деньги!..";
			link.l1.go = "PZ_Formosa_smuggler_14";
		break;
		
		case "PZ_Formosa_smuggler_14":
			dialog.text = "Да не трясись ты так! Подходил бы я к тебе вообще, если бы ничего не выяснил? Тебе, мой маленький друг, несказанно повезло - я тебя познакомлю с одним человечком, которому это известно\nДа и вообще, любит он вас, желтокожих - слуг набрал соответствующих. Хех, и служаночек, конечно... Даже язык поганый ваш учит. Зовут его Йохан ван Мерден. Он будет тебя ждать в двухэтажном доме неподалёку от резиденции.";
			link.l1 = "Мой благодарить.";
			link.l1.go = "PZ_Formosa_smuggler_15";
		break;
		
		case "PZ_Formosa_smuggler_15":
			DialogExit();
			
			locCameraSleep(true);
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(pchar, "reload", "reload1_back", "PZ_Formosa1_11", -1);
			LAi_ActorGoToLocation(npchar, "goto", "goto3", "", "", "", "", -1);
			npchar.location = "None";
			LocatorReloadEnterDisable("Formosa", "houseSp1", false);
		break;
		
		case "PZ_Formosa_JohanVanMerden_1":
			dialog.text = "Ты, видимо, Чанг-Чанг? Проходи, проходи, не стесняйся.";
			link.l1 = "Чанг Ту.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_2";
			DelLandQuestMark(npchar);
			locCameraFromToPos(-1.91, 2.06, -1.75, true, 2.23, -0.85, 0.85);
		break;
		
		case "PZ_Formosa_JohanVanMerden_2":
			dialog.text = "Вот как? Прими мои извинения. Ох уж этот Марселу и его бесконечные унизительные шуточки. Как будто до сих пор ребёнок, ей-Богу. Так мало кому интересна ваша культура, какое пренебрежение! И всё это всего лишь из-за другого языка, к тому же, весьма сложного, да разреза глаз. А ведь вы умны. В отличие от чёрных, хе-хе.";
			link.l1 = "(говорит по-китайски) Значит, тот контрабандист не солгал - вы и правда человек высокой культуры. И вы действительно говорите на нашем языке?";
			link.l1.go = "PZ_Formosa_JohanVanMerden_2a";
			link.l2 = "Мой благодарить вас за тёплый слова о мой культура. Вы, видимо, господин ван Мерден?";
			link.l2.go = "PZ_Formosa_JohanVanMerden_3";
		break;
		
		case "PZ_Formosa_JohanVanMerden_2a":
			dialog.text = "Ох... я понял буквально пару слов. Я ещё только начинаю учить ваш язык. Не мог бы ты продолжить на голландском?";
			link.l1 = "Как вы сказать. Так вы быть Йохан ван Мерден?";
			link.l1.go = "PZ_Formosa_JohanVanMerden_3";
		break;
		
		case "PZ_Formosa_JohanVanMerden_3":
			dialog.text = "Да, Чанг Ту, это я. Я слышал, ты ищешь Оливерио Ферментелуша. Ну что же, мне и правда известно, где его искать. Но скажи мне, для чего он тебе понадобился? От твоего ответа будет зависеть и мой.";
			link.l1 = "Этот... капитан похитить мой последний и самый дорогой человек, мой семья - мой сестра, Чанг Шин.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_4";
		break;
		
		case "PZ_Formosa_JohanVanMerden_4":
			dialog.text = "Тогда спешу тебя расстроить - скорее всего, ей уже не помочь, Чанг Ту. Полагаю, её уже продали в рабство богатому плантатору. Или в публичный дом. В обоих случаях ты не сможешь её спасти - тебя никуда не пустят. А все эти места хорошо охраняются.";
			link.l1 = "Мой быть уверен, что Чанг Шин всё ещё жить. Оливерио... положить на неё глаз. Она - гордо отказать. Он - украсть её, когда мой не быть дома. И... убить наш родители...";
			link.l1.go = "PZ_Formosa_JohanVanMerden_5";
		break;
		
		case "PZ_Formosa_JohanVanMerden_5":
			dialog.text = "Я... сочувствую твоему горю. В таком случае Чанг Шин, я верно запомнил? Чанг Шин действительно может быть жива\nВот как мы с тобой поступим. Дай мне время, чтобы выяснить, где сейчас точно может находиться Оливерио. Скажем, неделю. И увидимся снова. Но не здесь - за городскими воротами. Кто знает, какой хвост за тобой тащится. И вовлекать в это свою персону я не намерен, не обессудь.";
			link.l1 = "Мой... мой быть вам очень благодарен, господин ван Мерден! Ждать с нетерпением наш новый встреча.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_6";
		break;
		
		case "PZ_Formosa_JohanVanMerden_6":
			DialogExit();
			LAi_SetStayType(pchar);
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("Прошла неделя"+ NewStr() +"11 апреля 1645 года", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("Formosa_ExitTown", "goto", "goto3", "PZ_Formosa_Spustya7Dney");
			LaunchFrameForm();
		break;
		
		case "PZ_Formosa_JohanVanMerden_11":
			dialog.text = "Здравствуй, Чанг Ту. Вижу, как горят твои глаза, и новости у меня и правда есть. Но не слишком хорошие.";
			link.l1 = "Для мой любые новости быть крайне важны. Просить, рассказать скорее, господин ван Мерден!";
			link.l1.go = "PZ_Formosa_JohanVanMerden_12";
		break;
		
		case "PZ_Formosa_JohanVanMerden_12":
			dialog.text = "Ну хорошо, как скажешь... Ферментелуш отбыл в Батавию примерно месяц назад. Других ниточек к нему больше нет. Хорошие новости - там он бывает весьма подолгу, так что если как-нибудь туда попадёшь - застанешь его там. Плохие - он близкий друг тамошнего генерал-губернатора, Антони ван Димена. Так что тебя не подпустят и на расстояние выстрела.";
			link.l1 = "Этих новостей быть достаточно, и мой нижайше вас благодарить, господин ван Мерден! Я немедленно отправиться туда.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_13";
		break;
		
		case "PZ_Formosa_JohanVanMerden_13":
			dialog.text = "Что-то мне подсказывало, что ты так и ответишь, поэтому я решил сделать для тебя и Чанг Шин ещё кое-что, чтобы уравнять твои шансы. А именно написал письмо своему старому знакомому, Оливеру Трасту. Он владелец магазина в Батавии. И мой должник. Так что он тебе поможет.";
			link.l1 = "Мой... мой не знать, что сказать...";
			link.l1.go = "PZ_Formosa_JohanVanMerden_14";
			//Log_Info("Вы получили письмо");
			PlaySound("interface\important_item.wav");
		break;
		
		case "PZ_Formosa_JohanVanMerden_14":
			dialog.text = "Может быть, просто 'спасибо'? Я шучу. В случае же, если ты нигде не сможешь найти в городе самого Оливерио, поищи его корабль - 'Утреннюю звезду'. Через корабль всегда можно найти и капитана. Удачи тебе, друг мой! Вам с сестрой она понадобится.";
			link.l1 = "Благодарить вас от всё сердце, господин ван Мерден...";
			link.l1.go = "PZ_Formosa_JohanVanMerden_15";
		break;
		
		case "PZ_Formosa_JohanVanMerden_15":
			DialogExit();
			LAi_SetStayType(pchar);
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("Батавия"+ NewStr() +"29 мая 1645 года", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("Batavia", "merchant", "mrcActive5", "PZ_Batavia_Puteshestvie");
			LaunchFrameForm();
		break;
		
		case "PZ_OliverTrust_1": //
			dialog.text = "Кто ты и что забыл здесь? Я не торгую с вашими.";
			link.l1 = "У мой для вас письмо.";
			link.l1.go = "PZ_OliverTrust_2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_OliverTrust_2":
			dialog.text = "А, посыльный! Хотя я не ждал сегодня никаких писем. Стой здесь! Я пробегусь глазами\n(читает) Вот как...";
			link.l1 = "Вы быть Оливер Траст? Мой прислать господин ван Мерден к ваш.";
			link.l1.go = "PZ_OliverTrust_3";
			//Log_Info("Вы отдали письмо");
			PlaySound("interface\important_item.wav");
		break;
		
		case "PZ_OliverTrust_3":
			dialog.text = "Я читать умею. В обычных условиях я бы послал тебя куда подальше, но таким, как ван Мерден, не отказывают\nЗаодно расквитаюсь с ван Дименом.";
			link.l1 = "Мой цель - Ферментелуш. Но чем же вам насолить ван Димен?";
			link.l1.go = "PZ_OliverTrust_4";
		break;
		
		case "PZ_OliverTrust_4":
			dialog.text = "Это совершенно не твоё дело. Ты и так должен быть благодарен, что я тебе помогаю. А теперь слушай, пока я не решил, что это, всё-таки, плохая идея\nФерментелуша я тоже знаю. Бывает он тут часто и подолгу, но сейчас его нет - 'Утренняя звезда' отчалила с несколько недель назад. И Бог знает, когда ему в голову взбредёт вернуться. Поэтому твоя цель - его друг...";
			link.l1 = "... ван Димен.";
			link.l1.go = "PZ_OliverTrust_5";
		break;
		
		case "PZ_OliverTrust_5":
			dialog.text = "Верно. Ты и об этом знаешь? Полагаю, Йохан тебе об этом сказал? Ох и рискуешь же ты, ван Мерден... Но раз ты знаешь о ван Димене, то ты заодно знаешь, и кто он, верно? Как ты собираешься добраться до генерал-губернатора? Не вломишься же ты к нему в резиденцию!";
			link.l1 = "Чанг Ту - хороший воин.";
			link.l1.go = "PZ_OliverTrust_6";
		break;
		
		case "PZ_OliverTrust_6":
			dialog.text = "Вот что, хороший воин. Ты же понимаешь, что мы все теперь повязаны? И что будет, если тебя схватят? Так что подсоблю тебе, ради своего же благополучия\nПомимо своей резиденции, ван Димен бывает на плантации за городом, а также у своей любовницы, Ветте, которая живёт в двухэтажном доме рядом с таверной.";
			link.l1 = "Вы сказать, что у вас быть ещё что-то полезный для мой. Что это?";
			link.l1.go = "PZ_OliverTrust_12";
		break;
		
		case "PZ_OliverTrust_12":
			dialog.text = "Видишь ли, я считаю, что каждый человек должен чем-нибудь увлекаться. Я, например, коллекционирую редкое и дорогое оружие. Иногда с историей, иногда - нет, но всегда - смертоносное. Приготовил тут кое-что для тебя из своих старых запасов\nТак скажи мне, где ты по итогу решил устроить засаду ван Димену?";
			link.l1 = "(Резиденция) Раз вы владеть много хороший оружие, то резиденция - с добрый клинок у Чанг Ту не быть соперник среди белый люди.";
			link.l1.go = "PZ_OliverTrust_resedinsia_1";
			link.l2 = "(Плантация) Я подкараулить их у дорога на плантацию, чтобы им не быть куда бежать.";
			link.l2.go = "PZ_OliverTrust_Plantation1";
			link.l3 = "(Любовница) У любовница - людей там быть немного, стража не успеть помочь.";
			link.l3.go = "PZ_OliverTrust_lubovnitsa_1";
			SetCharacterPerk(pchar, "Gunman");
			SetCharacterPerk(pchar, "GunProfessional");
			InterfaceStates.Buttons.Save.enable = false;
		break;
		
		// Rebbebion, ну, с Богом...
		case "PZ_OliverTrust_Plantation1":
			pchar.questTemp.PZ_Batavia_plantation_Go = true;
			
			dialog.text = "Отличный план, кстати говоря! Я впечатлён. И чтобы воспользоваться всеми его преимуществами, тебе понадобится хорошее ружьё - устроим на них настоящую охоту. Скажи, с какой дистанции ты обычно стреляешь, Чанг Ту?";
			link.l1 = "Говоря правда, не слишком далеко - чтобы не промахнуться."
			link.l1.go = "PZ_OliverTrust_Plantation_MediumDistance1";
			link.l2 = "Издалека - так враг даже не сразу понять, откуда я его разить.";
			link.l2.go = "PZ_OliverTrust_Plantation_FarDistance1";
			notification("Открыт 'Егерь'", "Longway");		//Jager Unlocked
			SetCharacterPerk(pchar, "Jager");
		break;
		
		case "PZ_OliverTrust_Plantation_MediumDistance1":
			// делаем Лонгвэя мушкетёром с одновременной выдачей мушкета
			/* pchar.model = "Longway_mush";
			pchar.model.animation = "mushketer"; */
			pchar.model = "Longway";
			pchar.model.animation = "Longway";
			Characters_RefreshModel(pchar);
			GiveItem2Character(pchar, "mushket6"); 
			EquipCharacterByItem(pchar, "mushket6");
			//Log_Info("Вы получили башенный мушкетон");
			PlaySound("interface\important_item.wav");
			
			AddItems(pchar, "grapeshot", 50);
			AddItems(pchar, "gunpowder", 50);
			LAi_SetCharacterUseBullet(pchar, MUSKET_ITEM_TYPE, "grapeshot");
			
			dialog.text = "Понимаю тебя. В таком случае... Вот! Старинный португальский башенный мушкетон, бьёт полноценной крупнокалиберной картечью. Таких уже почти не делают даже в Старом Свете.";
			link.l1 = "Мой видеть такой в детство!..";
			link.l1.go = "PZ_OliverTrust_Plantation_MediumDistance2";
		break;
		
		case "PZ_OliverTrust_Plantation_MediumDistance2":
			dialog.text = "Значит, пользоваться умеешь?";
			link.l1 = "Нет...";
			link.l1.go = "PZ_OliverTrust_Plantation_MediumDistance3";
		break;
		
		case "PZ_OliverTrust_Plantation_MediumDistance3":
			dialog.text = "Имей ввиду - сменный механизм стал сильно заедать со временем. Никакое масло и прочие смазки не помогают - там что-то внутри сломалось. Заряжать его теперь гораздо труднее, так что сделаем это прямо сейчас. Смотри и запоминай - с небольшим усилием, вот так. Но не сильнее, иначе доломаешь.";
			link.l1 = "Так?";
			link.l1.go = "PZ_OliverTrust_Plantation_MediumDistance4";
		break;
		
		case "PZ_OliverTrust_Plantation_MediumDistance4":
			dialog.text = "Вот так вот.";
			link.l1 = "Понять. Большой спасибо вам!";
			link.l1.go = "PZ_OliverTrust_13";
		break;
		
		case "PZ_OliverTrust_Plantation_FarDistance1":
			// делаем Лонгвэя мушкетёром с одновременной выдачей мушкета
			/* pchar.model = "Longway_mush";
			pchar.model.animation = "mushketer"; */
			pchar.model = "Longway";
			pchar.model.animation = "Longway";
			Characters_RefreshModel(pchar);
			GiveItem2Character(pchar, "mushket2x2"); 
			EquipCharacterByItem(pchar, "mushket2x2");
			//Log_Info("Вы получили двуствольный штуцер");
			PlaySound("interface\important_item.wav");
			
			AddItems(pchar, "cartridge", 50);
			AddItems(pchar, "gunpowder", 50);
			LAi_SetCharacterUseBullet(pchar, MUSKET_ITEM_TYPE, "cartridge");
			
			dialog.text = "Настоящий охотник! Осторожнее, это был подарок. Один из редких случаев, когда оружие и богато украшено, и крайне эффективно. Двуствольный охотничий штуцер. Тяжело держать, легко и приятно использовать. Уже примерно понял, как из него стрелять?";
			link.l1 = "Понять. Большой спасибо вам!";
			link.l1.go = "PZ_OliverTrust_13";
		break;
		
		case "PZ_OliverTrust_lubovnitsa_1":
			dialog.text = "Насчёт стражи ты, конечно, прав, но людей там всё равно будет достаточно - ван Димен никуда не ходит по городу без своей правой руки, Сеппа ван дер Винка.";
			link.l1 = "Значит, они Ветте вместе?..";
			link.l1.go = "PZ_OliverTrust_lubovnitsa_2";
			pchar.questTemp.PZ_Batavia_lubovnitsa_Go = true;
			AddCharacterSkillDontClearExp(pchar, "Sailing", 10);
			AddCharacterSkillDontClearExp(pchar, "Commerce", 10);
			AddCharacterSkillDontClearExp(pchar, "Repair", 10);
			notification("Морские навыки +", "Longway");			//Naval Skills +
			notification("Открыт 'Крысиный волк'", "Longway");		//Rat Wolf Unlocked
			SetCharacterPerk(pchar, "RatsWolf");
		break;
		
		case "PZ_OliverTrust_lubovnitsa_2":
			dialog.text = "Что? Аха-ха-ха-ха-ха! А у тебя неплохое воображение, китаец! Но нет. Антони трусоват, и ван дер Винк там нужен на случай вроде нашего - если кто-то помешает идиллии любовничков. Сепп носит тяжеленный траншейный панцирь, не всякий палаш его пробьёт. Поэтому\nАсоледа. Не смотри на то, что рапира - за счёт длинного клинка, к слову, более прочного, чем у большинства других рапир и шпаг, весит она, как хороший меч.";
			link.l1 = "С рапира идти на латник?..";
			link.l1.go = "PZ_OliverTrust_lubovnitsa_3";
			//Log_Info("Вы получили асоледу");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(PChar, "blade_26");
			EquipCharacterByItem(Pchar, "blade_26");
		break;
		
		case "PZ_OliverTrust_lubovnitsa_3":
			dialog.text = "А кто-то предлагает тебе ею тыкать в сам доспех? Это тебе не эсток. Бей в щели. И другие уязвимые места, у паха, подмышек и горла. Изматывай его, диктуй свои условия - помимо панциря, Сепп владеет не менее тяжеленной секирой. Не пытайся парировать его удары - скорее, отмахивайся\nНо на случай, если тебе так и не удастся ткнуть его в открытые места - это. Бландербуз, чаще всего используется, как крупнокалиберная картечница. Но в нашем случае я дам тебе набор стальных стрел.";
			link.l1 = "Использовать стрелы для мушкет?..";
			link.l1.go = "PZ_OliverTrust_lubovnitsa_4";
			//Log_Info("Вы получили бландербуз");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(PChar, "pistol8");
			EquipCharacterByItem(Pchar, "pistol8");
			AddItems(Pchar, "harpoon", 30);
			AddItems(Pchar, "gunpowder", 30);
			LAi_SetCharacterUseBullet(Pchar, GUN_ITEM_TYPE, "harpoon");
		break;
		
		case "PZ_OliverTrust_lubovnitsa_4":
			dialog.text = "Необычно, да? Сплав старины и новизны. Рассчитан на стрельбу одной рукой. Однако вы, желтокожие, в целом слабоваты. Так что если не удержишь, то отскочи и возьмись обеими руками - многие так делают, к слову\nДумаю, если выдать тебе полноценную кирасу, как у Сеппа, то ты станешь черепахой. Так что примерь вот это - плетёный кожаный доспех. Но под прямые удары его секиры не попадай. Особенно обуха - тут не поможет даже миланский латный доспех. Понял меня?";
			link.l1 = "Да, понять. Огромный вам спасибо, господин Траст!";
			link.l1.go = "PZ_OliverTrust_13";
			//Log_Info("Вы получили кожаный корсет");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(PChar, "cirass5");
			EquipCharacterByItem(Pchar, "cirass5");
		break;
		
		case "PZ_OliverTrust_resedinsia_1":
			dialog.text = "Осторожнее с такими словами. Видимо, зря я тебе раньше времени сказал, что я собираю оружие. Но, вижу, тебя не отговорить\nХотя... всё гениальное просто, не правда ли? Никто не ждёт нападения на резиденцию средь бела дня. Поэтому\nДа, думаю, он подойдёт лучше всего. Не самое лучшее оружие на свете, но им одинаково удобно и колоть, и резать, и рубить.";
			link.l1 = "Клеванг! Знакомый вещь. Люди соседние острова часто владеть таким.";
			link.l1.go = "PZ_OliverTrust_resedinsia_2";
			pchar.questTemp.PZ_Batavia_resedinsia_Go = true;
			notification("Открыт 'Дуэлянт'", "Longway");
			SetCharacterPerk(pchar, "FencingMaster");
			SetCharacterPerk(pchar, "HT1");
		break;
		
		case "PZ_OliverTrust_resedinsia_2":
			dialog.text = "Уже пользовался таким? Вот и славно. Времени у тебя будет крайне мало, а народу нужно будет положить много. А посему\nДержи. Сам такими не пользуюсь, но отрываю эту красавицу от сердца. Картечница. Три ствола, прекрасно инкрустирована. Заряди лучше прямо сейчас, при мне - в пылу сражения у тебя не будет это сделать ни времени, ни возможности\nСам же надень вот это - простой бретерский жилет, и шансов выжить будет побольше, и двигаться в нём сможешь быстро. Практически не стесняет.";
			link.l1 = "Благодарить, господин Траст!";
			link.l1.go = "PZ_OliverTrust_13";
			//Log_Info("Вы получили клеванг");
			//Log_Info("Вы получили трёхствольный дробовик");
			//Log_Info("Вы получили жилет бретера");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(PChar, "blade_30");
			EquipCharacterByItem(Pchar, "blade_30");
			GiveItem2Character(PChar, "pistol2");
			EquipCharacterByItem(Pchar, "pistol2");
			GiveItem2Character(PChar, "cirass6");
			EquipCharacterByItem(Pchar, "cirass6");
			AddItems(Pchar, "grapeshot", 50);
			AddItems(Pchar, "gunpowder", 50);
			LAi_SetCharacterUseBullet(Pchar, GUN_ITEM_TYPE, "grapeshot");
		break;
		
		case "PZ_OliverTrust_13":
			dialog.text = "Погоди, мы ещё не закончили. В наших общих интересах, чтобы ты выжил, не правда ли? Так что возьми ещё с собой лекарств - раны зализать после битвы, да и крови если много потеряешь\nОсобенно береги это - тошнотворные вкус и запах, но сразу разлагает любой яд, попавший в твоё тело. Видишь ли, в чём дело - Сепп ван дер Винк, телохранитель и по совместительству правая рука ван Димена, смазывает своё оружие ядом. Чтобы если уж сам умер, то и противника на тот свет забрал. Он самоуверен, так что теперь у тебя ещё больше преимуществ.";
			link.l1 = "Я даже не знать, смочь ли однажды отблагодарить вас, господин Траст...";
			link.l1.go = "PZ_OliverTrust_14";
			//Log_Info("Вы получили 10 лечебных зелий");
			//Log_Info("Вы получили противоядие");
			PlaySound("interface\important_item.wav");
			AddItems(Pchar, "potion1", 10);
			AddItems(Pchar, "potion3", 1);
		break;
		
		case "PZ_OliverTrust_14":
			dialog.text = "Лучшей твоей благодарностью будет, если ты никого из нас не сдашь, ежели тебя повяжут. Хотя, скорее всего, сразу убьют. Но если ты справишься - что ж, передай этой твари, ван Димену, что своей смертью он обязан именно мне. Справишься?";
			link.l1 = "Без проблем. Благодарить вас ещё раз, господин Траст. До свидание!";
			link.l1.go = "PZ_Batavia_NaOhotu";
		break;
		
		case "PZ_Batavia_NaOhotu":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.PZ_Batavia_resedinsia_Go"))
			{
				DoQuestReloadToLocation("Batavia", "reload", "reload1", "PZ_Batavia_BitvaSoStrazhnikami");
			}
			if (CheckAttribute(pchar, "questTemp.PZ_Batavia_lubovnitsa_Go"))
			{
				DoQuestReloadToLocation("Batavia_HouseF3", "reload", "reload1", "PZ_Batavia_BitvaLubovnitsa");
			}
			if (CheckAttribute(pchar, "questTemp.PZ_Batavia_Plantation_Go"))
			{
				/*EndQuestMovie();
				sld = &Locations[FindLocation("Batavia_plantation")];
				sld.locators_radius.quest.detector4 = 3.0;
				PChar.quest.PZ_Batavia_plantation1.win_condition.l1 = "locator";
				PChar.quest.PZ_Batavia_plantation1.win_condition.l1.location = "Batavia_plantation";
				PChar.quest.PZ_Batavia_plantation1.win_condition.l1.locator_group = "quest";
				PChar.quest.PZ_Batavia_plantation1.win_condition.l1.locator = "detector4";
				PChar.quest.PZ_Batavia_plantation1.win_condition = "PZ_Batavia_plantation_selfdialog";*/
				DoQuestReloadToLocation("Batavia_plantation", "quest", "detector2", "PZ_Batavia_plantation_setguards");
			}
		break;
		
		case "PZ_Batavia_BitvaSoStrazhnikami_1":
			dialog.text = "Стоять! Куда это ты идёшь, желтокожий?";
			link.l1 = "В резиденцию.";
			link.l1.go = "PZ_Batavia_BitvaSoStrazhnikami_2";
			locCameraFromToPos(-0.44, 7.45, 24.65, true, -1.90, 5.10, 18.50);
		break;
		
		case "PZ_Batavia_BitvaSoStrazhnikami_2":
			dialog.text = "Это был риторический вопрос, гений. С чего ты взял, что туда кто-то пустит такого, как ты?";
			link.l1 = "У мой дело к господин ван Димен. Пропустить, пожалуйста.";
			link.l1.go = "PZ_Batavia_BitvaSoStrazhnikami_3";
		break;
		
		case "PZ_Batavia_BitvaSoStrazhnikami_3":
			dialog.text = "Ты знаешь имя генерал-губернатора? Что ж... расскажи, что у тебя за дело. А я передам и вернусь к тебе с ответом.";
			link.l1 = "Мой разговаривать только с господин ван Димен. Он ждать меня. Пропустить, иначе у ваш потом быть неприятности.";
			link.l1.go = "PZ_Batavia_BitvaSoStrazhnikami_4";
			locCameraSleep(true);
		break;
		
		case "PZ_Batavia_BitvaSoStrazhnikami_4":
			dialog.text = "Ну, ну, не кукарекай, узкоглазый. Будет либо по-моему, либо никак.";
			link.l1 = "Значит, неприятности у ваш быть прямо сейчас...";
			link.l1.go = "PZ_Batavia_BitvaSoStrazhnikami_5";
		break;
		
		case "PZ_Batavia_BitvaSoStrazhnikami_5":
			DialogExit();
			LAi_SetActorType(pchar);
			CharacterTurnByChr(pchar, CharacterFromID("PZ_SoldResid_1"));
			LAi_group_MoveCharacter(pchar, LAI_GROUP_PLAYER);
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			
			sld = CharacterFromID("PZ_SoldResid_1");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
				
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			
			DoQuestCheckDelay("PZ_Batavia_resedinsia_1", 0.9);
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_1":
			dialog.text = "Проклятый батрак! Кто тебя нанял?! Я заплачу тебе больше!";
			link.l1 = "Вы, белый люди, только и думать, что о золото. Драконы проклясть ваш народ. Мой прийти сам, нужен информация, но ваш люди не хотеть пускать.";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_2";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_2":
			dialog.text = "И что же тебе нужно?!";
			link.l1 = "Ферментелуш. Где он сейчас быть?";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_3";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_3":
			dialog.text = "Оливерио?.. Но на кой чёрт он тебе сдался? Я ничего тебе не скажу!";
			link.l1 = "Он убить мой семья. И похитить мой сестра. Мой вам советовать начать говорить. Для ваш благо.";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_4";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_4":
			dialog.text = "Да что ты мне сделаешь! Скоро здесь будет вся стража.";
			link.l1 = "Вы слышать про Линчи? Наказание мой народ. Означать 'Смерть Тысяча Порез'.";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_5";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_5":
			dialog.text = "Не успеешь ты мне столько порезов нанести, дубина!";
			link.l1 = "Это быть фигура речи. Казнь быть в том, что палач наносить жертва порез, один за другой. Или отрезать кусочек тела. Мы сделать, сколько успеть, если вы не начать говорить.";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_6";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_6":
			DialogExit();
			
			sld = GetCharacter(NPC_GenerateCharacter("PZ_Sepp", "mercen_26", "man", "man", sti(pchar.rank), HOLLAND, -1, false, "quest"));
			sld.name = "Сепп";
			sld.lastname = "ван дер Винк";
			GiveItem2Character(sld, "topor_04");
			EquipCharacterByItem(sld, "topor_04");
			GiveItem2Character(sld, "pistol3");
			EquipCharacterByItem(sld, "pistol3");
			sld.CantLoot = true;
			LAi_SetHP(sld, 300.0, 300.0);
			ChangeCharacterAddressGroup(sld, "Batavia_townhallRoom", "reload", "reload1");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
			
			LAi_SetStayType(pchar);
			locCameraFromToPos(-3.06, 1.64, -0.43, true, 1.87, -1.20, 2.39);
			DoQuestCheckDelay("PZ_Batavia_BitvaResidensia_7", 2.5);
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_7":
			dialog.text = "А-А-А!!! Стой! Стой, грязный нехристь. Скажу, всё скажу. Только прекрати. Сепп!.. Наконец-то! Где тебя черти носили столько времени?!";
			link.l1 = "Как невовремя...";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_8";
			SetCameraDialogMode(npchar);
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_8":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("PZ_Sepp");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_9";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_9":
			dialog.text = "Антони?.. Тебе срочно нужно к врачу! Я помогу тебе добраться туда, как только закончу здесь. Ты! Какого дьявола ты творишь, жёлтый мясник?!";
			link.l1 = "Жёлтый Мясник? Мой это даже нравится. Есть всего один вопрос. Но никто не хотеть на него отвечать...";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_10";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_10":
			dialog.text = "Какой ещё вопрос?!";
			link.l1 = "Где сейчас находиться Оливерио Ферментелуш? Может, хоть вы сказать?";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_11";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_11":
			dialog.text = "Плевал я на этого Ферментелуша! Но кто тебя снабдил деньгами и информацией?!";
			link.l1 = "Господин Оливер Траст. Кстати, он как раз просить передать, что помощь мне заодно быть месть для него.";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_12";
			
			sld = CharacterFromID("PZ_AntoniOneDimen");
			LAi_ActorSetGroundSitMode(sld);
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_12":
			dialog.text = "Траст?! Ха-ха-ха-ха-ха! Мерзкий скупердяй, решил отомстить, что мы отняли у него плантацию? Ничего, скоро и магазин, и жизнь отнимем, как только с тобой покончу.";
			link.l1 = "Ты тратить моё время.";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_13";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_13":
			DialogExit();
			LAi_SetFightMode(pchar, true);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			
			PChar.quest.PZ_Batavia_BitvaResidensia_8.win_condition.l1 = "NPC_Death";
			PChar.quest.PZ_Batavia_BitvaResidensia_8.win_condition.l1.character = "PZ_Sepp";
			PChar.quest.PZ_Batavia_BitvaResidensia_8.win_condition = "PZ_Batavia_BitvaResidensia_8";
		break;
		
		case "PZ_Batavia_PlantationSelfDialog":
			dialog.text = "(На китайском) Итак, где же мне лучше всего устроить им засаду...";
			if (CheckCharacterItem(pchar, "mushket6"))
			{
				link.l1 = "(На китайском) С этой штукой придётся подойти поближе. Ударю первым, резко и беспощадно - страх и неожиданность доделают за меня остальное.";
				link.l1.go = "Exit";
			}
			else
			{
				link.l1 = "(На китайском) Как раз здесь. Они даже сначала меня не увидят. Лучшие сражения - те, что не начинались... или закончились быстро и малой кровью.";
				link.l1.go = "Exit";
			}
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_Batavia_PlantationFight");
		break;
		
		case "PZ_Batavia_PlantationDimen1":
			if (!CharacterIsAlive("PZ_SoldPlantation_1") && !CharacterIsAlive("PZ_SoldPlantation_2") &&  !CharacterIsAlive("PZ_SoldPlantation_3") && !CharacterIsAlive("PZ_SoldPlantation_4") && !CharacterIsAlive("PZ_SoldPlantation_5") && !CharacterIsAlive("PZ_SoldPlantation_6"))
			{
				dialog.text = "Кха-кха... Мерзкий батрак... Ты - бежавший раб? Но откуда у тебя такое оружие? Тебя кто-то нанял?..";
				link.l1 = "Нет время! Говорить мне, где сейчас быть Оливерио Ферментелуш! Быстро!";
				link.l1.go = "PZ_Batavia_PlantationDimen2";
			}
			else
			{
				dialog.text = RandSwear()+"";
				link.l1 = "";
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_PlantationDimenSit");
			}
		break;
		
		case "PZ_Batavia_PlantationDimen2":
			dialog.text = "Хе-хе, кхе-кхе, ты прав... Нет времени - кровь так и хлещет из брюха. Гори в аду, нехристь...";
			link.l1 = "(На китайском) Проклятье, нет!!! Он истёк кровью...";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_Batavia_PlantationDimenDead1");
		break;
		
		case "PZ_Batavia_Plantation_DimenDeadSelfDialog":
			dialog.text = "(На китайском) Почему, за что?! Как мне теперь искать Ферментелуша?!..";
			link.l1 = "(На китайском) Но сначала нужно скрыться - наверняка кто-то успел сообщить об этом в город...";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_final";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_1":
			dialog.text = "К-китаец?! Не думал, что сюда позовут кого-то вроде, ик, тебя. Ты тоже из любителей послушать и посмотреть, да? Хе-хе.";
			link.l1 = "Почему здесь быть столько люди?.. И кто быть вы?";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_2";
			SetCameraDialogMode(npchar);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_2":
			dialog.text = "По одежде не понял? И т-тон смени, когда говоришь с самим генерал-губернатором, ик!";
			link.l1 = "Так вы быть господин ван Димен. Просить прощения, столько люди - мой не знать. Может, здесь быть карнавал с переодевания.";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_3";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_3":
			dialog.text = "И-именно так, господин, и никак иначе, ик! Карнавал с переодеваниями?! Ха-ха-ха! А ты не так уж и плох, батрак! Уверен, Люйтерсу понравится надеть платье Ветте, аха-ха!";
			link.l1 = "Люйтерс?..";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_4";
			locCameraFromToPos(-4.45, 2.11, 1.53, true, 0.47, -0.30, 2.74);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_4":
			dialog.text = "Воо-он тот тюфяк, жалкое подобие муженька и любитель подсматривать из шкафа, как сношают его дорогую жёнушку. А та и не против!";
			link.l1 = "";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_4_1";
			sld = CharacterFromID("PZ_Rubbe");
			CharacterTurnByChr(npchar, sld);
			CharacterTurnByChr(pchar, sld);
			CharacterTurnByChr(CharacterFromID("PZ_Brigitta"), sld);
			DoQuestCheckDelay("PZ_Batavia_BitvaLubovnitsa_4", 2.5);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_4_1":
			Event("QuestDelayExit","sl", "", 0);
			dialog.text = "Верно, Ветте, дорогая моя? Хе-хе.";
			link.l1 = "(На китайском) Какого чёрта здесь происходит...";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_5";
			sld = CharacterFromID("PZ_Rubbe");
			CharacterTurnByChr(npchar, CharacterFromID("PZ_Brigitta"));
			CharacterTurnByChr(pchar, npchar);
			CharacterTurnByChr(CharacterFromID("PZ_Brigitta"), npchar);
			locCameraFromToPos(-2.21, 1.90, 2.26, true, -0.81, -0.40, 4.36);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_5":
			dialog.text = "Не знаю, что ты там, ик, сказал, но судя по твоему взгляду и тону, ты со мной п-полностью согласен! Ван Хаан - чёртов извращенец\nТак кто ты, батрак? Тебя Ветте пригласила?";
			link.l1 = "Мой...";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_6";
			CharacterTurnByChr(pchar, npchar);
			CharacterTurnByChr(npchar, pchar);
			CharacterTurnByChr(CharacterFromID("PZ_Brigitta"), pchar);
			locCameraFromToPos(-4.45, 2.11, 1.53, true, 0.47, -0.30, 2.74);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_6":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("PZ_Sepp");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Batavia_BitvaLubovnitsa_7";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_7":
			dialog.text = "Приглашать к себе батрака - даже для Ветте слишком. Очевидно же, он заблудился и зашёл не туда\nЭй, ты. Уходи отсюда и забудь обо всём, что здесь видел. Кто твой господин? Мы с ним свяжемся, и вам обоим заплатят за молчание. Может быть, тебе даже позволят вернуться к родным на континент. Отвечай и выходи.";
			link.l1 = "На самом деле, мой зайти сюда по дело.";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_8";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_8":
			dialog.text = "Хех, дело. 'Делом' здесь занимается только минхер ван Димен. Я его охраняю от таких, как ты. Ну а Люйтерс... Люйтерс - как всегда\nИли... тебя и правда пригласила Ветте?..";
			link.l1 = "Нет, я здесь, чтобы...";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_9";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_9":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("PZ_Rubbe");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Batavia_BitvaLubovnitsa_10";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_10":
			dialog.text = "Стала бы моя дражайшая Ветте приглашать сюда желтозадого! Убирайся отсюда!!!";
			link.l1 = "Жалкий рогоносец...";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_11";
			link.l2 = "С тобой никто не разговаривать. Закрыть свой рот. Не отрастить ни член, ни достоинство.";
			link.l2.go = "PZ_Batavia_BitvaLubovnitsa_12";
			GiveItem2Character(npchar, "blade_06");
			EquipCharacterByItem(npchar, "blade_06");
			LAi_SetActorType(npchar);
			npchar.model.animation = "man";
			Characters_RefreshModel(npchar);
			SetCameraDialogMode(npchar);
			locCameraToPos(-1.88, 1.72, 0.27, false);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_11":
			dialog.text = "Ро-ро-рогоносец?! Не-е-ет, я люблю её больше себя. Ха, тупому китайцу вроде тебя этого не понять!";
			link.l1 = "(На китайском) Больной ублюдок.";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_13";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_12":
			dialog.text = "Ч-ч-член?! В-всё у меня в порядке с членом! Да! Я просто уже знаю, что другие мужчины доставляют моей дорогой Ветте больше удовольствия, вот и всё!!";
			link.l1 = "Как говорить на мой Родина, мужчина оставаться мужчина, пока у него есть всего один палец. Будь ты мужчина, ты бы это знать.";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_13";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_13":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("PZ_Brigitta");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Batavia_BitvaLubovnitsa_14";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_14":
			dialog.text = "Я его, конечно, не приглашала, но, знаете, он вполне себе ничего. Может задержаться, когда вы все уйдёте\nС нашей собакой я уже пробовала, а вот с жёлтой макакой у меня ещё ни разу не было...";
			link.l1 = "Молчать, потаскуха, когда мужчины разговаривать! Из животных здесь быть только ты. Я здесь по делу. Мой искать Оливерио Ферментелуш. Вы быть друзья. Вы не подсказать мне, где он мочь быть, господин ван Димен?";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_15";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_15":
			dialog.text = "Антони, он меня оскорбил! Оскорбил!! Ты же не оставишь это так?!";
			link.l1 = "...";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_16";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_16":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("PZ_AntoniOneDimen");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Batavia_BitvaLubovnitsa_17";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_17":
			dialog.text = "Хе-хе, извини, ик, приятель, но дама рассержена. П-придётся дать тебе урок хороших манер. Урок первый!..";
			link.l1 = "Но вы мочь мне помочь с поиски Оливерио?..";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_18";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_18":
			dialog.text = "Мёртвому батраку это ничем не поможет.";
			link.l1 = "(На китайском) Чтоб вас всех...";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_19";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_19":
			DialogExit();
			EndQuestMovie();
			InterfaceStates.Buttons.Save.enable = false;
			
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			LAi_SetFightMode(pchar, true);
			PlaySound("Voice\Russian\hambit\Longway-02.wav");
			
			sld = CharacterFromID("PZ_AntoniOneDimen");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			sld = CharacterFromID("PZ_Sepp");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			sld = CharacterFromID("PZ_Rubbe");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_Batavia_BitvaLubovnitsa_3");
			
			sld = CharacterFromID("PZ_Brigitta");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload2", "none", "", "", "", -1);
			PlaySound("People Fight\Peace_woman_death_05.wav");
			DoQuestCheckDelay("PZ_Batavia_BitvaLubovnitsa_5", 3.0);	//Нужно ещё раз, а то не бежит
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_21":
			dialog.text = "(На китайском) Проклятье! Мне так и не удалось ничего выяснить!";
			link.l1 = "(На китайском) Я нескоро забуду этот день... Нужно сматываться, пока сюда не нагрянула стража. Хотя не то чтобы их беспокоил шум, доносившийся из этого дома душевнобольных...";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_final";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_14":
			dialog.text = "(На китайском) Боги прокляли этот день! Ван Димен испустил дух, пока я возился с его подручным!..";
			link.l1 = "(На китайском) Стража идёт. Чувствую, придётся отсюда прорываться с боем...";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_final";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_final":
			DialogExit();
			RemoveCharacterEquip(PChar, GUN_ITEM_TYPE);
			RemoveCharacterEquip(PChar, MUSKET_ITEM_TYPE);
			if (CheckAttribute(pchar, "questTemp.PZ_Batavia_resedinsia_Go"))
			{
				TakeItemFromCharacter(pchar, "blade_30");
				TakeItemFromCharacter(pchar, "pistol2");
			}
			if (CheckAttribute(pchar, "questTemp.PZ_Batavia_lubovnitsa_Go"))
			{
				TakeItemFromCharacter(pchar, "blade_26");
				TakeItemFromCharacter(pchar, "pistol8");
			}
			if (CheckAttribute(pchar, "questTemp.PZ_Batavia_Plantation_Go"))
			{
				TakeItemFromCharacter(pchar, "mushket6");
				TakeItemFromCharacter(pchar, "mushket2x2");
			}
			EquipCharacterByItem(Pchar, "blade_11");
			pchar.model = "Longway";
			pchar.model.animation = "Longway";
			Characters_RefreshModel(pchar);
			
			
			SetCurrentTime(2, 30);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("Формоза"+ NewStr() +"26 июля 1645 года", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("Formosa", "goto", "goto7", "PZ_Formosa2_Start");
			LaunchFrameForm();
		break;
		
		case "PZ_Formosa_smuggler_21":
			dialog.text = "Да это же Чанг-Чанг! Ну, и с чем тебе нужна помощь на этот раз, мой маленький друг?";
			link.l1 = "Чанг Т... с чего ваш это взять?";
			link.l1.go = "PZ_Formosa_smuggler_22";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_Formosa_smuggler_22":
			dialog.text = "Ты ведь так и сочишься презрением ко мне. Так что ни за что бы не подошёл, не будь тебе что-то нужно.";
			link.l1 = "Вы знать, где господин ван Мерден? Он в город? Его не быть дома. Мой нужно поговорить с ним.";
			link.l1.go = "PZ_Formosa_smuggler_23";
		break;
		
		case "PZ_Formosa_smuggler_23":
			dialog.text = "Человеку из дому нельзя выйти, он должен денно и нощно дожидаться одного единственного желтокожего? А если серьёзно - дела у него на острове. Ночью вернётся в город, не переживай. Бывай, Чанг-Чанг!";
			link.l1 = "Благодарить. До свидание.";
			link.l1.go = "PZ_Formosa_smuggler_24";
		break;
		
		case "PZ_Formosa_smuggler_24":
			SetCurrentTime(1, 30);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			DoQuestReloadToLocation("Formosa", "goto", "goto7", "PZ_Formosa2_IshemMerden_3");
		break;
		
		case "PZ_Formosa_bandit_1":
			dialog.text = "Эй, узкоглазый, куда это ты так спешишь, да ещё в такое время? Все приличные люди уже спят в это время.";
			link.l1 = "Тогда что ваш делать здесь в такой время?";
			link.l1.go = "PZ_Formosa_bandit_2";
		break;
		
		case "PZ_Formosa_bandit_2":
			dialog.text = "Хорошо сказано, хоть и вопросом на вопрос! Да вот бегает тут по городу один желтозадый, вынюхивает что-то, людей достаёт - многим это не нравится.";
			link.l1 = "И кто же это не нравиться, сказать на милость?";
			link.l1.go = "PZ_Formosa_bandit_3";
		break;
		
		case "PZ_Formosa_bandit_3":
			dialog.text = "Хех, знаешь, да проще сказать, кому бы это вообще понравилось. Ну да ладно, довольно разговоров - и правда спать уже хочется.";
			link.l1 = "Не волноваться - скоро ваш спать вечный сон...";
			link.l1.go = "PZ_Formosa_bandit_4";
		break;
		
		case "PZ_Formosa_bandit_4":
			DialogExit();
			EndQuestMovie();
			InterfaceStates.Buttons.Save.enable = false;
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("PZ_JohanVanMerden");
			ChangeCharacterAddressGroup(sld, PChar.location, "patrol", "patrol7");
			GiveItem2Character(sld, "blade_31");
			EquipCharacterByItem(sld, "blade_31");
			LAi_SetActorType(sld);
			
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("PZ_FormosaBandit_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_Formosa2_IshemMerden_7");
			
			DoQuestCheckDelay("PZ_Formosa2_IshemMerden_6", 10.0);
		break;
		
		case "PZ_Formosa_JohanVanMerden_21":
			dialog.text = "Чанг Ту, ты в порядке?";
			link.l1 = "Господин ван Мерден! Мой бы справиться, благодарить, что вмешались. Но вы быть порядок? Это самый важный вопрос сейчас.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_22";
		break;
		
		case "PZ_Formosa_JohanVanMerden_22":
			dialog.text = "Всегда думаешь о других, не правда ли? Это у нас общее. Так что я не стал стоять в стороне, когда увидел, как они на тебя напали, хоть и, конечно, знал, что ты их без труда одолеешь\nОтвечая на твой вопрос - я в порядке, спасибо. Устал, правда - ноги уже ватные. А правды в них нет. Пройдём, с твоего позволения, в дом? Там и поговорим.";
			link.l1 = "Конечно, господин ван Мерден, не спрашивать - это ведь быть ваш дом.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_23";
		break;
		
		case "PZ_Formosa_JohanVanMerden_23":
			DoQuestReloadToLocation("Formosa_houseSp1", "goto", "goto1", "PZ_Formosa2_IshemMerden_8");
		break;
		
		case "PZ_Formosa_JohanVanMerden_24":
			dialog.text = "Ну, теперь можем и поговорить, без спешки, в тишине и спокойствии. Рассказывай, что тебя привело ко мне, Чанг Ту?";
			link.l1 = "Вы быть правы, господин ван Мерден. Я только что вернуться с Батавия, и...";
			link.l1.go = "PZ_Formosa_JohanVanMerden_25";
		break;
		
		case "PZ_Formosa_JohanVanMerden_25":
			dialog.text = "Подожди. Неужели бедняжка Чанг Шин?..";
			link.l1 = "Что вы, нет! Надеяться, что нет. Небо всё ещё хранить её судьба в тайне от меня. Как и... местоположение Ферментелуш. На Батавия его не быть. От ван Димен не оказаться никакой толк.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_26";
		break;
		
		case "PZ_Formosa_JohanVanMerden_26":
			dialog.text = "Ещё бы он стал тебе помогать, ведь они с Оливерио - старые друзья. Как говорят англичане, друзья и партнёры по преступлениям. Я был бы удивлён, если бы он тебе что-то сказал\nСкажи мне, а другой Оливерио, Оливер Траст, оказал тебе возможную помощь, как я его попросил?";
			link.l1 = "Да. Большой спасибо и ваш, и он. Благодаря помощь Траст, мой заполучить хороший оружие. Я напасть на ван Димен, чтобы допросить он и узнать, где быть Ферментелуш. Но он умереть в битва до того, как я что-то узнать...";
			link.l1.go = "PZ_Formosa_JohanVanMerden_28";
		break;
		
		case "PZ_Formosa_JohanVanMerden_28":
			dialog.text = "Впечатляет. Вижу, ты понимаешь, что люди не всегда хотят чем-то поделиться. Поэтому есть и другие... способы убеждения, скажем так. Я думал, что ты узнал о гибели сестры, и потому устроил бойню на острове\nНо что же привело тебя ко мне теперь? Я ведь ещё тогда сказал, что не знаю, где точно бывает Ферментелуш, помимо его периодических визитов на Батавию. А последняя ниточка в лице ван Димена утрачена...";
			link.l1 = "Но ведь вы многое знать! И многих знать. Чанг Ту решить, что вы смочь снова помочь, поспрашивать о Ферментелуш. Как тогда. Вы быть первый белый человек, который хорошо обойтись с мой. Первый... белый друг.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_29";
		break;
		
		case "PZ_Formosa_JohanVanMerden_29":
			dialog.text = "Вот как...";
			link.l1 = "Господин ван Мерден, почему вы так широко улыбаться?..";
			link.l1.go = "PZ_Formosa_JohanVanMerden_30";
		break;
		
		case "PZ_Formosa_JohanVanMerden_30":
			dialog.text = "А? Извини, Чанг Ту. Старею, становлюсь сентиментальным и меланхоличным с возрастом. Это искренняя улыбка, и поэтому я не смог её скрыть. Я рад, что ты считаешь меня другом\nИ, раз уж мы с тобой друзья, я тоже рассчитываю, что время от времени и ты будешь мне помогать. В свою очередь, я обязательно помогу тебе с Ферментелушем. О, не смотри так - не нужно думать, что ты попал в ловушку.";
			link.l1 = "Хм, помогать как?";
			link.l1.go = "PZ_Formosa_JohanVanMerden_31";
		break;
		
		case "PZ_Formosa_JohanVanMerden_31":
			dialog.text = "О, с последней нашей встречи я продолжил и углубился в изучении вашего языка. И вашей культуры, особенно медицины\nЯ бы хотел, чтобы ты иногда мне находил соответствующие таблички. Платить за них буду не менее щедро, чем за... другого рода просьбы. И, надеюсь, мы будем иногда с тобой практиковаться в беседах на китайском - слуг мне об этом просить стыдно. Но вот друга...";
			link.l1 = "Чанг Ту сделать всё возможное, господин ван Мерден.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_32";
		break;
		
		case "PZ_Formosa_JohanVanMerden_32":
			dialog.text = "Хорошо. Нам с тобой предстоит... долгий путь, друг мой. Долгий путь. Ха! Мне кажется, тебе это будет хороший псевдоним, чтобы никто не узнал твоего настоящего имени. На голландском это будет Ланге Афстанд. Англичане же говорят Лон Уэй. Что тебе больше по душе?";
			link.l1 = "Мой больше нравиться английский вариант. Лонг. Вэй. Лонг Вэй... Лонгвэй. Звучать вполне в духе мой язык. Благодарить, что выслушать, господин ван Мерден. Лонгвэй ждать от вас вести. И быть готов оказать помощь и выполнить поручения.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_33";
		break;
		
		case "PZ_Formosa_JohanVanMerden_33":
			DialogExit();
			
			SetCurrentTime(15, 00);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			DeleteAttribute(pchar, "questTemp.lockedMusic");
			
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			PChar = GetMainCharacter();
			LAi_SetPlayerType(PChar);
			
			bQuestDisableMapEnter = true;
			pchar.GenQuest.CabinLock = true;
			QuestToSeaLogin_Launch();
			QuestToSeaLogin_PrepareLoc("Guadeloupe", "Quest_Ships", "Quest_ship_8", false);
			DoQuestCheckDelay("PZ_SegodnyaVremya_2", 5.0);
		break;
		
		// Этап 3, СЛЕД ЗВЕЗДЫ
		case "PZ_Longway_PosleRasskaza":
			dialog.text = "Кстати, об архив. Он у вас быть с собой, господин капитан? Достаточно только архив - шифр Лонгвэй знать наизусть.";
			if (CheckCharacterItem(pchar, "MerdokArchive"))
			{
				notification("Все навыки +", "Longway");		//All Skills +
				AddCharacterExpToSkill(npchar, "Leadership", 50);
				AddCharacterExpToSkill(npchar, "FencingLight", 50);
				AddCharacterExpToSkill(npchar, "Fencing", 50);
				AddCharacterExpToSkill(npchar, "FencingHeavy", 50);
				AddCharacterExpToSkill(npchar, "Pistol", 50);
				AddCharacterExpToSkill(npchar, "Fortune", 50);
				AddCharacterExpToSkill(npchar, "Sneak", 50);
				AddCharacterExpToSkill(npchar, "Sailing", 50);
				AddCharacterExpToSkill(npchar, "Accuracy", 50);
				AddCharacterExpToSkill(npchar, "Cannons", 50);
				AddCharacterExpToSkill(npchar, "Grappling", 50);
				AddCharacterExpToSkill(npchar, "Defence", 50);
				AddCharacterExpToSkill(npchar, "Repair", 50);
				AddCharacterExpToSkill(npchar, "Commerce", 50);	
				
				link.l1 = "Да, я решил, что однажды он мне ещё пригодится.";
				link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_1";
			}
			else
			{
				link.l1 = "К сожалению, нет. Получается, мы теперь не сможем найти твою сестру?";
				link.l1.go = "PZ_Longway_PosleRasskaza_2";
			}
		break;
		
		case "PZ_Longway_PosleRasskaza_2":
			dialog.text = "Лонгвэй очень приятно, что господин капитан беспокоиться. Пока что шанс быть - мой найти новый зацепка на Гваделупа.";
			link.l1 = "Ну хорошо. Расскажи тогда как раз, что там с тобой произошло-то.";
			link.l1.go = "PZ_Longway_PosleRasskaza_3";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_1":
			dialog.text = "Это быть верный решение. Возможно, мы найти там что-то, что помочь нам в поиски Чанг Шин.";
			link.l1 = "Было бы неплохо. Давай тогда его изучим прямо сейчас.";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_2";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_2":
			dialog.text = "Да. Давать изучать вместе. Так, год быть... Тысяча шесть сотня тридцать и семь. Антони ван Димен продавать... продавать...";
			link.l1 = "Рабов, верно?";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_3";
			AddQuestRecordInfo("PZ_ArchiveOneMerden", "1");
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_3":
			dialog.text = "Женщины мой народ для богатый белый люди.";
			link.l1 = "Это, конечно, ужасно.";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_4";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_4":
			dialog.text = "Господин капитан даже не удивиться. Неужели ваш ни капля не жалко весь этот женщины?..";
			link.l1 = "Лонгвэй. Жалко, конечно. Искренне. Просто, как человек белый, я вижу всю эту грязь изнутри. Я всегда был защитником женщин. И дамским угодником. Хорошо тогда, что ты убил ван Димена - без сомнений, он это заслужил. Что там говорится дальше?";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_5";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_5":
			dialog.text = "Ван Димен сотрудничать только с те, кто очень доверять - Сепп ван дер Винк, его правый рука. Этот проклятый Оливерио Ферментелуш. И... И...";
			link.l1 = "Что такое? Ты как-то побледнел, Лонгвэй.";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_6";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_6":
			dialog.text = "Йохан ван Мерден...";
			link.l1 = "Ох. Сочувствую. Это ужасно, но почему ты так удивлён? Ты же говорил, что вырывал ранее все листки, где упоминался Ферментелуш. Разве ты уже не находил там упоминаний о ван Мердене?";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_7";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_7":
			dialog.text = "Лонгвэй тогда очень торопиться и легко мочь упустить некоторый важный листы вроде этот.";
			link.l1 = "Понимаю. Как будешь готов - давай дальше искать и читать то, что нам сейчас могло бы пригодиться.";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_8";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_8":
			dialog.text = "Вот как они это проворачивать - Ферментелуш посылать на поимки женщина свой люди, который он время от время уничтожать и заменять. Ван Мерден отправлять их в Батавия, где ван дер Винк и ван Димен продавать наш женщина белый человек. Если бы я только узнать об этом раньше...";
			link.l1 = "Не вини себя, Лонгвэй. Ты не мог этого знать. Да и архив попал к тебе в руки относительно недавно, когда ты уже вовсю жил здесь. Может, там что-то ещё говорится про ван Мердена?";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_9";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_9":
			dialog.text = "Да. Они заниматься это почти десять лет!.. Сколько женщина потерять семья, честь, надежда... Но затем Ферментелуш перестать выходить с ван Мерден на связь. Лишь поэтому он помочь мой, когда узнать, что я искать Ферментелуш - потому что прийти время избавиться от его.";
			link.l1 = "Какие ещё подробности их грязного дела тут записаны?";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_10";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_10":
			dialog.text = "Скорее, грязный мысли чёрный сердце ван Мерден. Он узнать, что ван Димен обманывать его по поводу деньги. Поэтому отправить меня в Батавия - надеяться... надеяться, что мой умереть там, но забрать ван Димен с собой.";
			link.l1 = "Это очень неприятно.";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_11";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_11":
			dialog.text = "Всё быть ещё хуже. Это ван Мерден отправить те наёмники к его дом, чтобы убить мой. И помочь, когда понять, что я скоро одолеть их сам.";
			link.l1 = "Расчётливо, ничего не скажешь.";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_12";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_12":
			dialog.text = "Он думать, что я узнать о его вина. И прийти покарать. Когда мы разговаривать, он нацелить на мой свой пистоль под стол. А когда я назвать его свой первый белый друг, то едва не начать смеяться...";
			link.l1 = "Ох, сочувствую, Лонгвэй. Ужасно осознавать, что те, кого мы считали друзьями, смеются над нами за нашими спинами.";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_13";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_13":
			dialog.text = "Лонгвэй... узнать кое-что некоторый время назад. Незадолго до прибытие на этот Архипелаг, мой поймать португальцы. Хотеть повесить. Господин Роденбург спасти меня.";
			link.l1 = "Так ты и попал к нему на службу? Лукас тоже был в тех водах?";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_14";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_14":
			dialog.text = "Верно. И не только он - все мы. Ван Берг тоже когда-то. Ван Мерден сказать мне, что это он помочь и посоветовать Роденбург спасти мой\nОдин сомнительный источник сказать Лонгвэй, что на самом дело это Йохан и отправить португальцы за мой. Я не поверить. Но теперь понимать, что, похоже, это быть правда...";
			link.l1 = "Отвратительно.";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_15";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_15":
			dialog.text = "Но сомнения поселиться мой сердце уже тот день. Поэтому, когда я узнать, что господин капитан и ван Мерден противостоять друг друг, Лонгвэй вспомнить ваш доброта. И принять ваш сторона.";
			link.l1 = "Это было верным решением, Лонгвэй. Хех, получается, что всё это время твоим первым настоящим белым другом был я.";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_16";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_16":
			dialog.text = "Получаться так, господин капитан. Теперь мой понимать. Ван Мерден говорить мне, что мой быть его друг. Но на деле Лонгвэй быть для его не больше, чем ещё один батрак - лишь более полезный, чем любой другой\nЭто всё. Другие страницы быть посвящены бухгалтерия, а также ван Берг и Роденбург.";
			link.l1 = "Понятно. Тогда расскажи, что ты делал на Гваделупе.";
			link.l1.go = "PZ_Longway_PosleRasskaza_3";
		break;
		
		case "PZ_Longway_PosleRasskaza_3":
			dialog.text = "Там я искать 'Утренняя звезда' - на один из вырванный лист архив говориться, что последний разы её видеть то там, то на Сент-Кристофер.";
			link.l1 = "Почему именно туда? Мы ведь договорились встретиться на Гваделупе, да и нашёл я тебя там.";
			link.l1.go = "PZ_Longway_PosleRasskaza_4";
		break;
		
		case "PZ_Longway_PosleRasskaza_4":
			dialog.text = "Потому что Сент-Кристофер жить Жорж Гравель - один из информатор ван Мерден. Жорж считать, что мой всё ещё работать на Йохан. Более того, однажды Гравель совершить один тяжёлый проступок по отношению к ван Мерден. А Лонгвэй помочь это скрыть.";
			link.l1 = "И какой же проступок это был?";
			link.l1.go = "PZ_Longway_PosleRasskaza_5";
		break;
		
		case "PZ_Longway_PosleRasskaza_5":
			dialog.text = "Это не быть важно. Важно то, что Жорж стать должник Лонгвэй. Поэтому мой идти туда - в церковь, где Гравель работать помощник жрец. Господин капитан готов слушать дальше? Он выглядеть немного рассеянно.";
			link.l1 = "Извини, отвлёкся. Да, конечно, продолжай, Лонгвэй.";
			link.l1.go = "PZ_Longway_PosleRasskaza_6";
		break;
		
		case "PZ_Longway_PosleRasskaza_6":
			DialogExit();
			SetCurrentTime(9, 00);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			SetMainCharacterIndex(GetCharacterIndex("Longway"));
			PChar = GetMainCharacter();
			LAi_SetPlayerType(PChar);
			
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("Капстервиль"+ NewStr() +"Остров Сент-Кристофер", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("Kapstervil", "patrol", "patrol12", "PZ_Kapstervil_Start");
			LaunchFrameForm();
		break;
		
		case "PZ_Zhorzh_1":
			dialog.text = "Отлично, вы не опоздали. Не хотелось бы здесь торчать больше необходимого, знаете ли! Что вам понадобилось на этот раз, Лонгвэй?";
			link.l1 = "Сменить тон, Гравель. Организация требоваться ваш работа.";
			link.l1.go = "PZ_Zhorzh_2";
		break;
		
		case "PZ_Zhorzh_2":
			dialog.text = "Признаться, я уже давно не получал от них никаких вестей и приказов. Уж не забыли ли они про меня вовсе?";
			link.l1 = "О, я мочь им напомнить. Например, рассказать господин ван Мерден о твой поступок.";
			link.l1.go = "PZ_Zhorzh_3";
		break;
		
		case "PZ_Zhorzh_3":
			dialog.text = "Ладно-ладно, я понял, не кипятитесь. Так чем могу служить?";
			link.l1 = "Другой дело. Мой требоваться информация о корабль 'Утренняя звезда'. Любой. Но чем быть больше - тем лучше.";
			link.l1.go = "PZ_Zhorzh_4";
		break;
		
		case "PZ_Zhorzh_4":
			dialog.text = "Конечно, но на это понадобится время! Особенно в текущих условиях. Два дня! Э-э, как минимум.";
			link.l1 = "Почему быть так долго? Что за условия такой?";
			link.l1.go = "PZ_Zhorzh_5";
		break;
		
		case "PZ_Zhorzh_5":
			dialog.text = "Понадобится много денег, чтобы развязать языки, кому нужно. Я мог бы взять из пожертвований наших прихожан, вот только нас недавно ограбили! Святой отец, конечно, объявит о сборе новых, но ещё у нас протекла крыша! На её ремонт уйдёт немало средств из этих новых пожертвований.";
			link.l1 = "Два день. Я не мочь находиться здесь целый вечность! У мой нет столько время. Лонгвэй не славиться терпение. Господин ван Мерден - тем более. Или твой об этом напомнить, Гравель?";
			link.l1.go = "PZ_Zhorzh_6";
		break;
		
		case "PZ_Zhorzh_6":
			dialog.text = "Я не могу влиять на то, что от меня не зависит! Сделаю, что могу. Я бы разузнал всё гораздо быстрее, если бы вы нашли этих разбойников и вернули нам все пожертвования!";
			link.l1 = "Мой подумать об это. Твой же начать поиск. Два день. Не больше. Встречаться этот же время и место.";
			link.l1.go = "PZ_Zhorzh_7";
		break;
		
		case "PZ_Zhorzh_7":
			DialogExit(); 
			SetCurrentTime(12, 00);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("День спустя"+ NewStr() +"В поисках грабителей", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("Kapstervil_Jungle", "goto", "goto1", "PZ_Kapstervil_Jungle");
			LaunchFrameForm();
		break;
		
		case "PZ_VorugaChurch_1":
			dialog.text = "Ого, не думал, что увижу у нас на острове узкоглазого! Бежал от хозяев, да, батрак? От кого же, если не секрет?";
			link.l1 = "Мой - свободный человек.";
			link.l1.go = "PZ_VorugaChurch_2";
		break;
		
		case "PZ_VorugaChurch_2":
			dialog.text = "Ну-у-у, уже да, в любом случае, ха-ха-ха! Ладно, не хочешь - не говори. Мужик ты коренастый, крепкий. Сразу видно - толковый, пусть и узкоглазый. Не хочешь к нам в банду? Всё равно тебе вряд ли есть куда податься.";
			link.l1 = "Лонгвэй думать, что ваш попытаться ограбить его, а не предложить вступить банда.";
			link.l1.go = "PZ_VorugaChurch_3";
		break;
		
		case "PZ_VorugaChurch_3":
			dialog.text = "Считай, что тебе повезло. Мы недавно ограбили церковь в городе, ты представляешь?! А что? Воровать у воров - не воровство.";
			link.l1 = "Я не собираться искать ваш сам. Но рад, что вы мне попасться.";
			link.l1.go = "PZ_VorugaChurch_4";
		break;
		
		case "PZ_VorugaChurch_4":
			dialog.text = "Искать?.. А-а-а, так ты наёмник, а не батрак... Теперь понятно.";
			link.l1 = "Именно.";
			link.l1.go = "PZ_VorugaChurch_5";
		break;
		
		case "PZ_VorugaChurch_5":
			DialogExit();
			EndQuestMovie();
			InterfaceStates.Buttons.Save.enable = false;
			
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			LAi_SetCheckMinHP(npchar, 1, true, "PZ_VorugaChurch_win");
			for (i=11; i<=14; i++)
			{
				sld = CharacterFromID("PZ_KapstervilBandit_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
		break;
		
		case "PZ_VorugaChurch_6":
			if (!CharacterIsAlive("PZ_KapstervilBandit_11") && !CharacterIsAlive("PZ_KapstervilBandit_12") && !CharacterIsAlive("PZ_KapstervilBandit_13"))
			{
				dialog.text = "Кхе... Почему не убил сразу? Что тебе нужно от меня? Неужто поведёшь в тюрьму?";
				link.l1 = "Мой это не нужно. Сказать, куда ваш деть золото церковь.";
				link.l1.go = "PZ_VorugaChurch_7";
			}
			else
			{
				dialog.text = RandSwear()+"";
				link.l1 = "";
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_VorugaChurch_win");	
			}
		break;
		
		case "PZ_VorugaChurch_7":
			dialog.text = "Хе-хе... Никогда ещё фраза 'Пёс Господень' не играла такими яркими красками! Чёртов желтозадый...";
			link.l1 = "Лонгвэй терять терпение. Он всё равно узнать. Вопрос лишь, как долго ваш страдать.";
			link.l1.go = "PZ_VorugaChurch_8";
			LAi_group_Delete("EnemyFight");
		break;
		
		case "PZ_VorugaChurch_8":
			dialog.text = "Хорошо, хорошо... Пещера. Мы всё сложили там. Деньги твои. Только не убивай, ладно?";
			link.l1 = "Мой сказать 'как долго страдать'. А не что страданий не быть вовсе...";
			link.l1.go = "PZ_VorugaChurch_9";
		break;
		
		case "PZ_VorugaChurch_9":
			DialogExit();
			
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "Shot", "1", 1.5);
			DoQuestCheckDelay("PZ_VorugaChurch_win_2", 0.9);
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_0":
			StartQuestMovie(true, false, true);
			locCameraFromToPos(2.48, 0.87, 9.26, true, 6.72, -0.85, 6.05);
			dialog.text = "(На китайском) Вот и схрон бандитов!";
			link.l1 = "";
			link.l1.go = "PZ_Kapstervil_GrotSoldiers_0_1";
			CharacterTurnToLoc(pchar, "box", "box1");
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_0_1":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "goto", "goto2", "PZ_Kapstervil_Grot_1", -1);
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_1":
			dialog.text = "(На китайском) Сколько же здесь всего!";
			link.l1 = "";
			link.l1.go = "PZ_Kapstervil_GrotSoldiers_1_1";
			CharacterTurnToLoc(pchar, "box", "box1");
			locCameraFromToPos(6.83, 2.65, 6.62, true, 2.83, -1.00, 7.67);
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_1_1":
			dialog.text = "(На китайском) Я слышу шаги...";
			link.l1 = "(На китайском) Здесь есть кто-то ещё...";
			link.l1.go = "PZ_Kapstervil_GrotSoldiers_2";
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_2":
			DialogExit();
			
			sld = GetCharacter(NPC_GenerateCharacter("PZ_Kapstervil_GrotSoldier_1", "sold_fra_7", "man", "man", 5, FRANCE, -1, true, "soldier"));
			LAi_SetActorType(sld);
			sld.CantLoot = true;
			ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto4");
			TeleportCharacterToPosAy(sld, 4.17, 0.65, -1.42, 0.00);
			
			sld = GetCharacter(NPC_GenerateCharacter("PZ_Kapstervil_GrotSoldier_2", "sold_fra_5", "man", "man", 5, FRANCE, -1, true, "soldier"));
			LAi_SetActorType(sld);
			sld.CantLoot = true;
			ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto4");
			TeleportCharacterToPosAy(sld, 4.10, 0.65, 0.30, 3.00);
			
			LAi_SetStayType(pchar);
			LAi_Fade("PZ_Kapstervil_Grot_2", "");
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_3":
			dialog.text = "Что мы вообще здесь забыли? Тут же нет никого - мы проследили, чтобы все грабители вышли.";
			link.l1 = "";
			link.l1.go = "exit";
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("PZ_Kapstervil_GrotSoldier_2"));
			AddDialogExitQuest("PZ_Kapstervil_Grot_4");
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_5":
			dialog.text = "В этом и смысл, дубина! Они вернутся, а мы им устроим горячий приём.";
			link.l1 = "";
			link.l1.go = "exit";
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("PZ_Kapstervil_GrotSoldier_1"));
			AddDialogExitQuest("PZ_Kapstervil_Grot_5");
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_7":
			dialog.text = "Осмотрюсь, что ли - может, тут кто-то остался. А то от тоски помереть уже готов...";
			link.l1 = "";
			link.l1.go = "PZ_Kapstervil_GrotSoldiers_8";
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("PZ_Kapstervil_GrotSoldier_2"));
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_8":
			DialogExit();
			LAi_Fade("PZ_Kapstervil_Grot_5_1", "");
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_9":
			dialog.text = "(На китайском) Солдаты! Как некстати... И что же мне теперь делать?";
			link.l1 = "(На китайском) Мне эти деньги пригодятся куда больше, чем белым солдафонам! Я без них никуда не уйду!";
			link.l1.go = "PZ_Kapstervil_GrotSoldiers_10";
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_10":
			DialogExit();
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			
			for (i=1; i<=2; i++)
			{
				sld = CharacterFromID("PZ_Kapstervil_GrotSoldier_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyWithRadius");
				LAi_group_SetRelation("EnemyWithRadius", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
				LAi_group_SetLookRadius("EnemyWithRadius", 6.0);
				LAi_group_SetHearRadius("EnemyWithRadius", 2.0);
				LAi_group_SetSayRadius("EnemyWithRadius", 12.0);
				LAi_group_SetCheck("EnemyWithRadius", "PZ_Kapstervil_Grot_6");
			}
		break;
		
		case "PZ_Zhorzh_11":
			dialog.text = "Вот вы и пришли, месье Лонгвэй!";
			link.l1 = "Конечно, иначе быть не мочь. Твой надеяться на обратное? Ты узнать что-нибудь об 'Утренняя звезда', Жорж?";
			link.l1.go = "PZ_Zhorzh_12";
		break;
		
		case "PZ_Zhorzh_12":
			dialog.text = "Да, месье. Это тяжёлый галеон под началом испанца, он...";
			link.l1 = "Он быть португалец. Вы, белый люди, даже сами друг друг не мочь отличить.";
			link.l1.go = "PZ_Zhorzh_13";
		break;
		
		case "PZ_Zhorzh_13":
			dialog.text = "А, да? Впрочем, неважно. Ну так вот! Он изменил тяжёлый галеон до неузнаваемости. Решил в торговцы податься - пушки поставил малокалиберные, людей стал меньше набирать. А вот трюм расширил. Набивает его до отказа, корабль еле плывёт.";
			link.l1 = "Решил начать новый жизнь, значит? Хорошо. Что ещё твой узнать? Где мой мочь его найти?";
			link.l1.go = "PZ_Zhorzh_14";
		break;
		
		case "PZ_Zhorzh_14":
			dialog.text = "С этим уже сложнее. Он постоянно перемещается между нашими и английскими колониями, но только среди Наветренных Островов. Однако мне удалось узнать, что он с большим грузом вина направился в Бас-Тер.";
			link.l1 = "Осталось придумать, как быстро добраться туда.";
			link.l1.go = "PZ_Zhorzh_15";
		break;
		
		case "PZ_Zhorzh_15":
			dialog.text = "Это уже ваша забота, месье Лонгвэй! У меня у самого их выше крыши. Ещё крышу чинить...";
			link.l1 = "Кстати, о заботы. Мой найти те разбойники. Так что возвращать твой пожертвования. Чинить крыша - негоже ваш бог быть без неё в его дом.";
			link.l1.go = "PZ_Zhorzh_16";
		break;
		
		case "PZ_Zhorzh_16":
			dialog.text = "Ого... Спасибо огромное, месье Лонгвэй! Ни за что бы не подумал, что вы этим займётесь.";
			link.l1 = "Мой и сам не думать. Но как-то быть нужно провести эти два день.";
			link.l1.go = "PZ_Zhorzh_17";
		break;
		
		case "PZ_Zhorzh_17":
			dialog.text = "Значит, вам нужно попасть на Гваделупу? Я постараюсь найти для вас корабль, идущий в те воды! Ждите от меня вестей в таверне!";
			link.l1 = "Быть неплохо. Спасибо, Жорж.";
			link.l1.go = "PZ_Zhorzh_18";
		break;
		
		case "PZ_Zhorzh_18":
			DialogExit();
			SetCurrentTime(9, 00);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			EndQuestMovie();
			InterfaceStates.Buttons.Save.enable = false;
			
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("На следующее утро"+ NewStr() +"Капстервиль", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("Kapstervil", "goto", "goto19", "PZ_Kapstervil_PoiskZvezda");
			LaunchFrameForm();
		break;
		
		case "PZ_Kapstervil_Kurier_1":
			dialog.text = "Ты, видимо, знакомый Жоржа? Он просил передать тебе это.";
			link.l1 = "Записка? Спасибо. А как вы понять, что передать нужно именно мой?";
			link.l1.go = "PZ_Kapstervil_Kurier_2";
		break;
		
		case "PZ_Kapstervil_Kurier_2":
			dialog.text = "Ты серьёзно? Да ты же единственный жёлтый батрак в нашем городе!";
			link.l1 = "Ах да.";
			link.l1.go = "PZ_Kapstervil_Kurier_3";
		break;
		
		case "PZ_Kapstervil_Kurier_3":
			DialogExit();
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("PZ_Kapstervil_ChitaemPismo", 1.5);
		break;
		
		case "PZ_Kapstervil_ChitaemPismo_Dialog":
			dialog.text = "(читает письмо) Месье Лонгвэй! Пинас 'Прованс' отбывает в Бас-Тер завтра утром. Полагаю, капитана, Матье Теруньи, вы сможете найти в таверне. Передайте моё почтение месье ван Мердену. Жорж Гравель.";
			link.l1 = "";
			link.l1.go = "PZ_Kapstervil_ChitaemPismo_Dialog_2";
		break;
		
		case "PZ_Kapstervil_ChitaemPismo_Dialog_2":
			DialogExit();
			LAi_RemoveCheckMinHP(pchar);
			chrDisableReloadToLocation = false;
			LAi_SetPlayerType(pchar);
			sld = characterFromId("PZ_Kapstervil_tavernkeeper");
			sld.dialog.currentnode = "PZ_TerunyiTavern1";
			LAi_SetBarmanType(sld);
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "PZ_TerunyiTavern1":
			dialog.text = "Здесь таким, как ты, не наливают. Комнату тоже не дам, а то потом постояльцы на блох будут жаловаться.";
			link.l1 = "Мой не нужно ни то, ни другое. Мой нужен информация. И... у Лонгвэй нет блох.";
			link.l1.go = "PZ_TerunyiTavern2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_TerunyiTavern2":
			dialog.text = "Да кто ж тебя знает. Ну ладно, выкладывай, что тебе нужно. Только потом сразу же на выход.";
			link.l1 = "Так и будет. Мой искать капитан Матье Теруньи. Не мочь его найти. Ваш, случайно, не знать, где он быть?";
			link.l1.go = "PZ_TerunyiTavern3";
		break;
		
		case "PZ_TerunyiTavern3":
			dialog.text = "Занят он. Корабль готовит к выходу в море - товары закупает в магазине. Это куда важнее, чем разглагольствовать с желтопузым вроде тебя, но тебе этого явно не понять.";
			link.l1 = "Вообще-то мой когда-то... Ладно, это не быть важно сейчас.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_CreateTerunyi");
		break;
		
		case "PZ_Terunyi1":
			dialog.text = "Что тебе нужно от меня, китаец? Не видишь? Я разговариваю, мне нужно загрузить корабль.";
			link.l1 = "Ваш быть капитан Матье Теруньи?";
			link.l1.go = "PZ_Terunyi2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_Terunyi2":
			dialog.text = "А вот это уже не смешно. Откуда желтокожий вроде тебя знает, кто я? Тебя кто-то подослал, решил напасть средь бела дня?";
			link.l1 = "Нет, не переживать. Мой слышать, что ваш плыть в Бас-Тер. Ваш не мочь взять мой как пассажир? Не за спасибо, сам собой.";
			link.l1.go = "PZ_Terunyi3";
		break;
		
		case "PZ_Terunyi3":
			dialog.text = "Час от часу не легче. Отправляюсь я в Сен-Пьер, а не Бас-Тер, так-то. Крюк будет совсем небольшим, но терпеть твою персону на корабле больше необходимого не намерен. Пять тысяч песо, отбываем через три часа, рассчитаемся на пирсе. И торг неуместен, хоть я и торговец. Усёк?";
			link.l1 = "Да. Благодарить. До встреча в порт, капитан Теруньи.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TeleportToPier");
		break;
		
		case "PZ_Terunyi4":
			dialog.text = "Явился всё-таки, желтокожий. Я уж думал, что не придёшь - денег-то такому никто даст. Добровольно, во всяком случае. Принёс их, кстати?";
			link.l1 = "Принести. Пять тысяч песо, как вы и просить. Ваш быть готов отчалить?";
			link.l1.go = "PZ_Terunyi5";
		break;
		
		case "PZ_Terunyi5":
			AddMoneyToCharacter(pchar, -5000);
			
			dialog.text = "Но-но! Это я должен у тебя такое спрашивать. Но, как я понимаю, ты готов. Идём. Будешь грести в шлюпке. На полноценную каюту не рассчитывай - обойдёшься. Мы и так из-за одного лишь тебя делаем крюк.";
			link.l1 = "Мой это и не быть нужно. Главное - добраться.";
			link.l1.go = "PZ_Terunyi6";
		break;
		
		case "PZ_Terunyi6":
			DialogExit();
			
			SetCurrentTime(2, 00);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			InterfaceStates.Buttons.Save.enable = true;
			
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			PChar = GetMainCharacter();
			LAi_SetPlayerType(PChar);
			
			QuestToSeaLogin_Launch();
			QuestToSeaLogin_PrepareLoc("Guadeloupe", "Quest_Ships", "Quest_ship_8", false);
			DoQuestCheckDelay("PZ_Flashback_Final_1", 3.5);
		break;
		
		case "PZ_Longway_PosleRasskaza21":
			dialog.text = "... так что Лонгвэй не удалось выяснить, куда направиться 'Утренняя звезда'.";
			link.l1 = "Да уж, теперь понятно, как ты оказался во всём этом дерьме.";
			link.l1.go = "PZ_Longway_PosleRasskaza22";
		break;
		
		case "PZ_Longway_PosleRasskaza22":
			if (GetCharacterIndex("Helena") != -1 && CheckPassengerInCharacter(pchar, "Helena")) sStr = "Элен";
			else sStr = "Алонсо";
			dialog.text = "Лонгвэй вспомнить ещё кое-что, господин капитан. Помнить, мой говорить, что Ферментелуш общаться с капитан бриг 'Бантен'? На самом деле, помимо солдаты, мой отбиваться от матросы с этот бриг у пещера. Они быть наёмники, и из их разговоры мой узнать, что их капитан щедро платить за голова Лонгвэй.";
			link.l1 = "А ведь я видел какой-то бриг в водах Гваделупы. Возможно, это как раз был 'Бантен'. Попробую это выяснить. Ну а ты можешь идти, Лонгвэй. Приведи ко мне " + sStr + ".";
			link.l1.go = "PZ_Longway_PosleRasskaza23";
		break;
		
		case "PZ_Longway_PosleRasskaza23":
			DialogExit();
			LAi_SetStayType(pchar);
			LAi_FadeLong("PZ_LongwayUhoditIzKauty", "PZ_HelenaOrAlonso");
		break;
		
		case "PZ_Helena_1":
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 6)
			{
				dialog.text = "Мой капитан, всё хорошо? Я всё бросила и отправилась к тебе, когда Лонгвэй сказал, что ты хотел поговорить.";
				link.l1 = "Как раз пытаюсь во всём разобраться. Слушай, ты не помнишь, как назывался тот бриг, что мы видели у берегов острова?";
				link.l1.go = "PZ_Helena_3";
			}
			else
			{
				dialog.text = "Ты хотел меня увидеть?";
				link.l1 = "Да. Помнишь, когда мы приближались к Гваделупе, то видели какой-то бриг? Выясни, где он сейчас, и как называется.";
				link.l1.go = "PZ_Helena_2";
			}
		break;
		
		case "PZ_Helena_2":
			dialog.text = "Припоминаю, но с чего вдруг тебе стал интересен какой-то бриг? Да и времени столько на это уйдёт.";
			link.l1 = "Боже, Элен, просто сделай это. И да, я отдаю себе отчёт в том, что это может затянуться. Жду тебя с вестями.";
			link.l1.go = "PZ_PoiskBanten";
		break;
		
		case "PZ_Helena_3":
			dialog.text = "Да нет. Как-то не стала проверять. А что такое, он нам нужен?";
			link.l1 = "Угу. Можешь, пожалуйста, узнать это? А заодно, где они сейчас бросили якорь. Если вообще не покинули акваторию Гваделупы.";
			link.l1.go = "PZ_Helena_4";
		break;
		
		case "PZ_Helena_4":
			dialog.text = "Да, конечно. Только предупреждаю тебя, что это может быть очень и очень долго. Я возьму с собой шлюпку и пару ребят в помощь, хорошо?";
			link.l1 = "Само собой, Элен, спасибо. Жду тебя.";
			link.l1.go = "PZ_PoiskBanten";
		break;
		
		case "PZ_Alonso_11":
			dialog.text = "Сеньор капитан, вызывали?";
			link.l1 = "Да, Алонсо. Мы когда возвращались за Лонгвэем, то проходили мимо одного брига в акватории острова. Ты случайно не обратил внимания, как он назывался?";
			link.l1.go = "PZ_Alonso_12";
		break;
		
		case "PZ_Alonso_12":
			dialog.text = "Нет. Моё дело - за новенькими приглядывать да в абордажах участвовать. К тому же, у меня ведь нет подзорной трубы, а проходили мы не настолько близко.";
			link.l1 = "И правда. Однако мне нужно это выяснить. Сделай это, пожалуйста. А заодно - и где они сейчас примерно находятся в здешних водах.";
			link.l1.go = "PZ_Alonso_13";
		break;
		
		case "PZ_Alonso_13":
			dialog.text = "Есть, капитан. Думаю, примерно за полдня управлюсь.";
			link.l1 = "Поторопись. Буду ждать.";
			link.l1.go = "PZ_PoiskBanten";
		break;
		
		case "PZ_PoiskBanten":
			DialogExit();
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			LAi_SetStayType(pchar);
			SetLaunchFrameFormParam("Пять часов спустя...", "PZ_PoiskBanten_2", 0, 4.0);
			LaunchFrameForm();
			locCameraSleep(true);
		break;
		
		case "PZ_Helena_5":
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 6)
			{
				dialog.text = "Я всё узнала. Ничего за это время не произошло, мой капитан?";
				link.l1 = "Нет, всё хорошо, спасибо, Элен. Рассказывай.";
				link.l1.go = "PZ_Helena_7";
			}
			else
			{
				dialog.text = "Фух, вернулась. Я нашла твой бриг.";
				link.l1 = "С возвращением. Где они причалили? И да, он называется...";
				link.l1.go = "PZ_Helena_6";
			}
		break;
		
		case "PZ_Helena_6":
			dialog.text = "'Бантен'. Кажется, это имя тебе о чём-то говорит, я права? Они сейчас у маяка, а на берег сошло несколько человек из их команды. Атакуем корабль?";
			link.l1 = "Нет, мне нужно выяснить, кто именно сошёл на берег, так что доберёмся до маяка по суше. Но, учитывая, что мы и так порядком задержались, а нам уже давно пора было отчалить, лучше бросить якорь в каком-нибудь отдалённом месте. Думаю, пляж Капстер подойдёт. Поспешим, Элен.";
			link.l1.go = "PZ_BasTerMayak";
		break;
		
		case "PZ_Helena_7":
			dialog.text = "Ну, этот бриг называется 'Бантен', и в данный момент они у маяка, туда высадились несколько людей из экипажа корабля. Что собираешься делать?";
			link.l1 = "Ну, чтобы узнать, капитан это был или его посланник, придётся незаметно добраться до маяка, а сделать это можно только пешком. Да и наше судно нужно куда-то деть... Как смотришь на то, чтобы причалить у пляжа Капстер?";
			link.l1.go = "PZ_Helena_8";
		break;
		
		case "PZ_Helena_8":
			dialog.text = "Хорошая идея. Шарль, с тобой сходить на маяк?";
			link.l1 = "Подумаю, пока корабль будем отгонять - ты и так очень устала.";
			link.l1.go = "PZ_BasTerMayak";
		break;
		
		case "PZ_Alonso_15":
			dialog.text = "Вернулся сразу же, как только закончил, сеньор капитан.";
			link.l1 = "Очень хорошо. Докладывай, Алонсо.";
			link.l1.go = "PZ_Alonso_16";
		break;
		
		case "PZ_Alonso_16":
			dialog.text = "Бриг всё ещё у берегов острова - у маяка, если быть точным. Название на корме - 'Бантен'. Несколько голубчиков с него как раз туда и отправились.";
			link.l1 = "Хорошая работа, Алонсо. Подготовь парней немедленно поднять якорь.";
			link.l1.go = "PZ_Alonso_17";
		break;
		
		case "PZ_Alonso_17":
			dialog.text = "Подготовить их заодно к абордажу?";
			link.l1 = "Пока что не стоит - вдруг к маяку направился их капитан? Он может скрыться в городе, если нападём в море. Так что мы сейчас на всех парусах к пляжу Капстер, чтобы за наш корабль не переживать, а оттуда уже бегом к маяку.";
			link.l1.go = "PZ_BasTerMayak";
		break;
		
		case "PZ_BasTerMayak":
			DialogExit();
			locCameraSleep(false);
			LAi_SetPlayerType(pchar);
			ChangeCharacterAddressGroup(npchar, "none", "", "");
			chrDisableReloadToLocation = false;
			bDisableCharacterMenu = false;
			bQuestDisableMapEnter = false;
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
			Island_SetReloadEnableGlobal("Guadeloupe", true);
			
			AddQuestRecord("PZ", "15");
			PChar.quest.PZ_Banten_PlyazhKapster.win_condition.l1 = "location";
			PChar.quest.PZ_Banten_PlyazhKapster.win_condition.l1.location = "Shore29";
			PChar.quest.PZ_Banten_PlyazhKapster.win_condition = "PZ_Banten_PlyazhKapster";
			
			PChar.quest.PZ_Banten_PlyazhKapster_Proval.win_condition.l1 = "Timer";
			PChar.quest.PZ_Banten_PlyazhKapster_Proval.win_condition.l1.date.hour = sti(GetTime() + 7);
			PChar.quest.PZ_Banten_PlyazhKapster_Proval.win_condition.l1.date.day = GetAddingDataDay(0, 0, 0);
			PChar.quest.PZ_Banten_PlyazhKapster_Proval.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			PChar.quest.PZ_Banten_PlyazhKapster_Proval.win_condition.l1.date.year = GetAddingDataYear(0, 0, 0);
			PChar.quest.PZ_Banten_PlyazhKapster_Proval.win_condition = "PZ_Banten_PlyazhKapster_Proval";
			
			if (GetCharacterIndex("Helena") != -1 && CheckPassengerInCharacter(pchar, "Helena"))
			{
				LAi_SetActorType(npchar);
				LAi_ActorFollow(npchar, pchar, "", -1);
				LAi_SetOfficerType(npchar);
				npchar.Dialog.Filename = "Quest\Saga\Helena.c";
				npchar.Dialog.CurrentNode = "Helena_officer";
			}
		break;
		
		case "PZ_Longway_21":
			dialog.text = "Господин капитан, смотреть! Внутри маяк кто-то есть.";
			link.l1 = "Отлично, значит, мы успели! Поспешим и схватим их. Чую, Алонсо сегодня предстоит хорошенько так поработать.";
			link.l1.go = "PZ_Longway_22";
		break;
		
		case "PZ_Longway_22":
			dialog.text = "Но что, если один умереть от рана, пока наш побеждать другой? Или если они умереть от боль, так ничего и не успеть сказать?";
			link.l1 = "И что же ты предлагаешь, Лонгвэй?";
			link.l1.go = "PZ_Longway_23";
		break;
		
		case "PZ_Longway_23":
			dialog.text = "Мы тихо пробраться и подслушать их разговор.";
			link.l1 = "Не думаю, что нам это удастся, учитывая, что нас могут увидеть из окна. Но давай попробуем.";
			link.l1.go = "PZ_Longway_24";
		break;
		
		case "PZ_Longway_24":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Longway.c";
			npchar.Dialog.CurrentNode = "Longway_officer";
			LAi_SetCheckMinHP(npchar, 1, true, "SkritoeBessmertie");
			PChar.quest.PZ_MayakPodslushivanie.win_condition.l1 = "locator";
			PChar.quest.PZ_MayakPodslushivanie.win_condition.l1.location = "Mayak4";
			PChar.quest.PZ_MayakPodslushivanie.win_condition.l1.locator_group = "goto";
			PChar.quest.PZ_MayakPodslushivanie.win_condition.l1.locator = "goto31";
			PChar.quest.PZ_MayakPodslushivanie.win_condition = "PZ_MayakPodslushivanie";
		break;
		
		case "PZ_MayakPodslushivanie_Dialog_1":
			dialog.text = "Подумай над тем, что я сказал. Хорошо подумай. Деньги - вообще не проблема. В разумных пределах, само собой. Но даже этот предел тебе покажется золотой горой - китаец должен умереть! Я уже отправлял за ним своих ребят, но так никто и не вернулся. Но вот если они объединятся с твоими парнями...";
			link.l1 = "";
			link.l1.go = "PZ_MayakPodslushivanie_Dialog_1_1";
			CharacterTurnByChr(npchar, CharacterFromID("PZ_BasTerJailOff_Clone"));
		break;
		
		case "PZ_MayakPodslushivanie_Dialog_1_1":
			StartInstantDialog("PZ_BasTerJailOff_Clone", "PZ_MayakPodslushivanie_Dialog_2", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_MayakPodslushivanie_Dialog_2":
			dialog.text = "Смотри, нас подслушивают! И это он! Он и его проклятый дружок!";
			link.l1 = "";
			link.l1.go = "PZ_MayakPodslushivanie_Dialog_3";
			CharacterTurnToLoc(npchar, "item", "flower5");
		break;
		
		case "PZ_MayakPodslushivanie_Dialog_3":
			DialogExit();
			EndQuestMovie();
			locCameraSleep(false);
			locCameraToPos(1.52, 18.87, -9.55, true);
			DoQuestCheckDelay("CameraReset", 1.0);
			DeleteAttribute(pchar, "questTemp.NoFast");
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("PZ_Neznakomets");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			
			sld = CharacterFromID("PZ_BasTerJailOff_Clone");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_SetCheckMinHP(sld, 1, true, "PZ_MayakPodslushivanie_win");
			
			for (i=1; i<=4; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("PZ_Neznakomets_Bandit_"+i, "citiz_" + (rand(9) + 41), "man", "man", sti(pchar.rank), PIRATE, -1, true, "pirate"));
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload2");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
		break;
		
		case "PZ_Mayak_KomendantSidit_1":
			if (!CharacterIsAlive("PZ_Neznakomets_Bandit_1") && !CharacterIsAlive("PZ_Neznakomets_Bandit_2") && !CharacterIsAlive("PZ_Neznakomets_Bandit_3")&& !CharacterIsAlive("PZ_Neznakomets_Bandit_4"))
			{
				dialog.text = "Будь ты проклят, мерзкий азиат, кхе-кхе... Столько из-за тебя пришлось вытерпеть. А сейчас и того, гляди, подохну...";
				link.l1 = "Мы отведём вас к нашему врачу, месье комендант. Только скажите, с кем вы сейчас разговаривали - это очень важно.";
				link.l1.go = "PZ_Mayak_KomendantSidit_2";
				LAi_group_Delete("EnemyFight");
			}
			else
			{
				dialog.text = RandSwear()+"";
				link.l1 = "";
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_MayakPodslushivanie_win");	
			}
		break;
		
		case "PZ_Mayak_KomendantSidit_2":
			dialog.text = "Его зовут Сепп ван дер Винк, он... кха...";
			link.l1 = "...";
			link.l1.go = "PZ_Mayak_KomendantSidit_3";
		break;
		
		case "PZ_Mayak_KomendantSidit_3":
			DialogExit();
			LAi_SetImmortal(npchar, false);
			LAi_KillCharacter(npchar);
			DoQuestCheckDelay("PZ_Mayak_Longway", 1.5);
		break;
		
		case "PZ_Longway_25":
			dialog.text = "";
			link.l1 = "Он умер... Ну, по крайней мере, мы знаем имя. Лонгвэй?..";
			link.l1.go = "PZ_Longway_26";
		break;
		
		case "PZ_Longway_26":
			dialog.text = "Это совершенно не мочь быть...";
			link.l1 = "Ты прямо-таки побледнел, Лонгвэй.";
			link.l1.go = "PZ_Longway_27";
		break;
		
		case "PZ_Longway_27":
			dialog.text = "Мой быть совершенно уверен, что убить ван дер Винк десять лет назад\nОни уходить! У них быть быстрый корабль...";
			link.l1 = "Да, добрый бриг... к несчастью для нас. Даже на нашем судне нам его не догнать - пока добежим, поднимем паруса, наберём ветра - они успеют скрыться, и Бог знает, в каком направлении...";
			link.l1.go = "PZ_Longway_28";
		break;
		
		case "PZ_Longway_28":
			dialog.text = "Это быть конец...";
			link.l1 = "Нет, Лонгвэй. Послушай меня. Если они планируют остаться на Архипелаге, то мы обязательно столкнёмся с ними, рано или поздно - мир тесен, а Карибы - особенно. Как только мы снова наткнёмся на их след - я всё брошу и отправлюсь за ними в погоню. Обещаю тебе. Слышишь?";
			link.l1.go = "PZ_Longway_29";
		break;
		
		case "PZ_Longway_29":
			dialog.text = "Да, господин капитан. Благодарить.";
			link.l1 = "А теперь не вешай нос, Лонгвэй. Идём - нам всё равно нужно поспешить на корабль - о смерти коменданта всем станет известно уже в ближайшее время.";
			link.l1.go = "PZ_Longway_30";
		break;
		
		case "PZ_Longway_30":
			DialogExit();
			
			Return_LongwayOfficer();
			LAi_RemoveCheckMinHP(npchar);
			AddQuestRecord("PZ", "17");
			sld = &Locations[FindLocation("Mayak4")];
			sld.locators_radius.goto.goto31 = 0.5;
			
			chrDisableReloadToLocation = false;
			QuestOpenSeaExit();
			
			pchar.questTemp.PZ_Etap4_Start = true;
		break;
		
		// Этап 4, Обманчивая Звезда
		case "PZ_PoterpKrushenie_1":
			dialog.text = "Сударь! Постойте, сударь! Вы ведь капитан, верно?";
			link.l1 = "Может быть. А как вы это поняли? И что вам нужно?";
			link.l1.go = "PZ_PoterpKrushenie_2";
		break;
		
		case "PZ_PoterpKrushenie_2":
			dialog.text = "Здесь вокруг лишь горы, и местная сельва непроходима - в город не вернётесь. Вы ведь как-то попали сюда. И вряд ли просто любуетесь видами в этой бухте.";
			link.l1 = "Неплохое наблюдение! Однако вы так и не ответили, что вы хотите.";
			link.l1.go = "PZ_PoterpKrushenie_3";
		break;
		
		case "PZ_PoterpKrushenie_3":
			dialog.text = "А, да! Видите ли, капитан, мы потерпели кораблекрушение прямо у этой бухты. Наш люггер разбился о здешние скалы, и мы единственные выжившие...";
			link.l1 = "Сочувствую. Полагаю, вы собирались попросить меня отвезти вас куда-нибудь.";
			link.l1.go = "PZ_PoterpKrushenie_4";
		break;
		
		case "PZ_PoterpKrushenie_4":
			dialog.text = "Верно... Мы не доставим вам проблем - пожалуйста, подбросьте нас до Белиза, а дальше мы сами.";
			link.l1 = "Что ж, это и правда недалеко. В таком случае, добро пожаловать на борт!";
			link.l1.go = "PZ_PoterpKrushenie_5";
			link.l2 = "Мне жаль, но я иду в совершенно другую сторону - нам не по пути.";
			link.l2.go = "PZ_PoterpKrushenie_7";
		break;
		
		case "PZ_PoterpKrushenie_5":
			dialog.text = "Спасибо вам большое, капитан! Кто знает, сколько бы нам пришлось торчать здесь, ожидая другие корабли.";
			link.l1 = "Это точно. Не будем терять времени!";
			link.l1.go = "PZ_PoterpKrushenie_6";
		break;
		
		case "PZ_PoterpKrushenie_6":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			DeleteAttribute(&locations[FindLocation("Shore9")], "DisableEncounters");
			
			for (i=1; i<=6; i++)
			{
				sld = CharacterFromID("PZ_PoterpKrushenie_"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "sea", "", "", "", "", -1);
				sld.location = "None";
			}
			
			PChar.quest.PZ_Beliz_PoterpKrushenie.win_condition.l1 = "location";
			PChar.quest.PZ_Beliz_PoterpKrushenie.win_condition.l1.location = "Beliz_town";
			PChar.quest.PZ_Beliz_PoterpKrushenie.win_condition = "PZ_Beliz_PoterpKrushenie";
			AddMapQuestMarkCity("Beliz", false);
			
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			
			SetTimerCondition("PZ_BelizFail", 0, 0, 30, false);
		break;
		
		case "PZ_PoterpKrushenie_7":
			dialog.text = "Но мы же не просим везти нас до, скажем, Сент-Джонса! До Белиза буквально рукой подать...";
			link.l1 = "Я очень спешу и не могу позволить себе крюк.";
			link.l1.go = "PZ_PoterpKrushenie_8";
		break;
		
		case "PZ_PoterpKrushenie_8":
			dialog.text = "Даже малейший, до Белиза?! У вас уйдёт на это не более, чем час-другой. Вы не можете бросить нас здесь на произвол судьбы, капитан!";
			link.l1 = "Ох, надеюсь, я не буду потом жалеть об этом. Быстро все на борт вместе со мной!";
			link.l1.go = "PZ_PoterpKrushenie_6";
			link.l2 = "К сожалению, могу. Такова жизнь, друзья мои. Прощайте.";
			link.l2.go = "PZ_PoterpKrushenie_9";
		break;
		
		case "PZ_PoterpKrushenie_9":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			DeleteAttribute(&locations[FindLocation("Shore9")], "DisableEncounters");
			
			for (i=1; i<=6; i++)
			{
				sld = CharacterFromID("PZ_PoterpKrushenie_"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1", "", "", "", "", 10);
				sld.location = "None";
			}
			
			PChar.quest.PZ_Beliz_PoterpKrushenie.win_condition.l1 = "location";
			PChar.quest.PZ_Beliz_PoterpKrushenie.win_condition.l1.location = "Beliz_town";
			PChar.quest.PZ_Beliz_PoterpKrushenie.win_condition = "PZ_Beliz_QuestCitizenDialog";
			
			AddMapQuestMarkCity("Beliz", false);
			
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			AddCharacterExpToSkill(pchar, "FencingL", 20);
			AddCharacterExpToSkill(pchar, "FencingS", 20);
			AddCharacterExpToSkill(pchar, "FencingH", 20);
			AddCharacterExpToSkill(pchar, "Pistol", 20);
			
			pchar.questTemp.PZ.Shipwreckers.Decline = true;
			
			SetTimerCondition("PZ_BelizFail", 0, 0, 30, false);
		break;
		
		case "PZ_PoterpKrushenie_11":
			dialog.text = "Ещё раз большое спасибо вам! К сожалению, мы простые матросы, так что, увы, нам нечем вас отблагодарить.";
			link.l1 = "Что ж, по крайней мере, не пришлось делать большой крюк.";
			link.l1.go = "PZ_PoterpKrushenie_12";
		break;
		
		case "PZ_PoterpKrushenie_12":
			dialog.text = "Мы выпьем за ваше здоровье и поставим за него свечку в церкви, капитан.";
			link.l1 = "Ладно, это немного лучше, чем ничего. Бывайте, ребята!";
			link.l1.go = "PZ_PoterpKrushenie_13";
		break;
		
		case "PZ_PoterpKrushenie_13":
			DialogExit();
			for (i=1; i<=6; i++)
			{
				sld = CharacterFromID("PZ_PoterpKrushenie_"+i);
				LAi_SetCitizenType(sld);
				LAi_CharacterDisableDialog(sld);
				sld.lifeday = 0;
				sld.location = "None";
			}
			
			sld = GetCharacter(NPC_GenerateCharacter("PZ_BelizZhitelNovosti", "citiz_4", "man", "man", 1, ENGLAND, 0, false, "quest"));
			ChangeCharacterAddressGroup(sld, pchar.location, "goto",  "goto5");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_BelizZhitelNovosti_1";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "PZ_BelizZhitelNovosti_1":
			dialog.text = "Вы слышали новости?! Наконец-то его поймали, и в наших водах стало спокойнее!";
			link.l1 = "Не слышал. Это, конечно, хорошо, но кого поймали-то?";
			link.l1.go = "PZ_BelizZhitelNovosti_2";
			DeleteQuestCondition("PZ_BelizFail");
		break;
		
		case "PZ_BelizZhitelNovosti_2":
			dialog.text = "Мэтью Латтера, самого Говорливого!";
			link.l1 = "Не знаю такого, что же он сделал?";
			link.l1.go = "PZ_BelizZhitelNovosti_3";
		break;
		
		case "PZ_BelizZhitelNovosti_3":
			dialog.text = "Как, не знаете?! А, ну да, вы ведь не англичанин, по вам заметно. Он пират, в течение нескольких лет грабивший наших и испанцев на своём корабле, 'Чайке'.";
			link.l1 = "Англичане и испанцы - необычное сочетание.";
			link.l1.go = "PZ_BelizZhitelNovosti_4";
		break;
		
		case "PZ_BelizZhitelNovosti_4":
			dialog.text = "Это точно. Он уходил ото всех патрульных кораблей, а в итоге откусил больше, чем смог проглотить - проиграл бой какому-то странному купцу, вы представляете?";
			link.l1 = "Надо же. Забавно. А что же было странного в том купце?";
			link.l1.go = "PZ_BelizZhitelNovosti_5";
		break;
		
		case "PZ_BelizZhitelNovosti_5":
			dialog.text = "Ну, то, что у него не торговый, а огромный военный корабль! Эти жадные испанцы - просто чокнутые. Но благодаря этому чокнутому песенка Говорливого скоро будет спета - его повесят сегодня. Обязательно приходите посмотреть!";
			link.l1 = "Непременно. Но сейчас мне уже пора идти.";
			link.l1.go = "PZ_BelizZhitelNovosti_6";
		break;
		
		case "PZ_BelizZhitelNovosti_6":
			DialogExit();
			
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			
			sld = CharacterFromID("Longway");
			if (!CharacterIsHere("Longway"))
			{
				ChangeCharacterAddressGroup(sld, PChar.location, "goto", LAi_FindNearestFreeLocator2Pchar("goto"));
			}
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Longway_31";
		break;
		
		case "PZ_Longway_31":
			dialog.text = "Господин капитан!";
			link.l1 = "Испанский торговец, легко одолевший пирата... Ты думаешь о том же, что и я, верно?";
			link.l1.go = "PZ_Longway_32";
		break;
		
		case "PZ_Longway_32":
			dialog.text = "'Утренняя звезда'...";
			link.l1 = "Скорее всего - сомневаюсь, что во всём Архипелаге сыщется хоть ещё один такой же капитан вроде него.";
			link.l1.go = "PZ_Longway_33";
		break;
		
		case "PZ_Longway_33":
			dialog.text = "Мы должен срочно найти он!";
			link.l1 = "Верно. Но я не вижу подобного галеона в порту. Попробуем поговорить с Мэттом, пока его не повесили. Узнаем, насколько он говорлив.";
			link.l1.go = "PZ_Longway_34";
		break;
		
		case "PZ_Longway_34":
			DialogExit();
			Return_LongwayOfficer();
			if (!CheckAttribute(pchar, "questTemp.PZ.Shipwreckers.Decline")) AddQuestRecord("PZ", "18");
			else AddQuestRecord("PZ", "18_1");
			pchar.questTemp.PZ_Beliz_Komendant = true;
			AddLandQuestMarkToPhantom("beliz_prison", "belizJailOff");
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
		break;
		
		case "PZ_Beliz_Komendant_8":
			dialog.text = "Он ещё быть жив? Мочь наш поговорить с его?";
			link.l1 = "";
			link.l1.go = "PZ_Beliz_Komendant_9";
			CharacterTurnByChr(npchar, CharacterFromID("BelizJailOff"));
		break;
		
		case "PZ_Beliz_Komendant_9":
			StartInstantDialogNoType("BelizJailOff", "PZ_Beliz_Komendant_10", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Beliz_Komendant_10":
			dialog.text = "Что? А, да, конечно. Жив он, казнь же ещё не состоялась. Можете пойти и поговорить с ним - в конце концов, он же Говорливый Мэтт! Даже более говорливый, чем обычно - околесицу какую-то несёт в последнее время и сам с собой разговаривает. Умом тронулся... Скорее бы уже повесить его, а то сами с ума сойдём от его бесконечной болтовни и криков.";
			link.l1 = "";
			link.l1.go = "PZ_Beliz_Komendant_11";
		break;
		
		case "PZ_Beliz_Komendant_11":
			StartInstantDialog("Longway", "PZ_Beliz_Komendant_12", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Beliz_Komendant_12":
			dialog.text = "Благодарить.";
			link.l1 = "";
			link.l1.go = "PZ_Beliz_Komendant_13";
			CharacterTurnByChr(npchar, CharacterFromID("BelizJailOff"));
		break;
		
		case "PZ_Beliz_Komendant_13":
			DialogExit();
			pchar.questTemp.jailCanMove = true;
			
			Return_LongwayOfficer();
			
			sld = CharacterFromID("BelizJailOff");
			LAi_SetHuberType(sld);
			sld.Dialog.Filename = "Common_Prison.c";
			sld.Dialog.CurrentNode = "First_officer";
			
			sld = GetCharacter(NPC_GenerateCharacter("PZ_MatthewLutter", "mercen_15", "man", "man", 1, ENGLAND, -1, false, "quest"));
			sld.name = "Мэтью";
			sld.lastname = "Латтер";
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_MatthewLutter1";
			ChangeCharacterAddressGroup(sld, "Beliz_prison", "goto", "goto9");
			LAi_SetStayType(sld);
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "PZ_MatthewLutter1":
			dialog.text = "Он украл её у нас, украл! Моё сокровище!";
			link.l1 = "Мэтью Латтер?";
			link.l1.go = "PZ_MatthewLutter2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_MatthewLutter2":
			dialog.text = "Теперь оно достанется ему, понимаешь, ЕМУ!!! Мы ничего не можем с этим поделать!..";
			link.l1 = "Послушай, я...";
			link.l1.go = "PZ_MatthewLutter3";
		break;
		
		case "PZ_MatthewLutter3":
			dialog.text = "Что вам всем нужно?! Решили отнять у нас ещё что-то?! А нечего! Теперь она умрёт, умрёт!! Или хуже!";
			link.l1 = "Кто умрёт, какое ещё сокровище? А, ладно, неважно. Сам ведь виноват - это же ты напал на тот тяжёлый галеон, не наоборот.";
			link.l1.go = "PZ_MatthewLutter4";
		break;
		
		case "PZ_MatthewLutter4":
			dialog.text = "Наоборот! Как раз наоборот!! Будь проклят этот идальго, из-за него у нас всё пошло наперекосяк! И в итоге он отнял её у нас!!!";
			link.l1 = "Даже так? Впрочем, не удивлён. Что ещё можешь рассказать о нём? И... что отнял-то, кто 'она'?";
			link.l1.go = "PZ_MatthewLutter5";
		break;
		
		case "PZ_MatthewLutter5":
			dialog.text = "А-а-а!!! А-А-А!!!";
			link.l1 = "Ох, понятно, чёрт возьми, я теряю время...";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_BelizPrisonSoldierDialog");
		break;
		
		case "PZ_BelizPrisonQuestSoldier1":
			dialog.text = "Верно говорите, капитан. Так что, с вашего позволения... (Латтеру) Латтер! На выход! Твоё время пришло.";
			link.l1 = "";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_BelizPrisonLongway_UvodyatNaKazn");
		break;
		
		case "PZ_Longway_35":
			dialog.text = "Капитан, наш нужно узнать о Сотта и Латтер больше. Поспрашивать люди вокруг.";
			link.l1 = "Хорошая мысль, Лонгвэй. А то от самого Латтера мы не узнали ничего, что могло бы нам помочь.";
			link.l1.go = "PZ_Longway_36";
		break;
		
		case "PZ_Longway_36":
			dialog.text = "Но, конечно, в первый очередь лучше спрашивать о Сотта.";
			link.l1 = "Ну да, в конце концов, это ведь его мы ищем. Идём.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_BelizPrisonLongwayBack");
		break;
		
		case "PZ_Longway_37":
			dialog.text = "Они ничто не знать!";
			link.l1 = "Ничего удивительного, откуда простым людям знать что-то, что могло бы действительно нам пригодиться. Но это не значит, что мы не можем подумать сами. Он уже давно переделал корабль, так что, скорее всего, попытается продать эти стратегические товары.";
			link.l1.go = "PZ_Longway_38";
		break;
		
		case "PZ_Longway_38":
			dialog.text = "Скоро всего! Значит, наш перехватить его там, где он продавать. Это быть...";
			link.l1 = "... Порт-Ройал и Капстервиль соответственно. Вопрос лишь в том, куда он направится. И где нам его лучше брать, если он отправится и туда, и туда. Или вовсе в открытом море...";
			link.l1.go = "PZ_Longway_39";
		break;
		
		case "PZ_Longway_39":
			dialog.text = "Нет! То есть... Мой хотеть сказать, что Ферментелуш быть очень опытный и опасный недруг. Бой открытый море мочь закончиться как угодно. Лучше устроить засада рядом с какой-то город.";
			link.l1 = "Ты прав, пожалуй. Неважно, он напал, или на него напали, однако он одолел пиратский корвет на тяжёлом галеоне, так что нельзя его недооценивать.";
			link.l1.go = "PZ_Longway_40";
		break;
		
		case "PZ_Longway_40":
			dialog.text = "Быть так, быть так. Но и медлить, раздумывать, наш тоже нельзя.";
			link.l1 = "И ты снова прав, Лонгвэй. Так что поднимаем якорь немедленно, а там уже подумаем, как нам быть.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_LongwayBelizDialogBack");
			DelMapQuestMarkCity("Beliz");
		break;
		
		case "PZ_Longway_41":
			dialog.text = "Господин капитан, 'Утренняя звезда' быть в порт!";
			link.l1 = "Да, я это уже заметил.";
			link.l1.go = "PZ_Longway_42";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_Longway_42":
			dialog.text = "И что ваш делать дальше?";
			link.l1 = "Пока ещё не придумывал. Пытаться абордировать их под фортовыми орудиями - самоубийство. А на их тяжёлом галеоне мы можем и не надеяться уйти. А что, у тебя уже есть идеи, Лонгвэй?";
			link.l1.go = "PZ_Longway_43";
		break;
		
		case "PZ_Longway_43":
			dialog.text = "Да, быть так. Наш причалить у безопасный бухта, и потом на лодки во время ночь добраться до галеон.";
			if (CheckAttribute(pchar, "questTemp.PZ_OhotaNaZvezdu_Kapstervil"))
			{
				link.l1 = "Что думаешь о заливе Халф Мун, Лонгвэй?";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_OhotaNaZvezdu_Yamaika"))
			{
				link.l1 = "Думаю, бухта Портленд подойдёт - достаточно близко и относительно безопасно. Что скажешь?";
			}
			link.l1.go = "PZ_Longway_44";
		break;
		
		case "PZ_Longway_44":
			dialog.text = "Хороший выбор.";
			link.l1 = "Отлично, с этим разобрались. Мы ничего не упустили из виду?";
			link.l1.go = "PZ_Longway_45";
		break;
		
		case "PZ_Longway_45":
			dialog.text = "Мой думать, что нет, господин капитан. Наш нужно хорошо подготовиться.";
			link.l1 = "Это точно.";
			link.l1.go = "PZ_Longway_46";
		break;
		
		case "PZ_Longway_46":
			DialogExit();
			
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar, "GenQuest.CabinLock");
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
			bQuestDisableMapEnter = false;
			AddQuestRecord("PZ", "21");
			if (CheckAttribute(pchar, "questTemp.PZ_OhotaNaZvezdu_Kapstervil"))
			{
				AddQuestUserData("PZ", "sText", "залив Халф Мун");
				Island_SetReloadEnableGlobal("Nevis", true);
				
				PChar.quest.PZ_GotovimShlupki_Buhta.win_condition.l1 = "location";
				PChar.quest.PZ_GotovimShlupki_Buhta.win_condition.l1.location = "Shore43";
				PChar.quest.PZ_GotovimShlupki_Buhta.win_condition = "PZ_GotovimShlupki_Buhta";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_OhotaNaZvezdu_Yamaika"))
			{
				AddQuestUserData("PZ", "sText", "бухту Портленд");
				Island_SetReloadEnableGlobal("Jamaica", true);
				
				PChar.quest.PZ_GotovimShlupki_Buhta.win_condition.l1 = "location";
				PChar.quest.PZ_GotovimShlupki_Buhta.win_condition.l1.location = "Shore36";
				PChar.quest.PZ_GotovimShlupki_Buhta.win_condition = "PZ_GotovimShlupki_Buhta";
			}
			PChar.quest.PZ_ZvezdaUhodimNaGlobalkru_Proval.win_condition.l1 = "MapEnter";
			PChar.quest.PZ_ZvezdaUhodimNaGlobalkru_Proval.win_condition = "PZ_ZvezdaUhodimNaGlobalkru_Proval";
			
			sld = CharacterFromID("Longway");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
			LAi_SetOfficerType(sld);
			sld.Dialog.Filename = "Quest\HollandGambit\Longway.c";
			sld.Dialog.CurrentNode = "Longway_officer";
		break;
		
		case "PZ_Zvezda_DialogWithCapitan":
			dialog.text = "Ты кто такой, что происходит? Все ко мне! Вахтенный! Вахтенный?..";
			link.l1 = "Никто не придёт, мы крепко-накрепко заколотили все люки. Так что какое-то время нам никто не помешает, месье Ферментелуш.";
			link.l1.go = "PZ_Zvezda_DialogWithCapitan_2";
			SetCameraDialogMode(npchar);
		break;
		
		case "PZ_Zvezda_DialogWithCapitan_2":
			dialog.text = "Ферментелуш? Вообще-то меня зовут Эдгардо Сотта!";
			link.l1 = "Угу, слышал об этом. Нам известно, что это твой псевдоним, Оливерио.";
			link.l1.go = "PZ_Zvezda_DialogWithCapitan_3";
		break;
		
		case "PZ_Zvezda_DialogWithCapitan_3":
			dialog.text = "Да нет же, ты не понимаешь! Ферментелуш мёртв! Я действительно Эдгардо Сотта.";
			link.l1 = "И правда - если присмотреться поближе, то ты выглядишь очень молодо. Ты явно не мог быть капитаном 'Утренней Звезды' десять лет назад. И что же случилось с Оливерио?";
			link.l1.go = "PZ_Zvezda_DialogWithCapitan_4";
		break;
		
		case "PZ_Zvezda_DialogWithCapitan_4":
			dialog.text = "Проблемы одни нам создавал! Вроде той, что стоит рядом с тобой. Вот и избавились от него.";
			link.l1 = "Что ж, раз ты не Ферментелуш, то, может быть, ответишь на наши вопросы? Мы ищем кое-что, что он отнял у моего друга.";
			link.l1.go = "PZ_Zvezda_DialogWithCapitan_5";
		break;
		
		case "PZ_Zvezda_DialogWithCapitan_5":
			dialog.text = "Ничего я тебе говорить не собираюсь! Он мне явно этого не простит.";
			link.l1 = "Ты бы лучше подумал, что будет, если мы тебя не простим...";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_SottaFight");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PZ_AnabelleLutter1":
			dialog.text = "Наконец-то он умер...";
			link.l1 = "Это точно. А вы кто, сударыня? Он вас, видимо, удерживал против вашей воли? Сочувствую, наверняка вам пришлось пройти через страшное...";
			link.l1.go = "PZ_AnabelleLutter2";
			SetCameraDialogMode(npchar);
		break;
		
		case "PZ_AnabelleLutter2":
			dialog.text = "Я Эннабел Латтер.";
			link.l1 = "Капитан Шарль де Мор. Латтер, говорите...";
			link.l1.go = "PZ_AnabelleLutter3";
		break;
		
		case "PZ_AnabelleLutter3":
			dialog.text = "А, вы, должно быть, слышали о Мэтте? Ох, бедный дурачок... Я была его... супругой.";
			link.l1 = "Вот как? Соболезную вам, миссис Латтер. Хотя, вы ведь теперь вдова. Какой же была ваша девичья фамилия, если не секрет?";
			link.l1.go = "PZ_AnabelleLutter4";
		break;
		
		case "PZ_AnabelleLutter4":
			dialog.text = "Её не было. Взгляните на меня получше - и нет, это не только свет так падает. Моей бедной матерью была темнокожая рабыня у пиратов. Никто не знает, кто именно из них был моим отцом, так что они не стали утруждать себя размышлениями о моей фамилии.";
			link.l1 = "А почему же тогда никто не тронул вас? Нет, не поймите меня неправильно - я рад, что этого не произошло. Но, всё же, это... странно.";
			link.l1.go = "PZ_AnabelleLutter5";
		break;
		
		case "PZ_AnabelleLutter5":
			dialog.text = "Да, вы правы. Всё в порядке, будем называть вещи своими именами. Я ведь не изнеженная дворянка, а дочь рабыни. И от тяжёлого разговора не упаду в обморок.";
			link.l1 = "Кхм, я тоже не изнеженный человек, знаете ли. Но продолжайте, пожалуйста. Почему же целый экипаж корабля не осмелился и пальцем тронуть дочь рабыни? Настоящего отца вы не знаете, да и, судя по всему, ему наплевать.";
			link.l1.go = "PZ_AnabelleLutter6";
		break;
		
		case "PZ_AnabelleLutter6":
			dialog.text = "Пожалуй, так. Раз уж вы знаете о Мэтте, скажите, вам известно, что он какое-то время работал на Левассера?";
			link.l1 = "Да, я слышал об этом, когда искал 'Утреннюю Звезду'. Но причём здесь это? Возможно, вас бы и не тронули, будь Мэтт жив и на коне - авторитет Левассера, как-никак. Но вот его победили и повесили. А вы всё ещё целы и невредимы.";
			link.l1.go = "PZ_AnabelleLutter7";
		break;
		
		case "PZ_AnabelleLutter7":
			dialog.text = "Напротив, дело в накалённых с Левассером отношениях. Вижу, вы всё ещё не понимаете, да? Видимо, вы не слышали о... пристрастиях Левассера?";
			link.l1 = "Не слышал, но, опять же, причём здесь...";
			link.l1.go = "PZ_AnabelleLutter8";
		break;
		
		case "PZ_AnabelleLutter8":
			dialog.text = "Ох, значит, придётся вам про всё это рассказать. Присядьте, если вы слишком впечатлительны, сударь. Дело в том, что он спит со множеством женщин, и...";
			if (pchar.questTemp.FMQT == "end")
			{
				link.l1 = "Его жена недалеко от него ушла и тоже спит едва ли не с кем попало.";
				link.l1.go = "PZ_AnabelleLutterKnow1";
			}
			else
			{
				link.l1 = "Невероятно.";
				link.l1.go = "PZ_AnabelleLutterDontKnow1";
			}
		break;
		
		case "PZ_AnabelleLutterKnow1":
			dialog.text = "Ну, не зря же говорят - муж и жена - одна Сатана. Но нет, уверена, он пошёл куда дальше.";
			link.l1 = "И насколько же далеко?";
			link.l1.go = "PZ_AnabelleLutter9";
		break;
		
		case "PZ_AnabelleLutterDontKnow1":
			dialog.text = "Ваш сарказм здесь неуместен, сударь. Вы и понятия не имеете, о чём идёт речь.";
			link.l1 = "Хорошо, хорошо, извините. Продолжайте, пожалуйста.";
			link.l1.go = "PZ_AnabelleLutter9";
		break;
		
		case "PZ_AnabelleLutter9":
			dialog.text = "Это не просто измены супруге. Он берёт женщин против их воли. Девушек удерживают в одном из подвалов, что ему принадлежат.";
			link.l1 = "Получается, ему регулярно привозят рабынь? И вы должны были стать одной из них?";
			link.l1.go = "PZ_AnabelleLutter10";
		break;
		
		case "PZ_AnabelleLutter10":
			dialog.text = "Вы правы насчёт второго. Но, увы, не первого. Ему не нужны рабыни. Левассер безумен - по-своему, не так, как Мэтт. Франсуа хотел владеть женщиной полностью - и телом, и душой. И речь, конечно, не о любви. Ему были нужны свободные женщины, чтобы сломить их волю. Он наслаждался тем, как со временем меняется их взгляд, поведение, манера речи...";
			link.l1 = "Отвратительно...";
			link.l1.go = "PZ_AnabelleLutter11";
		break;
		
		case "PZ_AnabelleLutter11":
			dialog.text = "Даже вам уже слегка нехорошо. А теперь представьте, каково пришлось этим женщинам. Я слышала обо всём этом и не только от Мэтта. Как-то к нему попала португальская дворянка...";
			link.l1 = "Вы как-то отвели взгляд и притихли. Рассказывайте. Меня уже трудно удивить - повидал всякого и в Старом Свете, и за это время на Архипелаге.";
			link.l1.go = "PZ_AnabelleLutterWant1";
			link.l2 = "Не продолжайте, я не хочу знать, что с ней произошло. Надеюсь, что все эти женщины не слишком долго мучились у него.";
			link.l2.go = "PZ_AnabelleLutter12";
		break;
		
		case "PZ_AnabelleLutterWant1":
			dialog.text = "Но такое вы не слышали. И, надеюсь, не увидите. Её привели к нему всё ещё гордой и несломленной, хотя уже, как рассказывал мне Мэтт, люди Левассера насиловали её всю дорогу до Тортуги после захвата плантации возле Кампече, которая принадлежала её мужу - он умер от кровотечения, после того как эти изверги прострелили ему оба колена...";
			link.l1 = "Сильная женщина... Но вы же сказали, что обычно женщин для Левассера не трогали по пути к нему.";
			link.l1.go = "PZ_AnabelleLutterWant2";
		break;
		
		case "PZ_AnabelleLutterWant2":
			dialog.text = "Тех, что он просил привести к нему сам - не трогали. Но сеньора Леонтина была подарком. Неожиданным и приятным для них всех. Так что они не отказали себе в удовольствии...";
			link.l1 = "Ожидаемо.";
			link.l1.go = "PZ_AnabelleLutterWant3";
		break;
		
		case "PZ_AnabelleLutterWant3":
			dialog.text = "Пожалуй... Мэтт на своей 'Чайке' тогда уже стал одним из любимцев Франсуа. И тот пригласил его на один из своих тайных вечеров, для избранных. И когда один из пиратов во время застолья сказал, что не хватает женщин, Левассер рассмеялся во всё горло, а затем...";
			link.l1 = "А затем? Ну что такое?..";
			link.l1.go = "PZ_AnabelleLutterWant4";
		break;
		
		case "PZ_AnabelleLutterWant4":
			dialog.text = "... затем её привели к нему. На поводке! Избитую, с исполосованной спиной, завязанными глазами и заткнутым ртом. И когда из её рта вытащили кляп, то она...";
			link.l1 = "Ужасно. Судя по всему, прокляла Левассера всем, на чём только свет стоит.";
			link.l1.go = "PZ_AnabelleLutterWant5";
		break;
		
		case "PZ_AnabelleLutterWant5":
			dialog.text = "Если бы... Донья Леонтина лишь тихонько произнесла: 'чего желает мой хозяин?'";
			link.l1 = "Кажется, мне сейчас действительно станет дурно. Мэтт не рассказывал, что с ней стало потом?";
			link.l1.go = "PZ_AnabelleLutterWant6";
		break;
		
		case "PZ_AnabelleLutterWant6":
			dialog.text = "Умерла, конечно же. И даже не от рук Левассера. Он выбросил её, как самую настоящую надоевшую собаку. И один из его капитанов застрелил её. Перед смертью она произнесла лишь одно...";
			link.l1 = "Проклятья? Молитву?";
			link.l1.go = "PZ_AnabelleLutterWant7";
		break;
		
		case "PZ_AnabelleLutterWant7":
			dialog.text = "Нет. 'Спасибо'...";
			link.l1 = "Через что же ей пришлось пройти, чтобы просто поблагодарить за избавление от мучений... Сколько же она и другие подобные ей страдали в его логове?..";
			link.l1.go = "PZ_AnabelleLutter12";
		break;
		
		case "PZ_AnabelleLutter12":
			dialog.text = "Ну, рабынь и темнокожих он особенно недолюбливал - не с чем было работать, как он говорил. Долго они у него не жили, как и краснокожие - кроме, разве что, каких-нибудь особенно строптивых дикарок. Но дикость и непокорность тоже не были решением - он убивал как тех, кто быстро пытались начать ему услужить, так и тех, кто слишком долго оставались непослушными.";
			link.l1 = "Вот как... Скажите, а бывали ли у Левассера желтокожие женщины?";
			link.l1.go = "PZ_AnabelleLutter13";
		break;
		
		case "PZ_AnabelleLutter13":
			dialog.text = "Нет, во всяком случае, я никогда о таком не слышала. Что же касается меня... Как вы слышали, и как мы все думали - он недолюбливает темнокожих женщин. Так что когда Мэтт работал на Франсуа, то спокойно гулял со мной по улицам Тортуги. И даже брал с собой в резиденцию.";
			link.l1 = "Но он захотел сделать вас одной из своих рабынь...";
			link.l1.go = "PZ_AnabelleLutter14";
		break;
		
		case "PZ_AnabelleLutter14":
			dialog.text = "Именно... Я уж не знаю, чем ему так приглянулась... Мэтт покинул остров сразу же, как ему сказали об этом. И больше никогда не возвращался на Тортугу. Пусть он и был немного не в себе, но он любил меня. Называл своим сокровищем...";
			link.l1 = "Так вот что он имел ввиду, когда говорил, что капитан 'Звезды' отнял у него сокровище!";
			link.l1.go = "PZ_AnabelleLutter15";
		break;
		
		case "PZ_AnabelleLutter15":
			dialog.text = "Хех, даже другим людям так обо мне говорил? Ох, Мэтт... Но, видимо, нам просто не суждено было состариться вместе - если Левассер положил глаз на женщину, то делал всё, чтобы заполучить её, независимо от происхождения. Сколько бы денег на это не ушло. Сотта ведь как раз один из его капитанов. Был им.";
			link.l1 = "Понятно. И что же вы намерены теперь делать, Эннабел?";
			link.l1.go = "PZ_AnabelleLutter16";
		break;
		
		case "PZ_AnabelleLutter16":
			dialog.text = "Бежать. Туда, где до меня не смогут добраться люди Левассера. Представляться другим именем. Носить другую причёску...";
			link.l1 = "Надеюсь, вам это удастся. Желаю вам успехов, Эннабел.";
			link.l1.go = "PZ_AnabelleLutter17";
			if (sti(pchar.Money) >= 10000)
			{
				link.l2 = "Вам понадобятся деньги, даже чтобы просто попросить начальника порта найти для вас ближайшее судно. Возьмите. Здесь десять тысяч песо.";
				link.l2.go = "PZ_AnabelleLutter17_Peso";
			}
			if (PCharDublonsTotal() >= 100)
			{
				link.l3 = "Для этого вам понадобится немало средств. Не каждый согласится помочь темнокожей девушке, даже полукровке. Поэтому держите, здесь сто дублонов - найдите корабль и спрячьтесь.";
				link.l3.go = "PZ_AnabelleLutter17_Dublon";
			}
		break;
		
		case "PZ_AnabelleLutter17":
			dialog.text = "И я вам! Прощайте, капитан.";
			link.l1 = "Прощайте.";
			link.l1.go = "Exit";
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddDialogExitQuest("PZ_AnabelleGo");
		break;
		
		case "PZ_AnabelleLutter17_Peso":
			dialog.text = "Я... Не знаю, что и сказать. Никто, кроме Мэтта, никогда не был столь добр ко мне.";
			link.l1 = "Может, это знак? Что вы, всё же, счастливо состаритесь где-нибудь. Прощайте.";
			link.l1.go = "Exit";
			AddMoneyToCharacter(pchar, -10000);
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			AddDialogExitQuest("PZ_AnabelleGo");
		break;
		
		case "PZ_AnabelleLutter17_Dublon":
			dialog.text = "Вы правы. Спасибо вам огромное, что учли это. Я буду вспоминать вас в своих молитвах всю жизнь.";
			link.l1 = "Спасибо и вам. До свидания.";
			link.l1.go = "Exit";
			RemoveDublonsFromPCharTotal(100);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			AddDialogExitQuest("PZ_AnabelleGo");
		break;
		
		case "PZ_Longway_47":
			dialog.text = "Этот человек... Нет, он уже не быть человек. Он быть зверь. Чудовище. Этот чудовище пытать женщины...";
			link.l1 = "Я понимаю, о чём ты подумал, Лонгвэй. Но ты слышал - у него никогда не было желтокожих женщин.";
			link.l1.go = "PZ_Longway_48";
			SetCameraDialogMode(npchar);
		break;
		
		case "PZ_Longway_48":
			dialog.text = "Но он знать весь этот банда! Ван дер Винк, Ферментелуш, Сотта... Мы сейчас только что прочитать это в его журнал. Что, если та самая 'она' - это... она?";
			link.l1 = "Кто знает... Женщина, что мечтала отомстить Ферментелушу за что-то - понимаю, почему ты так подумал. Но это могла быть любая женщина, жизнь которой когда-то сломал Оливерио. Необязательно твоя сестра. Необязательно даже желтокожая.";
			link.l1.go = "PZ_Longway_49";
		break;
		
		case "PZ_Longway_49":
			dialog.text = "Ваш... отказываться это проверить, господин капитан? В самый последний момент?..";
			link.l1 = "Нет, Лонгвэй. Но как ты себе это представляешь? Навряд ли Левассер ответит хоть на один из наших вопросов. А вынюхивать это в Тортуге вот так - слишком опасно.";
			link.l1.go = "PZ_Longway_50";
		break;
		
		case "PZ_Longway_50":
			dialog.text = "И что же вы предлагать?";
			link.l1 = "Выждать. Мы знаем, что Левассер не любит желтокожих женщин. Так что можем запастись силами. Терпением и силами. Франсуа - крепкий орешек, не в последнюю очередь благодаря своей 'черепашке'. Но с помощью Свенсона мы сможем поговорить с ним по душам, на наших условиях. Я ведь уже пообещал тебе, что обязательно помогу найти сестру. Хорошо, Лонгвэй?";
			link.l1.go = "PZ_Longway_51";
		break;
		
		case "PZ_Longway_51":
			dialog.text = "Хм-м-м... Хорошо, господин капитан. Тогда у мой быть ещё один просьба к вам.";
			link.l1 = "Что, снова хочешь отлучиться на месяц? В прошлый раз это не слишком хорошо закончилось.";
			link.l1.go = "PZ_Longway_52";
		break;
		
		case "PZ_Longway_52":
			dialog.text = "Что вы, господин капитан. Мой понять, что, к сожалению, не мочь искать что-либо один в мире белый люди. Лонгвэй просить вас причалить вас в Капстервиль, чтобы мой написать и передать его ещё один записка - быть мочь, Жорж Гравель узнать что-нибудь, пока вы готовиться.";
			link.l1 = "Разумная мысль, Лонгвэй. Так и поступим.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TeleportToShore");
		break;
		
		case "PZ_Longway_53":
			dialog.text = "Господин капитан, тут такой дело...";
			link.l1 = "Ты забыл написать письмо? Можно ведь пойти и спросить Гравеля обо всём без письма. Ну или договориться о встрече.";
			link.l1.go = "PZ_Longway_54";
		break;
		
		case "PZ_Longway_54":
			dialog.text = "Нет, письмо быть готово. Но Лонгвэй думать, что его лучше не расхаживать по город один. Господин капитан... ваш мочь передать письмо Жорж? Пожалуйста?";
			link.l1 = "Я что, похож на почтальона? Или, может быть, это ты капитан из нас двоих?";
			link.l1.go = "PZ_Longway_55";
		break;
		
		case "PZ_Longway_55":
			dialog.text = "Господин капитан...";
			link.l1 = "Ха-ха-ха, я шучу, Лонгвэй! Напомни, где искать этого твоего Гравеля?";
			link.l1.go = "PZ_Longway_56";
		break;
		
		case "PZ_Longway_56":
			dialog.text = "Он работать служка в церковь. Значит, искать его нужно там.";
			link.l1 = "Ну хорошо.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_ToCapstervilleChurch");
			AddLandQuestMark(characterFromId("Charles_Priest"), "questmarkmain");
		break;
		
		// Этап 5
		case "PZ_Mary_Sharptown1":
			dialog.text = "Шарль, дорогой мой Шарль, у тебя что-то случилось? Ты выглядишь взволнованным и... уставшим, да!";
			link.l1 = "О, нет-нет, Мэри, всё хорошо. Просто... эти поиски, которые уже наверняка зашли в тупик... А потом ещё и завещание Шарпа, будь оно неладно. Не бери в голову, в общем.";
			link.l1.go = "PZ_Mary_Sharptown2";
		break;
		
		case "PZ_Mary_Sharptown2":
			dialog.text = "Что? Какие поиски? И причём тут твой Шарп? Я ничего не понимаю, да!";
			link.l1 = "Слишком много вопросов, Мэри. И здесь не место для таких разговоров. Давай обсудим это... в комнате таверны? Всё как ты любишь, без лишних глаз и ушей.";
			link.l1.go = "PZ_Mary_Sharptown3";
		break;
		
		case "PZ_Mary_Sharptown3":
			dialog.text = "Да, давай! Но учти: если ты что-то скрываешь...";
			link.l1 = "Ни в коем случае! Ну, пойдём, время у нас ещё есть.";
			link.l1.go = "PZ_HelenaMary_Exit";
		break;
		
		case "PZ_Helena_Sharptown1":
			dialog.text = "Как странно, правда, Шарль? В моём владении должен находиться этот самый остров, но я абсолютно не чувствую себя его хозяйкой.";
			link.l1 = "Даже не знаю, с чем это может быть связано...";
			link.l1.go = "PZ_Helena_Sharptown2";
		break;
		
		case "PZ_Helena_Sharptown2":
			dialog.text = "Ох, эта твоя ухмылка... Умеешь ты найти к даме подход. Но... что с тобой? На тебе лица нет!";
			link.l1 = "А что? Вроде всё как обычно.";
			link.l1.go = "PZ_Helena_Sharptown3";
		break;
		
		case "PZ_Helena_Sharptown3":
			dialog.text = "Шарль, ну я же вижу: ты последнее время какой-то поникший, даже в твоём голосе это отражается.";
			link.l1 = "Столько дел навалилось, особенно с Лонгвэем. У меня просто уже нет сил этим заниматься. Но и сдаваться поздно, тем более, я же дал обещание.";
			link.l1.go = "PZ_Helena_Sharptown4";
		break;
		
		case "PZ_Helena_Sharptown4":
			dialog.text = "Не понимаю... Причём тут Лонгвэй? И какое обещание ты ему дал?";
			link.l1 = "Если мы и будем обсуждать это, то только в таверне, а если быть точнее, то в её комнате наверху. Подальше от остальных.";
			link.l1.go = "PZ_Helena_Sharptown5";
		break;
		
		case "PZ_Helena_Sharptown5":
			dialog.text = "Ладно, пойдём. Всё равно нечем заняться, так хоть время вместе проведём.";
			link.l1 = "Веди, дорогая!";
			link.l1.go = "PZ_HelenaMary_Exit";
		break;
		
		case "PZ_HelenaMary_Exit":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) Return_MaryOfficer();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) Return_HelenaOfficer();
			WaitDate("", 0, 0, 0, 2, 0);
			LAi_SetImmortal(npchar, true);
			ChangeCharacterAddressGroup(npchar, "Pirates_tavern_upstairs", "goto", "goto1");
			DoQuestReloadToLocation("Pirates_tavern_upstairs", "goto", "goto2", "PZ_Etap5_NaverhuTavernBandits");
		break;
		
		case "PZ_Etap5_NaverhuTavernBandits_1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Поглядите, как они сладко спят в объятиях друг друга! Какая прелесть!";
				link.l1 = "Завидуешь?";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Ну наконец-то. Как поспали, голубки?";
				link.l1 = "Прекрасно, спасибо, что спросил. А вам как вместе спалось?";
			}
			link.l1.go = "PZ_Etap5_NaverhuTavernBandits_2";
			locCameraFromToPos(2.34, 1.92, 1.66, true, -1.66, -0.69, -0.02);
		break;
		
		case "PZ_Etap5_NaverhuTavernBandits_2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Глупый вопрос, не находишь?";
				link.l1 = "Действительно. А с вашей стороны - глупый поступок. Хочешь знать, почему?";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Верно про тебя говорят, что у тебя острый язык, Шарль де Мор.";
				link.l1 = "И не только язык. Полагаю, хочешь проверить? Но скажи мне, почему ты не напал, пока мы спали? Не то чтобы у вас появилось больше шансов...";
			}
			link.l1.go = "PZ_Etap5_NaverhuTavernBandits_3";
		break;
		
		case "PZ_Etap5_NaverhuTavernBandits_3":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "И почему же?";
				link.l1 = "Не стоит злить Мэри с утра. Сейчас ты в этом убедишься.";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Всё просто - пока вы спали, в темноте было не разглядеть, кто из вас девушка.";
				link.l1 = "Ах ты мерзавец!";
			}
			link.l1.go = "PZ_Etap5_NaverhuTavernBandits_4";
		break;
		
		case "PZ_Etap5_NaverhuTavernBandits_4":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Я, в отличие от тебя, баб не боюсь. Кстати, о ней! Парни, её брать целой и невредимой, иначе гугенот нас самих бабами сделает!";
				link.l1 = "Гугенот?..";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Зато как мужчина хотя бы выгляжу. Ребята, ту девочку из этих двоих, что блондинка, брать живой - гугенот уже её совсем заждался.";
				link.l1 = "Гугенот, говоришь...";
			}
			link.l1.go = "PZ_Etap5_NaverhuTavernBandits_5";
		break;
		
		case "PZ_Etap5_NaverhuTavernBandits_5":
			DialogExit();
			LAi_SetFightMode(pchar, true);
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("PZ_NaverhuTavernBandits_"+i);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				
				LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
				LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
				LAi_group_SetCheck("EnemyFight", "PZ_Etap5_NaverhuTavernBandits_Win");
			}
		break;
		
		case "PZ_MaryHelena_BitvaNaverhu_1":
			DelLandQuestMark(npchar);
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Кто это был, Шарль? Что ещё за гугенот?! Неужели это...";
				link.l1 = "Больше некому, Мэри. И лучше бы нам...";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Шарль... что это сейчас было? Гугенот? Это тот человек, о котором я думаю?";
				link.l1 = "Боюсь, что да, Элен. Нам нужно...";
			}
			link.l1.go = "PZ_MaryHelena_BitvaNaverhu_2";
		break;
		
		case "PZ_MaryHelena_BitvaNaverhu_2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Ты слышишь? Кто-то идёт, да. Видимо, дружки этих мертвецов.";
				link.l1 = "Тогда отправим их следом. Приготовься...";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Слышишь? Шаги.";
				link.l1 = "И правда. Встань позади меня.";
			}
			link.l1.go = "PZ_MaryHelena_BitvaNaverhu_3";
		break;
		
		case "PZ_MaryHelena_BitvaNaverhu_3":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) Return_MaryOfficer();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) Return_HelenaOfficer();
			sld = CharacterFromID("Longway");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Longway_61";
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			RemovePassenger(pchar, sld);
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "PZ_Longway_61":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Мэри";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Элен";
			dialog.text = "Господин капитан, госпожа " + sStr + ".";
			link.l1 = "Лонгвэй?! Думаешь, можешь так спокойно заходить в комнату, когда я с " + sStr + "? А если бы мы?..";
			link.l1.go = "PZ_Longway_62";
			
			//заранее создаём заглушку для корабля
			sld = GetCharacter(NPC_GenerateCharacter("PZ_ShipStasis", "citiz_46", "man", "man", sti(pchar.rank), PIRATE, -1, false, "quest"));
			SetSPECIAL(sld, 1, 1, 1, 1, 1, 1, 1);
		break;
		
		case "PZ_Longway_62":
			dialog.text = "Хм, просить прощение, господин капитан. Мой думать, что в таком случае ваш бы закрыть дверь. Но Лонгвэй обнаружить, что она быть открыта.";
			link.l1 = "Выломана, а не открыта. Но скажи-ка, друг мой, а почему это ты так чертовски спокоен? На полу трупы, мы, мягко говоря, встревожены, а ты...";
			link.l1.go = "PZ_Longway_63";
		break;
		
		case "PZ_Longway_63":
			dialog.text = "Ну, мой привыкнуть, что мы постоянно кому-то противостоять.";
			link.l1 = "И не поспоришь ведь. И что, ты и правда не слышал звуков боя по пути к нам? Не видел, как эти ребята зашли в таверну и поднялись по лестнице прямо перед тобой? Слишком уж медленными и спокойными были твои шаги.";
			link.l1.go = "PZ_Longway_64";
		break;
		
		case "PZ_Longway_64":
			dialog.text = "Нет, господин капитан. Когда мой решить подняться, в зала никого странного не быть.";
			link.l1 = "Забавное совпадение. Ну ладно. Так что ты хотел, Лонгвэй?";
			link.l1.go = "PZ_Longway_65";
		break;
		
		case "PZ_Longway_65":
			dialog.text = "Мой срочно нужен корабль и команда, господин капитан.";
			link.l1 = "Чего? А зачем? Ты вышел на след Чанг Шин? В таком случае, отправляемся немедленно. Но вместе.";
			link.l1.go = "PZ_Longway_66";
		break;
		
		case "PZ_Longway_66":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Мэри";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Элен";
			dialog.text = "Выйти, верно. Но не Чанг Шин, увы. А... Сепп ван дер Винк. К мой подойти человек от Жорж Гравель и вручить письмо, покуда мой прогуливаться по город, а ваш... отдыхать с " + sStr + ".";
			link.l1 = "Да уж, отлично отдохнул, ничего не скажешь. И к чему нам разделяться, Лонгвэй? У нас, конечно, немало задач и недругов, которых не помешает изловить, но всё же.";
			link.l1.go = "PZ_Longway_67";
		break;
		
		case "PZ_Longway_67":
			dialog.text = "Ван дер Винк не быть так опасен, как Левассер или кто-то другой. К тому же, мой уже побеждать его однажды. И победить снова. На этот раз - убедиться, что навсегда. Так что мы не терять драгоценный время. Ваш отправиться на Тортуга и расспрашивать важный люди про всё, что наш нужно. А мой - поймать ван дер Винк. Сам, ведь мой уметь управлять корабль, и хорошо. Господин капитан не стоит тратить время на это.";
			link.l1 = "Хм, в твоих словах есть смысл, Лонгвэй. Но ван дер Винк, может, и не так опасен, однако “Бантен” - один из быстрейших кораблей Архипелага, как мне кажется. Тут подойдёт не каждое судно. И где же ты найдёшь команду, да еще так быстро?";
			link.l1.go = "PZ_Longway_68";
		break;
		
		case "PZ_Longway_68":
			dialog.text = "Мой знать... нужный место. И сохранить там связь. Ну или притвориться, что сохранить, как в случай с Жорж. Так действовать господин Роденбург, когда он срочно нуждаться в очень хороший команда на один раз, который не будет задавать вопросов.";
			link.l1 = "Команда наёмников, значит... Логично. И сколько тебе понадобится на то, чтобы провернуть всё это самостоятельно?";
			link.l1.go = "PZ_Longway_69";
		break;
		
		case "PZ_Longway_69":
			dialog.text = "Два с половиной тысяча.";
			link.l1 = "Всего-то? Да на то, чтобы нанять полный комплект обычных матросов из таверны, порой может уйти больше, особенно, если на большой корабль. Хех, видимо, для Роденбурга и его людей в особых местах и цены особые.";
			link.l1.go = "PZ_Longway_70";
		break;
		
		case "PZ_Longway_70":
			dialog.text = "Мой иметь ввиду дублоны, господин капитан.";
			link.l1 = "ЧТО?!";
			link.l1.go = "PZ_Longway_70_1";
		break;
		
		case "PZ_Longway_70_1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) StartInstantDialog("Mary", "PZ_Longway_70_2", "Quest\CompanionQuests\Longway.c");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) StartInstantDialog("Helena", "PZ_Longway_70_2", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Longway_70_2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Вот именно! Да это же грабёж средь бела дня, да! Шарль, почему бы нам просто не дать Лонгвэю денег на честных работяг из таверн, а не мутных личностей, которые просто убьют дело, поделят золото или даже угонят корабль.";
				link.l1 = "Идея, конечно, хорошая, но не думаю, что всё так просто. Будь это можно сделать - Лонгвэй предложил бы нам именно это. Ты уверен, что это надёжно, друг мой? И что на это действительно нужно СТОЛЬКО золота?..";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Шарль, постарайся успокоиться. Цена, конечно, неоправданно велика, но мне кажется, в этом есть смысл. Целая команда наёмников, готовая тут же отправиться на дело, само собой, будет стоить целое состояние.";
				link.l1 = "Да я понимаю. Эх, ты, конечно, права, как всегда, Элен. Просто до сих пор не могу поверить в то, что я услышал.";
			}
			link.l1.go = "PZ_Longway_70_3";
		break;
		
		case "PZ_Longway_70_3":
			StartInstantDialog("Longway", "PZ_Longway_70_4", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Longway_70_4":
			dialog.text = "Ваш прекрасно слышать, судя по ваш реакция. И, к сожаление, быть нужен именно столько золото. Это действительно важно, господин капитан. Мой бы не просить подобный сумма ради пустяк.";
			link.l1 = "Да слышал, конечно, просто всё ещё не могу поверить. Действительно, особые цены, чёрт побери. А песо принимают в твоих местах?";
			link.l1.go = "PZ_Longway_70_5";
		break;
		
		case "PZ_Longway_70_5":
			dialog.text = "Да... для белый люди. У Лонгвэй с этим мочь быть трудности, но... думать, мой суметь их убедить. Связи или сила - способ обязательно найтись.";
			link.l1 = "Ну хоть что-то. И это только на людей... А тебе ведь ещё и на корабль нужно. Наверное, тоже в каком-нибудь 'особом месте'? Боюсь спросить, сколько...";
			link.l1.go = "PZ_Longway_70_6";
		break;
		
		case "PZ_Longway_70_6":
			dialog.text = "Нисколько, господин капитан - мой учесть покупка корабль, когда назвать цена. Но...";
			link.l1 = "Но?";
			link.l1.go = "PZ_Longway_70_7";
		break;
		
		case "PZ_Longway_70_7":
			dialog.text = "'Мейфенг' помочь. Если ваш её сохранить где-то, это мочь стать решающий фактор - нет на Архипелаг корабль быстрее.";
			link.l1 = "Ну, есть один. Говорят, он очень быстроходен. Даже неуловим.";
			link.l1.go = "PZ_Longway_70_8";
		break;
		
		case "PZ_Longway_70_8":
			dialog.text = "Что это быть за корабль, господин капитан???";
			link.l1 = "А? Неважно, это я так, задумался.";
			link.l1.go = "PZ_Longway_70_9";
		break;
		
		case "PZ_Longway_70_9":
			dialog.text = "Так ваш поделиться этот сумма с Лонгвэй, господин капитан?";
			if (PCharDublonsTotal() >= 2500)
			{
				link.l1 = "Даже не припоминаю, отдавал ли когда-нибудь в жизни столько золота сразу... Но для тебя, Лонгвэй - так тому и быть. Держи. Две с половиной тысячи. И чтобы принёс мне голову ван дер Винка на блюдце из чистого золота, ха-ха-ха!";
				link.l1.go = "PZ_Longway_Dublons_1";
			}
			if (sti(pchar.Money) >= 300000)
			{
				link.l2 = "Я не ношу с собой столько дублонов, Лонгвэй. И даже сомневаюсь, что у меня найдётся такое количество на корабле - не так уж и часто они нужны. А песо - пожалуйста. Прошу. Триста тысяч, ровно столько, сколько тебе и нужно.";
				link.l2.go = "PZ_Longway_Peso_1";
			}
			link.l3 = "Знаешь-ка что, Лонгвэй... Прекращай валять дурака! Ты сейчас мне предлагаешь пойти на обычного разбойника из сельвы, купив перед этим оружие и кирасу из чистого золота, понимаешь?!";
			link.l3.go = "PZ_Longway_Otkaz";
		break;
		
		case "PZ_Longway_Dublons_1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) AddQuestUserData("PZ", "sText", "Мэри");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) AddQuestUserData("PZ", "sText", "Элен");
			
			dialog.text = "Вот это да... Лонгвэй снова благодарить вас от вся душа, господин капитан! Но, всё же, что насчёт 'Мейфенг'?";
			if (FindCompanionShips(SHIP_MAYFANG))
			{
				link.l1 = "А что 'Мейфенг'? Ты забываешь, по палубам каких кораблей мы с тобой ходим, друг мой?";
				link.l1.go = "PZ_Longway_Mayfang1";
			}
			else
			{
				link.l1 = "Мне нужно подумать об этом, Лонгвэй. Хорошо так подумать. Сколько у нас времени на поимку ван дер Винка?";
				link.l1.go = "PZ_Longway_NoMayfang1";
			}
			RemoveDublonsFromPCharTotal(2500);
			pchar.questTemp.PZ_FlagShipDublons = true;
			notification("Лонгвэй одобряет", "Longway");
		break;
		
		case "PZ_Longway_Peso_1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) AddQuestUserData("PZ", "sText", "Мэри");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) AddQuestUserData("PZ", "sText", "Элен");
			
			dialog.text = "Господин капитан, ваш немного ошибиться. В песо это быть двести пятьдесят тысяча.";
			link.l1 = "Я не ошибся, это особая математика Шарля де Мора, когда его друзьям нужна помощь, ха-ха. Специально даю с довеском, чтобы тебе точно на всё хватило.";
			link.l1.go = "PZ_Longway_Peso_2";
			AddMoneyToCharacter(pchar, -300000);
		break;
		
		case "PZ_Longway_Peso_2":
			dialog.text = "Спасибо ваш огромный, господин капитан... Но, сказать, пожалуйста, а что по повод 'Мейфенг'?";
			if (FindCompanionShips(SHIP_MAYFANG))
			{
				link.l1 = "А что 'Мейфенг'? Ты забываешь, по палубам каких кораблей мы с тобой ходим, друг мой?";
				link.l1.go = "PZ_Longway_Mayfang1";
			}
			else
			{
				link.l1 = "Мне нужно подумать об этом, Лонгвэй. Хорошо так подумать. Сколько у нас времени на поимку ван дер Винка?";
				link.l1.go = "PZ_Longway_NoMayfang1";
			}
		break;
		
		case "PZ_Longway_Otkaz":
			dialog.text = "Другой путь нет, господин капитан, пожалуйста, успокоиться...";
			link.l1 = "О, я ещё не начинал. Значит, так. Вот тебе пятьдесят тысяч. Этого впритык хватит, чтобы купить на верфи бриг, приготовить его к бою и даже нанять команду.";
			link.l1.go = "PZ_Longway_Otkaz_2";
			AddMoneyToCharacter(pchar, -50000);
			
			pchar.questTemp.PZ.LongwayBrig = true; // Лонгвэй будет на бриге
			notification("Лонгвэй не одобряет", "Longway");
		break;
		
		case "PZ_Longway_Otkaz_2":
			dialog.text = "Но, господин капитан!.. Этого хватать для белый капитан! Не всякий согласиться иметь дело с Лонгвэй даже. А если кто и захочет, то лишь после того, как поднять цена!";
			link.l1 = "Значит, будь поубедительнее! Торговаться ты вполне умеешь, судя по твоему изначальному... деловому предложению. Ты ещё здесь? Бери эти деньги - и пошёл, раз так мало времени!";
			link.l1.go = "PZ_Longway_Otkaz_3";
		break;
		
		case "PZ_Longway_Otkaz_3":
			dialog.text = "Да, господин капитан...";
			link.l1 = "И не смотри на меня так. Увидимся потом на Тортуге. Удачи.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_NeedToTortuga");
			AddQuestRecord("PZ", "58");
		break;
		
		case "PZ_Longway_Mayfang1":
			dialog.text = "Кхм, нет, господин капитан. Конечно, мой помнить. Лонгвэй просто спрашивать вас, готов ли ваш поделиться её с мой.";
			link.l1 = "Самой собой, готов. Ведь ван дер Винк причастен к несчастьям твоей сестры так же, как и остальные. Так что поймать его действительно важно. Заберёшь её в порту.";
			link.l1.go = "PZ_Longway_Mayfang2";
		break;
		
		case "PZ_Longway_Mayfang2":
			// если "Мейфенг" у ГГ
			if (FindCompanionShips(SHIP_MAYFANG))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MAYFANG)
						{
							//pchar.questTemp.PZ.Mayfang.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.Mayfang.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
			}
			
			pchar.questTemp.PZ.LongwayMayfang = true;
			pchar.questTemp.PZ_FlagShip = true;
			
			dialog.text = "Мой не мочь поверить... Благодарить ваш, господин капитан!!!";
			link.l1 = "А, пустое. Когда-то же это был твой корабль. Я помню. Ну, иди, удачной охоты! А я пока отправлюсь на Тортугу.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_NeedToTortuga");
			AddQuestRecord("PZ", "59");
			notification("Лонгвэй одобряет", "Longway");
		break;
		
		
		case "PZ_Longway_NoMayfang1":
			dialog.text = "О, на этот раз время терпеть, господин капитан. Но наш не стоит его тратить в любой случай - наш ведь ещё спасать Чанг Шин...";
			link.l1 = "Я понимаю это, Лонгвэй. И всё же, как ты думаешь, именно на поимку ван дер Винка - сколько?";
			link.l1.go = "PZ_Longway_NoMayfang2";
		break;
		
		case "PZ_Longway_NoMayfang2":
			dialog.text = "Пара месяц - его ходить регулярный рейс примерно столько время перед тем, как надолго пропадать где-то. Такой быть его образ жизни, как сообщить мне Гравель в свой письмо.";
			link.l1 = "Ну хорошо. Давай тогда сходим на корабль, и...";
			link.l1.go = "PZ_Longway_NoMayfang3";
		break;
		
		case "PZ_Longway_NoMayfang3":
			dialog.text = "Боюсь, что мой нужно срочно начать готовиться, господин капитан. Чтобы потом сразу же приступить. Вступать в переговоры с людьми в нужный место заранее. Мой добраться туда сам - найти способ. Не переживать за Лонгвэй.";
			link.l1 = "Так где же это твоё место, в котором ты наймёшь 'особую команду'?";
			link.l1.go = "PZ_Longway_NoMayfang4";
		break;
		
		case "PZ_Longway_NoMayfang4":
			AddQuestRecord("PZ", "60");
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) AddQuestUserData("PZ", "sText", "Мэри");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) AddQuestUserData("PZ", "sText", "Элен");
			
			i = FindColony("Pirates");
			if (colonies[i].nation != ENGLAND)
			{
				dialog.text = "Прямо здесь. Но для ваш удобство мы мочь встретиться на верфь.";
				link.l1 = "И почему я только сейчас узнаю о том, что тут можно нанимать готовую команду наёмников? Да ещё и за такие цены...";
				link.l1.go = "PZ_Longway_NoMayfangIslaTesoro1";
			}
			else
			{
				dialog.text = "Здесь. Раньше эти люди собираться в Исла-Тесоро, но затем быть вынуждены убраться сюда.";
				link.l1 = "Эх, понятное дело, почему. И где же мне тебя искать в Ла Веге?";
				link.l1.go = "PZ_Longway_NoMayfangLaVega1";
			}
		break;
		
		case "PZ_Longway_NoMayfangIslaTesoro1":
			dialog.text = "Потому что об это очень мало кто знать. И ещё меньше - мочь позволить. Чаще всего их нанимать господин Роденбруг. Очень мало быть другой клиент.";
			link.l1 = "Понятно. Ну хорошо, Лонгвэй. Попутного ветра. До встречи на месте.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_LongwayToPiratesShipyard");
		break;
		
		case "PZ_Longway_NoMayfangLaVega1":
			dialog.text = "Таверна, господин капитан. Где же быть ещё?";
			link.l1 = "И то верно. Тогда до встречи, Лонгвэй! Береги себя.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_LongwayToLaVegaTavern");
		break;
		
		case "PZ_Longway_WaitForShip1":
			dialog.text = "Господин капитан, мой спешить сообщить ваш, что команда быть готова. Осталось решить последний вопрос. Так что же быть с 'Мейфенг'?";
			link.l1 = "Пока что я не подобрал действительно достойный тебя корабль, Лонгвэй.";
			link.l1.go = "PZ_Longway_WaitForShip2";
			if ((FindCompanionShips(SHIP_SCHOONER_W)) || (FindCompanionShips(SHIP_BRIG)) || (FindCompanionShips(SHIP_CORVETTE)) || (FindCompanionShips(SHIP_POLACRE)) || (FindCompanionShips(SHIP_XebekVML)) || (FindCompanionShips(SHIP_BRIGANTINE)))
			{
				if (FindCompanionShips(SHIP_SCHOONER_W)) sStr = "военную шхуну";
				if (FindCompanionShips(SHIP_BRIG)) sStr = "бриг";
				if (FindCompanionShips(SHIP_CORVETTE)) sStr = "корвет";
				if (FindCompanionShips(SHIP_POLACRE)) sStr = "полакр";
				if (FindCompanionShips(SHIP_XebekVML)) sStr = "шебеку";
				if (FindCompanionShips(SHIP_BRIGANTINE)) sStr = "бригантину";
				link.l2 = "Забирай '" + sStr + "'.";
				link.l2.go = "PZ_Longway_NoQuestShip1";
			}
			if (FindCompanionShips(SHIP_MAYFANG))
			{
				link.l3 = "А что 'Мейфенг'? Думал, я её не сберёг?";
				link.l3.go = "PZ_Longway_Mayfang3";
			}
			if (FindCompanionShips(SHIP_CURSED_FDM))
			{
				link.l4 = "У меня для тебя... особенный корабль, Лонгвэй. Быстрый. И ещё более - смертоносный. Это... Военный галеон 'Летящее сердце'.";
				link.l4.go = "PZ_Longway_Caleuche1";
			}
			if (FindCompanionShips(SHIP_POLACRE_QUEST))
			{
				link.l5 = "Ты ведь любишь шебеки, Лонгвэй. А что насчёт полакров? Особенно этого, 'Тореро'. Не для регат, конечно, судно, но довольно-таки мощное.";
				link.l5.go = "PZ_Longway_Torero1";
			}
			if (FindCompanionShips(SHIP_ELCASADOR))
			{
				link.l6 = "Признаться, не думал, что однажды ему найдётся достойное применение. Что думаешь по поводу этого галеона 'Эль Касадор'?";
				link.l6.go = "PZ_Longway_ElCasador1";
			}
		break;
		
		case "PZ_Longway_NoQuestShip1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Мэри";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Элен";
			
			// а теперь хором, дети: ненавижу костыли, ненавижу костыли, ненавижу костыли, нена... помогите!!!
			if ((FindCompanionShips(SHIP_SCHOONER_W)) && (!FindCompanionShips(SHIP_BRIG)) && (!FindCompanionShips(SHIP_CORVETTE)) && (!FindCompanionShips(SHIP_POLACRE)) && (!FindCompanionShips(SHIP_XebekVML)) && (!FindCompanionShips(SHIP_BRIGANTINE)))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_SCHOONER_W)
						{
							//pchar.questTemp.PZ.SchoonerW.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.SchoonerW.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
				
				pchar.questTemp.PZ.LongwaySchoonerW = true;
			}
			if ((!FindCompanionShips(SHIP_SCHOONER_W)) && (FindCompanionShips(SHIP_BRIG)) && (!FindCompanionShips(SHIP_CORVETTE)) && (!FindCompanionShips(SHIP_POLACRE)) && (!FindCompanionShips(SHIP_XebekVML)) && (!FindCompanionShips(SHIP_BRIGANTINE)))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_BRIG)
						{
							//pchar.questTemp.PZ.Brig.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.Brig.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
				
				pchar.questTemp.PZ.LongwayBrig = true;
			}
			if ((!FindCompanionShips(SHIP_SCHOONER_W)) && (!FindCompanionShips(SHIP_BRIG)) && (FindCompanionShips(SHIP_CORVETTE)) && (!FindCompanionShips(SHIP_POLACRE)) && (!FindCompanionShips(SHIP_XebekVML)) && (!FindCompanionShips(SHIP_BRIGANTINE)))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_CORVETTE)
						{
							//pchar.questTemp.PZ.Corvette.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.Corvette.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
				
				pchar.questTemp.PZ.LongwayCorvette = true;
			}
			if ((!FindCompanionShips(SHIP_SCHOONER_W)) && (!FindCompanionShips(SHIP_BRIG)) && (!FindCompanionShips(SHIP_CORVETTE)) && (FindCompanionShips(SHIP_POLACRE)) && (!FindCompanionShips(SHIP_XebekVML)) && (!FindCompanionShips(SHIP_BRIGANTINE)))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_POLACRE)
						{
							//pchar.questTemp.PZ.Polacre.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.Polacre.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
				
				pchar.questTemp.PZ.LongwayPolacre = true;
			}
			if ((!FindCompanionShips(SHIP_SCHOONER_W)) && (!FindCompanionShips(SHIP_BRIG)) && (!FindCompanionShips(SHIP_CORVETTE)) && (!FindCompanionShips(SHIP_POLACRE)) && (FindCompanionShips(SHIP_XebekVML)) && (!FindCompanionShips(SHIP_BRIGANTINE)))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_XebekVML)
						{
							//pchar.questTemp.PZ.Xebek.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.Xebek.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
				
				pchar.questTemp.PZ.LongwayXebek = true;
			}
			if ((!FindCompanionShips(SHIP_SCHOONER_W)) && (!FindCompanionShips(SHIP_BRIG)) && (!FindCompanionShips(SHIP_CORVETTE)) && (!FindCompanionShips(SHIP_POLACRE)) && (!FindCompanionShips(SHIP_XebekVML)) && (FindCompanionShips(SHIP_BRIGANTINE)))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_BRIGANTINE)
						{
							//pchar.questTemp.PZ.Brigantine.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.Brigantine.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
				
				pchar.questTemp.PZ.LongwayBrigantine = true;
			}
			
			dialog.text = "Это, не 'Мейфенг', господин капитан. Что с 'Мейфенг'?";
			link.l1 = "Лонгвэй! Безопасность " + sStr + " теперь под угрозой! Как и твоей сестры! А ты капризничаешь, что корабль тебе не такой?! Да кто угодно был бы рад такому судну! Забирай его и покажи ван дер Винку, где раки зимуют.";
			link.l1.go = "PZ_Longway_NoQuestShip2";
		break;
		
		case "PZ_Longway_NoQuestShip2":
			dialog.text = "Ладно... Надеяться, что мой справиться. Как надеяться, что и ваш на Тортуга - тоже. До свидание, господин капитан.";
			link.l1 = "Уверен в этом. До свидания, Лонгвэй.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_NeedToTortuga");
			pchar.questTemp.PZ_NoQuestShip = true;
		break;
		
		case "PZ_Longway_Mayfang3":
			// если "Мейфенг" у ГГ
			if (FindCompanionShips(SHIP_MAYFANG))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MAYFANG)
						{
							//pchar.questTemp.PZ.Mayfang.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.Mayfang.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
			}
			
			pchar.questTemp.PZ.LongwayMayfang = true;
			pchar.questTemp.PZ_FlagShip = true;
			
			dialog.text = "Кхм, нет, господин капитан. Лонгвэй просто спрашивать вас, готов ли ваш поделиться её с мой.";
			link.l1 = "Самой собой, готов. Ведь ван дер Винк причастен к несчастьям твоей сестры так же, как и остальные. Так что поймать его действительно важно. Заберёшь её в порту.";
			link.l1.go = "PZ_Longway_Mayfang4";
		break;
		
		case "PZ_Longway_Mayfang4":
			dialog.text = "Мой не мочь поверить... Благодарить ваш, господин капитан!!!";
			link.l1 = "А, пустое. Когда-то же это был твой корабль. Я помню. Ну, иди, удачной охоты! А я пока отправлюсь на Тортугу.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_NeedToTortuga");
			notification("Лонгвэй одобряет", "Longway");
		break;
		
		case "PZ_Longway_Caleuche1":
			dialog.text = "Мой... мой не командовать ЭТИМ, господин капитан. Лонгвэй всё ещё беречь свой жизнь, душа и рассудок.";
			link.l1 = "Ха-ха-ха, Лонгвэй! Надо же, не знал, что ты такой суеверный. Но, в любом случае, проклятие ведь уже снято, тебе нечего бояться.";
			link.l1.go = "PZ_Longway_Caleuche2";
		break;
		
		case "PZ_Longway_Caleuche2":
			dialog.text = "А... а знать ли это ван дер Винк? Он же побежать быстрее испуганный кролик, как только завидеть этот корабль.";
			link.l1 = "Тут ты прав. Ладно, подберём для тебя что-нибудь другое.";
			link.l1.go = "PZ_Longway_WaitForShip2";
		break;
		
		case "PZ_Longway_Torero1":
			// если "Тореро" у ГГ
			if (FindCompanionShips(SHIP_POLACRE_QUEST))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_POLACRE_QUEST)
						{
							//pchar.questTemp.PZ.Torero.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.Torero.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
			}
			
			pchar.questTemp.PZ.LongwayTorero = true;
			if (CheckAttribute(pchar, "questTemp.PZ_FlagShipDublons"))
			{
				pchar.questTemp.PZ_FlagShip = true;
				notification("Лонгвэй одобряет", "Longway");
			}
			
			dialog.text = "Никогда не плавать на полакр, когда быть капитан сам. Думать, это интересно. Но Лонгвэй считать, что сейчас быть самым главным скорость, а не мощь корабль.";
			link.l1 = "Это, конечно, так, но ведь это же полакр. Пусть он и не так быстр, как 'Бантен', но на нём ты сможешь ловить ветер в направлениях, в которых не смогут они. Даже в больших, чем когда-то на 'Мейфенг'. Так что воспользуйся этим преимуществом.";
			link.l1.go = "PZ_Longway_Torero2";
		break;
		
		case "PZ_Longway_Torero2":
			dialog.text = "Всё равно. 'Мейфенг' быть лучше... Жаль, господин капитан. Удача ваш на Тортуга.";
			link.l1 = "И тебе того же, Лонгвэй, спасибо.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_NeedToTortuga");
		break;
		
		case "PZ_Longway_ElCasador1":
			// если "Эль Касадор" у ГГ
			if (FindCompanionShips(SHIP_ELCASADOR))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_ELCASADOR)
						{
							//pchar.questTemp.PZ.ElCasador.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.ElCasador.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
			}
			
			pchar.questTemp.PZ.LongwayElCasador = true;
			if (CheckAttribute(pchar, "questTemp.PZ_FlagShipDublons"))
			{
				pchar.questTemp.PZ_FlagShip = true;
				notification("Лонгвэй одобряет", "Longway");
			}
			
			dialog.text = "Что это быть самый необычный галеон на весь Архипелаг, господин капитан. Мой мочь управиться с ним, однако он медленнее, чем 'Бантен'...";
			link.l1 = "Ну тебе же не в регате с Сеппом состязаться, верно?";
			link.l1.go = "PZ_Longway_ElCasador2";
		break;
		
		case "PZ_Longway_ElCasador2":
			dialog.text = "Всё равно. 'Мейфенг' быть лучше... Жаль, господин капитан. Удача ваш на Тортуга.";
			link.l1 = "Успехов тебе в его поимке Винка, Лонгвэй! Встретимся на Тортуге.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_NeedToTortuga");
		break;
		
		case "PZ_Longway_WaitForShip2":
			NextDiag.TempNode = "PZ_Longway_WaitForShip1";
			
			dialog.text = "Мой ценить ваш забота, господин капитан, но, просить, поторопиться - время оставаться не так много, как ваш казаться.";
			link.l1 = "Я знаю. Но ты же не хочешь отправиться в погоню на корыте, не правда ли? Ладно, пойду искать тебе добротное судно.";
			link.l1.go = "Exit";
		break;
		
		case "PZ_HelenaTortugaCabin_1":
			dialog.text = "Мы почти на месте, Шарль. Ты уже решил, с чего начнём? Может, имеет смысл порасспрашивать людей...";
			link.l1 = "Может, и имеет. Вот только не нам, а мне. Ты останешься на борту, Элен.";
			link.l1.go = "PZ_HelenaTortugaCabin_2";
		break;
		
		case "PZ_HelenaTortugaCabin_2":
			dialog.text = "Шарль, мне, конечно, до сих пор не по себе от визита тех подонков, и на корабле под защитой ребят куда спокойнее, чем на берегу... Но, от того, что ты собираешься сунуться в логово этого зверя в одиночку, мне становится отнюдь не легче.";
			link.l1 = "Понимаю. Но, если что пойдёт наперекосяк, удрать будет куда проще одному, зная, что ты в безопасности. Так что это не обсуждается, Элен. Жди меня здесь и постарайся почём зря не волноваться.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TortugaCabin_Exit");
		break;
		
		case "PZ_MaryTortugaCabin_1":
			dialog.text = "Вот и Тортуга, Шарль, да. Мне уже не терпится поинтересоваться у этого жирного осла, что он от меня хотел...";
			link.l1 = "Именно поэтому ты и останешься на борту, милая моя.";
			link.l1.go = "PZ_MaryTortugaCabin_2";
			
			pchar.questTemp.MarySexBlock = true;
			pchar.quest.Mary_giveme_sex.over = "yes";
			pchar.quest.Mary_giveme_sex1.over = "yes";
		break;
		
		case "PZ_MaryTortugaCabin_2":
			dialog.text = "Ещё чего! Думаешь, я пущу тебя на берег одного?";
			link.l1 = "Думаю, что если Левассер, находясь на своей территории, решит доделать то, что не получилось тогда у его наёмников, шансов на то, чтобы отбиться, у нас не будет вовсе. Не стоит его лишний раз провоцировать, тем более, что сейчас моя цель - не он, а Сепп ван дер Винк.";
			link.l1.go = "PZ_MaryTortugaCabin_3";
		break;
		
		case "PZ_MaryTortugaCabin_3":
			dialog.text = "И что, мне теперь взаперти сидеть прикажешь, да?";
			link.l1 = "Я не приказываю, а прошу, Мэри.";
			link.l1.go = "PZ_MaryTortugaCabin_4";
		break;
		
		case "PZ_MaryTortugaCabin_4":
			dialog.text = "А если с тобой там что-то случится, в какой-нибудь подворотне?";
			link.l1 = "Тогда обещаю: я не буду размахивать клинком, а просто дам дёру. И уверенность в том, что тебе ничего не грозит, поможет мне бежать быстрее. Так что жди меня на корабле и, ради всего святого, не вздумай сунуться на берег, что бы ни случилось.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TortugaCabin_Exit");
		break;
		
		case "PZ_RobertMartin1":
			chrDisableReloadToLocation = true;
			
			dialog.text = "Кто ты? Сомневаюсь, что ты прошёл через весь берег и подошёл ко мне только потому, что тебе срочно захотелось с кем-то поговорить.";
			link.l1 = "Это верно. Шарль де Мор. Робер Мартэн?";
			link.l1.go = "PZ_RobertMartin2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_RobertMartin2":
			dialog.text = "Тот самый? Чёрт, хоть бы не втянул меня во что. Да, это я. Так чего тебе нужно?";
			link.l1 = "Мне сказали, что ты дружишь с Сеппом ван дер Винком, и...";
			link.l1.go = "PZ_RobertMartin3";
		break;
		
		case "PZ_RobertMartin3":
			dialog.text = "Кто это тебе сказал? Кишки бы выпустил. Ну, знакомы мы, и не более того. Мне не нужны проблемы из-за того, что он перешёл тебе дорогу.";
			link.l1 = "Хех, быстро же ты от друзей отказываешься...";
			link.l1.go = "PZ_RobertMartin4";
		break;
		
		case "PZ_RobertMartin4":
			dialog.text = "Ты не подумай. Я тебя не боюсь. Но зачем же идти навстречу неприятностям или даже создавать их? Сеппа я знаю отнюдь не так близко, как тебе сказали. Ищешь его?";
			link.l1 = "Да, вроде того. Я знаю, что он уже покинул Тортугу, но всё равно узнать о нём тут побольше не будет лишним - где был, с кем говорил. Не подсобишь?";
			link.l1.go = "PZ_RobertMartin5";
		break;
		
		case "PZ_RobertMartin5":
			dialog.text = "Тебе это всё равно не поможет, так что... почему нет. В борделе он был. Но не обычном, что для всех. Другом. Думаю, что он тебе по карману, поэтому говорю об этом.";
			link.l1 = "У вас открылся новый бордель? Одного стало уже не хватать?";
			link.l1.go = "PZ_RobertMartin6";
		break;
		
		case "PZ_RobertMartin6":
			dialog.text = "Ну, не то чтобы он был новым, но знает о нём мало кто. И лишь единицы - могут себе позволить. Видимо, пришло и твоё время. Но имей ввиду, принимают там только дублоны. Всучишь серебро - и пинка под зад получишь.";
			link.l1 = "Я как-то сразу понял. И где, говоришь, находится этот ваш бордель?";
			link.l1.go = "PZ_RobertMartin7";
		break;
		
		case "PZ_RobertMartin7":
			dialog.text = "А то здание с колоннами знаешь? Так вот, это оно. А какая там хозяйка!.. Желтокожая, но такая красавица! Ха, смотрю, ты уже замечтался, а?";
			link.l1 = "Хе-хе, вроде того. Спасибо, Робер. Сегодня без неприятностей - ты очень мне помог.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_LighthouseMartinGo");
		break;
		
		case "PZ_MaryTortugaCabin_11":
			dialog.text = "Ну наконец-то ты вернулся, Шарль! Я уже места себе найти не могла, да!";
			link.l1 = "Я ненадолго, Мэри. Тут, видишь ли, вот какое дело... Не буду томить - мне, по делу Лонгвэя, нужно заглянуть в местный бордель.";
			link.l1.go = "PZ_MaryTortugaCabin_12";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_MaryTortugaCabin_12":
			dialog.text = "Я знала, что нельзя тебя отпускать на берег одного. Ты то ли шляпу забыл напялить, и тебе голову напекло... То ли ты ей как следует обо что-то приложился, да!";
			link.l1 = "Мэри, выслушай меня. Возможно, хозяйка этого заведения - сестра Лонгвэя. Чтобы в этом убедиться, мне необходимо с ней увидеться - но только и всего. Сделать это, не оказавшись внутри, я не могу. Но я не хочу, чтобы ты подумала невесть что.";
			link.l1.go = "PZ_MaryTortugaCabin_13";
		break;
		
		case "PZ_MaryTortugaCabin_13":
			dialog.text = "Ты точно не врёшь мне, Шарль?";
			link.l1 = "Мэри, ну посуди сама... Ты когда-нибудь слышала о том, чтобы мужчина предупреждал свою возлюбленную о том...";
			link.l1.go = "PZ_MaryTortugaCabin_14";
		break;
		
		case "PZ_MaryTortugaCabin_14":
			dialog.text = "Не продолжай, Шарль, я даже думать об этом не хочу. Я тебе верю и доверяю. И надеюсь, что ты не задержишься там дольше чем нужно.";
			link.l1 = "Ни на минуту, милая, обещаю. Туда и обратно, увидишь.";
			link.l1.go = "PZ_PredupredilNashuDevushku";
		break;
		
		case "PZ_HelenaTortugaCabin_11":
			dialog.text = "Шарль! А ты вернулся даже быстрее, чем я ожидала. Но что случилось? На тебе лица нет... Ты что-то выяснил о ван дер Винке?";
			link.l1 = "Пока что нет. Кое-что я узнал, но, чтобы продвинуться дальше... Мне необходимо сходить в... бордель. Не за тем, о чём ты могла подумать, конечно же.";
			link.l1.go = "PZ_HelenaTortugaCabin_12";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_HelenaTortugaCabin_12":
			dialog.text = "Бордель, значит. Не знала, что в этих притонах оказывают какие-то ещё услуги, кроме самого очевидного.";
			link.l1 = "Мне нужно побеседовать с хозяйкой, только и всего. И это, по слухам, не простой бордель - а очень дорогое заведение, для членов высшего общества...";
			link.l1.go = "PZ_HelenaTortugaCabin_13";
		break;
		
		case "PZ_HelenaTortugaCabin_13":
			dialog.text = "Ну, то есть как раз для тебя, дорогой. Ладно, я шучу. И всё же, я не в восторге от того, что ты туда собрался.";
			link.l1 = "Я обещаю тебе, что пойду туда строго по делу Лонгвэя. Вполне возможно, хозяйка этого места - его сестра. Я не задержусь там надолго.";
			link.l1.go = "PZ_HelenaTortugaCabin_14";
		break;
		
		case "PZ_HelenaTortugaCabin_14":
			dialog.text = "Само собой. Ты не должен даже говорить мне о подобном. Я ведь никогда не обещала тебе, что не буду спать с другим мужчиной. И всё же, я этого и не делаю. Потому что это нечто само собой разумеющееся.";
			link.l1 = "В иных обстоятельствах я бы взял тебя с собой, но...";
			link.l1.go = "PZ_HelenaTortugaCabin_15";
		break;
		
		case "PZ_HelenaTortugaCabin_15":
			dialog.text = "Ещё только по таким притонам я не ходила. Шарль, не переживай. Я не какая-то ревнивая дура. Вернее, может, и ревнивая, но точно не дура. И тебе верю. Дура!";
			link.l1 = "Спасибо, Элен. Я скоро вернусь.";
			link.l1.go = "PZ_PredupredilNashuDevushku";
		break;
		
		case "PZ_PredupredilNashuDevushku":
			DialogExit();
			LAi_SetActorType(npchar);
			pchar.questTemp.PZ_PredupredilNashuDevushku = true;
		break;
		
		case "PZ_ElitaShluha_1":
			dialog.text = "О, новое лицо в нашем заведении? Добро пожаловать, месье. Еда, выдержанное вино, горячая ванна - всё это вас ждёт, если вам будет по карману провести время с одной из нас.";
			link.l1 = "Благодарю за радушный приём, мадемуазель. Я здесь не за этим. Я ищу кое-кого...";
			link.l1.go = "PZ_ElitaShluha_2";
			
			// Убираем Мартэна с Маяка
			sld = characterFromID("PZ_RobertMartin");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			
			for (i=1; i<=3; i++)
			{
				sld = characterFromID("PZ_MayakPiraty_"+i);
				sld.lifeday = 0;
			}
			
			sld = characterFromID("PZ_RobertMartin_CloneMayakShip");
			sld.lifeday = 0;
			
			locations[FindLocation("Mayak6")].DisableEncounters = false;
			LAi_LocationFightDisable(&Locations[FindLocation("Mayak6")], false);
			RemoveGeometryFromLocation("Mayak6", "smg");
		break;
		
		case "PZ_ElitaShluha_2":
			dialog.text = "Ах, где найти кого-то? Могу весь мир я обойти.";
			link.l1 = "Красиво. Никогда не слышал раньше этих строк.";
			link.l1.go = "PZ_ElitaShluha_3";
		break;
		
		case "PZ_ElitaShluha_3":
			dialog.text = "Ну так. Мы здесь девушки образованные, а не просто куклы. Хозяйка считает это крайне важным для нашего заведения.";
			link.l1 = "Хозяйка! Я как раз её и ищу. Слышал, что она желтокожая. Скажите, это правда? Как её зовут, кстати говоря?";
			link.l1.go = "PZ_ElitaShluha_4";
		break;
		
		case "PZ_ElitaShluha_4":
			dialog.text = "Правда. Но деловая хватка у неё получше многих белых женщин. Зовут её Бэлль Этуаль. Но довольно разговоров.";
			link.l1 = "Довольно разговоров, говорите? Я здесь сугубо для них. Задам ещё несколько - и уйду.";
			link.l1.go = "PZ_ElitaShluha_5";
		break;
		
		case "PZ_ElitaShluha_5":
			dialog.text = "А какую выгоду с этого получит заведение? У нас здесь платят не столько за тело, сколько за время в целом. Хотите поговорить? Пожалуйста. Но деньги вперёд. И пошепчемся без ушей в комнате. Чем мы там будем заниматься - без разницы, хоть свечи зажигать и молиться. Один мой клиент просил помочь ему в написании поэмы. Другой - поговорить о его невзгодах, называл меня своим добрым другом. А вот третий - как раз зажигать свечи, чтобы потом...";
			link.l1 = "Ладно, я не хочу этого знать - и так недавно слушал кое-что очень неприятное. Так сколько с меня?";
			link.l1.go = "PZ_ElitaShluha_6";
		break;
		
		case "PZ_ElitaShluha_6":
			dialog.text = "Двести пятьдесят дублонов. И никакого торга. Если мы понимаем, что перед нами обычный щёголь без гроша - выкидываем без сожалений. А если попросту жадный, пусть и состоятельный - поднимаем цену - всё равно заплатит.";
			if (PCharDublonsTotal() >= 250)
			{
				link.l1 = "Пожалуйста, двести пятьдесят золотых.";
				link.l1.go = "PZ_ElitaShluha_7";
			}
			link.l2 = "Чёрт, ничего себе, дороже, чем в том борделе на Ямайке. Могу я вернуться сюда позже, как схожу за золотом?";
			link.l2.go = "PZ_ElitaShluha_Otkaz_1";
		break;
		
		case "PZ_ElitaShluha_7":
			dialog.text = "Вот и славно. С чего начнём? Ужин, со свечами или без, ванна, беседа?";
			link.l1 = "У меня мало времени, так что я просто задам все свои вопросы. Ведите в комнату.";
			link.l1.go = "PZ_ElitaShluha_IdemVKomnatu";
			RemoveDublonsFromPCharTotal(250);
		break;
		
		case "PZ_ElitaShluha_Otkaz_1":
			dialog.text = "Ну конечно. Терпение - одна из добродетелей куртизанки. Выкинуть нищего - это одно. А позволить состоятельному господину вроде вас сходить за своими средствами или даже занять ради одной из нас - совершенно другое.";
			link.l1 = "Добродетели куртизанки... Иронично. Я скоро вернусь.";
			link.l1.go = "PZ_ElitaShluha_Otkaz_2";
		break;
		
		case "PZ_ElitaShluha_Otkaz_2":
			DialogExit();
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("PZ_ElitaShluha_"+i);
				LAi_CharacterDisableDialog(sld);
			}
			LAi_CharacterEnableDialog(npchar);
			npchar.dialog.filename = "Quest\CompanionQuests\Longway.c";
			npchar.dialog.currentnode = "PZ_ElitaShluha_Again";
		break;
		
		case "PZ_ElitaShluha_Again":
			dialog.text = "С возвращением, месье! Итак, кто же вы? Состоятельный господин или щёголь?";
			if (PCharDublonsTotal() >= 250)
			{
				link.l1 = "Ну конечно же, состоятельный господин, мадемуазель. Вот ваше золото, все двести пятьдесят дублонов, можете не пересчитывать.";
				link.l1.go = "PZ_ElitaShluha_Again_1";
			}
			link.l2 = "Мне всё ещё не хватает, потерпите немного.";
			link.l2.go = "exit";
			NextDiag.TempNode = "PZ_ElitaShluha_Again";
		break;
		
		case "PZ_ElitaShluha_Again_1":
			dialog.text = "У нас не пересчитывают. Хм, некоторые монеты выглядят погнутыми и ломаными, хозяйке это, конечно, не очень понравится, но, по крайней мере, это всё настоящее золото.";
			link.l1 = "Какая она у вас... изящная особа.";
			link.l1.go = "PZ_ElitaShluha_Again_2";
			RemoveDublonsFromPCharTotal(250);
		break;
		
		case "PZ_ElitaShluha_Again_2":
			dialog.text = "Это верно. Госпожа Этуаль может быть мягкой и заботливой, может быть строгой, а может быть и беспощадной. Поэтому и не пересчитывают, кстати. Хозяйке платят не сразу. Но всегда. Не золотом - так кровью. Любому дому терпимости нужны защитники и покровители. И нашему заведению они полностью соответствуют по статусу.";
			link.l1 = "Не нужно было это говорить, я ведь заплатил. Ведите.";
			link.l1.go = "PZ_ElitaShluha_IdemVKomnatu";
		break;
		
		case "PZ_ElitaShluha_IdemVKomnatu":
			DialogExit();
			pchar.PZ_ElitaShluha = npchar.id;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "reload", "reload3", "PZ_ElitaShluha_VKomnate", -1);
			LAi_SetActorType(pchar);
			LAi_ActorFollow(pchar, npchar, "", -1);
			bDisableCharacterMenu = true;
		break;
		
		case "PZ_ElitaShluha_8":
			dialog.text = "Так какие у вас вопросы, месье? Постараюсь удовлетворить ваше... любопытство.";
			link.l1 = "Вы знаете, что меня интересует, мадемуазель. Ваша хозяйка, мадам Этуаль.";
			link.l1.go = "PZ_ElitaShluha_9";
		break;
		
		case "PZ_ElitaShluha_9":
			dialog.text = "А что про неё сказать... она остаётся женщиной-загадкой даже для всех нас. Хоть она и заботится о нашем самочувствии, здоровье и безопасности, но не общается и не сближается ни с кем из нас.";
			link.l1 = "Возможно, она не любит долгие беседы. Скажите, она говорит с акцентом?";
			link.l1.go = "PZ_ElitaShluha_10";
		break;
		
		case "PZ_ElitaShluha_10":
			dialog.text = "Нет, с чего вы взяли, просто с того, что она желтокожая? Говорит на чистом французском и ещё на нескольких языках. И способна поддержать многочасовую беседу на любую тему с гостями и потенциальными пайщиками.";
			link.l1 = "Вот как? Хех, занятно... Она сейчас здесь? Если да, то я зайду к ней и не буду более тратить вашего поистине... драгоценного времени, чтобы вы вернулись к работе.";
			link.l1.go = "PZ_ElitaShluha_11";
		break;
		
		case "PZ_ElitaShluha_11":
			dialog.text = "Да было бы к чему возвращаться - не сказать, что у нас отбоя от клиентов нет, сами понимаете. Ведь цель хозяйки - сделать наше заведение лучшим на Архипелаге. Элитарным местом, куда не стыдно зайти ни купцу, ни дворянину, ни просто образованному человеку - ведь мы даём гораздо большее, чем наши тела.";
			link.l1 = "Но ей это не очень удаётся, верно?";
			link.l1.go = "PZ_ElitaShluha_12";
		break;
		
		case "PZ_ElitaShluha_12":
			dialog.text = "Как бы это сказать. Она видит в каждой из нас не просто товар, как в заведениях попроще, но прожект. Дорогая одежда, лекарства, образование - она вкладывается в каждую из нас. И, будь мы в крупном городе Старого Света, ей бы это удалось! Но здесь... Даже талантливый делец ничего не выручит, если выставлять на продажу товар столь дорогой, что почти никто не сможет его купить. Даже если сбивать цены, всё равно однажды мы пойдем по миру.";
			link.l1 = "Сочувствую. Так где сейчас, хозяйка, говорите?";
			link.l1.go = "PZ_ElitaShluha_13";
		break;
		
		case "PZ_ElitaShluha_13":
			dialog.text = "Да нам-то что? Пока что мы живём вполне неплохо, скажу я вам. Впрочем, и требования к нам соответствующие... А госпожа отправилась на Эспаньолу, обсудить возможность перебраться всем нам в Порт-о-Пренс - в конце концов, там сходится больше торговых путей, и мы не будем простаивать и терпеть едва ли не постоянные убытки.";
			link.l1 = "Вот как? А месье Левассер разве не стал вкладываться в её дело?";
			link.l1.go = "PZ_ElitaShluha_14";
		break;
		
		case "PZ_ElitaShluha_14":
			dialog.text = "Не слишком. Был он у нас, сказал, что будет вкладываться по-крупному только, если время от времени мы будем ходить к нему сами. Но госпожа отказалась наотрез. Да так, что Его Светлость опешил на секунду. Никогда не видела такими ни её, ни его.";
			link.l1 = "Хе-хе, ну надо же. Похоже, она знает... Смело, очень смело с её стороны.";
			link.l1.go = "PZ_ElitaShluha_15";
		break;
		
		case "PZ_ElitaShluha_15":
			dialog.text = "Знает что? Впрочем, раз мы с вами так разговорились, скажу вам ещё кое-что, но это большой секрет, так что не вздумайте ни с кем это обсуждать!";
			link.l1 = "Ну что вы, сударыня. Уверяю вас, я ищу вашу хозяйку отнюдь не для того, чтобы навредить ей. Продолжайте.";
			link.l1.go = "PZ_ElitaShluha_16";
		break;
		
		case "PZ_ElitaShluha_16":
			dialog.text = "Да я даже не знаю, удалось бы ли вам это - госпожа Этуаль ежедневно упражняется в фехтовании, и во всём городе у неё нет достойного соперника. Помимо Порт-о-Пренса, она планирует предложить вложиться и самому Маркусу Тираксу! Вернее, взять у него ссуду. Вы представляете?";
			link.l1 = "Да уж, чувствую, мне сегодня тоже предстоит тяжёлый разговор с одной женщиной, которая регулярно упражняется в фехтовании... Ну что же, спасибо, что поделились, сударыня. Удачного вам дня и щедрых клиентов.";
			link.l1.go = "PZ_ElitaShluha_17";
		break;
		
		case "PZ_ElitaShluha_17":
			dialog.text = "Благодарю, сударь. Но куда вы так торопитесь? Вы сполна заплатили, да и говорили мы не так уж и долго. К тому же, есть в вас что-то... утончённое, месье. Нечто гораздо большее, чем у обычных редких толстосумов, что заходят к нам. Может, насладимся обществом друг друга по-настоящему?";
			link.l1 = "Вы знаете... а какого чёрта? Почему я притворяюсь и вру самому себе, будто не хочу этого? Шанс с женщиной вроде вас - большая редкость.";
			link.l1.go = "PZ_ElitaShluha_YesSex";
			link.l2 = "Ох, к сожалению, вынужден вам отказать, мадемуазель. С самого начала я шёл сюда лишь за информацией. К тому же... у меня есть кое-кто, кто меня ждёт.";
			link.l2.go = "PZ_ElitaShluha_NoSex";
		break;
		
		case "PZ_ElitaShluha_NoSex":
			dialog.text = "Как будто это кого-то когда-либо останавливало. В таком случае, вы заслуживаете уважения, сударь. Я очень рада за вашего 'кое-кого'.";
			link.l1 = "Спасибо ещё раз, сударыня. До свидания.";
			link.l1.go = "PZ_ElitaShluha_NoSex_2";
		break;
		
		case "PZ_ElitaShluha_NoSex_2":
			DialogExit();
			AddQuestRecord("PZ", "30");
			chrDisableReloadToLocation = false;
			bDisableFastReload = true;
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("PZ_ElitaShluha_"+i);
				LAi_CharacterDisableDialog(sld);
			}
			npchar.lifeday = 0;
			
			PChar.quest.PZ_TortugaKlemanLebren.win_condition.l1 = "location";
			PChar.quest.PZ_TortugaKlemanLebren.win_condition.l1.location = "Tortuga_town";
			PChar.quest.PZ_TortugaKlemanLebren.win_condition = "PZ_TortugaKlemanLebren";
			DelMapQuestMarkCity("Tortuga");
			AddMapQuestMarkCity("LaVega", false);
			
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1 && !CheckAttribute(pchar, "questTemp.PZ_PredupredilNashuDevushku"))
			{
				setCharacterShipLocation(pchar, "Tortuga_town");
				setWDMPointXZ("Tortuga_town");
			}
		break;
		
		case "PZ_ElitaShluha_YesSex":
			dialog.text = "Благодарю. Как насчёт горячей ванны вместе, для начала?";
			link.l1 = "Обеими руками за.";
			link.l1.go = "PZ_ElitaShluha_YesSex_2";
		break;
		
		case "PZ_ElitaShluha_YesSex_2":
			DialogExit();
			LAi_SetStayType(pchar);
			DoQuestCheckDelay("PlaySex_1", 1.0);
			DoQuestCheckDelay("PZ_ElitaShluha_Fuck", 1.0);
		break;
		
		case "PZ_ElitaShluha_After":
			dialog.text = "Это было прекрасно, месье. Не думала, что мужчина сможет меня удивить. Вы знаете, как доставить удовольствие женщине...";
			link.l1 = "Зависит от женщины.";
			link.l1.go = "PZ_ElitaShluha_After_2";
		break;
		
		case "PZ_ElitaShluha_After_2":
			dialog.text = "Вы жалеете?";
			link.l1 = "Прямо сейчас - определённо нет. До свидания, сударыня.";
			link.l1.go = "PZ_ElitaShluha_After_3";
		break;
		
		case "PZ_ElitaShluha_After_3":
			DialogExit();
			AddQuestRecord("PZ", "30");
			chrDisableReloadToLocation = false;
			bDisableFastReload = true;
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("PZ_ElitaShluha_"+i);
				LAi_CharacterDisableDialog(sld);
			}
			npchar.lifeday = 0;
			LAi_SetPlayerType(pchar);
			pchar.questTemp.PZ.EliteWhoreFucked = true; // флаг того, что секс был (понадобится для диалога с Тираксом)
			
			PChar.quest.PZ_TortugaKlemanLebren.win_condition.l1 = "location";
			PChar.quest.PZ_TortugaKlemanLebren.win_condition.l1.location = "Tortuga_town";
			PChar.quest.PZ_TortugaKlemanLebren.win_condition = "PZ_TortugaKlemanLebren";
			DelMapQuestMarkCity("Tortuga");
			AddMapQuestMarkCity("LaVega", false);
			
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1 && !CheckAttribute(pchar, "questTemp.PZ_PredupredilNashuDevushku"))
			{
				setCharacterShipLocation(pchar, "Tortuga_town");
				setWDMPointXZ("Tortuga_town");
			}
		break;
		
		case "PZ_KlemanLebren_1":
			dialog.text = "Смотри, куда прёшь, хлыщ!";
			link.l1 = "Следи за языком! Толкнул тебя не я!";
			link.l1.go = "PZ_KlemanLebren_2";
		break;
		
		case "PZ_KlemanLebren_2":
			dialog.text = "Я-то смотрел, куда шёл, пока ты ворон считал.";
			link.l1 = "Так обойти же мог, раз смотрел, нет?";
			link.l1.go = "PZ_KlemanLebren_3";
		break;
		
		case "PZ_KlemanLebren_3":
			dialog.text = "А почему это я должен тебя обходить, а не ты меня?!";
			link.l1 = "Предлагаю выяснить за городом, кто, что и кому должен.";
			link.l1.go = "PZ_KlemanLebren_4";
		break;
		
		case "PZ_KlemanLebren_4":
			dialog.text = "Хм-м-м, нет. Уж простите, ваше благородие, не знал, что вам столь противно нечаянное прикосновение простого человека.";
			link.l1 = "Повтори?";
			link.l1.go = "PZ_KlemanLebren_5";
		break;
		
		case "PZ_KlemanLebren_5":
			dialog.text = "Хмм, извини. Я не ставил себе цель толкнуть тебя.";
			link.l1 = "То-то.";
			link.l1.go = "PZ_KlemanLebren_6";
		break;
		
		case "PZ_KlemanLebren_6":
			DialogExit();
			
			LAi_LocationFightDisable(loadedLocation, false);
			chrDisableReloadToLocation = false;
			
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4", "", "", "", "", -1);
			npchar.location = "None";
			
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				sld = CharacterFromID("Mary");
				DelLandQuestMark(sld);
				if (CheckAttribute(pchar, "questTemp.PZ_PredupredilNashuDevushku"))
				{
					PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition.l1 = "location";
					PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition.l1.location = "Tortuga";
					PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition = "PZ_TortugaRazgovorVKauteSDevushkoy";
				}
				else
				{
					ChangeCharacterAddressGroup(sld, "Tortuga_town", "rld", "loc0");
					sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
					sld.dialog.currentnode = "PZ_MaryRazgovorOBordeli_Bad_1";
					LAi_SetStayType(sld);
					CharacterTurnToLoc(sld, "quest", "quest1");
					sld.talker = 5;
					chrDisableReloadToLocation = true;
					LAi_LocationFightDisable(loadedLocation, true);
				}
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				sld = CharacterFromID("Helena");
				DelLandQuestMark(sld);
				PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition.l1 = "location";
				PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition.l1.location = "Tortuga";
				PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition = "PZ_TortugaRazgovorVKauteSDevushkoy";
			}
		break;
		
		case "PZ_MaryRazgovorOBordeli_Good_1":
			dialog.text = "Задержись ты ещё на полчаса, Шарль, и я бы приказала разложить нашими ядрами этот мерзкий притон по кирпичикам, да! Так ты нашёл, что искал? Это она, сестра Лонгвэя? Ты видел её?";
			link.l1 = "Тише, Мэри, не тараторь так. Нет, с Чанг Шин мне встретиться не удалось...";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Good_2";
			
			DeleteAttribute(pchar, "questTemp.MarySexBlock");
		break;
		
		case "PZ_MaryRazgovorOBordeli_Good_2":
			dialog.text = "Тогда какого чёрта ты был там так долго?! Что ты там делал?";
			link.l1 = "Тебе не о чем волноваться. Ни когда я уходил, ни сейчас. Как только я выяснил всё что мог, сразу же покинул стены этой богадельни - как и обещал.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Good_3";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Good_3":
			dialog.text = "Ну говори же, да!";
			link.l1 = "Хозяйки нет сейчас на Тортуге. Услуги её заведения мало кого здесь интересуют - у неё работают хорошо образованные дамочки в недешёвых нарядах, и берут в качестве платы только золото...";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Good_4";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Good_4":
			dialog.text = "Ты им что, ещё и заплатил?!";
			link.l1 = "Без этого они и разговаривать со мной не собирались. Так что неудивительно, что с таким подходом клиентов у них не то чтобы много. В Порт-о-Пренсе, куда мадам решила перебраться, дела могут пойти на лад - там народ побогаче будет. Но со средствами у неё, очевидно, не очень - раз уж она решила обратиться за ссудой к Маркусу...";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Good_5";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Good_5":
			dialog.text = "А он с ней знаком?";
			link.l1 = "Доберёмся до Ла-Веги и спросим. А если поторопимся поднять паруса и не будем тратить время на лишнюю болтовню, то и эту азиатку, кем бы она ни была, застанем.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Good_6";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Good_6":
			dialog.text = "Лишним был поход в этот притон, Шарль. Уверена, всё это можно было разузнать и в таверне или же на улицах, если как следует постараться, да.";
			link.l1 = "В следующий раз возьму тебя с собой, чтобы ты не забивала себе голову всякой чушью, договорились? А теперь пора заняться делом.";
			link.l1.go = "PZ_NaLaVega";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_1":
			dialog.text = "О, вижу, я малость не успела, да! Ну, держись, подлец...";
			link.l1 = "Мэри, какого дьявола ты тут забыла?! Я же велел тебе оставаться на судне!";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_2";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_2":
			dialog.text = "Чтобы я не мешала тебе развлекаться с портовыми девками?! Даже не думай отнекиваться, Шарль! Матросы видели тебя там, да! Как ты мог?!";
			link.l1 = "Так я и подумал. Видимо, следовало взять их с собой, чтобы увидели, чем я там занимался, а точнее НЕ занимался, и не возводили почём зря напраслину...";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_3";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_3":
			dialog.text = "Ты обвиняешь наших ребят во лжи? После того что сделал сам, негодяй?";
			link.l1 = "Обвиняю я только тебя - в беспримерной глупости. Не разобравшись в ситуации, ты...";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_4";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_4":
			dialog.text = "О-о, Шарль, вряд ли бы тебе и твоим шлюхам понравилось бы, как я разобралась бы в ситуации, доберись я до этой дыры. Но вам повезло - я насилу управилась с этой шлюпкой одна...";
			link.l1 = "Говорят, тяжёлый физический труд освобождает голову от лишних мыслей. Но у тебя их ещё навалом, так что обратно гребёшь тоже ты.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_5";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_5":
			dialog.text = "Я с места не сдвинусь, да!";
			link.l1 = "Мэри, выяснять отношения здесь, на виду у людей Левассера, я не намерен. Остынь, оглянись вокруг и здраво оцени происходящее. Сейчас не место и не время.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_6";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_6":
			dialog.text = "Чёрт с тобой. В каюте всё равно остались мои вещи... Но даже не думай, что я буду опять работать вёслами, да! Хоть что-то же от благородного дворянина в тебе должно было ещё остаться!";
			link.l1 = "Я подлец и негодяй, забыла? Доказывать обратное я буду на корабле, но до него ещё надо добраться. Так что твои увещевания тщетны.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_7";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_7":
			DialogExit();
			LAi_LocationFightDisable(loadedLocation, false);
			
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", Get_My_Cabin(), "rld", "loc1", "OpenTheDoors", -1);
			
			PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition.l1 = "location";
			PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition.l1.location = "Tortuga";
			PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition = "PZ_TortugaRazgovorVKauteSDevushkoy";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_8":
			dialog.text = "Над тобой вся команда смеётся, да!";
			link.l1 = "Ну, или над тобой. Такого зрелища давно у них не было. А теперь, когда твой пыл немного охладился, дай мне рассказать, как всё было.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_9";
			
			DeleteAttribute(pchar, "questTemp.MarySexBlock");
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_9":
			dialog.text = "Шарль, мне всё уже рассказали. У меня только один вопрос: неужели тебе чего-то не хватало?";
			link.l1 = "Хоть это и невежливо, но отвечу вопросом на вопрос: я давал тебе хоть один серьёзный повод мне не доверять? Молчишь? Я вот такого не припомню. Так что выдохни и выслушай меня. Про Сеппа ван дер Винка ничего толкового мне узнать не удалось - кроме того, что он заглядывал в бордель. Но не в тот, что рядом с 'Поющей вороной', а другой, недалеко от пирса. Я о нём раньше и знать не знал... в отличие, очевидно, от наших матросов, которые и подняли тебя на уши. Хотя их бы и на порог туда не пустили...";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_10";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_10":
			dialog.text = "Что это за бордель, куда не пускают матросов?";
			link.l1 = "Тот, где работают выряженные в шелка дамы, у которых в голове не ветер свищет. И чьи услуги оплачиваются исключительно в золотых дублонах. И причуды это не чьи-нибудь, а загадочной хозяйки, которую зовут Бэлль Этуаль.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_11";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_11":
			dialog.text = "Загадочнее не бывает, да.";
			link.l1 = "Дело не только в этом. А в том, что она - азиатка.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_12";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_12":
			dialog.text = "Азиатка? Мадам в борделе на Тортуге?";
			link.l1 = "Это может быть Чанг Шин. За этим я и пошёл туда - хотел увидеть её своими глазами. Только и всего.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_13";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_13":
			dialog.text = "И какая же она?";
			link.l1 = "Понятия не имею. Её не было на месте, поэтому пришлось пообщаться с другой... звездой.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_14";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_14":
			dialog.text = "Тоже азиаткой?";
			link.l1 = "Нет, белой. Она поведала мне о том, что дела у Бэлль Этуаль идут в последнее время не очень, в связи с чем она решила перебраться в Порт-о-Пренс. Разумно и логично - в городе де Мюссака народ будет побогаче. С деньгами, видимо, у мадам совсем худо, раз уж на открытие дела на Эспаньоле ей понадобилась ссуда, которую она намерена взять у Тиракса. Так что, если поспешим к Ла-Веге, можем успеть перехватить её у Маркуса.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_15";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_15":
			dialog.text = "Плевать я хотела и на неё, и на Маркуса, и на всех остальных. Шарль, скажи мне только одно - ты точно... не был с теми девушками в её борделе?";
			link.l1 = "Мне это просто не за чем, Мэри. Ведь у меня есть ты - лучшая девушка на земле. В толк не возьму, почему ты этого не понимаешь.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_16";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_16":
			dialog.text = "На самом деле, выяснить истину очень легко, хи-хи. Если ты ни с кем не был, то должен быть сейчас полон сил. Вот сейчас мы это и проверим, да!";
			link.l1 = "Мэри...";
			link.l1.go = "exit";
			pchar.quest.sex_partner = Npchar.id;
			AddDialogExitQuest("cabin_sex_go");
			pchar.questTemp.PZ_MaryRazgovorOBordeli = true;
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_17":
			DeleteAttribute(pchar, "questTemp.PZ_MaryRazgovorOBordeli");
			if (CheckAttribute(pchar, "questTemp.PZ.EliteWhoreFucked"))
			{
				if (IsCharacterPerkOn(pchar, "Medic"))
				{
					notification("Отменное здоровье", "Medic");
					dialog.text = "(Отменное здоровье) Фу-у-х... Похоже, ты не соврал, Шарль, да...";
					link.l1 = "Мне нет нужды тебя обманывать, дорогая...";
					link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_18";
				}
				else
				{
					notification("Не открыта способность", "Medic");
					dialog.text = "Шарль, ты... ты это серьёзно?! Это что такое было?";
					link.l1 = "Ох-х, ну и жара...";
					link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_19";
				}
			}
			else
			{
				dialog.text = "Фу-у-х... Похоже, ты не соврал, Шарль, да...";
				link.l1 = "Мне нет нужды тебя обманывать, дорогая...";
				link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_18";
			}
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_18":
			dialog.text = "Но этот заплыв на шлюпке я тебе ещё долго не забуду!";
			link.l1 = "Ха!";
			link.l1.go = "PZ_NaLaVega";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_19":
			dialog.text = "Раньше ты как-то на это не жаловался, да!";
			link.l1 = "А ты побегай по чёртовому острову...";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_20";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_20":
			dialog.text = "И борделям, да! Неужели ты всё-таки...";
			link.l1 = "Мэри, прости меня...";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_21";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_21":
			dialog.text = "Что?! Так, значит, ты...";
			link.l1 = "Да не за то, чтоб мне провалиться! Не был я ни с кем кроме тебя - сказал же. Я просто... не смог сосредоточиться. Тяжело, знаешь ли, это сделать, когда на тебя смотрят пушки Ля-Роша.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_22";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_22":
			dialog.text = "Прекрасная отговорка, Шарль. Ладно, поверю тебе. На этот раз... Но знай, что я всё равно обижена, да!";
			link.l1 = "Я заслужу твоё прощение, обещаю.";
			link.l1.go = "PZ_NaLaVega";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Good_1":
			dialog.text = "Ну, герой-любовник, рассказывай, что ты разузнал. Стоило это того, чтобы так рисковать моим расположением?";
			link.l1 = "И не поймёшь, шутишь ты или говоришь всерьёз. Сходил туда я не зря - пусть и не увидел хозяйку собственными глазами, но узнал, что она азиатка. Зовут её Бэлль Этуаль - дивная звезда. Псевдоним, конечно же, но настоящего имени мне выяснить не удалось.";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Good_2";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Good_2":
			dialog.text = "И для этого нужно обязательно было тащиться в этот притон? В трактире это было выяснить никак нельзя?";
			link.l1 = "Про это место как-то не особо болтают в городе, знаешь ли, хотя и знают о нём. Почему - хороший вопрос. Задать его можно будет самой Бэлль Этуаль - она отбыла на Эспаньолу.";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Good_3";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Good_3":
			dialog.text = "Тортуги ей оказалось мало?";
			link.l1 = "Дела тут, видимо, идут не очень. У неё работают не обычные портовые девки, а богато разодетые образованные дамы.";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Good_4";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Good_4":
			dialog.text = "И зачем им этим заниматься?";
			link.l1 = "Ещё один хороший вопрос. Так или иначе, наша пташка решила перепорхнуть под крыло де Мюссака, в Порт-о-Пренс. А вот ссуду на это дело она задумала получить ни у кого иного, как у Тиракса.";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Good_5";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Good_5":
			dialog.text = "Я хочу, чтобы эта история поскорее окончилась. Не будем терять времени и возьмём курс на Ла-Вегу.";
			link.l1 = "Так и поступим.";
			link.l1.go = "PZ_NaLaVega";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_1":
			dialog.text = "А ты весьма смел, Шарль, отдаю тебе должное. Явиться вот так запросто, с такой физиономией, будто ничего и не произошло.";
			link.l1 = "Я так полагаю, сболтнул кто-то из матросов? Не разобравшись в ситуации, разумеется. Потому что ничего и в самом деле не произошло - того, о чём ты подумала, во всяком случае.";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_2";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_2":
			dialog.text = "А я уж было обрадовалась, что ты не стал ничего отрицать, Шарль.";
			link.l1 = "Я и так собирался всё тебе рассказать, Элен.";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_3";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_3":
			dialog.text = "Не стоит, Шарль. Подробности меня не больно-то интересуют. А вот причины - как раз наоборот. Скажи, что тебя во мне не устраивало?";
			link.l1 = "Давай с причин и начнём. Путём расспросов мне удалось выяснить, что на Тортуге есть два дома терпимости. Один - общеизвестный. О втором же - много кто знает, но мало кто хочет говорить. Хозяйкой там является азиатка...";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_4";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_4":
			dialog.text = "Ты на ходу всё это выдумываешь?";
			link.l1 = "Проклятье, на кой чёрт мне это делать, Элен?! Ну не веришь ты мне - тебе это подтвердят в самом заведении!";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_5";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_5":
			dialog.text = "Во-первых, это ты запретил мне сходить на берег. Так что мне туда никак не попасть. Во-вторых, я кто, по-твоему, такая, чтобы по всяким вертепам шляться?! В-третьих... продолжай.";
			link.l1 = "Славно. Я решил туда зайти, чтобы своими глазами увидеть мадам хозяйку. Только за этим, чёрт побери, а не за тем, о чём в красках трепалась матросня!";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_6";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_6":
			dialog.text = "Допустим. И как, познакомился с ней?";
			link.l1 = "Нет. Она отбыла на Эспаньолу. Дела здесь у неё идут не самым лучшим образом, поэтому она решила попытать счастья в Порт-о-Пренсе. Там разодетые в шелка хорошо образованные дамы, которые трудятся в её заведении, могут принести ей прибыли куда больше, чем здесь...";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_7";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_7":
			dialog.text = "Разодетые, да ещё и образованные? Надо же, до чего жизнь довести может. Впрочем, тебе как раз такие должны прийтись по вкусу.";
			link.l1 = "Элен, хватит. Я не сделал ничего, чтобы заслужить твоё недоверие.";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_8";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_8":
			dialog.text = "Пожалуй, что так. Пытайся ты меня обмануть, не был бы так спокоен. Но всё же тебе следовало меня предупредить о своих планах, Шарль.";
			link.l1 = "Ты права, дорогая. Но я решил сэкономить немного времени. Моя ошибка.";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_9";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_9":
			dialog.text = "Ладно. Что теперь, курс на Порт-о-Пренс?";
			link.l1 = "На Ла-Вегу. Не удивляйся, Элен. С деньгами у мадам Бэлль Этуаль, а именно так её зовут, не очень-то хорошо. На открытие дела в Порт-о-Пренсе ей потребуется ссуда, и она решила взять её у Маркуса. Если поторопимся, успеем застать её там. Так что не станем терять ни минуты.";
			link.l1.go = "PZ_NaLaVega";
		break;
		
		case "PZ_NaLaVega":
			DialogExit();
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) 
			{
				AddLandQuestMark(characterFromId("Terrax"), "questmarkmain");
				QuestSetCurrentNode("Terrax", "PZ1");
			}
			else 
			{
				AddLandQuestMark(characterFromId("Vensan"), "questmarkmain");
				QuestSetCurrentNode("Vensan", "PZ1");
			}
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			Island_SetReloadEnableGlobal("Tortuga", true);
			bQuestDisableMapEnter = false;
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				sld = CharacterFromID("Mary");
				AddPassenger(pchar, sld, false);
				Return_MaryOfficer();
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				sld = CharacterFromID("Helena");
				AddPassenger(pchar, sld, false);
				Return_HelenaOfficer();
			}
			if (!CheckAttribute(pchar, "questTemp.PZ_PredupredilNashuDevushku")) AddQuestRecord("PZ", "31");
		break;
		
		case "PZ_KlemanLebren_7":
			dialog.text = "Поверить не могу, что хлыщ вроде тебя вместе со своим сбродом одолел нас!";
			link.l1 = "Ты...";
			link.l1.go = "PZ_KlemanLebren_8";
		break;
		
		case "PZ_KlemanLebren_8":
			dialog.text = "О, узнал меня?";
			link.l1 = "Ты кто такой?";
			link.l1.go = "PZ_KlemanLebren_9";
		break;
		
		case "PZ_KlemanLebren_9":
			dialog.text = "Что?! Ты издеваешься?!";
			link.l1 = "Сейчас бы помнить всякую невоспитанную шваль. Лучше скажи тогда, кто тебя отправил за нами. Скорее, от тебя просто хотели избавиться.";
			link.l1.go = "PZ_KlemanLebren_10";
		break;
		
		case "PZ_KlemanLebren_10":
			dialog.text = "Какого ты о себе мнения! Посмотрим, сможешь ли ещё раз подтвердить эти слова после нашей передышки. Ничего я такому, как ты, говорить не буду.";
			link.l1 = "Жаль. Ты отвратителен, но я мог бы просто высадить тебя на другом острове. Теперь могу лишь отправить на тот свет.";
			link.l1.go = "PZ_KlemanLebren_11";
		break;
		
		case "PZ_KlemanLebren_11":
			pchar.questTemp.PZ.HeavyFrigateAbordage = true; // флаг - абордаж был
			
			DialogExit();
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PZ_Tichingitu_11":
			dialog.text = "Вызывать меня, капитан?";
			link.l1 = "Да, дружище. Доложи о повреждениях.";
			link.l1.go = "PZ_Tichingitu_12";
		break;
		
		case "PZ_Tichingitu_12":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Мэри";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Элен";
			dialog.text = "Это есть жестокий буря. Корабль скрипит, трещит, его сильно шатать.";
			link.l1 = "Да уж, я заметил - самого даже совсем слегка мутит. Тичингиту, друг мой. Мы с " + sStr + " сходим на берег. Ты остаёшься за главного. Начни пока ремонтные работы - пока шторм не утихнет, бесполезно идти на верфь. К тому же, мы ненадолго. А прикрепить пару досок уже надо.";
			link.l1.go = "PZ_Tichingitu_13";
		break;
		
		case "PZ_Tichingitu_13":
			dialog.text = "Я сделать всё в лучший вид.";
			link.l1 = "Отлично, спасибо. Мы тогда безо всяких переживаний отправляемся в город.";
			link.l1.go = "PZ_Tichingitu_14";
		break;
		
		case "PZ_Tichingitu_14":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "PZ_PoP_Rain_4", -1);
		break;
		
		case "PZ_Matros_1":
			dialog.text = "Месье капитан? Это честь. Но обычно вы вызываете Алонсо в такие моменты. Всё хорошо, если позволите спросить?";
			link.l1 = "Да, полный порядок. Но наш Алонсо больше по разрушениям, а не починке чего-либо. Во всех смыслах. Насколько плох корабль?";
			link.l1.go = "PZ_Matros_2";
		break;
		
		case "PZ_Matros_2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Мэри";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Элен";
			dialog.text = "Тут вам и Алонсо бы сказал - паршиво, пусть и не идём ко дну. Вы упоминали ремонт - прикажете его начать?";
			link.l1 = "Да, сделайте, что сможете. Но не планируйте полномасштабные длительные работы - мы скоро поднимем якорь - сразу же, как я закончу свои дела в городе. Нас с " + sStr + " не будет, так что, в случае чего, принимайте все решения сами. Во всём слушайтесь Алонсо.";
			link.l1.go = "PZ_Matros_3";
		break;
		
		case "PZ_Matros_3":
			dialog.text = "Как прикажете, месье капитан.";
			link.l1 = "Вольно.";
			link.l1.go = "PZ_Matros_4";
		break;
		
		case "PZ_Matros_4":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
			Island_SetReloadEnableGlobal("Hispaniola2", true);
			bQuestDisableMapEnter = false;
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "PZ_PoP_Rain_4", -1);
		break;
		
		case "PZ_AnriTibo_1":
			dialog.text = "Приветствую, сударь! Добро пожаловать в Порт-о-Пренс.";
			link.l1 = "И вам не хворать, месье. Кто вы, и чем я обязан такому вниманию? Не сказал бы, что настроен на продолжительную беседу под таким дождём, да ещё и после шторма.";
			link.l1.go = "PZ_AnriTibo_2";
			
			sld = GetCharacter(NPC_GenerateCharacter("PZ_PoP_ChangShin", "Mei_Shin", "woman", "towngirl2", 30, FRANCE, 0, false, "quest"));
			FantomMakeCoolFighter(sld, 30, 80, 80, "blade_41", "", "", 0);
			sld.name = "Чанг";
			sld.lastname = "Шин";
			ChangeCharacterAddressGroup(sld, "PortPax_town", "goto", "goto16");
			EquipCharacterByItem(sld, "blade_41");
			GiveItem2Character(sld, "cirass8");
			EquipCharacterByItem(sld, "cirass8");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload8_back", "none", "", "", "", -1);
		break;
		
		case "PZ_AnriTibo_2":
			dialog.text = "О, я не отниму много вашего времени, месье де Мор.";
			link.l1 = "Мы знакомы?";
			link.l1.go = "PZ_AnriTibo_3";
		break;
		
		case "PZ_AnriTibo_3":
			dialog.text = "Ну что вы, едва ли не весь Архипелаг знает, кто вы. Ах, где же мои манеры! Анри Тибо. Я посыльный Его Светлости, месье де Мюссака. Как только он заметил ваше судно, то приказал мне устроить вам максимально радушный приём, сударь.";
			link.l1 = "Что ж, это многое объясняет. Рад знакомству, месье Тибо.";
			link.l1.go = "PZ_AnriTibo_4";
		break;
		
		case "PZ_AnriTibo_4":
			dialog.text = "И это взаимно, месье де Мор! Пойдёмте. Негоже человеку вашего полёта и его прекрасной спутнице ютиться в этом смердящем клоповнике под названием 'таверна'. Его Светлость выделил для вас один из домов в городе. И велел мне во всём вам содействовать. Пожалуйста, не забудьте потом передать его наилучшие пожелания шевалье де Пуанси.";
			link.l1 = "Вообще-то моё поручение было инкогнито. Знаете, месье, Тибо, я думаю, что...";
			link.l1.go = "PZ_AnriTibo_5";
		break;
		
		case "PZ_AnriTibo_5":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) StartInstantDialog("Helena", "PZ_HelenaPortPax1", "Quest\CompanionQuests\Longway.c");
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) StartInstantDialog("Mary", "PZ_MaryPortPax1", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_HelenaPortPax1":
			dialog.text = "Шарль. Я редко тебя прошу о чём-либо и, уж тем более, перебиваю, но, может, воспользуемся их предложением? Надоело уже мокнуть под дождём. А ещё меня тошнит, и голова кружится.";
			link.l1 = "Хе-хе, а ты уверена, что это в дожде дело?";
			link.l1.go = "PZ_HelenaPortPax2";
		break;
		
		case "PZ_HelenaPortPax2":
			dialog.text = "Типун тебе на язык, Шарль. В любом случае, я хочу передохнуть. На большой кровати и без качки.";
			link.l1 = "Ну хорошо. Обсохнем, передохнём - и сразу же вернёмся к делам.";
			link.l1.go = "PZ_AnriTibo_6";
		break;
		
		case "PZ_MaryPortPax1":
			dialog.text = "Можно мы передохнём в этом доме? Я неважно себя чувствую, а ещё я... устала, Шарль. Да.";
			link.l1 = "Мэри, родная, я понимаю, но, может, лучше пойдём в таверну? Как-то это всё шито белыми нитками.";
			link.l1.go = "PZ_MaryPortPax2";
		break;
		
		case "PZ_MaryPortPax2":
			dialog.text = "Что может со мной случиться? Здесь ведь даже не Тортуга. А я была в полной боевой готовности всё там разнести вместе с тобой ещё тогда!";
			link.l1 = "Это меня и пугает.";
			link.l1.go = "PZ_MaryPortPax3";
		break;
		
		case "PZ_MaryPortPax3":
			dialog.text = "Ну пожалуйста? Если что, организую в комнате оборону - совсем, как... тогда, да. Ты знаешь меня, как никто, Шарль, так что знаешь, что справлюсь.";
			link.l1 = "Ну ладно, ладно. Надеюсь, 'как тогда' не будет.";
			link.l1.go = "PZ_AnriTibo_6";
		break;
		
		case "PZ_AnriTibo_6":
			StartInstantDialog("Tibo", "PZ_AnriTibo_7", "Quest\CompanionQuests\Longway.c");
			
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) Return_MaryOfficer();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) Return_HelenaOfficer();
		break;
		
		case "PZ_AnriTibo_7":
			dialog.text = "Я знал, что вы передумаете, сударь! Касательно ваших переживаний - прекрасно вас понимаю. Но, видите ли, шевалье де Пуанси и Его Светлость - давние друзья, а потому вы в нашем городе - желанный гость, месье де Мор!";
			link.l1 = "Ох, ладно... Ну что ж, отведите тогда нас в дом, что Его Светлость приготовил для нас, месье Тибо.";
			link.l1.go = "PZ_AnriTibo_8";
		break;
		
		case "PZ_AnriTibo_8":
			dialog.text = "Конечно, сударь! Прошу за мной.";
			link.l1 = "Благодарю.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_GoToTiboHouse");
		break;
		
		case "PZ_AnriTibo_9":
			dialog.text = "Сударь, Его Светлость уже ждёт вас у себя. Он просил вас сходить к нему сразу же, как только сможете - он хотел бы поговорить с вами без лишних ушей.";
			link.l1 = "Неужели он уже знает, что...";
			link.l1.go = "PZ_AnriTibo_10";
		break;
		
		case "PZ_AnriTibo_10":
			pchar.questTemp.PZ.PortPaxMayorTalk = true; // флаг для разговора с губернатором
			
			dialog.text = "Ну конечно, знает! А потому уже ждёт вас. Ваша ненаглядная пусть сладко спит - она как раз хотела отдохнуть. Вы же пока сходите к месье де Мюссаку. Какой-то там шторм же не сломит знаменитого Шарля де Мора, верно? А вот у Его Светлости, как вы понимаете, не так много свободного времени между приёмами...";
			link.l1 = "Что ж, ваша правда, месье Тибо.";
			link.l1.go = "PZ_AnriTibo_11";
			
			for (i=1; i<=2; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("PZ_PoP_Escort_"+i, "sold_fra_"+(rand(7)+1), "man", "man", sti(pchar.rank), FRANCE, -1, true, "soldier"));
				LAi_SetActorType(sld);
				ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload1");
			}
		break;
		
		case "PZ_AnriTibo_11":
			StartInstantDialog("PZ_PoP_Escort_1", "PZ_AnriTibo_12", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_AnriTibo_12":
			dialog.text = "Мы вас проводим, капитан.";
			link.l1 = "О, так мне даже почётный эскорт положен... Ну что ж, ведите.";
			link.l1.go = "PZ_AnriTibo_13";
		break;
		
		case "PZ_AnriTibo_13":
			DoQuestReloadToLocation("PortPax_town", "reload", "houseF1", "PZ_PoP_EscortToGuber");
		break;
		
		case "PZ_Longway_71":
			dialog.text = "Господин капитан!";
			link.l1 = "Лонгвэй! На корабль! Живо!";
			link.l1.go = "PZ_Longway_72";
		break;
		
		case "PZ_Longway_72":
			dialog.text = "Но мой видеть Чанг Шин!";
			link.l1 = "Что?! Где? Когда? Она у тебя на корабле?";
			link.l1.go = "PZ_Longway_73";
		break;
		
		case "PZ_Longway_73":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Мэри";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Элен";
			dialog.text = "Увы, нет! Здесь, в город, издалека. Не успеть догнать - она подняться на борт галеон и только что отчалить!";
			link.l1 = "Уж галеон-то мы догоним! Но скажи мне - ты нигде не видел " + sStr + "???";
			link.l1.go = "PZ_Longway_74";
		break;
		
		case "PZ_Longway_74":
			dialog.text = "Нигде не видеть! Что-то случиться?";
			link.l1 = "Да, чёрт возьми! Ей угрожает опасность! А племянника Левассера не видел? Зовут Анри Тибо! Мерзкий худощавый длинноволосый юнец со смешными усиками!";
			link.l1.go = "PZ_Longway_75";
		break;
		
		case "PZ_Longway_75":
			dialog.text = "(на китайском) Не вам говорить о смешных усиках, капитан\n(на ломаном французском) Видеть! Он вместе с наёмники тоже подняться на тот самый галеон.";
			link.l1 = "Тем более! Бросаемся в погоню немедленно!";
			link.l1.go = "PZ_Longway_76";
		break;
		
		case "PZ_Longway_76":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Мэри";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Элен";
			dialog.text = "Ваш корабль быть сильно изношен, господин капитан!";
			link.l1 = "Мне плевать! На кону жизнь " + sStr + "!";
			link.l1.go = "PZ_Longway_77";
		break;
		
		case "PZ_Longway_77":
			if (CheckAttribute(pchar, "questTemp.PZ.LongwayMayfang"))
			{
				dialog.text = "Мой... Ваш 'Мейфенг' не подвести!";
				link.l1 = "И правда! Поспешим!";
				link.l1.go = "PZ_Longway_78";
			}
			else
			{
				dialog.text = "Не бросаться же наш в самоубийственный атака? Сесть на корабль, что ваш передать мой.";
				link.l1 = "Как всегда хорошая идея, Лонгвэй! Поторопимся!";
				link.l1.go = "PZ_Longway_78";
			}
		break;
		
		case "PZ_Longway_78":
			DialogExit();
			chrDisableReloadToLocation = false;
			Island_SetReloadEnableGlobal("Hispaniola2", false);
			LocatorReloadEnterDisable("PortPax_town", "gate_back", true);
			SetCurrentTime(15, 00);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			pchar.GenQuest.AbordageInStorm = true;	//Разрешить абордаж во время шторма
			SetLocationCapturedState("PortPax_town", false);

			LAi_LoginInCaptureTown(npchar, false);
			AddPassenger(pchar, npchar, false);
			Return_LongwayOfficer();
			
			if (GetCharacterIndex("Tichingitu") != -1)
			{
				sld = characterFromId("Tichingitu");
				AddPassenger(pchar, sld, false);
				Return_TichingituOfficer();
			}
			
			PChar.quest.PZ_PoP_Pogonya.win_condition.l1 = "location";
			PChar.quest.PZ_PoP_Pogonya.win_condition.l1.location = "Hispaniola2";
			PChar.quest.PZ_PoP_Pogonya.win_condition = "PZ_PoP_Pogonya";
			
			SeaAI_SwapShipsAttributes(pchar, CharacterFromID("PZ_ShipStasis"));
			AddCharacterGoodsSimple(pchar, GOOD_GRAPES, 300);
			AddCharacterGoodsSimple(pchar, GOOD_BOMBS, 200);
			AddCharacterGoodsSimple(pchar, GOOD_POWDER, 350);
			AddCharacterGoodsSimple(pchar, GOOD_FOOD, 150);
			AddCharacterGoodsSimple(pchar, GOOD_RUM, 50);
			AddCharacterGoodsSimple(pchar, GOOD_FOOD, 700);
			SetCrewQuantityFull(pchar);
			pchar.ship.HP = sti(pchar.ship.HP) / 2;
			pchar.Ship.Crew.Quantity = sti(pchar.ship.Crew.Quantity) / 2;
			AddCrewMorale(Pchar, 100);
			ChangeCrewExp(pchar, "Sailors", 100);
			ChangeCrewExp(pchar, "Cannoners", 100);
			ChangeCrewExp(pchar, "Soldiers", 100);
			
			//Вражина
			sld = characterFromId("PZ_RobertMartin");
			sld.nation = PIRATE;
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				GiveItem2Character(sld, "blade_31");
				EquipCharacterByItem(sld, "blade_31");
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				GiveItem2Character(sld, "pirate_cutlass");
				EquipCharacterByItem(sld, "pirate_cutlass");
			}
			FantomMakeCoolSailor(sld, SHIP_GALEON_L, "Вольтижёр", CANNON_TYPE_CANNON_LBS16, 50, 50, 50);
			sld.AlwaysEnemy = true;
			sld.AlwaysSandbankManeuver = true;
			sld.DontRansackCaptain = true;
			sld.ShipHideImmortal = 800;
			Group_FindOrCreateGroup("PZ_RM_Attack");
			Group_SetType("PZ_RM_Attack", "pirate");
			Group_AddCharacter("PZ_RM_Attack", "PZ_RobertMartin");
			Group_SetGroupCommander("PZ_RM_Attack", "PZ_RobertMartin");
			Group_SetTaskAttack("PZ_RM_Attack", PLAYER_GROUP);
			Group_SetAddress("PZ_RM_Attack", "Hispaniola2", "quest_ships", "Quest_ship_1");
			Ship_SetTaskAttack(SECONDARY_TASK, sti(sld.index), sti(pchar.index));
		break;
		
		case "PZ_RobertMartin_8":
			dialog.text = "Снова ты... Так и знал, что лучше было бы отказаться, чтобы кто-то другой забирал твою бабу.";
			link.l1 = "Где она?! Говори! Хотя нет... Закрой свой рот. Говорить будешь только в трюме, в кандалах! Понял меня?!";
			link.l1.go = "PZ_RobertMartin_9";
		break;
		
		case "PZ_RobertMartin_9":
			dialog.text = "...";
			link.l1 = "Её клинок. Мерзавец... Если не запоёшь соловьём, я разрежу им тебя на кусочки.";
			link.l1.go = "PZ_RobertMartin_10";
			/*RemoveAllCharacterItems(npchar, true);
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) GiveItem2Character(pchar, "blade_31");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) GiveItem2Character(pchar, "pirate_cutlass");*/
		break;
		
		case "PZ_RobertMartin_10":
			dialog.text = "Ты... ты сбрендил!..";
			link.l1 = "Сейчас ты узнаешь, каким я могу быть, если меня по-настоящему довести...";
			link.l1.go = "PZ_RobertMartin_11";
		break;
		
		case "PZ_RobertMartin_11":
			DialogExit();
			LAi_ReloadBoarding();
		break;
		
		case "PZ_RobertMartin_13":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Мэри";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Элен";
			dialog.text = "И это всё?";
			link.l1 = "Ещё раз спрашиваю! Где " + sStr + "?! Где китаянка?! Где Анри Тибо?!";
			link.l1.go = "PZ_RobertMartin_14";
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "beatmarten_idle_1", "", 0.3);
		break;
		
		case "PZ_RobertMartin_14":
			dialog.text = "(сплёвывает кровь) Бьёшь, как девчонка.";
			link.l1 = "Тварь! Я выбью из тебя каждое слово!";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_DoprosRobertMartin_Trum_6");
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "beatmarten_idle_1", "", 0.3);
		break;
		
		case "PZ_RobertMartin_16":
			dialog.text = "Слабо, очень слабо. Хотя... я скажу. Почему нет, ха-ха. Они все на другом корабле, прямо на пути в Тортугу. Ты опоздал.";
			link.l1 = "Если хоть волос с её головы упадёт...";
			link.l1.go = "PZ_RobertMartin_17";
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "beatmarten_idle_2", "", 0.3);
			locCameraFromToPos(0.27, 14.52, -3.38, true, -1.80, 9.90, -1.76);
		break;
		
		case "PZ_RobertMartin_17":
			dialog.text = "И кто в этом виноват?! Ты убил Эдгардо Сотту! Впервые в жизни Левассер захотел попробовать черномазую, а мы до сих пор не можем её найти! А когда мы не можем выполнить его заказы, он страшен, как дьявол...";
			link.l1 = "Тогда я стану страшнее самого дьявола и устрою тебе маленький личный ад, если ты не скажешь мне то, что я хочу знать, слышишь меня?!";
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) link.l1.go = "PZ_RobertMartin_Mary_1";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) link.l1.go = "PZ_RobertMartin_Helena_1";
		break;
		
		case "PZ_RobertMartin_Mary_1":
			dialog.text = "Да плевать мне - я всё равно уже не жилец, судя по твоим безумным глазам. Однако отдаю тебе должное, де Мор.";
			link.l1 = "О чём ты, чёрт тебя дери?..";
			link.l1.go = "PZ_RobertMartin_Mary_2";
		break;
		
		case "PZ_RobertMartin_Mary_2":
			dialog.text = "Левассер предпочитает блондинок. Но мне всегда больше нравились рыжие, прямо как и тебе, хе-хе-хе... Какая же она у тебя горячая!";
			link.l1 = "Ты прав, ты не переживёшь этот день...";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_DoprosRobertMartin_Trum_7");
		break;
		
		case "PZ_RobertMartin_Helena_1":
			dialog.text = "Плевать я хотел на то, что тебе хочется знать. А вот чего чаще всего хочется Левассеру - красотку-блондиночку, ха-ха-ха-ха-ха! Сначала он её...";
			link.l1 = "А-А-А!!!";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_DoprosRobertMartin_Trum_7");
		break;
		
		case "PZ_RobertMartin_19":
			dialog.text = "Визги и избиение безоружного - вот и всё, что ты можешь. Позорище. Ты проиграл, де Мор! Хочешь знать, когда?";
			link.l1 = "Просвети меня. Но если я не буду впечатлён, то ты потеряешь палец. Или ухо. Или гнилые зубы из своей вонючей пасти. Или ещё кое-что. Выбор за тобой...";
			link.l1.go = "PZ_RobertMartin_20";
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "beatmarten_idle_3", "", 0.3);
			//locCameraFromToPos(-1.75, 14.14, -0.31, true, 1.26, 11.00, -4.00);
			locCameraFromToPos(-2.47, 14.15, -0.01, true, 1.23, 10.92, -3.60);
		break;
		
		case "PZ_RobertMartin_20":
			dialog.text = "Хе-хе, у меня-то он есть, а вот у тебя его уже не осталось. Думаешь, Левассер не знал, что этот старый лис Пуанси замышляет против него? Франсуа всё знает, всё! Даже бароны Братства не решаются бросить ему вызов. А ты, такой умный, значит, решился. Но...";
			link.l1 = "Но что?! Не ломай комедию! Или я тебе начну переламывать пальцы по одному!";
			link.l1.go = "PZ_RobertMartin_21";
		break;
		
		case "PZ_RobertMartin_21":
			dialog.text = "Ха-ха, храбрый капитан де Мор! Но ладно. Я, Анри и желтокожая решили, что лучше уничтожить тебя здесь. А вину спихнуть на Тиракса, чтобы старые идиоты в Братстве начали новую войну друг с другом! Или же на де Мюссака - нос свой уже давно суёт, куда не следует... Знаешь, все смеялись надо мной, что я хожу на галеоне, но он легко перенёс этот шторм, в отличие от твоего корыта.";
			link.l1 = "Довольно!!! Где Левассер держит своих жертв?";
			link.l1.go = "PZ_RobertMartin_22";
		break;
		
		case "PZ_RobertMartin_22":
			dialog.text = "Так ты знаешь о его тайном местечке, в подземелье? О-о да, он настоящий владыка своего подземелья, ха-ха-ха! Но сможешь ли ты бросить ему вызов? Сомневаюсь. Хочешь победить зверя? Стань зверем сам. Посмотрим, сможешь ли ты вытянуть из меня хоть слово об этом и сломать, как Франсуа ломает этих девчонок. Как он вскоре сломит твою...";
			if (!CheckAttribute(pchar, "questTemp.PZ_FlagShip"))
			{
				link.l1 = "АЛО-О-ОН-СО-О-О-О!!!..";
				link.l1.go = "PZ_RobertMartin_23";
			}
			else
			{
				link.l1 = "...";
				link.l1.go = "PZ_LongwayKaznDialog_1";
			}
		break;
		
		case "PZ_RobertMartin_23":
			DialogExit();
			LAi_SetStayType(pchar);
			CharacterTurnByChr(pchar, CharacterFromID("PZ_RobertMartinPlennik"));
			LAi_Fade("PZ_AlonsoKazn", "");
		break;
		
		case "PZ_LongwayKaznDialog_1":
			DialogExit();
			LAi_SetStayType(pchar);
			CharacterTurnByChr(pchar, CharacterFromID("PZ_RobertMartinPlennik"));
			DoQuestCheckDelay("PZ_LongwayKazn_1", 1.0);
		break;
		
		case "PZ_LongwayKaznDialog_2":
			dialog.text = "";
			link.l1 = "Я же просил не беспокоить, чёрт возьми!..";
			link.l1.go = "PZ_LongwayKaznDialog_3";
		break;
		
		case "PZ_LongwayKaznDialog_3":
			DialogExit();
			LAi_SetStayType(pchar);
			LAi_Fade("PZ_LongwayKazn_3", "");
		break;
		
		case "PZ_LongwayKaznDialog_4":
			dialog.text = "Позвольте мой, господин капитан.";
			link.l1 = "Лонгвэй? Позволить что?";
			link.l1.go = "PZ_LongwayKaznDialog_5";
		break;
		
		case "PZ_LongwayKaznDialog_5":
			dialog.text = "Белый люди терзать тело. Наш же нужно терзать его жалкий душа, сводить с ума небольшой постоянный боль. Нельзя так просто брать и мучить без подготовка. Всегда нужен особый подход. Здесь нужен... Линчи.";
			link.l1 = "Линчи?..";
			link.l1.go = "PZ_LongwayKaznDialog_6";
		break;
		
		case "PZ_LongwayKaznDialog_6":
			dialog.text = "Да, господин капитан. Смерть от тысяча порезы.";
			link.l1 = "Ты сдурел?! Головой треснулся? Какая к чёртовой матери смерть?! Мне нужно выяснить...";
			link.l1.go = "PZ_LongwayKaznDialog_7";
		break;
		
		case "PZ_LongwayKaznDialog_7":
			dialog.text = "Лонгвэй знать, господин капитан. Он знать, что делать. Этот мерзавец всё рассказать. Дать мне время...";
			link.l1 = "Время? Время?! Ладно... Действуй. Только прошу, умоляю, вытряси из него всё, всё!!!";
			link.l1.go = "PZ_LongwayKaznDialog_8";
		break;
		
		case "PZ_LongwayKaznDialog_8":
			DialogExit();
			LAi_SetActorType(npchar);
			CharacterTurnByChr(npchar, CharacterFromID("PZ_RobertMartinPlennik"));
			LAi_SetStayType(pchar);
			CharacterTurnByChr(pchar, CharacterFromID("PZ_RobertMartinPlennik"));
			LAi_FadeToBlackStart();
			DoQuestCheckDelay("PZ_LongwayKazn_4", 1.5);
		break;
		
		case "PZ_LongwayKaznDialog_9":
			dialog.text = "Убей, просто убей меня, прошу... Что тебе ещё от меня надо?!";
			link.l1 = "Больше ничего. Захлопни пасть и сдохни.";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_LongwayKazn_11");
		break;//
		
		case "PZ_LongwayKaznDialog_9_1":
			DialogExit();
			sld = CharacterFromID("PZ_RobertMartinPlennik")
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "Shot", "1", 1.5);
			DoQuestCheckDelay("PZ_LongwayKazn_9", 0.9);
		break;
		
		case "PZ_LongwayKaznDialog_10":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "Shot", "1", 1.5);
			DoQuestCheckDelay("PZ_LongwayKazn_9", 0.9);
		break;
		
		case "PZ_LongwayKaznDialog_11":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Мэри";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Элен";
			dialog.text = "Хороший выстрел, господин капитан. Я ведь говорить, что всё сработать.";
			link.l1 = "Да. Молодец. Значит, подземелье. Что ж, за дело. Поднять все паруса! Курс на Тортугу. И да поможет Господь этому чёртову городу, если с головы " + sStr + " хоть волос упадёт...";
			link.l1.go = "PZ_LongwayKaznDialog_12";
		break;
		
		case "PZ_LongwayKaznDialog_12":
			DialogExit();
			ResetSound();
			chrDisableReloadToLocation = false;
			EndQuestMovie();
			DeleteAttribute(pchar, "GenQuest.BlockDialogCamera");
			locCameraTarget(PChar);
			locCameraFollow();
			AddQuestRecord("PZ", "39");
			
			LAi_SetPlayerType(pchar);
			npchar.greeting = "Longway";
			Return_LongwayOfficer();
			
			bQuestDisableMapEnter = false;
			Island_SetReloadEnableGlobal("Hispaniola2", true);
			Island_SetReloadEnableLocal("Hispaniola2", "reload_2", true)
			Island_SetGotoEnableLocal("Hispaniola2", "reload_2", true);
			Island_SetReloadEnableLocal("Hispaniola2", "reload_3", true)
			Island_SetGotoEnableLocal("Hispaniola2", "reload_3", true);
			DeleteAttribute(pchar, "GenQuest.CannotWait");
			DeleteAttribute(pchar,"questTemp.TimeLock");
			LocatorReloadEnterDisable("LaVega_ExitTown", "reload1_back", false);
			LocatorReloadEnterDisable("PortPax_town", "gate_back", false);
			LAi_LocationDisableOfficersGen("PortPax_town", false);
			LAi_LocationFightDisable(&Locations[FindLocation("PortPax_town")], false);
			DeleteAttribute(pchar, "GenQuest.AbordageInStorm");
			
			PChar.quest.PZ_Etap6_Start.win_condition.l1 = "location";
			PChar.quest.PZ_Etap6_Start.win_condition.l1.location = "Tortuga";
			PChar.quest.PZ_Etap6_Start.win_condition = "PZ_Etap6_Start";
			locations[FindLocation("Shore58")].DisableEncounters = true;
			SetTimerCondition("PZ_Etap6_Opozdal", 0, 0, 7, false);
			DelMapQuestMarkCity("PortPax");
			AddMapQuestMarkShore("Shore58", true);
			pchar.questTemp.PZ_FlagMartinInfo = true;
			
			// Компаньон-заглушка входит в состав нашей экскадры
			sld = CharacterFromID("PZ_ShipStasis");
			SetCompanionIndex(pchar, -1, sti(sld.index));
			SetCharacterRemovable(sld, true);
			SetShipRemovable(sld, true);
			sld.Dialog.Filename = "Enc_Officer_dialog.c";
			sld.quest.meeting = true;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(sld.id);
			sld.OfficerWantToGo.DontGo = true;
			sld.loyality = MAX_LOYALITY;
			sld.Dialog.CurrentNode = "hired";
			sld.Payment = true;
			sld.ship.HP = sti(sld.ship.HP) / 2;
			
			//
			makearef(arTmp, pchar.questTemp.PZ_PoP_More.ShipPos);
			QuestToSeaLogin_Prepare(stf(arTmp.x), stf(arTmp.z), arTmp.Island);
			DeleteAttribute(pchar, "questTemp.PZ_PoP_More.ShipPos");
			QuestToSeaLogin_Launch();
		break;
		
		case "PZ_AlonsoKaznDialog_1":
			dialog.text = "Dios mio... Никогда не видел и не слышал вас... таким, капитан.";
			link.l1 = "Он весь твой, Алонсо! Давай, покажи, что Святая Инквизиция делает с гугенотами и их приспешниками... А я посмотрю... Затем можешь делать с ним, что захочешь.";
			link.l1.go = "PZ_AlonsoKaznDialog_2";
		break;
		
		case "PZ_AlonsoKaznDialog_2":
			dialog.text = "Да, капитан...";
			link.l1 = "";
			link.l1.go = "PZ_AlonsoKaznDialog_3";
		break;
		
		case "PZ_AlonsoKaznDialog_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, CharacterFromID("PZ_RobertMartinPlennik"), "PZ_AlonsoKazn_2", -1);
		break;
		
		case "PZ_AlonsoKaznDialog_4":
			dialog.text = "Это не займёт много времени, сеньор капитан...";
			link.l1 = "Действуй, мать твою!";
			link.l1.go = "PZ_AlonsoKaznDialog_5";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("PZ_RobertMartinPlennik"));
			LAi_ActorAnimation(npchar, "Barman_idle", "1", 5);
		break;
		
		case "PZ_AlonsoKaznDialog_5":
			DialogExit();
			LAi_SetStayType(pchar);
			LAi_FadeToBlackStart();
			DoQuestCheckDelay("PZ_AlonsoKazn_3", 1.5);
		break;
		
		case "PZ_AlonsoKaznDialog_6":
			dialog.text = "Вставай, дерьма кусок. Вставай, сказал!";
			link.l1 = "Он что, сдох? Сдох?!";
			link.l1.go = "PZ_AlonsoKaznDialog_7";
			CharacterTurnByChr(npchar, CharacterFromID("PZ_RobertMartinPlennik"));
			CharacterTurnByChr(pchar, CharacterFromID("PZ_RobertMartinPlennik"));
		break;
		
		case "PZ_AlonsoKaznDialog_7":
			dialog.text = "Похоже на то, мой капитан...";
			link.l1 = "Ты какого дьявола натворил?!";
			link.l1.go = "PZ_AlonsoKaznDialog_8";
			CharacterTurnByChr(npchar, pchar);
			CharacterTurnByChr(pchar, npchar);
		break;
		
		case "PZ_AlonsoKaznDialog_8":
			dialog.text = "Кто ж знал, что этот олух окажется таким слабаком! Ещё и в панталоны навалил, мерзкая падаль! Будь я проклят, жаровня была лишней...";
			link.l1 = "Ты... Ладно, за борт его, на корм рыбам. Курс на Тортугу. Если понадобится, я разберу по кирпичику - сначала Ля Рош, потом... Потом помоги мне Создатель, если я не найду её живой...";
			link.l1.go = "PZ_AlonsoKaznDialog_9";
		break;
		
		case "PZ_AlonsoKaznDialog_9":
			DialogExit();
			ResetSound();
			chrDisableReloadToLocation = false;
			EndQuestMovie();
			DeleteAttribute(pchar, "GenQuest.BlockDialogCamera");
			locCameraTarget(PChar);
			locCameraFollow();
			AddQuestRecord("PZ", "38");
			
			LAi_SetPlayerType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "", "", "", "", -1);
			npchar.lifeday = 0;
			npchar.location = "None";
			
			bQuestDisableMapEnter = false;
			Island_SetReloadEnableGlobal("Hispaniola2", true);
			Island_SetReloadEnableLocal("Hispaniola2", "reload_2", true)
			Island_SetGotoEnableLocal("Hispaniola2", "reload_2", true);
			Island_SetReloadEnableLocal("Hispaniola2", "reload_3", true)
			Island_SetGotoEnableLocal("Hispaniola2", "reload_3", true);
			DeleteAttribute(pchar, "GenQuest.CannotWait");
			DeleteAttribute(pchar,"questTemp.TimeLock");
			LocatorReloadEnterDisable("LaVega_ExitTown", "reload1_back", false);
			LocatorReloadEnterDisable("PortPax_town", "gate_back", false);
			LAi_LocationDisableOfficersGen("PortPax_town", false);
			LAi_LocationFightDisable(&Locations[FindLocation("PortPax_town")], false);
			DeleteAttribute(pchar, "GenQuest.AbordageInStorm");
			
			PChar.quest.PZ_Etap6_Start.win_condition.l1 = "location";
			PChar.quest.PZ_Etap6_Start.win_condition.l1.location = "Tortuga";
			PChar.quest.PZ_Etap6_Start.win_condition = "PZ_Etap6_Start";
			locations[FindLocation("Shore58")].DisableEncounters = true;
			SetTimerCondition("PZ_Etap6_Opozdal", 0, 0, 7, false);
			DelMapQuestMarkCity("PortPax");
			AddMapQuestMarkShore("Shore58", true);
			
			// Компаньон-заглушка входит в состав нашей экскадры
			sld = CharacterFromID("PZ_ShipStasis");
			SetCompanionIndex(pchar, -1, sti(sld.index));
			SetCharacterRemovable(sld, true);
			SetShipRemovable(sld, true);
			sld.Dialog.Filename = "Enc_Officer_dialog.c";
			sld.quest.meeting = true;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(sld.id);
			sld.OfficerWantToGo.DontGo = true;
			sld.loyality = MAX_LOYALITY;
			sld.Dialog.CurrentNode = "hired";
			sld.Payment = true;
			sld.ship.HP = sti(sld.ship.HP) / 2;
			
			//
			makearef(arTmp, pchar.questTemp.PZ_PoP_More.ShipPos);
			QuestToSeaLogin_Prepare(stf(arTmp.x), stf(arTmp.z), arTmp.Island);
			DeleteAttribute(pchar, "questTemp.PZ_PoP_More.ShipPos");
			QuestToSeaLogin_Launch();
		break;
		
		case "PZ_Norman1":
			dialog.text = "Наконец-то. Теперь этот трон мой. Здесь, на этом камне...";
			link.l1 = "Чёрт возьми, что за... Неужели...";
			link.l1.go = "PZ_Norman2";
		break;
		
		case "PZ_Norman2":
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Маркус";
			else sTemp = "Акула";
			
			dialog.text = "... я создам Церковь мою. Я теперь Папа Римский. Не сметь чертыхаться в Доме Божьем!";
			link.l1 = "А я-то уж подумал... Что ж, Ваше Святейшество, не будете ли вы столь любезны сказать вашему верному прихожанину, где сейчас "+ sTemp +"?";
			link.l1.go = "PZ_Norman3";
		break;
		
		case "PZ_Norman3":
			dialog.text = "Он ушёл в поход. Священный, новый крестовый поход. Он отнимет деньги у нечестивцев и привезёт их мне.";
			link.l1 = "Тебе, как же. Ладно. Он не говорил, когда вернётся?";
			link.l1.go = "PZ_Norman4";
		break;
		
		case "PZ_Norman4":
			NextDiag.TempNode = "PZ_NormanBlock";
			
			dialog.text = "Через месяц. Или чуть позже. Я и сам жду его возвращения вместе со всей нашей паствой.";
			link.l1 = "Получается, он и правда в море. Пойду-ка я, пока не стал таким же как ты - вдруг это ещё заразно.";
			link.l1.go = "Exit";
		break;
		
		case "PZ_NormanBlock":
			NextDiag.TempNode = "PZ_NormanBlock";
			
			dialog.text = "Я очищу, всех их очищу в священном пламени...";
			link.l1 = "Голову бы тебе не помешало очистить...";
			link.l1.go = "Exit";
		break;
		
		case "PZ_HelenaIslaTesoro1":
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 6)
			{
				// ох, какой же костыль, м-м-мать...
				sld = characterFromId("Mary");
				if (sld.location != "Pirates_townhall")
				{
					if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "с Маркусом";
					else sTemp = "со Стивом";
					
					dialog.text = "Шарль! Чем я могу тебе помочь?";
					link.l1 = "Здравствуй, Элен! Я хочу поговорить "+ sTemp +". Он наверху? Или в таверне?";
					link.l1.go = "PZ_HelenaIslaTesoroGood1";
				}
				else
				{
					if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Маркус";
					else sTemp = "Стив";
					
					dialog.text = "Шарль! А, надо же. Какой... приятный сюрприз. Чем могу тебе помочь?";
					link.l1 = "Здравствуй, Элен. А где "+ sTemp +"?";
					link.l1.go = "PZ_HelenaIslaTesoroGoodMaryHere1";
				}
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Маркуса";
				else sTemp = "Акулу";
				
				dialog.text = TimeGreeting() + ", Шарль. Что привело тебя сюда?";
				link.l1 = TimeGreeting() + ", Элен. Я ищу "+ sTemp +". Не знаешь, где он?";
				link.l1.go = "PZ_HelenaIslaTesoroBad1";
			}
		break;
		
		case "PZ_HelenaIslaTesoroGood1":
			dialog.text = "Да, он вышел, но, боюсь, что далеко и надолго - в море, если быть точной.";
			link.l1 = "Надо же. Что-то произошло? Он не говорил, когда вернётся?";
			link.l1.go = "PZ_HelenaIslaTesoroGood2";
		break;
		
		case "PZ_HelenaIslaTesoroGood2":
			dialog.text = "Не говорил, но ничего такого - узнал о хорошей наводке, дело житейское. Как правило, он возвращается через месяц, самое долго, что было - через два. Иногда я тоже скучаю по корабельной палубе...";
			link.l1 = "Ты всегда можешь выйти в море. Было бы неплохо как-нибудь сделать это вместе - ты на 'Радуге', и я на...";
			link.l1.go = "PZ_HelenaIslaTesoroGood3";
		break;
		
		case "PZ_HelenaIslaTesoroGood3":
			NextDiag.TempNode = "PZ_HelenaIslaTesoroGoodBlock";
			
			dialog.text = "Было бы. Но, боюсь, твоя... пассия этого не оценит. Да и я не хочу быть третьей лишней во время похода.";
			link.l1 = "Кхм, извини, Элен, не хотел тебя обидеть. Спасибо за разговор. До встречи.";
			link.l1.go = "Exit";
		break;
		
		// Синистра, не забудь снять эту заглушку и вернуть дефолтную после этого этапа, плиз
		case "PZ_HelenaIslaTesoroGoodBlock":
			NextDiag.TempNode = "PZ_HelenaIslaTesoroGoodBlock";
			
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Маркус";
			else sTemp = "Стив";
			
			dialog.text = "Шарль, ты вернулся. Я могу тебе помочь чем-нибудь ещё?";
			link.l1 = "Нет-нет, спасибо, Элен. Я только хотел заглянуть, не появился ли "+ sTemp +".";
			link.l1.go = "Exit";
		break;
		
		case "PZ_HelenaIslaTesoroBad1":
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Тиракса";
			else sTemp = "Стивена";
			
			dialog.text = "Я бы удивилась, если бы тебе была нужна я. Что же касается "+ sTemp +", то он вышел в море.";
			link.l1 = "Вот как? Надо же. Он не сказал тебе, когда прибудет обратно?";
			link.l1.go = "PZ_HelenaIslaTesoroBad2";
		break;
		
		case "PZ_HelenaIslaTesoroBad2":
			NextDiag.TempNode = "PZ_HelenaIslaTesoroBadBlock";
			
			dialog.text = "Видимо, устаёт от управления этой клоакой и напоминает себе, что он всё ещё капитан корабля. Не первый раз, просто ты раньше как-то не заставал его в походе. Обычно он возвращается через месяц-полтора.";
			link.l1 = "Надо же, никогда раньше не обращал внимания. Спасибо, Элен. До свидания.";
			link.l1.go = "Exit";
		break;
		
		// Синистра, не забудь снять эту заглушку и вернуть дефолтную после этого этапа, плиз
		case "PZ_HelenaIslaTesoroBadBlock":
			NextDiag.TempNode = "PZ_HelenaIslaTesoroBadBlock";
			
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Маркус";
			else sTemp = "Стивен";
			
			dialog.text = ""+ sTemp +" всё ещё не вернулся, Шарль.";
			link.l1 = "Вижу, просто зашёл проверить - вдруг вернётся пораньше.";
			link.l1.go = "Exit";
		break;
		
		case "PZ_HelenaIslaTesoroGoodMaryHere1":
			dialog.text = "Он ведь свободный человек, не правда ли? Может выйти в море в любой момент.";
			link.l1 = "Конечно, может. Так где же он?";
			link.l1.go = "PZ_HelenaIslaTesoroGoodMaryHere2";
		break;
		
		case "PZ_HelenaIslaTesoroGoodMaryHere2":
			NextDiag.TempNode = "PZ_HelenaIslaTesoroGoodMaryHereBlock";
			
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Маркус";
			else sTemp = "Акула";
			
			dialog.text = "Но Шарль, где же ему быть, если на острове его нигде нет? Отправился щипать испанцев. А теперь, если позволишь, у меня много дел. Заглядывай сюда время от времени - обычно "+ sTemp +" возвращается где-то через месяц, бывает, чуть позже.";
			link.l1 = "Хорошо, Элен, не будем тебя отвлекать, спасибо.";
			link.l1.go = "Exit";
		break;
		
		// Синистра, не забудь снять эту заглушку и вернуть дефолтную после этого этапа, плиз
		case "PZ_HelenaIslaTesoroGoodMaryHereBlock":
			NextDiag.TempNode = "PZ_HelenaIslaTesoroGoodMaryHereBlock";
			
			dialog.text = "Я не в настроении, зайди как-нибудь в другой раз, хорошо, Шарль?";
			link.l1 = "Конечно, Элен, извини. Бывай.";
			link.l1.go = "Exit";
		break;
		
		case "PZ_Longway_81":
			if (CheckAttribute(pchar, "questTemp.PZ_FlagMartinInfo"))
			{
				dialog.text = "Мы быть на место, господин капитан. Вы помнить, куда идти?";
				link.l1 = "Конечно, Лонгвэй. Надеюсь, мы не заплутаем в проклятом подземелье...";
				link.l1.go = "PZ_Longway_FlagMartinInfo_1";		//Sinistra
			}
			else
			{
				dialog.text = "Мы быть на месте, господин капитан. У ваш есть план?";
				link.l1 = "Я всё ещё думаю о нём... А что, ты уже что-то придумал?";
				link.l1.go = "PZ_Longway_NotMartinInfo_1";		//Rebbebion
			}
			DelLandQuestMark(npchar);
			LAi_SetCheckMinHP(npchar, 1, true, "");		//На 6 эпизод даём Лонгвею бессмертие
			
			LocatorReloadEnterDisable("Tortuga_town", "houseS4", false);
		break;
		
		case "PZ_Longway_NotMartinInfo_1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Мэри";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Элен";
			dialog.text = "Ну, мой считать, что если наш поспешить к Чанг Шин, то...";
			link.l1 = "Лонгвэй... Я понимаю, как сильно ты хочешь увидеться с сестрой... " + sStr + " сейчас в смертельной опасности, и это не фигура речи! Пойми и ты, что первым делом нужно спасти её!";
			link.l1.go = "PZ_Longway_NotMartinInfo_2";
		break;
		
		case "PZ_Longway_NotMartinInfo_2":
			dialog.text = "Мой сомневаться, что господин капитан по-настоящему понимать, как Лонгвэй переживать все эти десять лет и прямо сейчас.";
			link.l1 = "Ты знаешь, отчасти на самом деле понимаю. Моего брата держат в тюрьме. И хотя его не трогают, в любой момент с ним могут сделать, что захотят - кто знает этих великих людей...";
			link.l1.go = "PZ_Longway_NotMartinInfo_3";
		break;
		
		case "PZ_Longway_NotMartinInfo_3":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Мэри";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Элен";
			dialog.text = "Но куда бы ваш тогда идти, если бы ваш нужно было спасти лишь госпожа " + sStr + "?";
			if (CheckAttribute(pchar, "questTemp.FMQT.GiveDiamonds") && !CheckAttribute(pchar, "questTemp.FMQT_ObchistilSunduk"))
			{
				link.l1 = "Есть одно местечко... один человек... Но ты себе не забивай этим голову, Лонгвэй - я сам должен это сделать.";
				link.l1.go = "PZ_GoMarceline1";
			}
			link.l2 = "На самом деле, я совершенно не знаю, куда идти. Если буду неосторожно вынюхивать везде - привлеку внимание, и тогда " + sStr + " точно конец. Так что... я просто не знаю.";
			link.l2.go = "PZ_GoTogether1";
		break;
		
		case "PZ_GoMarceline1":
			dialog.text = "Что ваш иметь ввиду? Почему?";
			link.l1 = "Что тебя туда просто не пустят - высшее общество, чёрт его побери. Так что я один пойду. Ну а ты тем временем беги к сестре. Я присоединюсь сразу же, как только смогу. Удачи, Лонгвэй!";
			link.l1.go = "PZ_GoMarceline2";
			RemovePassenger(pchar, npchar);
		break;
		
		case "PZ_GoMarceline2":
			dialog.text = "Да! Спасибо, господин капитан. И ваш удача!";
			link.l1 = "Ох, спасибо - она сегодня мне крайне необходима. Всем нам.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_MarcelineLongwayGo");
		break;
		
		case "PZ_GoTogether1":
			dialog.text = "Господин капитан...";
			link.l1 = "В любом случае, я собираюсь пойти с тобой, Лонгвэй. Разделяться сейчас подобно смерти. Поспешим к твоей сестре и выясним у неё, где логово Левассера. А затем вместе отправимся туда - сейчас мне нужна вся возможная помощь. Надеюсь, не опоздаем.";
			link.l1.go = "PZ_GoTogether2";
		break;
		
		case "PZ_GoTogether2":
			dialog.text = "Не опоздаем, господин капитан. Не будем более медлить и тратить время на споры. Отправляться к Чанг Шин!";
			link.l1 = "Ты прав, поторопимся.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TogetherLongwayGo");
		break;
		
		case "PZ_FrenchSoldier1":
			dialog.text = "Ты куда собрался? Ты хоть знаешь, куда ведёт эта дверь?";
			link.l1 = "Прекрасно знаю, я иду туда по делу, а не из праздного любопытства или чтобы обворовать.";
			link.l1.go = "PZ_FrenchSoldier2";
		break;
		
		case "PZ_FrenchSoldier2":
			dialog.text = "Какому ещё делу? Госпожа Левассер сейчас не принимает. К тому же, она замужняя женщина - негоже тут всяким у неё шастать.";
			link.l1 = "Замужняя, верно. Но ведь она устраивает приёмы время от времени, не так ли? В том числе индивидуальные. Сейчас как раз такой. Она меня ждёт, я очень тороплюсь.";
			link.l1.go = "PZ_FrenchSoldier3";
		break;
		
		case "PZ_FrenchSoldier3":
			dialog.text = "Она бы меня предупредила в таком случае.";
			link.l1 = "Я особенный гость, о таких не всегда предупреждают. И они любят приходить сами.";
			link.l1.go = "PZ_FrenchSoldier4";
		break;
		
		case "PZ_FrenchSoldier4":
			dialog.text = "Ага, а потом после таких 'особенных гостей' Его Светлость прикажет меня расстрелять. Или госпожа сама велит снять с меня шкуру.";
			link.l1 = "Я ранее уже бывал гостем госпожи Марселины. Уверяю тебя, ничего с тобой потом не случится, служивый.";
			link.l1.go = "PZ_FrenchSoldier5";
		break;
		
		case "PZ_FrenchSoldier5":
			dialog.text = "Конечно, верить и пропускать всех подряд - именно в этом заключается работа городской стражи.";
			link.l1 = "Видит Бог, я хотел по-хорошему, упрямый ты осёл...";
			link.l1.go = "Exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_FrenchSoldierFight");
		break;
		
		case "PZ_Marceline1":
			dialog.text = "Вы?..";
			// начинаем проверять результат прохождения "Почти как дома"
			switch (pchar.questTemp.FMQT.Marceline)
			{
				// поделили алмазы и "охладили трахание, углепластики" (с)
				case "Fuck":
					link.l1 = "О да, мадам. Ваш рыцарь рад новой встрече с вами. Вижу, вы удивлены меня видеть. Неужели радость от этой встречи... не взаимна?";
					link.l1.go = "PZ_MarcelineFuck1";
				break;
				
				// поделили алмазы, без трахания и углепластиков
				case "NoFuck":
					link.l1 = "Да, я. Понимаю, что я не самый красивый и достойный мужчина на этом острове, как вы изволили выразиться во время нашей последней встречи, но хотя бы вы знаете, что я честный человек. Выслушайте меня, мадам - я не отниму много вашего... драгоценного времени.";
					link.l1.go = "PZ_MarcelineNoFuck1";
				break;
				
				// "сошлись вот где-то посередине" (с)
				case "Deception":
					link.l1 = "Чш-ш-ш, Бога ради, только не кричите, мадам. Я здесь не для того, чтобы расквитаться с вами за то, что вы обманули вашего рыцаря и сбежали с сокровищами дракона. И уверяю вас - желай я вас убить - выстрелил бы и бежал со всех ног. Это же Тортуга! Но, думаю, вы и так знаете, что это было бы ниже моего достоинства.";
					link.l1.go = "PZ_MarcelineDeception1";
				break;
			}
		break;
		
		case "PZ_MarcelineFuck1":
			dialog.text = "Ах, что вы! Я просто подумала, что... А, впрочем, это и не важно! Видите ли, злые языки распускают грязные слухи обо мне - бедной женщине, которая, даже если бы и захотела, не смогла бы ни навредить кому, ни защититься от недругов. Да и столько времени прошло... Я думала, что вы явились ко мне не просто так и не с благими намерениями. Рада ошибиться. Трудно жить, когда вокруг одни недоброжелатели.";
			link.l1 = "Да как я мог!.. Даже если бы я услышал что-то такое - то не поверил бы ни слову. Но вы правы в том, что я явился сюда не просто для того, чтобы увидеть вас. Хоть и очень рад этому. Знаю, прозвучит необычно, но... на этот раз вашему рыцарю нужна ваша помощь, мадам.";
			link.l1.go = "PZ_Marceline2";
		break;
		
		case "PZ_MarcelineNoFuck1":
			dialog.text = "А вы куда обидчивее, чем я предполагала. Однако вы тоже хороши, месье де Мор - я думала, что вы гораздо более... утончённый. На деле же... либо вы всегда таким были, либо Архипелаг уже успел извратить вас. Вам стоит заново поучиться тому, как разговаривать с дамой. Но вы правы - человек вы честный, пусть и... простоватый.";
			link.l1 = "Вы тоже женщина гордая и мстительная. Об этом говорят и ваши глаза, и слова, и... поступки. Так что если кто меня и поймёт - так это вы. Как и я вас когда-то. Так что не будем более ворошить прошлого. Не могли бы вы мне помочь, мадам?";
			link.l1.go = "PZ_Marceline2";
		break;
		
		case "PZ_MarcelineDeception1":
			dialog.text = "Ох... Признаю, некрасиво тогда поступила с вами. Но только потому, что была не до конца уверена в вас, не более того!.. Может, вы бы отняли у меня все алмазы? Или привели туда моего мужа, сказав, что узнали от наших слуг, что я его обокрала, отрицая и ваше участие в этом. В конце концов, все вокруг ищут его расположение, а не бедной женщины вроде меня... Теперь я понимаю, что ошибалась в вас. Примите мои извинения... мой рыцарь.";
			link.l1 = "Уж не знаю теперь, искренние они теперь, или нет. Но это и не важно. Мне... нужна ваша помощь, мадам Марселина. Дело жизни и смерти. В прямом смысле. Прошу, не откажите.";
			link.l1.go = "PZ_Marceline2";
		break;
		
		case "PZ_Marceline2":
			dialog.text = "Моя помощь?.. Я, конечно, не последняя женщина в городе, но моё влияние не так велико, как вам всем кажется. Я - королева, что царствует, а не правит. Но я вас выслушаю. Чем же вам может помочь моя скромная персона?";
			link.l1 = "Я понимаю, что это неприятная для вас тема, но я ищу вашего супруга, мадам, и как можно скорее. Дело в том, что...";
			link.l1.go = "PZ_Marceline3";
		break;
		
		case "PZ_Marceline3":
			dialog.text = "Это что, шутка? А в резиденции его сейчас нет? Значит, отбыл по делам. Ничем не могу вам помочь, месье де Мор.";
			link.l1 = "Вы отвели глаза. Значит, вы тоже знаете. Я слышал о его подземелье, где он издевается над девушками. Мне лишь нужно туда добраться. Прошу, не притворяйтесь, будто впервые слышите об этом - вы слишком умны, чтобы не знать.";
			link.l1.go = "PZ_Marceline4";
		break;
		
		case "PZ_Marceline4":
			dialog.text = "Ох, чувствую, этот разговор прибавит мне ещё один седой волос. Как будто мне и так мало первых морщин. Что же ты с нами всеми делаешь, Франсуа...";
			link.l1 = "Седой локон лишь добавит вам благородства и не отнимет красоты. Но к вашему мужу попала одна добрая, невинная девушка. И теперь она рискует потерять красоту, здоровье и даже саму жизнь!.. Вы знаете, что бывает с теми, кто попадает туда. Пожалуйста, мадам. Марселина... Выручите своего рыцаря.";
			link.l1.go = "PZ_Marceline5";
		break;
		
		case "PZ_Marceline5":
			dialog.text = "Уже не моего, верно? Перестаньте, я же не дура. Но... я помогу вам, месье де Мор. В конце концов, это не могло продолжаться вечно. И однажды бы стало известно общественности. Мне сейчас важно вовремя и грамотно уйти. И... я не смогу обречь вас на вечные страдания, вызванные тем, что мой 'благоверный' сделает с вашей... знакомой.";
			link.l1 = "Может, я больше и не ваш рыцарь, мадам. Но и вы с самого начала не были моей леди. Однако я буду вам всю жизнь благодарен. Так где находится это место?";
			link.l1.go = "PZ_Marceline6";
		break;
		
		case "PZ_Marceline6":
			dialog.text = "Что ж, ловлю вас на слове, Шарль. В городских подземельях. В одном из тупиков стоит большая бочка, рядом с ней начинается проход, ведущий в логово этого изверга. Внутрь я не заглядывала - проследовала за ним лишь один раз и давно. И испугалась, услышав, какие нечеловеческие крики издают те бедняжки.";
			link.l1 = "Вы сегодня спасли много жизней, мадам. Не только моего дорого человека, но и всех, кто в будущем мог бы попасть к вашему мужу. Благодарю.";
			link.l1.go = "PZ_Marceline7";
		break;
		
		case "PZ_Marceline7":
			dialog.text = "Ах, оставьте меня с этими пустыми словами, месье. Вы очень о многом меня попросили. И я пошла на огромный риск. Постарайтесь уж теперь, чтобы ваш новый поход в логово дракона был успешным... мой рыцарь.";
			link.l1 = "Постараюсь изо всех сил. До свидания, Марселина.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_MarcelineOver");
		break;
		
		case "PZ_ElitaShluha_18":
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko") && !CheckAttribute(pchar, "questTemp.PZ_DevushkaMertva"))
			{
				dialog.text = "Так вы - бандит, месье?.. Мы так не принимаем новых работниц - все мы появились здесь добровольно. Мне придётся попросить вас с вашим... подельником выйти. И я прослежу, чтобы эта девушка получила лечение - иначе сообщу о вас властям!";
				link.l1 = "Не бандиты мы. А эта девушка даст фору любому из них. И клинок носит не для вида. Просто ранена. Этот же человек - мой друг. А ещё он - родной брат вашей хозяйки. Так что позвольте нам пройти к ней.";
				link.l1.go = "PZ_ElitaShluha_WithLongwayAndGirl1";
			}
			else
			{
				dialog.text = "Рады вас снова видеть, месье! Ой, а вы знаете, мы не принимаем здесь гостей... низкого сорта. Даже если за них ручаются и платят. Особенно желтокожих батраков или рабов-негров. Боюсь, ваш друг вынужден уйти.";
				link.l1 = "Смотрите, не скажите такое при вашей хозяйке - она ведь тоже желтокожая. И никакой это не батрак, а брат её родной. Давно потерянный. Ищет её. Вы же не помешаете семейному воссоединению? Я ручаюсь за своего друга.";
				link.l1.go = "PZ_ElitaShluha_WithLongway1";
			}
		break;
		
		case "PZ_ElitaShluha_18_1":
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko") && !CheckAttribute(pchar, "questTemp.PZ_DevushkaMertva"))
			{
				dialog.text = "Час от часу не легче... Сначала обезумевший жёлтый батрак, а теперь ещё и вы. Нет, месье, мы не платим за приведённых к нам силком девушек - здесь все оказались по своей воле.";
				link.l1 = "Ни в коем случае - я спас эту девушку, и она никогда не будет работать в подобном месте - это ниже её достоинства. Батрак, говорите?";
				link.l1.go = "PZ_ElitaShluha_AfterLevasseurWithGirl1";
			}
			else
			{
				dialog.text = "Ох месье, как вы невовремя! А мы сегодня больше не принимаем - сами видите, что у нас тут произошло.";
				link.l1 = "Я как раз по этому поводу. Это всё ведь устроил некий желтокожий мужчина, верно?";
				link.l1.go = "PZ_ElitaShluha_AfterLevasseurWithoutGirl1";
			}
		break;
		
		case "PZ_ElitaShluha_AfterLevasseurWithGirl1":
			dialog.text = "Да, месье, батрак! Мы едва понимали, что он говорит! Этот оборванец ворвался и потребовал встречи с госпожой. Уверял нас, что он её брат. Мы позвали мужчин, но...";
			link.l1 = "Это для него не препятствие. Что было потом?";
			link.l1.go = "PZ_ElitaShluha_AfterLevasseurWithGirl2";
		break;
		
		case "PZ_ElitaShluha_AfterLevasseurWithGirl2":
			for (i = 1; i <= 4; i++)
			{
				sld = characterFromId("PZ_EliteBrothelMercenary" + i);
				sld.lifeday = 0;
			}
			
			dialog.text = "Как оказалось, он не соврал. Госпожа вышла к нам и узнала его. Собственно, они до сих пор разговаривают в её роскошном кабинете.";
			link.l1 = "Однако кто знает, что у него в голове. Мы идём туда, если понадобится - спасём её. Не поднимайте шум - это уничтожит репутацию заведения.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_EliteBrothelCreateChangShin");
		break;
		
		case "PZ_ElitaShluha_AfterLevasseurWithoutGirl1":
			dialog.text = "Всё именно так, месье. Сказал, что он брат госпожи.";
			link.l1 = "И вы его не пропустили...";
			link.l1.go = "PZ_ElitaShluha_AfterLevasseurWithoutGirl2";
		break;
		
		case "PZ_ElitaShluha_AfterLevasseurWithoutGirl2":
			dialog.text = "Конечно, нет! Госпожа изысканно одета и говорит без акцента, в отличие от того батрака. Мы пытались его прогнать, а он положил всю охрану, представляете?!";
			link.l1 = "Легко могу представить. И где он сейчас?";
			link.l1.go = "PZ_ElitaShluha_AfterLevasseurWithoutGirl3";
		break;
		
		case "PZ_ElitaShluha_AfterLevasseurWithoutGirl3":
			for (i = 1; i <= 4; i++)
			{
				sld = characterFromId("PZ_EliteBrothelMercenary" + i);
				sld.lifeday = 0;
			}
			
			dialog.text = "Они с госпожой всё ещё о чём-то разговаривают, но мы не можем понять, о чём - видимо, на своём языке.";
			link.l1 = "Я пойду к ним. Возможно, вашей госпоже нужна помощь. Не зовите стражу - в случае огласки к вам уже больше никто и никогда не зайдёт.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_EliteBrothelCreateChangShin");
		break;
		
		case "PZ_ElitaShluha_WithLongway1":
			dialog.text = "Брат? Госпожа выглядит достойно, чего не скажешь об этом её 'брате'. Не стоит морочить ей голову и пытаться обмануть на деньги с помощью этого батрака. Уведите его.";
			link.l1 = "Я же сказал, что они давно потеряли друг друга. Просто ему меньше повезло. Мы сами заплатим заведению за потраченное время. Сообщите о нас хозяйке.";
			link.l1.go = "PZ_ElitaShluha_WithLongway2";
		break;
		
		case "PZ_ElitaShluha_WithLongway2":
			dialog.text = "Нечего ей о вас знать. И мне не нравится ваша настойчивость. Мальчики! Выкиньте этого батрака! И его попутавшего берега господина - тоже!";
			link.l1 = "Проклятье! Сколько же гонору для куртизанки!";
			link.l1.go = "Exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_EliteBrothelFight");
		break;
		
		case "PZ_ElitaShluha_WithLongwayAndGirl1":
			dialog.text = "Ещё чего! Чтобы хозяйка была один на один со всей этой вашей странной компанией? Только, если вы пойдёте туда один, месье. И ваши... друзья будут ждать на улице - у нас здесь приличное заведение.";
			link.l1 = "Чего ей бояться? Всем известно, что она - один из лучших фехтовальщиков Тортуги. И мои друзья будут поприличнее большинства людей в этом городе.";
			link.l1.go = "PZ_ElitaShluha_WithLongwayAndGirl2";
		break;
		
		case "PZ_ElitaShluha_WithLongwayAndGirl2":
			dialog.text = "Ребята!!! Здесь раненая бандитка и грязный батрак! Им что-то нужно от хозяйки! Разберитесь с ними!";
			link.l1 = "Какая самоотверженность, чёрт возьми...";
			link.l1.go = "Exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_EliteBrothelFight");
		break;
		
		case "PZ_ChangShin1":
			locCameraFromToPos(2.17, 2.32, 0.55, true, -0.92, -0.37, -4.09);
			sld = characterFromId("Longway");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto9", "PZ_LongwayTurnToChangShin", -1);
			
			// итак, снова проверка по результатам прохождения. Лонгвэй с нами, тян ещё в пыточной
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
			{
				dialog.text = "Видимо, ты Шарль де Мор? А это?.. Неужели...";
				link.l1 = "А ты, видимо, Бэлль Этуаль. Или мне лучше сказать Чанг Шин? И да. Это твой брат. Он искал тебя больше десяти лет. У нас с ним к тебе много, много вопросов. И довольно мало времени.";
				link.l1.go = "PZ_ChangShin_WithLongway1";
			}
			// пришли с Лонгвэем и тян
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom") && CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
			{
				dialog.text = "А ты уцелела, надо же. У тебя неплохой защитник, пусть он и немного опоздал. Всяко лучше, чем тот, кто, видимо, считает меня своим защитником и стоит сейчас рядом с вами. Небо благоволит тебе.";
				link.l1 = "Значит, ты догадалась. Так даже лучше - меньше объяснений. Но скажи, чему это ты улыбаешься... Чанг Шин? Нравится смотреть на страдания других девушек, да? Раз уж ты их продаёшь.";
				link.l1.go = "PZ_ChangShin_WithLongwayAndGirl1";
			}
			// Лонгвэй с нами, тян на небесах
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom") && CheckAttribute(pchar, "questTemp.PZ_DevushkaMertva"))
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Мэри";
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Элен";
				dialog.text = "Шарль де Мор, верно? Я слышала, ты хотел меня видеть. Так чем же ты недоволен? Не понравилось обслуживание в нашем заведении, когда был здесь в прошлый раз?";
				link.l1 = "Я только что из другого заведения, где ты иногда бываешь, Чанг Шин. "+ sStr +", моя возлюбленная, мертва. И я знаю, что ты тоже приложила к этому руку.";
				link.l1.go = "PZ_ChangShin_GirlDied1";
			}
		break;
		
		case "PZ_ChangShin_WithLongway1":
			dialog.text = "Чанг Шин... давно я не слышала этого имени. Очень давно. Белые люди... вечно вы куда-то торопитесь. А как же неторопливое семейное воссоединение? Хотя мне плевать. Я перестала надеяться на других людей уже как много лет назад. Что же ты молчишь, как воды в рот набрал, брат мой? Неужто не рад родной сестре? Ты же так искал меня.";
			link.l1 = "Потому что у нас есть и другое, крайне срочное и крайне важное дело. Поговори с сестрой, Лонгвэй. Но помни, куда нам ещё идти. Нам нужно поторапливаться. И у меня тоже есть к ней вопросы.";
			link.l1.go = "PZ_Longway_SisterDialog1";
		break;
		
		case "PZ_Longway_SisterDialog1":
			locCameraFromToPos(0.65, 2.59, -3.06, true, 0.23, 0.34, -5.21);
			
			sld = characterFromId("Longway");
			ChangeCharacterAddressGroup(sld, "Tortuga_brothelElite_room2", "goto", "goto8");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, characterFromId("PZ_ChangShin"));
			
			sld = characterFromId("PZ_ChangShin");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, characterFromId("Longway"));
			
			dialog.text = "(На китайском) Лонгвэй, значит? Что ж, если не считать имени, то ты почти не изменился... Чанг Ту.";
			link.l1 = "(На китайском) А вот ты очень изменилась, сестра. Что же произошло? Раньше твой взгляд согревал не слабее полуденного солнца. А теперь он холоден и выражает лишь презрение. А твой голос? Ласковый и нежный, я так любил тебя смешить и слушать этот звон серебристых колокольчиков... Теперь же он холоднее, чем Гоанго зимой. И ты носишь их одежду. И продаёшь девушек сама, хотя тебя когда-то похитил Ферментелуш.";
			link.l1.go = "PZ_Longway_SisterDialog2";
		break;
		
		case "PZ_Longway_SisterDialog2":
			dialog.text = "Пришёл мне мораль читать, хотя сам когда-то работал на Роденбурга, одного из главных мерзавцев Архипелага? Думаешь, я не знала о тебе? Мне ведомо многое. И не тебе судить, какой я стала и почему, мой непутёвый старший брат.";
			link.l1 = "Так позволь узнать, Шин! И скажи. Если ты знала, что я на Архипелаге, почему не захотела встретиться со мной спустя столько лет?.. Я посвятил твоим поискам едва ли не всю жизнь...";
			link.l1.go = "PZ_Longway_SisterDialog3";
		break;
		
		case "PZ_Longway_SisterDialog3":
			dialog.text = "Потому что от самого ужасного ни ты, ни Небеса меня не уберегли. А затем я уже поняла, что ни в ком на свете более не нуждаюсь. И могу полагаться только на себя. Ну что ж, я расскажу тебе, раз ты так хочешь узнать. Но говорить я буду на его языке. Наверняка он тоже хотел бы послушать. Ты же понимаешь по-французски, Ту?";
			link.l1 = "(На французском) Да, мой говорить этот язык.";
			link.l1.go = "PZ_Longway_SisterDialog4";
		break;
		
		case "PZ_Longway_SisterDialog4":
			dialog.text = "Ха-ха-ха, о, Небо! Твой акцент ужасен. Впрочем, ты не так уж и виноват - произношение и письменность французского и правда малость сложны.";
			link.l1 = "Как же поменялся твой смех, сестра...";
			link.l1.go = "PZ_ChangShin_WithLongway3";
		break;
		
		/*case "PZ_Longway_SisterDialog5":
			Return_LongwayOfficer();
			
			StartInstantDialog("PZ_ChangShin", "PZ_ChangShin_WithLongway3", "Quest\CompanionQuests\Longway.c");
		break;*/
		
		case "PZ_ChangShin_WithLongway3":
			locCameraFromToPos(2.17, 2.32, 0.55, true, -0.92, -0.37, -4.09);
			sld = characterFromId("Longway");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto9", "PZ_LongwayTurnToChangShin", -1);
			dialog.text = "Мой дорогой братец желает знать, что же со мной произошло за все эти годы. Думаю, тебе тоже будет не лишним послушать - как ты сказал, у тебя есть вопросы. Поэтому можешь не переживать - я расскажу обо всём этом на французском.";
			link.l1 = "Расскажи главное - когда Лонгвэй рассказывал мне историю своей жизни, это заняло добрых несколько часов. А я сейчас очень спешу.";
			link.l1.go = "PZ_ChangShin_WithLongway4";
		break;
		
		case "PZ_ChangShin_WithLongway4":
			dialog.text = "Потерпишь. Я держала всё это в себе не один год. А будешь перебивать - и я не стану отвечать ни на один твой вопрос.";
			link.l1 = "Ну хорошо... Тогда продолжай.";
			link.l1.go = "PZ_ChangShin2";
		break;
		
		case "PZ_ChangShin_WithLongwayAndGirl1":
			dialog.text = "Где же твои манеры, Шарль де Мор? Мне говорили, что ты человек превосходных манер и образцовый дамский угодник? Просто слухи, а на деле, как всегда, пшик? Так я и думала. И ты неправ - я одинаково сильно ненавижу всех людей. И с радостью бы раздавила твои тестикулы, попадись ты мне в руки. А вообще, я уже никому не верю, ничему не удивляюсь и ничего не жду. Но услышать своё настоящее имя спустя столько лет было немного... освежающе.";
			link.l1 = "Я дамский угодник для дам, а не для ведьм вроде тебя. Да и вообще, чего ты ожидала, учитывая, что ты причастна к мучениям самого дорогого мне человека? Я тоже едва сдерживаюсь, чтобы не сделать с тобой что-нибудь. Не в последнюю очередь - ради него. Лонгвэй - мой друг. А ты - его семья. Он искал тебя больше десяти лет. И заслуживает поговорить с тобой.";
			link.l1.go = "PZ_ChangShin_WithLongwayAndGirl2";
		break;
		
		case "PZ_ChangShin_WithLongwayAndGirl2":
			dialog.text = "Как сентиментально. И как жаль, что мне плевать. Но ты так легко теперь не уйдёшь, верно, Ту? Не убивать же тебя и всех вас за то, что ты когда-то опоздал. Но вот знать... пожалуй, знать ты и правда заслуживаешь. То, что я не всегда была такой, ты и так всегда знал.";
			link.l1 = "Что бы с тобой ни произошло... у тебя всегда был выбор, Чанг Шин.";
			link.l1.go = "PZ_ChangShin_WithLongwayAndGirl3";
		break;
		
		case "PZ_ChangShin_WithLongwayAndGirl3":
			dialog.text = "Ты ещё молод и не знаешь, как устроен этот мир, Шарль де Мор. Выбор есть только один - жить или сдохнуть. Пожалуй, тебе тогда тоже не будет лишним узнать всё. Так что расскажу всё на французском. Ту ведь говорит на нём?";
			link.l1 = "С акцентом. Но прекрасно понимает. Можешь начинать.";
			link.l1.go = "PZ_ChangShin2";
		break;
		
		case "PZ_ChangShin_GirlDied1":
			dialog.text = "И где же ты был всё это время? От Эспаньолы до сюда день-два пути. А ты умудрился опоздать. Так что её смерть - и твоя вина тоже. Ну а ты. Ты вовсе опоздал на десять с лишним лет. Вот такие из вас спасители, защитники вы наши. Чем раньше женщина научится защищаться сама, тем лучше. Кто-то это делает вовремя, кто-то - нет. А кому-то не хватает мозгов к этому прийти.";
			link.l1 = "Будь осторожна с каждым своим последующим словом. Я до сих пор не разорвал тебя на кусочки лишь ради своего друга, твоего брата. Ты и понятия не имеешь, через что ему пришлось пройти ради тебя.";
			link.l1.go = "PZ_ChangShin_GirlDied2";
		break;
		
		case "PZ_ChangShin_GirlDied2":
			dialog.text = "Я сильно сомневаюсь, что он перенёс хотя бы отдалённо схожее с тем, что вынесла я.";
			link.l1 = "Ну так расскажи нам.";
			link.l1.go = "PZ_ChangShin2";
		break;
		
		case "PZ_ChangShin2":
			dialog.text = "Ну, что тут сказать, я тогда была молода, глупа и наивна. И нетерпима. Ту уже рассказывал о том, что я была похищена Оливерио Ферментелушем после того, как он убил наших с ним родителей?";
			link.l1 = "Верно.";
			link.l1.go = "PZ_ChangShin3";
		break;
		
		case "PZ_ChangShin3":
			dialog.text = "Ранее он признавался в чувствах, но я отвергла его. И тогда-то он и вырезал нашу семью и украл меня. А потом...";
			link.l1 = "Догадываюсь.";
			link.l1.go = "PZ_ChangShin4";
		break;
		
		case "PZ_ChangShin4":
			dialog.text = "Если бы. Потом он мне снова горячо и в слезах признался в чувствах, сказал, что иначе просто не выходило, ведь я проводила почти всё время с семьёй.";
			link.l1 = "Безумие какое-то...";
			link.l1.go = "PZ_ChangShin5";
		break;
		
		case "PZ_ChangShin5":
			dialog.text = "Хех, да вся моя жизнь с того дня - одно сплошное безумие. Я отвергла его снова. И так продолжалось ещё какое-то время. Но ясно, что это не могло длиться вечность, ведь я была целиком в его власти.";
			link.l1 = "Значит, это всё же произошло?";
			link.l1.go = "PZ_ChangShin6";
		break;
		
		case "PZ_ChangShin6":
			dialog.text = "Конечно. Он взял меня силой, грубо и беспощадно. Не то чтобы это когда-либо волновало насильников, но не он ли ранее слёзно признавался мне в великой любви? Её и след простыл. Не было ни извинений, ни новых признаний, ни даже попыток как-то оправдаться. И всё это продолжалось каждый день, как нечто само собой разумеющееся. Поначалу я кричала и сопротивлялась, а потом перестала - какой смысл?..";
			link.l1 = "Однако Ферментелуш получил по заслугам, а ты оказалась здесь. Как это произошло?";
			link.l1.go = "PZ_ChangShin7";
		break;
		
		case "PZ_ChangShin7":
			dialog.text = "Ну, в довольно скором времени я ему надоела. Забавно, да? Он убил наших с Ту родителей, выкрал меня, бесчестил на регулярной основе, чтобы потом просто сказать, что более я ему не нужна. Он прибыл на этот Архипелаг и продал меня Левассеру в качестве рабыни.";
			link.l1 = "Даже врагу я бы такого не пожелал. И как же ты выжила? И вообще, оказалась на свободе? Учитывая то, что я слышал, Левассер не выпускал девушек наружу из своего убежища. И всегда избавлялся от них.";
			link.l1.go = "PZ_ChangShin8";
		break;
		
		case "PZ_ChangShin8":
			dialog.text = "Это сейчас так обстоят дела. Тогда Левассер был иным. Нет, животным он был всегда. Но поначалу он просто изредка похищал местных молодых колонисток, сношал их против воли в своём подвале и почти сразу же избавлялся, чтобы не платить за молчание. Лишь изредка он держал их дольше, чем несколько дней, в те годы. Со мной же всё было иначе с самого начала.";
			link.l1 = "Потому что ты была рабыней, верно?";
			link.l1.go = "PZ_ChangShin9";
		break;
		
		case "PZ_ChangShin9":
			dialog.text = "Именно. Главным желанием Левассера было не одно только физическое удовольствие. И даже не сиюминутное ощущение власти над жертвами - в конце концов, она у него надо всем островом. А...";
			link.l1 = "... наслаждение тем, как они ломаются - их воля, взгляд, голос, поведение.";
			link.l1.go = "PZ_ChangShin10";
		break;
		
		case "PZ_ChangShin10":
			dialog.text = "Да. Вижу, ты пришёл подготовленным. Но в этом плане ему было со мной скучно - Ферментелуш привёз меня уже сломленной. И красивой меня Левассер тоже не считал - на самом деле ему не нравятся азиатские женщины. Знаешь, почему-то это так сильно повлияло на меня - я понимаю, что привлекательна, но по-настоящему красивой себя не считаю. И не верю, когда мне это говорят. Даже сейчас, когда упражняюсь, ношу шелка и поливаю себя изысканными духами. Не то чтобы мне было нужно одобрение моего мучителя, но...";
			link.l1 = "Что ж, тогда я снова повторю свой вопрос - как же ты выжила? Как только ему надоедает та или иная женщина, он от неё избавляется. С тобой же ему было скучно сразу, как ты говоришь.";
			link.l1.go = "PZ_ChangShin11";
		break;
		
		case "PZ_ChangShin11":
			dialog.text = "Видимо, то, что было скучно изначально, и повлияло. И то, что я была рабыней - не могла ни пойти куда-либо, ни сказать что-либо. С рабынями тысячелетиями делали, что хотели. Тогда он начал думать, как сделать так, чтобы время, проведённое со мной, было для него 'весёлым'.";
			link.l1 = "Похоже, так и появились на свет его пристрастия, в их нынешнем виде.";
			link.l1.go = "PZ_ChangShin12";
		break;
		
		case "PZ_ChangShin12":
			dialog.text = "Именно. Поначалу это были избиения, плевки и прочие унижения. И насмешки - как над моей лично внешностью, так и над моим происхождением, моей кровью. А затем пошли первые пытки - ножи, щипцы, жаровня... Поэтому я ношу такую закрытую одежду - всё тело в шрамах, ожогах и увечьях. И потому больше не планирую раздеваться перед мужчиной. Никогда. Тогда я наконец-то поняла то, что следовало понять ещё во время похищения меня Ферментелушем.";
			link.l1 = "Что именно?";
			link.l1.go = "PZ_ChangShin13";
		break;
		
		case "PZ_ChangShin13":
			dialog.text = "Что я не должна более быть безвольной куклой. А напротив - управлять своей жизнью. Со мной это был тот случай, когда женщина может хоть как-то менять свою жизнь только управляя мужчинами, что её окружают.";
			link.l1 = "Не сказал бы, что Левассером можно управлять.";
			link.l1.go = "PZ_ChangShin14";
		break;
		
		case "PZ_ChangShin14":
			dialog.text = "И ты не ошибёшься. Но осторожно влиять можно на всех. Левассер одинаково ненавидит как полное послушание с самого начала, так и споры или мольбы. Это я поняла сразу, весьма мучительной ценой. Как и лесть - видимо, осознавал, какая он свинья на самом деле. Но, когда он был всем доволен после очередного вечера пыток и насилия, с ним можно было осторожно поговорить. Пусть я и не благородного происхождения, но умом не обделена.";
			link.l1 = "И о чём же вы говорили?";
			link.l1.go = "PZ_ChangShin15";
		break;
		
		case "PZ_ChangShin15":
			dialog.text = "Я разжигала его интерес. Предлагала идеи для мучений, советовала, какие пыточные устройства лучше не использовать, а какие - наоборот, стоит завести. Поначалу он пробовал это всё на мне, конечно же. Но затем... он начал меня уважать, чёрт его возьми. Что же у него в голове? Я пыталась узнать, как он таким стал, но он снова избил меня до полусмерти. После чего схватился за голову и привёл личного врача.";
			link.l1 = "Это ещё более странно и отвратительно, чем то, что я уже слышал о нём.";
			link.l1.go = "PZ_ChangShin16";
		break;
		
		case "PZ_ChangShin16":
			dialog.text = "Более он не требовал от меня отдаваться ему - 'всё равно уродливая жёлтая обезьяна', как он говорил, уже больше по привычке и в шутку. Называл ученицей. Но всегда говорил, что как его прожект - я полное разочарование. Видимо, чтобы не расслаблялась. И начал обучать меня фехтованию, языкам, хоть и удерживал всё ещё в подвале, но именно мне, а не своей жене дарил дорогие платья.";
			link.l1 = "Действительно - прожект. Видно явную параллель с тем, как этим заведением управляешь ты.";
			link.l1.go = "PZ_ChangShin17";
		break;
		
		case "PZ_ChangShin17":
			dialog.text = "Я об этом не задумывалась, хм-м-м. И мне не нравится твоя параллель, ведь я не пытаю своих работниц. И не позволяю клиентам этого делать. Хоть и ненавижу этих куриц и завидую их красоте. И с этой свиньёй у меня ничего общего, так и знай.";
			link.l1 = "Как же ты получила этот бордель?";
			link.l1.go = "PZ_ChangShin18";
		break;
		
		case "PZ_ChangShin18":
			dialog.text = "От Левассера, конечно. Ещё некоторое время он держал меня у себя. Изредка даже советовался, как сломать ту или иную девицу. И как лучше мучить её так, чтобы сердце не остановилось раньше времени. В конце концов, я была особенной для него, пусть он это ни за что и не признает. Я была первой. Я видела всё.";
			link.l1 = "Это ещё кто у кого учился, чёрт побери...";
			link.l1.go = "PZ_ChangShin19";
		break;
		
		case "PZ_ChangShin19":
			dialog.text = "Я не такая! Я всей душой ненавижу тех, у кого с самого рождения было всё! Это несправедливо! Так что этот бордель - моя идея. Эти работницы - дочери купцов, чиновников и дворян, что иногда попадали к Левассеру. Я попросила его передать их мне. Пытки и унижения в тайном подвале - это одно. А вот публичная деятельность куртизанки для таких, как они - совсем другое!";
			link.l1 = "Я бы не сказал, что твои работницы выглядят такими уж униженными, несчастными и сломленными.";
			link.l1.go = "PZ_ChangShin20";
		break;
		
		case "PZ_ChangShin20":
			dialog.text = "Потому что знают, что Левассер или даже я сделаем с ними, если они хоть пикнут. Но ты прав отчасти, конечно же. Вино, еда, шелка, отсутствие ежедневных истязаний - многие из них начинали видеть во мне спасительницу. Проклятые дуры! Лишь единицам из них неприятно находиться здесь. Некоторых из них он отдавал скрепя сердце. И посмеивался, говорил, что я всегда могу вернуть ему любую в обмен на решение денежных проблем моего заведения. Но я всегда отказывалась наотрез. Так они хоть принесут золото, а не подохнут в подвале. Это слишком легко для них.";
			link.l1 = "Какая жалость, что не все почувствовали себя униженными, сменив застенки похлеще Святой Инквизиции на золотую клетку...";
			link.l1.go = "PZ_ChangShin21";
		break;
		
		case "PZ_ChangShin21":
			dialog.text = "Осуждаешь? Я хотела не просто выжить, а заполучить своё место под солнцем - плевать, какой ценой. Пусть и неосознанно, Левассер был благодарен мне. Я уже больше не была рабыней. Но и отпустить меня он не мог. Я всё ещё была вынуждена работать на него и помогать его прихвостням. Особенно размазне в виде его тощего племянника, который пускал на меня слюни каждый раз, как видел. Но не решался ни напасть, ни всерьёз заговорить. Отвратительно. Знаешь, хоть он и называл меня разочарованием, но от меня было больше толку, чем от Тибо и Мартэна вместе взятых. Поэтому я довольно часто сопровождала их по его приказу, как тогда, в Порт-о-Пренсе.";
			link.l1 = "Это всё очень многое объясняет...";
			link.l1.go = "PZ_ChangShin22";
		break;
		
		case "PZ_ChangShin22":
			dialog.text = "Верно. Послушай. Я не пытала твою возлюбленную. Как не пытала ни одну девушку вот этими вот руками, пусть и давала иногда советы Левассеру. Но, раз уж мы так разоткровенничались...";
			link.l1 = "Ну-ка...";
			link.l1.go = "PZ_ChangShin23";
		break;
		
		case "PZ_ChangShin23":
			dialog.text = "Как ты тоже, возможно, знаешь, Левассер иногда требует привезти ему определённую девушку, которую мельком видел в Тортуге, а потом она покидала остров. Или что кто-то делал ему сюрприз и привозил ему незнакомку, чтобы заслужить расположение, как это было со мной. Похищение твоей любимой было моей идеей.";
			link.l1 = "Что ты сказала?..";
			link.l1.go = "PZ_ChangShin24";
		break;
		
		case "PZ_ChangShin24":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Поначалу мы хотели схватить ту блондинку, что была с тобой раньше, но теперь она вне досягаемости. А, поскольку девушка уже ему была обещана с нашей стороны, мы взялись за твою рыженькую.";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "До меня дошли слухи о тебе и твоей прекрасной спутнице, что не отходит от тебя ни на шаг. Учитывая, что Левассер больше всего любит блондинок, мне даже не пришлось его уговаривать.";
			dialog.text = "Сотта, его шавка, должен был притащить к нему мулатку, жену Латтера. Но твоими стараниями всё провалилось. Левассер пришёл в ярость. Досталось всем - и Тибо с Мартэном, и даже мне. Уж не знаю, кто разозлил меня больше: он, потому что снова избил меня, или же ты, ставший тому причиной... "+ sStr +"";
			link.l1 = "Так это даже не из-за него, а из-за тебя с ней всё это случилось...";
			link.l1.go = "PZ_ChangShin25";
		break;
		
		case "PZ_ChangShin25":
			dialog.text = "Даже не надеюсь на твоё прощение и, более того, не нуждаюсь в нём. Захочешь крови - будет тебе кровь. И ты очень пожалеешь об этом. Но от понимания - не откажусь. Не помешает оно мне впервые за столько лет. Я просто делала всё, чтобы однажды вырваться из всего этого. У тебя есть ко мне какие-нибудь вопросы, Шарль де Мор?";
			if (!CheckAttribute(pchar, "questTemp.PZ_FlagShinInfo") && !CheckAttribute(pchar, "questTemp.PZ_FlagMarselinaInfo") && !CheckAttribute(pchar, "questTemp.PZ_FlagMartinInfo"))
			{
				link.l1 = "Но ты участвовала в её похищении. И ты знаешь, где Левассер развлекается со своими жертвами. Скажи мне, где это. И если непоправимого не случится - я хорошо подумаю над тем, чтобы не мстить тебе.";
				link.l1.go = "PZ_ChangShinDontKnow1";
			}
			else
			{
				link.l1 = "Ну что же, мне всё стало понятно. Думаю, что...";
				link.l1.go = "PZ_ChangShin26";
			}
		break;
		
		case "PZ_ChangShinDontKnow1":
			dialog.text = "Знаю - ведь я была там. И если у тебя сложилось впечатление, что я к нему взаимно и нездорово привязана - то крепко ошибаешься. Буду рада, если кто-то наконец насадит эту свинью на вертел.";
			link.l1 = "Времени мало, Чанг Шин. Где это?";
			link.l1.go = "PZ_ChangShinDontKnow2";
		break;
		
		case "PZ_ChangShinDontKnow2":
			dialog.text = "Знаешь местное подземелье под улицами города? Тебе туда. В одном из тупиков стоит большая винная бочка, рядом с ней начинается потайной проход в его комнату наслаждений, как он её иногда называет.";
			link.l1 = "Ну что же, мне всё стало понятно. Думаю, что...";
			link.l1.go = "PZ_ChangShin26";
		break;
		
		case "PZ_ChangShin26":
			if (CheckAttribute(pchar, "questTemp.PZ_FlagArhiv") && CheckAttribute(pchar, "questTemp.PZ_FlagShip")) StartInstantDialog("Longway", "PZ_Longway_SisterDialog6", "Quest\CompanionQuests\Longway.c");
			else
			{
				dialog.text = "Я рада, что тебе всё понятно. А теперь убирайся. Пусть мне и хотелось высказаться спустя столько лет, но при этом от осознания того, что ты знаешь все мои тайны, знаешь, что со мной делали - противно. Один твой вид теперь меня лишь сердит. Ах да, и Ту остаётся со мной.";
				link.l1 = "Это ещё почему?";
				link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet1";
			}
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet1":
			dialog.text = "Может, потому что я его семья? И потому что я вижу, какой он с тобой - забитая несчастная мямля, которой даже некогда доучить язык и начать нормально разговаривать. Хотя он говорил мне, что вы друзья. Оно и видно, как ты на него влияешь. А я из него хоть человека сделаю.";
			link.l1 = "А сама-то вся счастливая? Кого из него сделаешь ты? Жестокое, озлобленное существо, торгующее жизнями?";
			link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet2";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet2":
			StartInstantDialog("Longway", "PZ_Longway_SisterDialog_Ubezhdaet3", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet3":
			if (CheckAttribute(pchar, "questTemp.PZ_FlagArhiv") || CheckAttribute(pchar, "questTemp.PZ_FlagShip"))
			{
				dialog.text = "Господин капитан, пожалуйста, перестать. Просить, оставить сестра в покой. И... мой остаться с её.";
				link.l1 = "Ты... что? Лонгвэй... но почему? Неужели ты не видишь, какой она стала?";
				link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet4";
			}
			else
			{
				dialog.text = "А разве с ваш мой быть лучше? Вы измениться за всё это время. В худший сторона. Сначала ваш быть так вежлив, понимающ. Но затем стать груб, даже больше грубый, чем Роденбург. А когда мой нуждаться хороший корабль для поимка ван дер Винк, ваш дать мой какой-то корыто!";
				link.l1 = "Лонгвэй...";
				link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet8";
			}
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet4":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Мэри";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Элен";
			dialog.text = "Потому что мой однажды выйти в море и провести там столько время только ради того, чтобы найти и спасти сестра. И вот она здесь. Мой задача выполнен. А ещё... мой звать Чанг Ту. Лонгвэй - имя, что дать мне предатель ван Мерден, если ваш позабыть. А Чанг Ту - свободный человек. Долгий путь Чанг Ту наконец-то быть завершён.";
			link.l1 = "Она сделает из тебя такого же слугу, как когда-то Роденбург. И будет давить, потому что вы семья. А ещё... неужели ты так легко переметнёшься к той, из-за которой у меня и " + sStr + " было столько проблем?";
			link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet5";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet5":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Мэри";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Элен";
			dialog.text = "А прямо сейчас на Чанг Ту давить ваш. Прошу, отпустить. Мой очень устать. Вы неплохой человек, господин капитан - Небо быть тому свидетель. Но вы не семья для мой. В отличие от Шин. Если мой не остаться, получаться, что все эти годы пройти зазря. Теперь мой стать её путеводный звезда. И зажечь её погасший огонь - тёплый и согревающий, а не сжигающий всё, чего касаться.";
			if (CheckAttribute(pchar, "questTemp.PZ_LevasserPobezhden"))
			{
				link.l1 = "Хм, ты прав. Возможно, я сейчас и правда давлю. Что ж. Я всегда уважал тебя. Желаю тебе снова обрести долгожданную семью в лице твоей сестры. Но предупреждаю тебя. Не видать тебе с ней покоя.";
				link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet6";
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko") && !CheckAttribute(pchar, "questTemp.PZ_DevushkaMertva")) 
				{
					pchar.questTemp.PZ_LongwayHochetMira = true;
					link.l1.go = "PZ_Longway_SisterDialog_ReactiaDevushek";
				}
				
			}
			else
			{
				link.l1 = "Ты не можешь меня оставить сейчас! Мне ещё спасать " + sStr + " от Левассера! Хочешь, чтобы я отправился туда совсем один?! Помоги мне, Лонгвэй. И тогда я тебя отпущу. Обещаю тебе.";
				link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet6";
			}
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet6":
			if (CheckAttribute(pchar, "questTemp.PZ_LevasserPobezhden"))
			{
				dialog.text = "Мой справиться. Ваш мочь больше никогда не переживать за мой. Благодарить.";
				link.l1 = "Кажется, твоя сестра злится, что мы решили разойтись мирным путём.";
			}
			else
			{
				dialog.text = "Ваш не пропасть, господин капитан. Ваш быть самый толковый человек, что мой когда-либо видеть. Ваш легко справиться с этот червь, что привыкнуть лишь истязать женщина. Просить, не заставлять. Мой нужно о стольком поговорить с сестра! И... мой звать Чанг Ту.";
				link.l1 = "Ты же понимаешь, что оставляя меня сейчас, ты, по сути, предаёшь меня?! Особенно, оставшись с ней - женщиной, из-за которой это всё началось!";
			}
			link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet7";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet7":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Мэри";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Элен";
			if (CheckAttribute(pchar, "questTemp.PZ_LevasserPobezhden"))
			{
				dialog.text = "Не бояться, господин капитан. Старший брат и мужчина здесь быть я, хоть она и говорит про мой не очень уважительно. Ваш мочь идти. Мой не позволить её убить ваш. Прощать.";
				link.l1 = "Я и не боюсь. Ну что же, прощай... Чанг Ту.";
				DeleteAttribute(pchar, "questTemp.PZ_LongwayRyadom");
				AddDialogExitQuest("PZ_BrothelTeleportVZal");	//Мирно разошлись
			}
			else
			{
				dialog.text = "Мой всё сказать. Прощаться, господин капитан. И успех ваш. Чанг Ту всегда быть свободный человек. Не забывать об это.";
				link.l1 = "И это после того, как я всё бросил и помогал тебе в поисках?! После того, что сейчас творят с " + sStr + "?! Ты предатель, Чанг Ту. Но ты прав. Прощайся. Прощайтесь с жизнью, вы оба, чёртовы желтокожие змеи...";
				link.l1.go = "exit";
				LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
				AddDialogExitQuest("MainHeroFightModeOn");
				AddDialogExitQuest("PZ_ChangShinAndLongwayFightMe");
			}
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet8":
			dialog.text = "Мой звать Чанг Ту. Лонгвэй умереть. Ваш его убить. Больше вы не господин капитан для мой. И сейчас умереть ваш. А я и мой семья наконец-то обрести спокойный жизнь, и наш звезда снова ярко воссиять на ночной небо.";
			if (IsCharacterPerkOn(pchar, "Trustworthy") && GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 85)
			{
				link.l1 = "(Вызывающий доверие) (Харизма) Лонгвэй... Чанг Ту. Остановись. Я не был идеальным капитаном. Но ты правда так сильно хочешь убить меня из-за этого? После всего, через что мы прошли? Сначала Роденбург, теперь поиски твоей сестры.";
				link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet9";
				notification("Вызывающий доверие", "Trustworthy");
				notification("Проверка пройдена", SKILL_LEADERSHIP);
			}
			else
			{
				link.l1 = "Лонгвэй, я твой капитан. Не брат, не сын. Не нянечка. Я отдаю приказы, а не размышляю, а не нагрубил ли я тебе нечаянно. Ты предъявляешь мне претензию, будто мы старые супруги, ей-Богу...";
				link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet15";
				if (!IsCharacterPerkOn(pchar, "Trustworthy")) notification("Не открыта способность", "Trustworthy");
				if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 85) notification("Недостаточно развит навык (85)", SKILL_LEADERSHIP);
			}
			link.l2 = "Да-а-а. Теперь я вижу это. Ты такой же гнилой самовлюблённый эгоист, которому плевать на всех остальных... Лонгвэй. Как и твоя сестрёнка. Как вы похожи! Сегодня будет жить моя семья - ваша этого больше не заслуживает. Отправляйтесь к чёрту!";
			link.l2.go = "PZ_Longway_SisterDialog_Ubezhdaet8_1";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet8_1":
			DialogExit();
			LAi_SetPlayerType(pchar);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetFightMode(pchar, true);
			DoQuestCheckDelay("PZ_ChangShinAndLongwayFightMe", 0.5);
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet9":
			dialog.text = "Если выбирать между ваш и мой семья - я всё же выбрать семья, пусть это быть и непростой выбор.";
			link.l1 = "Семья, которая и пальцем не пошевелила, пока ты её искал столько лет? А ведь возможность потом появилась! А я тем временем бросил всё, чтобы помочь тебе. Мы бы сейчас не оказались здесь без моей самоотверженной помощи. Чёрт, да я тебе больше семья, чем она, друг мой!";
			link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet10";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet10":
			dialog.text = "Ваш быть прав. Как всегда быть прав. Ваш простить мой... господин капитан?";
			link.l1 = "Ну конечно! В чём-то прав и ты - я тоже был хорош. Так что мы квиты. Как бы ты хотел, чтобы я к тебе по итогу к тебе обращался? Лонгвэй? Чанг Ту?";
			link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet11";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet11":
			dialog.text = "Пусть быть Лонгвэй. Мой уже привык, что ваш так обращаться.";
			link.l1 = "Тогда забудем обо всех разногласиях, и добро пожаловать на борт снова, Лонгвэй.";
			link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet12";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet12":
			StartInstantDialog("PZ_ChangShin", "PZ_Longway_SisterDialog_Ubezhdaet13", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet13":
			locCameraFromToPos(2.17, 2.32, 0.55, true, -0.92, -0.37, -4.09);
			dialog.text = "Ту! Что ты такое говоришь?! Почему ты остановился?! Убей его! Ты навсегда останешься для него батраком! Твоя семья - я и только я!";
			link.l1 = "Как же она злится, верно, Лонгвэй? Ну а ты. Ты перестала быть его семьёй, когда отказалась увидеться с ним, узнав, что он на Архипелаге. И когда чуть не заставила его накинуться на капитана и старого друга заодно в моём лице. Так что замолчи. Мы уходим.";
			link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet14";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet14":
			dialog.text = "Видимо, из него так и не вытравить это рабское мышление. Значит, его уже не спасти. Тогда я убью вас сама.";
			link.l1 = "Кого здесь не спасти - так это тебя. Я уже почти был готов простить тебе всё, но как хочешь. Так даже лучше. Думаю, даже Лонгвэй уже понял, что ты за змея. И не слишком будет горевать по тебе.";
			link.l1.go = "exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_ChangShinFightWithLongway");
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet15":
			dialog.text = "Шутки сейчас быть неуместны! Вы скрывать ваш страх и неудача за ними! Что лишь крепче убедить мой. Защищаться, господин де Мор! Ибо Чанг Ту не собираться щадить ваш.";
			link.l1 = "Мне жаль, что всё так кончилось. Но если ты так хочешь - так тому и быть. В таком случае ты тоже от меня не дождёшься пощады.";
			link.l1.go = "exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_ChangShinAndLongwayFightMe");
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaDevushek":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) StartInstantDialog("Mary", "PZ_Longway_SisterDialog_ReactiaMary", "Quest\CompanionQuests\Longway.c");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) StartInstantDialog("Helena", "PZ_Longway_SisterDialog_ReactiaHelena", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaHelena":
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayHochetMira"))
			{
				dialog.text = "Шарль, послушай...";
				link.l1 = "Элен?..";
			}
			else
			{
				dialog.text = "Шарль, Лонгвэй, остановитесь...";
				link.l1 = "Элен, лучше отойди за меня. Мне так будет спокойнее, когда они набросятся на нас...";
			}
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaHelena2";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaHelena2":
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayHochetMira"))
			{
				dialog.text = "Я очень устала, я едва стою на ногах. Я хочу отсюда уйти. Просто уйти. Не будем же мы силком тащить Лонгвэя обратно на корабль, раз он так не хочет? Я буду твоим штурманом и старпомом, мой капитан, сразу же, как только восстановлюсь. Надеюсь, самым любимым. К тому же, в чём-то он и прав - не мы его семья. А она. Какой бы она не была.";
				link.l1 = "Но что насчёт неё? Из-за неё тебя пытали, это всё была её идея. И это она тебя похитила.";
			}
			else
			{
				dialog.text = "Но ведь ещё не набросились, верно? Давай мы сейчас просто уйдём, и всё. Раз он такого мнения о нас после всего, что мы для него сделали, то не стоит его переубеждать. Ведь поступки - громче слов. Хочется ему - пускай остаётся с этой... своей сестрой.";
				link.l1 = "Элен, ты же так пострадала из-за неё...";
			}
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaHelena3";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaHelena3":
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayHochetMira"))
			{
				dialog.text = "Оставь эту демоницу наедине с её демонами. Они всё равно сожрут её душу в скором времени. А наши заслужили хороший отдых. Пойдём.";
				link.l1 = "Да. Пожалуй, так и поступим. Идём, мой ангел. Ну а ты... Лонгвэй или Чанг Ту - прощай.";
			}
			else
			{
				dialog.text = "Но не умерла же. Да и худшего не случилось. Я здесь, перед тобой, и это главное. Как и то, что Левассер мёртв. Без него она ноль без палки. Её притон терпит убытки и скоро окончательно пойдёт ко дну. А они вместе с ним. Идём, мой капитан. Нам больше нечего здесь делать.";
				link.l1 = "Не стану спорить, Элен.";
			}
			AddDialogExitQuest("PZ_BrothelTeleportVZal");		//Мирно разошлись
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaHelena4":
			StartInstantDialog("Helena", "PZ_Longway_SisterDialog_ReactiaHelena5", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaHelena5":
			dialog.text = "Куда ваш собраться, почему?..";
			link.l1 = "Что, удивлён, что мы не горим желанием выпустить вам с сестрой кишки, Лонгвэй? Вот она - разница между нами. И ты ещё считаешь меня плохим человеком... Но ладно, послушай. Если ты желаешь убить меня, это значит, что тебе придётся убить и Элен. Раненую. Пострадавшую. Ты правда хочешь убить Элен?..";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaHelena6";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaHelena6":
			dialog.text = "Хм-м-м...";
			link.l1 = "Я вижу сомнение в твоих глазах, пусть ты и накопил немало обид на меня. Но давай оба возьмём пример с Элен? На нашем судне не было человека более доброго и прощающего, чем она. Мы уходим. И если в тебе осталась хоть капля доброты или хотя бы ума - ты не будешь нам препятствовать.";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaHelena7";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaHelena7":
			dialog.text = "Хм, ладно, быть так. Прощать. Но больше вы не господин капитан для мой.";
			link.l1 = "Как-нибудь переживу. Желаю всего хорошего вам с сестрой. Несмотря на то, что она сделала. Прощай, Лонгвэй.";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_BrothelTeleportVZal");		//Мирно разошлись
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary":
			dialog.text = "Давай, Шарль, настала пора подавить этот бунт на корабле...";
			link.l1 = "Видит Бог, я этого не хотел... и не хочу.";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaMary2";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary2":
			dialog.text = "Не хочешь?! Шарль, послушай. Ты столько для него сделал, а что получил взамен? Предательство и гадкие слова, да! И ты что, собрался ему это простить?";
			link.l1 = "Я не хочу проливать кровь Лонгвэя... Я-то не забыл, что когда-то мы были друзьями.";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaMary3";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary3":
			dialog.text = "Упаси Господь от таких друзей - они хуже врагов, да! Шарль, посмотри на меня. Посмотри на то, что случилось со мной - по вине его сестрицы, которая насмехалась надо мной, оскорбляла и унижала по пути на этот треклятый остров!";
			link.l1 = "Мэри, я понимаю: ты сейчас очень и очень зла...";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaMary4";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary4":
			dialog.text = "О нет, Шарль, я не зла, нет... Я в ярости! И не только из-за того, что тут наговорил тебе этот жалкий недомерок! Посмотри на меня ещё раз, Шарль - и представь, сколько ещё девушек через это пройдёт, если мы не положим этому конец. Здесь и сейчас.";
			link.l1 = "Они больше никому не причинят зла. Левассер мёртв.";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaMary5";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary5":
			dialog.text = "Шарль, ты хорошо слушал ту ересь, что она несла? Она ответственна за то, что творилось в том подвале в том подвале в ничуть не меньшей степени, чем этот вонючий боров. А теперь взгляни на Лонгвэя... или как там его теперь зовут. Как быстро ей удалось переманить его на свою сторону, да! Кто знает, какие ещё больные идеи она вложит в голову этого изменника? Думаешь, этой дьяволице составит большого труда толкнуть его на путь Левассера? Не думай о том, какой он сейчас, Шарль. Подумай о том, в какое чудовище он может превратиться через год... или даже месяц. Ты ведь знаешь, что я права, да!";
			link.l1 = "Как бы мне не было жаль, но возразить тебе мне нечего, Мэри...";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaMary6";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary6":
			StartInstantDialog("PZ_ChangShin", "PZ_Longway_SisterDialog_ReactiaMary7", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary7":
			dialog.text = "Ха-ха-ха! Очаровательно, какое представление. Давно я так искренне не смеялась. А у неё кишка не тонка, скажу я тебе.";
			link.l1 = "Закрой пасть, ты, змея.";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaMary8";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary8":
			dialog.text = "А это забавно, не находишь, де Мор? Я и сама на самом деле бы хотела, чтобы Ту расправился с вами. А тут твоя женщина как раз жаждет крови. Очень хорошо. Я тоже не буду стоять в стороне - не зря же я столько времени тренировалась с Левассером и не только. Посмотрим, чей дуэт выйдет победителем.";
			link.l1 = "У тебя был не слишком хороший учитель. А ещё вы разозлили Мэри. Вам конец. Даже если бы меня здесь не было.";
			link.l1.go = "exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_ChangShinAndLongwayFightMe");
		break;
		
		case "PZ_Longway_SisterDialog6":
			dialog.text = "Мой тоже всё быть понятно. Мочь мой ещё раз поговорить с сестра, господин капитан? Недолго.";
			link.l1 = "Конечно, Лонгвэй. Только если и правда недолго - мы тут явно не на весь день.";
			link.l1.go = "PZ_Longway_SisterDialog7";
		break;
		
		case "PZ_Longway_SisterDialog7":
			dialog.text = "Мой быстро.";
			link.l1 = "Хорошо.";
			link.l1.go = "PZ_Longway_SisterDialog7_1";
		break;
		
		case "PZ_ChangShin26":
			StartInstantDialog("СhangShin", "PZ_Longway_SisterDialog7_1", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Longway_SisterDialog7_1":
			locCameraFromToPos(0.65, 2.59, -3.06, true, 0.23, 0.34, -5.21);
			
			sld = characterFromId("Longway");
			ChangeCharacterAddressGroup(sld, "Tortuga_brothelElite_room2", "goto", "goto8");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, characterFromId("PZ_ChangShin"));
			
			sld = characterFromId("PZ_ChangShin");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, characterFromId("Longway"));
			
			dialog.text = "И что же ты хотел мне сказать, брат мой?";
			link.l1 = "Что мой быть очень разочарован в твой, Шин.";
			link.l1.go = "PZ_Longway_SisterDialog8";
		break;
		
		case "PZ_Longway_SisterDialog8":
			dialog.text = "(На китайском) Почему ты не говоришь на нашем языке, раз уж ты хотел поговорить ещё раз, Ту? Ты его стесняешься? На твоём месте я бы стеснялась скорее твоего акцента.";
			link.l1 = "Нет. У мой нет секрет от господин капитан. Больше нет.";
			link.l1.go = "PZ_Longway_SisterDialog9";
		break;
		
		case "PZ_Longway_SisterDialog9":
			dialog.text = "(Снова на французском) Сначала Роденбург, теперь де Мор. Вечно тебе нужен 'господин'. Ты так ничего и не добился здесь за десяток с лишним лет. Даже ни один из их языков не смог выучить толком. А ведь они гораздо проще нашего! Если кто из нас и разочарование, так это ты.";
			link.l1 = "Зато мой не торговать женщины. И не участвовать в их похищение и истязание.";
			link.l1.go = "PZ_Longway_SisterDialog10";
		break;
		
		case "PZ_Longway_SisterDialog10":
			dialog.text = "Ты серьёзно? Мне перечислить, чем ты занимался для Роденбурга? То, что делала я, будет просто детской шалостью в сравнении с этим.";
			link.l1 = "У мой быть цель. Искать твой. Но твой даже не захотеть увидеться. И вот мой найти твой. Но увидеть чудовище, а не тёплый путеводный звезда, когда-то светивший на мой путь.";
			link.l1.go = "PZ_Longway_SisterDialog11";
		break;
		
		case "PZ_Longway_SisterDialog11":
			dialog.text = "Чудовище? Что ж, может, ты и прав. Я больше не та весёлая девочка, что ты знал. Останься я ею - и жизнь бы меня прожевала и выплюнула. Пришлось отрастить зубы самой. Моя звезда уже давно погасла. Но я всё ещё твоя сестра, Ту.";
			link.l1 = "Нет. Твой больше не мой сестра.";
			link.l1.go = "PZ_Longway_SisterDialog12";
		break;
		
		case "PZ_Longway_SisterDialog12":
			dialog.text = "Так легко отказываешься от меня после стольких лет поисков? Хех... А кто знает, может, я бы и осталась прежней, если бы ты в тот день успел вернуться домой и убил Ферментелуша?";
			link.l1 = "Твой прав. Частично это и мой вина. Из-за мой это случилось. Мой это и закончить. И избавить твой от мучение. Закончить этот несчастный существование.";
			link.l1.go = "PZ_Longway_SisterDialog13";
		break;
		
		case "PZ_Longway_SisterDialog13":
			dialog.text = "Ты и правда убьёшь родную сестру, Чанг Ту? Не то чтобы тебе удастся, но сам факт. Надо же...";
			link.l1 = "Твой быть кто угодно, но не мой сестра. Видимо, Шин умереть десять лет назад. А сегодня окончательно умереть Чанг Ту. Отныне и навсегда мой звать... Лонгвэй.";
			link.l1.go = "Exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_ChangShinFightWithLongway");
		break;
		
		case "PZ_Longway_FlagMartinInfo_1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Мэри";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Элен";
			dialog.text = "Сначала мы спасти Чанг Шин.";
			link.l1 = "Что?! Ты, кажется, не понимаешь, друг мой. Твоей сестре ничего не грозит. А вот " + sStr + " - совсем напротив. И надо ли мне тебе напоминать, что Чанг Шин виновата в этом не меньше Мартэна и Тибо?";
			link.l1.go = "PZ_Longway_FlagMartinInfo_2";
		break;
		
		case "PZ_Longway_FlagMartinInfo_2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Мэри";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Элен";
			dialog.text = "Это не быть так! Она...";
			link.l1 = "Ты хоть представляешь, что Левассер может сделать с " + sStr + ", пока мы тут с тобой спорим?";
			link.l1.go = "PZ_Longway_FlagMartinInfo_3";
		break;
		
		case "PZ_Longway_FlagMartinInfo_3":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Мэри";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Элен";
			dialog.text = "Но Чанг Шин остаться последнее, что есть у Лонгвэй! Его семья! У ваш-то всё ещё быть семья, господин капитан...";
			link.l1 = + sStr + " мне может и не жена, но дорога мне ничуть не меньше отца или брата.";
			link.l1.go = "PZ_Longway_FlagMartinInfo_4";
		break;
		
		case "PZ_Longway_FlagMartinInfo_4":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Мэри";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Элен";
			dialog.text = "Лонгвэй всё сказать. Чанг Шин быть его последний путеводный звезда. К тому же, ваш быть обязан мой за то, что я добыть признание от Робер Мартэн.";
			if (CheckAttribute(pchar, "questTemp.PZ_FlagArhiv") && CheckAttribute(pchar, "questTemp.PZ_FlagShip"))
			{
				link.l1 = "Мы пойдём за твоей сестрой, клянусь тебе. Но за всё это время Левассер и пальцем её не тронул. " + sStr + " в куда большей опасности чем Чанг Шин. Так что помоги мне спасти её, и тогда я действительно буду обязан тебе по гроб жизни...";
				link.l1.go = "PZ_Longway_FlagMartinInfo_VD1";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.PZ_FlagArhiv") || CheckAttribute(pchar, "questTemp.PZ_FlagShip"))
				{
					if (IsCharacterPerkOn(pchar, "Trustworthy") && GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 85)
					{
						link.l1 = "(Вызывающий доверие) (Харизма) Мы пойдём за твоей сестрой, клянусь тебе. Но за всё это время Левассер и пальцем её не тронул. " + sStr + " в куда большей опасности чем Чанг Шин. Так что помоги мне спасти её, и тогда я действительно буду обязан тебе по гроб жизни...";
						link.l1.go = "PZ_Longway_FlagMartinInfo_VD1";
						notification("Вызывающий доверие", "Trustworthy");
						notification("Проверка пройдена", SKILL_LEADERSHIP);
					}
					else
					{
						link.l1 = "Лонгвэй! " + sStr + " сейчас в руках изверга, который пытает её или, не приведи Господь, делает ещё что похуже! А твоя сестра и так хорошо устроилась! Думаешь, Левассер позволил бы ей владеть дорогим заведением, обращайся он с ней, как с теми бедняжками в своём подземелье?!";
						link.l1.go = "PZ_Longway_FlagMartinInfo_netVD1";
						if (!IsCharacterPerkOn(pchar, "Trustworthy")) notification("Не открыта способность", "Trustworthy");
						if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 85) notification("Недостаточно развит навык (85)", SKILL_LEADERSHIP);
					}
				}
			}
			link.l2 = "Не стану тратить время на пустые споры. У каждого из нас своя правда. Разделимся ещё раз. И да поможет мне мой Бог, а тебе - твой.";
			link.l2.go = "PZ_Longway_FlagMartinInfo_Razdelimsya";
			link.l3 = "Ты прав, я обязан тебе. Хорошо, будь по-твоему. Без тебя я могу и не справиться с Левассером и его людьми. Но, если за то время, что мы будем разбираться с твоей сестрой, с " + sStr + " что-нибудь...";
			link.l3.go = "PZ_Longway_FlagMartinInfo_IdemKSestreLongweya";
		break;
		
		case "PZ_Longway_FlagMartinInfo_Razdelimsya":
			dialog.text = "Благодарить за понимание, господин капитан. Удача вам!";
			link.l1 = "И тебе, Лонгвэй.";
			link.l1.go = "PZ_Longway_FlagMartinInfo_SharleOdinVPodzemelie";
		break;
		
		case "PZ_Longway_FlagMartinInfo_IdemKSestreLongweya":
			dialog.text = "Не тратить время впустую на бессмысленные угрозы, господин капитан. Надо поспешить. И тогда мы везде успеть.";
			link.l1 = "Твои бы слова да Богу в уши. Вперёд!";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TogetherLongwayGo");
		break;
		
		case "PZ_Longway_FlagMartinInfo_netVD1":
			dialog.text = "'Хорошо устроилась', говорить?! Лонгвэй не ударить ваш только лишь из-за очень большой уважение к вам, господин капитан. Мой идти спасать сестра прямо сейчас, нравиться это ваш, или нет.";
			link.l1 = "Что ж... Я не стану более тратить время на споры с тобой, Лонгвэй. В конце концов, у каждого из нас есть то, что дороже всего на свете именно ему.";
			link.l1.go = "PZ_Longway_FlagMartinInfo_SharleOdinVPodzemelie";
		break;
		
		case "PZ_Longway_FlagMartinInfo_SharleOdinVPodzemelie":
			pchar.questTemp.PZ_DevushkaRanena_Legko = true;
			LAi_LocationDisableOfficersGen("Tortuga_Cave", true);
			DoQuestReloadToLocation("Tortuga_Cave", "reload", "reload2", "PZ_Etap6TortugaPodzemelie");
		break;
		
		case "PZ_Longway_FlagMartinInfo_VD1":
			dialog.text = "Хм-м-м, хорошо, господин капитан. Но тогда наш должен поторопиться.";
			link.l1 = "Верно. Поспешим. И спасибо, Лонгвэй.";
			link.l1.go = "PZ_Longway_FlagMartinInfo_VD2";
		break;
		
		case "PZ_Longway_FlagMartinInfo_VD2":
			pchar.questTemp.PZ_LongwayRyadom = true;
			pchar.questTemp.PZ_DevushkaRanena_Legko = true;
			LAi_LocationDisableOfficersGen("Tortuga_Cave", true);
			DoQuestReloadToLocation("Tortuga_Cave", "reload", "reload2", "PZ_Etap6TortugaPodzemelie");
		break;
		
		case "PZ_TortureRoom_Levasser_1":
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
			{
				dialog.text = "Ну кого там ещё принесло... Твою мать. Шарль де Мор и его узкоглазая псина.";
				link.l1 = "Псина здесь только одна. Хочешь увидеть - в зеркало посмотри, сволочь гугенотская. Ну или на своего племянничка. Правда, он скорее на облезлую крысу тянет.";
				link.l1.go = "PZ_TortureRoom_Levasser_2";
			}
			else
			{
				dialog.text = "Я же велел меня не беспокоить! А-а, Шарль де Мор, хе-хе. Вот же неугомонный ублюдок.";
				link.l1 = "Уж какой есть. А теперь захлопни пасть и...";
				link.l1.go = "PZ_TortureRoom_Levasser_1_1";
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Sredne") || CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Tyazhelo") || CheckAttribute(pchar, "questTemp.PZ_Etap6_Opozdal")) Achievment_Set("ach_CL_130");
			}
			locCameraSleep(true);
			sld = CharacterFromID("Tibo");
			ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto2");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, CharacterFromID("Levasser"));
		break;
		
		case "PZ_TortureRoom_Levasser_1_1":
			dialog.text = "Ты не у себя на корабле, щенок! На этом острове распоряжается только один человек - я!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_Etap6TortugaPytochnaya9");
		break;
		
		case "PZ_TortureRoom_Levasser_2":
			StartInstantDialog("Tibo", "PZ_TortureRoom_Levasser_3", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_3":
			dialog.text = "Да как ты смеешь, мразь!";
			link.l1 = "";
			link.l1.go = "PZ_TortureRoom_Levasser_4";
			sld = CharacterFromID("Tibo");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
		break;
		
		case "PZ_TortureRoom_Levasser_4":
			StartInstantDialog("Levasser", "PZ_TortureRoom_Levasser_5", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_5":
			dialog.text = "Тише, тише, племянник! Сейчас мы преподадим месье де Мору урок хороших манер.";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_Etap6TortugaPytochnaya9");
			sld = CharacterFromID("Tibo");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, CharacterFromID("Levasser"));
		break;
		
		case "PZ_TortureRoom_Levasser_6":
			if (!CheckAttribute(pchar, "questTemp.PZ_Etap6_Opozdal"))
			{
				dialog.text = "Я тебе что, разрешал визжать?!";
			}
			else
			{
				dialog.text = "И куда только делся весь запал, крошка, а? Ах, кажется, понимаю...";
			}
			link.l1 = "Оставь её, подонок!";
			link.l1.go = "PZ_TortureRoom_Levasser_7";
			LAi_SetActorType(npchar);
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) LAi_ActorTurnToCharacter(npchar, CharacterFromID("Mary"));
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) LAi_ActorTurnToCharacter(npchar, CharacterFromID("Helena"));
		break;
		
		case "PZ_TortureRoom_Levasser_7":
			dialog.text = "Хе-хе-хе... Можешь кричать, оскорблять меня, но я вижу, как ты дрожишь - словно лист на ветру. Вижу страх в твоих глазах. У вас с Анри это общее. Не в обиду, племянник.";
			link.l1 = "Ты прав, это страх. Но отнюдь не перед тобой, тварь.";
			link.l1.go = "PZ_TortureRoom_Levasser_7_1";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
		break;
		
		case "PZ_TortureRoom_Levasser_7_1":
			dialog.text = "Разумеется, разумеется. Я уже слышал это - что ты никого не боишься, де Мор. От неё. 'Шарль придёт, Шарль спасёт... Шарль то, Шарль сё...'. Ну вот Шарль и пришёл. У Шарля место в первом ряду. Анри, помоги нашему гостю поудобнее устроиться...";
			link.l1 = "";
			link.l1.go = "PZ_TortureRoom_Levasser_8";
		break;
		
		case "PZ_TortureRoom_Levasser_8":
			StartInstantDialog("Tibo", "PZ_TortureRoom_Levasser_9", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_9":
			if (CheckAttribute(pchar, "questTemp.PZ_Etap6_Opozdal"))
			{
				dialog.text = "Похоже, в том уже нет нужды, дядюшка. Боюсь, ты малость перестарался...";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
				{
					dialog.text = "Дядюшка, боюсь, в этом деле мне понадобится твоя помощь...";
				}
				else
				{
					dialog.text = "Мне прикончить его, дядюшка, или пусть посмотрит?";
				}
			}
			link.l1 = "";
			link.l1.go = "PZ_TortureRoom_Levasser_10";
			LAi_SetActorType(npchar);
			//LAi_ActorTurnToCharacter(npchar, CharacterFromID("Levasser"));
			LAi_ActorTurnToLocator(npchar, "goto", "goto8");
			locCameraFromToPos(-15.67, 2.57, -1.23, true, -17.49, 1.42, -3.26);
		break;
		
		case "PZ_TortureRoom_Levasser_10":
			StartInstantDialog("Levasser", "PZ_TortureRoom_Levasser_11", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_11":
			if (CheckAttribute(pchar, "questTemp.PZ_Etap6_Opozdal"))
			{
				dialog.text = "Это не я перестарался, это месье Сопляк долго до нас добирался. Похоже, спектакль-то... окончен, ха-ха-ха!!!";
				link.l1 = "Господи, нет...";
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_TortureRoom_Levasser_DevushkaMertva");
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
				{
					dialog.text = "Я так и думал. И как только ты дожил до своих лет? К тебе, де Мор, кстати, тот же вопрос.";
					link.l1 = "Ты не представляешь, сколько вопросов у меня к тебе, мясник!";
				}
				else
				{
					dialog.text = "Хотел бы я, чтобы у нашего маленького представления был зритель... Но, думаю, месье Упрямец не доставит нам такого удовольствия.";
					link.l1 = "Доставлю удовольствие я лишь себе - тем, что выпущу тебе кишки, мясник!";
				}
				link.l1.go = "PZ_TortureRoom_Levasser_14";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
			{
				locCameraFromToPos(-16.74, 2.58, -0.51, true, -13.13, -0.72, 2.49);
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Sredne"))
			{
				locCameraFromToPos(-18.38, 1.77, 2.73, true, -20.53, 0.01, 0.32);
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Tyazhelo"))
			{
				locCameraFromToPos(-16.97, 2.09, 3.98, true, -20.02, -0.17, 2.28);
			}
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("Tibo"));
		break;
		
		case "PZ_TortureRoom_Levasser_12":
			dialog.text = "Ну иди, забирай! Ха-ха-ха!";
			link.l1 = "Скоты, вы пожалеете о том, что появились на свет!";
			link.l1.go = "PZ_TortureRoom_Levasser_13";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
		break;
		
		case "PZ_TortureRoom_Levasser_13":
			DialogExit();
			EndQuestMovie();
			locCameraSleep(false);
			DeleteAttribute(pchar, "GenQuest.BlockDialogCamera");
			LAi_SetPlayerType(pchar);
			locCameraTarget(PChar);
			locCameraFollow();
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
			{
				sld = CharacterFromID("Longway");
				ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto4");
				Return_LongwayOfficer();
				PlaySound("VOICE\Russian\hambit\Longway-02.wav");
			}
			LAi_SetFightMode(pchar, true);
			sld = CharacterFromID("Levasser");
			LAi_group_MoveCharacter(sld, "EnemyFight");
			sld = CharacterFromID("Tibo");
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "PZ_TortureRoom_Levasser_DevushkaMertva5");
		break;
		
		case "PZ_TortureRoom_Levasser_14":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Мясник? Думаю, я скорее художник, живописец - ты просто попробуй воспринять это как искусство... Погляди-ка сюда\nТебе нравится моя работа? Воистину, один из моих шедевров. Больше всего люблю блондинок, но ей... ей я простил цвет её волос. Но не только лишь они рыжие словно огонь! Она сама была словно пламя, и я чуть не обжёгся о него. Дралась, кусалась, рычала, как зверь! Я аж вспомнил одну краснокожую дикарку, с которой мне было, пусть и недолго, но чертовски весело!..";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Мясник? Думаю, я скорее художник, живописец - ты просто попробуй воспринять это как искусство... Погляди-ка сюда\nЯ ещё с ней не закончил - работы непочатый край. Она не только прекрасна, но и тверда, как скала, и холодна, как лёд. Мне пришлось даже попотеть, чтобы заставить её кричать. До последнего терпела, лишь бы не доставить мне удовольствия послушать её голосок.";
			}
			link.l1 = "Освободи её немедленно, выродок.";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_Etap6TortugaPytochnaya13");
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
		break;
		
		case "PZ_TortureRoom_Levasser_15":
			dialog.text = "Куда собрался? Она теперь моя собственность. Как и всё вокруг - этот город, эта крепость... Сама Тортуга такой, какой ты её знаешь - это я. И вам с Пуанси, этим старым вонючим индюком, этого не изменить.";
			link.l1 = "Левассер, ты...";
			link.l1.go = "PZ_TortureRoom_Levasser_16";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
		break;
		
		case "PZ_TortureRoom_Levasser_16":
			dialog.text = "Для тебя - сеньор де Рене де Буадуфле де Летр.";
			link.l1 = "Плевать я хотел. Доставай свою железяку и покажи, чего ты стоишь в бою - с мужчиной, а не девушкой.";
			link.l1.go = "PZ_TortureRoom_Levasser_17";
		break;
		
		case "PZ_TortureRoom_Levasser_17":
			dialog.text = "Тоже мне, мужчина! Но ты прав, мне и самому надоела эта болтовня. Хочется поскорее вернуться к... моей даме. Но последний вопрос я тебе всё же задам. Как ты сюда попал? Кто выдал расположение этого места? О нём знают считанные единицы.";
			if (CheckAttribute(pchar, "questTemp.PZ_FlagMartinInfo"))
			{
				link.l1 = "Ваш общий друг, Робер, запел соловьём. Хотя, он скорее визжал, как свинья на скотобойне...";
				link.l1.go = "PZ_TortureRoom_Levasser_FlagMartinInfo_1";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_FlagMarselinaInfo"))
			{
				link.l2 = "Может, это лучше останется для тебя тайной? Боюсь ранить твоё самолюбие, сеньор де Рене и так далее.";
				link.l2.go = "PZ_TortureRoom_Levasser_FlagMarselinaInfo_1";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_FlagShinInfo"))
			{
				link.l3 = "Одна из твоих жертв, Левассер.";
				link.l3.go = "PZ_TortureRoom_Levasser_FlagShinInfo_1";
			}
		break;
		
		case "PZ_TortureRoom_Levasser_FlagShinInfo_1":
			dialog.text = "Лжёшь, негодяй! Никто не покидал этих стен!";
			link.l1 = "Напряги память, ну же. Одна такая всё же была. Чанг Шин.";
			link.l1.go = "PZ_TortureRoom_Levasser_FlagShinInfo_2";
		break;
		
		case "PZ_TortureRoom_Levasser_FlagShinInfo_2":
			dialog.text = "Не может быть. Только не она. Некоторые мои задумки были порождены этой дьяволицей. О-о, мы многому научили друг друга, хе-хе. Неужели она решила очистить совесть? Сомневаюсь. Ведь я вытравил это из неё давным-давно!";
			link.l1 = "А теперь я вытравлю из тебя кровь. По капле. Или одним большим фонтаном.";
			link.l1.go = "PZ_TortureRoom_Levasser_Bitva";
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMartinInfo_1":
			dialog.text = "И после этого ты ещё меня мясником называешь, жалкий лицемер! Хе-хе... Но коль скоро он горит в Аду, то и бояться мне нечего.";
			link.l1 = "Он ждёт тебя не дождётся. И твоего подлеца племянника. Давайте не будем его разочаровывать.";
			link.l1.go = "PZ_TortureRoom_Levasser_Bitva";
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMarselinaInfo_1":
			dialog.text = "А может мне ранить эту куколку ещё чуток? Распороть ей брюхо или горло, и посмотреть, как она будет истекать кровью, пока ты будешь добираться до неё...";
			link.l1 = "Как скажешь, Левассер, как скажешь... Твоя жёнушка шлёт тебе привет. И вместе с ним - прощальный поклон.";
			link.l1.go = "PZ_TortureRoom_Levasser_FlagMarselinaInfo_2";
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMarselinaInfo_2":
			dialog.text = "ЧТО?! Кха-кха... Марселина... А-а-ать! Жалкая сучка, мерзавка, гнида!";
			link.l1 = "Какие эпитеты. В этом вы друг друга стоите. Только у неё с головой всё в порядке. На первый взгляд, по крайней мере.";
			link.l1.go = "PZ_TortureRoom_Levasser_FlagMarselinaInfo_3";
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMarselinaInfo_3":
			dialog.text = "Я насажу её куриную башку на пику. Но прежде... о-ох, прежде с этой потаскухой случится много, много всего... Я даже дам отдых моей новой игрушке. Или нет - я отдам её Анри. На время, разумеется.";
			link.l1 = "";
			link.l1.go = "PZ_TortureRoom_Levasser_FlagMarselinaInfo_4";
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMarselinaInfo_4":
			StartInstantDialog("Tibo", "PZ_TortureRoom_Levasser_FlagMarselinaInfo_5", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMarselinaInfo_5":
			dialog.text = "В самом деле? Спасибо, дядя!";
			link.l1 = "";
			link.l1.go = "PZ_TortureRoom_Levasser_FlagMarselinaInfo_6";
			CharacterTurnByChr(npchar, CharacterFromID("Levasser"));
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMarselinaInfo_6":
			StartInstantDialog("Levasser", "PZ_TortureRoom_Levasser_FlagMarselinaInfo_7", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMarselinaInfo_7":
			dialog.text = "Заслужи сперва - подсоби-ка мне, а потом...";
			link.l1 = "'Потом' для вас уже не будет, отморозки.";
			link.l1.go = "PZ_TortureRoom_Levasser_Bitva";
			CharacterTurnByChr(npchar, CharacterFromID("Tibo"));
		break;
		
		case "PZ_TortureRoom_Levasser_Bitva":
			DialogExit();
			EndQuestMovie();
			locCameraSleep(false);
			DeleteAttribute(pchar, "GenQuest.BlockDialogCamera");
			LAi_SetPlayerType(pchar);
			locCameraTarget(PChar);
			locCameraFollow();
			
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
			{
				sld = CharacterFromID("Longway");
				ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto4");
				Return_LongwayOfficer();
				PlaySound("VOICE\Russian\hambit\Longway-02.wav");
			}
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sld = CharacterFromID("Mary");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sld = CharacterFromID("Helena");
			LAi_SetImmortal(sld, true);
			
			LAi_SetFightMode(pchar, true);
			sld = CharacterFromID("Levasser");
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_SetCheckMinHP(sld, 1, true, "PZ_Etap6TortugaPytochnaya19");
			sld = CharacterFromID("Tibo");
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		break;
		
		case "PZ_TortureRoom_Longway_1":
			dialog.text = "Господин капитан... Лонгвэй приносит соболезнования. Наш сделать, что мочь.";
			link.l1 = "Не всё, совсем не всё.";
			link.l1.go = "PZ_TortureRoom_Longway_2";
		break;
		
		case "PZ_TortureRoom_Longway_2":
			dialog.text = "Лонгвэй собираться отправиться к Чанг Шин. Ваш с мой?";
			link.l1 = "О да-а, я с тобой, Лонгвэй. Ты только не забывай, что твоя сестрица приняла в этом кровавом представлении самое что ни на есть деятельное участие. И ей придётся очень постараться, чтобы я не отправил её вслед за этими выродками. И только попробуй мне помешать... А теперь пошли, настала пора со всем этим покончить.";
			link.l1.go = "PZ_TortureRoom_Longway_3";
		break;
		
		case "PZ_TortureRoom_Longway_3":
			DialogExit();
			Return_LongwayOfficer();
			chrDisableReloadToLocation = false;
		break;
		
		case "PZ_TortureRoom_Devushka_1":
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
				{
					dialog.text = "Шарль, я знала, знала, да! Знала, что ты придёшь. Ты ведь всегда приходишь, да!";
					link.l1 = "Не хотел бы я проверять это в четвёртый раз, Мэри... Эти подонки, они...";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
				{
					dialog.text = "Ох, Шарль, ты не представляешь, насколько ты вовремя. Эти... эти...";
					link.l1 = "Ну-ну, всё кончилось. Всё хорошо. Теперь всё хорошо. Господи, что они с тобой сделали...";
				}
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
				{
					dialog.text = "Шарль, ты здесь... Я верила, знала, да!";
					link.l1 = "Я летел на всех парусах и бежал со всех ног, Мэри. Ты... Они...";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
				{
					dialog.text = "Шарль... Наконец-то ты здесь. Я уж почти разуверилась...";
					link.l1 = "Я спешил как мог, Элен. Прости, что так долго.";
				}
				locCameraFromToPos(-15.32, 1.24, 1.31, true, -14.25, -1.00, -1.50);
			}
			link.l1.go = "PZ_TortureRoom_Devushka_2";
		break;
		
		case "PZ_TortureRoom_Devushka_2":
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
				{
					dialog.text = "Нет, Шарль, нет. Они хотели, но я сопротивлялась, как могла. Потому они и избили меня так сильно... Шарль, умоляю, давай уйдём отсюда, да.";
					link.l1 = "Сию же минуту, родная. Я лишь закончу одно дело...";
					link.l1.go = "PZ_TortureRoom_Devushka_3";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
				{
					dialog.text = "Худшее - не успели, Шарль. Остальное заживёт. А теперь прошу, уведи меня отсюда.";
					link.l1 = "Конечно, дорогая, конечно. Здесь осталось сделать лишь одно.";
					link.l1.go = "PZ_TortureRoom_Devushka_3";
				}
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
				{
					dialog.text = "Нет, Шарль. Они уже собирались - но ты успел. Снова. Который это уже раз?";
					link.l1 = "Я не считал, Мэри. И никогда не буду. ";
					link.l1.go = "PZ_TortureRoom_Devushka_2_1";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
				{
					dialog.text = "Ну, ты успел почти вовремя - худшего со мной не случилось. А теперь давай уйдём отсюда. Куда угодно.";
					link.l1 = "Поднимайся на ноги, Элен, и ступай наверх. Мне же надо разобраться с этой гнидой...";
					link.l1.go = "PZ_TortureRoom_Devushka_3";
				}
			}
		break;
		
		case "PZ_TortureRoom_Devushka_2_1":
			dialog.text = "А я - не перестану. А теперь давай покинем это место, прошу тебя.";
			link.l1 = "Разумеется, милая. Нам нечего здесь больше делать. Кроме одного.";
			link.l1.go = "PZ_TortureRoom_Devushka_3";
		break;
		
		case "PZ_TortureRoom_Devushka_3":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko")) AddPassenger(pchar, npchar, false);
			LAi_SetPlayerType(pchar);
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) Return_MaryOfficer();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) Return_HelenaOfficer();
		break;
		
		case "PZ_TortureRoom_Levasser_18":
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
			{
				dialog.text = "Что, кха-кха, кишка тонка, а, соплежуй? Ну так попроси своего желтозадого кабана помочь тебе... Или всё-таки сам сдюжишь? Будет повод потом, кха-кха, рассказать Пуанси, какой же ты храбрец.";
				link.l1 = "Я расскажу всем о том, каким ты был трусливым куском дерьма.";
			}
			else
			{
				dialog.text = "Что, молокосос, хочешь посмотреть, как я истеку кровью? Наслаждаешься, да, кха-кха? Все уши прожужжишь теперь своей бабе, какой ты у неё герой. Видишь тот скелет там, на стене? Жена банкира Сантьяго... Её муженёк тоже считал себя героем, но оказался лишь знатным крикуном - когда я наматывал его на это колесо...";
				link.l1 = "Можно было бы намотать на него твою тушу, подонок - но, боюсь, оно не выдержит веса твоего зада.";
			}
			link.l1.go = "PZ_TortureRoom_Levasser_19";
		break;
		
		case "PZ_TortureRoom_Levasser_19":
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
			{
				dialog.text = "Трусливым? Неужели, кха-кха...";
				link.l1 = "Жестокость - обратная сторона трусости. Но где такому как ты об этом знать?";
				link.l1.go = "PZ_TortureRoom_Levasser_20";
			}
			else
			{
				dialog.text = "Как остроумно. Попомни мои слова, де Мор: ты сдохнешь так же как этот толстосум, охрипший от собственных воплей и оглохший от криков своей...";
				link.l1 = "Гори в Аду, мразь.";
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_TortureRoom_Levasser_Mertv1");
			}
		break;
		
		case "PZ_TortureRoom_Levasser_20":
			dialog.text = "Да-а, в философии я не так умён, это признаю. Видишь тот скелет на стене, де Мор? Кха-кха... Всё, что осталось от жёнушки ростовщика Сантьяго. Он тоже любил нести заумную брехню и даже считал себя немножко смелым... А потом всё это вдруг куда-то исчезло - в тот самый момент, когда я начал наматывать его тело на вот это самое колесо. Остались лишь его вопли, от которых я чуть не оглох...";
			link.l1 = "Покончим с этим...";
			link.l1.go = "PZ_TortureRoom_Levasser_21";
		break;
		
		case "PZ_TortureRoom_Levasser_21":
			StartInstantDialog("Longway", "PZ_TortureRoom_Levasser_22", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_22":
			dialog.text = "Погодить, господин капитан... Не надо так спешить.";
			link.l1 = "В чём дело, Лонгвэй?";
			link.l1.go = "PZ_TortureRoom_Levasser_23";
		break;
		
		case "PZ_TortureRoom_Levasser_23":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Мэри";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Элен";
			dialog.text = "Не убивать его. Не так просто. Он заслужить худшее.";
			link.l1 = "Ты зол из-за сестры, друг мой. А я - из-за " + sStr + ", того, что он с ней сделал... и мог сделать. Но я не животное, как он. И жечь его углями из этой жаровни, ломать кости на том колесе... Я мог бы заковать его в кандалы или колодки и оставить так умирать от потери крови - но рисковать тем, что этот подонок выберется благодаря одному из своих прихвостней, я не могу. Не имею права.";
			link.l1.go = "PZ_TortureRoom_Levasser_24";
		break;
		
		case "PZ_TortureRoom_Levasser_24":
			dialog.text = "Погодить, господин капитан. Лонгвэй не об этом. Лонгвэй - о Пуанси.";
			link.l1 = "А что с ним?";
			link.l1.go = "PZ_TortureRoom_Levasser_25";
		break;
		
		case "PZ_TortureRoom_Levasser_25":
			dialog.text = "Подумать, как он вознаградить вас, если вы притащить ему этот скотина в живой вид. Он осыпать вас дублоны, а его... Лонгвэй думать, что сеньор с очень длинный имя предпочесть умереть здесь, а не в темница в Капстервиль.";
			link.l1 = "Может быть, ты и прав, Лонгвэй. Но я не знаю, что именно произошло между этим отморозком и шевалье. Поверь, я знаю эту публику лучше тебя. Если дело в одних лишь деньгах, как говорят, эти двое могут договориться. Пуанси отпустит его на все четыре стороны, и такая комната появится на каком-нибудь другом острове или же в одном из городов Старого света.";
			link.l1.go = "PZ_TortureRoom_Levasser_26";
			link.l2 = "А это дельная мысль, Лонгвэй. Сомневаюсь, что шевалье проявит щедрость - не в его это духе... Но в моём случае дело здесь совсем не в деньгах. Подними его! И перевяжи раны, чтобы не издох раньше положенного.";
			link.l2.go = "PZ_TortureRoom_Levasser_28";
		break;
		
		case "PZ_TortureRoom_Levasser_26":
			StartInstantDialogNoType("Levasser", "PZ_TortureRoom_Levasser_27", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_27":
			dialog.text = "Но прежде я приду за тобой. И твоей подружкой. Тебя, узкоглазый, я трогать не буду - такие пугала мне не интересны.";
			link.l1 = "Вот видишь, Лонгвэй? Это всё нужно прекратить немедленно. Здесь и сейчас.";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_TortureRoom_Levasser_Mertv1");
		break;
		
		case "PZ_TortureRoom_Levasser_28":
			StartInstantDialogNoType("Levasser", "PZ_TortureRoom_Levasser_29", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_29":
			dialog.text = "Погоди, капитан, погоди минуту, кха-кха.";
			link.l1 = "Что такое, сеньор бывший губернатор?";
			link.l1.go = "PZ_TortureRoom_Levasser_30";
		break;
		
		case "PZ_TortureRoom_Levasser_30":
			dialog.text = "В этой комнате где-то лежит мой ключ. Он открывает сундук в моём кабинете. Там двести тысяч серебром и недурной клинок. Если этого мало - в спальне моей жены, в комоде, россыпь дорогих камней.";
			link.l1 = "Хм-м, а что взамен?";
			link.l1.go = "PZ_TortureRoom_Levasser_31";
		break;
		
		case "PZ_TortureRoom_Levasser_31":
			dialog.text = "Пуля. Прикончи меня. Здесь и сейчас.";
			link.l1 = "А как же шевалье де Пуанси? Я слышал, вы старые друзья... Неужели ты не хочешь с ним повидаться?";
			link.l1.go = "PZ_TortureRoom_Levasser_32";
		break;
		
		case "PZ_TortureRoom_Levasser_32":
			dialog.text = "К дьяволу Пуанси! Так ты согласен или нет?";
			link.l1 = "Не совсем, сеньор де... не хочу перечислять.";
			link.l1.go = "PZ_TortureRoom_Levasser_33";
		break;
		
		case "PZ_TortureRoom_Levasser_33":
			dialog.text = "Тебе мало? Хорошо, есть ещё...";
			link.l1 = "Должно быть, ты и впрямь оглох от криков своих жертв, Левассер. Я же сказал: дело совсем не в деньгах. Ты боишься Пуанси неспроста, верно? Не хочу даже знать, что он с тобой сделает. Но, если это послужит толикой возмездия за твои... художества - так тому и быть.";
			link.l1.go = "PZ_TortureRoom_Levasser_34";
			pchar.questTemp.PZ_LevasserPlenen = true;
			pchar.questTemp.PZ_LevasserPobezhden = true;
		break;
		
		case "PZ_TortureRoom_Levasser_34":
			dialog.text = "Так вот каков ты на самом деле, кха-кха... Ничем не лучше меня.";
			link.l1 = "Довольно. Лонгвэй - взять его!";
			link.l1.go = "PZ_TortureRoom_Levasser_35";
		break;
		
		case "PZ_TortureRoom_Levasser_35":
			DialogExit();
			
			PChar.quest.PZ_TortureRoom_Levasser_ObratnoNaBereg.win_condition.l1 = "locator";
			PChar.quest.PZ_TortureRoom_Levasser_ObratnoNaBereg.win_condition.l1.location = "Tortuga_Torture_room";
			PChar.quest.PZ_TortureRoom_Levasser_ObratnoNaBereg.win_condition.l1.locator_group = "reload";
			PChar.quest.PZ_TortureRoom_Levasser_ObratnoNaBereg.win_condition.l1.locator = "reload1";
			PChar.quest.PZ_TortureRoom_Levasser_ObratnoNaBereg.win_condition = "PZ_TortureRoom_Levasser_ObratnoNaBereg";
			
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) Return_MaryOfficer();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) Return_HelenaOfficer();
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom")) Return_LongwayOfficer();
			sld = CharacterFromID("Levasser");
			sld.location = "None";
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		break;
		
		case "PZ_Etap6_NaBeregu_DevaZdorovaya_1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				if (!CheckAttribute(pchar, "questTemp.PZ_FlagShinInfo"))
				{
					dialog.text = "Наш корабль... Никогда не думала, что буду так рада его видеть, да... Наконец эта дьявольщина кончилась.";
				}
				else
				{
					dialog.text = "Наконец-то всё закончилось. Куда теперь, Шарль?";
				}
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				if (!CheckAttribute(pchar, "questTemp.PZ_FlagShinInfo"))
				{
					dialog.text = "Поверить не могу, что всё закончилось... Что будем делать теперь, Шарль?";
				}
				else
				{
					dialog.text = "Ну, вот и всё, Шарль. Что теперь?";
				}
			}
			if (!CheckAttribute(pchar, "questTemp.PZ_FlagShinInfo"))
			{
				link.l1 = "Увы, это ещё не конец. Чанг Шин... Лишь после встречи с ней эта история наконец закончится.";
				link.l1.go = "PZ_Etap6_NaBeregu_DevaZdorovaya_2";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.PZ_LevasserPlenen"))
				{
					link.l1 = "Курс на Капстервиль. Настала пора сеньору Левассеру стать частью истории.";
				}
				else
				{
					link.l1 = "Задание шевалье выполнено. Надо доложить ему об этом. Детали я опущу. Надеюсь лишь, что он сдержит слово, и Мишель окажется на свободе...";
				}
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_Final_SdaemKvestPuansi");
			}
		break;
		
		case "PZ_Etap6_NaBeregu_DevaZdorovaya_2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "И я тоже, да. Так что я пойду с тобой. И даже не смей спорить со мной, Шарль.";
				link.l1 = "Мэри, милая, тебе нужен отдых. Ты вот-вот в обморок упадёшь...";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Я пойду с тобой.";
				link.l1 = "Элен, ты едва не погибла в руках этого исчадия Ада. Ты едва на ногах держишься...";
			}
			link.l1.go = "PZ_Etap6_NaBeregu_DevaZdorovaya_3";
		break;
		
		case "PZ_Etap6_NaBeregu_DevaZdorovaya_3":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Мне нужен ты, Шарль. А тебе нужна я. И если кто сегодня ещё куда и упадёт - то это Чанг Шин. На пол своего шалмана. С дыркой от пули промеж глаз, да!";
				link.l1 = "Да уж, боевой задор Левассеру из тебя выбить не удалось. Я бы отправил тебя на судно, но ты же бросишься за мной следом...";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Но клинок я держать способна. Шарль, я обязана быть там. Обязана понять, что заставило её пойти на такое. Понимаешь?";
				link.l1 = "Понимаю, что тебе нужен отдых. Причём, долгий.";
			}
			link.l1.go = "PZ_Etap6_NaBeregu_DevaZdorovaya_4";
		break;
		
		case "PZ_Etap6_NaBeregu_DevaZdorovaya_4":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Ты очень хорошо меня знаешь, Шарль, да. Так что давай не будем болтать почём зря. Покончим с этим наконец.";
				link.l1 = "Будь по-твоему. Но только не лезь на рожон. Никто не знает, какие сюрпризы нас там ждут.";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Это подождёт. Ты пришёл за мной, и сейчас я пойду с тобой. Хочешь ты того или нет.";
				link.l1 = "Вижу, силу духа ты не утратила, Элен. Хорошо. Держись за мной и, ради всего святого, будь осторожна.";
			}
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_SDevushkoyKShin");
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_1":
			if (!CheckAttribute(pchar, "questTemp.PZ_FlagShinInfo"))
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
				{
					dialog.text = "Наш корабль... Не верю, что я вновь поднимусь на его борт, да...";
					link.l1 = "Он ждёт тебя, Мэри. А на нём - сытная еда и мягкая постель...";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
				{
					dialog.text = "Уф-ф... Я думала, не доберусь до шлюпки на своих двоих.";
					link.l1 = "Ты самый стойкий человек, из всех, кого я видел, Элен. Теперь забирайся в шлюпку, а потом в постель...";
				}
				link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_2";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
				{
					dialog.text = "Наш корабль... Не верю, что я вновь поднимусь на его борт, да...";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
				{
					dialog.text = "Уф-ф... Я думала, не доберусь до шлюпки на своих двоих.";
				}
				if (CheckAttribute(pchar, "questTemp.PZ_LevasserPlenen"))
				{
					link.l1 = "Курс на Капстервиль. Настала пора сеньору Левассеру стать частью истории.";
				}
				else
				{
					link.l1 = "Задание шевалье выполнено. Надо доложить ему об этом. Детали я опущу. Надеюсь лишь, что он сдержит слово, и Мишель окажется на свободе...";
				}
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_Final_SdaemKvestPuansi");
			}
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "И ты, Шарль... Но что это за взгляд? Ты опять что-то задумал, да?";
				link.l1 = "Чанг Шин. Я должен добраться и до неё.";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "А ты? Куда собрался ты?";
				link.l1 = "За Чанг Шин. Последняя часть этой ужасной истории.";
			}
			link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_3";
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_3":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Тогда я с тобой, да! Мне она задолжала по самое не балуйся!";
				link.l1 = "Мэри, родная, ты едва добралась до шлюпки. И клинок ты сейчас точно не удержишь. Я спрошу с неё за тебя, Богом клянусь. Но мне будет гораздо спокойнее, если ты останешься на корабле - тогда я буду знать, что тебе больше ничего не грозит.";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Шарль, я бы так хотела пойти с тобой... Прошу, будь осторожен. Кто знает, на что она ещё способна. Она держала меня, пока этот щенок Тибо...";
				link.l1 = "Самое страшное позади, Элен. Скоро всё закончится, обещаю.";
			}
			link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_4";
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_4":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
				{
					dialog.text = "Ну хоть Лонгвэй прикроет тебе спину в моё отсутствие. Но не дай Бог с тобой что-то случится - я и его, и Чанг Шин из-под земли достану, да!";
					link.l1 = "Всё будет хорошо. А теперь отправляйся отдыхать. И глазом не успеешь моргнуть, как я вернусь.";
					link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_7";
				}
				else
				{
					dialog.text = "А куда подевался Лонгвэй, Шарль?";
					link.l1 = "Пошёл к Чанг Шин без меня. Не утерпел, что поделать...";
					link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_5";
				}
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
				{
					dialog.text = "Что ж, по крайней мере, с тобой пойдёт Лонгвэй. Это хоть немного успокаивает.";
					link.l1 = "Вот видишь! Переживать не стоит. Я надолго не задержусь.";
					link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_7";
				}
				else
				{
					dialog.text = "А где Лонгвэй? Только сейчас заметила его отсутствие.";
					link.l1 = "Он отправился к своей сестре без меня. Не осуждаю его. Он слишком долго ждал этой встречи.";
					link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_5";
					
				}
			}
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_5":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Шарль, у меня дурное предчувствие, да...";
				link.l1 = "А у меня - совсем напротив. Эта история слишком уж затянулась, и конец её уже не за горами. Самое плохое уже позади.";
				link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_6";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Кто знает, что у него на уме, Шарль? Держи ухо востро, хорошо?";
				link.l1 = "Всенепременно. Я скоро вернусь, Элен."
				link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_7";
			}
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_6":
			dialog.text = "Обещай, что будешь готов ко всему.";
			link.l1 = "Так и есть, и так и будет. Я скоро вернусь, Мэри.";
			link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_7";
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_7":
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom")) StartInstantDialog("Longway", "PZ_Etap6_NaBeregu_DevaBolnaya_8", "Quest\CompanionQuests\Longway.c");
			else
			{
				DialogExit();
				LAi_SetPlayerType(pchar);
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sld = CharacterFromID("Mary");
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sld = CharacterFromID("Helena");
				LAi_ActorRunToLocation(sld, "reload", "sea", "", "", "", "", -1);
				sld.location = "None";
				AddQuestRecord("PZ", "51");
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) AddQuestUserData("PZ", "sText", "Мэри");
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) AddQuestUserData("PZ", "sText", "Элен");
				PChar.quest.PZ_Etap6_BrothelPoiskSestry.win_condition.l1 = "location";
				PChar.quest.PZ_Etap6_BrothelPoiskSestry.win_condition.l1.location = "Tortuga_brothelElite";
				PChar.quest.PZ_Etap6_BrothelPoiskSestry.win_condition = "PZ_Etap6_BrothelPoiskSestry";
			}
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_8":
			dialog.text = "Лонгвэй помочь вам, господин капитан. Теперь - ваш слово.";
			link.l1 = "Ты всё прекрасно слышал, Лонгвэй. Пойдём повидаемся с твоей сестрой.";
			link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_9";
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_9":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Мэри";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Элен";
			dialog.text = "Господин капитан, Лонгвэй просить ещё лишь об одно: дать Чанг Шин всё объяснить. Выслушать её и не принимать решения, которые мочь...";
			link.l1 = "То, что случилось с " + sStr + ", и её рук дело. Но я дам ей шанс себя оправдать. И только после этого приму то или иное решение.";
			link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_10";
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_10":
			dialog.text = "Лонгвэй верить ваше слово, ваш разум и ваша доброта.";
			link.l1 = "Приятель, в этой чёртовой заварухе разуму и доброте отродясь не было места. Настала пора положить всему этому конец.";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_SLongwayKShin");
		break;
		
		case "PZ_LongwayPrishelOdin":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) sStr = "Мэри";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sStr = "Элен";
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaMertva"))
			{
				dialog.text = "Господин капитан...";
				link.l1 = + sStr + " мертва.";
				link.l1.go = "PZ_LongwayPrishelOdin2";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
				{
					dialog.text = "Господин капитан, госпожа " + sStr + ", мой рад вас видеть. Это... Чанг Шин.";
					link.l1 = "Я догадался, Лонгвэй. Отойди. У тебя было достаточно времени поговорить с сестрой. Теперь она должна ответить перед " + sStr + " за то, что помогала приспешникам Левассера похитить её.";
					link.l1.go = "PZ_LongwayPrishelOdin7";
				}
				else
				{
					dialog.text = "Ваш прийти... А где же госпожа " + sStr + "? Неужели?..";
					link.l1 = "Нет, Лонгвэй. Слава Богу, нет. Я отвёл её на корабль. В противном случае я бы даже сейчас не стал разговаривать. Однако мой разговор с твоей сестрой всё равно будет не из простых и приятных.";
					link.l1.go = "PZ_LongwayPrishelOdin12";
				}
			}
		break;
		
		case "PZ_LongwayPrishelOdin2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Мэри";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Элен";
			dialog.text = "Наш с Чанг Шин приносить ваш соболезнования...";
			link.l1 = "Соболезнования от Чанг Шин?! Ты бы ещё принёс соболезнования от имени Левассера, Лонгвэй! Ты прекрасно знаешь, что она участвовала в похищении " + sStr + " наравне с остальными! И теперь её нет!..";
			link.l1.go = "PZ_LongwayPrishelOdin3";
		break;
		
		case "PZ_LongwayPrishelOdin3":
			dialog.text = "Наш... Мой понимать, что ваш чувствовать, господин капитан.";
			link.l1 = "Да неужели?";
			link.l1.go = "PZ_LongwayPrishelOdin4";
		break;
		
		case "PZ_LongwayPrishelOdin4":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Мэри";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Элен";
			dialog.text = "Мой потерять родители, как ваш помнить. Если ваш помнить. К тому же, это не Чанг Шин пытать и убивать " + sStr + ". Мой понимать ваш боль, ваш ярость. Но мой сестра виноват не так сильно, как ваш считать. Выслушать, пожалуйста.";
			link.l1 = "Я помню. Ты меня, конечно, извини, но я не могу оставить подобное безнаказанным! Я выслушаю. Но только быстро!";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_LongwayPrishelOdin_ChangShinNext");
		break;
		
		case "PZ_LongwayPrishelOdin5":
			dialog.text = "Тогда мне лучше самой всё рассказать ещё раз, уже вам, месье де Мор. Наш Ту так косноязычен, вы и так уже чуть не набросились на него.";
			link.l1 = "Тебе-то как раз стоило бы держать рот на замке. На Лонгвэя я бросаться не собирался, а вот на тебя... Это ведь ты одна из виновных в её смерти.";
			link.l1.go = "PZ_LongwayPrishelOdin6";
			locCameraFromToPos(2.17, 2.32, 0.55, true, -0.92, -0.37, -4.09);
			sld = characterFromId("Longway");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto9", "PZ_LongwayTurnToChangShin", -1);
		break;
		
		case "PZ_LongwayPrishelOdin6":
			dialog.text = "Я бы поспорила с этим, но понимаю, что лучше не стоит. Ту говорил мне о тебе, как о человеке уважительном и понимающем. Но так ли это на самом деле? Имеет ли смысл мне вообще начинать говорить? Или ты уже принял решение?";
			link.l1 = "Умеете вы залезать в голову, мадемуазель. Спорить сейчас и правда не стоит. А вот попытаться оправдаться - определённо. Ну что же, говори. Хотя бы ради Лонгвэя, но я тебя выслушаю.";
			link.l1.go = "PZ_ChangShin2";
		break;
		
		case "PZ_LongwayPrishelOdin7":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Мэри";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Элен";
			dialog.text = "Мой мочь всё объяснить, господин капитан... Всё не так, как ваш думать... Не совсем...";
			link.l1 = "Ну так объясняй. Но не мне. " + sStr + ". Взгляни в её глаза. Посмотри на её синяки и раны. И скажи ей, что всё не так, как она видела и слышала.";
			link.l1.go = "PZ_LongwayPrishelOdin8";
		break;
		
		case "PZ_LongwayPrishelOdin8":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Мэри";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Элен";
			dialog.text = "Мой просить прощение от лицо Шин, господин капитан...";
			link.l1 = "Судя по её ухмыляющемуся лицу, ты зря это делаешь. Она этого не заслуживает.";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_LongwayPrishelOdin_ChangShinNext");
		break;
		
		case "PZ_LongwayPrishelOdin9":
			dialog.text = "Вы слишком строги к нему, месье де Мор. Хотя, наверное, вы привыкли так с ним обращаться - как с типичным желтокожим батраком.";
			link.l1 = "Пытаешься настроить Лонгвэя против меня? Не выйдет. Я всегда относился к нему с уважением, и он это знает. И это главное. Хотя я понимаю, что это единственное, что тебе сейчас остаётся сделать.";
			link.l1.go = "PZ_LongwayPrishelOdin10";
			locCameraFromToPos(2.17, 2.32, 0.55, true, -0.92, -0.37, -4.09);
			sld = characterFromId("Longway");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto9", "PZ_LongwayTurnToChangShin", -1);
		break;
		
		case "PZ_LongwayPrishelOdin10":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Мэри";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Элен";
			dialog.text = "А что же хочешь сделать ты? Лишить бедного Ту семьи? Когда он снова её обрёл спустя десять лет?";
			link.l1 = "Не всегда самые крепкие семьи начинались с крови, знаешь ли. Но что же нам предлагаешь сделать ты? Оставить безнаказанным то, как ты поступила с " + sStr + "? И предлагать Лонгвэю иногда навещать женщину, что торгует другими девушками и не испытывает при этом ни малейших угрызений совести?";
			link.l1.go = "PZ_LongwayPrishelOdin11";
		break;
		
		case "PZ_LongwayPrishelOdin11":
			dialog.text = "Ну, для начала - выслушать. В отличие от него, я могу внятно рассказать то, что только что говорила ему. И при этом, я смогу смотреть в глаза хоть тебе, хоть даже ей. И всё это без акцента, который уже наверняка тебе до смерти надоел. В конце концов, что мы все от этого потеряем?";
			link.l1 = "Я привык к акценту Лонгвэя, для меня это уже его неотъемлемая часть. Я выслушаю тебя. Но только ради моего друга. Продолжай.";
			link.l1.go = "PZ_ChangShin2";
		break;
		
		case "PZ_LongwayPrishelOdin12":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Мэри";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Элен";
			dialog.text = "Почему же, господин капитан?..";
			link.l1 = "Ты ещё спрашиваешь? Она ведь тоже причастна к похищению " + sStr + ".";
			link.l1.go = "PZ_LongwayPrishelOdin13";
		break;
		
		case "PZ_LongwayPrishelOdin13":
			dialog.text = "Я... приносить искренний извинения. Это и мой вина тоже, потому что не суметь спасти сестра десять лет назад, уберечь её от всё это.";
			link.l1 = "Не стоит приносить извинения за тех, кто не испытывает ни малейшего раскаяния, Лонгвэй. Ты закончил тут? Моя очередь поговорить с ней. Основательно так поговорить.";
			link.l1.go = "PZ_LongwayPrishelOdin14";
		break;
		
		case "PZ_LongwayPrishelOdin14":
			dialog.text = "Господин капитан, постоять! Чанг Шин не быть такой, как Левассер. Не всегда. Она поведать мой о свой жизнь за этот десять лет. Позволить рассказать и ваш.";
			link.l1 = "Ну хорошо, Лонгвэй. Я слушаю. От твоего рассказа сейчас зависит многое.";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_LongwayPrishelOdin_ChangShinNext");
		break;
		
		case "PZ_LongwayPrishelOdin15":
			dialog.text = "Если это будешь рассказывать ты, у нас всех разболится голова. Позволь мне, Ту. Шарль де Мор, я ведь права?";
			link.l1 = "Права. А ты Бэлль Этуаль, настоящее имя Чанг Шин. А ещё ты тогда похитила мою возлюбленную вместе с Тибо и Мартэном. И улыбаешься, когда я упоминаю об этом. Так ведь?";
			link.l1.go = "PZ_LongwayPrishelOdin16";
		break;
		
		case "PZ_LongwayPrishelOdin16":
			dialog.text = "Глупо это отрицать. Но что теперь? Будешь пытать меня на глазах у моего брата? Или даже попросишь его тебе помочь? Или вовсе убьёшь? Ты и правда так с ним поступишь?";
			link.l1 = "Как я уже сказал, несмотря на всё, что я бы хотел сейчас сделать, я всё ещё разговариваю с тобой. Ради Лонгвэя. Не пытайся давить на жалость. Не пытайся попросить прощения. Расскажи мне то, что до этого уже рассказала ему. А там уже посмотрим, как нам всем быть дальше.";
			link.l1.go = "PZ_ChangShin2";
		break;
		
		case "PZ_Longway_91":
			if (!CheckAttribute(pchar, "questTemp.PZ_LevasserPobezhden"))
			{
				dialog.text = "Мой всё ещё не мочь поверить, что Чанг Шин превратиться в... это.";
				link.l1 = "Люди меняются, Лонгвэй. Всех можно или сломать, или вытравить из них последние капли доброты и веры в неё.";
				link.l1.go = "PZ_Longway_ToGirl1";
			}
			else
			{
				dialog.text = "Лонгвэй до сих пор не верить, что мой сестра стать такой. Почему... Если бы мой быть дом в тот день...";
				link.l1 = "Не кори себя. 'Если' - это плохое слово. К тому же, все эти годы ты делал всё, что мог.";
				link.l1.go = "PZ_Longway_ToShore1";
			}
		break;
		
		case "PZ_Longway_ToGirl1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Мэри";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Элен";
			dialog.text = "Эх... Видимо, быть так, господин капитан.";
			link.l1 = "Уходим отсюда. Нам всё ещё предстоит разгребать то, что она устроила, и спасти " + sStr + " как можно скорее.";
			link.l1.go = "PZ_Longway_ToGirl2";
		break;
		
		case "PZ_Longway_ToGirl2":
			dialog.text = "Да. Наш нужно торопиться - наш и так задержаться из-за мой.";
			link.l1 = "Ты в этом не виноват, Лонгвэй. Однако поспешим!";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_LeaveEliteBrothel");
		break;
		
		case "PZ_Longway_ToShore1":
			dialog.text = "Верно. Спасибо за поддержка, господин капитан.";
			link.l1 = "Не благодари. Она всё равно не заслуживала твоей самоотверженности - она-то тебя не искала, даже когда уже могла. Так что она перестала быть твоей семьёй. Пусть тебе от этого будет легче. Теперь мы твоя семья, Лонгвэй. Все мы.";
			link.l1.go = "PZ_Longway_ToShore2";
		break;
		
		case "PZ_Longway_ToShore2":
			dialog.text = "Да... Это быть так. А мой этого не замечать весь этот время.";
			link.l1 = "В данном случае как раз лучше поздно, чем никогда. А теперь идём... домой - наш корабль ждёт нас.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_LeaveEliteBrothel");
		break;
		
		case "PZ_Mary_91":
			dialog.text = "Как же мне хотелось это сделать, ты себе даже не представляешь, да.";
			link.l1 = "Легко представляю. Как ты себя чувствуешь, Мэри? Не в последнюю очередь, я хотел избежать этого, потому что не знал, сможешь ли ты держать свой клинок так же твёрдо, как и всегда - не одолел бы тебя ли один из них, пока я был бы занят другим?";
			link.l1.go = "PZ_Mary_92";
		break;
		
		case "PZ_Mary_92":
			dialog.text = "Ты меня недооцениваешь. К тому же, гнев придал мне много сил. А ещё... я не сомневалась, что ты бы ринулся меня спасти - совсем, как я тебя всегда, да. Знаешь, Шарль... Хоть ты и зовёшь меня своим Рыжим Талисманом, но что, если ты тоже мой талисман? Когда мы рядом, всегда происходит нечто удивительное.";
			link.l1 = "Я - твой талисман? А что, мне нравится эта мысль.";
			link.l1.go = "PZ_Mary_93";
		break;
		
		case "PZ_Mary_93":
			dialog.text = "Ну вот, уже улыбнулся! А теперь уйдём из этого отвратительного места, да поскорее, да.";
			link.l1 = "Эх-х, тяжело всё это. Хотелось бы мне, чтобы это кончилось как-то иначе.";
			link.l1.go = "PZ_Mary_94";
		break;
		
		case "PZ_Mary_94":
			dialog.text = "А мне нет. Её было уже не спасти, Шарль. И она утянула Лонгвэя на дно за собой. Он сделал свой выбор. И не оставил его нам. Подумай лучше обо всех, кому мы сегодня помогли.";
			link.l1 = "И снова мне тебе нечего возразить, Мэри. А на этот раз - даже и не хочется. Идём, мой Рыжий Талисман...";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_LeaveEliteBrothel");
		break;
		
		case "PZ_ElitaShluha_Final1":
			if (CheckAttribute(pchar, "questTemp.PZ_ChangShinMertva"))
			{
				dialog.text = "Что там произошло, месье? Мы слышали ругань и крики. Но не решились звать на помощь, пока всё не закончится.";
				link.l1 = "И правильно сделали. Ваша хозяйка мертва. Вы свободны. На вашем месте я бы собрал казну заведения, разделил и бежал с острова, как можно скорее. Я знаю, что вы не обычные куртизанки, а достойные дамы.";
				link.l1.go = "PZ_ElitaShluha_Final2";
			}
			else
			{
				dialog.text = "Ой, это вы, месье. Мы всё ждём, как выйдет хозяйка.";
				link.l1 = "Вы... Ох. Всё в порядке с вашей хозяйкой. Но я бы на вашем месте отошёл от двери. И никогда не обсуждал с ней этот вечер - всё равно не поделится, да и любопытные кошки разом все жизни теряют. Похоже, ваша мадам ой как не любит, когда кто-то суёт нос в её тайны.";
				link.l1.go = "PZ_ElitaShluha_Final3";
			}
		break;
		
		case "PZ_ElitaShluha_Final2":
			dialog.text = "Вы убили госпожу?!";
			link.l1 = "Да, убил. И если вы останетесь здесь, да ещё и натравите стражу на меня - это будет вашей величайшей глупостью. Она не была вашей благодетельницей - вас удерживали здесь и заставляли отдаваться, пусть и за деньги, пусть и не всякому сброду. Желаю вам всем вырваться отсюда. До свидания, дамы.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_ToTortugaStreets");
		break;
		
		case "PZ_ElitaShluha_Final3":
			dialog.text = "Там точно всё хорошо, мы можем зайти? Нам не нужно звать стражу?";
			link.l1 = "Там никогда не будет хорошо. Можете... на свой страх и риск. Она всё ещё беседует со своим братом. И не думаю, что им будет приятно, если их потревожат.";
			link.l1.go = "PZ_ElitaShluha_Final4";
		break;
		
		case "PZ_ElitaShluha_Final4":
			dialog.text = "Понятно... Ну вы к нам заходите как-нибудь ещё, месье.";
			link.l1 = "Я бы предпочёл здесь больше никогда не появляться. Прощайте, сударыни.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_ToTortugaStreets");
		break;
		
		case "PZ_TortugaSoldier1":
			dialog.text = "Стойте! Из заведения госпожи Этуаль за милю было слышно вопли и звуки драки. Мы думаем, что это учинили вы. Пройдёмте с нами, месье.";
			if (!CheckAttribute(pchar, "questTemp.PZ_DevushkaMertva"))
			{
				link.l1 = "Верно, но мы не учинили, а закончили эту драку. Охрана взбунтовалась из-за задержек выплаты и набросилась на мадам Этуаль, чтобы ограбить. Вот и доверяй наёмникам, да? Мы их одолели, но, к несчастью, она погибла.";
				link.l1.go = "PZ_TortugaSoldier2";
			}
			else
			{
				link.l1 = "А каким он должен быть? Я сегодня потерял любимого человека, так что дайте пройти, офицер.";
				link.l1.go = "PZ_TortugaSoldierGirlDied1";
			}
		break;
		
		case "PZ_TortugaSoldier2":
			dialog.text = "Вы же понимаете, что мы не можем поверить вам на слово? Мы должны задержать вас. А вам нужны свидетели в лице работниц. Посмотрим, что они скажут.";
			link.l1 = "Мой близкий человек тяжело ранен. А ещё я чертовски устал. Пожалуйста, могу я пройти?";
			link.l1.go = "PZ_TortugaSoldier3";
		break;
		
		case "PZ_TortugaSoldier3":
			dialog.text = "Мы постараемся разобраться во всём как можно скорее. А теперь отправляйтесь за нами.";
			link.l1 = "Отправляйтесь-ка вы в Ад...";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TortugaSoldiersFight");
		break;
		
		case "PZ_TortugaSoldierGirlDied1":
			dialog.text = "Соболезную, месье. И я ещё не офицер, но... в общем, неважно. Вы не могли бы пройти с нами и рассказать, что там такое произошло?";
			link.l1 = "Я вам и так скажу. Её заведение терпит большие убытки, и на охрану наёмникам денег уже нет. Они решили забрать всё, что оставалось, ровно в тот момент, как там был я. Мы с мадам Этуаль отбились, но сама она умерла от ран. А теперь позвольте мне, наконец, пройти.";
			link.l1.go = "PZ_TortugaSoldierGirlDied2";
		break;
		
		case "PZ_TortugaSoldierGirlDied2":
			dialog.text = "Да я бы с радостью, но ещё столько бумаг заполнить и составить. Да и работниц нужно опросить. Боюсь, вам ещё придётся задержаться в городе хотя бы на день, даже если вы говорите правду, месье.";
			link.l1 = "Ах вы проклятые крючкотворцы!";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TortugaSoldiersFight");
		break;
		
		case "PZ_Longway_101":
			dialog.text = "У Лонгвэй есть кое-что для вас, господин капитан.";
			link.l1 = "Как красиво и причудливо. Никогда не видел ничего подобного. Что это?";
			link.l1.go = "PZ_Longway_102";
			GiveItem2Character(PChar, "talisman14");
			PlaySound("interface\important_item.wav");
		break;
		
		case "PZ_Longway_102":
			dialog.text = "Это оберег для капитаны с мой Родина. И, поскольку, капитан снова ваш, а не Лонгвэй, мой передать это вам.";
			link.l1 = "Спасибо, Лонгвэй. Выходит, что со смертью ван дер Винка ты отомстил всем, кому хотел. Я очень рад этому.";
			link.l1.go = "PZ_Longway_103";
		break;
		
		case "PZ_Longway_103":
			dialog.text = "Жаль только, что мой не смочь убедить Шин снова стать хороший человек...";
			link.l1 = "Она бы уже не захотела тебя слушать, хоть ты и брат ей. Вообще никого. Ты сделал всё, что мог. Мы все прошли через очень многое за время этих поисков.";
			link.l1.go = "PZ_Longway_104";
		break;
		
		case "PZ_Longway_104":
			dialog.text = "Да... Спасибо ваш огромный, господин капитан. Лонгвэй снова быть свободен, и у его снова есть дом и друзья.";
			link.l1 = "Всегда пожалуйста, друг мой. А теперь давай ты вместе со мной навестишь моего брата. Это будет весьма... иронично.";
			link.l1.go = "PZ_Longway_105";
		break;
		
		case "PZ_Longway_105":
			DialogExit();
			DeleteAttribute(npchar, "CompanionDisable");//теперь можем и в компаньоны
			chrDisableReloadToLocation = false;
			Return_LongwayOfficer();
		break;
		
		case "PZ_PuansieDialogWithLevasser_1":
			dialog.text = "Вот мы и снова встретились, Франсуа. Смотрю, жизнь тебя малость потрепала, хе-хе.";
			link.l1 = "";
			link.l1.go = "PZ_PuansieDialogWithLevasser_1_1";
			LAi_SetHuberType(npchar);
		break;
		case "PZ_PuansieDialogWithLevasser_1_1":
			StartInstantDialog("Levasser", "PZ_PuansieDialogWithLevasser_2", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_PuansieDialogWithLevasser_2":
			dialog.text = "Пуанси, жадный ты мерзавец... Ещё не подавился золотом, от которого ломятся твои сундуки, а тебе всё мало?";
			link.l1 = "";
			link.l1.go = "PZ_PuansieDialogWithLevasser_2_1";
			CharacterTurnByChr(npchar, CharacterFromID("Puancie"));
		break;
		case "PZ_PuansieDialogWithLevasser_2_1":
			StartInstantDialogNoType("Puancie", "PZ_PuansieDialogWithLevasser_3", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_PuansieDialogWithLevasser_3":
			//LAi_SetActorType(npchar);
			//LAi_ActorSetHuberMode(npchar);
			dialog.text = "Я поделюсь с тобой, Франсуа. Тебе хватит, поверь мне.";
			link.l1 = "";
			link.l1.go = "PZ_PuansieDialogWithLevasser_3_1";
			//LAi_tmpl_SetDialog(npchar, pchar, -1.0);
		break;
		case "PZ_PuansieDialogWithLevasser_3_1":
			StartInstantDialog("Levasser", "PZ_PuansieDialogWithLevasser_4", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_PuansieDialogWithLevasser_4":
			dialog.text = "Что... что ты имеешь в виду?";
			link.l1 = "";
			link.l1.go = "PZ_PuansieDialogWithLevasser_4_1";
			CharacterTurnByChr(npchar, CharacterFromID("Puancie"));
		break;
		case "PZ_PuansieDialogWithLevasser_4_1":
			StartInstantDialogNoType("Puancie", "PZ_PuansieDialogWithLevasser_5", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_PuansieDialogWithLevasser_5":
			dialog.text = "";
			link.l1 = "Генерал-губернатор, вы что, собрались...";
			link.l1.go = "PZ_PuansieDialogWithLevasser_6";
		break;
		
		case "PZ_PuansieDialogWithLevasser_6":
			dialog.text = "Шарль, друг мой, вы выполнили свою работу и сделали это блестяще! То, что случится с этим человеком, вас волновать не должно... А впрочем, вам будет полезно знать, капитан - на случай, если вашу светлую голову однажды посетят не самые светлые мысли... Нашего с вами общего друга ждёт, так сказать, несварение желудка. Золото самую малость вредно для пищеварения... Надеюсь, прочие детали вас не интересуют.";
			link.l1 = "Обойдусь, Ваша Светлость.";
			link.l1.go = "PZ_PuansieDialogWithLevasser_7";
		break;
		
		case "PZ_PuansieDialogWithLevasser_7":
			dialog.text = "Вас ждёт большое будущее, Шарль. В отличие от месье Франсуа. Парни, тащите этого борова в тюрьму!";
			link.l1 = "";
			link.l1.go = "PZ_PuansieDialogWithLevasser_7_1";
		break;
		case "PZ_PuansieDialogWithLevasser_7_1":
			StartInstantDialog("Levasser", "PZ_PuansieDialogWithLevasser_8", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_PuansieDialogWithLevasser_8":
			dialog.text = "Что, доволен, де Мор?! Будь ты проклят, ПРОКЛЯТ! Вы оба сгорите в Аду, на одной сковородке со мной!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_LevasserVGostyahUPuansie3");
			CharacterTurnByChr(npchar, CharacterFromID("Puancie"));
			sld = characterFromID("PZ_SoldFra_1");
			CharacterTurnByChr(sld, CharacterFromID("Levasser"));
			sld = characterFromID("PZ_SoldFra_2");
			CharacterTurnByChr(sld, CharacterFromID("Levasser"));
		break;
		
		case "PZ_Baker_1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Каспер";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Шарп";
			dialog.text = "Что ж, сэр, я осмотрел мисс " + sStr + "...";
			link.l1 = "Так, и что скажешь, Раймонд?";
			link.l1.go = "PZ_Baker_2";
		break;
		
		case "PZ_Baker_2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
				{
					dialog.text = "Переживать не о чем, капитан. Мэри, конечно, пострадала, но, в целом, всё обошлось. Несколько дней ей, конечно, стоит полежать в постели, но, полагаю, уже через две недели она вновь будет рваться в бой.";
					link.l1 = "Всё ясно, Раймонд, спасибо. Ты свободен.";
					link.l1.go = "PZ_Baker_4";
				}
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Sredne"))
				{
					dialog.text = "Мэри сильно досталось, капитан. Синяки, порезы... и шок от всего пережитого, разумеется - пусть она и старается этого не показывать.";
					link.l1 = "Держится молодцом, как и всегда. Но, думаю, она всё же понимает, что сейчас ей лучше соблюдать постельный режим. Вопрос в том, как долго.";
					link.l1.go = "PZ_Baker_3";
				}
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Tyazhelo"))
				{
					dialog.text = "Не всякий моряк такое переживёт - вот что я вам скажу, капитан. Вывихи, растяжения... Повезло, что эти изверги не переломали ей кости. Однако, сухожилия всё же повреждены - клинок в руки она сможет взять не раньше, чем через месяц.";
					link.l1 = "Чёрт с ним, с клинком. На ноги она когда сможет встать?";
					link.l1.go = "PZ_Baker_3";
				}
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
				{
					dialog.text = "Не волнуйтесь, капитан. Элен пострадала, но не сильно. Несколько дней ей, конечно, надо соблюдать постельный режим, но, думаю, через пару недель она полностью восстановится.";
					link.l1 = "Всё ясно, Раймонд, спасибо. Ты свободен.";
					link.l1.go = "PZ_Baker_4";
				}
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Sredne"))
				{
					dialog.text = "Элен крепко досталось, капитан. Дело даже не столько в физических увечьях... Пребывание в том месте напомнило ей тот кошмар, что она пережила на 'Арбутусе'.";
					link.l1 = "Ну ещё бы, чёрт побери! Когда она встанет на ноги?";
					link.l1.go = "PZ_Baker_3";
				}
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Tyazhelo"))
				{
					dialog.text = "Элен прошла буквально по лезвию ножа, капитан. Удивлён, как она вообще выжила - после всего пережитого. Разрывов внутренних органов и переломов нет, зато вывихов и растяжений более чем достаточно.";
					link.l1 = "Бедная... Как долго займёт её восстановление?";
					link.l1.go = "PZ_Baker_3";
				}
			}
		break;
		
		case "PZ_Baker_3":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Sredne"))
				{
					dialog.text = "Хотя бы неделю, сэр. Если будет соблюдать мои рекомендации, то где-то через месяц сможет вернуться в строй.";
				}
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Tyazhelo"))
				{
					dialog.text = "Не раньше чем через две недели, сэр. После этого я разрешу ей непродолжительные прогулки на квартердеке. Полное же восстановление займёт никак не меньше двух месяцев.";
				}
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Sredne"))
				{
					dialog.text = "Не беспокойте её как минимум неделю, вот что я вам скажу, сэр. Полное же восстановление займёт не меньше месяца.";
				}
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Tyazhelo"))
				{
					dialog.text = "Две недели ей должно провести в постели, после - возможны недолгие прогулки по палубе. Но увидеть ее в строю раньше чем через два месяца даже не рассчитывайте.";
				}
			}
			link.l1 = "Всё ясно, Раймонд, спасибо. Ты свободен.";
			link.l1.go = "PZ_Baker_4";
		break;
		
		case "PZ_Baker_4":
			DialogExit();
			sld = CharacterFromID("Baker");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "PZ_RazgovorSVrachom_4", -1);
		break;
		
		case "PZ_DevushkaVstalaSKrovati_Dialog1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "А это тяжелее, чем я думала - простоять даже пару минут на своих двоих после того, как провалялась столько времени, да!";
				link.l1 = "Может, не стоит так резко прекращать соблюдать постельный режим, родная?";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Ох-х, моя голова...";
				link.l1 = "Элен! Не рановато ли ты встала? Ты же едва на ногах стоишь!";
			}
			link.l1.go = "PZ_DevushkaVstalaSKrovati_Dialog2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_DevushkaVstalaSKrovati_Dialog2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Да я скорее спалю эту чёртову кровать, чем снова лягу в неё - по крайней мере, пока не пройдусь от носа до кормы и обратно!";
				link.l1 = "Это хорошая удобная кровать. Да и корабль неплохой. Так что не стану тебе препятствовать. Но буду рядом, чтобы ты не выкинула какую-нибудь глупость.";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Я в порядке, капитан, пусть и не в полном. Клинком махать я пока не готова, но и постель эту уже ненавижу всей душой.";
				link.l1 = "Ну, недолгая прогулка по шканцам тебе, наверное, не повредит. Но даже не думай приближаться к вантам!";
			}
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_DevushkaStoitVosstanovlenie");
		break;
		
		case "PZ_DevushkaSnovaOfficer_Sex1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Шарль, скажи, а тебе не кажется, что ты про меня совсем позабыл? Напомни-ка, когда мы последний раз были вместе, да!";
				link.l1 = "До того, как... Давай не будем об этом вспоминать, хорошо, Мэри?";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Мой капитан, мне кажется, или я перестала быть тебе интересна как женщина?";
				link.l1 = "Неожиданный заход, Элен. Обычно с подобными инициативами выступаю я, но... не был уверен, что ты успела оправиться после...";
			}
			link.l1.go = "PZ_DevushkaSnovaOfficer_Sex2";
			DelLandQuestMark(npchar);
			pchar.questTemp.PZ_DevushkaSnovaOfficer = true;
			DeleteQuestCondition("PZ_DevushkaSnovaOfficer2");
		break;
		
		case "PZ_DevushkaSnovaOfficer_Sex2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Тогда вспомни обо мне наконец, да. Или после того, как меня отделали эти два ублюдка, я стала тебе неприятна?";
				link.l1 = "В жизни ничего глупее не слышал. Я просто не хотел тебя тревожить, пока ты сама не будешь к этому готова. И, раз уж ты хочешь...";
				link.l1.go = "PZ_DevushkaSnovaOfficer_Sex3";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Всё хорошо, Шарль, правда. Я просто стараюсь об этом не вспоминать, вот и всё. К тому же от самого страшного ты меня спас. А теперь давай не будем трепаться почём зря и просто наверстаем упущенное.";
				link.l1 = "Чертовски правильная мысль, Элен.";
				link.l1.go = "exit";
				pchar.quest.sex_partner = Npchar.id;
				AddDialogExitQuest("cabin_sex_go");
			}
		break;
		
		case "PZ_DevushkaSnovaOfficer_Sex3":
				dialog.text = "Шарль, я не хочу - я требую, да!";
				link.l1 = "Не рискну тебе отказать...";
				link.l1.go = "exit";
				pchar.quest.sex_partner = Npchar.id;
				AddDialogExitQuest("cabin_sex_go");
		break;
		
		case "PZ_DevushkaSnovaOfficer_Dialog1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Шарль, нам нужно поговорить, да.";
				link.l1 = "Что-то случилось, Мэри? У тебя весьма озабоченный вид, и обычно это не предвещает ничего хорошего.";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Капитан, должна тебе кое-что сказать.";
				link.l1 = "Вот как, Элен? Что ж, слушаю тебя.";
			}
			link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_DevushkaSnovaOfficer_Dialog2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Вот значит как! А разве то, что я готова вернуться к исполнению своих обязанностей офицера - это ничего хорошего?!";
				link.l1 = "Так вот в чём дело. Ну, если ты чувствуешь в себе достаточно сил для этого - это не хорошо, а просто прекрасно, дорогая.";
				link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog3";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Мне надоело, что команда таращится на меня как на немощную бабку с протянутой рукой. Я хочу вернуться за штурвал нашего судна, а ещё - размять руки тренировкой с клинком...";
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
				{
					link.l1 = "Если ты чувствуешь себя готовой к этому, то возражать не стану, милая. Однако, в схватках попрошу тебя быть осторожной, договорились?";
					link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog2_1";
				}
				else
				{
					link.l1 = "На мостике тебя не хватает, Элен. Что же до клинка... думаю, тебе пригодится это.";
					link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog3";
				}
			}
		break;
		
		case "PZ_DevushkaSnovaOfficer_Dialog2_1":
			dialog.text = "Конечно, капитан, как скажешь.";
			link.l1 = "Вот и славно.";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_DevushkaSnovaOfficer3");
		break;
		
		case "PZ_DevushkaSnovaOfficer_Dialog3":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Замечательно, да! Не терпится уже поупражняться с клинком...";
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
				{
					link.l1 = "Рад это слышать, Мэри. Но всё же пока не рвись в гущу событий... Хотя кому я это говорю?";
					link.l1.go = "exit";
					AddDialogExitQuest("PZ_DevushkaSnovaOfficer3");
				}
				else
				{
					link.l1 = "Тогда, полагаю, ты будешь рада вновь вложить в ножны этот палаш...";
					link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog4";
				}
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Я... я не знаю, что сказать, Шарль. Я только сейчас поняла, сколько для меня значит этот катлас...";
				link.l1 = "Ну, я понял это уже давно, потому он и дожидался тебя в целости и сохранности.";
				link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog4";
				notification("Отдали Катлас Блейза", "None");
				PlaySound("interface\important_item.wav");
			}
		break;
		
		case "PZ_DevushkaSnovaOfficer_Dialog4":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Мой нарвал, да!!! Шарль, ты сберёг его! Я... я не рада, я счастлива, да! Спасибо тебе, спасибо! Я так боялась, что он остался на корабле Мартэна...";
				link.l1 = "Этому клинку место в твоей руке, мой Рыжий Талисман. Верю, что больше ты его никогда не утратишь... Ну, не стану мешать вашему воссоединению, ха-ха!";
				notification("Отдали Нарвал", "None");
				PlaySound("interface\important_item.wav");
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_DevushkaSnovaOfficer3");
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Спасибо тебе, Шарль. Знаешь, наверное, за это я тебя и люблю...";
				link.l1 = "За то, что возвращаю потерянные вещи? Ха-ха-ха...";
				link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog5";
			}
		break;
		
		case "PZ_DevushkaSnovaOfficer_Dialog5":
			dialog.text = "Тебе смешно, а я ведь серьёзно говорю.";
			link.l1 = "Знаю, Элен. Я тоже тебя люблю - хотя пока сам не понял, за что именно.";
			link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog6";
		break;
		
		case "PZ_DevushkaSnovaOfficer_Dialog6":
			dialog.text = "Наверное, за то, что терплю тебя. И ещё не прибила - этим самым катласом.";
			link.l1 = "Пожалуй, спасусь от этого на шканцах. Жду тебя там, Элен.";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_DevushkaSnovaOfficer3");
		break;
	}
} 