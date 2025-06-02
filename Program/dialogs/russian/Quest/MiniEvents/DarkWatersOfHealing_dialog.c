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
		
		case "Tomas":
			dialog.text = ""+TimeGreeting()+"! Что привело вас в мой дом?";
			link.l1 = "Я капитан "+GetFullName(pchar)+". Пришёл по просьбе цыганки. Она не понимает, почему вы отвергли её помощь, и хочет узнать причину. Разве вы сейчас в таком положении, чтобы отказываться от любой - даже малейшей возможности помочь?";
			link.l1.go = "Tomas_1";
			DelLandQuestMark(npchar);
		break;
		
		case "Tomas_1":
			dialog.text = "Ох, капитан... Поймите, мне пришлось отказаться, но вовсе не по своей воле. Поверьте, я готов отдать всё, чтобы Эстер выздоровела.";
			link.l1 = "Что же могло заставить вас отвергнуть помощь, в которой вы так нуждаетесь?";
			link.l1.go = "Tomas_2";
		break;
		
		case "Tomas_2":
			dialog.text = "Видите ли, наша семья всегда была набожна. После смерти моей жены, Оливии, я и вовсе держусь только благодаря одной лишь вере. Когда цыганка предложила свою помощь, я согласился - лишь бы спасти дочь. Но... об этом узнал наш пастырь.";
			link.l1 = "Дайте угадаю: он - противник такого рода услуг?";
			link.l1.go = "Tomas_3";
		break;
		
		case "Tomas_3":
			dialog.text = "Именно так. Он убедил меня, что только молитва и воля Господня способны излечить мою дочь. А на тот случай, если я отступлю от этого пути, - воспользуюсь помощью 'ведьмы', он пригрозил отлучением от церкви. Понимаете? Отлучением!";
			link.l1 = "Значит, здоровье Эстер зависит только от слова пастыря?";
			link.l1.go = "Tomas_4";
		break;
		
		case "Tomas_4":
			dialog.text = "Мы с дочерью живём церковью. Она - наше всё. Если у цыганки ничего не получится, я потеряю не только дочь, но и остатки своего места в этом мире. Люди отвернутся, церковь отвергнет. Мы с Эстер останемся совсем одни.";
			link.l1 = "А если бы пастырь дал своё согласие? Вы бы тогда позволили цыганке попытаться?";
			link.l1.go = "Tomas_5";
		break;
		
		case "Tomas_5":
			dialog.text = "Да. Если бы церковь благословила её действия... Тогда я бы доверился. Я готов испробовать всё, что может помочь.";
			link.l1 = "Понятно. Хорошо, Томас, я помогу вам. Поговорю с вашим пастырем. Возможно, мне удастся убедить его.";
			link.l1.go = "Tomas_6";
		break;
		
		case "Tomas_6":
			dialog.text = "Вы... вы действительно готовы нам помочь? Капитан, я буду молиться за ваш успех. Но имейте в виду... наш пастырь - человек упрямый и принципиальный,  переубедить его будет непросто.";
			link.l1 = "Принципиальность побеждается убедительными аргументами. Ждите, я скоро вернусь.";
			link.l1.go = "Tomas_7";
		break;
		
		case "Tomas_7":
			DialogExit();
			
			LAi_SetActorType(npchar);
			AddQuestRecord("DWH", "3");
			pchar.questTemp.DWH_pastor = true;
			AddLandQuestMark(characterFromId("SentJons_Priest"), "questmarkmain");
		break;
		
		case "Tomas_11":
			dialog.text = "...";
			link.l1 = "Томас, мне удалось убедить пастыря.";
			link.l1.go = "Tomas_12";
			DelLandQuestMark(npchar);
		break;
		
		case "Tomas_12":
			dialog.text = "Правда? Невероятно! Тогда давайте же пригласим цыганку скорее.";
			link.l1 = "Обязательно пригласим, но есть один нюанс. Пастырь надеется, что всё это не поколеблет вашу веру и ждёт от вас искреннего раскаяния и добрых дел. Первым из них может стать покупка нового колокола для прихода.";
			link.l1.go = "Tomas_13";
		break;
		
		case "Tomas_13":
			dialog.text = "Ох, капитан... Колокол стоит немалых денег. Возможно, мне придётся расстаться с чем-то из украшений моей покойной жены. Но ради Эстер я готов отдать всё, что у меня есть, и даже больше. Разумеется, я буду молить Господа о прощении. Я отправлюсь к кузнецу, сделаю заказ и найду цыганку/nА вас прошу передать пастору, что колокол скоро будет. Я достану его даже из-под земли, если понадобится.";
			link.l1 = "Хорошо, Томас.";
			link.l1.go = "Tomas_14";
		break;
		
		case "Tomas_14":
			DialogExit();
			
			LAi_SetActorType(npchar);
			pchar.questTemp.DWH_pastor_PrinesDengi = true;
			AddLandQuestMark(characterFromId("SentJons_Priest"), "questmarkmain");
		break;
		
		case "Tomas_15":
			dialog.text = "...";
			link.l1 = "Я передал пастору ваши слова. Больше он не будет чинить препятствий, так что вы можете начинать.";
			link.l1.go = "Tomas_16";
			DelLandQuestMark(npchar);
		break;
		
		case "Tomas_16":
			dialog.text = "Спасибо, капитан, за ваше участие! Возьмите эти пятьдесят дублонов, это наименьшее, что я могу для вас сделать, но это всё что у меня есть на данный момент...";
			link.l1 = "Что вы! Я помогаю вам вовсе не из-за денег. Сейчас всё готово для проведения... кхм... лечения?";
			link.l1.go = "Tomas_16_1";
			link.l2 = "Ну, раз уж вы настаиваете... Я могу ещё чем-нибудь помочь?";
			link.l2.go = "Tomas_16_2";
		break;
		
		case "Tomas_16_1":
			StartInstantDialog("DWH_gypsy", "gypsy_1", "Quest\MiniEvents\DarkWatersOfHealing_dialog.c");
			AddCharacterExpToSkill(pchar, "Leadership", 150);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
		break;
		
		case "Tomas_16_2":
			StartInstantDialog("DWH_gypsy", "gypsy_1", "Quest\MiniEvents\DarkWatersOfHealing_dialog.c");
			AddCharacterExpToSkill(pchar, "Commerce", 150);
			AddItems(pchar, "gold_dublon", 50);
		break;
		
		case "gypsy_1":
			dialog.text = "Для приготовления снадобья, что вернёт девчушке здоровье, мне нужна мангароса - редкое растение, растущее в местах, где человек редко ступает. Знаю я одну пещеру за городом, там часто шастают... всякие отбросы. Мангаросу они на куриво переводят, не понимая её силы. Выручи, соколик, добудь мне мангаросу, без неё ничего не получится.";
			if (CheckAttribute(pchar, "questTemp.Mangarosa"))
			{
				link.l1 = "Мангароса? Мне знакомо это растение.";
				link.l1.go = "gypsy_VD_manga_1";
			}
			else
			{
				link.l1 = "Как это растение выглядит?";
				link.l1.go = "gypsy_VD_no_manga";
			}
		break;
		
		case "gypsy_VD_no_manga":
			dialog.text = "Это довольно высокое растение с рассечёнными листьями и приятным, дурманящим запахом. Ты точно не спутаешь его ни с чем.";
			link.l1 = "Хорошо, я найду эту мангаросу.";
			link.l1.go = "gypsy_2";
		break;
		
		case "gypsy_VD_manga_1":
			dialog.text = "Ты тоже подмешиваешь его в табак?";
			if (CheckAttribute(pchar, "questTemp.Mangarosa") && pchar.questTemp.Mangarosa == "amelia")
			{
				link.l1 = "Нет, что ты! Есть одна знахарка, Амелия. Она готовит на основе этого растения такие зелья, что, без преувеличения, способны перевернуть сознание.";
				link.l1.go = "gypsy_VD_manga_1_2";
			}
			else
			{
				link.l1 = "Нет, но мне доводилось пару раз держать мангаросу в руках.";
				link.l1.go = "gypsy_VD_manga_2";
			}
		break;
		
		case "gypsy_VD_manga_1_2":
			dialog.text = "Так ты знаком с Амелией? Ну, соколик, ты и мне скоро конкуренцию составишь. Но сейчас не время об этом говорить. Ступай, принеси мангаросу, а я приготовлю всё необходимое.";
			link.l1 = "Уже иду.";
			link.l1.go = "gypsy_2";
			AddCharacterExpToSkill(pchar, "Fortune", 200);
		break;
		
		case "gypsy_VD_manga_2":
			dialog.text = "Вижу, не простой ты, соколик. Знания твои велики, ум острый, как нож! Ты не боишься шагать в неизведанное, стремишься понять всё, что скрыто от других. Повезло Томасу, что ты помочь ему взялся. Ступай теперь, принеси мне мангаросу, и я излечу девочку.";
			link.l1 = "...";
			link.l1.go = "gypsy_2";
		break;
		
		case "gypsy_2":
			DialogExit();
			
			sld = CharacterFromID("DWH_Tomas");
			LAi_SetActorType(sld);
			sld = CharacterFromID("DWH_gypsy");
			LAi_SetActorType(sld);
			
			AddQuestRecord("DWH", "5");
			
			// поход за мангаросой
			LAi_LocationDisableOfficersGen("Antigua_Grot", true);
			locations[FindLocation("Antigua_Grot")].DisableEncounters = true;
			PChar.quest.DWH_Grot.win_condition.l1 = "location";
			PChar.quest.DWH_Grot.win_condition.l1.location = "Antigua_Grot";
			PChar.quest.DWH_Grot.function = "DWH_Grot";
		break;
		
		case "Bandit_1":
			dialog.text = "Ха-ха. Говорю тебе, Марк, он - простофиля. Он даже дом не запирает.";
			link.l1 = "А ты уверен, что его курица не будет дома торчать?";
			link.l1.go = "Bandit_2";
			
			locCameraSleep(true);
			sld = CharacterFromID("DWH_Bandit_1");
			CharacterTurnToLoc(sld, "goto", "ass4");
			sld = CharacterFromID("DWH_Bandit_2");
			CharacterTurnToLoc(sld, "goto", "ass2");
		break;
		
		case "Bandit_2":
			DialogExit();
			
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "goto", "goto2", "", -1);
			DoQuestFunctionDelay("DWH_Grot_2", 4.0);
		break;
		
		case "Bandit_3":
			sld = CharacterFromID("DWH_gypsy");
			dialog.text = "Гляньте-ка, свежая рыба заплыла! Давай-давай, не стой столбом. Карманы выворачивай, да побыстрее, пока мы добрые.";
			link.l1 = "Тише, разбойнички. Я пришёл к вам по делу, меня к вам прислала "+sld.name+". Мне нужна мангароса.";
			link.l1.go = "Bandit_4";
			
			locCameraSleep(false);
			locCameraFromToPos(3.39, 1.16, -1.80, true, 3.62, -0.50, 3.63);
			sld = CharacterFromID("DWH_Bandit_2");
			CharacterTurnToLoc(sld, "goto", "goto2");
		break;
		
		case "Bandit_4":
			sld = CharacterFromID("DWH_gypsy");
			dialog.text = ""+sld.name+" говоришь? Хорошо, есть у нас мангароса. Давай десять золотых и она твоя.";
			if (PCharDublonsTotal() >= 10)
			{
				link.l1 = "Держи.";
				link.l1.go = "Bandit_5";
			}
			link.l2 = "Деньги? Зачем вам деньги? Я милостыню не раздаю. А вот два фунта стали под рёбра - это запросто!";
			link.l2.go = "Bandit_7";
		break;
		
		case "Bandit_5":
			dialog.text = "Ладно, вот твоя мангароса. И запомни, ты нас не видел.";
			link.l1 = "Хех. Мог бы и не предупреждать.";
			link.l1.go = "Bandit_6";
			GiveItem2Character(PChar, "cannabis7");
			RemoveDublonsFromPCharTotal(10);
		break;
		
		case "Bandit_6":
			DialogExit();
			
			EndQuestMovie();
			LAi_SetPlayerType(pchar);
			LAi_LocationDisableOfficersGen("Antigua_Grot", false);
			locations[FindLocation("Antigua_Grot")].DisableEncounters = false;
			
			SetFunctionLocatorCondition("DWH_VorovstvoSunduk", "Antigua_Grot", "box", "box1", false)
			
			sld = CharacterFromID("DWH_gypsy");
			LAi_SetStayType(sld);
			sld.dialog.filename = "Quest\MiniEvents\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "gypsy_3";
			AddLandQuestMark(sld, "questmarkmain");
			
			for (i=1; i<=2; i++)
			{
				sld = CharacterFromID("DWH_Bandit_"+i);
				LAi_CharacterDisableDialog(sld);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
				LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, false, "DWH_Podkreplenie");
			}
		break;
		
		case "Bandit_7":
			DialogExit();
			
			chrDisableReloadToLocation = true;
			EndQuestMovie();
			LAi_SetPlayerType(pchar);
			GiveItem2Character(NPChar, "cannabis7");
			npchar.SaveItemsForDead = true;
			npchar.DontClearDead = true;
			LAi_SetFightMode(pchar, true);
			
			for (i=1; i<=2; i++)
			{
				sld = CharacterFromID("DWH_Bandit_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			for (i=3; i<=4; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("DWH_Bandit_"+i, "citiz_48", "man", "man", sti(pchar.rank), PIRATE, 0, true, "pirate"));
				if (i==4) sld.model = "citiz_49";
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				ChangeCharacterAddressGroup(sld, "Antigua_Grot", "reload", "reload1");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheckFunction("EnemyFight", "DWH_Grot_4");
		break;
		
		case "gypsy_3":
			if (CheckCharacterItem(PChar, "cannabis7"))
			{
				dialog.text = "...";
				link.l1 = "Посмотри, "+npchar.name+", это растение тебе нужно?";
				link.l1.go = "gypsy_4";
				DelLandQuestMark(npchar);
			}
			else
			{
				dialog.text = "Ты принёс то, что я просила?";
				link.l1 = "Ещё нет, я решаю этот вопрос.";
				link.l1.go = "exit";
				NextDiag.TempNode = "gypsy_3";
			}
		break;
		
		case "gypsy_4":
			dialog.text = "Да, это оно. Теперь у меня есть всё, и я могу начинать.";
			link.l1 = "...";
			link.l1.go = "gypsy_5";
			TakeItemFromCharacter(pchar, "cannabis7");
		break;
		
		case "gypsy_5":
			StartInstantDialog("DWH_Tomas", "Tomas_17", "Quest\MiniEvents\DarkWatersOfHealing_dialog.c");
		break;
		
		case "Tomas_17":
			dialog.text = "Идём скорее, не будем терять времени.";
			link.l1 = "...";
			link.l1.go = "Tomas_18";
			CharacterTurnByChr(npchar, CharacterFromID("DWH_gypsy"));
		break;
		
		case "Tomas_18":
			dialog.text = "Капитан, если вы не против, увидимся позже. Сейчас нам предстоит самая важная часть... лечения.";
			link.l1 = "Конечно, Томас. Надеюсь, вскоре ваша дочь поправится.";
			link.l1.go = "Tomas_19";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "Tomas_19":
			DialogExit();
			
			sld = CharacterFromID("DWH_gypsy");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", -1);
			
			sld = CharacterFromID("DWH_Tomas");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", -1);
			
			LocatorReloadEnterDisable("SentJons_houseS3", "reload2", true);
			LocatorReloadEnterDisable("SentJons_town", "houseS3", true);
			
			AddQuestRecord("DWH", "6");
			SetTimerFunction("DWH_Vizdorovela", 0, 0, 30);
		break;
		
		case "gypsy_6":	// если не прошли проверку ВД у священника
			dialog.text = "...";
			link.l1 = ""+npchar.name+", Томас выдворил тебя из дома не по своей воле. Пастырь пригрозил ему отлучением от церкви, если тот примет твою помощь.";
			link.l1.go = "gypsy_7";
			DelLandQuestMark(npchar);
		break;
		
		case "gypsy_7":
			dialog.text = "Я ведь сразу поняла, милок, что с тяжёлым сердцем отказ он мне преподнёс.";
			link.l1 = "Можно ли ему помочь, не привлекая внимания церкви?";
			link.l1.go = "gypsy_8";
		break;
		
		case "gypsy_8":
			dialog.text = "Ох, милок, дело-то непростое, но пути мне ведомы, знаю, что делать. Только без помощи твоей тут не обойтись, сам понимаешь.";
			link.l1 = "Конечно, ты можешь на меня рассчитывать.";
			link.l1.go = "gypsy_10";
			link.l2 = "Мне жаль, чернобровая, но у меня совершенно нет времени этим заниматься. Я сделал всё что мог, теперь мне пора заняться своими делами.";
			link.l2.go = "gypsy_9";
		break;
		
		case "gypsy_9":
			DialogExit();
			CloseQuestHeader("DWH");
			
			sld = CharacterFromID("DWH_gypsy");
			LAi_CharacterDisableDialog(sld);
			sld.lifeday = 0;
			
			sld = CharacterFromID("DWH_Tomas");
			sld.lifeday = 0;
		break;
		
		case "gypsy_10":
			dialog.text = "Тогда вот что мне нужно: вещь, которая принадлежит девочке, два стебля дурман травы, один стебель ипекакуаны, и один - вербены. Если ты принесёшь мне это всё, я смогу приготовить для неё лечебное снадобье.";
			link.l1 = "Хорошо, я достану всё что нужно.";
			link.l1.go = "gypsy_11";
		break;
		
		case "gypsy_11":
			DialogExit();
			AddQuestRecord("DWH", "7");
			
			LAi_CharacterDisableDialog(npchar);
			
			sld = CharacterFromID("DWH_Tomas");
			LAi_SetStayType(sld);
			sld.dialog.filename = "Quest\MiniEvents\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "Tomas_21";
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "Tomas_21":
			dialog.text = "...";
			link.l1 = "Томас, увы, пастырь не прислушался к моим аргументам. Но мы с цыганкой сможем помочь вам. Мне нужно...";
			link.l1.go = "Tomas_22";
			DelLandQuestMark(npchar);
		break;
		
		case "Tomas_22":
			dialog.text = "Вы предлагаете мне пойти против церкви?";
			link.l1 = "Мы сделаем всё тихо, никто ничего не узнает. Совсем скоро ваша дочь сможет вновь наслаждаться жизнью и свободно гулять по городу, как и подобает юной леди.";
			link.l1.go = "Tomas_23";
			link.l2 = "Чёрт возьми, Томас Моррисон, вы хотите, чтобы ваша дочь выздоровела или только прикрываетесь красивыми словами?";
			link.l2.go = "Tomas_24";
		break;
		
		case "Tomas_23":
			dialog.text = "Ладно, я согласен. Но прошу вас, действуйте осторожно. Я не хочу лишних слухов и неприятностей.";
			link.l1 = "Безусловно. Итак, мне нужна личная вещь вашей дочери - что-то, к чему она привязана.";
			link.l1.go = "Tomas_25";
			AddCharacterExpToSkill(pchar, "Sneak", 200);
		break;
		
		case "Tomas_24":
			dialog.text = "Ладно, я согласен. Но прошу вас, действуйте осторожно. Я не хочу лишних слухов и неприятностей.";
			link.l1 = "Безусловно. Итак, мне нужна личная вещь вашей дочери - что-то, к чему она привязана.";
			link.l1.go = "Tomas_25";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "Tomas_25":
			dialog.text = "Хм... Да! Я знаю, что подойдёт. Подождите меня здесь, я мигом.";
			link.l1 = "Жду...";
			link.l1.go = "Tomas_26";
		break;
		
		case "Tomas_26":
			DialogExit();
			SetLaunchFrameFormParam("Прошло несколько минут...", "Run_Function", 0, 4.0);
			SetLaunchFrameRunFunctionParam("DWH_TomasGovotitAgain", 0.0);
			LaunchFrameForm();
		break;
		
		case "Tomas_27":
			dialog.text = "Вот. Это нефритовые бусы. Эстер никогда их не снимала - они ей очень дороги.";
			link.l1 = "Отлично. Теперь вам остаётся только ждать. Скоро увидимся, Томас.";
			link.l1.go = "Tomas_28";
			GiveItem2Character(PChar, "jewelry49");
		break;
		
		case "Tomas_28":
			DialogExit();
			AddQuestRecord("DWH", "8");
			
			sld = CharacterFromID("DWH_gypsy");
			LAi_CharacterEnableDialog(sld);
			sld.dialog.filename = "Quest\MiniEvents\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "gypsy_21";
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "gypsy_21":
			dialog.text = "Ты принёс то, что я просила?";
			if (GetCharacterItem(pchar, "cannabis1") >= 2 && GetCharacterItem(pchar, "cannabis4") >= 1 && GetCharacterItem(pchar, "cannabis3") >= 1)
			{
				link.l1 = "Я собрал всё что нужно.";
				link.l1.go = "gypsy_22";
			}
			link.l2 = "Напомни мне, что мне нужно принести.";
			link.l2.go = "gypsy_napomni";
		break;
		
		case "gypsy_napomni":
			dialog.text = "Вот что мне нужно: вещь, которая принадлежит девочке, два стебля дурман травы, один стебель ипекакуаны, и один вербены. Если ты принесёшь мне это всё, я смогу приготовить для неё лечебное снадобье.";
			link.l1 = "Хорошо, я достану всё что нужно.";
			link.l1.go = "gypsy_napomni_2";
		break;
		
		case "gypsy_napomni_2":
			DialogExit();
			NextDiag.TempNode = "gypsy_21";
		break;
		
		case "gypsy_22":
			dialog.text = "Отлично. Теперь я смогу приготовить лечебное снадобье для девчонки. Оно будет готово не раньше завтрашнего утра. Найти ты меня сможешь, как обычно, на улицах города.";
			link.l1 = "Хорошо, до встречи.";
			link.l1.go = "gypsy_23";
			DelLandQuestMark(npchar);
			RemoveItems(pchar, "cannabis1", 2);
			RemoveItems(pchar, "cannabis4", 1);
			RemoveItems(pchar, "cannabis3", 1);
			RemoveItems(pchar, "jewelry49", 1);
		break;
		
		case "gypsy_23":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("DWH", "11");
			SetTimerFunction("DWH_GypsyPrigotovilaZelie", 0, 0, 1);
		break;
		
		case "gypsy_31":
			dialog.text = "...";
			link.l1 = "Ну что, "+npchar.name+", твоё снадобье готово?";
			link.l1.go = "gypsy_32";
			DelLandQuestMark(npchar);
		break;
		
		case "gypsy_32":
			dialog.text = "Вот оно, милок. Пусть девочка наденет эти бусы и выпьет содержимое флакона до дна. Не более чем через месяц она будет полностью здорова.";
			link.l1 = "Немедленно отнесу это Томасу. Бывай, чернобровая.";
			link.l1.go = "gypsy_33";
			GiveItem2Character(PChar, "potion1");
			GiveItem2Character(PChar, "jewelry49");
		break;
		
		case "gypsy_33":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			
			sld = CharacterFromID("DWH_Tomas");
			LAi_SetStayType(sld);
			sld.dialog.filename = "Quest\MiniEvents\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "Tomas_31";
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "Tomas_31":
			dialog.text = "...";
			link.l1 = "Томас, всё готово. Эстер должна надеть эти бусы и осушить флакон со снадобьем за один раз.";
			link.l1.go = "Tomas_32";
			DelLandQuestMark(npchar);
		break;
		
		case "Tomas_32":
			dialog.text = "Спасибо вам, "+pchar.name+"! Прошу меня простить, не хочу терять ни минуты...";
			link.l1 = "Конечно-конечно.";
			link.l1.go = "Tomas_33";
		break;
		
		case "Tomas_33":
			DialogExit();
			
			sld = CharacterFromID("DWH_Tomas");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", -1);
			
			LocatorReloadEnterDisable("SentJons_houseS3", "reload2", true);
			LocatorReloadEnterDisable("SentJons_town", "houseS3", true);
			
			AddQuestRecord("DWH", "6");
			SetTimerFunction("DWH_Vizdorovela", 0, 0, 30);
		break;
		
		case "Tomas_41":
			dialog.text = "Здравствуйте, "+pchar.name+"! Моя Эстер выздоровела! Она полностью здорова и сейчас в церкви, молится Господу Богу нашему, благодарит Его за то, что Он ниспослал нам вас и цыганку!";
			link.l1 = "Томас, я рад, что всё получилось! Берегите девочку - теперь у неё впереди долгая и счастливая жизнь.";
			link.l1.go = "Tomas_42";
			DelLandQuestMark(npchar);
		break;
		
		case "Tomas_42":
			dialog.text = "Возьмите эти триста дублонов. К сожалению, больше я предложить не могу, ибо мне пришлось влезть в долги, чтобы собрать эту сумму. Но знайте: никакие слова и никакое золото не смогут выразить той благодарности, которую я испытываю к вам, капитан. Вы не только избавили меня от страха за её жизнь, но и дали нашей семье шанс на будущее. Я всегда буду вам признателен!";
			link.l1 = "Спасибо! Триста дублонов - весьма щедрая награда, так что не волнуйтесь, вы отблагодарили меня сполна!";
			link.l1.go = "Tomas_43";
			link.l2 = "Не возьму я ваши деньги, Томас. Даже не думайте настаивать! Я помогал вам вовсе не корысти ради. Купите лучше юной Эстер красивое платье - она этого заслуживает.";
			link.l2.go = "Tomas_46";
		break;
		
		case "Tomas_43":
			dialog.text = ""+pchar.name+", заходите к нам в любое время. В нашем доме вам всегда будут рады. И ещё - поговорите с цыганкой, она хотела вас увидеть.";
			link.l1 = "Почту за честь! А теперь, прошу простить, Томас - дела.";
			link.l1.go = "Tomas_44";
			AddItems(sld, "gold_dublon", 300);
			AddCharacterExpToSkill(pchar, "Commerce", 200);
		break;
		
		case "Tomas_44":
			dialog.text = "Конечно-конечно. Да пребудет с вами Бог, "+GetFullName(pchar)+"!";
			link.l1 = "До свидания.";
			link.l1.go = "Tomas_45";
		break;
		
		case "Tomas_45":
			DialogExit();
			
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("SentJons_houseS3", "reload2", false);
			LocatorReloadEnterDisable("SentJons_town", "houseS3", false);
			SetFunctionExitFromLocationCondition("DWH_Vizdorovela_3", PChar.location, false);
			
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
			NextDiag.CurrentNode = "Tomas_51";
			
			sld = CharacterFromID("DWH_gypsy");
			LAi_CharacterEnableDialog(sld);
			sld.dialog.filename = "Quest\MiniEvents\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "gypsy_41";
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "Tomas_46":
			dialog.text = "Вы благороднейший человек, "+GetFullName(pchar)+"! Да пребудет с вами Дева Мария! Заходите к нам - в нашем доме вы всегда желанный гость. И ещё, "+pchar.name+", поговорите с цыганкой - она хотела вас увидеть.";
			link.l1 = "Непременно! А теперь, прошу простить - дела.";
			link.l1.go = "Tomas_47";
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
		break;
		
		case "Tomas_47":
			DialogExit();
			
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("SentJons_houseS3", "reload2", false);
			LocatorReloadEnterDisable("SentJons_town", "houseS3", false);
			SetFunctionExitFromLocationCondition("DWH_Vizdorovela_3", PChar.location, false);
			
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
			NextDiag.CurrentNode = "Tomas_51";
			
			sld = CharacterFromID("DWH_gypsy");
			LAi_CharacterEnableDialog(sld);
			sld.dialog.filename = "Quest\MiniEvents\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "gypsy_44";
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "gypsy_41":
			dialog.text = "А вот и ты, соколик! Знала, что снова появишься здесь. Благодаря твоим стараниям девочка выздоровела и теперь порхает, как голубка. Весь город ею восхищается.";
			link.l1 = "Ну, чернобровая, не только моими стараниями, не переоценивай. Это твоё зелье поставило её на ноги, так что, не скрывай своей заслуги.";
			link.l1.go = "gypsy_42";
			DelLandQuestMark(npchar);
		break;
		
		case "gypsy_42":
			dialog.text = "Доброе сердце у тебя, милок, и ум острый! Быть тебе великим человеком - вот моё пророчество.";
			link.l1 = "Хех... ну спасибо, "+npchar.name+".";
			link.l1.go = "gypsy_43";
		break;
		
		case "gypsy_43":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddQuestRecord("DWH", "9");
			CloseQuestHeader("DWH");
			
			AddSimpleRumourCity("Вы слышали? "+GetFullName(pchar)+" достал для дочери Томаса Моррисона снадобье, которое вмиг поставило бедную девочку на ноги!", "SentJons", 10, 1, "");
			AddSimpleRumourCity("Томас Моррисон ежедневно ставит в приходе свечку за здоровье "+GetFullName(pchar)+". Поговаривают, он спас его дочь от затяжной болезни.", "SentJons", 10, 1, "");
			AddSimpleRumourCity("Эстер Моррисон расцвела на глазах - как будто никогда и не болела. Никто толком не может объяснить, что заставило болезнь отступить.", "SentJons", 10, 1, "");
		break;
		
		case "gypsy_44":
			dialog.text = "А вот и ты, соколик! Знала я, что ты появишься здесь вновь. Твоими стараниями девочка выздоровела и порхает, как голубка. Весь город восхищается ею.";
			link.l1 = "Но-но, сама девочку спасла, а хочешь, чтобы я лавры собирал? Так не пойдёт! Ты снадобье готовила, ты её на ноги поставила - тебе и славу принимать.";
			link.l1.go = "gypsy_45";
			DelLandQuestMark(npchar);
		break;
		
		case "gypsy_45":
			dialog.text = "Доброе сердце имеешь соколик, да душу благородную. Есть у меня подарок для тебя - такой, что любой капитан оценит. Держи. Теперь крысам на твоём корабле не будет ни счастья, ни покоя!";
			link.l1 = "Подарок? Неожиданно!";
			link.l1.go = "gypsy_46";
			GiveItem2Character(PChar, "rat_poison");
		break;
		
		case "gypsy_46":
			if (IsCharacterPerkOn(pchar, "Trustworthy"))
			{
				dialog.text = "Душа твоя чиста, вижу я, что не станешь ты жечь мангаросу ради минутного удовольствия. Если она тебе понадобится срочно, приходи ко мне, соколик. Пять стеблей обойдутся тебе в двести дублонов\nТравка эта капризная, сам знаешь, не всякому её найти по силам. Так что не торопи меня - чаще чем раз в месяц не спрашивай, всё равно не добуду.";
			}
			else
			{
				dialog.text = "Душа твоя светла, вижу я - не прост ты, в травах разбираешься не хуже знахарок некоторых. Многое сыскать сумеешь, да не всегда удача улыбнётся. Есть растение редкое, что не каждому найти по плечу. Мангароссой зовётся оно. Коли понадобится - приходи ко мне, соколик. Пять стеблей достану, но даром не отдам - двести дублонов возьму\nТолько травка эта своенравная, так что не торопи меня. Чаще чем раз в месяц не спрашивай - хоть все карты судьбы раскинь, а раньше не добуду.";
			}
			link.l1 = "Ну спасибо тебе, "+npchar.name+".";
			link.l1.go = "gypsy_47";
		break;
		
		case "gypsy_47":
			DialogExit();
			NextDiag.CurrentNode = "gypsy_Mangarosa";
			
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddQuestRecord("DWH", "10");
			CloseQuestHeader("DWH");
			AddQuestRecordInfo("Useful_Acquaintances", "1");
			
			SetTimerFunction("DWH_Mangarosa", 0, 0, 30);
			
			AddSimpleRumourCity("Вы слышали? "+GetFullName(pchar)+" достал для дочери Томаса Моррисона снадобье, которое вмиг поставило бедную девочку на ноги!", "SentJons", 10, 1, "");
			AddSimpleRumourCity("Томас Моррисон ежедневно ставит в приходе свечку за здоровье "+GetFullName(pchar)+". Поговаривают, он спас его дочь от затяжной болезни.", "SentJons", 10, 1, "");
			AddSimpleRumourCity("Эстер Моррисон расцвела на глазах - как будто никогда и не болела. Никто толком не может объяснить, что заставило болезнь отступить.", "SentJons", 10, 1, "");
		break;
		
		case "Tomas_51":
			dialog.text = "Капитан, я всё думаю - не иначе как сам Господь направил вас сюда в нужный час! Вы спасли мою дочь, и я никогда этого не забуду.";
			link.l1 = "Возможно, Томас. Пути Господни неисповедимы.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Tomas_52";
			SetTimerFunction("DWH_Tomas_HelloAgain", 0, 0, 1);
		break;
		
		case "Tomas_52":
			dialog.text = "Хотите вина, капитан? У меня есть нечто особенное для дорогих гостей.";
			link.l1 = "Спасибо, Томас, но, к сожалению, мне пора идти.";
			link.l1.go = "exit";
		break;
		
		case "gypsy_Mangarosa":
			dialog.text = "Чего тебе, соколик?";
			if (CheckAttribute(pchar, "questTemp.DWH_Mangarosa"))
			{
				link.l1 = "Скажи, чернобровая, найдётся ли у тебя мангароса для меня?";
				link.l1.go = "gypsy_Mangarosa_1";
			}
			link.l2 = "Просто решил поздороваться. Мне пора!";
			link.l2.go = "exit";
			NextDiag.TempNode = "gypsy_Mangarosa";
		break;
		
		case "gypsy_Mangarosa_1":
			dialog.text = "Кто ж, как не я, милок, достанет тебе редкость такую? Двести дублонов - и она твоя, пять стеблей, не больше, не меньше.";
			if (PCharDublonsTotal() >= 300)
			{
				link.l1 = "Держи свои дублоны.";
				link.l1.go = "gypsy_Mangarosa_2";
			}
			link.l2 = "Дьявол. У меня нет нужной суммы. Я приду позже.";
			link.l2.go = "exit";
			NextDiag.TempNode = "gypsy_Mangarosa";
		break;
		
		case "gypsy_Mangarosa_2":
			dialog.text = "Вот так-то лучше, милок. Бери. Да смотри, не растрачивай её понапрасну - сам знаешь - мангароса не простая травка. Сила в ней скрыта, что не каждому по плечу.";
			link.l1 = "Не беспокойся, чернобровая, я найду достойное применение её силе.";
			link.l1.go = "gypsy_Mangarosa_3";
			AddItems(pchar, "cannabis7", 5);
			RemoveDublonsFromPCharTotal(300);
		break;
		
		case "gypsy_Mangarosa_3":
			DialogExit();
			
			NextDiag.CurrentNode = "gypsy_Mangarosa";
			DeleteAttribute(pchar, "questTemp.DWH_Mangarosa");
			SetTimerFunction("DWH_Mangarosa", 0, 0, 30);
		break;
	}
}